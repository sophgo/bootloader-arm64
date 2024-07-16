#include <drivers/sophgo/mango_ddr.h>
#include <stdint.h>
#include <string.h>
#include <platform_def.h>
#include <drivers/delay_timer.h>
#include <common/debug.h>
#include <lib/mmio.h>
#include <lib/cli.h>
#include <platform_def.h>
#include <drivers/sophgo/mango_ddr_ctl.h>
#include <drivers/sophgo/mango_ddr_phy.h>
#include <drivers/sophgo/mango_ddr_pi.h>
#include <drivers/sophgo/mango_ddr_register.h>
#include <drivers/sophgo/spd.h>

#define Rshift(ope, num) ((uint64_t)(ope) >> (num))
#define Lshift(ope, num) ((uint64_t)(ope) << (num))

//#define DDR_APP_NO_USE

enum reg_type {ctl, phy, pi};

static void mmio_modify_32(uint64_t address, uint32_t mask, uint32_t value)
{
	uint32_t data32 = mmio_read_32(address);

	data32 = ((data32 & (~mask)) | value);
	mmio_write_32(address, data32);

}

static uint32_t shift_to_mask_bit(uint32_t mask_bit, uint32_t shift_data)
{
	uint32_t value, index, buffer = 0;

	for (index = 0; index < 32; index++) {
		buffer = mask_bit;
		if ((buffer >> index) & 0x01)
			break;
	}
	value = shift_data << index;
	return value;
}

static uint64_t mango_ddr_cfg_address(uint8_t dram_index, uint8_t reg_type, uint64_t reg_index)
{
	uint64_t   address = 0;
	uint64_t   dram_ctl_base = 0;
	uint64_t   dram_phy_base = 0;
	uint64_t   dram_pi_base = 0;

	switch (dram_index) {
	case 0:
		dram_ctl_base = DDR0_CFG_BASE + DDR_CTL_BASE_ADDR;
		dram_phy_base = DDR0_CFG_BASE + DDR_PHY_BASE_ADDR;
		dram_pi_base = DDR0_CFG_BASE + DDR_PI_BASE_ADDR;
		break;
	case 1:
		dram_ctl_base = DDR1_CFG_BASE + DDR_CTL_BASE_ADDR;
		dram_phy_base = DDR1_CFG_BASE + DDR_PHY_BASE_ADDR;
		dram_pi_base = DDR1_CFG_BASE + DDR_PI_BASE_ADDR;
		break;
	case 2:
		dram_ctl_base = DDR2_CFG_BASE + DDR_CTL_BASE_ADDR;
		dram_phy_base = DDR2_CFG_BASE + DDR_PHY_BASE_ADDR;
		dram_pi_base = DDR2_CFG_BASE + DDR_PI_BASE_ADDR;
		break;
	case 3:
		dram_ctl_base = DDR3_CFG_BASE + DDR_CTL_BASE_ADDR;
		dram_phy_base = DDR3_CFG_BASE + DDR_PHY_BASE_ADDR;
		dram_pi_base = DDR3_CFG_BASE + DDR_PI_BASE_ADDR;
		break;
	default:
		break;
	}

	switch (reg_type) {
	case ctl:
		address = address + dram_ctl_base + reg_index;
		break;
	case phy:
		address = address + dram_phy_base + reg_index;
		break;
	case pi:
		address = address + dram_pi_base + reg_index;
		break;
	default:
		break;
	}

	return address;

}

