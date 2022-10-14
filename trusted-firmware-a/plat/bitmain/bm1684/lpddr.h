#ifndef __LPDDR4X_H_
#define __LPDDR4X_H_

#define FW_COMPLET_SUCCESS  0x07
#define FW_COMPLET_FAILED  0x0ff

#define MAJOR_MSG   0x0
#define STREAM_MSG  0x8

#define MEM_RSETE_L				0x20060
#define MICRO_CONT_MUX_SEL		0xd0000
#define UCT_SHANDOW_REG			0xd0004
#define DCT_WRITE_PROT_REG		0xd0031
#define UCT_WRITE_ONLY_SHADOW_REG  0xd0032
#define UCT_DATWRITE_ONLY_SHADOW_REG   0xd0034

#define UCT_WRITE_PROT_SHADOW  0x01

#define PHY_OFFSET			0x01000000
#define TARIN_IMEM_OFFSET	0x50000
#define TARIN_DMEM_OFFSET	0x54000

#define NORMAL_MODE MODE_NORMAL
#define FAST_MODE MODE_FAST

#define PLL_STATUS_OFFSET	0xc0
#define PLL_EN_OFFSET	0xc4
#define DPLL0_OFFSET	0xf8
#define DPLL1_OFFSET	0xfc

enum {
	DDR_CTRL0_A_INDEX,
	DDR_CTRL0_B_INDEX,
	DDR_CTRL1_INDEX,
	DDR_CTRL2_INDEX,
};

enum {
	GROUP0,
	GROUP1,
};

#define GROUP_RANK(group0, group1) \
	((group0) & 0xff) | (((group1) & 0xff) << 8)

#define GROUP0_RANK(rank) ((rank) & 0xff)

#define GROUP1_RANK(rank) (((rank) >> 8) & 0xff)

struct pll_freq_table {
	uint32_t freq;
	uint32_t rate;
};

struct init_data {
	uint32_t offset;
	uint32_t value;
};

struct dwc_reg_data {
	uint32_t offset;
	uint32_t value;
};

struct msg_block {
	uint32_t msg_index;
	uint8_t *msg;
};

struct msg_mrs {
	uint16_t train_chan_a;
	uint16_t train_chan_b;
	uint8_t mr1;
	uint8_t mr2;
	uint8_t mr3;
	uint8_t mr4;
	uint8_t mr11;
	uint8_t mr12;
	uint8_t mr13;
	uint8_t mr14;
	uint8_t mr16;
	uint8_t mr17;
	uint8_t mr22;
	uint8_t mrxx; // don't know which it is, maybe just a padding
} __packed;

struct dwc_precfg_freq {
	uint32_t frequency;
	struct dwc_reg_data pie_freq_data[3];
	struct dwc_reg_data phy_freq_data[3];
	struct dwc_reg_data train1d_dmem_freq_data[1];
	struct dwc_reg_data train2d_dmem_freq_data[1];
};

struct dwc_precfg_rank {
	uint32_t rank_num;
	uint32_t cfg_rank;
	struct dwc_reg_data train1d_dmem_rank_data[1];
	struct dwc_reg_data train2d_dmem_rank_data[1];
};

/* pie */
#define PIE_FREQ_2400M \
	{{0x0002000b, 0x004b}, {0x0002000c, 0x0096}, {0x0002000d, 0x05dc}}

#define PIE_FREQ_3600M \
	{{0x0002000b, 0x0070}, {0x0002000c, 0x00e1}, {0x0002000d, 0x08ca}}

#define PIE_FREQ_4000M \
	{{0x0002000b, 0x007d}, {0x0002000c, 0x00fa}, {0x0002000d, 0x09c4}}

#define PIE_FREQ_4266M \
	{{0x0002000b, 0x0085}, {0x0002000c, 0x010a}, {0x0002000d, 0x0a6a}}

/* phy */
#define PHY_FREQ_2400M \
	{{0x000200c5, 0x000a}, {0x00020056, 0x0002}, {0x00020008, 0x0258}}

#define PHY_FREQ_3600M \
	{{0x000200c5, 0x0019}, {0x00020056, 0x0003}, {0x00020008, 0x0384}}

