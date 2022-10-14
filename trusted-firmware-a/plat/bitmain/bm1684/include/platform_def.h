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

//#define CONFIG_ARCH_BM1686_PLD
//#define CONFIG_ARCH_BM1686_FPGA
#define BL1_IN_SPI_FLASH
//#define BL1_TEST_MODE
#define HAS_PCIE
//#define DDR_ECC_ENABLE

/* Special value used to verify platform parameters from BL2 to BL3-1 */
#define BM_BL31_PLAT_PARAM_VAL		0x0f1e2d3c4b5a6978ULL

#define PLATFORM_STACK_SIZE		0x1000

#define PLATFORM_MAX_CPUS_PER_CLUSTER	4
#define PLATFORM_CLUSTER_COUNT		2
#define PLATFORM_CLUSTER0_CORE_COUNT	PLATFORM_MAX_CPUS_PER_CLUSTER
#define PLATFORM_CLUSTER1_CORE_COUNT	PLATFORM_MAX_CPUS_PER_CLUSTER
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER0_CORE_COUNT + \
					 PLATFORM_CLUSTER1_CORE_COUNT)

#define BM_PRIMARY_CPU		0

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
 * Some data must be aligned on the biggest cache line size in the platform.
 * This is known only to the platform as it might have a combination of
 * integrated and external caches.
 */
#define CACHE_WRITEBACK_SHIFT		6
#define CACHE_WRITEBACK_GRANULE		BIT(CACHE_WRITEBACK_SHIFT)

/*
 * BM1686 FPGA has no SRAM, so we put ROM and SRAM at the end of DRAM.
 * it's safe for u-boot and kernel to over write these two regions,
 * just remember to reload them after every reset.
 */
#ifdef CONFIG_ARCH_BM1686_FPGA
#define DDR_OFFSET_ROM		0x10000000 // 256MB
#define DDR_OFFSET_SRAM		0x10100000 // 256+1MB
#endif

/*
 * Partition memory into secure ROM, non-secure DRAM, secure "SRAM",
 * and secure DRAM.
 */
#ifdef BL1_IN_SPI_FLASH
#define SEC_ROM_BASE			0x06000000
#elif defined(CONFIG_ARCH_BM1686_FPGA)
#define SEC_ROM_BASE			(NS_DRAM_BASE + DDR_OFFSET_ROM)
#else
#define SEC_ROM_BASE			0x07000000
#endif
#define SEC_ROM_SIZE			0x00020000 // 128KB

#define NS_DRAM0_BASE			0x100000000 // 8GB
#define NS_DRAM1_BASE			0x300000000 // 4GB
#define NS_DRAM2_BASE			0x400000000 // 4GB

#ifdef CONFIG_ARCH_BM1686_FPGA
#define NS_DRAM_BASE			NS_DRAM2_BASE
#else
#define NS_DRAM_BASE			NS_DRAM1_BASE
#endif
#define NS_DRAM_SIZE			0x10000000 // 256MB

#ifdef CONFIG_ARCH_BM1686_FPGA
#define SEC_SRAM_BASE			(NS_DRAM_BASE + DDR_OFFSET_SRAM)
#else
#define SEC_SRAM_BASE			0x10000000
#endif
#define SEC_SRAM_SIZE			0x00100000 // 1MB

#define NS_SRAM_BASE			(SEC_SRAM_BASE + SEC_SRAM_SIZE)
#define NS_SRAM_SIZE			0x00100000 // 1MB

#define PLAT_BM_FIP_MAX_SIZE		NS_SRAM_SIZE

#define SRAM_RESERVE_BASE		0x101FB000
#define BL1_VERSION_OFFSET		0x200
#define BL1_VERSION_BASE		(SRAM_RESERVE_BASE + BL1_VERSION_OFFSET)
#define BL1_VERSION_SIZE		0x40
#define BL2_VERSION_BASE		(BL1_VERSION_BASE + BL1_VERSION_SIZE)
#define BL2_VERSION_SIZE		0x40
#define BL31_VERSION_BASE		(BL2_VERSION_BASE + BL2_VERSION_SIZE)

