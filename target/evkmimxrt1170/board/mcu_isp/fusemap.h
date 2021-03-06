/*
 * Copyright 2018-2021 NXP
 *
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __FUSEMAP_H__
#define __FUSEMAP_H__

#include "fsl_device_registers.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

#define FUSE_BANK0_OFFSET 0x800
#define HW_FUSE_REG_ADDR(n) (OCOTP_BASE + FUSE_BANK0_OFFSET + ((n)*0x10))
#define HW_OCOTP_REG_RD(n) (*(volatile uint32_t *)HW_FUSE_REG_ADDR(n))

/* ======================== Boot Mode ================================= */
#define FUSE_BOOTMODE_SHIFT ((uint8_t)24)
#define FUSE_BOOTMODE_MASK ((uint32_t)(3 << FUSE_BOOTMODE_SHIFT))
#define FUSE_BOOTMODE_VALUE ((SRC->SBMR2 & FUSE_BOOTMODE_MASK) >> FUSE_BOOTMODE_SHIFT)

#define ROM_BOOTMODE_INTERNAL_FUSE (0)
#define ROM_BOOTMODE_SERIAL (1)
#define ROM_BOOTMODE_INTERNAL (2)
#define ROM_BOOTMODE_TEST (3)

/* ======================== Boot Configuration ================================= */
/* TEST MODE */
#define FUSE_TESTMODE_SHIFT ((uint8_t)27)
#define FUSE_TESTMODE_MASK ((uint32_t)(7 << FUSE_TESTMODE_SHIFT))
#define FUSE_TESTMODE_VALUE ((SRC->SBMR2 & FUSE_TESTMODE_MASK) >> FUSE_TESTMODE_SHIFT)

/* SEC_CONFIG */
#define FUSE_SECURE_CONFIG_SHIFT ((uint8_t)0)
#define FUSE_SECURE_CONFIG_MASK ((uint32_t)(3 << FUSE_SECURE_CONFIG_SHIFT))
#define FUSE_SECURE_CONFIG_VALUE ((SRC->SBMR2 & FUSE_SECURE_CONFIG_MASK) >> FUSE_SECURE_CONFIG_SHIFT)

/* DIR_BT_DIS */
#define FUSE_DIR_BT_DIS_SHIFT ((uint8_t)3)
#define FUSE_DIR_BT_DIS_MASK ((uint32_t)(1 << FUSE_DIR_BT_DIS_SHIFT))
#define FUSE_DIR_BT_DIS_VALUE ((HW_OCOTP_REG_RD(0x16) & FUSE_DIR_BT_DIS_MASK) >> FUSE_DIR_BT_DIS_SHIFT)

/* BT_FUSE_SEL */
#define FUSE_BT_FUSE_SEL_SHIFT ((uint8_t)4)
#define FUSE_BT_FUSE_SEL_MASK ((uint32_t)(1 << FUSE_BT_FUSE_SEL_SHIFT))
#define FUSE_BT_FUSE_SEL_VALUE ((HW_OCOTP_REG_RD(0x16) & FUSE_BT_FUSE_SEL_MASK) >> FUSE_BT_FUSE_SEL_SHIFT)

/* BT_CORE_SEL */
#define FUSE_BT_CORE_SEL_SHIFT ((uint8_t)12)
#define FUSE_BT_CORE_SEL_MASK ((uint32_t)(1 << FUSE_BT_CORE_SEL_SHIFT))
#define FUSE_BT_CORE_SEL_VALUE ((HW_OCOTP_REG_RD(0x16) & FUSE_BT_FUSE_SEL_MASK) >> FUSE_BT_FUSE_SEL_SHIFT)

/* BOOT DEVICE */
#define FUSE_BOOT_DEVICE_SHIFT ((uint8_t)4)
#define FUSE_BOOT_DEVICE_MASK ((uint32_t)(0xf << FUSE_BOOT_DEVICE_SHIFT))
#define FUSE_BOOT_DEVICE_VALUE ((SRC->SBMR1 & FUSE_BOOT_DEVICE_MASK) >> FUSE_BOOT_DEVICE_SHIFT)

#define FUSE_BOOT_MSI_PART_SHIFT (5)
#define FUSE_BOOT_MSI_PART_MASK (1u << FUSE_BOOT_MSI_PART_SHIFT)
#define FUSE_BOOT_MSI_PART_VALUE ((HW_OCOTP_REG_RD(0x13) & FUSE_BOOT_MSI_PART_MASK) >> FUSE_BOOT_MSI_PART_SHIFT)

/* SPEED_LIMIT */
#define FUSE_SPEED_LIMIT_SHIFT (2)
#define FUSE_SPEED_LIMIT_MASK (1u << FUSE_SPEED_LIMIT_SHIFT)
#define FUSE_SPEED_LIMIT_VALUE ((HW_OCOTP_REG_RD(0x07) & FUSE_SPEED_LIMIT_MASK) >> FUSE_SPEED_LIMIT_SHIFT)

/* ======================== FlexSPI NOR Boot ================================= */
/* Encrypted XIP */
#define FUSE_ENCRYPT_XIP_SHIFT 0x01
#define FUSE_ENCRYPT_XIP_MASK (1u << FUSE_ENCRYPT_XIP_SHIFT)
#define FUSE_ENCRYPT_XIP_VALUE ((SRC->SBMR1 & FUSE_ENCRYPT_XIP_MASK) >> FUSE_ENCRYPT_XIP_SHIFT)

/* FLASH Auto Probe */
#define FUSE_XSPI_FLASH_AUTO_PROBE_EN_SHIFT 0x00
#define FUSE_XSPI_FLASH_AUTO_PROBE_EN_MASK (1u << FUSE_XSPI_FLASH_AUTO_PROBE_EN_SHIFT)
#define FUSE_XSPI_FLASH_AUTO_PROBE_EN_VALUE \
    \
((SRC->SBMR1 & FUSE_XSPI_FLASH_AUTO_PROBE_EN_MASK) >> FUSE_XSPI_FLASH_AUTO_PROBE_EN_SHIFT)

/* FLASH Auto Probe Type */
#define FUSE_XSPI_FLASH_AUTO_PROBE_TYPE_SHIFT 0x02
#define FUSE_XSPI_FLASH_AUTO_PROBE_TYPE_MASK (0x03u << FUSE_XSPI_FLASH_AUTO_PROBE_TYPE_SHIFT)
#define FUSE_XSPI_FLASH_AUTO_PROBE_TYPE_VALUE \
    \
((SRC->SBMR1 & FUSE_XSPI_FLASH_AUTO_PROBE_TYPE_MASK) >> FUSE_XSPI_FLASH_AUTO_PROBE_TYPE_SHIFT)

/* Flash Type */
#define FUSE_FLASH_TYPE_SHIFT ((uint8_t)8)
#define FUSE_FLASH_TYPE_MASK (0x07 << FUSE_FLASH_TYPE_SHIFT)
#define FUSE_FLASH_TYPE_VALUE ((SRC->SBMR1 & FUSE_FLASH_TYPE_MASK) >> FUSE_FLASH_TYPE_SHIFT)
/* FlexSPI Index */
#define FUSE_FLEXSPI_INSTANCE_SHIFT ((uint8_t)11)
#define FUSE_FLEXSPI_INSTANCE_MASK (0x01 << FUSE_FLEXSPI_INSTANCE_SHIFT)
#define FUSE_FLEXSPI_INSTANCE_VALUE ((SRC->SBMR1 & FUSE_FLEXSPI_INSTANCE_MASK) >> FUSE_FLEXSPI_INSTANCE_SHIFT)

/* Delay-Cell_Num */
#define FUSE_DELAY_CELL_NUM_SHIFT ((uint8_t)8)
#define FUSE_DELAY_CELL_NUM_MASK (0x7f << FUSE_DELAY_CELL_NUM_SHIFT)
#define FUSE_DELAY_CELL_NUM_VALUE ((HW_OCOTP_REG_RD(0x19) & FUSE_DELAY_CELL_NUM_MASK) >> FUSE_DELAY_CELL_NUM_SHIFT)

/* QSPI RESET pin enable */
#define FUSE_FLEXSPI_RESET_PIN_ENABLE_SHIFT (7U)
#define FUSE_FLEXSPI_RESET_PIN_ENABLE_MASK (1U << FUSE_FLEXSPI_RESET_PIN_ENABLE_SHIFT)
#define FUSE_FLEXSPI_RESET_PIN_ENABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_FLEXSPI_RESET_PIN_ENABLE_MASK) >> FUSE_FLEXSPI_RESET_PIN_ENABLE_SHIFT)

