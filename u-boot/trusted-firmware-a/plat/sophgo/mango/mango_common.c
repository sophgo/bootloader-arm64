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

#include "mango_common.h"

#define MAP_DEVICE0	MAP_REGION_FLAT(DEVICE0_BASE,			\
					DEVICE0_SIZE,			\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_SHARED_RAM	MAP_REGION_FLAT(SHARED_RAM_BASE,		\
					SHARED_RAM_SIZE,		\
					MT_DEVICE  | MT_RW | MT_SECURE)

#define MAP_NS_DRAM	MAP_REGION_FLAT(NS_DRAM_BASE,			\
					NS_DRAM_SIZE,			\
					MT_MEMORY | MT_RW | MT_NS)

#define MAP_FLASH0	MAP_REGION_FLAT(FLASH0_BASE,		\
					FLASH_SIZE,		\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_FLASH1	MAP_REGION_FLAT(FLASH1_BASE,		\
					FLASH_SIZE,		\
					MT_DEVICE | MT_RW | MT_SECURE)

#define MAP_IO_BUFFER	MAP_REGION_FLAT(IO_BUFFER_BASE,		\
					IO_BUFFER_SIZE,		\
					MT_MEMORY | MT_RW | MT_SECURE)

/*
 * Table of regions for various BL stages to map using the MMU.
 * This doesn't include TZRAM as the 'mem_layout' argument passed to
 * arm_configure_mmu_elx() will give the available subset of that,
 */
#ifdef IMAGE_BL1
static const mmap_region_t mango_mmap[] = {
	MAP_FLASH1,
	MAP_SHARED_RAM,
	MAP_DEVICE0,
#ifdef CONFIG_ARCH_MANGO_FPGA
	MAP_NS_DRAM,
#endif
	{0}
};
#endif

#ifdef IMAGE_BL2
static const mmap_region_t mango_mmap[] = {
	MAP_FLASH0,
	MAP_FLASH1,
	MAP_SHARED_RAM,
	MAP_IO_BUFFER,
	MAP_DEVICE0,
	MAP_NS_DRAM,
	{0}
};
#endif

#ifdef IMAGE_BL31
static const mmap_region_t mango_mmap[] = {
	MAP_SHARED_RAM,
	MAP_DEVICE0,
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
		mmap_add(mango_mmap);				\
		init_xlat_tables();					\
									\
		enable_mmu_##_el(0);					\
	}

/* Define EL1 and EL3 variants of the function initialising the MMU */
DEFINE_CONFIGURE_MMU_EL(el1)
DEFINE_CONFIGURE_MMU_EL(el3)

/*
 * Mango platform routines
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

	for (i = 0; i < MANGO_GPIO_WIDTH; ++i)
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
		clk_in_hz = PLAT_MANGO_BOOT_SD_CLK_IN_HZ_NORMAL;
		break;
	case MODE_FAST:
		clk_in_hz = PLAT_MANGO_BOOT_SD_CLK_IN_HZ_FAST;
		break;
	case MODE_SAFE:
		clk_in_hz = PLAT_MANGO_BOOT_SD_CLK_IN_HZ_SAFE;
		break;
	case MODE_BYPASS:
		clk_in_hz = PLAT_MANGO_BOOT_SD_CLK_IN_HZ_BYPASS;
		break;
	default:
		clk_in_hz = PLAT_MANGO_BOOT_SD_CLK_IN_HZ_NORMAL;
		break;
	}
	return clk_in_hz;
}

void bm_wdt_stop(void)
{
	mmio_clrbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN);
	// reset watchdog module
	mmio_clrbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_WDT);
	udelay(1);
	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_WDT);
	// clear indicator
	mmio_write_32(TOP_BASE + REG_TOP_WDT_RST_STATUS, 1);
}

void bm_wdt_start(uint32_t top)
{
	mmio_setbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_SW_ROOT_RESET_EN);
	// watchdog is at 100MHz, timeout period is 2 ^ (16 + i), i = 0 to 15
	mmio_write_32(WDT_BASE + REG_WDT_TORR, top | (top << 4)); // Set timeout range reigster
	mmio_write_32(WDT_BASE + REG_WDT_CRR, 0x76); // Counter restart register
	mmio_write_32(WDT_BASE + REG_WDT_CR, 0x11); // Reset pulse length, Response mode and enable WDT
}

void bm_wdt_reset(void)
{
	NOTICE("watchdog reset\n");
	console_flush();

	bm_wdt_stop();
	bm_wdt_start(0);
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
	dw_gpio_init(MANGO_GPIO_BASE, MANGO_GPIO_SIZE, MANGO_GPIO_WIDTH);
}

void __dead2 plat_error_handler(int err)
{
#if DEBUG
	cli_loop(0);
#endif
	bm_wdt_start(15);

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
	bm_spi_init(FLASH1_BASE);
	bm_spi_flash_program((uint8_t *)addr, offset, size);
	// back to DMMR mode
	mmio_write_32(FLASH1_BASE + REG_SPI_DMMR, 1);
}

int plat_spif_read(uint64_t addr, uint32_t offset, uint32_t size)
{
	int ret;

	bm_spi_init(FLASH1_BASE);
	ret = bm_spi_flash_read((uint8_t *)addr, offset, size);
	// back to DMMR mode
	mmio_write_32(FLASH1_BASE + REG_SPI_DMMR, 1);

	return ret;
}

void plat_cli_prepare(void)
{
	bm_wdt_stop();
}