/*
 * ARM-TF lives in SRAM, partition it here
 */

#define SHARED_RAM_BASE			SEC_SRAM_BASE
#define SHARED_RAM_SIZE			0x00001000 // 4KB

#define PLAT_BM_TRUSTED_MAILBOX_BASE	SHARED_RAM_BASE
#define PLAT_BM_TRUSTED_MAILBOX_SIZE	(8 + PLAT_BM_HOLD_SIZE)
#define PLAT_BM_HOLD_BASE		(PLAT_BM_TRUSTED_MAILBOX_BASE + 8)
#define PLAT_BM_HOLD_SIZE		(PLATFORM_CORE_COUNT * \
					 PLAT_BM_HOLD_ENTRY_SIZE)
#define PLAT_BM_HOLD_ENTRY_SHIFT	3
#define PLAT_BM_HOLD_ENTRY_SIZE		BIT(PLAT_BM_HOLD_ENTRY_SHIFT)
#define PLAT_BM_HOLD_STATE_WAIT		0
#define PLAT_BM_HOLD_STATE_GO		1

/*
 * some "register" for configurations, at end of share memory region
 */
#ifndef __ASSEMBLER__
extern unsigned long BOARD_TYPE_REG;
extern unsigned long FIP_SOURCE_REG;
extern unsigned long BOOT_ARGS_REG;
extern unsigned long BOOT_STAGE_REG;
extern uint32_t SPIF_OFFSET_A_FIP;
extern uint32_t SPIF_OFFSET_B_FIP;
#endif

#define FIP_SOURCE_REG_OLD		0x102FFFF8 // used by BM1684 boot ROMs

#define BL_RAM_BASE			(SHARED_RAM_BASE + SHARED_RAM_SIZE)
#define BL_RAM_SIZE			(SEC_SRAM_SIZE - SHARED_RAM_SIZE)

/*
 * block IO buffer, start address and size must be block size aligned
 */
#define IO_BUFFER_BASE			BL_RAM_BASE
#define IO_BUFFER_SIZE			0x00001000 // 4KB

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
#define BL1_RW_BASE		(IO_BUFFER_BASE + IO_BUFFER_SIZE)
#define BL1_RW_LIMIT		(BL1_RW_BASE + 0x0001E000) // 120KB

/* check bl2_entrypoint.S */
#define BL1_RW_BASE_OLD		0x1002E000 // used by BM1684 boot ROMs
#define BL1_RW_LIMIT_OLD	0x10040000 // used by BM1684 boot ROMs
#define BL1_RW_SIZE		(BL1_RW_LIMIT_OLD - BL1_RW_BASE_OLD) // 0x12000
#define BL1_RW_SAVE		(NS_SRAM_BASE + NS_SRAM_SIZE - BL1_RW_SIZE) // 0x102EE000
#define BL1_PARAM_SIZE		0x400
#define BL1_PARAM_SAVE		(BL1_RW_SAVE - BL1_PARAM_SIZE) // 0x102EA000
#define BL2_BASE_OLD		0x10003000 // used by BM1684 boot ROMs

/*
 * BL2 specific defines.
 *
 * Put BL2 just below BL3-1. BL2_BASE is calculated using the current BL2 debug
 * size plus a little space for growth.
 */
#define BL2_BASE			BL1_RW_LIMIT
#define BL2_LIMIT			(SEC_SRAM_BASE + SEC_SRAM_SIZE)

/*
 * BL3-1 specific defines.
 *
 * Put BL3-1 at the top of the Trusted SRAM. BL31_BASE is calculated using the
 * current BL3-1 debug size plus a little space for growth.
 */
#define BL31_BASE			NS_DRAM_BASE
#define BL31_LIMIT			(NS_DRAM_BASE + 0x40000) // 256KB
#define BL31_PROGBITS_LIMIT		(NS_DRAM_BASE + 0x20000) // 128KB

#define A53L_PARK_END			(NS_SRAM_BASE + NS_SRAM_SIZE)
#define A53L_PARK_SIZE			4
#define A53L_PARK_SHIFT			4
#define A53L_PARK_ALIGN			(1 << A53L_PARK_SHIFT)
#define A53L_PARK_START			\
	round_down((A53L_PARK_END - A53L_PARK_SIZE), A53L_PARK_ALIGN)