/* FlexSPI JEDEC HW reset enable */
#define FUSE_FLEXSPI_JEDEC_HW_RESET_PIN_ENABLE_SHIFT (6U)
#define FUSE_FLEXSPI_JEDEC_HW_RESET_PIN_ENABLE_MASK (1U << FUSE_FLEXSPI_JEDEC_HW_RESET_PIN_ENABLE_SHIFT)
#define FUSE_FLEXSPI_JEDEC_HW_RESET_PIN_ENABLE_VALUE                          \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_FLEXSPI_JEDEC_HW_RESET_PIN_ENABLE_MASK) >> \
     FUSE_FLEXSPI_JEDEC_HW_RESET_PIN_ENABLE_SHIFT)

/* FlexSPI RESET PIN select */
#define FUSE_FLEXSPI_RESET_PIN_SEL_SHIFT (5U)
#define FUSE_FLEXSPI_RESET_PIN_SEL_MASK (1U << FUSE_FLEXSPI_RESET_PIN_SEL_SHIFT)
#define FUSE_FLEXSPI_RESET_PIN_SEL_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_FLEXSPI_RESET_PIN_SEL_MASK) >> FUSE_FLEXSPI_RESET_PIN_SEL_SHIFT)

/* Hold_Time */
#define FUSE_HOLD_TIME_SHIFT (3u)
#define FUSE_HOLD_TIME_MASK (0x03u << FUSE_HOLD_TIME_SHIFT)
#define FUSE_HOLD_TIME_VALUE ((HW_OCOTP_REG_RD(0x48) & FUSE_HOLD_TIME_MASK) >> FUSE_HOLD_TIME_SHIFT)

/* xSPI FLASH Frequency */
#define FUSE_XSPI_FLASH_FREQ_SHIFT (0u)
#define FUSE_XSPI_FLASH_FREQ_MASK (0x7u << FUSE_XSPI_FLASH_FREQ_SHIFT)
#define FUSE_XSPI_FLASH_FREQ_VALUE ((HW_OCOTP_REG_RD(0x48) & FUSE_XSPI_FLASH_FREQ_MASK) >> FUSE_XSPI_FLASH_FREQ_SHIFT)

/* xSPI FLASH Dummy Cycle */
#define FUSE_XSPI_FLASH_DUMMY_CYCLE_SHIFT (8u)
#define FUSE_XSPI_FLASH_DUMMY_CYCLE_MASK (0xfu << FUSE_XSPI_FLASH_DUMMY_CYCLE_SHIFT)
#define FUSE_XSPI_FLASH_DUMMY_CYCLE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_XSPI_FLASH_DUMMY_CYCLE_MASK) >> FUSE_XSPI_FLASH_DUMMY_CYCLE_SHIFT)

/* xSPI FLASH image size */
#define FUSE_XSPI_FLASH_IMG_SIZE_SHIFT (12u)
#define FUSE_XSPI_FLASH_IMG_SIZE_MASK (0x0fu << FUSE_XSPI_FLASH_IMG_SIZE_SHIFT)
#define FUSE_XSPI_FLASH_IMG_SIZE_VALUE \
    \
((HW_OCOTP_REG_RD(0x48) & FUSE_XSPI_FLASH_IMG_SIZE_MASK) >> FUSE_XSPI_FLASH_IMG_SIZE_SHIFT)

/* xSPI FLASH_SEC_IMAGE_OFFSET */
#define FUSE_XSPI_FLASH_SEC_IMG_OFFSET_SHIFT (16u)
#define FUSE_XSPI_FLASH_SEC_IMG_OFFSET_MASK (0xffu << FUSE_XSPI_FLASH_SEC_IMG_OFFSET_SHIFT)
#define FUSE_XSPI_FLASH_SEC_IMG_OFFSET_VALUE \
    \
((HW_OCOTP_REG_RD(0x48) & FUSE_XSPI_FLASH_SEC_IMG_OFFSET_MASK) >> FUSE_XSPI_FLASH_SEC_IMG_OFFSET_SHIFT)

/* FLEXSPI PIN Group Selection */
#define FUSE_FLEXSPI_PIN_GROUP_SEL_SHIFT (10u)
#define FUSE_FLEXSPI_PIN_GROUP_SEL_MASK (0x1u << FUSE_FLEXSPI_PIN_GROUP_SEL_SHIFT)
#define FUSE_FLEXSPI_PIN_GROUP_SEL_VALUE \
    \
((HW_OCOTP_REG_RD(0x1A) & FUSE_FLEXSPI_PIN_GROUP_SEL_MASK) >> FUSE_FLEXSPI_PIN_GROUP_SEL_SHIFT)

/* FLEXSPI DQS Pin Group Selection */
#define FUSE_FLEXSPI_DQS_PIN_SEL_SHIFT (11u)
#define FUSE_FLEXSPI_DQS_PIN_SEL_MASK (0x1u << FUSE_FLEXSPI_DQS_PIN_SEL_SHIFT)
#define FUSE_FLEXSPI_DQS_PIN_SEL_VALUE \
    \
((HW_OCOTP_REG_RD(0x1A) & FUSE_FLEXSPI_DQS_PIN_SEL_MASK) >> FUSE_FLEXSPI_DQS_PIN_SEL_SHIFT)

/* FLEXSPI CONNECTION Selection */
#define FUSE_FLEXSPI_CONNECTION_SEL_SHIFT (8u)
#define FUSE_FLEXSPI_CONNECTION_SEL_MASK (0x3u << FUSE_FLEXSPI_CONNECTION_SEL_SHIFT)
#define FUSE_FLEXSPI_CONNECTION_SEL_VALUE \
    \
((HW_OCOTP_REG_RD(0x1A) & FUSE_FLEXSPI_CONNECTION_SEL_MASK) >> FUSE_FLEXSPI_CONNECTION_SEL_SHIFT)

/* FlexSPI PAD SETTING ENABLE */
#define FUSE_FLEXSPI_PAD_SETTING_EN_SHIFT (8u)
#define FUSE_FLEXSPI_PAD_SETTING_EN_MASK (0x1u << FUSE_FLEXSPI_PAD_SETTING_EN_SHIFT)
#define FUSE_FLEXSPI_PAD_SETTING_EN_VALUE \
    \
((HW_OCOTP_REG_RD(0x19) & FUSE_FLEXSPI_PAD_SETTING_EN_MASK) >> FUSE_FLEXSPI_PAD_SETTING_EN_SHIFT)

/* FlexSPI Pad setting override value */
#define FUSE_FLEXSPI_PAD_SETTING_OVERRIDE_SHIFT (8u)
#define FUSE_FLEXSPI_PAD_SETTING_OVERRIDE_MASK (0x7u << FUSE_FLEXSPI_PAD_SETTING_OVERRIDE_SHIFT)
#define FUSE_FLEXSPI_PAD_SETTING_OVERRIDE_VALUE \
    \
((HW_OCOTP_REG_RD(0x47) & FUSE_FLEXSPI_PAD_SETTING_OVERRIDE_MASK) >> FUSE_FLEXSPI_PAD_SETTING_OVERRIDE_SHIFT)

/* ====================== FlexSPI NAND Boot ================================= */
/* Safe Frequency */
#define FUSE_SAFE_FREQ_SHIFT ((uint8_t)5)
#define FUSE_SAFE_FREQ_MASK (1u << FUSE_SAFE_FREQ_SHIFT)
#define FUSE_SAFE_FREQ_VALUE ((SRC->SBMR1 & FUSE_SAFE_FREQ_MASK) >> FUSE_SAFE_FREQ_SHIFT)

/* COL_Address_width */
#define FUSE_COL_ADDRESS_WIDTH_SHIFT ((uint8_t)4)
#define FUSE_COL_ADDRESS_WIDTH_MASK (1u << FUSE_COL_ADDRESS_WIDTH_SHIFT)
#define FUSE_COL_ADDRESS_WIDTH_VALUE ((SRC->SBMR1 & FUSE_COL_ADDRESS_WIDTH_MASK) >> FUSE_COL_ADDRESS_WIDTH_SHIFT)

/* Boot_Search_Stride */
#define FUSE_SPI_NAND_HOLD_TIME_SHIFT ((uint8_t)2)
#define FUSE_SPI_NAND_HOLD_TIME_MASK (3u << FUSE_SPI_NAND_HOLD_TIME_SHIFT)
#define FUSE_SPI_NAND_HOLD_TIME_VALUE ((SRC->SBMR1 & FUSE_SPI_NAND_HOLD_TIME_MASK) >> FUSE_SPI_NAND_HOLD_TIME_SHIFT)

/* Boot_Search_Stride */
#define FUSE_BOOT_SEARCH_STRIDE_SHIFT ((uint8_t)0)
#define FUSE_BOOT_SEARCH_STRIDE_MASK (3u << FUSE_BOOT_SEARCH_STRIDE_SHIFT)
#define FUSE_BOOT_SEARCH_STRIDE_VALUE ((SRC->SBMR1 & FUSE_BOOT_SEARCH_STRIDE_MASK) >> FUSE_BOOT_SEARCH_STRIDE_SHIFT)

