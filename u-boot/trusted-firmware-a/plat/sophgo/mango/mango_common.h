/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BM_PRIVATE_H
#define BM_PRIVATE_H

#include <stdint.h>

enum {
	MODE_NORMAL = 0x0,
	MODE_FAST,
	MODE_SAFE,
	MODE_BYPASS,
};

enum {
	BOOTSEL_SKIP_SD = 0x1,
	BOOTSEL_SPIF_BOOT = 0x2,
	BOOTSEL_SKIP_CLI_DELAY = 0x4,
};

enum {
	FIP_SRC_SPIF = 0x0, // SPI flash
	FIP_SRC_SDFT = 0x1, // SD card FAT32 partition
};

enum {
	BOOT_START = 0xBEBEBEBE,
	BOOT_WDTED = 0xDEADDEAD, // watchdog timeout during boot
	BOOT_SUCSS = 0xDADADADA, // successful boot
};

enum {
	MCU_MANGO_EVB = 0x80,
};

enum {
	MANGO_PLD = 0,
	MANGO_FPGA = 1,
	MANGO_EVB_V0_0 = 2,
};

enum {
	MANGO_CORE_DOWN = 0,
	MANGO_CORE_UP = 1,
};

void bm_configure_mmu_svc_mon(unsigned long total_base,
			      unsigned long total_size,
			      unsigned long code_start, unsigned long code_limit,
			      unsigned long ro_start, unsigned long ro_limit,
			      unsigned long coh_start, unsigned long coh_limit);

void bm_configure_mmu_el1(unsigned long total_base, unsigned long total_size,
			  unsigned long code_start, unsigned long code_limit,
			  unsigned long ro_start, unsigned long ro_limit,
			  unsigned long coh_start, unsigned long coh_limit);

void bm_configure_mmu_el3(unsigned long total_base, unsigned long total_size,
			  unsigned long code_start, unsigned long code_limit,
			  unsigned long ro_start, unsigned long ro_limit,
			  unsigned long coh_start, unsigned long coh_limit);

void bm_console_init(void);
void bm_ip_reset(void);
void bm_pin_init(void);

unsigned int bm_calc_core_pos(u_register_t mpidr);
void bm_locate_next_image(void);
int bm_get_sd_clock(void);

uint32_t bm_gpio_read(uint32_t mask);
void bm_wdt_reset(void);
void bm_wdt_start(uint32_t top);
void bm_wdt_stop(void);

void bm_gic_init(void);
void bm_pwr_gic_on_finish(void);

void mango_cci_init(void);
void mango_cci_enable(int en);

#endif /* BM_PRIVATE_H */