#define A53L_PARK_INST			0x14000000

#define NS_IMAGE_OFFSET			(NS_DRAM_BASE + 0x08000000) // 128MB, u-boot text base
#define NS_IMAGE_MAX_SIZE		(NS_DRAM_SIZE - 0x08000000) // 128MB

#define PLAT_PHY_ADDR_SPACE_SIZE	BIT(39)
#define PLAT_VIRT_ADDR_SPACE_SIZE	BIT(39)
#define MAX_MMAP_REGIONS		11
#define MAX_XLAT_TABLES			6
#define MAX_IO_DEVICES			3
#define MAX_IO_HANDLES			2

/*
 * DDR setting
 */
//#define DDR_PERF_ENABLE
//#define DDR_ENTER_REFRESH
#define DDR_RANK_SIZE		0x80000000 //2GB

/*
 * SPI flash layout, decided by boot ROM
 */
#define SPIF_OFFSET_A_BL1	(0)
#define SPIF_OFFSET_A_PAT	(0x00020000) // 128KB
#define SPIF_OFFSET_B_BL1	(0x00200000) // 2MB
#define SPIF_OFFSET_B_PAT	(0x00220000) // 2MB + 128KB
#define SPIF_OFFSET_BLEND	(0x00400000) // 4MB
#define SPIF_OFFSET_ALEND	(0x01000000) // 16MB

/*
 * Clock setting
 */
#ifdef CONFIG_ARCH_BM1686_PLD
#define SYS_COUNTER_FREQ_IN_TICKS		50000000
#elif defined(CONFIG_ARCH_BM1686_FPGA)
#define SYS_COUNTER_FREQ_IN_TICKS		20000000
#else
#define SYS_COUNTER_FREQ_IN_TICKS		50000000
#endif
#define SYS_COUNTER_FREQ_IN_TICKS_BYPASS	25000000

#ifdef CONFIG_ARCH_BM1686_PLD
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL	PLAT_BM_CONSOLE_BAUDRATE * 16
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_FAST	PLAT_BM_CONSOLE_BAUDRATE * 16
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_SAFE	PLAT_BM_CONSOLE_BAUDRATE * 16
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_BYPASS	PLAT_BM_CONSOLE_BAUDRATE * 16
#elif defined(CONFIG_ARCH_BM1686_FPGA)
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL	25000000
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_FAST	25000000
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_SAFE	25000000
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_BYPASS	25000000
#else
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL	500000000
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_FAST	500000000
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_SAFE	250000000
#define PLAT_BM_BOOT_UART_CLK_IN_HZ_BYPASS	25000000
#endif

#define PLAT_BM_BOOT_SD_CLK_IN_HZ_NORMAL	100000000
#define PLAT_BM_BOOT_SD_CLK_IN_HZ_FAST		100000000
#define PLAT_BM_BOOT_SD_CLK_IN_HZ_SAFE		100000000
#define PLAT_BM_BOOT_SD_CLK_IN_HZ_BYPASS	25000000

#define PLAT_BM_BOOT_EMMC_CLK_IN_HZ_NORMAL	100000000
#define PLAT_BM_BOOT_EMMC_CLK_IN_HZ_FAST	100000000
#define PLAT_BM_BOOT_EMMC_CLK_IN_HZ_SAFE	100000000
#define PLAT_BM_BOOT_EMMC_CLK_IN_HZ_BYPASS	25000000

/*
 * device address map
 */
#define DEVICE1_BASE			0x06000000 // SPI flash
#define DEVICE1_SIZE			0x00400000 // 4MB
#define DEVICE2_BASE			0x50000000 // peripheral registers
#define DEVICE2_SIZE			0x00300000 // 3MB
#define DEVICE3_BASE			0x5F600000 // PCIe config
#define DEVICE3_SIZE			0x00A00000 // 10MB

#define DDRC_BASE			0x68000000 // DDR controller
#define DDRC_SIZE			0x08000000 // 128MB

