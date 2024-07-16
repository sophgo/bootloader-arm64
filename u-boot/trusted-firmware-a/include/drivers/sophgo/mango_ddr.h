/*
 * Copyright (c) 2020, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <string.h>
#include <stdint.h>
#include<stdbool.h>

#ifndef MANGO_DDR_H
#define MANGO_DDR_H

void mango_ddr_init(void);
void mango_ddr_init_pld(void);
void mango_ddr_init_asic(void);

/* define CTL PHY PI registers regmap */
#define DDR_CTL_BASE_ADDR  0
#define DDR_PI_BASE_ADDR   0x2000
#define DDR_PHY_BASE_ADDR  0x4000

#define MANGO_MAX_RANKS 8
#define MANGO_MAX_DIMMS 4
#define MANGO_MAX_BYTES 9
#define MANGO_MAX_BIT   8
#define SPD_SIZE        512

#define DRAM_FREQ_3200		3200
#define DRAM_FREQ_2666		2666 //2650
#define DRAM_FREQ_2400		2400
#define DRAM_FREQ_1600		1600

#define DRAM_CYCLE_3200		625
#define DRAM_CYCLE_2666		750 //2650
#define DRAM_CYCLE_2400		833
#define DRAM_CYCLE_1600		1250

#define BL8   0x3

#define ECC_EN    true
#define ECC_DIS   false

#define RDIMM 0x1
#define UDIMM 0x2
#define SODIMM 0x3

#define DFS_EN    true
#define DFS_DIS   false

#define FAST_BOOT_EN    true
#define FAST_BOOT_DIS   false

//1600
#define MR0   0x414
#define MR1   0x301
#define MR2   0x400
#define MR3   0
#define MR4   0
#define MR5   0x501
#define MR6   0x493

//3200
//#define MR0   0x2050
//#define MR1   0x301
//#define MR2   0x428
//#define MR3   0x400
//#define MR4   0
//#define MR5   0x503
//#define MR6   0x1093

typedef enum {
	IDLE = 0,
	active_power_down,
	active_power_down_with_memory_clock_gating,
	pre_charge_power_down,
	pre_charge_power_down_with_memory_clock_gating,
	self_refresh_short,
	self_refresh_short_with_memory_clock_gating,
	self_refresh_long,
	self_refresh_long_with_memory_glock_gating,
	self_refresh_long_with_memory_and_controller_clock_gating
} low_power_state;

typedef struct {
	uint8_t  BG_num;
	uint8_t  bank_num;
	uint8_t  row_num;
	uint8_t  col_num;
	uint8_t  rank_num;
	uint32_t rank_size; //unit of M

} mango_ddr_rank_info;

typedef struct{
	bool spd_present;
	bool ecc_support;
	uint8_t dev_type;// DDR3 DDR4
	uint8_t ddr_type;// rdimm sodimm udimm
	uint8_t package_type;
	uint8_t nominal_voltage[3];
	uint8_t bus_width;
	uint8_t timebase[2];
	uint8_t min_cycle_time;
	uint8_t max_cycle_time;
	uint8_t support_cl_byte[4];
	uint8_t min_cl_time;
	uint8_t min_trcd;
	uint8_t min_trrd_short;
	uint8_t min_trrd_long;
	uint8_t min_trp;
	uint8_t upper_nibble_tras_trc;
	uint8_t min_tras_lsb;
	uint8_t min_trfc_lsb;
	uint8_t min_trfc1_lsb;
	uint8_t min_trfc1_msb;
	uint8_t min_trfc2_lsb;
	uint8_t min_trfc2_msb;
	uint8_t min_trfc3_lsb;
	uint8_t min_trfc3_msb;
	uint8_t min_upper_nibble_tfaw;
	uint8_t min_tfaw;
	uint8_t max_activate_count;
	uint8_t max_activate_window;
	uint8_t post_package_repair;
	uint8_t tccd_long_fine_offset;
	uint8_t trrd_long_fine_offset;
	uint8_t trrd_short_fine_offset;
	uint8_t trc_fine_offset;
	uint8_t trp_fine_offset;
	uint8_t trcd_fine_offset;
	uint8_t cl_fine_offset;
	uint8_t min_cycle_time_fine_offset;
	uint8_t max_cycle_time_fine_offset;
	uint8_t thermal_refresh;
	uint8_t thermal_sensor;
	uint8_t reference_raw_card;
	uint8_t udimm_rank1_addrmapping;
	uint8_t rdimm_rank1_addrmapping;
	uint8_t rcd_ca_drive[4];
	uint8_t rcd_clk_drive[2];
	uint8_t rank_num;
	uint8_t DDR4_MIN_CYCLE;
	uint8_t DDR4_SERIAL_NUMBER[4];
	uint8_t DDR4_PART_NUMBER[20];
	uint8_t module_type; //ddr3  ddr4
	uint8_t MANUFACTURING_INFO[5];//320-324
	uint8_t buffer[SPD_SIZE];
} mango_spd_data;