#define PHY_FREQ_4000M \
	{{0x000200c5, 0x0018}, {0x00020056, 0x0003}, {0x00020008, 0x03e8}}

#define PHY_FREQ_4266M \
	{{0x000200c5, 0x0018}, {0x00020056, 0x0003}, {0x00020008, 0x042b}}

#define TRAIN_DMEM_2400M {{0x3, 0x0960}}
#define TRAIN_DMEM_3600M {{0x3, 0x0e10}}
#define TRAIN_DMEM_4000M {{0x3, 0x0fa0}}
#define TRAIN_DMEM_4266M {{0x3, 0x10aa}}

#define TRAIN_DMEM_1RANK {{0x12, 0x120}}
#define TRAIN_DMEM_2RANK {{0x12, 0x320}}

#define CONTROLLER_1RANK 0x81080020
#define CONTROLLER_2RANK 0x83080020

enum {
	FREQ_2400M,
	FREQ_3600M,
	FREQ_4000M,
	FREQ_4266M,
};

enum {
	RANK1 = 1,
	RANK2,
};

static struct msg_mrs lpddr4_1rank = {
	.train_chan_a = 0x32,
	.train_chan_b = 0x65,
	.mr1 = 0x74,
	.mr2 = 0x3f,
	.mr3 = 0xf2,
	.mr11 = 0x16,
	.mr12 = 0x29,
	.mr13 = 0x8,
	.mr14 = 0x15,
	.mr22 = 0x1e
};

static struct msg_mrs lpddr4_2rank = {
	.train_chan_a = 0x32,
	.train_chan_b = 0x65,
	.mr1 = 0x74,
	.mr2 = 0x3f,
	.mr3 = 0xf2,
	.mr11 = 0x16,
	.mr12 = 0x29,
	.mr13 = 0x8,
	.mr14 = 0x15,
	.mr22 = 0x1e
};

#define cfg_freq(freq) \
	{ \
		.frequency = FREQ_##freq##M, \
		.pie_freq_data = PIE_FREQ_##freq##M, \
		.phy_freq_data = PHY_FREQ_##freq##M, \
		.train1d_dmem_freq_data = TRAIN_DMEM_##freq##M, \
		.train2d_dmem_freq_data = TRAIN_DMEM_##freq##M, \
	}

#define cfg_rank(rank) \
	{ \
		.rank_num = RANK##rank, \
		.cfg_rank = CONTROLLER_##rank##RANK, \
		.train1d_dmem_rank_data = TRAIN_DMEM_##rank##RANK, \
		.train2d_dmem_rank_data = TRAIN_DMEM_##rank##RANK, \
	}

struct dwc_precfg_freq pre_cfg_freq[] = {
	cfg_freq(2400),
	cfg_freq(3600),
	cfg_freq(4000),
	cfg_freq(4266),
};

struct dwc_precfg_rank pre_cfg_rank[] = {
	cfg_rank(1),
	cfg_rank(2),
};

#ifdef DDR_ECC_ENABLE
static struct init_data cfg_ecc_1rank[] = {
	// for single rank
	{0x00000200, 0x0000001f},
	// ADDRMAP0, cs0 set to 31 for single rank
	{0x00000204, 0x00080808},
	// ADDRMAP1, bank address continue mapping to 10,11,12
	{0x00000208, 0x00000000},
	// ADDRMAP2, col 2,3,4,5 continue mapping to 2,3,4,5
	{0x0000020c, 0x13131300},
	// ADDRMAP3, col 6 mapping to 6, col 7,8,9 mapping to 26,27,28, no 29 now
	{0x00000210, 0x00001f1f},
	// ADDRMAP4, col b10,11, still no mapping
	{0x00000214, 0x040f0101},
	// ADDRMAP5, row b0,1 continue mapping to 7,8,
	//b2 still set to invalid, b11 map to 21
	{0x00000218, 0x04040404},
	// ADDRMAP6, row 12,13,14,15 mapping to 22,23,24,25, one smaller
	{0x0000021c, 0x00000f0f},
	// ADDRMAP7, row b16,17, still invalid
	{0x00000220, 0x00000000},
	// ADDRMAP8, bg, still invalid
	{0x00000224, 0x04040401},
	// ADDRMAP9, b2 still 9, other minus 1
	{0x00000228, 0x04040404},
	// ADDRMAP10
	{0x0000022c, 0x00000004},
	// ADDRMAP11
};