#define SPIF_BASE			0x06000000
#define EMMC_BASE			0x50100000
#define SDIO_BASE			0x50101000
#define DDR_CTRL2			0x68000000
#define DDR_CTRL0_A			0x6A000000
#define DDR_CTRL0_B			0x6C000000
#define DDR_CTRL1			0x6E000000
#define TOP_BASE			0x50010000
#define I2C0_BASE			0x5001A000
#define I2C1_BASE			0x5001C000
#define I2C2_BASE			0x5001E000
#define UART0_BASE			0x50118000
#define WATCHDOG_BASE			0x50026000
#define GPIO0_BASE			0x50027000
#define EFUSE_BASE			0x50028000
#define NCORE_BASE			0x50200000
#define DMAC_BASE			0x50110000

/*
 * UART setting
 */
#define PLAT_BM_BOOT_UART_BASE		UART0_BASE
#define PLAT_BM_BOOT_UART_CLK_IN_HZ	PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL
#define PLAT_BM_CRASH_UART_BASE		UART0_BASE
#define PLAT_BM_CRASH_UART_CLK_IN_HZ	PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL
#define PLAT_BM_CONSOLE_BAUDRATE	115200

/*
 * GPIO setting
 * here we assume only the GPIO0's first(lower) 24 pins are used, and
 * the higher 8 pins are reserved for BOOT_SEL and MODE_SEL.
 *
 * BM1684's ROM used GPIO0 to entering command line mode, GPIO12 to
 * disable MMU, and GPIO13 to apply eFuse patch`. be aware of this.
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

#define BM_GPIO_BASE	GPIO0_BASE
#define BM_GPIO_SIZE	1024
#define BM_GPIO_WIDTH	32

/*
 * TOP registers
 */
#define REG_TOP_CHIP_VERSION		0x0
#define REG_TOP_CONF_INFO		0x4
#define REG_TOP_CTRL			0x8
#define REG_TOP_ARM_BOOT_ADDR		0x20
#define REG_TOP_DBG_I2C_ID		0x2C
#define REG_TOP_A53L_RST_VEC		0x3C
#define REG_TOP_GP_REG0			0x80
#define REG_TOP_PLL_EN_CTRL		0xC4
#define REG_TOP_MPLL_CTRL		0xE8
#define REG_TOP_TPLL_CTRL		0xEC
#define REG_TOP_FPLL_CTRL		0xF0
#define REG_TOP_VPLL_CTL		0xF4
#define REG_TOP_NV_COUNTER_L		0x184
#define REG_TOP_NV_COUNTER_H		0x188
#define REG_TOP_WDT_RST_STATUS		0x18C
#define REG_TOP_PINMUX_BASE		0x488 // starts from GPIO0
#define REG_TOP_SOFT_RST0		0xC00
#define REG_TOP_SOFT_RST1		0xC04
#define REG_TOP_SOFT_RST2		0xC08
#define REG_TOP_CLOCK_ENABLE0		0x800
#define REG_TOP_CLOCK_ENABLE1		0x804
#define REG_TOP_CLOCK_ENABLE2		0x808
#define REG_TOP_CLOCK_ENABLE3		0x820

#define BIT_SHIFT_TOP_CONF_INFO_MODE_SEL	0
#define BIT_SHIFT_TOP_CONF_INFO_BOOT_SEL	3
#define BIT_SHIFT_TOP_CONF_INFO_EFUSE_CHK	15

#define BIT_MASK_TOP_CONF_INFO_MODE_SEL		(0x7 << BIT_SHIFT_TOP_CONF_INFO_MODE_SEL)
#define BIT_MASK_TOP_CONF_INFO_BOOT_SEL		(0xF << BIT_SHIFT_TOP_CONF_INFO_BOOT_SEL)
#define BIT_MASK_TOP_CONF_INFO_EFUSE_CHK	(0x1 << BIT_SHIFT_TOP_CONF_INFO_EFUSE_CHK)