static void dump_dram_ctl_regiters(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint32_t data;
	uint16_t index1, index2;

	printf("dump CTL port address:\n");
	printf("	 00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
	printf("---+---------------------------------------------------------------\n");
	for (index1 = 0; index1 < 0x70; index1++) {
		printf("%03x|", index1 * 16);
		for (index2 = 0; index2 < 0x10; index2++) {
			address = mango_ddr_cfg_address(dram_index, ctl, index1 * 16 + index2);
			data = mmio_read_8(address);
			printf(" %02x ", data);
			if (index2 == 0x0F)
				printf("\n");
		}
		if ((index1 % 0x10) == 0x0F)
			printf("-------------------------------------------------------------------\n");
	}

	printf("\n");
}

static void dump_dram_phy_regiters(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint32_t data;
	uint16_t index1, index2;

	printf("dump PHY port address:\n");
	printf("	 00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
	printf("---+---------------------------------------------------------------\n");
	for (index1 = 0; index1 < 0x270; index1++) {
		printf("%03x|", index1 * 16);
		for (index2 = 0; index2 < 0x10; index2++) {
			address = mango_ddr_cfg_address(dram_index, phy, index1 * 16 + index2);
			data = mmio_read_8(address);
			printf("%02x", data);
			if (index2 == 0x0F)
				printf("\n");
		}
		if ((index1 % 0x10) == 0x0F)
			printf("-------------------------------------------------------------------\n");
	}

	printf("\n");
}

static void dump_dram_pi_regiters(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint32_t data;
	uint16_t index1, index2;

	printf("dump PI port address:\n");
	printf("	 00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
	printf("---+---------------------------------------------------------------\n");
	for (index1 = 0; index1 < 0x35; index1++) {
		printf("%03x|", index1 * 16);
		for (index2 = 0; index2 < 0x10; index2++) {
			address = mango_ddr_cfg_address(dram_index, pi, index1 * 16 + index2);
			data = mmio_read_8(address);
			printf("%02x", data);
			if (index2 == 0x0F)
				printf("\n");
		}
		if ((index1 % 0x10) == 0x0F)
			printf("-------------------------------------------------------------------\n");
	}

	printf("\n");
}

static uint32_t set_dram_configraton(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint64_t rank_size;
	uint32_t dimm_size;

	//DDR type detect
	if (p_dram_attr->spd[dram_index].dev_type == 0xC) {
		NOTICE("DIMM %d is DDR4\n", dram_index);
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_0_DATA);
		mmio_modify_32(address, DRAM_CLASS_RW_8_4, shift_to_mask_bit(DRAM_CLASS_RW_8_4, 0xA));
	} else {
		NOTICE("DIMM %d is DDR3\n", dram_index);
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_0_DATA);
		mmio_modify_32(address, DRAM_CLASS_RW_8_4, shift_to_mask_bit(DRAM_CLASS_RW_8_4, 0x6));
	}

	if (p_dram_attr->spd[dram_index].rank_num == 1)
		p_dram_attr->rank_present |= 0x1 << (dram_index * 2);
	else
		p_dram_attr->rank_present |= 0x3 << (dram_index * 2);

	//CS MAP  CTL + PI regiter
	if (p_dram_attr->rank_info[dram_index].rank_num == 1) {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_248_DATA);
		mmio_modify_32(address, CS_MAP_RW_16_2, shift_to_mask_bit(CS_MAP_RW_16_2, 0x1));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_12_DATA);
		mmio_modify_32(address, PI_CS_MAP_RW_D_16_2, shift_to_mask_bit(PI_CS_MAP_RW_D_16_2, 0x1));
	} else if (p_dram_attr->rank_info[dram_index].rank_num == 2) {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_248_DATA);
		mmio_modify_32(address, CS_MAP_RW_16_2,
			       shift_to_mask_bit(CS_MAP_RW_16_2, 0x3));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_12_DATA);
		mmio_modify_32(address, PI_CS_MAP_RW_D_16_2, shift_to_mask_bit(PI_CS_MAP_RW_D_16_2, 0x3));
	}

	//cal rank size
	rank_size = Lshift(1, (p_dram_attr->rank_info[dram_index].BG_num +
				p_dram_attr->rank_info[dram_index].bank_num +
				p_dram_attr->rank_info[dram_index].row_num +
				p_dram_attr->rank_info[dram_index].col_num + 3));

	p_dram_attr->rank_info[dram_index].rank_size = Rshift(rank_size, 20); //unit of MB
	NOTICE("DIMM %d rank_size = %d M\n", dram_index, p_dram_attr->rank_info[dram_index].rank_size);

	//set dimm size 5=32G 6=16G
	dimm_size =  Rshift(rank_size, 30) * p_dram_attr->rank_info[dram_index].rank_num;
	switch (dimm_size) {
	case 32:
		NOTICE("DIMM %d size = %d G\n", dram_index, dimm_size);
		mmio_setbits_32(SYS_CTRL_BASE + REG_TOP_DDR_SIZE_REG, 0x5 << (dram_index * 8));
		break;
	case 16:
		NOTICE("DIMM %d size = %d G\n", dram_index, dimm_size);
		mmio_setbits_32(SYS_CTRL_BASE + REG_TOP_DDR_SIZE_REG, 0x6 << (dram_index * 8));
		break;
	}
	mmio_setbits_32(SYS_CTRL_BASE + REG_TOP_DDR_SIZE_REG, 0x5 << (dram_index * 8));

	//ECC enable
	if (p_dram_attr->setup.ecc == ECC_EN) {
		if (p_dram_attr->spd[dram_index].ecc_support == ECC_EN) {

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_195_DATA);
			mmio_modify_32(address, ECC_ENABLE_RW_16_2, shift_to_mask_bit(ECC_ENABLE_RW_16_2, 0x03));
			//0x3  enable ECC with both error detection and error correction
			address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_69_DATA);
			mmio_modify_32(address, PI_ECC_EN_RW_24_1, shift_to_mask_bit(PI_ECC_EN_RW_24_1, 0x1));

			//address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_197_DATA);
			//mmio_modify_32(address, ECC_DISABLE_W_UC_ERR_RW_8_1,
			//shift_to_mask_bit(ECC_DISABLE_W_UC_ERR_RW_8_1, 0x01));
			//Set to 1 to disable corruption.
		}
	} else {
		NOTICE("ECC: One of the dimms doesn't support ECC.\n");
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_195_DATA);
		mmio_modify_32(address, ECC_ENABLE_RW_16_2, shift_to_mask_bit(ECC_ENABLE_RW_16_2, 0));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_69_DATA);
		mmio_modify_32(address, PI_ECC_EN_RW_24_1, shift_to_mask_bit(PI_ECC_EN_RW_24_1, 0));
		//0x3  enable ECC with both error detection and error correction
	}

	//RCD enable
	if (p_dram_attr->spd[dram_index].ddr_type == RDIMM) {
		NOTICE("DIMM %d is RDIMM.\n", dram_index);
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_37_DATA);
		mmio_modify_32(address, REG_DIMM_ENABLE_RW_8_1, shift_to_mask_bit(REG_DIMM_ENABLE_RW_8_1, 0x1));
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_67_DATA);
		mmio_modify_32(address, PI_REG_DIMM_ENABLE_RW_24_1, shift_to_mask_bit(PI_REG_DIMM_ENABLE_RW_24_1, 0x1));
	} else {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_37_DATA);
		mmio_modify_32(address, REG_DIMM_ENABLE_RW_8_1, shift_to_mask_bit(REG_DIMM_ENABLE_RW_8_1, 0));
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_67_DATA);
		mmio_modify_32(address, PI_REG_DIMM_ENABLE_RW_24_1, shift_to_mask_bit(PI_REG_DIMM_ENABLE_RW_24_1, 0x0));
	}

	// DFS enable
	if (p_dram_attr->setup.dfs == DFS_EN) {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_135_DATA);
		mmio_modify_32(address, DFS_ENABLE_RW_24_1, shift_to_mask_bit(DFS_ENABLE_RW_24_1, 0x1));
		NOTICE("ddr DFS enable!\n");
	} else {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_135_DATA);
		mmio_modify_32(address, DFS_ENABLE_RW_24_1, shift_to_mask_bit(DFS_ENABLE_RW_24_1, 0));
		NOTICE("ddr DFS disable!\n");
	}

	//set pin swap
	switch (dram_index)	{
	case 0:
		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_107_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_0_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_0_RW_0_32, 0x40516327));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_363_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_1_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_1_RW_0_32, 0x45610327));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_619_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_2_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_2_RW_0_32, 0x45103726));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_875_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_3_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_3_RW_0_32, 0x45016732));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1131_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_4_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_4_RW_0_32, 0x27360451));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1387_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_5_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x62731405));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1643_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_6_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x37240516));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1899_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_7_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_7_RW_0_32, 0x72634105));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2155_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_8_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_8_RW_0_32, 0x72631054));
		break;
	case 1:
		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_107_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_0_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_0_RW_0_32, 0x41506273));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_363_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_1_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_1_RW_0_32, 0x45103672));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_619_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_2_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_2_RW_0_32, 0x41052637));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_875_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_3_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_3_RW_0_32, 0x45106273));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1131_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_4_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_4_RW_0_32, 0x63270145));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1387_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_5_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x63207154));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1643_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_6_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x23605417));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1899_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_7_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_7_RW_0_32, 0x62031574));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2155_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_8_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_8_RW_0_32, 0x26743051));
		break;
	case 2:
		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_107_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_0_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_0_RW_0_32, 0x51406327));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_363_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_1_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_1_RW_0_32, 0x45710326));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_619_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_2_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_2_RW_0_32, 0x54013726));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_875_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_3_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_3_RW_0_32, 0x45017632));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1131_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_4_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_4_RW_0_32, 0x27361540));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1387_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_5_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x73621405));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1643_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_6_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x37241506));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1899_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_7_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_7_RW_0_32, 0x63724105));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2155_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_8_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_8_RW_0_32, 0x72630145));
		break;
	case 3:
		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_107_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_0_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_0_RW_0_32, 0x50416273));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_363_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_1_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_1_RW_0_32, 0x45103762));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_619_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_2_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_2_RW_0_32, 0x50142637));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_875_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_3_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_3_RW_0_32, 0x45107263));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1131_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_4_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_4_RW_0_32, 0x63271045));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1387_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_5_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x72316054));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1643_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_6_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x23615407));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1899_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_7_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_7_RW_0_32, 0x72130465));

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2155_DATA);
		mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_8_RW_0_32,
			       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_8_RW_0_32, 0x26743150));
		break;
	default:
		break;
	}

	//set cmd pin swap
	switch (dram_index) {
	case 0:
	case 2:
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_174_DATA);
		mmio_modify_32(address, PI_RESET_N_MUX_0_RW_D_16_5, shift_to_mask_bit(PI_RESET_N_MUX_0_RW_D_16_5, 0xE));
		mmio_modify_32(address, PI_ODT_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_ODT_MUX_1_RW_D_8_5, 0x4));
		mmio_modify_32(address, PI_ODT_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_ODT_MUX_0_RW_D_0_5, 0x7));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_173_DATA);
		mmio_modify_32(address, PI_CS_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_CS_MUX_1_RW_D_8_5, 0x3));
		mmio_modify_32(address, PI_CS_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_CS_MUX_0_RW_D_0_5, 0xD));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_172_DATA);
		mmio_modify_32(address, PI_CKE_MUX_0_RW_D_16_5, shift_to_mask_bit(PI_CKE_MUX_0_RW_D_16_5, 0x2));
		mmio_modify_32(address, PI_CKE_MUX_1_RW_D_24_5, shift_to_mask_bit(PI_CKE_MUX_1_RW_D_24_5, 0x8));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_87_DATA);
		mmio_modify_32(address, PI_PARITY_IN_MUX_RW_D_16_5, shift_to_mask_bit(PI_PARITY_IN_MUX_RW_D_16_5, 0x0));
		mmio_modify_32(address, PI_CMD_SWAP_EN_RW_D_8_1, shift_to_mask_bit(PI_CMD_SWAP_EN_RW_D_8_1, 0x1));
		//enable cmd swap

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_88_DATA);
		mmio_modify_32(address, PI_WE_N_MUX_RW_D_24_5, shift_to_mask_bit(PI_WE_N_MUX_RW_D_24_5, 0x5));
		mmio_modify_32(address, PI_CAS_N_MUX_RW_D_16_5, shift_to_mask_bit(PI_CAS_N_MUX_RW_D_16_5, 0xC));
		mmio_modify_32(address, PI_RAS_N_MUX_RW_D_8_5, shift_to_mask_bit(PI_RAS_N_MUX_RW_D_8_5, 0x9));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_89_DATA);
		mmio_modify_32(address, PI_BANK_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_BANK_MUX_1_RW_D_8_5, 0xF));
		mmio_modify_32(address, PI_BANK_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_BANK_MUX_0_RW_D_0_5, 0x10));
		break;
	case 1:
	case 3:
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_174_DATA);
		mmio_modify_32(address, PI_RESET_N_MUX_0_RW_D_16_5, shift_to_mask_bit(PI_RESET_N_MUX_0_RW_D_16_5, 0x0));
		mmio_modify_32(address, PI_ODT_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_ODT_MUX_1_RW_D_8_5, 0x9));
		mmio_modify_32(address, PI_ODT_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_ODT_MUX_0_RW_D_0_5, 0x4));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_173_DATA);
		mmio_modify_32(address, PI_CS_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_CS_MUX_1_RW_D_8_5, 0xC));
		mmio_modify_32(address, PI_CS_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_CS_MUX_0_RW_D_0_5, 0x10));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_172_DATA);
		mmio_modify_32(address, PI_CKE_MUX_0_RW_D_16_5, shift_to_mask_bit(PI_CKE_MUX_0_RW_D_16_5, 0xF));
		mmio_modify_32(address, PI_CKE_MUX_1_RW_D_24_5, shift_to_mask_bit(PI_CKE_MUX_1_RW_D_24_5, 0x5));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_87_DATA);
		mmio_modify_32(address, PI_PARITY_IN_MUX_RW_D_16_5, shift_to_mask_bit(PI_PARITY_IN_MUX_RW_D_16_5, 0xE));
		mmio_modify_32(address, PI_CMD_SWAP_EN_RW_D_8_1, shift_to_mask_bit(PI_CMD_SWAP_EN_RW_D_8_1, 0x1));
		//enable cmd swap

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_88_DATA);
		mmio_modify_32(address, PI_WE_N_MUX_RW_D_24_5, shift_to_mask_bit(PI_WE_N_MUX_RW_D_24_5, 0x2));
		mmio_modify_32(address, PI_CAS_N_MUX_RW_D_16_5, shift_to_mask_bit(PI_CAS_N_MUX_RW_D_16_5, 0x8));
		mmio_modify_32(address, PI_RAS_N_MUX_RW_D_8_5, shift_to_mask_bit(PI_RAS_N_MUX_RW_D_8_5, 0x9));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_89_DATA);
		mmio_modify_32(address, PI_BANK_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_BANK_MUX_1_RW_D_8_5, 0x3));
		mmio_modify_32(address, PI_BANK_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_BANK_MUX_0_RW_D_0_5, 0xD));
		break;
	default:
		break;
	}

#ifdef a53_master_mode
	//XMR_PIN_SWAP
	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_107_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_0_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_0_RW_0_32, 0x40516723));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_363_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_1_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_1_RW_0_32, 0x04156732));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_619_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_2_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_2_RW_0_32, 0x01745326));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_875_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_3_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_3_RW_0_32, 0x70145236));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1131_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_4_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_4_RW_0_32, 0x73265140));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1387_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_5_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x32670145));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1643_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_6_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_6_RW_0_32, 0x62750413));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_1899_DATA);
	mmio_modify_32(address, PHY_DQ_DM_SWIZZLE0_7_RW_0_32,
		       shift_to_mask_bit(PHY_DQ_DM_SWIZZLE0_7_RW_0_32, 0x02635147));

	//XMR_cmd_swap
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_174_DATA);
	mmio_modify_32(address, PI_RESET_N_MUX_0_RW_D_16_5, shift_to_mask_bit(PI_RESET_N_MUX_0_RW_D_16_5, 0x0));
	mmio_modify_32(address, PI_ODT_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_ODT_MUX_1_RW_D_8_5, 0x4));
	mmio_modify_32(address, PI_ODT_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_ODT_MUX_0_RW_D_0_5, 0x5));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_173_DATA);
	mmio_modify_32(address, PI_CS_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_CS_MUX_1_RW_D_8_5, 0xC));
	mmio_modify_32(address, PI_CS_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_CS_MUX_0_RW_D_0_5, 0xF));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_172_DATA);
	mmio_modify_32(address, PI_CKE_MUX_0_RW_D_16_5, shift_to_mask_bit(PI_CKE_MUX_0_RW_D_16_5, 0x10));
	mmio_modify_32(address, PI_CKE_MUX_1_RW_D_24_5, shift_to_mask_bit(PI_CKE_MUX_1_RW_D_24_5, 0x7));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_87_DATA);
	mmio_modify_32(address, PI_PARITY_IN_MUX_RW_D_16_5, shift_to_mask_bit(PI_PARITY_IN_MUX_RW_D_16_5, 0x3));
	mmio_modify_32(address, PI_CMD_SWAP_EN_RW_D_8_1, shift_to_mask_bit(PI_CMD_SWAP_EN_RW_D_8_1, 0x1));
	//enable cmd swap

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_88_DATA);
	mmio_modify_32(address, PI_WE_N_MUX_RW_D_24_5, shift_to_mask_bit(PI_WE_N_MUX_RW_D_24_5, 0xE));
	mmio_modify_32(address, PI_CAS_N_MUX_RW_D_16_5, shift_to_mask_bit(PI_CAS_N_MUX_RW_D_16_5, 0x2));
	mmio_modify_32(address, PI_RAS_N_MUX_RW_D_8_5, shift_to_mask_bit(PI_RAS_N_MUX_RW_D_8_5, 0xD));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_89_DATA);
	mmio_modify_32(address, PI_BANK_MUX_1_RW_D_8_5, shift_to_mask_bit(PI_BANK_MUX_1_RW_D_8_5, 0x8));
	mmio_modify_32(address, PI_BANK_MUX_0_RW_D_0_5, shift_to_mask_bit(PI_BANK_MUX_0_RW_D_0_5, 0x9));