static struct init_data cfg_ecc_2rank[] = {
	// for dual rank
	{0x00000200, 0x00000007}, // ADDRMAP0
	{0x00000204, 0x00080808}, // ADDRMAP1
	{0x00000208, 0x00000000}, // ADDRMAP2
	{0x0000020c, 0x14141400}, // ADDRMAP3
	{0x00000210, 0x00001f1f}, // ADDRMAP4
	{0x00000214, 0x050f0101}, // ADDRMAP5
	{0x00000218, 0x05050505}, // ADDRMAP6
	{0x0000021c, 0x00000f0f}, // ADDRMAP7
	{0x00000220, 0x00000000}, // ADDRMAP8
	{0x00000224, 0x05050501}, // ADDRMAP9
	{0x00000228, 0x05050505}, // ADDRMAP10
	{0x0000022c, 0x00000005}, // ADDRMAP11
};
#endif

static struct init_data addrmap_1684[] = {
	// for bm1684 ADDRMAP
	{0x00000200, 0x00000017}, // ADDRMAP0
	{0x00000204, 0x00080808}, // ADDRMAP1
	{0x00000208, 0x00000000}, // ADDRMAP2
	{0x0000020c, 0x00000000}, // ADDRMAP3
	{0x00000210, 0x00001f1f}, // ADDRMAP4
	{0x00000214, 0x07070707}, // ADDRMAP5
	{0x00000218, 0x07070707}, // ADDRMAP6
	{0x0000021c, 0x00000f0f}, // ADDRMAP7
	{0x00000220, 0x00000000}, // ADDRMAP8
	{0x00000224, 0x07070707}, // ADDRMAP9
	{0x00000228, 0x07070707}, // ADDRMAP10
	{0x0000022c, 0x00000007}, // ADDRMAP11
};

