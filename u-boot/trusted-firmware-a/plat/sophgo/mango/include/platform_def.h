/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef PLATFORM_DEF_H
#define PLATFORM_DEF_H

#include <arch.h>
#include <common/tbbr/tbbr_img_def.h>
#include <lib/utils_def.h>
#include <plat/common/common_def.h>

//#define CONFIG_ARCH_MANGO_PLD
//#define CONFIG_ARCH_MANGO_FPGA
//#define BL1_IN_SPI_FLASH

#ifdef CONFIG_ARCH_MANGO_FPGA
/*
 * for simulation on FPGA, FPGA only has 64KB SRAM.
 * so just run BL1 in it. no BL2 allowed. also to
 * minimux the modificaton of normal code, we only
 * hacked BL1 RW section, thus we can't enable MMU
 * due to section overlap.
 */
//#define BL1_TEST_MODE
#endif

#define MANGO_HAS_PCIE
#define MANGO_HAS_CMN

/* Special value used to verify platform parameters from BL2 to BL3-1 */
#define MANGO_BL31_PLAT_PARAM_VAL	0x0f1e2d3c4b5a6978ULL

#define PLATFORM_STACK_SIZE	0x1000

#define PLAT_MANGO_CCI_CLUSTER0_SL_IFACE_IX 1
#define PLAT_MANGO_CCI_CLUSTER1_SL_IFACE_IX 2

#define PLATFORM_MAX_CPUS_PER_CLUSTER	U(4)
#define PLATFORM_CLUSTER_COUNT		U(2)
#define PLATFORM_CLUSTER0_CORE_COUNT	PLATFORM_MAX_CPUS_PER_CLUSTER
#define PLATFORM_CLUSTER1_CORE_COUNT	PLATFORM_MAX_CPUS_PER_CLUSTER
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER0_CORE_COUNT + \
					 PLATFORM_CLUSTER1_CORE_COUNT)

#define MANGO_PRIMARY_CPU		U(0)

#define PLAT_NUM_PWR_DOMAINS		(PLATFORM_CLUSTER_COUNT + \
					 PLATFORM_CORE_COUNT)
#define PLAT_MAX_PWR_LVL		MPIDR_AFFLVL1

#define PLAT_MAX_RET_STATE		U(1)
#define PLAT_MAX_OFF_STATE		U(2)

/* Local power state for power domains in Run state. */
#define PLAT_LOCAL_STATE_RUN		U(0)
/* Local power state for retention. Valid only for CPU power domains */
#define PLAT_LOCAL_STATE_RET		U(1)
/*
 * Local power state for OFF/power-down. Valid for CPU and cluster power
 * domains.
 */
#define PLAT_LOCAL_STATE_OFF		2

/*
 * Macros used to parse state information from State-ID if it is using the
 * recommended encoding for State-ID.
 */
#define PLAT_LOCAL_PSTATE_WIDTH		4
#define PLAT_LOCAL_PSTATE_MASK		(BIT(PLAT_LOCAL_PSTATE_WIDTH) - 1)

/*
 * Partition memory into secure ROM, non-secure DRAM, secure "SRAM",
 * and secure DRAM.
 */
#if defined(CONFIG_ARCH_MANGO_FPGA) && !defined(FPGA_BL1_TEST)
#define DDR_OFFSET_ROM			(NS_DRAM_SIZE + 0)
#define DDR_OFFSET_SRAM			(NS_DRAM_SIZE + SEC_ROM_SIZE)
#define DDR_OFFSET_FLASH		(NS_DRAM_SIZE + SEC_ROM_SIZE + \
					 SEC_SRAM_SIZE)
#ifdef BL1_IN_SPI_FLASH
#define SEC_ROM_BASE			FLASH1_BASE
#else
#define SEC_ROM_BASE			(NS_DRAM_BASE + DDR_OFFSET_ROM)
#endif
#define SEC_ROM_SIZE			(64 * 1024)

#define SEC_SRAM_BASE			(NS_DRAM_BASE + DDR_OFFSET_SRAM)
#define SEC_SRAM_SIZE			0x00100000 //1MB
#else
#ifdef BL1_IN_SPI_FLASH
#define SEC_ROM_BASE			FLASH1_BASE
#else
#define SEC_ROM_BASE			BOOT_ROM1_BASE
#endif
#define SEC_ROM_SIZE			(64 * 1024)