typedef struct{
	//init
	bool  ecc;
	bool  dfs;
	bool  fast_boot;
	uint8_t  wrlvl_en;
	uint8_t  wrlvl_map;
	uint8_t  gate_en;
	uint8_t  gate_map;
	uint8_t  rdlvl_map;
	uint8_t  rdlvl_en;
	uint8_t  wdq_en;
	uint8_t  wdq_map;
	uint8_t  pi_cs_map;
	uint8_t  ctrl_cs_map;
	uint8_t  start_pi;
	uint8_t  disable_pi_lvl;
	uint8_t  pi_init_mode_reg;
	uint8_t  mc_init;
	uint8_t  pi_init;
	//IO_calibration
	uint8_t  init_disable;
	uint8_t  auto_enable;
	uint8_t  base_mode;
	uint8_t  cal_polarity;
	uint8_t  cal_mode_pass1;
	uint8_t  cal_mode_pass2;
	//write leveling
	uint8_t  dcc_wrlvl_en;
	uint8_t  pi_wdqlvl_vref_en;
	uint8_t  phy_ntp_mult_train;
} mango_setup;

typedef struct{
	mango_setup setup;
	mango_spd_data spd[MANGO_MAX_DIMMS];
	mango_ddr_rank_info rank_info[MANGO_MAX_DIMMS];
	uint32_t dimm_size[MANGO_MAX_DIMMS];
	uint8_t rank_present;
	uint8_t twr;
	uint8_t cl;
	uint8_t cwl;
	uint8_t tccd_s;
	uint8_t trrd_s;
	uint8_t twtr_s;
	uint16_t ddr_freq;
	uint16_t ddr_dfs_low;
	//Normal mode:2666; Fast mode:3200; Safe mode 1600
	uint16_t ddr_cycle; //Unit: 0.001ns
	uint8_t burst_length; //Only set 1: BL8
} ddr_attr;

typedef struct{
	mango_spd_data spd[MANGO_MAX_DIMMS];

} ddr_info_save;

#define DDR_BIT0   0x1
#define DDR_BIT1   0x2
#define DDR_BIT2   0x4
#define DDR_BIT3   0x8
#define DDR_BIT4   0x10
#define DDR_BIT5   0x20
#define DDR_BIT6   0x40
#define DDR_BIT7   0x80
#define DDR_BIT8   0x100
#define DDR_BIT9   0x200
#define DDR_BIT10  0x400
#define DDR_BIT11  0x800
#define DDR_BIT12  0x1000
#define DDR_BIT13  0x2000
#define DDR_BIT14  0x4000
#define DDR_BIT15  0x8000
#define DDR_BIT16  0x10000
#define DDR_BIT17  0x20000
#define DDR_BIT18  0x40000
#define DDR_BIT19  0x80000
#define DDR_BIT20  0x100000
#define DDR_BIT21  0x200000
#define DDR_BIT22  0x400000
#define DDR_BIT23  0x800000
#define DDR_BIT24  0x1000000
#define DDR_BIT25  0x2000000
#define DDR_BIT26  0x4000000
#define DDR_BIT27  0x8000000
#define DDR_BIT28  0x10000000
#define DDR_BIT29  0x20000000
#define DDR_BIT30  0x40000000
#define DDR_BIT31  0x80000000
#define DDR_BIT32  0x100000000

#endif /* MANGO_DDR_H */