static struct init_data cfg_data[] = {
	{0x00000000, 0x83080020},
	{0x00000010, 0x00000030},
	{0x00000014, 0x00000000},
	{0x0000001c, 0x00000000},
	{0x00000020, 0x00001404},
	{0x00000024, 0x2f02aab9},
	{0x0000002c, 0x00000001},
	{0x00000030, 0x00000000},
	{0x00000034, 0x00402010},
	{0x00000038, 0x00000000},
	{0x00000050, 0x00e1f070},
	{0x00000054, 0x005b0073},
	{0x00000060, 0x00000000},
	{0x00000064, 0x00820197},
	{0x00000068, 0x00610000},
#ifdef DDR_ECC_ENABLE
	{0x00000070, 0x80000114}, // ECCCFG0
	{0x00000074, 0x000007b0}, // ECCCFG1
#else
	{0x00000070, 0x80000010}, // ECCCFG0
	{0x00000074, 0x00000000}, // ECCCFG1
#endif
	{0x0000007c, 0x00000300},
	{0x000000b8, 0x01000000},
	{0x000000bc, 0x00000000},
	{0x000000c0, 0x00000000},
	{0x000000c4, 0x00000000},
	{0x000000d0, 0xc0030002}, //bit 31:30 0b00->0b11
	{0x000000d4, 0x0001000a},
	{0x000000d8, 0x00007b05},
	{0x000000dc, 0x0074003f},
	{0x000000e0, 0x00f20000},
	{0x000000e4, 0x0005000c},
	{0x000000e8, 0x0001004d},
	{0x000000ec, 0x0000004d},
	{0x000000f0, 0x00000000},
	{0x000000f4, 0x0000f735},
	{0x00000100, 0x2121482d},
	{0x00000104, 0x00090901},
	{0x00000108, 0x09141c1d},
	{0x0000010c, 0x00f0f006},
	{0x00000110, 0x14040914},
	{0x00000114, 0x0f0c1111},
	{0x00000118, 0x0307000a},
	{0x0000011c, 0x00000c05},
	{0x00000120, 0x01016101},
	{0x00000124, 0x00000012},
	{0x00000128, 0x00040e0d},
	{0x0000012c, 0x7f01001a},
	{0x00000130, 0x00020000},
	{0x00000134, 0x0e100002},
	{0x00000138, 0x00000ac4},
	{0x0000013c, 0x00000000},
	{0x00000180, 0x042f0021},
	{0x00000184, 0x03600070},
	{0x00000188, 0x00000000},
	{0x00000190, 0x03a3820e},
	{0x00000194, 0x00090202},
	{0x00000198, 0x07000000},
	{0x0000019c, 0x00000000},
	{0x000001a0, 0x40400018},
	{0x000001a4, 0x008c00b8},
	{0x000001a8, 0x80000000},
	{0x000001b0, 0x00000051},
	{0x000001b4, 0x0000230e},
	{0x000001b8, 0x00000017},
	{0x000001c0, 0x00000007},
	{0x000001c4, 0x00000001},
	{0x00000200, 0x00000007},
	{0x00000204, 0x00080808},
	{0x00000208, 0x00000000},
	{0x0000020c, 0x00000000},
	{0x00000210, 0x00001f1f},
	{0x00000214, 0x08080808},
	{0x00000218, 0x08080808},
	{0x0000021c, 0x00000f08},
	{0x00000220, 0x00000000},
	{0x00000224, 0x08080808},
	{0x00000228, 0x08080808},
	{0x0000022c, 0x00000008},
	{0x00000240, 0x0f0b0440},
	{0x00000244, 0x00000000},
	{0x00000250, 0x10001f85},
	{0x00000254, 0x00000000},
	{0x0000025c, 0x10000000},
	{0x00000264, 0x100001f4},
	{0x0000026c, 0x100001f4},
	{0x00000300, 0x00000040},
	{0x00000304, 0x00000000},
	{0x0000030c, 0x00000003},
	{0x00000320, 0x00000001},
	{0x0000036c, 0x00000000},
	{0x00000374, 0x00000000},
	{0x0000037c, 0x00000000},
	{0x00000384, 0x00000000},
	{0x00000400, 0x00000000},
	{0x00000404, 0x00005040},
	{0x00000408, 0x00005040},
	{0x00000490, 0x00000001},
	{0x00000494, 0x00000000},
	{0x000004b4, 0x00005080},
	{0x000004b8, 0x00005080},
	{0x00000540, 0x00000001},
	{0x00000544, 0x00000000},
	{0x00000564, 0x00004100},
	{0x00000568, 0x00005100},
	{0x000005f0, 0x00000001},
	{0x000005f4, 0x00000000},
	{0x00000614, 0x00005200},
	{0x00000618, 0x00005200},
	{0x000006a0, 0x00000001},
	{0x000006a4, 0x00000000},
	{0x00000f24, 0x0001ff00},
	{0x00000f2c, 0x5a5a5a5a},
};

//pinswap
static struct dwc_reg_data pin_swap_1684_0[] = {
	{0x020100, 0x4},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac
	{0x020101, 0x1},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac
	{0x020102, 0x3},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac
	{0x020103, 0x0},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac
	{0x020104, 0x2},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac
	{0x020105, 0x5},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac

	{0x0100a0, 0x4},	//byte0 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0100a1, 0x6},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0100a2, 0x5},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0100a3, 0x7},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0100a4, 0x0},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0100a5, 0x1},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0100a6, 0x3},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0100a7, 0x2},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0110a0, 0x5},	//byte1 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0110a1, 0x6},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0110a2, 0x1},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0110a3, 0x2},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0110a4, 0x7},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0110a5, 0x4},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0110a6, 0x0},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0110a7, 0x3},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit7
	{0x0120a0, 0x3},	//byte2 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0120a1, 0x6},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0120a2, 0x7},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0120a3, 0x0},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0120a4, 0x4},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0120a5, 0x5},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0120a6, 0x2},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0120a7, 0x1},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0130a0, 0x0},	//byte3 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0130a1, 0x3},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0130a2, 0x1},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0130a3, 0x2},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0130a4, 0x4},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0130a5, 0x5},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0130a6, 0x6},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0130a7, 0x7},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit7
};

static struct dwc_reg_data pin_swap_1684_1[] = {
	{0x020100, 0x4},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac
	{0x020101, 0x1},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac
	{0x020102, 0x0},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac
	{0x020103, 0x3},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac
	{0x020104, 0x2},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac
	{0x020105, 0x5},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac

