#! /usr/bin/env python3
#
# Copyright 2017 Linaro Limited
# Copyright 2019 Arm Limited
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import io
import re
import click
import getpass
import imgtool.keys as keys
from imgtool import image
from imgtool.version import decode_version


def gen_rsa2048_sign(keyfile, passwd):
    keys.RSA2048.generate().export_private(path=keyfile, passwd=passwd)


def gen_rsa2048_enc(keyfile, passwd):
    keys.RSA2048.generate().export_private1(path=keyfile, passwd=passwd)


def gen_ecdsa_p256(keyfile, passwd):
    keys.ECDSA256P1.generate().export_private(keyfile, passwd=passwd)


def gen_ecdsa_p224(keyfile, passwd):
    print("TODO: p-224 not yet implemented")


valid_langs = ['c', 'rust']
keygens = {
    'rsa-2048-sign': gen_rsa2048_sign,
    'rsa-2048-enc':  gen_rsa2048_enc,
    'ecdsa-p256':    gen_ecdsa_p256,
    'ecdsa-p224':    gen_ecdsa_p224,
}


def load_key(keyfile):
    # TODO: better handling of invalid pass-phrase
    key = keys.load(keyfile)
    if key is not None:
        return key
    passwd = getpass.getpass("Enter key passphrase: ").encode('utf-8')
    return keys.load(keyfile, passwd)


def get_password():
    while True:
        passwd = getpass.getpass("Enter key passphrase: ")
        passwd2 = getpass.getpass("Reenter passphrase: ")
        if passwd == passwd2:
            break
        print("Passwords do not match, try again")

    # Password must be bytes, always use UTF-8 for consistent
    # encoding.
    return passwd.encode('utf-8')


@click.option('-p', '--password', is_flag=True,
              help='Prompt for password to protect key')
@click.option('-t', '--type', metavar='type', required=True,
              type=click.Choice(keygens.keys()),
              help='support ras-2048-sign or ecdsa-p256')
@click.option('-k', '--key', metavar='filename', required=True)
@click.command(help='Generate pub/private keypair')
def keygen(key, type, password):
    password = get_password() if password else None
    keygens[type](key, password)
    if type == 'rsa-2048-enc':
        name = key.split('.')
        k = keys.load(key)
        ccode = io.StringIO()
        k.emit_c(file=ccode, type='priv')
        file = open(name[0] + '.c', 'w')
        file.write(ccode.getvalue())
        file.close()
        print(ccode.getvalue())


@click.option('-l', '--lang', metavar='lang', default=valid_langs[0],
              type=click.Choice(valid_langs))
@click.option('-t', '--type', metavar='type', required=True,
              type=click.Choice(['sign', 'enc']),
              help='choose the key type: sign or enc')
@click.option('-k', '--key', metavar='filename', required=True)
@click.option('-o', '--out', metavar='filename', required=True)
@click.command(help='Get public key from keypair')
def getpub(out, key, type, lang):
    name = out.rsplit('.', 1)
    key = load_key(key)
    if key is None:
        print("Invalid passphrase")
    elif lang == 'c':
        ccode = io.StringIO()
        key.emit_c(file=ccode)

        if type == 'sign':
            file = open(name[0] + '.c', 'w')
            file.write(ccode.getvalue())
            file.close()
            print(ccode.getvalue())

        key.export_public(out)
    elif lang == 'rust':
        key.emit_rust()
    else:
        raise ValueError("BUG: should never get here!")


def validate_version(ctx, param, value):
    try:
        decode_version(value)
        return value
    except ValueError as e:
        raise click.BadParameter("{}".format(e))


def validate_header_size(ctx, param, value):
    min_hdr_size = image.IMAGE_HEADER_SIZE
    if value < min_hdr_size:
        raise click.BadParameter(
            "Minimum value for -H/--header-size is {}".format(min_hdr_size))
    return value