/* Boot_Search_Count */
#define FUSE_BOOT_SEARCH_COUNT_SHIFT ((uint8_t)8)
#define FUSE_BOOT_SEARCH_COUNT_MASK (1u << FUSE_BOOT_SEARCH_COUNT_SHIFT)
#define FUSE_BOOT_SEARCH_COUNT_VALUE ((SRC->SBMR1 & FUSE_BOOT_SEARCH_COUNT_MASK) >> FUSE_BOOT_SEARCH_COUNT_SHIFT)

/* CS_Interval */
#define FUSE_CS_INTERVAL_SHIFT ((uint8_t)9)
#define FUSE_CS_INTERVAL_MASK (0x3u << FUSE_CS_INTERVAL_SHIFT)
#define FUSE_CS_INTERVAL_VALUE ((SRC->SBMR1 & FUSE_CS_INTERVAL_MASK) >> FUSE_CS_INTERVAL_SHIFT)

/* SPI NAND Boot - override Busy Offset */
#define FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_OVERRIDE_SHIFT ((uint8_t)7)
#define FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_OVERRIDE_MASK (1u << FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_OVERRIDE_SHIFT)
#define FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_OVERRIDE_VALUE                          \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_OVERRIDE_MASK) >> \
     FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_OVERRIDE_SHIFT)

/* SPI NAND Boot - Busy Bit Offset */
#define FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_SHIFT ((uint8_t)8)
#define FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_MASK (0x3fu << FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_SHIFT)
#define FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_MASK) >> FUSE_SPI_NAND_BOOT_BUSY_BIT_OFFSET_SHIFT)

/* Bypass_ECC_Read */
#define FUSE_BYPASS_ECC_READ_SHIFT ((uint8_t)14)
#define FUSE_BYPASS_ECC_READ_MASK (1u << FUSE_BYPASS_ECC_READ_SHIFT)
#define FUSE_BYPASS_ECC_READ_VALUE ((HW_OCOTP_REG_RD(0x48) & FUSE_BYPASS_ECC_READ_MASK) >> FUSE_BYPASS_ECC_READ_SHIFT)

/* Bypass_Read_Status */
#define FUSE_BYPASS_READ_STATUS_SHIFT ((uint8_t)15)
#define FUSE_BYPASS_READ_STATUS_MASK (1u << FUSE_BYPASS_READ_STATUS_SHIFT)
#define FUSE_BYPASS_READ_STATUS_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_BYPASS_READ_STATUS_MASK) >> FUSE_BYPASS_READ_STATUS_SHIFT)

/* SPI NAND BOOT - Page read time */
#define FUSE_SPI_NAND_BOOT_PAGE_RD_TIME_MASK 0x00003F00
#define FUSE_SPI_NAND_BOOT_PAGE_RD_TIME_SHIFT ((uint8_t)8)
#define FUSE_SPI_NAND_BOOT_PAGE_FRD_TIME_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SPI_NAND_BOOT_PAGE_RD_TIME_MASK) >> FUSE_SPI_NAND_BOOT_PAGE_RD_TIME_SHIFT)

/* SPI NAND BOOT - page read cmd */
#define FUSE_SPI_NAND_BOOT_PAGE_RD_CMD_SHIFT ((uint8_t)16)
#define FUSE_SPI_NAND_BOOT_PAGE_RD_CMD_MASK (0xffu << FUSE_SPI_NAND_BOOT_PAGE_RD_CMD_SHIFT)
#define FUSE_SPI_NAND_BOOT_PAGE_RD_CMD_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SPI_NAND_BOOT_PAGE_RD_CMD_MASK) >> FUSE_SPI_NAND_BOOT_PAGE_RD_CMD_SHIFT)

/* SPI NAND BOOT - cache read cmd */
#define FUSE_SPI_NAND_BOOT_CACHE_RD_CMD_SHIFT ((uint8_t)24)
#define FUSE_SPI_NAND_BOOT_CACHE_RD_CMD_MASK (0xFFu << FUSE_SPI_NAND_BOOT_CACHE_RD_CMD_SHIFT)
#define FUSE_SPI_NAND_BOOT_CACHE_RD_CMD_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SPI_NAND_BOOT_CACHE_RD_CMD_MASK) >> FUSE_SPI_NAND_BOOT_CACHE_RD_CMD_SHIFT)

/* ======================== SEMC NAND Boot ================================= */
/* Boot_Search_Count */
#define FUSE_SEMC_NAND_SEARCH_COUNT_SHIFT ((uint8_t)0)
#define FUSE_SEMC_NAND_SEARCH_COUNT_MASK (1u << FUSE_SEMC_NAND_SEARCH_COUNT_SHIFT)
#define FUSE_SEMC_NAND_SEARCH_COUNT_VALUE \
    ((SRC->SBMR1 & FUSE_SEMC_NAND_SEARCH_COUNT_MASK) >> FUSE_SEMC_NAND_SEARCH_COUNT_SHIFT)

/* Boot_Search_Stride  */
#define FUSE_SEMC_NAND_SEARCH_STRIDE_SHIFT ((uint8_t)1)
#define FUSE_SEMC_NAND_SEARCH_STRIDE_MASK (0xFu << FUSE_SEMC_NAND_SEARCH_STRIDE_SHIFT)
#define FUSE_SEMC_NAND_SEARCH_STRIDE_VALUE \
    ((SRC->SBMR1 & FUSE_SEMC_NAND_SEARCH_STRIDE_MASK) >> FUSE_SEMC_NAND_SEARCH_STRIDE_SHIFT)

/* ONFI compliant */
#define FUSE_SEMC_NAND_ONFI_COMPLIANT_SHIFT ((uint8_t)8)
#define FUSE_SEMC_NAND_ONFI_COMPLIANT_MASK (1u << FUSE_SEMC_NAND_ONFI_COMPLIANT_SHIFT)
#define FUSE_SEMC_NAND_ONFI_COMPLIANT_VALUE \
    ((SRC->SBMR1 & FUSE_SEMC_NAND_ONFI_COMPLIANT_MASK) >> FUSE_SEMC_NAND_ONFI_COMPLIANT_SHIFT)

/* EDO mode */
#define FUSE_SEMC_NAND_EDO_MODE_SHIFT ((uint8_t)9)
#define FUSE_SEMC_NAND_EDO_MODE_MASK (1u << FUSE_SEMC_NAND_EDO_MODE_SHIFT)
#define FUSE_SEMC_NAND_EDO_MODE_VALUE ((SRC->SBMR1 & FUSE_SEMC_NAND_EDO_MODE_MASK) >> FUSE_SEMC_NAND_EDO_MODE_SHIFT)

/* Memory Access Command */
#define FUSE_SEMC_NAND_ACCESS_COMMAND_SHIFT ((uint8_t)10)
#define FUSE_SEMC_NAND_ACCESS_COMMAND_MASK (1u << FUSE_SEMC_NAND_ACCESS_COMMAND_SHIFT)
#define FUSE_SEMC_NAND_ACCESS_COMMAND_VALUE \
    ((SRC->SBMR1 & FUSE_SEMC_NAND_ACCESS_COMMAND_MASK) >> FUSE_SEMC_NAND_ACCESS_COMMAND_SHIFT)

/* I/O Port_width */
#define FUSE_SEMC_NAND_IO_PORT_WIDTH_SHIFT ((uint8_t)3)
#define FUSE_SEMC_NAND_IO_PORT_WIDTH_MASK (1u << FUSE_SEMC_NAND_IO_PORT_WIDTH_SHIFT)
#define FUSE_SEMC_NAND_IO_PORT_WIDTH_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_IO_PORT_WIDTH_MASK) >> FUSE_SEMC_NAND_IO_PORT_WIDTH_SHIFT)

/* ECC Type */
#define FUSE_SEMC_NAND_ECC_TYPE_SHIFT ((uint8_t)4)
#define FUSE_SEMC_NAND_ECC_TYPE_MASK (1u << FUSE_SEMC_NAND_ECC_TYPE_SHIFT)
#define FUSE_SEMC_NAND_ECC_TYPE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_ECC_TYPE_MASK) >> FUSE_SEMC_NAND_ECC_TYPE_SHIFT)

/* RDY Polarity */
#define FUSE_SEMC_NAND_RDY_POLARITY_SHIFT ((uint8_t)5)
#define FUSE_SEMC_NAND_RDY_POLARITY_MASK (1u << FUSE_SEMC_NAND_RDY_POLARITY_SHIFT)
#define FUSE_SEMC_NAND_RDY_POLARITY_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_RDY_POLARITY_MASK) >> FUSE_SEMC_NAND_RDY_POLARITY_SHIFT)