#define SEC_SRAM_BASE			SRAM0_BASE
#define SEC_SRAM_SIZE			0x00200000 //2MB
#endif

#define NS_DRAM_BASE			DDR0_BASE
#define NS_DRAM_SIZE			0x80000000 //2GB

#define PLAT_MANGO_FIP_MAX_SIZE		SEC_SRAM_SIZE

/*
 * ARM-TF lives in SRAM, partition it here
 */
#define SHARED_RAM_BASE			SEC_SRAM_BASE
#define SHARED_RAM_SIZE			0x00001000 // 4KB

#define PLAT_MANGO_TRUSTED_MAILBOX_BASE		SHARED_RAM_BASE
#define PLAT_MANGO_TRUSTED_MAILBOX_SIZE		(8 + PLAT_MANGO_HOLD_SIZE)
#define PLAT_MANGO_HOLD_BASE			(PLAT_MANGO_TRUSTED_MAILBOX_BASE + 8)
#define PLAT_MANGO_HOLD_SIZE			(PLATFORM_CORE_COUNT * \
						 PLAT_MANGO_HOLD_ENTRY_SIZE)
#define PLAT_MANGO_HOLD_ENTRY_SHIFT		3
#define PLAT_MANGO_HOLD_ENTRY_SIZE		BIT(PLAT_BM_HOLD_ENTRY_SHIFT)
#define PLAT_MANGO_HOLD_STATE_WAIT		0
#define PLAT_MANGO_HOLD_STATE_GO		1

/*
 * some "register" for configurations, at end of share memory region
 */
#define BOARD_TYPE_REG		(TOP_BASE + 0x23C) // GP_REG31
#define FIP_SOURCE_REG		(TOP_BASE + 0x238) // GP_REG30
#define BOOT_ARGS_REG		(TOP_BASE + 0x234) // GP_REG29
#define BOOT_STAGE_REG		(TOP_BASE + 0x230) // GP_REG28

#define BL_RAM_BASE		(SHARED_RAM_BASE + SHARED_RAM_SIZE)
#define BL_RAM_SIZE		(SEC_SRAM_SIZE - SHARED_RAM_SIZE)

/*
 * block IO buffer, start address and size must be block size aligned
 */
#define IO_BUFFER_BASE		BL_RAM_BASE
#define IO_BUFFER_SIZE		0x00001000 //4KB

/*
 * BL1 specific defines.
 *
 * BL1 RW data is relocated from ROM to RAM at runtime so we need 2 sets of
 * addresses.
 * Put BL1 RW at the top of the Secure SRAM. BL1_RW_BASE is calculated using
 * the current BL1 RW debug size plus a little space for growth.
 */
#define BL1_RO_BASE		SEC_ROM_BASE
#define BL1_RO_LIMIT		(SEC_ROM_BASE + SEC_ROM_SIZE)
#ifdef FPGA_BL1_TEST
#define BL1_RW_LIMIT		(SRAM0_BASE + 0x10000)
#define BL1_RW_BASE		 SRAM0_BASE
#else
#define BL1_RW_BASE		(IO_BUFFER_BASE + IO_BUFFER_SIZE)
#define BL1_RW_LIMIT		(BL1_RW_BASE + 0x0001E000) // 120KB
#endif

/*
 * BL2 specific defines.
 *
 * Put BL2 just below BL3-1. BL2_BASE is calculated using the current BL2 debug
 * size plus a little space for growth.
 */
#define BL2_BASE		BL1_RW_LIMIT
#define BL2_LIMIT		(SEC_SRAM_BASE + SEC_SRAM_SIZE)

/*
 * BL3-1 specific defines.
 *
 * Put BL3-1 at the top of the Trusted SRAM. BL31_BASE is calculated using the
 * current BL3-1 debug size plus a little space for growth.
 */
#define BL31_BASE			(BL31_LIMIT - 0x40000)
#define BL31_LIMIT			(BL_RAM_BASE + BL_RAM_SIZE)
#ifdef FPGA_BL1_TEST
#define BL31_PROGBITS_LIMIT		0x70101EE000
#else
#define BL31_PROGBITS_LIMIT		(BL31_BASE + 0x20000)
#endif

#define NS_IMAGE_OFFSET			(NS_DRAM_BASE + 0x8000000) // 128M
#define NS_IMAGE_MAX_SIZE		(NS_DRAM_SIZE - 0x8000000)

#define ZSBL_IMAGE_NAME			"zsbl.bin"
#define ZSBL_BASE			0x40000000