#endif
	//ODT MAP
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_305_DATA);
	mmio_modify_32(address, ODT_WR_MAP_CS1_RW_24_2, shift_to_mask_bit(ODT_WR_MAP_CS1_RW_24_2, 0x1));
	mmio_modify_32(address, ODT_RD_MAP_CS1_RW_16_2, shift_to_mask_bit(ODT_RD_MAP_CS1_RW_16_2, 0x0));
	mmio_modify_32(address, ODT_WR_MAP_CS0_RW_8_2, shift_to_mask_bit(ODT_WR_MAP_CS0_RW_8_2, 0x2));
	mmio_modify_32(address, ODT_RD_MAP_CS0_RW_0_2, shift_to_mask_bit(ODT_RD_MAP_CS0_RW_0_2, 0x0));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_151_DATA);
	mmio_modify_32(address, PI_ODT_WR_MAP_CS0_RW_24_2, shift_to_mask_bit(PI_ODT_WR_MAP_CS0_RW_24_2, 0x2));
	mmio_modify_32(address, PI_ODT_RD_MAP_CS0_RW_16_2, shift_to_mask_bit(PI_ODT_RD_MAP_CS0_RW_16_2, 0x0));

	address = mango_ddr_cfg_address(dram_index, pi,  DENALI_PI_152_DATA);
	mmio_modify_32(address, PI_ODT_WR_MAP_CS1_RW_8_2, shift_to_mask_bit(PI_ODT_WR_MAP_CS1_RW_8_2, 0x1));
	mmio_modify_32(address, PI_ODT_RD_MAP_CS1_RW_0_2, shift_to_mask_bit(PI_ODT_RD_MAP_CS1_RW_0_2, 0x0));

	//address mirror
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_37_DATA);
	mmio_modify_32(address, ADDRESS_MIRRORING_RW_16_2, shift_to_mask_bit(ADDRESS_MIRRORING_RW_16_2, 0x2));

	return 0;
}

#ifdef DDR_APP_NO_USE
static uint32_t check_lock_status(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t lck_0, lck_1;
	uint64_t ready_0, ready_1;
	uint64_t address;

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2336_DATA);
	lck_0 =  mmio_read_32(address) & DDR_BIT0;

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2338_DATA);
	lck_1 =  mmio_read_32(address) & DDR_BIT0;

	if ((lck_0 != 1) || (lck_1 != 1)) {

		NOTICE("De-Skew PLL failed to lock\n");
		NOTICE("lck_0 = %lx", lck_0);
		NOTICE("lck_1 = %lx", lck_1);
		return -1;
	}

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2336_DATA);
	ready_0 =  mmio_read_32(address) & DDR_BIT1;

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2338_DATA);
	ready_1 =  mmio_read_32(address) & DDR_BIT1;

	if ((ready_0 != 1) || (ready_1 != 1)) {

		NOTICE("De-Skew PLL failed to lock\n");
		NOTICE("ready_0 = %lx", ready_0);
		NOTICE("ready_1 = %lx", ready_1);
		return -1;
	}

	NOTICE("De-Skew PLL locked and ready\n");
	return 0;
}
#endif

static uint32_t dram_frequency_set(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint32_t fbdiv, postdiv2, postdiv1, refdiv;
	uint32_t reg_val;
	uint16_t ctrl_offset;
	uint8_t enable_bit = 0;
	uint16_t pll_lock, pll_en;
	// choose PLL
	if (dram_index == 0) { //pll 0 - ddr0 ddr1
		enable_bit = BIT_UPDATING_DPLL0_VAL;
		ctrl_offset = REG_TOP_DPLL0_CTRL;
		pll_lock = BIT_DPLL0_LOCK;
		pll_en = BIT_DPLL0_CLK_EN;
	} else if (dram_index == 2) { //pll 1 - ddr2 ddr3
		enable_bit = BIT_UPDATING_DPLL1_VAL;
		ctrl_offset = REG_TOP_DPLL1_CTRL;
		pll_lock = BIT_DPLL1_LOCK;
		pll_en = BIT_DPLL1_CLK_EN;
	} else {
		return 0;
	}

	// disable PLL
	mmio_clrbits_32(SYS_CTRL_BASE + REG_TOP_PLL_EN_CTRL, 1 << enable_bit);

	// update PLL
	// pll_freq = refclk * fbdiv / refdiv / (postdiv1 * postdiv2), where refclk is fixed to 25MHz.
	postdiv1 = 1;
	postdiv2 = 1;
	refdiv = 1;
	fbdiv = (p_dram_attr->ddr_freq / 2) * postdiv1 * postdiv2 * refdiv / 25;
	reg_val = (refdiv & 0x3F) |
		((postdiv1 & 0x7) << 8) |
		((postdiv2 & 0x7) << 12) |
		((fbdiv & 0xFFF) << 16);
	NOTICE("reg_val = %x\n", reg_val);
	mmio_write_32(SYS_CTRL_BASE + ctrl_offset, reg_val);

	// wait PLL lock
	reg_val = mmio_read_32(SYS_CTRL_BASE + REG_TOP_PLL_START);
	while (!((reg_val >> pll_lock)) & 0x1)
		reg_val = mmio_read_32(SYS_CTRL_BASE + REG_TOP_PLL_START);

	// wait PLL update
	reg_val = mmio_read_32(SYS_CTRL_BASE + REG_TOP_PLL_START);
	while ((reg_val >> enable_bit) & 0x1)
		reg_val = mmio_read_32(SYS_CTRL_BASE + REG_TOP_PLL_START);

	// enable PLL
	mmio_setbits_32(SYS_CTRL_BASE + REG_TOP_PLL_EN_CTRL, 1 << pll_en);

	return 0;

}

static uint32_t set_ddr_reset(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint32_t reg_val;
	uint32_t BitIndex;
	//Software Reset Register 1 (0x7030013004)
	//9	   RW		  0x1		 Software Reset for ddr3 (Active Low)
	//8	   RW		  0x1		 Software Reset for ddr2 (Active Low)
	//7	   RW		  0x1		 Software Reset for ddr1 (Active Low)
	//6	   RW		  0x1		 Software Reset for ddr0 (Active Low)

	reg_val = mmio_read_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1);
	switch (dram_index) {
	case 0:
		BitIndex = 1 << 6;
		reg_val &= ~BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	case 1:
		BitIndex = 1 << 7;
		reg_val &= ~BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	case 2:
		BitIndex = 1 << 8;
		reg_val &= ~BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	case 3:
		BitIndex = 1 << 9;
		reg_val &= ~BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	default:
		BitIndex = 1 << 6;
		reg_val &= ~BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	}

	//Deassert DDR reset
	switch (dram_index) {
	case 0:
		BitIndex = 1 << 6;
		reg_val &= BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	case 1:
		BitIndex = 1 << 7;
		reg_val &= BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	case 2:
		BitIndex = 1 << 8;
		reg_val &= BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	case 3:
		BitIndex = 1 << 9;
		reg_val &= BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	default:
		BitIndex = 1 << 6;
		reg_val &= BitIndex;
		mmio_write_32(SYS_CTRL_BASE + REG_TOP_SOFT_RST1, reg_val);
		break;
	}

	return 0;
}

static uint32_t dram_init_table(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	int reg_index;
	uint32_t wdata;
	uint64_t address;

	for (reg_index = 0; reg_index <= 430; reg_index++) {
		wdata = ctl_registers[reg_index];
		address = mango_ddr_cfg_address(dram_index, ctl, reg_index * 4);
		mmio_write_32(address, wdata);
	}
	NOTICE("CTL register config done!\n");

	for (reg_index = 0; reg_index <= 203; reg_index++) {
		wdata = pi_registers[reg_index];
		address = mango_ddr_cfg_address(dram_index, pi, reg_index * 4);
		mmio_write_32(address, wdata);
	}
	NOTICE("PHY register config done!\n");
	for (reg_index = 0; reg_index <= 2449; reg_index++) {
		wdata = phy_registers[reg_index];
		address = mango_ddr_cfg_address(dram_index, phy, reg_index * 4);
		mmio_write_32(address, wdata);
	}
	NOTICE("PI register config done!\n");

	udelay(10);
	return 0;
}