	{0x0100a0, 0x0},	//byte0 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0100a1, 0x2},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0100a2, 0x1},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0100a3, 0x3},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0100a4, 0x7},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0100a5, 0x5},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0100a6, 0x6},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0100a7, 0x4},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0110a0, 0x0},	//byte1 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0110a1, 0x7},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0110a2, 0x4},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0110a3, 0x3},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0110a4, 0x5},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0110a5, 0x2},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0110a6, 0x6},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0110a7, 0x1},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0120a0, 0x2},	//byte2 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0120a1, 0x1},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0120a2, 0x7},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0120a3, 0x6},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0120a4, 0x4},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0120a5, 0x5},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0120a6, 0x3},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0120a7, 0x0},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit7
	{0x0130a0, 0x3},	//byte3 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0130a1, 0x1},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0130a2, 0x2},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0130a3, 0x0},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0130a4, 0x4},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0130a5, 0x6},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0130a6, 0x5},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0130a7, 0x7},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit7
};

static struct dwc_reg_data pin_swap_1684_2[] = {
	{0x020100, 0x1},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac
	{0x020101, 0x3},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac
	{0x020102, 0x2},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac
	{0x020103, 0x5},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac
	{0x020104, 0x0},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac
	{0x020105, 0x4},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac

	{0x0100a0, 0x5},	//byte0 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0100a1, 0x2},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0100a2, 0x1},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0100a3, 0x4},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0100a4, 0x3},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0100a5, 0x0},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0100a6, 0x6},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0100a7, 0x7},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0110a0, 0x0},	//byte1 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0110a1, 0x1},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0110a2, 0x2},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0110a3, 0x3},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0110a4, 0x4},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0110a5, 0x7},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0110a6, 0x5},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0110a7, 0x6},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0120a0, 0x2},	//byte2 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0120a1, 0x7},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0120a2, 0x4},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0120a3, 0x6},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0120a4, 0x3},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0120a5, 0x0},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0120a6, 0x5},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0120a7, 0x1},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit7

	{0x0130a0, 0x2},	//byte3 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0130a1, 0x0},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0130a2, 0x3},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit2
	{0x0130a3, 0x1},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit3
	{0x0130a4, 0x4},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit4
	{0x0130a5, 0x5},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit5
	{0x0130a6, 0x7},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit6
	{0x0130a7, 0x6},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit7
};

static struct dwc_reg_data pin_swap_1684_3[] = {
	{0x020100, 0x5},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac5
	{0x020101, 0x0},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac0
	{0x020102, 0x1},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac1
	{0x020103, 0x3},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac3
	{0x020104, 0x4},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac4
	{0x020105, 0x2},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac2

	{0x0100a0, 0x7},	//byte0 Dq0LnSel,  phy-bit7 connect to dram-bit0
	{0x0100a1, 0x4},	//byte0 Dq1LnSel,  phy-bit4 connect to dram-bit1
	{0x0100a2, 0x2},	//byte0 Dq1LnSel,  phy-bit2 connect to dram-bit2
	{0x0100a3, 0x6},	//byte0 Dq1LnSel,  phy-bit6 connect to dram-bit3
	{0x0100a4, 0x5},	//byte0 Dq1LnSel,  phy-bit5 connect to dram-bit4
	{0x0100a5, 0x1},	//byte0 Dq1LnSel,  phy-bit1 connect to dram-bit5
	{0x0100a6, 0x3},	//byte0 Dq1LnSel,  phy-bit3 connect to dram-bit6
	{0x0100a7, 0x0},	//byte0 Dq1LnSel,  phy-bit0 connect to dram-bit7