/*
 * Platform specific page table and MMU setup constants
 */
#define PLAT_CHIP_ADDR_SPACE		(1ULL << 39)
#define PLAT_CHIP_ADDR_BASE(n)		((n) * PLAT_CHIP_ADDR_SPACE)

#define PLAT_PHY_ADDR_SPACE_SIZE	BIT(39)
#define PLAT_VIRT_ADDR_SPACE_SIZE	BIT(39)

#define MAX_MMAP_REGIONS		11
#define MAX_XLAT_TABLES			10

#define MAX_IO_DEVICES			3
#define MAX_IO_HANDLES			2

/*
 * Some data must be aligned on the biggest cache line size in the platform.
 * This is known only to the platform as it might have a combination of
 * integrated and external caches.
 */
#define CACHE_WRITEBACK_SHIFT		6
#define CACHE_WRITEBACK_GRANULE		BIT(CACHE_WRITEBACK_SHIFT)

/*
 * SPI flash layout
 */
#define SPIF_OFFSET_A_BL1		(0)
#define SPIF_OFFSET_A_PAT		(0x00020000) // 128KB
#define SPIF_OFFSET_A_FIP		(0x00030000) // 192KB
#define SPIF_OFFSET_B_BL1		(0x00200000) // 2MB
#define SPIF_OFFSET_B_PAT		(0x00220000) // 2MB + 128KB
#define SPIF_OFFSET_B_FIP		(0x00230000) // 2MB + 192KB
#define SPIF_OFFSET_BLEND		(0x00400000) // 4MB
#define SPIF_OFFSET_ALEND		(0x01000000) // 16MB

/*
 * Clock setting
 */
#ifdef CONFIG_ARCH_MANGO_PLD
#define SYS_COUNTER_FREQ_IN_TICKS		50000000
#elif defined(CONFIG_ARCH_MANGO_FPGA)
#define SYS_COUNTER_FREQ_IN_TICKS		20000000
#else
#define SYS_COUNTER_FREQ_IN_TICKS		50000000
#endif
#define SYS_COUNTER_FREQ_IN_TICKS_BYPASS	25000000

#ifdef CONFIG_ARCH_MANGO_PLD
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_NORMAL	PLAT_MANGO_CONSOLE_BAUDRATE * 16
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_FAST	PLAT_MANGO_CONSOLE_BAUDRATE * 16
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_SAFE	PLAT_MANGO_CONSOLE_BAUDRATE * 16
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_BYPASS	PLAT_MANGO_CONSOLE_BAUDRATE * 16
#elif defined(CONFIG_ARCH_MANGO_FPGA)
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_NORMAL	25000000
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_FAST	25000000
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_SAFE	25000000
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_BYPASS	25000000
#else
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_NORMAL	500000000
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_FAST	500000000
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_SAFE	250000000
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ_BYPASS	25000000
#endif

#define PLAT_MANGO_BOOT_SD_CLK_IN_HZ_NORMAL	100000000
#define PLAT_MANGO_BOOT_SD_CLK_IN_HZ_FAST	100000000
#define PLAT_MANGO_BOOT_SD_CLK_IN_HZ_SAFE	100000000
#define PLAT_MANGO_BOOT_SD_CLK_IN_HZ_BYPASS	25000000

#define PLAT_MANGO_BOOT_EMMC_CLK_IN_HZ_NORMAL	100000000
#define PLAT_MANGO_BOOT_EMMC_CLK_IN_HZ_FAST	100000000
#define PLAT_MANGO_BOOT_EMMC_CLK_IN_HZ_SAFE	100000000
#define PLAT_MANGO_BOOT_EMMC_CLK_IN_HZ_BYPASS	25000000

/*
 * UART setting
 */
#define PLAT_MANGO_BOOT_UART_BASE		UART1_BASE
#define PLAT_MANGO_BOOT_UART_CLK_IN_HZ		PLAT_MANGO_BOOT_UART_CLK_IN_HZ_NORMAL
#define PLAT_MANGO_CRASH_UART_BASE		PLAT_MANGO_BOOT_UART_BASE
#define PLAT_MANGO_CRASH_UART_CLK_IN_HZ		PLAT_MANGO_BOOT_UART_CLK_IN_HZ
#define PLAT_MANGO_CONSOLE_BAUDRATE		115200