#ifdef DDR_APP_NO_USE
static void dram_timing_rcd(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint32_t rdimm_tmrc;
	uint32_t rdimm_tmrd;
	uint32_t rdimm_tmrd_l, rdimm_tmrd_l2;
	uint32_t rdimm_tstab_fN = 0;

	if (p_dram_attr->spd[dram_index].ddr_type == RDIMM) {
		switch (p_dram_attr->ddr_freq) {
		case DRAM_FREQ_3200:
			rdimm_tmrc = 0x10;
			rdimm_tmrd = 0x8;
			rdimm_tmrd_l = 0x10;
			rdimm_tmrd_l2 = 0x20;
			rdimm_tstab_fN = 0x1f40;
			break;
		case DRAM_FREQ_2666:
			rdimm_tmrc = 0x10;
			rdimm_tmrd = 0x8;
			rdimm_tmrd_l = 0x10;
			rdimm_tmrd_l2 = 0x20;
			rdimm_tstab_fN = 0x1a0b;
			break;
		case DRAM_FREQ_1600:
			rdimm_tmrc = 0x10;
			rdimm_tmrd = 0x8;
			rdimm_tmrd_l = 0x10;
			rdimm_tmrd_l2 = 0x20;
			rdimm_tstab_fN = 0xfa0;
			break;
		default:
			break;
		}

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_70_DATA);
		mmio_modify_32(address, RDIMM_TMRC_RW_0_5, shift_to_mask_bit(RDIMM_TMRC_RW_0_5, rdimm_tmrc));

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_41_DATA);
		mmio_modify_32(address, RDIMM_TMRD_RW_24_8, shift_to_mask_bit(RDIMM_TMRD_RW_24_8, rdimm_tmrd));

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_69_DATA);
		mmio_modify_32(address, RDIMM_TMRD_L_RW_16_5, shift_to_mask_bit(RDIMM_TMRD_L_RW_16_5, rdimm_tmrd_l));
		mmio_modify_32(address, RDIMM_TMRD_L2_RW_24_6, shift_to_mask_bit(RDIMM_TMRD_L2_RW_24_6, rdimm_tmrd_l2));

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_66_DATA);
		mmio_modify_32(address, RDIMM_TSTAB_F0_RW_8_24,
			       shift_to_mask_bit(RDIMM_TSTAB_F0_RW_8_24, rdimm_tstab_fN));
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_67_DATA);
		mmio_modify_32(address, RDIMM_TSTAB_F1_RW_0_24,
			       shift_to_mask_bit(RDIMM_TSTAB_F1_RW_0_24, rdimm_tstab_fN));
	}

}

static void dram_timing_cl(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint32_t cl_support, mask;
	uint16_t tmp = 0;
	int8_t fine_offset = 0;
	uint8_t index;

	cl_support = ((p_dram_attr->spd[dram_index].support_cl_byte[3] << 24) |
			(p_dram_attr->spd[dram_index].support_cl_byte[2]) << 16 |
			(p_dram_attr->spd[dram_index].support_cl_byte[1]) << 8 |
			(p_dram_attr->spd[dram_index].support_cl_byte[0]));

	if (p_dram_attr->spd[dram_index].min_cl_time > tmp) {
		tmp = p_dram_attr->spd[dram_index].min_cl_time;
		fine_offset = p_dram_attr->spd[dram_index].cl_fine_offset;
	}

	tmp = (tmp * 125 + fine_offset + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);
	mask = 1 << (tmp - 7);
	while (mask != 0x40000) {
		if (!(cl_support & mask))
			mask <<= 1; //not match
		else
			break; //match
	}

	if (mask == 0x40000) {
		switch (p_dram_attr->ddr_freq) {
		case DRAM_FREQ_3200:
			mask = 0x008000; //CL = 22
			break;
		case DRAM_FREQ_2666:
			mask = 0x000800; //CL = 18
			break;
		case DRAM_FREQ_1600:
			mask = 0x000020; //CL =  12
			break;
		default:
			break;
		}
	}
	for (index = 0; index < 32; index++) {
		if (mask != 0x01) {
			mask >>= 1;
		} else {
			tmp = index + 7;
			break;
		}
	}

	if (tmp == 9 || tmp == 10) {
		tmp = 11;
	}

	tmp <<= 1;
	p_dram_attr->cl = (uint8_t)tmp;
	NOTICE("DIMM %d , CL = %d\n", dram_index, tmp);
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_14_DATA);
	mmio_modify_32(address, CASLAT_LIN_F0_RW_0_6, shift_to_mask_bit(CASLAT_LIN_F0_RW_0_6, tmp));

}

static void dram_timing_trp(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t tmp = 0;
	int8_t fine_offset = 0;

	tmp = p_dram_attr->spd[dram_index].min_trp;
	fine_offset = p_dram_attr->spd[dram_index].trp_fine_offset;

	tmp = (tmp * 125 + fine_offset + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);
	NOTICE("DIMM %d , trp = %d\n", dram_index, tmp);

	if (p_dram_attr->rank_info[dram_index].rank_num == 1) {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_21_DATA);
		mmio_modify_32(address, TRP_F0_RW_0_8, shift_to_mask_bit(TRP_F0_RW_0_8, tmp));
	} else {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_35_DATA);
		mmio_modify_32(address, TRP_AB_F0_0_RW_16_8, shift_to_mask_bit(TRP_AB_F0_0_RW_16_8, tmp));
	}
}

static void dram_timing_trcd(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t tmp = 0;
	int8_t fine_offset = 0;

	tmp = p_dram_attr->spd[dram_index].min_trcd;
	fine_offset = p_dram_attr->spd[dram_index].trcd_fine_offset;

	tmp = (tmp * 125 + fine_offset + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);
	NOTICE("DIMM %d , trp = %d\n", dram_index, tmp);

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_32_DATA);
	mmio_modify_32(address, TRCD_F0_RW_8_8, shift_to_mask_bit(TRCD_F0_RW_8_8, tmp));
}

static void dram_timing_tras(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t tmp = 0;
	uint16_t tras_min = 0;
	int8_t fine_offset = 0;

	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		tras_min = 0x118; //35ns
		break;
	case DRAM_FREQ_2666:
		tras_min = 0x100; //32ns
		break;
	case DRAM_FREQ_3200:
		tras_min = 0x100; //32ns
		break;
	default:
		break;
	}

	tmp = ((p_dram_attr->spd[dram_index].upper_nibble_tras_trc & 0x0F) << 8) |
		(p_dram_attr->spd[dram_index].min_tras_lsb);
	fine_offset = p_dram_attr->spd[dram_index].trcd_fine_offset;

	if (tmp < tras_min)
		tmp = tras_min;
	tmp = (tmp * 125 + fine_offset + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);
	NOTICE("DIMM %d , tras = %d\n", dram_index, tmp);

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_28_DATA);
	//mmio_modify_32(address, TRAS_MAX_F0_RW_0_20, shift_to_mask_bit(TRAS_MAX_F0_RW_0_20, tmp));
	mmio_modify_32(address, TRAS_MAX_F0_RW_0_20, shift_to_mask_bit(TRAS_MAX_F0_RW_0_20, 0x01b6c0));

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_34_DATA);
	mmio_modify_32(address, TRAS_LOCKOUT_RW_16_1, shift_to_mask_bit(TRAS_LOCKOUT_RW_16_1, 0x1));
}

static void dram_timing_trrd(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t tmp = 0;
	int8_t fine_offset = 0;

	tmp = p_dram_attr->spd[dram_index].min_trrd_short;
	fine_offset = p_dram_attr->spd[dram_index].trrd_short_fine_offset;

	tmp = (tmp * 125 + fine_offset + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);
	NOTICE("DIMM %d , trrd = %d\n", dram_index, tmp);

	p_dram_attr->trrd_s = tmp;

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_18_DATA);
	mmio_modify_32(address, TRRD_F0_RW_24_8, shift_to_mask_bit(TRRD_F0_RW_24_8, tmp));
}

static void dram_timing_twr(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t tmp = 0;
	uint16_t max = 0;

	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		max = 120; //15ns
		break;
	case DRAM_FREQ_2666:
		max = 120;
		break;
	case DRAM_FREQ_3200:
		max = 120;
		break;
	default:
		break;
	}

	tmp = (max * 125 + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);
	p_dram_attr->twr = (uint8_t)tmp;
	NOTICE("DIMM %d , twr = %d\n", dram_index, tmp);

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_32_DATA);
	mmio_modify_32(address, TWR_F0_RW_16_8, shift_to_mask_bit(TWR_F0_RW_16_8, tmp));
}

static void dram_timing_twtr(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t twtr_s = 0;

	//max(2nck,2.5 ns) //DDR4
	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		twtr_s = 3; //15ns
		break;
	case DRAM_FREQ_2666:
		twtr_s = 4;
		break;
	case DRAM_FREQ_3200:
		twtr_s = 4;
		break;
	default:
		break;
	}

	NOTICE("DIMM %d , twtr = %d\n", dram_index, twtr_s);
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_20_DATA);
	mmio_modify_32(address, TWTR_F0_RW_16_6, shift_to_mask_bit(TWTR_F0_RW_16_6, twtr_s));
}

static void dram_timing_trtp(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t trtp = 0;

	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		trtp = 0x07;
		break;
	case DRAM_FREQ_2666:
		trtp = 0x0b;
		break;
	case DRAM_FREQ_3200:
		trtp = 0x0d;
		break;
	default:
		break;
	}

	NOTICE("DIMM %d , trtp = %d\n", dram_index, trtp);
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_26_DATA);
	mmio_modify_32(address, TRTP_F0_RW_24_8, shift_to_mask_bit(TRTP_F0_RW_24_8, trtp));
}

static void dram_timing_tcwl(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t cwl = 0;

	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		cwl = 16; //15ns
		break;
	case DRAM_FREQ_2666:
		cwl = 14;
		break;
	case DRAM_FREQ_3200:
		cwl = 9;
		break;
	default:
		break;
	}

	NOTICE("DIMM %d , tcwl = %d\n", dram_index, cwl);
	p_dram_attr->cwl = (uint8_t)cwl;
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_26_DATA);
	mmio_modify_32(address, TRTP_F0_RW_24_8, shift_to_mask_bit(TRTP_F0_RW_24_8, cwl));
}

static void dram_timing_tfawx(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t tmp = 0;
	uint16_t data = 0;
	int8_t fine_offset = 0;

	tmp = ((p_dram_attr->spd[dram_index].min_upper_nibble_tfaw & 0x0F) << 8) |
		(p_dram_attr->spd[dram_index].min_tfaw);

	tmp = (tmp * 125 + fine_offset + (p_dram_attr->ddr_cycle) - 1) / (p_dram_attr->ddr_cycle);

	data = p_dram_attr->trrd_s * 4;
	if (tmp < data)
		tmp = 1;
	else
		tmp = tmp - data;

	NOTICE("DIMM %d , tfaw = %d\n", dram_index, tmp);

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_21_DATA);
	mmio_modify_32(address, TFAW_F0_RW_8_9, shift_to_mask_bit(TFAW_F0_RW_8_9, tmp));
}

