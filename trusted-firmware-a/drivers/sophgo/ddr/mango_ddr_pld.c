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
#include <drivers/sophgo/mango_ddr.h>
#include <drivers/sophgo/mango_ddr_register.h>
#include <drivers/sophgo/spd.h>

#define Rshift(ope, num) ((uint64_t)(ope) >> (num))
#define Lshift(ope, num) ((uint64_t)(ope) << (num))

enum reg_type {ctl, phy, pi};

static void mmio_modify_32(uint64_t address, uint32_t mask, uint32_t value)
{
	int32_t data32 = mmio_read_32(address);

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

#if 0
static void dump_dram_ctl_regiters(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint32_t data;
	uint16_t index1, index2;

	printf("dump CTL port address:\n");
	printf("     00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
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
	printf("     00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
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
	printf("     00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F\n");
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
#endif

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

#if 0
	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_37_DATA);
	mmio_modify_32(address, REG_DIMM_ENABLE_RW_8_1, shift_to_mask_bit(REG_DIMM_ENABLE_RW_8_1, 0x1));

	address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_419_DATA);
	mmio_modify_32(address, RDLAT_ADJ_F0_RW_0_7, shift_to_mask_bit(RDLAT_ADJ_F0_RW_0_7, 0x12));
	mmio_modify_32(address, WRLAT_ADJ_F0_RW_8_7, shift_to_mask_bit(WRLAT_ADJ_F0_RW_8_7, 0x0c));
	NOTICE("enable RDIMM\n");
#endif

	udelay(10);
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
		       shift_to_mask_bit(PI_RDLVL_GATE_EN_F0_RW_0_2, p_dram_attr->setup.gate_en)); //Freq0
	mmio_modify_32(address, PI_RDLVL_GATE_EN_F1_RW_16_2,
		       shift_to_mask_bit(PI_RDLVL_GATE_EN_F1_RW_16_2, p_dram_attr->setup.gate_en)); //Freq1

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

/* wdq_map Map of CS included in write DQ training sequence.  */
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

static void mango_ddr_setup_init(ddr_attr *p_dram_attr)
{
	p_dram_attr->ddr_freq = DRAM_FREQ_3200;
	p_dram_attr->ddr_cycle = DRAM_CYCLE_3200;
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
}

static uint32_t set_dram_feature(uint8_t dram_index, ddr_attr *p_dram_attr)
{
	uint64_t address;
	uint64_t begin_addr = 0;
	uint64_t begin_addr_msb = 0;
	uint32_t reg_val;
	uint32_t conter = 0;

//ECC clear memory
	if (p_dram_attr->setup.ecc == ECC_EN) {
		if (1) {
			NOTICE(" ECC clear memory start\n");

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

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
			mmio_modify_32(address, ADDR_SPACE_RW_8_6, shift_to_mask_bit(ADDR_SPACE_RW_8_6, 0x1E));  //1G

			//3.Enables the data check portion of the BIST algorithm
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
			mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1,
				       shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0x1));
			mmio_modify_32(address, BIST_ADDR_CHECK_RW_24_1,
				       shift_to_mask_bit(BIST_ADDR_CHECK_RW_24_1, 0));
			/*TODO :When this parameter is set to b1, the following parameters should all be cleared to b0*/

			//4.bist_test_mode parameter to b100  = Memory initialization programming
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
					NOTICE(" time out! clear memory fail\n ");
					break;
				}
			} while (!reg_val);
			printf("\n");
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_250_DATA);
			mmio_modify_32(address, IN_ORDER_ACCEPT_RW_8_1, shift_to_mask_bit(IN_ORDER_ACCEPT_RW_8_1, 0));

			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_270_DATA);
			mmio_modify_32(address, INT_ACK_BIST_WR_0_8, shift_to_mask_bit(INT_ACK_BIST_WR_0_8, DDR_BIT0));

			//8.Clear the bist_go parameter to 0 to re-enable normal operation.
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_175_DATA);
			mmio_modify_32(address, BIST_GO_WR_24_1, shift_to_mask_bit(BIST_GO_WR_24_1, 0));
			address = mango_ddr_cfg_address(dram_index, ctl, DENALI_CTL_176_DATA);
			mmio_modify_32(address, BIST_DATA_CHECK_RW_16_1, shift_to_mask_bit(BIST_DATA_CHECK_RW_16_1, 0));
		}
	}
	return 0;
}

void mango_ddr_init_pld(void)
{
	uint8_t dram_index = 0;

	ddr_attr p_dram_attr;

	NOTICE("enter ddr_init\n");
	mango_ddr_setup_init(&p_dram_attr);

	for (dram_index = 0; dram_index < MANGO_MAX_DIMMS; dram_index++) {
		dram_init_table(dram_index, &p_dram_attr);
		NOTICE("dram_init_table dimm_index = %d\n", dram_index);

		dram_init(dram_index, &p_dram_attr);
		NOTICE(" dram_init dimm_index = %d\n", dram_index);

		set_dram_feature(dram_index, &p_dram_attr); //ECC clear memory
		NOTICE(" set dram_feature: dimm_index = %d\n", dram_index);

		//dump_dram_ctl_regiters(dram_index, &p_dram_attr);
		//dump_dram_phy_regiters(dram_index, &p_dram_attr);
		//dump_dram_pi_regiters(dram_index, &p_dram_attr);
	}
}