/*
 * GPIO setting
 * here we assue only the GPIO0's first(lower) 24 pins are used, and
 * the higher 8 pins are reserved for BOOT_SEL and MODE_SEL.
 */
#define REG_GPIO_DATA			0x0
#define REG_GPIO_DATA_DIR		0x4
#define REG_GPIO_EXT_PORTA		0x50

#define BIT_SHIFT_GPIO_I2C_ADDR		5 // 4bits, GPIO[8:5]
#define BIT_SHIFT_GPIO_PCIE_SEL		9 // 3bits, GPIO[11:9]
#define BIT_SHIFT_GPIO_PCIE_LANE_REV	12 // GPIO[12]
#define BIT_SHIFT_GPIO_PCIE_REFCLK	14 // GPIO[14]
#define BIT_SHIFT_GPIO_PCIE_RC_RST	16 // GPIO[16], output
#define BIT_SHIFT_GPIO_BOOT_SEL		24 // 4bits, from TOP register
#define BIT_SHIFT_GPIO_MODE_SEL		28 // 3bits, from TOP register

#define BIT_MASK_GPIO_I2C_ADDR		(0xF << BIT_SHIFT_GPIO_I2C_ADDR)
#define BIT_MASK_GPIO_PCIE_SEL		(0x7 << BIT_SHIFT_GPIO_PCIE_SEL)
#define BIT_MASK_GPIO_PCIE_LANE_REV	BIT(BIT_SHIFT_GPIO_PCIE_LANE_REV)
#define BIT_MASK_GPIO_PCIE_REFCLK	BIT(BIT_SHIFT_GPIO_PCIE_REFCLK)
#define BIT_MASK_GPIO_PCIE_RC_RST	BIT(BIT_SHIFT_GPIO_PCIE_RC_RST)
#define BIT_MASK_GPIO_BOOT_SEL		(0xF << BIT_SHIFT_GPIO_BOOT_SEL)
#define BIT_MASK_GPIO_MODE_SEL		(0x7 << BIT_SHIFT_GPIO_MODE_SEL)

#define MANGO_GPIO_BASE			GPIO0_BASE
#define MANGO_GPIO_SIZE			1024
#define MANGO_GPIO_WIDTH		32

/*
 * TOP registers
 */
#define REG_TOP_CHIP_VERSION		0x0
#define REG_TOP_CONF_INFO		0x4
#define REG_TOP_CTRL			0x8

#define REG_TOP_WDT_RST_STATUS		0x1C

#define REG_TOP_DBG_I2C_ID		0x40

#define REG_TOP_ARM_BOOT_ADDR_L		0x88
#define REG_TOP_ARM_BOOT_ADDR_H		0x8c

#define REG_TOP_DDR_SIZE_REG	0x54
#define REG_TOP_PLL_START		0xC0
#define REG_TOP_PLL_EN_CTRL		0xC4
#define REG_TOP_MPLL_CTRL		0xE8
#define REG_TOP_FPLL_CTRL		0xF4
#define REG_TOP_DPLL0_CTRL		0xF8
#define REG_TOP_DPLL1_CTRL		0xFC

#define REG_TOP_GP_REG0			0x1C0

#define REG_TOP_RP_CFGM_PERIPHBASE_L	0x358
#define REG_TOP_RP_CFGM_PERIPHBASE_H	0x35c

#define REG_TOP_CLOCK_ENABLE0		0x2000
#define REG_TOP_CLOCK_ENABLE1		0x2004

#define REG_TOP_SOFT_RST0		0x3000
#define REG_TOP_SOFT_RST1		0x3004
#define REG_TOP_SOFT_RST2		0x3008

#define BIT_UPDATING_DPLL0_VAL	BIT(4)
#define BIT_UPDATING_DPLL1_VAL	BIT(5)
#define BIT_DPLL1_LOCK			BIT(13)
#define BIT_DPLL0_LOCK			BIT(12)
#define BIT_DPLL0_CLK_EN		BIT(4)
#define BIT_DPLL1_CLK_EN		BIT(5)

#define BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN	BIT(2) // 1 to enable warm reboot
#define BIT_MASK_TOP_SOFT_RST0_WDT		BIT(10)

#define BIT_SHIFT_TOP_CONF_INFO_BOOT_SEL	0
#define BIT_SHIFT_TOP_CONF_INFO_MODE_SEL	8