static void dram_timing_tcke(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t trtp = 0;

	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		trtp = 0x4;
		break;
	case DRAM_FREQ_2666:
		trtp = 0x7;
		break;
	case DRAM_FREQ_3200:
		trtp = 0x8;
		break;
	default:
		break;
	}

	NOTICE("DIMM %d , trtp = %d\n", dram_index, trtp);
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_28_DATA);
	mmio_modify_32(address, TCKE_F0_RW_24_4, shift_to_mask_bit(TCKE_F0_RW_24_4, trtp));
}

static void dram_timing_txp(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint16_t trtp = 0;

	switch (p_dram_attr->ddr_freq) {
	case DRAM_FREQ_1600:
		trtp = 0x4;
		break;
	case DRAM_FREQ_2666:
		trtp = 0x7;
		break;
	case DRAM_FREQ_3200:
		trtp = 0x8;
		break;
	default:
		break;
	}

	NOTICE("DIMM %d , trtp = %d\n", dram_index, trtp);
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_28_DATA);
	mmio_modify_32(address, TCKE_F0_RW_24_4, shift_to_mask_bit(TCKE_F0_RW_24_4, trtp));

}

static uint32_t dram_timing(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	dram_timing_rcd(dram_index, p_dram_attr);
	dram_timing_cl(dram_index, p_dram_attr); //MR0
	dram_timing_trp(dram_index, p_dram_attr);
	dram_timing_trcd(dram_index, p_dram_attr);
	dram_timing_tras(dram_index, p_dram_attr);
	dram_timing_trrd(dram_index, p_dram_attr);
	dram_timing_twr(dram_index, p_dram_attr); //MR0
	dram_timing_twtr(dram_index, p_dram_attr);
	dram_timing_trtp(dram_index, p_dram_attr); //MR0
	dram_timing_tcwl(dram_index, p_dram_attr); //MR2
	dram_timing_tfawx(dram_index, p_dram_attr);
	dram_timing_tcke(dram_index, p_dram_attr);

	dram_timing_txp(dram_index, p_dram_attr);  //register
	return 0;
}

static uint32_t dram_init(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;

	//set levling setting
	/* wrlvl_en PI write leveling module  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_123_DATA);
	mmio_modify_32(address, PI_WRLVL_EN_F0_RW_16_2,
		       shift_to_mask_bit(PI_WRLVL_EN_F0_RW_16_2, p_dram_attr->setup.wrlvl_en)); //Freq0
	mmio_modify_32(address, PI_WRLVL_EN_F1_RW_24_2,
		       shift_to_mask_bit(PI_WRLVL_EN_F1_RW_24_2, p_dram_attr->setup.wrlvl_en)); //Freq1

	/* wrlvl_map chip select map for write leveling operations */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_49_DATA);
	mmio_modify_32(address, PI_WRLVL_CS_MAP_RW_0_2,
		       shift_to_mask_bit(PI_WRLVL_CS_MAP_RW_0_2, p_dram_attr->setup.wrlvl_map));

	/* gate_en Enable the PI gate training module for frequency set  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_127_DATA);
	mmio_modify_32(address, PI_RDLVL_GATE_EN_F0_RW_0_2,
		       shift_to_mask_bit(PI_RDLVL_GATE_EN_F0_RW_0_2, p_dram_attr->setup.gate_en));
	//Freq0
	mmio_modify_32(address, PI_RDLVL_GATE_EN_F1_RW_16_2,
		       shift_to_mask_bit(PI_RDLVL_GATE_EN_F1_RW_16_2, p_dram_attr->setup.gate_en));
	//Freq1

	/* gate_map PI chip select map for gate training operations  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_60_DATA);
	mmio_modify_32(address, PI_RDLVL_GATE_CS_MAP_RW_24_2,
		       shift_to_mask_bit(PI_RDLVL_GATE_CS_MAP_RW_24_2, p_dram_attr->setup.gate_map));

	/* rdlvl_en PI chip select map for gate training operations  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_126_DATA);
	mmio_modify_32(address, PI_RDLVL_EN_F0_RW_24_2,
		       shift_to_mask_bit(PI_RDLVL_EN_F0_RW_24_2, p_dram_attr->setup.rdlvl_en));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_127_DATA);
	mmio_modify_32(address, PI_RDLVL_EN_F1_RW_8_2,
		       shift_to_mask_bit(PI_RDLVL_EN_F1_RW_8_2, p_dram_attr->setup.rdlvl_en));

	/* rdlvl_map PI chip select map for gate training operations  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_60_DATA);
	mmio_modify_32(address, PI_RDLVL_CS_MAP_RW_16_2,
		       shift_to_mask_bit(PI_RDLVL_CS_MAP_RW_16_2, p_dram_attr->setup.rdlvl_map));

	/* wdq_en Indicates if Write DQ leveling is enabled for frequency set  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_134_DATA);
	mmio_modify_32(address, PI_WDQLVL_EN_F0_RW_8_2,
		       shift_to_mask_bit(PI_WDQLVL_EN_F0_RW_8_2, p_dram_attr->setup.wdq_en)); //Freq0
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_137_DATA);
	mmio_modify_32(address, PI_WRLVL_EN_F1_RW_24_2,
		       shift_to_mask_bit(PI_WDQLVL_EN_F1_RW_8_2, p_dram_attr->setup.wdq_en)); //Freq1

	/* wdq_map Map of CS’s included in write DQ training sequence.  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_72_DATA);
	mmio_modify_32(address, PI_WDQLVL_CS_MAP_RW_0_2,
		       shift_to_mask_bit(PI_WDQLVL_CS_MAP_RW_0_2, p_dram_attr->setup.wdq_map));

	/* pi_cs_map Defines which chip selects are active  */
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_12_DATA);
	mmio_modify_32(address, PI_CS_MAP_RW_D_16_2,
		       shift_to_mask_bit(PI_CS_MAP_RW_D_16_2, p_dram_attr->setup.pi_cs_map));

	/* Ctrl_cs_map Defines the size of the logical stacks. 3DS DIMM */
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_36_DATA);
	mmio_modify_32(address, LOGICAL_CS_MAP_RW_24_2,
		       shift_to_mask_bit(LOGICAL_CS_MAP_RW_24_2, p_dram_attr->setup.ctrl_cs_map));

	// set MRS regitsr CTL + PI
	// MR0
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_146_DATA);
	mmio_modify_32(address, MR0_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR0_DATA_F0_0_RW_0_18, MR0));//3200-2050
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_161_DATA);
	mmio_modify_32(address, MR0_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR0_DATA_F0_1_RW_0_18, MR0));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_176_DATA);
	mmio_modify_32(address, PI_MR0_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR0_DATA_F0_0_RW_0_18, MR0));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_190_DATA);
	mmio_modify_32(address, PI_MR0_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR0_DATA_F0_1_RW_0_18, MR0));

	//MR1
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_147_DATA);
	mmio_modify_32(address, MR1_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR1_DATA_F0_0_RW_0_18, MR1));//3200-301
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_162_DATA);
	mmio_modify_32(address, MR1_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR1_DATA_F0_1_RW_0_18, MR1));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_177_DATA);
	mmio_modify_32(address, PI_MR1_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR1_DATA_F0_0_RW_0_18, MR1));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_191_DATA);
	mmio_modify_32(address, PI_MR1_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR1_DATA_F0_1_RW_0_18, MR1));

	//MR2
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_148_DATA);
	mmio_modify_32(address, MR2_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR2_DATA_F0_0_RW_0_18, MR2));//3200-428
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_163_DATA);
	mmio_modify_32(address, MR2_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR2_DATA_F0_1_RW_0_18, MR2));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_178_DATA);
	mmio_modify_32(address, PI_MR2_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR2_DATA_F0_0_RW_0_18, MR2));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_192_DATA);
	mmio_modify_32(address, PI_MR2_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR2_DATA_F0_1_RW_0_18, MR2));

	//MR3
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_153_DATA);
	mmio_modify_32(address, MR3_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR3_DATA_F0_0_RW_0_18, MR3));//3200-400
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_168_DATA);
	mmio_modify_32(address, MR3_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR3_DATA_F0_1_RW_0_18, MR3));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_179_DATA);
	mmio_modify_32(address, PI_MR3_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR3_DATA_F0_0_RW_0_18, MR3));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_193_DATA);
	mmio_modify_32(address, PI_MR3_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR3_DATA_F0_1_RW_0_18, MR3));

	//MR4
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_155_DATA);
	mmio_modify_32(address, MR4_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR4_DATA_F0_0_RW_0_18, MR4));//3200-0
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_170_DATA);
	mmio_modify_32(address, MR4_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR4_DATA_F0_1_RW_0_18, MR4));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_180_DATA);
	mmio_modify_32(address, PI_MR4_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR4_DATA_F0_0_RW_0_18, MR4));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_194_DATA);
	mmio_modify_32(address, PI_MR4_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR4_DATA_F0_1_RW_0_18, MR4));

	//MR5
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_157_DATA);
	mmio_modify_32(address, MR5_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR5_DATA_F0_0_RW_0_18, MR5));//3200-503
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_172_DATA);
	mmio_modify_32(address, MR5_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR5_DATA_F0_1_RW_0_18, MR5));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_181_DATA);
	mmio_modify_32(address, PI_MR5_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR5_DATA_F0_0_RW_0_18, MR5));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_195_DATA);
	mmio_modify_32(address, PI_MR5_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR5_DATA_F0_1_RW_0_18, MR5));

	//MR6
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_159_DATA);
	mmio_modify_32(address, MR6_DATA_F0_0_RW_0_18, shift_to_mask_bit(MR6_DATA_F0_0_RW_0_18, MR6));//3200-1093
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_174_DATA);
	mmio_modify_32(address, MR6_DATA_F0_1_RW_0_18, shift_to_mask_bit(MR6_DATA_F0_1_RW_0_18, MR6));

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_182_DATA);
	mmio_modify_32(address, PI_MR6_DATA_F0_0_RW_0_18, shift_to_mask_bit(PI_MR6_DATA_F0_0_RW_0_18, MR6));
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_196_DATA);
	mmio_modify_32(address, PI_MR6_DATA_F0_1_RW_0_18, shift_to_mask_bit(PI_MR6_DATA_F0_1_RW_0_18, MR6));

	// start PI
	if (p_dram_attr->setup.start_pi == 1) {

		if (p_dram_attr->setup.disable_pi_lvl == 1) {
			NOTICE("Disabling PI levelling at initialization\n");
			address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_5_DATA);
			mmio_modify_32(address, PI_INIT_LVL_EN_RW_8_1, shift_to_mask_bit(PI_INIT_LVL_EN_RW_8_1, 0));
		}

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_8_DATA);
		mmio_modify_32(address, PHY_INDEP_TRAIN_MODE_RW_24_1,
			       shift_to_mask_bit(PHY_INDEP_TRAIN_MODE_RW_24_1, 0x1));

		if (p_dram_attr->setup.pi_init_mode_reg == 1) {
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_9_DATA);
			mmio_modify_32(address, PHY_INDEP_INIT_MODE_RW_8_1,
				       shift_to_mask_bit(PHY_INDEP_INIT_MODE_RW_8_1, 0x1));
			NOTICE("Mode Reg Initialization by PI\n");
		} else {

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_9_DATA);
			mmio_modify_32(address, PHY_INDEP_INIT_MODE_RW_8_1,
				       shift_to_mask_bit(PHY_INDEP_INIT_MODE_RW_8_1, 0x0));
			NOTICE("Mode Reg Initialization by PI and CTRL\n");

		}

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_0_DATA);
		mmio_modify_32(address, PI_START_RW_0_1, shift_to_mask_bit(PI_START_RW_0_1, 0x1));
		NOTICE("Started PI\n");
	} else {

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_8_DATA);
		mmio_modify_32(address, PHY_INDEP_TRAIN_MODE_RW_24_1,
			       shift_to_mask_bit(PHY_INDEP_TRAIN_MODE_RW_24_1, 0x1));
		NOTICE("Not Starting PI\n");
	}

	// start controller
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_0_DATA);
	mmio_modify_32(address, START_RW_0_1, shift_to_mask_bit(START_RW_0_1, 0x1));
	NOTICE("start controller\n");

	udelay(10);

	if (p_dram_attr->setup.start_pi == 1) {

		uint32_t counter = 5;

		do {
			//Thread.Sleep(500);
			udelay(500);
			counter--;
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_264_DATA);
			p_dram_attr->setup.mc_init = (mmio_read_32(address) & INT_STATUS_INIT_RD_8_8) >> 9;
			NOTICE("mc_init complete = %x\n", p_dram_attr->setup.mc_init);

			address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_84_DATA);
			p_dram_attr->setup.pi_init = mmio_read_32(address) & DDR_BIT0;
			NOTICE("pi_init complete = %x\n", p_dram_attr->setup.pi_init);

		} while (((p_dram_attr->setup.mc_init == 0) || (p_dram_attr->setup.pi_init == 0)) && (counter > 0));
	} else {

		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_264_DATA);
		p_dram_attr->setup.mc_init = (mmio_read_32(address) & INT_STATUS_INIT_RD_8_8) >> 9;
		NOTICE("mc_init complete = %x\n", p_dram_attr->setup.mc_init);
	}

	if (check_lock_status(dram_index, p_dram_attr) != 0) {
		NOTICE("Deskew PLL Failed\n");
		if (p_dram_attr->setup.mc_init == 0)
			NOTICE("Controller initialized\n");
		else
			NOTICE("Controller initialization failed\n");
		if (p_dram_attr->setup.pi_init == 0)
			NOTICE("PI initialized\n");
		else
			NOTICE("PI initialization failed\n");
	}
	return 0;
}