	{0x0110a0, 0x0},	//byte1 Dq0LnSel,  phy-bit0 connect to dram-bit0
	{0x0110a1, 0x3},	//byte1 Dq1LnSel,  phy-bit3 connect to dram-bit1
	{0x0110a2, 0x1},	//byte1 Dq1LnSel,  phy-bit1 connect to dram-bit2
	{0x0110a3, 0x2},	//byte1 Dq1LnSel,  phy-bit2 connect to dram-bit3
	{0x0110a4, 0x6},	//byte1 Dq1LnSel,  phy-bit6 connect to dram-bit4
	{0x0110a5, 0x7},	//byte1 Dq1LnSel,  phy-bit7 connect to dram-bit5
	{0x0110a6, 0x4},	//byte1 Dq1LnSel,  phy-bit4 connect to dram-bit6
	{0x0110a7, 0x5},	//byte1 Dq1LnSel,  phy-bit5 connect to dram-bit7

	{0x0120a0, 0x3},	//byte2 Dq0LnSel,  phy-bit3 connect to dram-bit0
	{0x0120a1, 0x0},	//byte2 Dq1LnSel,  phy-bit0 connect to dram-bit1
	{0x0120a2, 0x7},	//byte2 Dq1LnSel,  phy-bit7 connect to dram-bit2
	{0x0120a3, 0x4},	//byte2 Dq1LnSel,  phy-bit4 connect to dram-bit3
	{0x0120a4, 0x2},	//byte2 Dq1LnSel,  phy-bit2 connect to dram-bit4
	{0x0120a5, 0x6},	//byte2 Dq1LnSel,  phy-bit6 connect to dram-bit5
	{0x0120a6, 0x1},	//byte2 Dq1LnSel,  phy-bit1 connect to dram-bit6
	{0x0120a7, 0x5},	//byte2 Dq1LnSel,  phy-bit5 connect to dram-bit7
	{0x0130a0, 0x1},	//byte3 Dq0LnSel,  phy-bit1 connect to dram-bit0
	{0x0130a1, 0x0},	//byte3 Dq1LnSel,  phy-bit0 connect to dram-bit1
	{0x0130a2, 0x2},	//byte3 Dq1LnSel,  phy-bit2 connect to dram-bit2
	{0x0130a3, 0x3},	//byte3 Dq1LnSel,  phy-bit3 connect to dram-bit3
	{0x0130a4, 0x5},	//byte3 Dq1LnSel,  phy-bit5 connect to dram-bit4
	{0x0130a5, 0x4},	//byte3 Dq1LnSel,  phy-bit4 connect to dram-bit5
	{0x0130a6, 0x6},	//byte3 Dq1LnSel,  phy-bit6 connect to dram-bit6
	{0x0130a7, 0x7},	//byte3 Dq1LnSel,  phy-bit7 connect to dram-bit7
};

//pinswap
static struct dwc_reg_data pin_swap_1684x_0[] = {
	{0x020100, 0x0},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac
	{0x020101, 0x4},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac
	{0x020102, 0x3},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac
	{0x020103, 0x5},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac
	{0x020104, 0x1},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac
	{0x020105, 0x2},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac

	{0x0100a0, 0x0},	//byte0 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0100a1, 0x3},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0100a2, 0x7},	//byte0 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0100a3, 0x6},	//byte0 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0100a4, 0x5},	//byte0 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0100a5, 0x4},	//byte0 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0100a6, 0x2},	//byte0 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0100a7, 0x1},	//byte0 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0110a0, 0x4},	//byte1 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0110a1, 0x5},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0110a2, 0x2},	//byte1 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0110a3, 0x1},	//byte1 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0110a4, 0x0},	//byte1 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0110a5, 0x3},	//byte1 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0110a6, 0x6},	//byte1 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0110a7, 0x7},	//byte1 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0120a0, 0x7},	//byte2 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0120a1, 0x5},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0120a2, 0x4},	//byte2 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0120a3, 0x1},	//byte2 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0120a4, 0x3},	//byte2 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0120a5, 0x2},	//byte2 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0120a6, 0x0},	//byte2 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0120a7, 0x6},	//byte2 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0130a0, 0x0},	//byte3 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0130a1, 0x3},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0130a2, 0x1},	//byte3 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0130a3, 0x2},	//byte3 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0130a4, 0x4},	//byte3 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0130a5, 0x7},	//byte3 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0130a6, 0x5},	//byte3 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0130a7, 0x6},	//byte3 Dq7LnSel,  phy-bit connect to dram-bit7
};