#define BIT_MASK_TOP_CONF_INFO_BOOT_SEL		(0xFF << BIT_SHIFT_TOP_CONF_INFO_BOOT_SEL)
#define BIT_MASK_TOP_CONF_INFO_MODE_SEL		(0x7 << BIT_SHIFT_TOP_CONF_INFO_MODE_SEL)

#define BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN	BIT(2) // 1 to enable warm reboot

#define BIT_MASK_TOP_SOFT_RST0_DDRC		(0xFF << 3)
#define BIT_MASK_TOP_SOFT_RST0_EMMC		BIT(27)
#define BIT_MASK_TOP_SOFT_RST0_SDIO		BIT(28)
#define BIT_MASK_TOP_SOFT_RST0_I2C0		BIT(13)

#define BIT_MASK_TOP_SOFT_RST1_WDT		BIT(10)

/*
 * MCU register
 */
#define MCU_I2C_DEV		1
#define MCU_DEV_ADDR		0x17

#define HW_TYPE_REG		0x00
#define HW_VERSION_REG		0x02 // BOM version
#define INSTRUCT_REG		0x03
#define DDR_TYPE_REG		0x15 // LPDDR4 or LPDDR4X
#define PCIE_CHECK_REG		0x17 // use perst signal to check PCIe plugging

#define POWER_OFF_CMD		0x02
#define REBOOT_CMD		0x07

/*
 * eFuse register
 */
#define REG_EFUSE_MODE		0x0
#define REG_EFUSE_ADR		0x4
#define REG_EFUSE_RD_DATA	0xc
#define REG_EFUSE_ECCSRAM_ADR		0x10
#define REG_EFUSE_ECCSRAM_RDPORT	0x14

#define EFUSE_NUM_ADDRESS_BITS		7

/******************************************************************************
 * eFuse has 4096bits, each content in eFuse has an extra
 * copy for reliablity reason. so the access scheme is:
 * each 32bits address includes a block id in lower 16bits and
 * a cell id in upper 16bits. we use the block id to find the
 * first cell of the wanted content, and use cell id to get the
 * exact cell we want inside this block.
 *****************************************************************************/
#define EBLK_ID_SECONF		0
#define EBLK_ID_ROTPKD		1

// cell index for block content and its duplicate, physical
#define EBLK_BASE_SECONF	0
#define EBLK_DUP_SECONF		0
#define EBLK_BASE_ROTPKD	18
#define EBLK_DUP_ROTPKD		26

// bit define in cell[0], logical, after merged double bits
#define EBIT_SHIFT_SEC_FIREWALL		0
#define EBIT_SHIFT_JTAG_DBG_DIS		1
#define EBIT_SHIFT_ONCHIP_BOOT		2
#define EBIT_SHIFT_SECURE_BOOT		3

/*
 * Watchdog register
 */
#define REG_WDT_CR		0x00 /*control register*/
#define REG_WDT_TORR		0x04 /*timeout range register*/
#define REG_WDT_CCVR    `	0x08 /*current counter register*/
#define REG_WDT_CRR		0x0C /*counter restart register*/
#define REG_WDT_STAT		0x10 /*interrupt status register */
#define REG_WDT_EOI		0x14 /*interrupt clear register */

#define WDT_CRR_RESTART_VAL	(0x76)
#define WDT_CR_RPL_8PCLK_VAL	(0x010)
#define WDT_CR_EN		(1)

#define WDT_CR_EN_OFFSET	BIT(0)//enable
#define WDT_CR_RMOD_OFFSET	BIT(1)//response mode
#define WDT_CR_RPL_OFFSET	BIT(2)//reset pulse length

#define WDT_TORR_TOP_INIT_OFFSET	BIT(4)//top init

/*
 * device address map
 */

/* EFUSE0 - FAU2_CFG */
#define DEVICE0_BASE			EFUSE0_BASE
#define DEVICE0_SIZE			0x94000000

#define RV_BOOTROM_BASE			DDR0_BASE
#define RV_BOOTROM_SIZE			(64 * 1024)

#define FLASH0_BASE			SERIAL_FLASH0_BASE
#if defined(CONFIG_ARCH_MANGO_FPGA) && !defined(FPGA_BL1_TEST)
#define FLASH1_BASE			NS_DRAM_BASE + DDR_OFFSET_FLASH
#else
#define FLASH1_BASE			SERIAL_FLASH1_BASE
#endif
#define FLASH_SIZE			0x01000000 //16MB