static uint32_t io_calibration(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint8_t  pad_cal_done, pad_cal_done2;

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2358_DATA);
	mmio_modify_32(address, PHY_CAL_MODE_0_RW_0_13, shift_to_mask_bit(DDR_BIT0, p_dram_attr->setup.init_disable));
	NOTICE("pad calibration upon initialization 0 = enable, 1 = disable %d\n", p_dram_attr->setup.init_disable);

	mmio_modify_32(address, PHY_CAL_MODE_0_RW_0_13,
		       shift_to_mask_bit(DDR_BIT1, p_dram_attr->setup.auto_enable));
	mmio_modify_32(address, PHY_CAL_MODE_0_RW_0_13,
		       shift_to_mask_bit(DDR_BIT2 + DDR_BIT3, p_dram_attr->setup.base_mode));
	mmio_modify_32(address, PHY_CAL_MODE_0_RW_0_13,
		       shift_to_mask_bit(DDR_BIT8, p_dram_attr->setup.cal_polarity));
	mmio_modify_32(address, PHY_CAL_MODE_0_RW_0_13,
		       shift_to_mask_bit(DDR_BIT4 + DDR_BIT5 + DDR_BIT6 + DDR_BIT7,
					 p_dram_attr->setup.cal_mode_pass1));
	mmio_modify_32(address, PHY_CAL_MODE_0_RW_0_13,
		       shift_to_mask_bit(DDR_BIT9 + DDR_BIT10 + DDR_BIT11 + DDR_BIT12,
					 p_dram_attr->setup.cal_mode_pass2));

	//trigger IO calibration no read results
	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2358_DATA);
	mmio_modify_32(address, PHY_CAL_CLEAR_0_WR_16_1, shift_to_mask_bit(PHY_CAL_CLEAR_0_WR_16_1, 0x1));
	mmio_modify_32(address, PHY_CAL_START_0_WR_24_1, shift_to_mask_bit(PHY_CAL_START_0_WR_24_1, 0x1));

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2360_DATA);
	pad_cal_done = (mmio_read_32(address) & DDR_BIT31) >> 31;
	NOTICE("pad_cal_done = %d\n", pad_cal_done);

	address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_2361_DATA);
	pad_cal_done2 = (mmio_read_32(address) & DDR_BIT31) >> 31;
	NOTICE("pad_cal_done2 = %d\n", pad_cal_done2);

	//TODO: print results log
	return 0;
}

static uint32_t write_leveling(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	int byte_index, rank_index;
	bool ecc_enable;
	uint8_t lvl_done, wrlvl_req, wrlvl_err;

	//dcc
	ecc_enable = p_dram_attr->setup.ecc;
	if (p_dram_attr->setup.dcc_wrlvl_en) {
		for (byte_index = 0; byte_index < ((ecc_enable) ? MANGO_MAX_BYTES : MANGO_MAX_BYTES - 1);
			byte_index++) {
			address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_105_DATA + byte_index * 256);
			mmio_modify_32(address, PHY_DATA_DC_WRLVL_ENABLE_0_RW_0_1,
				       shift_to_mask_bit(PHY_DATA_DC_WRLVL_ENABLE_0_RW_0_1,
							 p_dram_attr->setup.dcc_wrlvl_en));
			NOTICE("Enable duty cycle adjust during write leveling\n");
		}
	}
	//Enable the PI write leveling module Bit(1) represents the support when non-initialization.
	//Bit(0)represents the support when initialization. Set to 1 to enable
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_123_DATA);
	mmio_modify_32(address, PI_WRLVL_EN_F0_RW_16_2,
		       shift_to_mask_bit(PI_WRLVL_EN_F0_RW_16_2, 2)); //F0 set2?
	mmio_modify_32(address, PI_WRLVL_EN_F1_RW_24_2,
		       shift_to_mask_bit(PI_WRLVL_EN_F1_RW_24_2, 2)); //F1

	for (rank_index = 0; rank_index < p_dram_attr->rank_info[dram_index].rank_num; rank_index++) {
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_46_DATA);
		mmio_modify_32(address, PI_WRLVL_CS_RW_8_1, shift_to_mask_bit(PI_WRLVL_CS_RW_8_1, rank_index));
		mmio_modify_32(address, PI_WRLVL_REQ_WR_0_1, shift_to_mask_bit(PI_WRLVL_REQ_WR_0_1, 0x1));
		NOTICE("PI-Initiated Write leveling in Progress\n");
		udelay(500);

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_84_DATA);
		lvl_done = (mmio_read_32(address) & DDR_BIT11) >> 11;
		wrlvl_req = (mmio_read_32(address) & DDR_BIT9) >> 9;
		wrlvl_err = (mmio_read_32(address) & DDR_BIT4) >> 4;
		NOTICE("lvl_done = %d, wrlvl_req = %d, wrlvl_err = %d\n", lvl_done, wrlvl_req, wrlvl_err);

		//clear IRQ
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_85_DATA);
		mmio_modify_32(address, PI_INT_ACK_WR_0_18,
			       shift_to_mask_bit(DDR_BIT11 + DDR_BIT9 + DDR_BIT4, DDR_BIT11 + DDR_BIT9 + DDR_BIT4));
	}
	//TODO: print results log
	return 0;
}

static uint32_t gate_training(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint8_t lvl_done, rdlvl_gate_req, rdlvl_gate_err;
	int rank_index;

	//Enable the PI write leveling module Bit(1) represents the support when non-initialization.
	//Bit(0)represents the support when initialization. Set to 1 to enable
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_127_DATA);
	mmio_modify_32(address, PI_RDLVL_GATE_EN_F0_RW_0_2,
		       shift_to_mask_bit(PI_RDLVL_GATE_EN_F0_RW_0_2, 2)); //F0 set2?
	mmio_modify_32(address, PI_RDLVL_GATE_EN_F1_RW_16_2,
		       shift_to_mask_bit(PI_RDLVL_GATE_EN_F1_RW_16_2, 2)); //F1

	for (rank_index = 0; rank_index < p_dram_attr->rank_info[dram_index].rank_num; rank_index++) {
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_56_DATA);
		mmio_modify_32(address, PI_RDLVL_CS_RW_0_1, shift_to_mask_bit(PI_RDLVL_CS_RW_0_1, rank_index));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_55_DATA);
		mmio_modify_32(address, PI_RDLVL_GATE_REQ_WR_24_1, shift_to_mask_bit(PI_RDLVL_GATE_REQ_WR_24_1, 0x1));
		NOTICE(" PI-Initiated Gate Training in progress\n");
		udelay(500);

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_84_DATA);
		lvl_done = (mmio_read_32(address) & DDR_BIT11) >> 11;
		rdlvl_gate_req = (mmio_read_32(address) & DDR_BIT8) >> 8;
		rdlvl_gate_err = (mmio_read_32(address) & DDR_BIT3) >> 3;
		NOTICE("lvl_done = %d, rdlvl_gate_req = %d, rdlvl_gate_err = %d\n",
		       lvl_done, rdlvl_gate_req, rdlvl_gate_err);

		//clear IRQ
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_85_DATA);
		mmio_modify_32(address, PI_INT_ACK_WR_0_18,
			       shift_to_mask_bit(DDR_BIT11 + DDR_BIT8 + DDR_BIT3, DDR_BIT11 + DDR_BIT8 + DDR_BIT3));
	}
	//TODO: print results log
	return 0;
}

