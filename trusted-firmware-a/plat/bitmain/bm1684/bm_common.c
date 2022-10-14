/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>
#include <arch_helpers.h>
#include <common/bl_common.h>
#include <common/debug.h>
#include <drivers/delay_timer.h>
#include <lib/xlat_tables/xlat_tables_v2.h>
#include <lib/mmio.h>
#include <lib/cli.h>
#include <drivers/bitmain/bm_spif.h>
#include <dw_gpio.h>
#include <gpio.h>

#include "bm_common.h"

#define MAP_DEVICE1	MAP_REGION_FLAT(DEVICE1_BASE,			\
					DEVICE1_SIZE,			\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_DEVICE2	MAP_REGION_FLAT(DEVICE2_BASE,			\
					DEVICE2_SIZE,			\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_DEVICE3	MAP_REGION_FLAT(DEVICE3_BASE,			\
					DEVICE3_SIZE,			\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_SHARED_RAM	MAP_REGION_FLAT(SHARED_RAM_BASE,		\
					SHARED_RAM_SIZE,		\
					MT_DEVICE  | MT_RW | MT_SECURE)

#define MAP_NS_DRAM	MAP_REGION_FLAT(NS_DRAM_BASE,			\
					NS_DRAM_SIZE,			\
					MT_MEMORY | MT_RW | MT_NS)

#define MAP_NS_SRAM	MAP_REGION_FLAT(NS_SRAM_BASE,			\
					NS_SRAM_SIZE,			\
					MT_NON_CACHEABLE | MT_RW | MT_SECURE)

#define MAP_DDRC	MAP_REGION_FLAT(DDRC_BASE,			\
					DDRC_SIZE,			\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_IO_BUFFER	MAP_REGION_FLAT(IO_BUFFER_BASE,			\
					IO_BUFFER_SIZE,			\
					MT_MEMORY | MT_RW | MT_SECURE)

/*
 * Table of regions for various BL stages to map using the MMU.
 * This doesn't include TZRAM as the 'mem_layout' argument passed to
 * arm_configure_mmu_elx() will give the available subset of that,
 */
#ifdef IMAGE_BL1
static const mmap_region_t bm_mmap[] = {
	MAP_SHARED_RAM,
	MAP_DEVICE1,
	MAP_DEVICE2,
	MAP_DEVICE3,
	MAP_NS_SRAM,
#ifdef CONFIG_ARCH_BM1686_FPGA
	MAP_NS_DRAM,
#endif
	{0}
};
#endif

#ifdef IMAGE_BL2
static const mmap_region_t bm_mmap[] = {
	MAP_SHARED_RAM,
	MAP_IO_BUFFER,
	MAP_DEVICE1,
	MAP_DEVICE2,
	MAP_DEVICE3,
	MAP_NS_SRAM,
	MAP_DDRC,
	MAP_NS_DRAM,
	{0}
};
#endif

#ifdef IMAGE_BL31
static const mmap_region_t bm_mmap[] = {
	MAP_SHARED_RAM,
	MAP_DEVICE2,
	MAP_NS_SRAM,
	MAP_NS_DRAM,
	{0}
};
#endif

/*******************************************************************************
 * Macro generating the code for the function setting up the pagetables as per
 * the platform memory map & initialize the mmu, for the given exception level
 ******************************************************************************/

#define DEFINE_CONFIGURE_MMU_EL(_el)					\
	void bm_configure_mmu_##_el(unsigned long total_base,	\
				   unsigned long total_size,		\
				   unsigned long code_start,		\
				   unsigned long code_limit,		\
				   unsigned long ro_start,		\
				   unsigned long ro_limit,		\
				   unsigned long coh_start,		\
				   unsigned long coh_limit)		\
	{								\
		mmap_add_region(total_base, total_base,			\
				total_size,				\
				MT_MEMORY | MT_RW | MT_SECURE);		\
		mmap_add_region(code_start, code_start,			\
				code_limit - code_start,		\
				MT_CODE | MT_SECURE);			\
		mmap_add_region(ro_start, ro_start,			\
				ro_limit - ro_start,			\
				MT_RO_DATA | MT_SECURE);		\
		mmap_add_region(coh_start, coh_start,			\
				coh_limit - coh_start,			\
				MT_DEVICE | MT_RW | MT_SECURE);		\
		mmap_add(bm_mmap);				\
		init_xlat_tables();					\
									\
		enable_mmu_##_el(0);					\
	}

