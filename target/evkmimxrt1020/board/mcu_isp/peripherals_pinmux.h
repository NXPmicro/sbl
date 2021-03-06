/*
 * The Clear BSD License
 * Copyright 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "fsl_device_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! peripheral enable configurations
#define BL_ENABLE_PINMUX_UART1 (BL_CONFIG_LPUART_1)

#define UART1_RX_IOMUXC_MUX_FUNC IOMUXC_GPIO_AD_B0_07_LPUART1_RX
#define UART1_RX_IOMUXC_MUX_GPIO IOMUXC_GPIO_AD_B0_07_GPIO1_IO07
#define UART1_RX_IOMUXC_PAD_DEFAULT 0x000010B0
#define UART1_RX_GPIO_BASE GPIO1
#define UART1_RX_GPIO_PIN_NUM 7 // GPIO_AD_B0_06/GPIO1[6]
#define UART1_RX_GPIO_IRQn GPIO1_Combined_0_15_IRQn
#define UART1_RX_GPIO_IRQHandler GPIO1_Combined_0_15_IRQHandler

#define UART1_TX_IOMUXC_MUX_FUNC IOMUXC_GPIO_AD_B0_06_LPUART1_TX
#define UART1_TX_IOMUXC_PAD_DEFAULT 0x000010B0
#define UART1_TX_GPIO_PIN_NUM 6 // GPIO_AD_B0_7/GPIO1[7]

/*====================== LPUART IOMUXC Definitions ===========================*/
#define SW_MUX_CTL_PAD_LPUART1_TX_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_06
#define SW_PAD_CTL_PAD_LPUART1_TX_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_06
#define SW_MUX_CTL_PAD_LPUART1_RX_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_07
#define SW_PAD_CTL_PAD_LPUART1_RX_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_07
#define LPUART1_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(2)
#define LPUART1_PAD_CTRL                                                                            \
    (IOMUXC_SW_PAD_CTL_PAD_SRE(0) | IOMUXC_SW_PAD_CTL_PAD_DSE(6) | IOMUXC_SW_PAD_CTL_PAD_SPEED(2) | \
     IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUE(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(1))
#define UART1_PULLUP_PAD_CTRL (IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(2))

/*====================== FLEXSPI IOMUXC Definitions ===========================*/
#define SW_MUX_CTL_PAD_FLEXSPIB_DQS_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05
#define SW_MUX_CTL_PAD_FLEXSPIB_DATA3_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_00
#define SW_MUX_CTL_PAD_FLEXSPIB_DATA2_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_03
#define SW_MUX_CTL_PAD_FLEXSPIB_DATA1_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_04
#define SW_MUX_CTL_PAD_FLEXSPIB_DATA0_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_02
#define SW_MUX_CTL_PAD_FLEXSPIB_SS0_B_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04
#define SW_MUX_CTL_PAD_FLEXSPIB_SS1_B_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01
#define SW_MUX_CTL_PAD_FLEXSPIB_SCLK_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_01

#define SW_MUX_CTL_PAD_FLEXSPIA_DQS_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_05
#define SW_MUX_CTL_PAD_FLEXSPIA_SS0_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_11
#define SW_MUX_CTL_PAD_FLEXSPIA_SS1_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00
#define SW_MUX_CTL_PAD_FLEXSPIA_SCLK_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_07
#define SW_MUX_CTL_PAD_FLEXSPIA_DATA0_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_08
#define SW_MUX_CTL_PAD_FLEXSPIA_DATA1_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_10
#define SW_MUX_CTL_PAD_FLEXSPIA_DATA2_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_09
#define SW_MUX_CTL_PAD_FLEXSPIA_DATA3_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_06
#define SW_MUX_CTL_PAD_FLEXSPIA_SCLK_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_01

#define SW_PAD_CTL_PAD_FLEXSPIB_DQS_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05
#define SW_PAD_CTL_PAD_FLEXSPIB_DATA3_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_00
#define SW_PAD_CTL_PAD_FLEXSPIB_DATA2_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_03
#define SW_PAD_CTL_PAD_FLEXSPIB_DATA1_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_04
#define SW_PAD_CTL_PAD_FLEXSPIB_DATA0_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_02
#define SW_PAD_CTL_PAD_FLEXSPIB_SS0_B_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04
#define SW_PAD_CTL_PAD_FLEXSPIB_SS1_B_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01
#define SW_PAD_CTL_PAD_FLEXSPIB_SCLK_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_01

#define SW_PAD_CTL_PAD_FLEXSPIA_DQS_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_05
#define SW_PAD_CTL_PAD_FLEXSPIA_SS0_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_11
#define SW_PAD_CTL_PAD_FLEXSPIA_SS1_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00
#define SW_PAD_CTL_PAD_FLEXSPIA_SCLK_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_07
#define SW_PAD_CTL_PAD_FLEXSPIA_DATA0_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_08
#define SW_PAD_CTL_PAD_FLEXSPIA_DATA1_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_10
#define SW_PAD_CTL_PAD_FLEXSPIA_DATA2_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_09
#define SW_PAD_CTL_PAD_FLEXSPIA_DATA3_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_06
#define SW_PAD_CTL_PAD_FLEXSPIA_SCLK_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_01

#define FLEXSPIA_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(1)
#define FLEXSPIB_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(1)
#define FLEXSPIA_SS1_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(6)
#define FLEXSPIB_SS1_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(6)
#define FLEXSPIB_SS0_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(4)
#define FLEXSPIB_DQS_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(4)

// Fast Slew Rate
// Driver Strength: R0=260Ohm @3.3V, 150Ohm @1.8V, 240 Ohm for DDR, Actual R = R0/6
// Max Speed : 200MHz
// Pull enabled
// Keeper
#define FLEXSPI_SW_PAD_CTL_VAL                                                                      \
    (IOMUXC_SW_PAD_CTL_PAD_SRE(1) | IOMUXC_SW_PAD_CTL_PAD_DSE(6) | IOMUXC_SW_PAD_CTL_PAD_SPEED(3) | \
     IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUE(0) | IOMUXC_SW_PAD_CTL_PAD_PUS(0))

// Fast Slew Rate
// Driver Strength: R0=260Ohm @3.3V, 150Ohm @1.8V, 240 Ohm for DDR, Acutal R = R0/6
// Max Speed : 200MHz
// Pull enabled
// Pull
// 100k ohm pull down resistor
#define FLEXSPI_DQS_SW_PAD_CTL_VAL                                                                  \
    (IOMUXC_SW_PAD_CTL_PAD_SRE(1) | IOMUXC_SW_PAD_CTL_PAD_DSE(6) | IOMUXC_SW_PAD_CTL_PAD_SPEED(3) | \
     IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUE(1) | IOMUXC_SW_PAD_CTL_PAD_PUS(0) |   \
     IOMUXC_SW_PAD_CTL_PAD_HYS(1))

/*====================== FLEXSPI Secondary IOMUXC Definitions ===========================*/
#define SW_MUX_CTL_PAD_FLEXSPIA_SEC_SS0_B_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_05
#define SW_MUX_CTL_PAD_FLEXSPIA_SEC_SCLK_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01
#define SW_MUX_CTL_PAD_FLEXSPIA_SEC_DATA0_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02
#define SW_MUX_CTL_PAD_FLEXSPIA_SEC_DATA1_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_04
#define SW_MUX_CTL_PAD_FLEXSPIA_SEC_DATA2_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03
#define SW_MUX_CTL_PAD_FLEXSPIA_SEC_DATA3_IDX kIOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00

#define SW_PAD_CTL_PAD_FLEXSPIA_SEC_SS0_B_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_05
#define SW_PAD_CTL_PAD_FLEXSPIA_SEC_SCLK_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01
#define SELECT_INPUT_FLEXSPIA_SEC_SCLK_IDX kIOMUXC_FLEXSPI_A_SCLK_SELECT_INPUT
#define SW_PAD_CTL_PAD_FLEXSPIA_SEC_DATA0_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02
#define SELECT_INPUT_FLEXSPIA_SEC_DATA0_IDX kIOMUXC_FLEXSPI_A_DATA0_SELECT_INPUT
#define SW_PAD_CTL_PAD_FLEXSPIA_SEC_DATA1_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_04
#define SELECT_INPUT_FLEXSPIA_SEC_DATA1_IDX kIOMUXC_FLEXSPI_A_DATA1_SELECT_INPUT
#define SW_PAD_CTL_PAD_FLEXSPIA_SEC_DATA2_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03
#define SELECT_INPUT_FLEXSPIA_SEC_DATA2_IDX kIOMUXC_FLEXSPI_A_DATA2_SELECT_INPUT
#define SW_PAD_CTL_PAD_FLEXSPIA_SEC_DATA3_IDX kIOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00
#define SELECT_INPUT_FLEXSPIA_SEC_DATA3_IDX kIOMUXC_FLEXSPI_A_DATA3_SELECT_INPUT

#define FLEXSPIA_SEC_MUX_VAL IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(1)

/*====================== FLEXSPI Reset IOMUXC Definitions ===========================*/
#define SW_MUX_CTL_PAD_FLEXSPI_RESET_IDX 71
#define SW_PAD_CTL_PAD_FLEXSPI_RESET_IDX 71
#define FLEXSPI_RESET_PIN_MUX IOMUXC_SW_MUX_CTL_PAD_MUX_MODE(5)
#define FLEXSPI_RESET_PIN_SW_PAD_CTRL_VAL                                                         \
    (IOMUXC_SW_PAD_CTL_PAD_DSE(6) | IOMUXC_SW_PAD_CTL_PAD_PKE(1) | IOMUXC_SW_PAD_CTL_PAD_PUE(0) | \
     IOMUXC_SW_PAD_CTL_PAD_PUS(0))
#define FLEXSPI_RESET_PIN_GPIO GPIO1
#define FLEXSPI_RESET_PIN_INDEX 29

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