static uint32_t read_leveling(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint8_t lvl_done, rdlvl_req, rdlvl_err;
	int rank_index;

	//Enable the PI write leveling module Bit(1) represents the support when non-initialization.
	//Bit(0)represents the support when initialization. Set to 1 to enable
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_126_DATA);
	mmio_modify_32(address, PI_RDLVL_EN_F0_RW_24_2, shift_to_mask_bit(PI_RDLVL_EN_F0_RW_24_2, 2)); //F0 set2?
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_127_DATA);
	mmio_modify_32(address, PI_RDLVL_GATE_EN_F1_RW_16_2, shift_to_mask_bit(PI_RDLVL_GATE_EN_F1_RW_16_2, 2)); //F1

	for (rank_index = 0; rank_index < p_dram_attr->rank_info[dram_index].rank_num; rank_index++) {
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_56_DATA);
		mmio_modify_32(address, PI_RDLVL_CS_RW_0_1, shift_to_mask_bit(PI_RDLVL_CS_RW_0_1, rank_index));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_55_DATA);
		mmio_modify_32(address, PI_RDLVL_REQ_WR_16_1, shift_to_mask_bit(PI_RDLVL_REQ_WR_16_1, 0x1));
		NOTICE(" PI-Initiated Read Levling in progress\n");
		udelay(500);

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_84_DATA);
		lvl_done = (mmio_read_32(address) & DDR_BIT11) >> 11;
		rdlvl_req = (mmio_read_32(address) & DDR_BIT7) >> 7;
		rdlvl_err = (mmio_read_32(address) & DDR_BIT2) >> 2;
		NOTICE("lvl_done = %d, rdlvl_req = %d, rdlvl_err = %d\n", lvl_done, rdlvl_req, rdlvl_err);

		//clear IRQ
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_85_DATA);
		mmio_modify_32(address, PI_INT_ACK_WR_0_18,
			       shift_to_mask_bit(DDR_BIT11 + DDR_BIT7 + DDR_BIT2, DDR_BIT11 + DDR_BIT7 + DDR_BIT2));
	}
	//TODO: print results log
	return 0;
}

static uint32_t write_dq_training(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint8_t lvl_done, wdqlvl_req, wdqlvl_err;
	bool ecc_enable;
	int byte_index, rank_index;

	//dcc
	ecc_enable = p_dram_attr->setup.ecc;
	if (p_dram_attr->setup.dcc_wrlvl_en) {
		for (byte_index = 0; byte_index < ((ecc_enable) ?
					MANGO_MAX_BYTES : MANGO_MAX_BYTES - 1); byte_index++) {
			address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_105_DATA + byte_index * 256);
			mmio_modify_32(address, PHY_DATA_DC_WDQLVL_ENABLE_0_RW_8_1,
				       shift_to_mask_bit(PHY_DATA_DC_WDQLVL_ENABLE_0_RW_8_1,
							 p_dram_attr->setup.dcc_wrlvl_en));
			NOTICE("Enable duty cycle adjust during write dq training\n");
		}
	}

	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_70_DATA);
	mmio_modify_32(address, PI_WDQLVL_VREF_EN_RW_0_1,
		       shift_to_mask_bit(PI_WDQLVL_VREF_EN_RW_0_1, p_dram_attr->setup.pi_wdqlvl_vref_en));
	NOTICE("pi_wdqlvl_vref_en = %d\n", p_dram_attr->setup.pi_wdqlvl_vref_en);

	for (byte_index = 0; byte_index < ((ecc_enable) ? MANGO_MAX_BYTES : MANGO_MAX_BYTES - 1) ; byte_index++) {
		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_74_DATA + byte_index * 256);
		mmio_modify_32(address, PHY_NTP_TRAIN_EN_0_RW_16_1,
			       shift_to_mask_bit(PHY_NTP_TRAIN_EN_0_RW_16_1, p_dram_attr->setup.pi_wdqlvl_vref_en));
		NOTICE("pi_wdqlvl_vref_en = %d\n", p_dram_attr->setup.pi_wdqlvl_vref_en);

		address = mango_ddr_cfg_address(dram_index, phy, DENALI_PHY_40_DATA + byte_index * 256);
		mmio_modify_32(address, PHY_NTP_MULT_TRAIN_0_RW_16_1,
			       shift_to_mask_bit(PHY_NTP_MULT_TRAIN_0_RW_16_1, p_dram_attr->setup.phy_ntp_mult_train));
		NOTICE("phy_ntp_mult_train = %d\n", p_dram_attr->setup.phy_ntp_mult_train);
	}

	//Enable the PI write leveling module Bit(1) represents the support when non-initialization.
	//Bit(0)represents the support when initialization. Set to 1 to enable
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_134_DATA);
	mmio_modify_32(address, PI_WDQLVL_EN_F0_RW_8_2, shift_to_mask_bit(PI_WDQLVL_EN_F0_RW_8_2, 2)); //F0 set2 ？？
	address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_137_DATA);
	mmio_modify_32(address, PI_WDQLVL_EN_F1_RW_8_2, shift_to_mask_bit(PI_WDQLVL_EN_F1_RW_8_2, 2)); //F1

	for (rank_index = 0; rank_index < p_dram_attr->rank_info[dram_index].rank_num; rank_index++) {
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_73_DATA);
		mmio_modify_32(address, PI_WDQLVL_CS_RW_0_1, shift_to_mask_bit(PI_WDQLVL_CS_RW_0_1, rank_index));

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_72_DATA);
		mmio_modify_32(address, PI_WDQLVL_REQ_WR_24_1, shift_to_mask_bit(PI_WDQLVL_REQ_WR_24_1, 0x1));
		NOTICE(" PI-Initiated Read Levling in progress\n");
		udelay(500);

		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_84_DATA);
		lvl_done = (mmio_read_32(address) & DDR_BIT11) >> 11;
		wdqlvl_req = (mmio_read_32(address) & DDR_BIT10) >> 10;
		wdqlvl_err = (mmio_read_32(address) & DDR_BIT5) >> 5;
		NOTICE("lvl_done = %d, wdqlvl_req = %d, wdqlvl_err = %d\n", lvl_done, wdqlvl_req, wdqlvl_err);

		//clear IRQ
		address = mango_ddr_cfg_address(dram_index, pi, DENALI_PI_85_DATA);
		mmio_modify_32(address, PI_INT_ACK_WR_0_18,
			       shift_to_mask_bit(DDR_BIT11 + DDR_BIT10 + DDR_BIT5, DDR_BIT11 + DDR_BIT10 + DDR_BIT5));
	}
	//TODO: print results log
	return 0;

}
#endif

static void mango_ddr_setup_init(ddr_attr *p_dram_attr)
{
	p_dram_attr->ddr_freq = DRAM_FREQ_1600;
	p_dram_attr->ddr_cycle = DRAM_CYCLE_1600;
	p_dram_attr->ddr_dfs_low = DRAM_FREQ_1600;
	p_dram_attr->burst_length = BL8;
	p_dram_attr->setup.dfs = DFS_DIS;
	p_dram_attr->setup.ecc = ECC_DIS;
	p_dram_attr->setup.fast_boot = FAST_BOOT_DIS;

	p_dram_attr->setup.wrlvl_en = 1;
	p_dram_attr->setup.wrlvl_map = 3;
	p_dram_attr->setup.gate_en = 1;
	p_dram_attr->setup.gate_map = 3;
	p_dram_attr->setup.wdq_en = 1;
	p_dram_attr->setup.wdq_map = 3;
	p_dram_attr->setup.rdlvl_en = 1;// 2: non-initialization 1: initialization
	p_dram_attr->setup.rdlvl_map = 3;
	p_dram_attr->setup.pi_cs_map = 3;
	p_dram_attr->setup.ctrl_cs_map = 3; //for 3DS
	p_dram_attr->setup.start_pi = 1;
	p_dram_attr->setup.disable_pi_lvl = 0;
	p_dram_attr->setup.pi_init_mode_reg = 0;
	p_dram_attr->setup.mc_init = 0;
	p_dram_attr->setup.pi_init = 0;

	p_dram_attr->setup.init_disable = 0; //0:enable 1:disable
	p_dram_attr->setup.auto_enable = 0;
	p_dram_attr->setup.base_mode = 1;
	p_dram_attr->setup.cal_polarity = 0;
	p_dram_attr->setup.cal_mode_pass1 = 4;
	p_dram_attr->setup.cal_mode_pass2 = 0;

	p_dram_attr->setup.dcc_wrlvl_en = 0; //disable for bringup
	p_dram_attr->setup.pi_wdqlvl_vref_en = 0; //disable for bringup
	p_dram_attr->setup.phy_ntp_mult_train = 0; //disable for bringup

}