def get_dependencies(ctx, param, value):
    if value is not None:
        versions = []
        images = re.findall(r"\((\d+)", value)
        if len(images) == 0:
            raise click.BadParameter(
                "Image dependency format is invalid: {}".format(value))
        raw_versions = re.findall(r",\s*([0-9.+]+)\)", value)
        if len(images) != len(raw_versions):
            raise click.BadParameter(
                '''There's a mismatch between the number of dependency images
                and versions in: {}'''.format(value))
        for raw_version in raw_versions:
            try:
                versions.append(decode_version(raw_version))
            except ValueError as e:
                raise click.BadParameter("{}".format(e))
        dependencies = dict()
        dependencies[image.DEP_IMAGES_KEY] = images
        dependencies[image.DEP_VERSIONS_KEY] = versions
        return dependencies


class BasedIntParamType(click.ParamType):
    name = 'integer'

    def convert(self, value, param, ctx):
        try:
            if value[:2].lower() == '0x':
                return int(value[2:], 16)
            elif value[:1] == '0':
                return int(value, 8)
            return int(value, 10)
        except ValueError:
            self.fail('%s is not a valid integer' % value, param, ctx)


@click.argument('outfile')
@click.argument('infile')
@click.option('-E', '--encrypt', metavar='filename',
              help='Encrypt image using the provided public key')
@click.option('-e', '--endian', type=click.Choice(['little', 'big']),
              default='little', help="Select little or big endian")
@click.option('--overwrite-only', default=False, is_flag=True,
              help='Use overwrite-only instead of swap upgrades')
@click.option('-M', '--max-sectors', type=int,
              help='When padding allow for this amount of sectors (defaults to 128)')
@click.option('--pad', default=False, is_flag=True,
              help='Pad image to --slot-size bytes, adding trailer magic')
@click.option('-S', '--slot-size', type=BasedIntParamType(), required=True,
              help='Size of the slot where the image will be written')
@click.option('--pad-header', default=False, is_flag=True,
              help='Add --header-size zeroed bytes at the beginning of the image')
@click.option('-H', '--header-size', callback=validate_header_size,
              type=BasedIntParamType(), required=True)
@click.option('-d', '--dependencies', callback=get_dependencies,
              required=False, help='''Add dependence on another image, format:
              "(<image_ID>,<image_version>), ... "''')
@click.option('-v', '--version', callback=validate_version,  required=True)
@click.option('--align', type=click.Choice(['1', '2', '4', '8']),
              required=True)
@click.option('-k', '--key', metavar='filename')
@click.option('--key-info', help='Add image key info block in the MCUBOOT header')
@click.command(help='''Create a signed or unsigned image\n
               INFILE and OUTFILE are parsed as Intel HEX if the params have
               .hex extension, othewise binary format is used''')
def sign(key, align, version, header_size, pad_header, slot_size, pad,
         max_sectors, overwrite_only, endian, encrypt, infile, outfile,
         dependencies, key_info):
    img = image.Image(version=decode_version(version), header_size=header_size,
                      pad_header=pad_header, pad=pad, align=int(align),
                      slot_size=slot_size, max_sectors=max_sectors,
                      overwrite_only=overwrite_only, endian=endian, key_info=key_info)
    img.load(infile)
    key = load_key(key) if key else None
    enckey = load_key(encrypt) if encrypt else None
    if enckey:
        if not isinstance(enckey, (keys.RSA2048, keys.RSA2048Public)):
            raise Exception("Encryption only available with RSA key")
        if key and not isinstance(key, keys.RSA2048):
            raise Exception("Signing only available with private RSA key")
    img.create(key, enckey, dependencies)
    img.save(outfile)


class AliasesGroup(click.Group):

    _aliases = {
        "create": "sign",
    }

    def list_commands(self, ctx):
        cmds = [k for k in self.commands]
        aliases = [k for k in self._aliases]
        return sorted(cmds + aliases)

    def get_command(self, ctx, cmd_name):
        rv = click.Group.get_command(self, ctx, cmd_name)
        if rv is not None:
            return rv
        if cmd_name in self._aliases:
            return click.Group.get_command(self, ctx, self._aliases[cmd_name])
        return None


@click.command(cls=AliasesGroup,
               context_settings=dict(help_option_names=['-h', '--help']))
def imgtool():
    pass


imgtool.add_command(keygen)
imgtool.add_command(getpub)
imgtool.add_command(sign)


if __name__ == '__main__':
    imgtool()