/* Ready Check type */
#define FUSE_SEMC_NAND_READY_CHECK_TYPE_SHIFT ((uint8_t)6)
#define FUSE_SEMC_NAND_READY_CHECK_TYPE_MASK (1u << FUSE_SEMC_NAND_READY_CHECK_TYPE_SHIFT)
#define FUSE_SEMC_NAND_READY_CHECK_TYPE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_READY_CHECK_TYPE_MASK) >> FUSE_SEMC_NAND_READY_CHECK_TYPE_SHIFT)

/* Clock Frequency */
#define FUSE_SEMC_NAND_CLK_FREQ_SHIFT ((uint8_t)7)
#define FUSE_SEMC_NAND_CLK_FREQ_MASK (1u << FUSE_SEMC_NAND_CLK_FREQ_SHIFT)
#define FUSE_SEMC_NAND_CLK_FREQ_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_CLK_FREQ_MASK) >> FUSE_SEMC_NAND_CLK_FREQ_SHIFT)

/* Row Column address mode */
#define FUSE_SEMC_NAND_ROW_COL_ADDR_MODE_SHIFT ((uint8_t)8)
#define FUSE_SEMC_NAND_ROW_COL_ADDR_MODE_MASK (0x07u << FUSE_SEMC_NAND_ROW_COL_ADDR_MODE_SHIFT)
#define FUSE_SEMC_NAND_ROW_COL_ADDR_MODE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_ROW_COL_ADDR_MODE_MASK) >> FUSE_SEMC_NAND_ROW_COL_ADDR_MODE_SHIFT)

/* COL_Address_width */
#define FUSE_SEMC_NAND_COL_ADDRESS_WIDTH_SHIFT ((uint8_t)11)
#define FUSE_SEMC_NAND_COL_ADDRESS_WIDTH_MASK (0x7u << FUSE_SEMC_NAND_COL_ADDRESS_WIDTH_SHIFT)
#define FUSE_SEMC_NAND_COL_ADDRESS_WIDTH_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_COL_ADDRESS_WIDTH_MASK) >> FUSE_SEMC_NAND_COL_ADDRESS_WIDTH_SHIFT)

/* Status Command Type */
#define FUSE_SEMC_NAND_STATUS_CMD_TYPE_SHIFT ((uint8_t)14)
#define FUSE_SEMC_NAND_STATUS_CMD_TYPE_MASK (1u << FUSE_SEMC_NAND_STATUS_CMD_TYPE_SHIFT)
#define FUSE_SEMC_NAND_STATUS_CMD_TYPE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_STATUS_CMD_TYPE_MASK) >> FUSE_SEMC_NAND_STATUS_CMD_TYPE_SHIFT)

/* Pages in block */
#define FUSE_SEMC_NAND_PAGES_IN_BLOCK_SHIFT ((uint8_t)16)
#define FUSE_SEMC_NAND_PAGES_IN_BLOCK_MASK (0x07 << FUSE_SEMC_NAND_PAGES_IN_BLOCK_SHIFT)
#define FUSE_SEMC_NAND_PAGES_IN_BLOCK_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_PAGES_IN_BLOCK_MASK) >> FUSE_SEMC_NAND_PAGES_IN_BLOCK_SHIFT)

/* PCS selection */
#define FUSE_SEMC_NAND_PCS_SELECTION_SHIFT ((uint8_t)19)
#define FUSE_SEMC_NAND_PCS_SELECTION_MASK (0x07 << FUSE_SEMC_NAND_PCS_SELECTION_SHIFT)
#define FUSE_SEMC_NAND_PCS_SELECTION_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_PCS_SELECTION_MASK) >> FUSE_SEMC_NAND_PCS_SELECTION_SHIFT)

/* Device ECC initial status */
#define FUSE_SEMC_NAND_DEVICE_ECC_STATUS_SHIFT ((uint8_t)24)
#define FUSE_SEMC_NAND_DEVICE_ECC_STATUS_MASK (1u << FUSE_SEMC_NAND_DEVICE_ECC_STATUS_SHIFT)
#define FUSE_SEMC_NAND_DEVICE_ECC_STATUS_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_DEVICE_ECC_STATUS_MASK) >> FUSE_SEMC_NAND_DEVICE_ECC_STATUS_SHIFT)

/* ONFI Timing mode */
#define FUSE_SEMC_NAND_TIMING_MODE_SHIFT ((uint8_t)25)
#define FUSE_SEMC_NAND_TIMING_MODE_MASK (0x07u << FUSE_SEMC_NAND_TIMING_MODE_SHIFT)
#define FUSE_SEMC_NAND_TIMING_MODE_VALUE \
    ((HW_OCOTP_REG_RD(0x48) & FUSE_SEMC_NAND_TIMING_MODE_MASK) >> FUSE_SEMC_NAND_TIMING_MODE_SHIFT)

/* ========================== Recovery boot ======================================= */
/* Enable Recovery boot */
#define FUSE_RECOVERY_SPI_EEPROM_BOOT_ENABLE_SHIFT 24
#define FUSE_RECOVERY_SPI_EEPROM_BOOT_ENABLE_MASK (1u << FUSE_RECOVERY_SPI_EEPROM_BOOT_ENABLE_SHIFT)
#define FUSE_RECOVERY_SPI_EEPROM_BOOT_ENABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_RECOVERY_SPI_EEPROM_BOOT_ENABLE_MASK) >> FUSE_RECOVERY_SPI_EEPROM_BOOT_ENABLE_SHIFT)

/* SPI_INSTANCE */
#define FUSE_SPI_INSTANCE_SHIFT ((uint8_t)25)
#define FUSE_SPI_INSTANCE_MASK (0x3 << FUSE_SPI_INSTANCE_SHIFT)
#define FUSE_SPI_INSTANCE_VALUE ((HW_OCOTP_REG_RD(0x47) & FUSE_SPI_INSTANCE_MASK) >> FUSE_SPI_INSTANCE_SHIFT)

/* SPI_Memory_Speed */
#define FUSE_SPI_MEMORY_SPEED_SHIFT ((uint8_t)27)
#define FUSE_SPI_MEMORY_SPEED_MASK (0x3 << FUSE_SPI_MEMORY_SPEED_SHIFT)
#define FUSE_SPI_MEMORY_SPEED_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_SPI_MEMORY_SPEED_MASK) >> FUSE_SPI_MEMORY_SPEED_SHIFT)

/* ========================== LP boot ======================================= */
#define FUSE_LPB_BOOT_SHIFT 4
#define FUSE_LPB_BOOT_MASK (0x03 << FUSE_LPB_BOOT_SHIFT)
#define FUSE_LPB_BOOT_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_LPB_BOOT_MASK) >> FUSE_LPB_BOOT_SHIFT)

#define FUSE_BOOT_FREQ_SHIFT 0x03
#define FUSE_BOOT_FREQ_MASK (1u << FUSE_BOOT_FREQ_SHIFT)
#define FUSE_BOOT_FREQ_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_BOOT_FREQ_MASK) >> FUSE_BOOT_FREQ_SHIFT)

#define FUSE_BOOT_OSC_REF_SHIFT 0x02
#define FUSE_BOOT_OSC_REF_MASK (1u << FUSE_BOOT_OSC_REF_SHIFT)
#define FUSE_BOOT_OSC_REF_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_BOOT_OSC_REF_MASK) >> FUSE_BOOT_OSC_REF_SHIFT)

/* ========================== Boot Failure Indicator Pin ====================== */
/* Enable_Boot_Failure_Indicator pin */
#define BOOT_FAIL_INDICATOR_ENABLE_SHIFT ((uint8_t)5)
#define BOOT_FAIL_INDICATOR_ENABLE_MASK (1u << BOOT_FAIL_INDICATOR_ENABLE_SHIFT)
#define BOOT_FAIL_INDICATOR_ENABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x19) & BOOT_FAIL_INDICATOR_ENABLE_MASK) >> BOOT_FAIL_INDICATOR_ENABLE_SHIFT)

#define BOOT_FAIL_INDICATOR_PIN_SHIFT ((uint8_t)0)
#define BOOT_FAIL_INDICATOR_PIN_MASK (0x1F << BOOT_FAIL_INDICATOR_PIN_SHIFT)
#define BOOT_FAIL_INDICATOR_PIN_VALUE \
    ((HW_OCOTP_REG_RD(0x19) & BOOT_FAIL_INDICATOR_PIN_MASK) >> BOOT_FAIL_INDICATOR_PIN_SHIFT)

/* ========================== Secure/Encrypt boot ======================================= */