#ifdef DDR_APP_NO_USE
static bool mem_test(uint8_t dram_index, ddr_attr *p_dram_attr, uint64_t test_type)
{
	uint64_t address;
	bool status = false;
	uint16_t addr_space;
	uint16_t rank_space;
	uint8_t test_result;
	uint32_t reg_val;
	uint32_t conter = 0;
	int index;

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_250_DATA);
	mmio_modify_32(address, IN_ORDER_ACCEPT_RW_8_1, shift_to_mask_bit(IN_ORDER_ACCEPT_RW_8_1, 0x1));

	//2.Define the addr_space :0 to 2^addr_space
	rank_space = p_dram_attr->rank_info[dram_index].BG_num +
		p_dram_attr->rank_info[dram_index].bank_num +
		p_dram_attr->rank_info[dram_index].row_num +
		p_dram_attr->rank_info[dram_index].col_num + 3;

	addr_space = rank_space * (p_dram_attr->rank_info[dram_index].rank_num);

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
	mmio_modify_32(address, ADDR_SPACE_RW_8_6, shift_to_mask_bit(ADDR_SPACE_RW_8_6, addr_space));

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_178_DATA);
	mmio_modify_32(address, BIST_START_ADDRESS_RW_0_32, shift_to_mask_bit(BIST_START_ADDRESS_RW_0_32, 0));
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_179_DATA);
	mmio_modify_32(address, BIST_START_ADDRESS_RW_0_8, shift_to_mask_bit(BIST_START_ADDRESS_RW_0_8, 0));

	if (test_type == 0) { //address test
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
		mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1, shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0));
		mmio_modify_32(address, BIST_ADDR_CHECK_RW_24_1, shift_to_mask_bit(BIST_ADDR_CHECK_RW_24_1, 0x1));

		//4.bist_test_mode parameter to ’b100  = Memory initialization programming
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_184_DATA);
		mmio_modify_32(address, BIST_TEST_MODE_RW_16_3, shift_to_mask_bit(BIST_TEST_MODE_RW_16_3, 0x4));

	} else { //data check
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
		mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1, shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0x1));
		mmio_modify_32(address, BIST_ADDR_CHECK_RW_24_1, shift_to_mask_bit(BIST_ADDR_CHECK_RW_24_1, 0));

		//4.bist_test_mode parameter to ’b100  = Memory initialization programming
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_184_DATA);
		mmio_modify_32(address, BIST_TEST_MODE_RW_16_3, shift_to_mask_bit(BIST_TEST_MODE_RW_16_3, 0x4));

	}

	for (index = 0;  index < 4; index++) {
		address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_180_DATA + index);
		mmio_modify_32(address, BIST_DATA_MASK_RW_0_32, shift_to_mask_bit(BIST_DATA_MASK_RW_0_32, 0));
	}
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_184_DATA);
	mmio_modify_32(address, BIST_DATA_MASK_RW_0_32, shift_to_mask_bit(BIST_DATA_MASK_RW_0_32, 0));

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_175_DATA);
	mmio_modify_32(address, BIST_GO_WR_24_1, shift_to_mask_bit(BIST_GO_WR_24_1, 0x1));
	udelay(10);

	//7.Wait for the BIST complete interrupt = 1
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_263_DATA);
	do {
		reg_val = mmio_read_32(address) & INT_STATUS_BIST_RD_0_8 & DDR_BIT0; //bit[0]
		//printf(" %d ", reg_val);
		udelay(500);
		conter++;
		if (conter > 1200) {
			printf(" time out! memory test fail\n");
			break;
		}
	} while (!reg_val);
	printf("\n");

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_250_DATA);
	mmio_modify_32(address, IN_ORDER_ACCEPT_RW_8_1, shift_to_mask_bit(IN_ORDER_ACCEPT_RW_8_1, 0));

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_270_DATA);
	mmio_modify_32(address, INT_ACK_BIST_WR_0_8, shift_to_mask_bit(INT_ACK_BIST_WR_0_8, DDR_BIT0));

	//8.Clear the bist_go parameter to ’b0 to re-enable normal operation.
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_175_DATA);
	mmio_modify_32(address, BIST_GO_WR_24_1, shift_to_mask_bit(BIST_GO_WR_24_1, 0));
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
	test_result = mmio_read_32(address) & BIST_RESULT_RD_0_2;
	mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1, shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0));
	mmio_modify_32(address, BIST_ADDR_CHECK_RW_24_1, shift_to_mask_bit(BIST_ADDR_CHECK_RW_24_1, 0));

	if (test_type == 0x0) {
		test_result = test_result >> 1;
		if (test_type == 0x1) {
			status = true;
			NOTICE("ddr%d address check pass\n", dram_index);
		} else {
			status = false;
			NOTICE("ddr%d address check fail\n", dram_index);
		}
	} else {
		test_result &= DDR_BIT0;
		if (test_result == 0x1) {
			status = true;
			NOTICE("ddr%d data check pass\n", dram_index);
		} else {
			status = false;
			NOTICE("ddr%d data check fail\n", dram_index);
		}
	}
	return status;
}

static uint32_t set_dram_feature(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint64_t begin_addr = 0;
	uint64_t begin_addr_msb = 0;
	uint16_t addr_space;
	uint16_t rank_space;
	uint32_t reg_val;
	uint32_t conter = 0;

	//ECC clear memory
	if (p_dram_attr->setup.ecc == ECC_EN) {
		if (p_dram_attr->spd[dram_index].ecc_support == ECC_EN) {
			printf(" ECC clear memory start\n");

			//0. Forces the controller to accept commands in the orderin which
			//they are placed in the command queue.
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_250_DATA);
			mmio_modify_32(address, IN_ORDER_ACCEPT_RW_8_1, shift_to_mask_bit(IN_ORDER_ACCEPT_RW_8_1, 0x1));

			//1.Define the data range to check by programming the bist_start_address [40:0]
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_178_DATA);
			mmio_modify_32(address, BIST_START_ADDRESS_RW_0_32,
				       shift_to_mask_bit(BIST_START_ADDRESS_RW_0_32, begin_addr));

			begin_addr_msb = begin_addr >> 32;
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_179_DATA);
			mmio_modify_32(address, BIST_START_ADDRESS_RW_0_8,
				       shift_to_mask_bit(BIST_START_ADDRESS_RW_0_8, begin_addr_msb));

			//2.Define the addr_space :0 to 2^addr_space
			rank_space = p_dram_attr->rank_info[dram_index].BG_num +
				p_dram_attr->rank_info[dram_index].bank_num +
				p_dram_attr->rank_info[dram_index].row_num +
				p_dram_attr->rank_info[dram_index].col_num + 3;

			addr_space = rank_space * (p_dram_attr->rank_info[dram_index].rank_num);

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
			mmio_modify_32(address, ADDR_SPACE_RW_8_6, shift_to_mask_bit(ADDR_SPACE_RW_8_6, addr_space));
			//3.Enables the data check portion of the BIST algorithm
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
			mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1,
				       shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0x1));
			mmio_modify_32(address, BIST_ADDR_CHECK_RW_24_1,
				       shift_to_mask_bit(BIST_ADDR_CHECK_RW_24_1, 0));
			//TODO :When this parameter is set to ’b1, the following parameters
			//should all be cleared to ’b0

			//4.bist_test_mode parameter to ’b100  = Memory initialization programming
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_184_DATA);
			mmio_modify_32(address, BIST_TEST_MODE_RW_16_3, shift_to_mask_bit(BIST_TEST_MODE_RW_16_3, 0x4));

			//5.Program the data pattern to be used into the bist_data_pattern parameter
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_185_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x5a5a5a5a));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_186_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x3c3c3c3c));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_187_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x2d2d2d2d));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_188_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x4b4b4b4b));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_189_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x87878787));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_190_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x96969696));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_191_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x2e2e2e2e));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_192_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x3f3f3f3f));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_193_DATA);
			mmio_modify_32(address, BIST_DATA_PATTERN_RW_0_32,
				       shift_to_mask_bit(BIST_DATA_PATTERN_RW_0_32, 0x0));

			udelay(10);
			//6.Initiates a BIST address or data check operation
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_175_DATA);
			mmio_modify_32(address, BIST_GO_WR_24_1, shift_to_mask_bit(BIST_GO_WR_24_1, 0x1));
			udelay(10);

			//7.Wait for the BIST complete interrupt = 1
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_263_DATA);
			do {
				reg_val = mmio_read_32(address) & INT_STATUS_BIST_RD_0_8 & DDR_BIT0; //bit[0]
				printf(" %d ", reg_val);
				udelay(500);
				conter++;
				if (conter > 1200) {
					printf(" time out! clear memory fail\n");
					break;
				}
			} while (!reg_val);
			printf("\n");
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_250_DATA);
			mmio_modify_32(address, IN_ORDER_ACCEPT_RW_8_1, shift_to_mask_bit(IN_ORDER_ACCEPT_RW_8_1, 0));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_270_DATA);
			mmio_modify_32(address, INT_ACK_BIST_WR_0_8, shift_to_mask_bit(INT_ACK_BIST_WR_0_8, DDR_BIT0));

			//8.Clear the bist_go parameter to ’b0 to re-enable normal operation.
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_175_DATA);
			mmio_modify_32(address, BIST_GO_WR_24_1, shift_to_mask_bit(BIST_GO_WR_24_1, 0));
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
			mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1, shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0));
		}
	}
	return 0;
}
#endif

void mango_ddr_init_asic(void)
{
	int status = 1;
	uint8_t dram_index = 0;
	ddr_attr p_dram_attr;

	for (dram_index = 0; dram_index < MANGO_MAX_DIMMS; dram_index++) {

		status = get_spd_data(dram_index, &p_dram_attr);
		if (status != 0)//get spd fail
			continue;

		mango_ddr_setup_init(&p_dram_attr);
		NOTICE("0. ddr_set_init\n");

		dram_frequency_set(dram_index, &p_dram_attr); //pll
		set_ddr_reset(dram_index, &p_dram_attr);
		NOTICE("1 . dram_frequency_set\n");

		dram_init_table(dram_index, &p_dram_attr);
		NOTICE("2 . dram_init_table\n");

		set_dram_configraton(dram_index, &p_dram_attr);
		NOTICE("3 . set_dram_configraton\n");

		cli_loop(0);

#ifdef DDR_APP_NO_USE
		dram_timing(dram_index, &p_dram_attr); //AC timinng
		NOTICE("4 . dram_timing\n");

		dram_init(dram_index, &p_dram_attr);
		NOTICE("6 . dram_init\n");

		io_calibration(dram_index, &p_dram_attr);
		NOTICE("7 . io_calibration\n");

		write_leveling(dram_index, &p_dram_attr);
		NOTICE("8 . write_leveling\n");

		gate_training(dram_index, &p_dram_attr);
		NOTICE("9 . gate_training\n");

		read_leveling(dram_index, &p_dram_attr);
		NOTICE("10 . read_leveling\n");

		write_dq_training(dram_index, &p_dram_attr);
		NOTICE("11 . write_dq_training\n");

		set_dram_feature(dram_index, &p_dram_attr); //ECC clear memory/ data & addr check (ECC)/ lp moode en
		NOTICE("12 . set_dram_feature\n");

		mem_test(dram_index, &p_dram_attr, 1);//1:data check 0:addr check
#endif
		NOTICE("dump_dram_ctl_regiters\n");
		dump_dram_ctl_regiters(dram_index, &p_dram_attr);
		dump_dram_phy_regiters(dram_index, &p_dram_attr);
		dump_dram_pi_regiters(dram_index, &p_dram_attr);
	}
}
