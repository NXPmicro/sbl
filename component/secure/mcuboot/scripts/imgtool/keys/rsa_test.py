# Copyright 2019 Cypress Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0
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

"""
Tests for RSA keys
"""

import io
import os
import sys
import tempfile
import unittest

from cryptography.exceptions import InvalidSignature
from cryptography.hazmat.primitives.asymmetric.padding import PSS, MGF1
from cryptography.hazmat.primitives.hashes import SHA256

# Setup sys path so 'imgtool' is in it.
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../..')))

from imgtool.keys import load, RSA2048, RSAUsageError

class KeyGeneration(unittest.TestCase):

    '''def setUp(self):
        self.test_dir = tempfile.TemporaryDirectory()'''

    def tname(self, base):
	    #self.test_dir.name
        return os.path.join('.', base)

    '''def tearDown(self):
        self.test_dir.cleanup()'''

    def test_keygen(self):
        #print("Filename = " + __file__, file=sys.stdout)
        name1 = self.tname("keygen.pem")
        k = RSA2048.generate()
        #b'secret'
        k.export_private1(name1, None)

        # Try loading the key without a password.
        #self.assertIsNone(load(name1))

        #'enc-rsa2048-priv.pem'
        #b'secret'
        k2 = load(name1, None)

        pubname = self.tname('keygen-pub.pem')
        k2.export_public(pubname)
        pk2 = load(pubname)

        # We should be able to export the public key from the loaded
        # public key, but not the private key.
        pk2.export_public(self.tname('keygen-pub2.pem'))
        self.assertRaises(RSAUsageError, pk2.export_private, self.tname('keygen-priv2.pem'))

    def test_emit(self):
        """Basic sanity check on the code emitters."""
        k = RSA2048.generate()

        ccode = io.StringIO()
        k.emit_c(file=ccode)
        self.assertIn("rsa_pub_key", ccode.getvalue())
        self.assertIn("rsa_pub_key_len", ccode.getvalue())

        rustcode = io.StringIO()
        k.emit_rust(rustcode)
        self.assertIn("RSA_PUB_KEY", rustcode.getvalue())

    def test_emit_pub(self):
        """Basic sanity check on the code emitters, from public key."""
        pubname = self.tname("public.pem")
        k = RSA2048.generate()
        k.export_public(pubname)

        k2 = load(pubname)

        ccode = io.StringIO()
        k2.emit_c(file=ccode)
        self.assertIn("rsa_pub_key", ccode.getvalue())
        self.assertIn("rsa_pub_key_len", ccode.getvalue())
        
        k3 = load('imxrt1060.pem')
        k3.emit_c()
        k4 = load('enc-rsa2048-priv.pem')
        k4.emit_c(type='priv')

        rustcode = io.StringIO()
        k2.emit_rust(rustcode)
        self.assertIn("RSA_PUB_KEY", rustcode.getvalue())

    def test_sig(self):
        k = RSA2048.generate()
        buf = b'This is the message'
        sig = k.sign(buf)

        # The code doesn't have any verification, so verify this
        # manually.
        k.key.public_key().verify(
                signature=sig,
                data=buf,
                padding=PSS(mgf=MGF1(SHA256()), salt_length=32),
                algorithm=SHA256())

        # Modify the message to make sure the signature fails.
        self.assertRaises(InvalidSignature,
                k.key.public_key().verify,
                signature=sig,
                data=b'This is thE message',
                padding=PSS(mgf=MGF1(SHA256()), salt_length=32),
                algorithm=SHA256())

if __name__ == '__main__':
    unittest.main()