/* TESTPORT_DISABLE */
#define FUSE_TESTPORT_DISABLE_SHIFT ((uint8_t)3)
#define FUSE_TESTPORT_DISABLE_MASK (0x1u << FUSE_TESTPORT_DISABLE_SHIFT)
#define FUSE_FUSE_TESTPORT_DISABLE_VALUE ((HW_OCOTP_REG_RD(0x0D) & FUSE_TESTPORT_DISABLE_MASK) >> FUSE_TESTPORT_DISABLE_SHIFT)



/* FIELD_RETURN */
#define FUSE_FIELD_RETURN_SHIFT ((uint8_t)4)
#define FUSE_FIELD_RETURN_MASK (0xFu << FUSE_FIELD_RETURN_SHIFT)
#define FUSE_FIELD_RETURN_VALUE ((HW_OCOTP_REG_RD(0x0D) & FUSE_FIELD_RETURN_MASK) >> FUSE_FIELD_RETURN_SHIFT)

/* SEC Config[0] */
#define FUSE_SEC_CONFIG0_SHIFT ((uint8_t)1)
#define FUSE_SEC_CONFIG0_MASK (1u << FUSE_SEC_CONFIG0_SHIFT)
#define FUSE_SEC_CONFIG0_VALUE ((HW_OCOTP_REG_RD(0x0E) & FUSE_SEC_CONFIG0_MASK) >> FUSE_SEC_CONFIG0_SHIFT)
/* SEC_Config[1] */
#define FUSE_SEC_CONFIG1_SHIFT ((uint8_t)1)
#define FUSE_SEC_CONFIG1_MASK (1u << FUSE_SEC_CONFIG1_SHIFT)
#define FUSE_SEC_CONFIG1_VALUE ((HW_OCOTP_REG_RD(0x16) & FUSE_SEC_CONFIG1_MASK) >> FUSE_SEC_CONFIG1_SHIFT)
#define FUSE_SEC_CONFIG_VALUE (FUSE_SEC_CONFIG0_VALUE | (FUSE_SEC_CONFIG1_VALUE << 1))

#define FUSE_ENCRYPT_XIP_ENGINE_SHIFT (0u)
#define FUSE_ENCRYPT_XIP_ENGINE_MASK (1u << FUSE_ENCRYPT_XIP_ENGINE_SHIFT)
#define FUSE_ENCRYPT_XIP_ENGINE \
    ((HW_OCOTP_REG_RD(0x18) & FUSE_ENCRYPT_XIP_ENGINE_MASK) >> FUSE_ENCRYPT_XIP_ENGINE_SHIFT)

/* AP_BI_VER */
#define FUSE_AP_BI_VER_SHIFT ((uint8_t)0)
#define FUSE_AP_BI_VER_MASK (0xFFFFu << FUSE_AP_BI_VER_SHIFT)
#define FUSE_AP_BI_VER_VALUE ((HW_OCOTP_REG_RD(0x0B) & FUSE_AP_BI_VER_MASK) >> FUSE_AP_BI_VER_SHIFT)

/* OTFAD1_DISABLE */
#define FUSE_OTFAD1_DISABLE_SHIFT (10)
#define FUSE_OTFAD1_DISABLE_MASK (1u << FUSE_OTFAD1_DISABLE_SHIFT)
#define FUSE_OTFAD1_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_OTFAD1_DISABLE_MASK) >> FUSE_OTFAD1_DISABLE_SHIFT)

/* OTFAD2 DISABLE */
#define FUSE_OTFAD2_DISABLE_SHIFT (11)
#define FUSE_OTFAD2_DISABLE_MASK (1u << FUSE_OTFAD2_DISABLE_SHIFT)
#define FUSE_OTFAD2_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_OTFAD2_DISABLE_MASK) >> FUSE_OTFAD2_DISABLE_SHIFT)

/* CAAM Disable */
#define FUSE_CAAM_DISABLE_SHIFT (9)
#define FUSE_CAAM_DISABLE_MASK (1u << FUSE_CAAM_DISABLE_SHIFT)
#define FUSE_CAAM_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_CAAM_DISABLE_MASK) >> FUSE_CAAM_DISABLE_SHIFT)

/* IEE disable */
#define FUSE_IEE_DISABLE_SHIFT (8)
#define FUSE_IEE_DISABLE_MASK (1u << FUSE_IEE_DISABLE_SHIFT)
#define FUSE_IEE_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_IEE_DISABLE_MASK) >> FUSE_IEE_DISABLE_SHIFT)

/* DRYICE disable */
#define FUSE_DRYICE_DISABLE_SHIFT (5)
#define FUSE_DRYICE_DISABLE_MASK (1u << FUSE_DRYICE_DISABLE_SHIFT)
#define FUSE_DRYICE_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_DRYICE_DISABLE_MASK) >> FUSE_DRYICE_DISABLE_SHIFT)

/* RDC disable */
#define FUSE_RDC_DISABLE_SHIFT (12)
#define FUSE_RDC_DISABLE_MASK (1u << FUSE_RDC_DISABLE_SHIFT)
#define FUSE_RDC_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_RDC_DISABLE_MASK) >> FUSE_RDC_DISABLE_SHIFT)

/* XRDC disable */
#define FUSE_XRDC_DISABLE_SHIFT (13)
#define FUSE_XRDC_DISABLE_MASK (1u << FUSE_XRDC_DISABLE_SHIFT)
#define FUSE_XRDC_DISABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_XRDC_DISABLE_MASK) >> FUSE_XRDC_DISABLE_SHIFT)

/* UDF Enable */
#define FUSE_UDF_ENABLE_SHIFT (7)
#define FUSE_UDF_ENABLE_MASK (1u << FUSE_UDF_ENABLE_SHIFT)
#define FUSE_UDF_ENABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_UDF_ENABLE_MASK) >> FUSE_UDF_ENABLE_SHIFT)

/* PUF Enable */
#define FUSE_PUF_ENABLE_SHIFT (6)
#define FUSE_PUF_ENABLE_MASK (1u << FUSE_PUF_ENABLE_SHIFT)
#define FUSE_PUF_ENABLE_VALUE (HW_OCOTP_REG_RD(0x6) & FUSE_PUF_ENABLE_MASK) >> FUSE_PUF_ENABLE_SHIFT)

/* XECC Enable */
#define FUSE_XECC_ENABLE_SHIFT (3)
#define FUSE_XECC_ENABLE_MASK (1u << FUSE_XECC_ENABLE_SHIFT)
#define FUSE_XECC_ENABLE_VALUE (HW_OCOTP_REG_RD(0x4) & FUSE_XECC_ENABLE_MASK) >> FUSE_XECC_ENABLE_SHIFT)

/* MECC Enable */
#define FUSE_MECC_ENABLE_SHIFT (2)
#define FUSE_MECC_ENABLE_MASK (1u << FUSE_MECC_ENABLE_SHIFT)
#define FUSE_MECC_ENABLE_VALUE ((HW_OCOTP_REG_RD(0x4) & FUSE_MECC_ENABLE_MASK) >> FUSE_MECC_ENABLE_SHIFT)

/*OTFAD1 SCRAMBLE EN */
#define FUSE_OTFAD1_SCRAMBLE_EN_SHIFT (0)
#define FUSE_OTFAD1_SCRAMBLE_EN_MASK (1u << FUSE_OTFAD1_SCRAMBLE_EN_SHIFT)
#define FUSE_OTFAD1_SCRAMBLE_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD1_SCRAMBLE_EN_MASK) >> FUSE_OTFAD1_SCRAMBLE_EN_SHIFT)

/*OTFAD1 KEYBLOB EN */
#define FUSE_OTFAD1_KEYBLOB_EN_SHIFT (1)
#define FUSE_OTFAD1_KEYBLOB_EN_MASK (1u << FUSE_OTFAD1_KEYBLOB_EN_SHIFT)
#define FUSE_OTFAD1_KEYBLOB_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD1_KEYBLOB_EN_MASK) >> FUSE_OTFAD1_KEYBLOB_EN_SHIFT)

/*OTFAD1 RESTRICT IPS EN */
#define FUSE_OTFAD1_RESTRICT_IP_EN_SHIFT (2)
#define FUSE_OTFAD1_RESTRICT_IP_EN_MASK (1u << FUSE_OTFAD1_RESTRICT_IP_EN_SHIFT)
#define FUSE_OTFAD1_RESTRICT_IP_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD1_RESTRICT_IP_EN_MASK) >> FUSE_OTFAD1_RESTRICT_IP_EN_SHIFT)