/* Define EL1 and EL3 variants of the function initialising the MMU */
DEFINE_CONFIGURE_MMU_EL(el1)
DEFINE_CONFIGURE_MMU_EL(el3)

/*
 * Bitmain platform routines
 */
uint32_t system_counter_freq = SYS_COUNTER_FREQ_IN_TICKS;
static uint32_t gpio_value_override;

unsigned int plat_get_syscnt_freq2(void)
{
	uint32_t mode_sel = bm_gpio_read(BIT_MASK_GPIO_MODE_SEL);

	switch (mode_sel) {
	case MODE_BYPASS:
		system_counter_freq = SYS_COUNTER_FREQ_IN_TICKS_BYPASS;
		break;
	default:
		system_counter_freq = SYS_COUNTER_FREQ_IN_TICKS;
		break;
	}

	return system_counter_freq;
}

static inline uint32_t bm_gpio_get(void)
{
	int i;
	uint32_t value = 0;

	for (i = 0; i < BM_GPIO_WIDTH; ++i)
		value |= (gpio_get_value(i) == GPIO_LEVEL_HIGH ? 1 : 0) << i;

	return value;
}

uint32_t bm_gpio_read(uint32_t mask)
{
	uint32_t value;

	if (gpio_value_override) {
		value = gpio_value_override & mask;
	} else {
		if (mask == BIT_MASK_GPIO_BOOT_SEL) {
			// get the actual value
			value = mmio_read_32(TOP_BASE + REG_TOP_CONF_INFO);
			value &= BIT_MASK_TOP_CONF_INFO_BOOT_SEL;
			value >>= BIT_SHIFT_TOP_CONF_INFO_BOOT_SEL;
			// shift to GPIO bit sequence
			value <<= BIT_SHIFT_GPIO_BOOT_SEL;
		} else if (mask == BIT_MASK_GPIO_MODE_SEL) {
			// get the actual value
			value = mmio_read_32(TOP_BASE + REG_TOP_CONF_INFO);
			value &= BIT_MASK_TOP_CONF_INFO_MODE_SEL;
			value >>= BIT_SHIFT_TOP_CONF_INFO_MODE_SEL;
			// shift to GPIO bit sequence
			value <<= BIT_SHIFT_GPIO_MODE_SEL;
		} else {
			value = bm_gpio_get();
			value = value & mask;
		}
	}

	switch (mask) {
	case BIT_MASK_GPIO_I2C_ADDR:
		value >>= BIT_SHIFT_GPIO_I2C_ADDR;
		value |= 0x20; // to avoid I2C reserved address
		break;
	case BIT_MASK_GPIO_PCIE_SEL:
		value >>= BIT_SHIFT_GPIO_PCIE_SEL;
		break;
	case BIT_MASK_GPIO_PCIE_REFCLK:
		value >>= BIT_SHIFT_GPIO_PCIE_REFCLK;
		break;
	case BIT_MASK_GPIO_PCIE_LANE_REV:
		value >>= BIT_SHIFT_GPIO_PCIE_LANE_REV;
		break;
	case BIT_MASK_GPIO_BOOT_SEL:
		value >>= BIT_SHIFT_GPIO_BOOT_SEL;
		break;
	case BIT_MASK_GPIO_MODE_SEL:
		value >>= BIT_SHIFT_GPIO_MODE_SEL;
		break;
	default:
		value = 0;
		ERROR("illegal GPIO mask 0x%x\n", mask);
		break;
	}
	return value;
}