#define BIT_MASK_TOP_CTRL_AHBROM_BOOT_FIN	BIT(0) // 1 to put boot ROM in sleep mode
#define BIT_MASK_TOP_CTRL_ITCM_AXI_ENABLE	BIT(1) // 0: ITCM for ARM9; 1: ITCM for A53
#define BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN	BIT(2) // 1 to enable warm reboot
#define BIT_MASK_TOP_CTRL_DDR_INTLV_EN		BIT(3)
#define BIT_MASK_TOP_CTRL_DDR_INTLV_MODE	BIT(4)

#define BIT_MASK_TOP_SOFT_RST0_A53L		BIT(1) // 0 to reset
#define BIT_MASK_TOP_SOFT_RST0_DDRC		(0xFF << 3)
#define BIT_MASK_TOP_SOFT_RST0_EMMC		BIT(20)
#define BIT_MASK_TOP_SOFT_RST0_SDIO		BIT(21)
#define BIT_MASK_TOP_SOFT_RST0_I2C0		BIT(26)

#define BIT_MASK_TOP_SOFT_RST1_WDT		BIT(3)

/*
 * MCU register
 */
#define MCU_I2C_DEV			1
#define MCU_DEV_ADDR			0x17

#define HW_TYPE_REG			0x00 // board type
#define HW_VERSION_REG			0x02 // PCB and BOM version
#define INSTRUCT_REG			0x03
#define DDR_TYPE_REG			0x15 // LPDDR4 or LPDDR4X
#define PCIE_CHECK_REG			0x17 // use perst signal to check PCIe plugging

#define POWER_OFF_CMD			0x02
#define REBOOT_CMD			0x07

/*
 * eFuse register
 */
#define REG_EFUSE_MODE			0x0
#define REG_EFUSE_ADR			0x4
#define REG_EFUSE_RD_DATA		0xc
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
#define REG_WDT_CR	0x0
#define REG_WDT_TORR	0x4
#define REG_WDT_CRR	0xC

/*
 * PCIe setting
 */
#define PCIE_SINGLE_CHIP_MODE		4
#define PCIE_RC_ONLY_MODE		3

#define PCIE_FOUR_CHIP_FIRST		7
#define PCIE_THREE_CHIP_FIRST		6
#define PCIE_TWO_CHIP_FIRST		5
#define PCIE_FOUR_CHIP_SECOND		2
#define PCIE_FOUR_CHIP_THIRD		1
#define PCIE_FOUR_CHIP_LAST		0

/*
 * NCORE register
 */
#define NCORE_DIRUCASER0	0x80040
#define NCORE_DIRUMRHER		0x80070
#define NCORE_DIRUSFER		0x80010
#define NCORE_CSADSER		0xff040

/*
 * GIC register
 */
#define GICD_BASE			0x50001000
#define GICC_BASE			0x50002000

#define BM_IRQ_SEC_SGI_0		8
#define BM_IRQ_SEC_SGI_1		9
#define BM_IRQ_SEC_SGI_2		10
#define BM_IRQ_SEC_SGI_3		11
#define BM_IRQ_SEC_SGI_4		12
#define BM_IRQ_SEC_SGI_5		13
#define BM_IRQ_SEC_SGI_6		14
#define BM_IRQ_SEC_SGI_7		15

/*
 * PCIE security register
 */
#define PCIE_SECURITY_BASE		0x5000E400
#define REG_SECURE_CONTROL		0x0
#define REG_SPACE3_START_ADDRESS	0x38
#define REG_SPACE3_END_ADDRESS		0x3c

/******************************************************************************
 * On a GICv2 system, the Group 1 secure interrupts are treated as Group 0
 * interrupts.
 *****************************************************************************/
#define PLATFORM_G1S_PROPS(grp)						\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_0, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_1, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_2, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_3, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_4, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_5, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_6, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE),	\
	INTR_PROP_DESC(BM_IRQ_SEC_SGI_7, GIC_HIGHEST_SEC_PRIORITY,	\
					   grp, GIC_INTR_CFG_EDGE)

#define PLATFORM_G0_PROPS(grp)

#ifndef __ASSEMBLER__

void plat_sys_reset(int is_warm_reset) __dead2;
void plat_spif_program(uint64_t addr, uint32_t offset, uint32_t size);
void plat_cli_prepare(void);

#endif

#endif /* PLATFORM_DEF_H */