/*OTFAD1 KEYBLOB_CRC EN */
#define FUSE_OTFAD1_KEYBLOB_CRC_EN_SHIFT (3)
#define FUSE_OTFAD1_KEYBLOB_CRC_EN_MASK (1u << FUSE_OTFAD1_KEYBLOB_CRC_EN_SHIFT)
#define FUSE_OTFAD1_KEYBLOB_CRC_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD1_KEYBLOB_CRC_EN_MASK) >> FUSE_OTFAD1_KEYBLOB_CRC_EN_SHIFT)

/*OTFAD2 SCRAMBLE EN */
#define FUSE_OTFAD2_SCRAMBLE_EN_SHIFT (4)
#define FUSE_OTFAD2_SCRAMBLE_EN_MASK (1u << FUSE_OTFAD2_SCRAMBLE_EN_SHIFT)
#define FUSE_OTFAD2_SCRAMBLE_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD2_SCRAMBLE_EN_MASK) >> FUSE_OTFAD2_SCRAMBLE_EN_SHIFT)

/*OTFAD2 KEYBLOB EN */
#define FUSE_OTFAD2_KEYBLOB_EN_SHIFT (5)
#define FUSE_OTFAD2_KEYBLOB_EN_MASK (1u << FUSE_OTFAD2_KEYBLOB_EN_SHIFT)
#define FUSE_OTFAD2_KEYBLOB_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD2_KEYBLOB_EN_MASK) >> FUSE_OTFAD2_KEYBLOB_EN_SHIFT)

/*OTFAD2 RESTRICT IPS EN */
#define FUSE_OTFAD2_RESTRICT_IP_EN_SHIFT (6)
#define FUSE_OTFAD2_RESTRICT_IP_EN_MASK (1u << FUSE_OTFAD2_RESTRICT_IP_EN_SHIFT)
#define FUSE_OTFAD2_RESTRICT_IP_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD2_RESTRICT_IP_EN_MASK) >> FUSE_OTFAD2_RESTRICT_IP_EN_SHIFT)

/*OTFAD2 KEYBLOB_CRC EN */
#define FUSE_OTFAD2_KEYBLOB_CRC_EN_SHIFT (7)
#define FUSE_OTFAD2_KEYBLOB_CRC_EN_MASK (1u << FUSE_OTFAD2_KEYBLOB_CRC_EN_SHIFT)
#define FUSE_OTFAD2_KEYBLOB_CRC_EN_VALUE \
    ((HW_OCOTP_REG_RD(0x47) & FUSE_OTFAD2_KEYBLOB_CRC_EN_MASK) >> FUSE_OTFAD2_KEYBLOB_CRC_EN_SHIFT)

#define OTFAD_KEYBLOB_EN_VALUE (FUSE_OTFAD1_KEYBLOB_EN_VALUE | FUSE_OTFAD2_KEYBLOB_EN_VALUE)

/* ========================== MMC/SD boot(Common Part)======================================= */
/* Card Type selection, eMMC or SD. */
#define FUSE_SDMMC_TYPE_SEL_SHIFT ((uint8_t)6)
#define FUSE_SDMMC_TYPE_SEL_MASK ((uint32_t)(0x3 << FUSE_SDMMC_TYPE_SEL_SHIFT))
#define FUSE_SDMMC_TYPE_SEL_VALUE ((SRC->SBMR1 & FUSE_SDMMC_TYPE_SEL_MASK) >> FUSE_SDMMC_TYPE_SEL_SHIFT)

/* SD1 VOLTAGE SELECTION */
#define FUSE_SD1_VOLTAGE_SELECTION_SHIFT ((uint8_t)3)
#define FUSE_SD1_VOLTAGE_SELECTION_MASK ((uint32_t)(0x1 << FUSE_SD1_VOLTAGE_SELECTION_SHIFT))
#define FUSE_SD1_VOLTAGE_SELECTION_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SD1_VOLTAGE_SELECTION_MASK) >> FUSE_SD1_VOLTAGE_SELECTION_SHIFT)

/* SD2 VOLTAGE SELECTION */
#define FUSE_SD2_VOLTAGE_SELECTION_SHIFT ((uint8_t)8)
#define FUSE_SD2_VOLTAGE_SELECTION_MASK ((uint32_t)(0x1 << FUSE_SD2_VOLTAGE_SELECTION_SHIFT))
#define FUSE_SD2_VOLTAGE_SELECTION_VALUE \
    ((SRC->SBMR1 & FUSE_SD2_VOLTAGE_SELECTION_MASK) >> FUSE_SD2_VOLTAGE_SELECTION_SHIFT)

/* SD Loopback_Clock_Source */
#define FUSE_SDMMC_LOOPBACK_CLK_SOURCE_SHIFT ((uint8_t)2)
#define FUSE_SDMMC_LOOPBACK_CLK_SOURCE_MASK ((uint32_t)(0x1 << FUSE_SDMMC_LOOPBACK_CLK_SOURCE_SHIFT))
#define FUSE_SDMMC_LOOPBACK_CLK_SOURCE_VALUE \
    ((SRC->SBMR1 & FUSE_SDMMC_LOOPBACK_CLK_SOURCE_MASK) >> FUSE_SDMMC_LOOPBACK_CLK_SOURCE_SHIFT)

/* SD/MMC/eMMC Fast_Boot */
#define FUSE_SDMMC_FAST_BOOT_SHIFT ((uint8_t)0)
#define FUSE_SDMMC_FAST_BOOT_MASK ((uint32_t)(0x1 << FUSE_SDMMC_FAST_BOOT_SHIFT))
#define FUSE_SDMMC_FAST_BOOT_VALUE ((SRC->SBMR1 & FUSE_SDMMC_FAST_BOOT_MASK) >> FUSE_SDMMC_FAST_BOOT_SHIFT)

/* Power cycle enable */
#define FUSE_SDMMC_POWER_CYCLE_ENABLE_SHIFT ((uint8_t)3)
#define FUSE_SDMMC_POWER_CYCLE_ENABLE_MASK ((uint32_t)(0x1 << FUSE_SDMMC_POWER_CYCLE_ENABLE_SHIFT))
#define FUSE_SDMMC_POWER_CYCLE_ENABLE_VALUE \
    ((SRC->SBMR1 & FUSE_SDMMC_POWER_CYCLE_ENABLE_MASK) >> FUSE_SDMMC_POWER_CYCLE_ENABLE_SHIFT)

/* Power cycle selection */
#define FUSE_SDMMC_PWR_CYCLE_SEL_SHIFT ((uint8_t)6)
#define FUSE_SDMMC_PWR_CYCLE_SEL_MASK ((uint32_t)(0x3 << FUSE_SDMMC_PWR_CYCLE_SEL_SHIFT))
#define FUSE_SDMMC_PWR_CYCLE_SEL_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SDMMC_PWR_CYCLE_SEL_MASK) >> FUSE_SDMMC_PWR_CYCLE_SEL_SHIFT)

/* Power stable cycle selection */
#define FUSE_SDMMC_PWR_STABLE_CYCLE_SEL_SHIFT ((uint8_t)5)
#define FUSE_SDMMC_PWR_STABLE_CYCLE_SEL_MASK ((uint32_t)(0x1 << FUSE_SDMMC_PWR_STABLE_CYCLE_SEL_SHIFT))
#define FUSE_SDMMC_PWR_STABLE_CYCLE_SEL_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SDMMC_PWR_STABLE_CYCLE_SEL_MASK) >> FUSE_SDMMC_PWR_STABLE_CYCLE_SEL_SHIFT)

/* DLL override enable for SD/eMMC */
#define FUSE_SDMMC_DLL_OVERRIDE_ENABLE_SHIFT ((uint8_t)10)
#define FUSE_SDMMC_DLL_OVERRIDE_ENABLE_MASK ((uint32_t)(0x1 << FUSE_SDMMC_DLL_OVERRIDE_ENABLE_SHIFT))
#define FUSE_SDMMC_DLL_OVERRIDE_ENABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SDMMC_DLL_OVERRIDE_ENABLE_MASK) >> FUSE_SDMMC_DLL_OVERRIDE_ENABLE_SHIFT)

/* DLL delay */
#define FUSE_SDMMC_DLL_DLY_SHIFT ((uint8_t)8)
#define FUSE_SDMMC_DLL_DLY_MASK ((uint32_t)(0x7Fu << FUSE_SDMMC_DLL_DLY_SHIFT))
#define FUSE_SDMMC_DLL_DLY_VALUE ((HW_OCOTP_REG_RD(0x19) & FUSE_SDMMC_DLL_DLY_MASK) >> FUSE_SDMMC_DLL_DLY_SHIFT)

/* SD/MMC Index */
#define FUSE_SDMMC_PORT_SEL_SHIFT ((uint8_t)1)
#define FUSE_SDMMC_PORT_SEL_MASK ((uint32_t)(0x1 << FUSE_SDMMC_PORT_SEL_SHIFT))
#define FUSE_SDMMC_PORT_SEL_VALUE ((SRC->SBMR1 & FUSE_SDMMC_PORT_SEL_MASK) >> FUSE_SDMMC_PORT_SEL_SHIFT)