/* sg2042 memory map */
#define DDR0_BASE			0x0000000000
#define DDR1_BASE			0x1000000000
#define DDR2_BASE			0x2000000000
#define DDR3_BASE			0x3000000000
#define PCIE0_SLV0_BASE			0x4000000000
#define PCIE0_SLV1_BASE			0x4400000000
#define PCIE1_SLV0_BASE			0x4800000000
#define PCIE1_SLV1_BASE			0x4C00000000
#define BOOT_ROM0_BASE			0x7000100000
#define BOOT_ROM1_BASE			0x7000140000
#define SERIAL_FLASH0_BASE		0x7000180000
#define SERIAL_FLASH1_BASE		0x7002180000
#define LPC_BASE			0x7008000000
#define SRAM0_BASE			0x7010000000
#define SRAM1_BASE			0x7010100000
#define EFUSE0_BASE			0x7030000000
#define EFUSE1_BASE			0x7030001000
#define RTC_BASE			0x7030002000
#define TIMER_BASE			0x7030003000
#define WDT_BASE			0x7030004000
#define I2C0_BASE			0x7030005000
#define I2C1_BASE			0x7030006000
#define I2C2_BASE			0x7030007000
#define I2C3_BASE			0x7030008000
#define GPIO0_BASE			0x7030009000
#define GPIO1_BASE			0x703000A000
#define GPIO2_BASE			0x703000B000
#define PWM_BASE			0x703000C000
#define SYS_CTRL_BASE			0x7030010000
#define GIC_BASE			0x7031000000
#define CCI_CFG_BASE			0x7032000000
#define UART0_BASE			0x7040000000
#define UART1_BASE			0x7040001000
#define UART2_BASE			0x7040002000
#define UART3_BASE			0x7040003000
#define SPI0_BASE			0x7040004000
#define SPI1_BASE			0x7040005000
#define SYS_DMA_CFG_BASE		0x7040006000
#define HS_DMA_CFG_BASE			0x7040016000
#define ETH0_CFG_BASE			0x7040026000
#define EMMC_BASE			0x704002A000
#define SDIO_BASE			0x704002B000
#define TOP_MONITOR_BASE		0x70400A0000
#define HSPERI_MONITOR_BASE		0x70402A0000
#define DDR0_CFG_BASE			0x7050000000
#define DDR1_CFG_BASE			0x7052000000
#define DDR2_CFG_BASE			0x7054000000
#define DDR3_CFG_BASE			0x7056000000
#define PCIE0_CFG_BASE			0x7060000000
#define PCIE1_CFG_BASE			0x7062000000
#define CMN600_BASE			0x7070000000
#define PLIC_CFG_BASE			0x7090000000
#define CLINT_IPI_CFG_BASE		0x7094000000
#define RP_CPU_CLINT_TIMER_CFG_BASE	0x70AC000000
#define RPU_CFG				0x70b0000000
#define FAU0_CFG_BASE			0X70B8000000
#define FAU1_CFG_BASE			0X70BC000000
#define FAU2_CFG_BASE			0X70C0000000
#define DDR0_CFG_SIZE			0x0002000000
#define GICD_BASE			GIC_BASE + 0x1000
#define GICC_BASE			GIC_BASE + 0x2000
#define TOP_BASE			SYS_CTRL_BASE

#define MANGO_IRQ_SEC_SGI_0		8
#define MANGO_IRQ_SEC_SGI_1		9
#define MANGO_IRQ_SEC_SGI_2		10
#define MANGO_IRQ_SEC_SGI_3		11
#define MANGO_IRQ_SEC_SGI_4		12
#define MANGO_IRQ_SEC_SGI_5		13
#define MANGO_IRQ_SEC_SGI_6		14
#define MANGO_IRQ_SEC_SGI_7		15

/******************************************************************************
 * On a GICv2 system, the Group 1 secure interrupts are treated as Group 0
 * interrupts.
 *****************************************************************************/
#define PLATFORM_G1S_PROPS(grp)						\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_0, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_1, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_2, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_3, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_4, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_5, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_6, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(MANGO_IRQ_SEC_SGI_7, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE)

#define PLATFORM_G0_PROPS(grp)

#ifndef __ASSEMBLER__

void plat_sys_reset(int is_warm_reset) __dead2;
void plat_spif_program(uint64_t addr, uint32_t offset, uint32_t size);
int plat_spif_read(uint64_t addr, uint32_t offset, uint32_t size);
void plat_cli_prepare(void);

#endif

#endif /* PLATFORM_DEF_H */