int bm_get_sd_clock(void)
{
	uint32_t clk_in_hz;
	uint32_t mode_sel = bm_gpio_read(BIT_MASK_GPIO_MODE_SEL);

	switch (mode_sel) {
	case MODE_NORMAL:
		clk_in_hz = PLAT_BM_BOOT_SD_CLK_IN_HZ_NORMAL;
		break;
	case MODE_FAST:
		clk_in_hz = PLAT_BM_BOOT_SD_CLK_IN_HZ_FAST;
		break;
	case MODE_SAFE:
		clk_in_hz = PLAT_BM_BOOT_SD_CLK_IN_HZ_SAFE;
		break;
	case MODE_BYPASS:
		clk_in_hz = PLAT_BM_BOOT_SD_CLK_IN_HZ_BYPASS;
		break;
	default:
		clk_in_hz = PLAT_BM_BOOT_SD_CLK_IN_HZ_NORMAL;
		break;
	}
	return clk_in_hz;
}

void bm_wdt_stop(void)
{
	mmio_clrbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN);
	// reset watchdog module
	mmio_clrbits_32(TOP_BASE + REG_TOP_SOFT_RST1, BIT_MASK_TOP_SOFT_RST1_WDT);
	udelay(1);
	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST1, BIT_MASK_TOP_SOFT_RST1_WDT);

	if (bm_get_chip_id() == CHIP_BM1684X) {
		// clear indicator
		mmio_write_32(TOP_BASE + REG_TOP_WDT_RST_STATUS, 1);
	}
}

void bm_wdt_start(uint32_t top)
{
	mmio_setbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN);
	// watchdog is at 100MHz, timeout period is 2 ^ (16 + i), i = 0 to 15
	mmio_write_32(WATCHDOG_BASE + REG_WDT_TORR, top | (top << 4)); // Set timeout range reigster
	mmio_write_32(WATCHDOG_BASE + REG_WDT_CRR, 0x76); // Counter restart register
	mmio_write_32(WATCHDOG_BASE + REG_WDT_CR, 0x11); // Reset pulse length, Response mode and enable WDT
}

void bm_wdt_reset(void)
{
	NOTICE("watchdog reset\n");
	console_flush();

	bm_wdt_stop();
	bm_wdt_start(0);
}

void bm_clear_secure_firewall(void)
{
	/*
	 * clear AXI SRAM protection, check platform_mem_init
	 * disable the 4th memory space for PCIe
	 */
	mmio_write_32(PCIE_SECURITY_BASE + REG_SECURE_CONTROL, 0x7);
	/* remove the 4th memory space for PCIe */
	mmio_write_32(PCIE_SECURITY_BASE + REG_SPACE3_START_ADDRESS, 0);
	mmio_write_32(PCIE_SECURITY_BASE + REG_SPACE3_END_ADDRESS, 0);
}

void bm_ip_reset(void)
{
	// I2C reset
	mmio_clrbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_I2C0);
	udelay(10);
	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_I2C0);
	udelay(10);

	// SDIO reset
	mmio_clrbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_SDIO);
	udelay(10);
	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_SDIO);
	udelay(10);
}

void bm_pin_init(void)
{
	dw_gpio_init(BM_GPIO_BASE, BM_GPIO_SIZE, BM_GPIO_WIDTH);
#ifdef IMAGE_BL1
	// PCIe RC reset pin
	gpio_set_direction(BIT_SHIFT_GPIO_PCIE_RC_RST, GPIO_DIR_OUT);

	// debug I2C address
	mmio_write_32(TOP_BASE + REG_TOP_DBG_I2C_ID, 0x80 | bm_gpio_read(BIT_MASK_GPIO_I2C_ADDR));

	NOTICE("GPIO0: %x\n", bm_gpio_get());
#endif
}