/* SD/MMC instance 1 reset polarity */
#define FUSE_SD1_RST_ACTIVE_POLARITY_SHIFT ((uint8_t)2)
#define FUSE_SD1_RST_ACTIVE_POLARITY_MASK ((uint32_t)(0x1 << FUSE_SD1_RST_ACTIVE_POLARITY_SHIFT))
#define FUSE_SD1_RST_ACTIVE_POLARITY_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SD1_RST_ACTIVE_POLARITY_MASK) >> FUSE_SD1_RST_ACTIVE_POLARITY_SHIFT)

/* SD/MMC instance 2 reset polarity */
#define FUSE_SD2_RST_ACTIVE_POLARITY_SHIFT ((uint8_t)1)
#define FUSE_SD2_RST_ACTIVE_POLARITY_MASK ((uint32_t)(0x1 << FUSE_SD2_RST_ACTIVE_POLARITY_SHIFT))
#define FUSE_SD2_RST_ACTIVE_POLARITY_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SD2_RST_ACTIVE_POLARITY_MASK) >> FUSE_SD2_RST_ACTIVE_POLARITY_SHIFT)

/* USDHC IOMUX SION Enable */
#define FUSE_USDHC_IOMUX_SION_ENABLE_SHIFT ((uint8_t)4)
#define FUSE_USDHC_IOMUX_SION_ENABLE_MASK ((uint32_t)(0x1 << FUSE_USDHC_IOMUX_SION_ENABLE_SHIFT))
#define FUSE_USDHC_IOMUX_SION_ENABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_USDHC_IOMUX_SION_ENABLE_MASK) >> FUSE_USDHC_IOMUX_SION_ENABLE_SHIFT)

/* Disable SDMMC Manufacture Mode */
#define FUSE_SDMMC_MFG_DISABLE_SHIFT ((uint8_t)15)
#define FUSE_SDMMC_MFG_DISABLE_MASK ((uint32_t)(0x1 << FUSE_SDMMC_MFG_DISABLE_SHIFT))
#define FUSE_SDMMC_MFG_DISABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SDMMC_MFG_DISABLE_MASK) >> FUSE_SDMMC_MFG_DISABLE_SHIFT)

/* ========================== MMC/SD boot(MMC Part)======================================= */
/* MMC Speed */
#define FUSE_MMC_SPEED_SHIFT ((uint8_t)5)
#define FUSE_MMC_SPEED_MASK ((uint32_t)(0x1 << FUSE_MMC_SPEED_SHIFT))
#define FUSE_MMC_SPEED_VALUE ((SRC->SBMR1 & FUSE_MMC_SPEED_MASK) >> FUSE_MMC_SPEED_SHIFT)

/* MMC/eMMC Fast_Boot_ACK_Disable */
#define FUSE_MMC_FAST_BOOT_ACK_SHIFT ((uint8_t)4)
#define FUSE_MMC_FAST_BOOT_ACK_MASK ((uint32_t)(0x1 << FUSE_MMC_FAST_BOOT_ACK_SHIFT))
#define FUSE_MMC_FAST_BOOT_ACK_VALUE ((SRC->SBMR1 & FUSE_MMC_FAST_BOOT_ACK_MASK) >> FUSE_MMC_FAST_BOOT_ACK_SHIFT)

/* MMC Bus_Width */
#define FUSE_MMC_BUS_WIDTH_SHIFT ((uint8_t)9)
#define FUSE_MMC_BUS_WIDTH_MASK ((uint32_t)(0x3 << FUSE_MMC_BUS_WIDTH_SHIFT))
#define FUSE_MMC_BUS_WIDTH_VALUE ((SRC->SBMR1 & FUSE_MMC_BUS_WIDTH_MASK) >> FUSE_MMC_BUS_WIDTH_SHIFT)

/* eMMC fast boot pre-idle reset mode fuse*/
#define FUSE_EMMC_RESET_PREIDLE_STATE_SHIFT ((uint8_t)0)
#define FUSE_EMMC_RESET_PREIDLE_STATE_MASK ((uint32_t)(0x1 << FUSE_EMMC_RESET_PREIDLE_STATE_SHIFT))
#define FUSE_EMMC_RESET_PREIDLE_STATE() \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_EMMC_RESET_PREIDLE_STATE_MASK) >> FUSE_EMMC_RESET_PREIDLE_STATE_SHIFT)

/* ========================== MMC/SD boot(SD Part)======================================= */
/* SD Speed */
#define FUSE_SD_SPEED_SHIFT ((uint8_t)4)
#define FUSE_SD_SPEED_MASK ((uint32_t)(0x3 << FUSE_SD_SPEED_SHIFT))
#define FUSE_SD_SPEED_VALUE ((SRC->SBMR1 & FUSE_SD_SPEED_MASK) >> FUSE_SD_SPEED_SHIFT)

/* SD_Calibration Step  */
#define FUSE_SD_CAL_STEP_SHIFT ((uint8_t)8)
#define FUSE_SD_CAL_STEP_MASK ((uint32_t)(0x3 << FUSE_SD_CAL_STEP_SHIFT))
#define FUSE_SD_CAL_STEP_VALUE ((HW_OCOTP_REG_RD(0x17) & FUSE_SD_CAL_STEP_MASK) >> FUSE_SD_CAL_STEP_SHIFT)

/* SD BUS_Width */
#define FUSE_SD_BUS_WIDTH_SHIFT ((uint8_t)9)
#define FUSE_SD_BUS_WIDTH_MASK ((uint32_t)(0x1 << FUSE_SD_BUS_WIDTH_SHIFT))
#define FUSE_SD_BUS_WIDTH_VALUE ((SRC->SBMR1 & FUSE_SD_BUS_WIDTH_MASK) >> FUSE_SD_BUS_WIDTH_SHIFT)

/* ========================== SDIO slave SDP boot ======================================= */
/* Disable SDIO slave SDP */
#define FUSE_SDIO_SLAVE_SDP_DISABLE_SHIFT ((uint8_t)14)
#define FUSE_SDIO_SLAVE_SDP_DISABLE_MASK ((uint32_t)(0x1 << FUSE_SDIO_SLAVE_SDP_DISABLE_SHIFT))
#define FUSE_SDIO_SLAVE_SDP_DISABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SDIO_SLAVE_SDP_DISABLE_MASK) >> FUSE_SDIO_SLAVE_SDP_DISABLE_SHIFT)

/* Enable SDIO slave MANFID Override */
#define FUSE_SDIO_SLAVE_MANFID_OVERRIDE_ENABLE_SHIFT ((uint8_t)13)
#define FUSE_SDIO_SLAVE_MANFID_OVERRIDE_ENABLE_MASK ((uint32_t)(0x1 << FUSE_SDIO_SLAVE_MANFID_OVERRIDE_ENABLE_SHIFT))
#define FUSE_SDIO_SLAVE_MANFID_OVERRIDE_ENABLE_VALUE                          \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SDIO_SLAVE_MANFID_OVERRIDE_ENABLE_MASK) >> \
     FUSE_SDIO_SLAVE_MANFID_OVERRIDE_ENABLE_SHIFT)

/* SDIO slave MANFID LOW BYTE */
#define FUSE_SDIO_SLAVE_MANFID_LOW_SHIFT ((uint8_t)0)
#define FUSE_SDIO_SLAVE_MANFID_LOW_MASK ((uint32_t)(0xFF << FUSE_SDIO_SLAVE_MANFID_LOW_SHIFT))
#define FUSE_SDIO_SLAVE_MANFID_LOW_VALUE \
    ((HW_OCOTP_REG_RD(0x49) & FUSE_SDIO_SLAVE_MANFID_LOW_MASK) >> FUSE_SDIO_SLAVE_MANFID_LOW_SHIFT)

/* SDIO slave MANFID HIGH BYTE */
#define FUSE_SDIO_SLAVE_MANFID_HIGH_SHIFT ((uint8_t)8)
#define FUSE_SDIO_SLAVE_MANFID_HIGH_MASK ((uint32_t)(0xFF << FUSE_SDIO_SLAVE_MANFID_HIGH_SHIFT))
#define FUSE_SDIO_SLAVE_MANFID_HIGH_VALUE \
    ((HW_OCOTP_REG_RD(0x49) & FUSE_SDIO_SLAVE_MANFID_HIGH_MASK) >> FUSE_SDIO_SLAVE_MANFID_HIGH_SHIFT)

