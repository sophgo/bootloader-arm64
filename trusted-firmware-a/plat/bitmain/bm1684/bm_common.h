/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef BM_PRIVATE_H
#define BM_PRIVATE_H

#include <stdint.h>
#include <lib/mmio.h>

enum {
	MODE_NORMAL = 0x0,
	MODE_FAST,
	MODE_SAFE,
	MODE_BYPASS,
};

enum {
	CHIP_BM1684 = 0x16840000,
	CHIP_BM1684X = 0x16860000,
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
	FIP_LOADED = (1 << 0), // fip.bin being loaded into RAM, set by PCIe host or JTAG
	SKIP_PCIEI = (1 << 1), // skip PCIe init during boot, set by warm reset routine
	PCIE_EP_LINKED = (1 << 2), // board has valid PCIe link to some PCIe host
	SOC_EP = (1 << 3), // SoC mode with PCIe EP linked
};

enum {
	BOOT_START = 0xBEBEBEBE,
	BOOT_WDTED = 0xDEADDEAD, // watchdog timeout during boot
	BOOT_SUCSS = 0xDADADADA, // successful boot
};

enum {
	MCU_BM1684_EVB = 0,
	MCU_BM1684_SM5_TB = 1,
	MCU_BM1684_SC5 = 2,
	MCU_BM1684_SE5_V1 = 3,
	MCU_BM1684_SM5_PB = 4,
	MCU_BM1684_SM5_RB = 5,
	MCU_BM1684_SC5T = 7,
	MCU_BM1684_SC5H = 8,
	MCU_BM1684_SC5P = 9,
	MCU_BM1684_SM5M_PB = 11,
	MCU_BM1684_SM5M_RB = 12,
	MCU_BM1684_SM5M_TB = 13,
	MCU_BM1684_SE5_V2 = 14,
	MCU_BM1684_SE6_CTRL = 15,
	MCU_BM1684X_SC7_HP300 = 16,
};

enum {
	MCU_BM1684X_EVB = 0x20,
	MCU_BM1684X_SM7M_RB = 0x30,
	MCU_BM1684X_SM7_CTRL = 0x31,
	MCU_BM1684X_SM7M_CUST_V1 = 0x32,
	MCU_BM1684X_SE7_V1 = 0x33,
};

enum {
	// BM1684 boards
	BM1684_EVB_V1_2 = 6,
	BM1684_CUST_V1_1 = 4,
	BM1684_CUST_V1_3 = 33,
	BM1684_CUST_V1_4 = 34,
	BM1684_SM5_V1_1_RB = 7,
	BM1684_SM5_V1_2_RB = 17,
	BM1684_SM5_V1_2_TB = 18,
	BM1684_SE5_V1_1 = 5,
	BM1684_SE5_V1_3 = 8,
	BM1684_SE5_V2_0 = 23,
	BM1684_SE5_V2_1 = 22,
	BM1684_SE5_V2_5 = 26,
	BM1684_SM5M_V0_0_RB = 10,
	BM1684_SM5M_V0_1_RB = 14,
	BM1684_SM5M_V0_2_RB = 20,
	BM1684_SM5M_V3_0_RB = 30,
	BM1684_SM5M_V3_1_RB = 35,
	BM1684_SM5M_V0_0_TB = 11,
	BM1684_SM5M_V0_1_TB = 15,
	BM1684_SM5M_V0_2_TB = 21,
	BM1684_SM5M_V3_0_TB = 31,
	BM1684_SM5M_V3_1_TB = 36,
	BM1684_SE6_CTRL = 27,
	BM1684_SC5_EP = 38,
	BM1684_SC5_MIX = 39,

	// BM1684x boards
	BM1684X_PLD = 128,
	BM1684X_FPGA = 129,
	BM1684X_EVB_V0_0 = 130,
	BM1684X_EP = 131,
	BM1684X_SC7_HP300 = 132, // deperecated
	BM1684X_MIX = 133,
	BM1684X_SM7M_V0_0_RB = 134,
	BM1684X_SM7_CTRL = 135,
	BM1684X_SM7M_V0_0_CUST_V1 = 136,
	BM1684X_SE7_V1 = 137,

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

void bm_reg_base_init(void);
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

static inline uint32_t bm_get_chip_id(void)
{
	return mmio_read_32(TOP_BASE + REG_TOP_CHIP_VERSION);
}

void bm_storage_boot_loader_version(uint32_t addr);

#endif /* BM_PRIVATE_H */