void bm_dump_nv_counter(const char *tag)
{
	uint64_t nv_counter = ((uint64_t)mmio_read_32(TOP_BASE + REG_TOP_NV_COUNTER_H) << 32) |
		mmio_read_32(TOP_BASE + REG_TOP_NV_COUNTER_L);

	printf("%s %ld\n", tag, nv_counter);
	// 25MHz, 40ns per tick
}

unsigned long BOARD_TYPE_REG;
unsigned long FIP_SOURCE_REG;
unsigned long BOOT_ARGS_REG;
unsigned long BOOT_STAGE_REG;
uint32_t SPIF_OFFSET_A_FIP;
uint32_t SPIF_OFFSET_B_FIP;

void bm_reg_base_init(void)
{
	// this should be called in each stage as early as possible
	if (bm_get_chip_id() == CHIP_BM1684) {
		BOARD_TYPE_REG = (SHARED_RAM_BASE + SHARED_RAM_SIZE - 4); // 4bytes, 0x10000FFC
		FIP_SOURCE_REG = (SHARED_RAM_BASE + SHARED_RAM_SIZE - 8); // 4bytes, 0x10000FF8
		BOOT_ARGS_REG = (SHARED_RAM_BASE + SHARED_RAM_SIZE - 12); // 4bytes, 0x10000FF4
		BOOT_STAGE_REG = (SHARED_RAM_BASE + SHARED_RAM_SIZE - 16); // 4bytes, 0x10000FF0
		SPIF_OFFSET_A_FIP = (0x00040000); // 256KB
		SPIF_OFFSET_B_FIP = (0x00240000); // 2MB + 256KB

		// workaround, SRAM may have random value
		if (mmio_read_32(BOOT_ARGS_REG) != SKIP_PCIEI) {
			// assume this is a cold boot
			mmio_write_32(BOOT_ARGS_REG, 0x0);
		}
	} else {
		BOARD_TYPE_REG = (TOP_BASE + 0x21C); // GP_REG31
		FIP_SOURCE_REG = (TOP_BASE + 0x218); // GP_REG30
		BOOT_ARGS_REG = (TOP_BASE + 0x214); // GP_REG29
		BOOT_STAGE_REG = (TOP_BASE + 0x210); // GP_REG28
		SPIF_OFFSET_A_FIP = (0x00030000); // 192KB
		SPIF_OFFSET_B_FIP = (0x00230000); // 2MB + 192KB
	}
}

void __dead2 plat_error_handler(int err)
{
#if defined(IMAGE_BL1) && defined(DEBUG)
	cli_loop(0);
#endif
	while (1)
		wfi();
}

void __dead2 plat_sys_reset(int is_warm_reset)
{
	if (is_warm_reset) {
		uint64_t rmr_el3;

		NOTICE("warm reset\n");
		console_flush();
		mmio_setbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN);
		mmio_setbits_32(BOOT_ARGS_REG, SKIP_PCIEI);

		rmr_el3 = read_rmr_el3();
		write_rmr_el3(rmr_el3 | RMR_WARM_RESET_CPU);
	} else {
		bm_wdt_reset();
	}

	while (1)
		wfi();
}

void plat_spif_program(uint64_t addr, uint32_t offset, uint32_t size)
{
	bm_spi_init(SPIF_BASE);
	bm_spi_flash_program((uint8_t *)addr, offset, size);
	// back to DMMR mode
	mmio_write_32(SPIF_BASE + REG_SPI_DMMR, 1);
}

void plat_cli_prepare(void)
{
	bm_wdt_stop();
	mmio_write_32(BOOT_STAGE_REG, 0);
}

void bm_storage_boot_loader_version(uint32_t addr)
{
	int size_version, size_time;

	size_version = strlen(version_string);
	for (int i = 0; i < size_version; i++) {
		mmio_write_8(addr + i, version_string[i]);
	}

	mmio_write_8(addr + size_version, ' ');

	size_time = strlen(build_message);
	for (int i = 0; i < size_time; i++) {
		mmio_write_8(addr + size_version + 1 + i, build_message[i]);
	}

	mmio_write_8(addr + size_version + 1 + size_time, '\0');
}
