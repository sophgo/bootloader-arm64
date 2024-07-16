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
	BOOTSEL_FORCE_SRAM = 0x2,
	BOOTSET_SPIF_BOOT = 0x8,
};

enum {
	FIP_SRC_SPIF = 0x0, // SPI flash
	FIP_SRC_SRAM = 0x1, // SRAM upper half
	FIP_SRC_SDFT = 0x2, // SD card FAT32 partition
};

enum {
	FIP_LOADED = (1 << 0), // fip.bin being loaded into RAM
	SKIP_PCIEI = (1 << 1), // skip PCIe init during boot
	PCIE_MODE = (1 << 2), // This indicates the board is PCIe mode
};

enum {
	MCU_BOARD_TYPE_EVB = 0,
};

enum {
	BOARD_PLD = 0,
	BOARD_FPGA = 1,
	BOARD_EVB_V1_0 = 2,
};

enum {
	BM_CORE_DOWN = 0,
	BM_CORE_UP = 1,
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
void bm_ddr_init_pld(void);
void bm_ddr_init_asic(void);
void bm_ip_reset(void);
void bm_pin_init(void);
void bm_ncore_setup(int32_t en);
void bm_pcie_init(void);

unsigned int bm_calc_core_pos(u_register_t mpidr);
void bm_locate_next_image(void);
void bm_pcie_status_init(void);
bool bm_check_pcie_link(void);
int bm_get_sd_clock(void);
void bm_dump_nv_counter(const char *tag);

uint32_t bm_gpio_read(uint32_t mask);
void bm_wdt_reset(void);
void bm_wdt_start(uint32_t top);
void bm_wdt_stop(void);

void bm_gic_init(void);
void bm_pwr_gic_on_finish(void);

void bm_ncore_init(uintptr_t ncore_base);
void bm_ncore_enable_cluster(int en);

void bm_clear_secure_firewall(void);

#endif /* BM_PRIVATE_H */
