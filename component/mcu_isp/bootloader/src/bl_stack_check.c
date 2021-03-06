/*
* Copyright 2014-2016 Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*
*/

#include "bootloader/bootloader.h"
#include "bootloader_common.h"

#if BL_FEATURE_STACK_CHECK
////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////
#if defined(__ICCARM__)
__interwork __nounwind __noreturn void __stack_chk_fail(void);
#else
#warning Need to specific the toolchain prototype.
#endif

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////
#if defined(__ICCARM__)
__no_init uint32_t __stack_chk_guard;
#elif defined(__CC_ARM)
void *__stack_chk_guard BL_SECTION(".stack_guard");
#else
#error Un-supported toolchain.
#endif

////////////////////////////////////////////////////////////////////////////////
// Codes
////////////////////////////////////////////////////////////////////////////////
void __stack_chk_fail(void)
{
    target_reset();

    // Should never go here.
    go_fatal_mode();

    /*
     * Add infinite loop here to avoid the following warning.
     * Warning[Pe1305]: function declared with "noreturn" does return
     */
    while (1)
        ;
}

void stack_check_init(void)
{
#warning Need to add random word generator code here
#if defined(__ICCARM__)
    __stack_chk_guard = 0x1234fedc;
#elif defined(__CC_ARM)
    *((uint32_t *)__stack_chk_guard) = 0x1234fedc;
#endif
}

#endif // #if BL_FEATURE_STACK_CHECK
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