static struct dwc_reg_data pin_swap_1684x_1[] = {
	{0x020100, 0x5},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac
	{0x020101, 0x3},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac
	{0x020102, 0x2},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac
	{0x020103, 0x4},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac
	{0x020104, 0x1},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac
	{0x020105, 0x0},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac

	{0x0100a0, 0x1},	//byte0 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0100a1, 0x4},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0100a2, 0x0},	//byte0 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0100a3, 0x6},	//byte0 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0100a4, 0x3},	//byte0 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0100a5, 0x2},	//byte0 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0100a6, 0x5},	//byte0 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0100a7, 0x7},	//byte0 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0110a0, 0x2},	//byte1 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0110a1, 0x4},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0110a2, 0x0},	//byte1 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0110a3, 0x3},	//byte1 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0110a4, 0x5},	//byte1 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0110a5, 0x6},	//byte1 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0110a6, 0x1},	//byte1 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0110a7, 0x7},	//byte1 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0120a0, 0x0},	//byte2 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0120a1, 0x5},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0120a2, 0x1},	//byte2 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0120a3, 0x6},	//byte2 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0120a4, 0x4},	//byte2 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0120a5, 0x7},	//byte2 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0120a6, 0x3},	//byte2 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0120a7, 0x2},	//byte2 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0130a0, 0x0},	//byte3 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0130a1, 0x3},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0130a2, 0x1},	//byte3 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0130a3, 0x2},	//byte3 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0130a4, 0x6},	//byte3 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0130a5, 0x4},	//byte3 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0130a6, 0x5},	//byte3 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0130a7, 0x7},	//byte3 Dq7LnSel,  phy-bit connect to dram-bit7
};

static struct dwc_reg_data pin_swap_1684x_2[] = {
	{0x020100, 0x0},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac
	{0x020101, 0x4},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac
	{0x020102, 0x3},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac
	{0x020103, 0x5},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac
	{0x020104, 0x1},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac
	{0x020105, 0x2},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac

	{0x0100a0, 0x0},	//byte0 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0100a1, 0x3},	//byte0 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0100a2, 0x7},	//byte0 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0100a3, 0x6},	//byte0 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0100a4, 0x5},	//byte0 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0100a5, 0x4},	//byte0 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0100a6, 0x2},	//byte0 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0100a7, 0x1},	//byte0 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0110a0, 0x4},	//byte1 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0110a1, 0x5},	//byte1 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0110a2, 0x2},	//byte1 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0110a3, 0x1},	//byte1 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0110a4, 0x0},	//byte1 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0110a5, 0x3},	//byte1 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0110a6, 0x6},	//byte1 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0110a7, 0x7},	//byte1 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0120a0, 0x7},	//byte2 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0120a1, 0x5},	//byte2 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0120a2, 0x4},	//byte2 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0120a3, 0x1},	//byte2 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0120a4, 0x3},	//byte2 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0120a5, 0x2},	//byte2 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0120a6, 0x0},	//byte2 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0120a7, 0x6},	//byte2 Dq7LnSel,  phy-bit connect to dram-bit7

	{0x0130a0, 0x0},	//byte3 Dq0LnSel,  phy-bit connect to dram-bit0
	{0x0130a1, 0x3},	//byte3 Dq1LnSel,  phy-bit connect to dram-bit1
	{0x0130a2, 0x1},	//byte3 Dq2LnSel,  phy-bit connect to dram-bit2
	{0x0130a3, 0x2},	//byte3 Dq3LnSel,  phy-bit connect to dram-bit3
	{0x0130a4, 0x4},	//byte3 Dq4LnSel,  phy-bit connect to dram-bit4
	{0x0130a5, 0x7},	//byte3 Dq5LnSel,  phy-bit connect to dram-bit5
	{0x0130a6, 0x5},	//byte3 Dq6LnSel,  phy-bit connect to dram-bit6
	{0x0130a7, 0x6},	//byte3 Dq7LnSel,  phy-bit connect to dram-bit7
};

