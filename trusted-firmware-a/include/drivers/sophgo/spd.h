#include <string.h>
#include <stdint.h>
#include<stdbool.h>
#include <drivers/sophgo/mango_ddr.h>

#ifndef _SPD_H
#define _SPD_H

#define SLOT0     0x50
#define SLOT1     0x51
#define SLOT2     0x52
#define SLOT3     0x53

#define SPD_BYTE    512
#define SPD_DEVICE	0

#define NOT_READY       1

//DDR4 SPD offset
#define DDR4_SPD_DEVICE_TYPE 2
#define DDR4_SPD_MODULE_TYPE 3
#define DDR4_SPD_DENSITY_BANKS 4
#define DDR4_SPD_ADDRESSING 5
#define DDR4_SPD_PACKAGE_TYPE 6
#define DDR4_SPD_NOMINAL_VOLTAGE 11
#define DDR4_SPD_MODULE_ORG 12
#define DDR4_SPD_BUS_WIDTH 13
#define DDR4_SPD_TIMEBASE 17

#define DDR4_SPD_MIN_CYCLE_TIME 18
#define DDR4_SPD_MAX_CYCLE_TIME 19
#define DDR4_SPD_SUPPORTED_CL_FIRST_BYTE 20
#define DDR4_SPD_SUPPORTED_CL_SECOND_BYTE 21
#define DDR4_SPD_SUPPORTED_CL_THIRD_BYTE 22
#define DDR4_SPD_SUPPORTED_CL_FOURTH_BYTE 23

#define DDR4_SPD_MIN_CL_TIME 24

#define DDR4_SPD_MIN_TRCD 25
#define DDR4_SPD_MIN_TRRD_SHORT 38
#define DDR4_SPD_MIN_TRRD_LONG 39
#define DDR4_SPD_MIN_TCCD_LONG 40

#define DDR4_SPD_MIN_TRP 26
#define DDR4_SPD_UPPER_NIBBLE_TRAS_TRC 27
#define DDR4_SPD_MIN_TRAS_LSB 28
#define DDR4_SPD_MIN_TRC_LSB 29
#define DDR4_SPD_MIN_TRFC1_LSB 30
#define DDR4_SPD_MIN_TRFC1_MSB 31
#define DDR4_SPD_MIN_TRFC2_LSB 32
#define DDR4_SPD_MIN_TRFC2_MSB 33
#define DDR4_SPD_MIN_TRFC3_LSB 34
#define DDR4_SPD_MIN_TRFC3_MSB 35

#define DDR4_SPD_UPPER_NIBBLE_TFAW 36
#define DDR4_SPD_MIN_TFAW 37
#define DDR4_SPD_OPTIONAL_FEATURE 7
#define DDR4_SPD_OPTIONAL_OTHER_FEATURE 9

#define DDR4_SPD_DQ_NIBBLE_MAP0 60
#define DDR4_SPD_DQ_NIBBLE_MAP32 70
#define DDR4_SPD_DQ_NIBBLE_MAPCB0 68
#define DDR4_SPD_DQ_NIBBLE_MAPCB4 69

#define DDR4_SPD_TCCD_LONG_FINE_OFFSET 117
#define DDR4_SPD_TRRD_LONG_FINE_OFFSET 118
#define DDR4_SPD_TRRD_SHORT_FINE_OFFSET 119
#define DDR4_SPD_TRC_FINE_OFFSET 120
#define DDR4_SPD_TRP_FINE_OFFSET 121
#define DDR4_SPD_TRCD_FINE_OFFSET 122
#define DDR4_SPD_CL_FINE_OFFSET 123

#define DDR4_SPD_MIN_CYCLE_TIME_FINE_OFFSET 125
#define DDR4_SPD_MAX_CYCLE_TIME_FINE_OFFSET 124

#define DDR4_SPD_THERMAL_REFRESH 8
#define DDR4_SPD_THERMAL_SENSOR 14

