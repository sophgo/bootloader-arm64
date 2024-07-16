#include <sophgo/spd.h>
#include <drivers/bitmain/i2c.h>
#include <common/debug.h>
#define SPD_DEVICE_BL2	0

/**
 * @param index ddr slot index
 * @return 0 success, nagtive number failed
 */

int read_spd_byte(uint8_t dram_index, uint8_t byte_index, uint8_t *val)
{

	uint8_t smbus_addr;
	int status = NOT_READY;

	if (val == NULL)
		return -1;
	*val = 0;

	switch (dram_index)	{
	case 0:
		smbus_addr = SLOT0;
		break;
	case 1:
		smbus_addr = SLOT1;
		break;
	case 2:
		smbus_addr = SLOT2;
		break;
	case 3:
		smbus_addr = SLOT3;
		break;
	default:
		return -1;
	}

	status = i2c_smbus_read_byte(SPD_DEVICE, smbus_addr, byte_index, val);

	return status;
}

/**
 * @param index ddr slot index
 * @return 0 success, nagtive number failed
 */
int spd_get_info(uint8_t dram_index, uint16_t length, uint8_t *buf)
{
	int i;
	uint8_t val;
	int status;

	if (length < 1 || buf == NULL)
		return -1;

	if (length <= 256) {
		i2c_smbus_write_byte(SPD_DEVICE_BL2, 0x36, 0x00, 1);
		for (i = 0; i < length; i++) {
			status = read_spd_byte(dram_index, i, &val);
			if (status != 0)//read byte fail
				return status;
			*(buf + i) = val;
		}
	} else {
		i2c_smbus_write_byte(SPD_DEVICE_BL2, 0x36, 0x00, 1);
		for (i = 0; i < 256; i++) {
			status = read_spd_byte(dram_index, i, &val);
			if (status != 0)//read byte fail
				return status;
			*(buf + i) = val;
		}
		i2c_smbus_write_byte(SPD_DEVICE_BL2, 0x37, 0x00, 1);
		for (i = 0; i < (length - 256); i++) {
			status = read_spd_byte(dram_index, i, &val);
			if (status != 0)//read byte fail
				return status;
			*(buf + 256 + i) = val;
		}
	}
	return 0;
}