static struct dwc_reg_data pin_swap_1684x_3[] = {
	{0x020100, 0x5},	//MapCAA0toDfi,  connect phy-AC0 to dram-ac5
	{0x020101, 0x3},	//MapCAA1toDfi,  connect phy-AC1 to dram-ac0
	{0x020102, 0x2},	//MapCAA2toDfi,  connect phy-AC2 to dram-ac1
	{0x020103, 0x4},	//MapCAA3toDfi,  connect phy-AC3 to dram-ac3
	{0x020104, 0x1},	//MapCAA4toDfi,  connect phy-AC4 to dram-ac4
	{0x020105, 0x0},	//MapCAA5toDfi,  connect phy-AC5 to dram-ac2

	{0x0100a0, 0x1},	//byte0 Dq0LnSel,  phy-bit7 connect to dram-bit0
	{0x0100a1, 0x4},	//byte0 Dq1LnSel,  phy-bit4 connect to dram-bit1
	{0x0100a2, 0x0},	//byte0 Dq2LnSel,  phy-bit2 connect to dram-bit2
	{0x0100a3, 0x6},	//byte0 Dq3LnSel,  phy-bit6 connect to dram-bit3
	{0x0100a4, 0x3},	//byte0 Dq4LnSel,  phy-bit5 connect to dram-bit4
	{0x0100a5, 0x2},	//byte0 Dq5LnSel,  phy-bit1 connect to dram-bit5
	{0x0100a6, 0x5},	//byte0 Dq6LnSel,  phy-bit3 connect to dram-bit6
	{0x0100a7, 0x7},	//byte0 Dq7LnSel,  phy-bit0 connect to dram-bit7

	{0x0110a0, 0x2},	//byte1 Dq0LnSel,  phy-bit0 connect to dram-bit0
	{0x0110a1, 0x4},	//byte1 Dq1LnSel,  phy-bit3 connect to dram-bit1
	{0x0110a2, 0x0},	//byte1 Dq2LnSel,  phy-bit1 connect to dram-bit2
	{0x0110a3, 0x3},	//byte1 Dq3LnSel,  phy-bit2 connect to dram-bit3
	{0x0110a4, 0x5},	//byte1 Dq4LnSel,  phy-bit6 connect to dram-bit4
	{0x0110a5, 0x6},	//byte1 Dq5LnSel,  phy-bit7 connect to dram-bit5
	{0x0110a6, 0x1},	//byte1 Dq6LnSel,  phy-bit4 connect to dram-bit6
	{0x0110a7, 0x7},	//byte1 Dq7LnSel,  phy-bit5 connect to dram-bit7

	{0x0120a0, 0x0},	//byte2 Dq0LnSel,  phy-bit3 connect to dram-bit0
	{0x0120a1, 0x5},	//byte2 Dq1LnSel,  phy-bit0 connect to dram-bit1
	{0x0120a2, 0x1},	//byte2 Dq2LnSel,  phy-bit7 connect to dram-bit2
	{0x0120a3, 0x6},	//byte2 Dq3LnSel,  phy-bit4 connect to dram-bit3
	{0x0120a4, 0x4},	//byte2 Dq4LnSel,  phy-bit2 connect to dram-bit4
	{0x0120a5, 0x7},	//byte2 Dq5LnSel,  phy-bit6 connect to dram-bit5
	{0x0120a6, 0x3},	//byte2 Dq6LnSel,  phy-bit1 connect to dram-bit6
	{0x0120a7, 0x2},	//byte2 Dq7LnSel,  phy-bit5 connect to dram-bit7

	{0x0130a0, 0x0},	//byte3 Dq0LnSel,  phy-bit1 connect to dram-bit0
	{0x0130a1, 0x3},	//byte3 Dq1LnSel,  phy-bit0 connect to dram-bit1
	{0x0130a2, 0x1},	//byte3 Dq2LnSel,  phy-bit2 connect to dram-bit2
	{0x0130a3, 0x2},	//byte3 Dq3LnSel,  phy-bit3 connect to dram-bit3
	{0x0130a4, 0x6},	//byte3 Dq4LnSel,  phy-bit5 connect to dram-bit4
	{0x0130a5, 0x4},	//byte3 Dq5LnSel,  phy-bit4 connect to dram-bit5
	{0x0130a6, 0x5},	//byte3 Dq6LnSel,  phy-bit6 connect to dram-bit6
	{0x0130a7, 0x7},	//byte3 Dq7LnSel,  phy-bit7 connect to dram-bit7
};

#endif