#define DDR4_SPD_REFERENCE_RAW_CARD 130
#define DDR4_UDIMM_SPD_RANK1_ADDRMAPPING 131
#define DDR4_RDIMM_SPD_RANK1_ADDRMAPPING 136
#define DDR4_RDIMM_SPD_RCD_CA_DRIVE 137
#define DDR4_RDIMM_SPD_RCD_CLK_DRIVE 138

#define DDR4_SPD_MODULE_MANUFACTURING_ID_LSB 320
#define DDR4_SPD_MODULE_MANUFACTURING_ID_MSB 321
#define DDR4_SPD_MODULE_MANUFACTURING_LOCATION 322
#define DDR4_SPD_MODULE_MANUFACTURING_YEAR 323
#define DDR4_SPD_MODULE_MANUFACTURING_WEEK 324
#define DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE00 325
#define DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE01 326
#define DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE02 327
#define DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE03 328
#define DDR4_SPD_MODULE_PART_NUMBER_BYTE00 329
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE05			330
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE06			331
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE07			332
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE08			333
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE09			334
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE0A			335
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE0B			336
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE0C			337
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE0D			338
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE0E			339
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE0F			340
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE10			341
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE11			342
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE12			343
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE13			344
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE14			345
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE15			346
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE16			347
//#define DDR4_SPD_MODULE_PART_NUMBER_BYTE17			348
#define DDR4_SPD_DRAM_MANUFACTURING_ID_LSB 350
#define DDR4_SPD_DRAM_MANUFACTURING_ID_MSB 351
#define DDR4_SPD_DRAM_MANUFACTURING_ID_LSB 350
#define DDR4_SPD_DRAM_MANUFACTURING_ID_MSB 351

int read_spd_byte(uint8_t dram_index, uint8_t byte_index, uint8_t *val);
int spd_get_info(uint8_t dram_index, uint16_t length, uint8_t *buf);
int get_spd_data(uint8_t dram_index, ddr_attr *p_dram_attr);

typedef struct spd_ddr4_info {
	int bytes_used;
	int bytes_total;
	unsigned char spd_revision[8];
	unsigned char dev_type[30];
	unsigned char mod_type[30];
	unsigned char sdram_capacity[12];
	int bank_number;
	int bank_group;
	int column_addr;
	int row_addr;
	unsigned char signal_loading[32];
	unsigned char die_count[12];
	unsigned char pack_type[30];
	unsigned char max_act_count[20];
	unsigned char max_act_window[20];
	unsigned char post_package_repair[60];
	unsigned char vdd_12v[30];
	unsigned char vdd_tbd1v[30];
	unsigned char vdd_tbd2v[30];
	int dev_width;
	int ranks_per_dimm;
	int bus_width;
	int bus_width_ext;
	unsigned char thermal_sensor[40];
	int cycle_time_min;
	int cycle_time_max;
	int cas_latencies_support[24];
	int taa_min;
	int trcd_min;
	int trp_min;
	int tras_min;
	int trc_min;
	int trfc1_min;
	int trfc2_min;
	int trfc4_min;
	int tfwa_min;
	int trrds_min;
	int trrdl_min;
	int tccdl_min;
	unsigned char dq[18][48];
	unsigned char crc_125_res[16];
	unsigned char mod_height[24];
	int raw_card_revision;
	unsigned char ref_raw_card[4];
	unsigned char thickness_front[24];
	unsigned char thickness_back[24];
	unsigned char rank_1_mapping[12];
	int num_reg;
	int row_drams;
	unsigned char heat_sp_solution[40];
	int reg_continuation_codes;
	int reg_last_nonzero_byte;
	int reg_revision_num;
	unsigned char reg_output_drive[6][16];
	unsigned char crc_253_res[20];
	int mod_continuation_codes;
	int mod_last_nonzero_byte;
	int mod_manu_location;
	unsigned char mod_manu_date[20];
	unsigned char mod_serial_number[4];
	unsigned char mod_part_number[24];
	int mod_revision_code;
	int dram_continuation_codes;
	int dram_last_nonzero_byte;
	unsigned char dram_stepping[12];
	unsigned char manu_specific_data[29];
} spd_info;

#endif /* _SPD_HS */