int get_spd_data(uint8_t dram_index, ddr_attr *p_dram_attr)
{

	int status;
	uint8_t  i, j;

	status = spd_get_info(dram_index, SPD_SIZE, &p_dram_attr->spd[dram_index].buffer[0]);

	if (status != 0) {
		p_dram_attr->spd[dram_index].spd_present = false;
		return status;
	}
	NOTICE("DIMM %x is OK\n", dram_index);
	p_dram_attr->spd[dram_index].spd_present = true;

	NOTICE("\n");
	NOTICE("SPD For DIMM %x\n", dram_index);
	NOTICE("	00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
	NOTICE(" --+-----------------------------------------------\n");
	for (i = 0; i < 32; i++) {
		if (i * 16 < SPD_SIZE) {
			NOTICE(" %02x|", i * 16);
		for (j = 0; j < 16; j++) {
			if (i * 16 + j < SPD_SIZE)
				NOTICE(" %02x", p_dram_attr->spd[dram_index].buffer[i * 16 + j]);
		}
		if (i * 16 + j < SPD_SIZE)
			NOTICE("\n");
		}
	}
	NOTICE("\n");

	p_dram_attr->spd[dram_index].dev_type = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_DEVICE_TYPE] & 0x0F;
	p_dram_attr->spd[dram_index].ddr_type = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_TYPE] & 0x0F;
	NOTICE("DIMM[%d] module_type : %x\n", dram_index, p_dram_attr->spd[dram_index].ddr_type);
	//01:RDIMM
	p_dram_attr->spd[dram_index].package_type = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_PACKAGE_TYPE] & 0x80) >> 7;
	NOTICE("DIMM[%d] package_type : %x\n", dram_index, p_dram_attr->spd[dram_index].package_type);

	p_dram_attr->spd[dram_index].nominal_voltage[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_NOMINAL_VOLTAGE] & 0x03;
	p_dram_attr->spd[dram_index].nominal_voltage[1] = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_NOMINAL_VOLTAGE] >> 2) & 0x03;
	p_dram_attr->spd[dram_index].nominal_voltage[2] = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_NOMINAL_VOLTAGE] >> 4) & 0x03;
	p_dram_attr->spd[dram_index].bus_width = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_BUS_WIDTH] & 0x07;
	p_dram_attr->spd[dram_index].timebase[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TIMEBASE] & 0x03;
	p_dram_attr->spd[dram_index].timebase[1] = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TIMEBASE] & 0x0c) >> 2;
	p_dram_attr->spd[dram_index].min_cycle_time = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_CYCLE_TIME];
	p_dram_attr->spd[dram_index].max_cycle_time = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MAX_CYCLE_TIME];
	p_dram_attr->spd[dram_index].support_cl_byte[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_SUPPORTED_CL_FIRST_BYTE];
	p_dram_attr->spd[dram_index].support_cl_byte[1] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_SUPPORTED_CL_SECOND_BYTE];
	p_dram_attr->spd[dram_index].support_cl_byte[2] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_SUPPORTED_CL_THIRD_BYTE];
	p_dram_attr->spd[dram_index].support_cl_byte[3] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_SUPPORTED_CL_FOURTH_BYTE];
	p_dram_attr->spd[dram_index].min_cl_time = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_CL_TIME];
	p_dram_attr->spd[dram_index].min_trcd = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRCD];
	p_dram_attr->spd[dram_index].min_trrd_short = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRRD_SHORT];
	p_dram_attr->spd[dram_index].min_trrd_long = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRRD_LONG];
	p_dram_attr->spd[dram_index].min_trp = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRP];
	p_dram_attr->spd[dram_index].upper_nibble_tras_trc = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_UPPER_NIBBLE_TRAS_TRC];
	p_dram_attr->spd[dram_index].min_tras_lsb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRAS_LSB];
	p_dram_attr->spd[dram_index].min_trfc_lsb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRC_LSB];
	p_dram_attr->spd[dram_index].min_trfc1_lsb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRFC1_LSB];
	p_dram_attr->spd[dram_index].min_trfc1_msb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRFC1_MSB];
	p_dram_attr->spd[dram_index].min_trfc2_lsb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRFC2_LSB];
	p_dram_attr->spd[dram_index].min_trfc2_msb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRFC2_MSB];
	p_dram_attr->spd[dram_index].min_trfc3_lsb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRFC3_LSB];
	p_dram_attr->spd[dram_index].min_trfc3_msb = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TRFC3_MSB];
	p_dram_attr->spd[dram_index].min_upper_nibble_tfaw = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_UPPER_NIBBLE_TFAW] & 0x0F;
	p_dram_attr->spd[dram_index].min_tfaw = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TFAW];
	p_dram_attr->spd[dram_index].max_activate_count = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_OPTIONAL_FEATURE] & 0x0F;
	p_dram_attr->spd[dram_index].max_activate_window = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_OPTIONAL_FEATURE] & 0x30) >> 4;
	p_dram_attr->spd[dram_index].post_package_repair = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_TFAW] & 0xc0) >> 6;
	p_dram_attr->spd[dram_index].tccd_long_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TCCD_LONG_FINE_OFFSET];
	p_dram_attr->spd[dram_index].trrd_long_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TRRD_LONG_FINE_OFFSET];
	p_dram_attr->spd[dram_index].trrd_short_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TRRD_SHORT_FINE_OFFSET];
	p_dram_attr->spd[dram_index].trc_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TRC_FINE_OFFSET];
	p_dram_attr->spd[dram_index].trp_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TRP_FINE_OFFSET];
	p_dram_attr->spd[dram_index].trcd_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_TRCD_FINE_OFFSET];
	p_dram_attr->spd[dram_index].cl_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_CL_FINE_OFFSET];
	p_dram_attr->spd[dram_index].min_cycle_time_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MIN_CYCLE_TIME_FINE_OFFSET];
	p_dram_attr->spd[dram_index].max_cycle_time_fine_offset = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MAX_CYCLE_TIME_FINE_OFFSET];
	p_dram_attr->spd[dram_index].thermal_refresh = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_THERMAL_REFRESH];
	p_dram_attr->spd[dram_index].thermal_sensor = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_THERMAL_SENSOR] >> 7;
	p_dram_attr->spd[dram_index].reference_raw_card = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_REFERENCE_RAW_CARD];
	p_dram_attr->spd[dram_index].udimm_rank1_addrmapping = p_dram_attr->spd[dram_index]
								.buffer[DDR4_UDIMM_SPD_RANK1_ADDRMAPPING] & 0x01;
	NOTICE("DIMM[%d] udimm_rank1_addrmapping : %x\n",
	       dram_index, p_dram_attr->spd[dram_index].udimm_rank1_addrmapping);

	p_dram_attr->spd[dram_index].rdimm_rank1_addrmapping = p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RANK1_ADDRMAPPING] & 0x01;
	NOTICE("DIMM[%d] rdimm_rank1_addrmapping : %x\n",
	       dram_index, p_dram_attr->spd[dram_index].rdimm_rank1_addrmapping);

	p_dram_attr->spd[dram_index].rcd_ca_drive[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RCD_CA_DRIVE] & 0x3;
	p_dram_attr->spd[dram_index].rcd_ca_drive[1] = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RCD_CA_DRIVE] >> 2) & 0x03;
	p_dram_attr->spd[dram_index].rcd_ca_drive[2] = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RCD_CA_DRIVE] >> 4) & 0x03;
	p_dram_attr->spd[dram_index].rcd_ca_drive[3] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RCD_CA_DRIVE] >> 6;
	p_dram_attr->spd[dram_index].rcd_clk_drive[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RCD_CLK_DRIVE] & 0x03;
	p_dram_attr->spd[dram_index].rcd_clk_drive[1] = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_RDIMM_SPD_RCD_CLK_DRIVE] >> 2) & 0x03;
	p_dram_attr->spd[dram_index].MANUFACTURING_INFO[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_MANUFACTURING_ID_LSB];
	p_dram_attr->spd[dram_index].MANUFACTURING_INFO[1] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_MANUFACTURING_ID_MSB];
	p_dram_attr->spd[dram_index].MANUFACTURING_INFO[2] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_MANUFACTURING_LOCATION];
	p_dram_attr->spd[dram_index].MANUFACTURING_INFO[3] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_MANUFACTURING_YEAR];
	p_dram_attr->spd[dram_index].MANUFACTURING_INFO[4] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_MANUFACTURING_WEEK];
	p_dram_attr->spd[dram_index].DDR4_SERIAL_NUMBER[0] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE00];
	p_dram_attr->spd[dram_index].DDR4_SERIAL_NUMBER[1] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE01];
	p_dram_attr->spd[dram_index].DDR4_SERIAL_NUMBER[2] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE02];
	p_dram_attr->spd[dram_index].DDR4_SERIAL_NUMBER[3] = p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_SERIAL_NUMBER_BYTE03];
	p_dram_attr->rank_info[dram_index].rank_num = ((p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_MODULE_ORG] & 0x38) >> 3) + 1;
	NOTICE("DIMM[%d] rank pre dimm : %d\n", dram_index, p_dram_attr->rank_info[dram_index].rank_num);
	if (p_dram_attr->rank_info[dram_index].rank_num == 1) {
		p_dram_attr->setup.wrlvl_map = 0x1;
		p_dram_attr->setup.gate_map = 0x1;
		p_dram_attr->setup.wdq_map = 0x1;
	} else if (p_dram_attr->rank_info[dram_index].rank_num == 2) {
		p_dram_attr->setup.wrlvl_map = 0x3;
		p_dram_attr->setup.gate_map = 0x3;
		p_dram_attr->setup.wdq_map = 0x3;
	}

	p_dram_attr->rank_info[dram_index].BG_num = ((p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_DENSITY_BANKS] >> 6) & 0x03);
	NOTICE("DIMM[%d] BG_num : %d\n", dram_index, p_dram_attr->rank_info[dram_index].BG_num);

	p_dram_attr->rank_info[dram_index].bank_num = ((p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_DENSITY_BANKS] >> 4) & 0x03) + 2;
	NOTICE("DIMM[%d] bank_num : %d\n", dram_index, p_dram_attr->rank_info[dram_index].bank_num);

	p_dram_attr->rank_info[dram_index].row_num = ((p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_ADDRESSING] >> 3) & 0x07) + 12;
	NOTICE("DIMM[%d] row_num : %d\n", dram_index, p_dram_attr->rank_info[dram_index].row_num);

	p_dram_attr->rank_info[dram_index].col_num = (p_dram_attr->spd[dram_index]
								.buffer[DDR4_SPD_ADDRESSING]  & 0x07) + 9;
	NOTICE("DIMM[%d]col_num : %d\n", dram_index, p_dram_attr->rank_info[dram_index].col_num);

	return status;
}