/* SDIO slave Part number LOW BYTE */
#define FUSE_SDIO_SLAVE_PARTNUM_LOW_SHIFT ((uint8_t)16)
#define FUSE_SDIO_SLAVE_PARTNUM_LOW_MASK ((uint32_t)(0xFF << FUSE_SDIO_SLAVE_PARTNUM_LOW_SHIFT))
#define FUSE_SDIO_SLAVE_PARTNUM_LOW_VALUE \
    ((HW_OCOTP_REG_RD(0x49) & FUSE_SDIO_SLAVE_PARTNUM_LOW_MASK) >> FUSE_SDIO_SLAVE_PARTNUM_LOW_SHIFT)

/* SDIO slave Part number HIGH BYTE */
#define FUSE_SDIO_SLAVE_PARTNUM_HIGH_SHIFT ((uint8_t)24)
#define FUSE_SDIO_SLAVE_PARTNUM_HIGH_MASK ((uint32_t)(0xFF << FUSE_SDIO_SLAVE_PARTNUM_HIGH_SHIFT))
#define FUSE_SDIO_SLAVE_PARTNUM_HIGH_VALUE \
    ((HW_OCOTP_REG_RD(0x49) & FUSE_SDIO_SLAVE_PARTNUM_HIGH_MASK) >> FUSE_SDIO_SLAVE_PARTNUM_HIGH_SHIFT)

/* ========================== Misc. Configuration ======================================= */
/* Force_Boot_from_fuse */
#define FUSE_FORCE_COLD_BOOT_SHIFT ((uint8_t)5)
#define FUSE_FORCE_COLD_BOOT_MASK (1u << FUSE_FORCE_COLD_BOOT_SHIFT)
#define FUSE_FORCE_COLD_BOOT_VALUE ((HW_OCOTP_REG_RD(0x16) & FUSE_FORCE_COLD_BOOT_MASK) >> FUSE_FORCE_COLD_BOOT_SHIFT)

/* Force Boot from Fuse fuse */
#define FUSE_FORCE_INTERNAL_BOOT_SHIFT ((uint8_t)14)
#define FUSE_FORCE_INTERNAL_BOOT_MASK (1u << FUSE_FORCE_INTERNAL_BOOT_SHIFT)
#define FUSE_FORCE_INTERNAL_BOOT_VALUE \
    ((HW_OCOTP_REG_RD(0x1A) & FUSE_FORCE_INTERNAL_BOOT_MASK) >> FUSE_FORCE_INTERNAL_BOOT_SHIFT)

/* SDP_ENABLE fuse */
#define FUSE_SDP_DISABLE_SHIFT ((uint8_t)0)
#define FUSE_SDP_DISABLE_MASK (1U << FUSE_SDP_DISABLE_SHIFT)
#define FUSE_SDP_DISABLE_VALUE ((HW_OCOTP_REG_RD(0x1A) & FUSE_SDP_DISABLE_MASK) >> FUSE_SDP_DISABLE_SHIFT)

/* WDOG enable fuse */
#define FUSE_WDOG_ENABLE_SHIFT ((uint8_t)15)
#define FUSE_WDOG_ENABLE_MASK (1u << FUSE_WDOG_ENABLE_SHIFT)
#define FUSE_WDOG_ENABLE_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_WDOG_ENABLE_MASK) >> FUSE_WDOG_ENABLE_SHIFT)

/* L1 I-Cache DISABLE */
#define FUSE_ICACHE_DISABLE_SHIFT ((uint8_t)7)
#define FUSE_ICACHE_DISABLE_MASK (1u << FUSE_ICACHE_DISABLE_SHIFT)
#define FUSE_ICACHE_DISABLE_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_ICACHE_DISABLE_MASK) >> FUSE_ICACHE_DISABLE_SHIFT)

/* L1 D-Cache DISABLE */
#define FUSE_DCACHE_DISABLE_SHIFT ((uint8_t)6)
#define FUSE_DCACHE_DISABLE_MASK (1u << FUSE_DCACHE_DISABLE_SHIFT)
#define FUSE_DCACHE_DISABLE_VALUE ((HW_OCOTP_REG_RD(0x1a) & FUSE_DCACHE_DISABLE_MASK) >> FUSE_DCACHE_DISABLE_SHIFT)

/* UART Serial Download DISABLE */
#define FUSE_UART_SERIAL_DOWNLOAD_DISABLE_SHIFT ((uint8_t)1)
#define FUSE_UART_SERIAL_DOWNLOAD_DISABLE_MASK (1u << FUSE_UART_SERIAL_DOWNLOAD_DISABLE_SHIFT)
#define FUSE_UART_SERIAL_DOWNLOAD_DISABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x1a) & FUSE_UART_SERIAL_DOWNLOAD_DISABLE_MASK) >> FUSE_UART_SERIAL_DOWNLOAD_DISABLE_SHIFT)

/* Disable SAI SLAVE SDP */
#define FUSE_SAI_SLAVE_SDP_DISABLE_SHIFT ((uint8_t)12)
#define FUSE_SAI_SLAVE_SDP_DISABLE_MASK ((uint32_t)(0x1 << FUSE_SAI_SLAVE_SDP_DISABLE_SHIFT))
#define FUSE_SAI_SLAVE_SDP_DISABLE_VALUE \
    ((HW_OCOTP_REG_RD(0x17) & FUSE_SAI_SLAVE_SDP_DISABLE_MASK) >> FUSE_SAI_SLAVE_SDP_DISABLE_SHIFT)

/* FLEXRAM PART */
#define FUSE_FLEXRAM_CFG_SHIFT ((uint8_t)16)
#define FUSE_FLEXRAM_CFG_MASK (0x3fu << FUSE_FLEXRAM_CFG_SHIFT)
#define FUSE_FLEXRAM_CFG_VALUE ((HW_OCOTP_REG_RD(0x47) & FUSE_FLEXRAM_CFG_MASK) >> FUSE_FLEXRAM_CFG_SHIFT)

/* ========================== USB Configuration ======================================= */
#define FUSE_USB_VID_SHIFT (0u)
#define FUSE_USB_VID_MASK (0xFFFFu << FUSE_USB_VID_SHIFT)
#define FUSE_USB_VID_VAL ((HW_OCOTP_REG_RD(0x2E) & FUSE_USB_VID_MASK) >> FUSE_USB_VID_SHIFT)

#define FUSE_USB_PID_SHIFT (16u)
#define FUSE_USB_PID_MASK (0xFFFFu << FUSE_USB_PID_SHIFT)
#define FUSE_USB_PID_VAL ((HW_OCOTP_REG_RD(0x2E) & FUSE_USB_PID_MASK) >> FUSE_USB_PID_SHIFT)

/* Disable USB SDP */
#define FUSE_USB_SDP_DISABLE_SHIFT ((uint8_t)11)
#define FUSE_USB_SDP_DISABLE_MASK ((uint32_t)(0x1 << FUSE_USB_SDP_DISABLE_SHIFT))
#define FUSE_USB_SDP_DISABLE_VALUE ((HW_OCOTP_REG_RD(0x17) & FUSE_USB_SDP_DISABLE_MASK) >> FUSE_USB_SDP_DISABLE_SHIFT)

/* ========================== MISC. Configuration ======================================= */
#define FUSE_OSC_4_16M_TRIM_EN_SHIFT (21)
#define FUSE_OSC_4_16M_TRIM_EN_MASK (1u << FUSE_OSC_4_16M_TRIM_EN_SHIFT)
#define FUSE_OSC_4_16M_TRIM_EN_VAL \
    ((HW_OCOTP_REG_RD(0x21) & FUSE_OSC_4_16M_TRIM_EN_MASK) >> FUSE_OSC_4_16M_TRIM_EN_SHIFT)

/* ========================== Device Sepefic Configuration ======================================= */
#define FUSE_DEVICE_UUID_WORD0_SHIFT (0u)
#define FUSE_DEVICE_UUID_WORD0_MASK (0xFFFFFFFFu << FUSE_DEVICE_UUID_WORD0_SHIFT)
#define FUSE_DEVICE_UUID_WORD0_VAL \
    ((HW_OCOTP_REG_RD(0x10) & FUSE_DEVICE_UUID_WORD0_MASK) >> FUSE_DEVICE_UUID_WORD0_SHIFT)

#define FUSE_DEVICE_UUID_WORD1_SHIFT (0u)
#define FUSE_DEVICE_UUID_WORD1_MASK (0xFFFFFFFFu << FUSE_DEVICE_UUID_WORD1_SHIFT)
#define FUSE_DEVICE_UUID_WORD1_VAL \
    ((HW_OCOTP_REG_RD(0x11) & FUSE_DEVICE_UUID_WORD1_MASK) >> FUSE_DEVICE_UUID_WORD1_SHIFT)

#endif /* __FUSEMAP_H__*/
