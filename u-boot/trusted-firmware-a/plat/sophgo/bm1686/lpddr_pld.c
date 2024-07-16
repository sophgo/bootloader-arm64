/*
 * Copyright (c) 2015-2018, ARM Limited and Contributors.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <mmio.h>
#include "platform_def.h"
#include "bm_common.h"

#define DDR_TYPE_LPDDR_PLD
#ifdef DDR_TYPE_LPDDR_PLD

/*
 * this file is for configuring the DDR sub-system for:
 *  - LPDDR4
 *  - non-inlineECC
 *  - No training, and uMCTL2 will do SDRAM initialization
 *  - Speedbin: 4267, Set-A
 *  - LOCKSTEP model
 *  - 2 DFI (POP) connection
 *  - 2 rank
 *  - 32 Gb per rank
 */

static inline void opdelay(unsigned int times)
{
	while (times--)
		__asm__ volatile ("nop");
}

void ddr_init(int cfg_base)
{
	uint32_t read_data;
	uint32_t ddr_index = 0;	//0:ddr0a,1:ddr0b,2:ddr1,3:ddr2

	if (cfg_base == DDR_CTRL2)
		ddr_index = 3;
	else if (cfg_base == DDR_CTRL0_A)
		ddr_index = 0;
	else if (cfg_base == DDR_CTRL0_B)
		ddr_index = 1;
	else if (cfg_base == DDR_CTRL1)
		ddr_index = 2;

	// 1. Assert the core_ddrc_rstn and areset_n resets (ddrc reset,
	// and axi reset)
	// 2. assert the preset
	// 3. start the clocks (pclk, core_ddrc_clk, aclk_n)
	// 4. Deassert presetn once the clocks are active and stable
	// 5. allow 128 cycle for synchronization of presetn to
	// core_ddrc_core_clk and aclk domain and to
	//    permit initialization of end logic
	// 6. Initialize the registers
	// 7. Deassert the resets

	///////////////////////////////////////////
	//					 //
	// uMCTL2 DDRC Controller Initialization //
	//					 //
	///////////////////////////////////////////
	//
	// Start Clocks
	// TODO:
	//
	// Assert core_ddrc_rstn, areset_n
	read_data = mmio_read_32(0x50010c00);
	read_data = read_data & (~(1 << (3 + ddr_index)));
	mmio_write_32(0x50010c00, read_data);
	opdelay(50);
	// De-assert preset
	read_data = mmio_read_32(0x50010c00);
	mmio_write_32(0x50010c00, read_data | (1 << (7 + ddr_index)));
	opdelay(100);
	// Assert preset
	mmio_write_32(0x50010c00, read_data);
	opdelay(100);
	// Assert pwrokin, bit[11:14]
	//bit 11:14 -> ddr0a/ddr0b/ddr1/ddr2 pwrokin
	read_data |= 1 << (11 + ddr_index);
	mmio_write_32(0x50010c00, read_data);
	opdelay(100);
	// Deassert preset
	read_data |= 1 << (7 + ddr_index);
	mmio_write_32(0x50010c00, read_data);
	opdelay(100);
	//
	// wait 128 cycle of pclk at least
	// TODO:
	opdelay(1000);
	//
	mmio_write_32(cfg_base + 0x00000000, 0x83080020);
	mmio_write_32(cfg_base + 0x00000010, 0x00000030);
	mmio_write_32(cfg_base + 0x00000014, 0x00000000);
	mmio_write_32(cfg_base + 0x0000001c, 0x00000000);
	mmio_write_32(cfg_base + 0x00000020, 0x00001404);
	mmio_write_32(cfg_base + 0x00000024, 0x2f02aab9);
	mmio_write_32(cfg_base + 0x0000002c, 0x00000001);
	mmio_write_32(cfg_base + 0x00000030, 0x00000000);
	mmio_write_32(cfg_base + 0x00000034, 0x00402010);
	mmio_write_32(cfg_base + 0x00000038, 0x00000000);
	mmio_write_32(cfg_base + 0x00000050, 0x00e1f070);
	mmio_write_32(cfg_base + 0x00000054, 0x005b0073);
	mmio_write_32(cfg_base + 0x00000060, 0x00000000);
	mmio_write_32(cfg_base + 0x00000064, 0x00820197);
	mmio_write_32(cfg_base + 0x00000068, 0x00610000);
#ifdef DDR_ECC_ENABLE
	mmio_write_32(cfg_base + 0x00000070, 0x80000114); // ECCCFG0
	mmio_write_32(cfg_base + 0x00000074, 0x000007b0); // ECCCFG1
#else
	mmio_write_32(cfg_base + 0x00000070, 0x80000010); // ECCCFG0
	mmio_write_32(cfg_base + 0x00000074, 0x00000000); // ECCCFG1
#endif
	mmio_write_32(cfg_base + 0x0000007c, 0x00000300);
	mmio_write_32(cfg_base + 0x000000b8, 0x01000000);
	mmio_write_32(cfg_base + 0x000000bc, 0x00000000);
	mmio_write_32(cfg_base + 0x000000c0, 0x00000000);
	mmio_write_32(cfg_base + 0x000000c4, 0x00000000);
	mmio_write_32(cfg_base + 0x000000d0, 0x00030002);
	mmio_write_32(cfg_base + 0x000000d4, 0x0001000a);
	mmio_write_32(cfg_base + 0x000000d8, 0x00007b05);
	mmio_write_32(cfg_base + 0x000000dc, 0x0074003f);
	mmio_write_32(cfg_base + 0x000000e0, 0x00f20000);
	mmio_write_32(cfg_base + 0x000000e4, 0x0005000c);
	mmio_write_32(cfg_base + 0x000000e8, 0x0001004d);
	mmio_write_32(cfg_base + 0x000000ec, 0x0000004d);
	mmio_write_32(cfg_base + 0x000000f0, 0x00000000);
	mmio_write_32(cfg_base + 0x000000f4, 0x0000f735);
	mmio_write_32(cfg_base + 0x00000100, 0x2121482d);
	mmio_write_32(cfg_base + 0x00000104, 0x00090901);
	mmio_write_32(cfg_base + 0x00000108, 0x09141c1d);
	mmio_write_32(cfg_base + 0x0000010c, 0x00f0f006);
	mmio_write_32(cfg_base + 0x00000110, 0x14040914);
	mmio_write_32(cfg_base + 0x00000114, 0x0f0c1111);
	mmio_write_32(cfg_base + 0x00000118, 0x0307000a);
	mmio_write_32(cfg_base + 0x0000011c, 0x00000c05);
	mmio_write_32(cfg_base + 0x00000120, 0x01016101);
	mmio_write_32(cfg_base + 0x00000124, 0x00000012);
	mmio_write_32(cfg_base + 0x00000128, 0x00040e0d);
	mmio_write_32(cfg_base + 0x0000012c, 0x7f01001a);
	mmio_write_32(cfg_base + 0x00000130, 0x00020000);
	mmio_write_32(cfg_base + 0x00000134, 0x0e100002);
	mmio_write_32(cfg_base + 0x00000138, 0x00000ac4);
	mmio_write_32(cfg_base + 0x0000013c, 0x00000000);
	mmio_write_32(cfg_base + 0x00000180, 0x042f0021);
	mmio_write_32(cfg_base + 0x00000184, 0x03600070);
	mmio_write_32(cfg_base + 0x00000188, 0x00000000);
	mmio_write_32(cfg_base + 0x00000190, 0x03a3820e);
	mmio_write_32(cfg_base + 0x00000194, 0x00090202);
	mmio_write_32(cfg_base + 0x00000198, 0x07000000);
	mmio_write_32(cfg_base + 0x0000019c, 0x00000000);
	mmio_write_32(cfg_base + 0x000001a0, 0x40400018);
	mmio_write_32(cfg_base + 0x000001a4, 0x008c00b8);
	mmio_write_32(cfg_base + 0x000001a8, 0x80000000);
	mmio_write_32(cfg_base + 0x000001b0, 0x00000051);
	mmio_write_32(cfg_base + 0x000001b4, 0x0000230e);
	mmio_write_32(cfg_base + 0x000001b8, 0x00000017);
	mmio_write_32(cfg_base + 0x000001c0, 0x00000007);
	mmio_write_32(cfg_base + 0x000001c4, 0x00000001);
#ifdef DDR_ECC_ENABLE
	mmio_write_32(cfg_base + 0x00000200, 0x00000007); // ADDRMAP0
	mmio_write_32(cfg_base + 0x00000204, 0x00080808); // ADDRMAP1
	mmio_write_32(cfg_base + 0x00000208, 0x00000000); // ADDRMAP2
	mmio_write_32(cfg_base + 0x0000020c, 0x14141400); // ADDRMAP3
	mmio_write_32(cfg_base + 0x00000210, 0x00001f1f); // ADDRMAP4
	mmio_write_32(cfg_base + 0x00000214, 0x050f0101); // ADDRMAP5
	mmio_write_32(cfg_base + 0x00000218, 0x05050505); // ADDRMAP6
	mmio_write_32(cfg_base + 0x0000021c, 0x00000f0f); // ADDRMAP7
	mmio_write_32(cfg_base + 0x00000220, 0x00000000); // ADDRMAP8
	mmio_write_32(cfg_base + 0x00000224, 0x05050501); // ADDRMAP9
	mmio_write_32(cfg_base + 0x00000228, 0x05050505); // ADDRMAP10
	mmio_write_32(cfg_base + 0x0000022c, 0x00000005); // ADDRMAP11
#else
	mmio_write_32(cfg_base + 0x00000200, 0x00000007);
	mmio_write_32(cfg_base + 0x00000204, 0x00080808);
	mmio_write_32(cfg_base + 0x00000208, 0x00000000);
	mmio_write_32(cfg_base + 0x0000020c, 0x00000000);
	mmio_write_32(cfg_base + 0x00000210, 0x00001f1f);
	mmio_write_32(cfg_base + 0x00000214, 0x08080808);
	mmio_write_32(cfg_base + 0x00000218, 0x08080808);
	mmio_write_32(cfg_base + 0x0000021c, 0x00000f08);
	mmio_write_32(cfg_base + 0x00000220, 0x00000000);
	mmio_write_32(cfg_base + 0x00000224, 0x08080808);
	mmio_write_32(cfg_base + 0x00000228, 0x08080808);
	mmio_write_32(cfg_base + 0x0000022c, 0x00000008);
#endif
	mmio_write_32(cfg_base + 0x00000240, 0x0f0b0440);
	mmio_write_32(cfg_base + 0x00000244, 0x00000000);
	mmio_write_32(cfg_base + 0x00000250, 0x10001f85);
	mmio_write_32(cfg_base + 0x00000254, 0x00000000);
	mmio_write_32(cfg_base + 0x0000025c, 0x10000000);
	mmio_write_32(cfg_base + 0x00000264, 0x100001f4);
	mmio_write_32(cfg_base + 0x0000026c, 0x100001f4);
	mmio_write_32(cfg_base + 0x00000300, 0x00000040);
	mmio_write_32(cfg_base + 0x00000304, 0x00000000);
	mmio_write_32(cfg_base + 0x0000030c, 0x00000003);
	mmio_write_32(cfg_base + 0x00000320, 0x00000001);
	mmio_write_32(cfg_base + 0x0000036c, 0x00000000);
	mmio_write_32(cfg_base + 0x00000374, 0x00000000);
	mmio_write_32(cfg_base + 0x0000037c, 0x00000000);
	mmio_write_32(cfg_base + 0x00000384, 0x00000000);
	mmio_write_32(cfg_base + 0x00000400, 0x00000000);
	mmio_write_32(cfg_base + 0x00000404, 0x00005040);
	mmio_write_32(cfg_base + 0x00000408, 0x00005040);
	mmio_write_32(cfg_base + 0x00000490, 0x00000001);
	mmio_write_32(cfg_base + 0x00000494, 0x00000000);
	mmio_write_32(cfg_base + 0x000004b4, 0x00005080);
	mmio_write_32(cfg_base + 0x000004b8, 0x00005080);
	mmio_write_32(cfg_base + 0x00000540, 0x00000001);
	mmio_write_32(cfg_base + 0x00000544, 0x00000000);
	mmio_write_32(cfg_base + 0x00000564, 0x00004100);
	mmio_write_32(cfg_base + 0x00000568, 0x00005100);
	mmio_write_32(cfg_base + 0x000005f0, 0x00000001);
	mmio_write_32(cfg_base + 0x000005f4, 0x00000000);
	mmio_write_32(cfg_base + 0x00000614, 0x00005200);
	mmio_write_32(cfg_base + 0x00000618, 0x00005200);
	mmio_write_32(cfg_base + 0x000006a0, 0x00000001);
	mmio_write_32(cfg_base + 0x000006a4, 0x00000000);
	mmio_write_32(cfg_base + 0x00000f24, 0x0001ff00);
	mmio_write_32(cfg_base + 0x00000f2c, 0x5a5a5a5a);

	// make sure the write is done
	// in ddrc_env, it just wait 10 clock to make sure write is done,
	// and then release core_ddrc_rstn
	// TODO:
	opdelay(100);
	//
	// the DDR initialization if done by here ////
	//
	// Dessert the resets: axi reset and core_ddrc_rstn
	// TODO:
	read_data = mmio_read_32(0x50010c00);
	read_data = read_data | (1 << (3 + ddr_index));
	mmio_write_32(0x50010c00, read_data);
	opdelay(50);

	//////////////////////////////////////////
	//					//
	// PHY Inialization, without training	//
	//					//
	//////////////////////////////////////////

	// enable the reigster access for dynamic register
	// APB_QUASI_DYN_G0_SLEEP
	mmio_write_32(cfg_base + 0x00000320, 0x00000000);

	// set dfi_init_complete_en, for phy initialization
	mmio_write_32(cfg_base + 0x000001b0, 0x00000040);

#ifdef DDR_PHY_ENABLE
	// phy register, original is APB address which is half word based
	// left shift by one since in SOC it's byte based,
	// add 16MB since the first 16MB is allocated to uMCTL2
	// phy initialization file, generated automically
	mmio_write_16(cfg_base + 0x01000000 + (0x0001005f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001015f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001105f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001115f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001205f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001215f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001305f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001315f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011005f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011015f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011105f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011115f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011205f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011215f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011305f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011315f << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00000055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00001055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00002055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00003055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00004055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00005055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00006055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00007055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00008055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00009055 << 1), 0x000001ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200c5 << 1), 0x00000019);
	mmio_write_16(cfg_base + 0x01000000 + (0x001200c5 << 1), 0x00000006);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002002e << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012002e << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090204 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00190204 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020024 << 1), 0x000001e3);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002003a << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x00120024 << 1), 0x000001e3);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002003a << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020056 << 1), 0x00000003);
	mmio_write_16(cfg_base + 0x01000000 + (0x00120056 << 1), 0x00000003);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001004d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001014d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001104d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001114d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001204d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001214d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001304d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0001314d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011004d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011014d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011104d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011114d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011204d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011214d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011304d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x0011314d << 1), 0x00000600);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113049 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113149 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00000043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00001043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00002043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00003043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00004043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00005043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00006043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00007043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00008043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00009043 << 1), 0x000003ff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020018 << 1), 0x00000003);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020075 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020050 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020008 << 1), 0x0000042f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00120008 << 1), 0x0000010b);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020088 << 1), 0x00000009);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200b2 << 1), 0x00000104);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x001200b2 << 1), 0x00000104);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113043 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113143 << 1), 0x000005a1);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200fa << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x001200fa << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020019 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00120019 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f0 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f1 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f2 << 1), 0x00004444);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f3 << 1), 0x00008888);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f4 << 1), 0x00005555);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f5 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f6 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200f7 << 1), 0x0000f000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020025 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002002d << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012002d << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010020 << 1), 0x00000007);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011020 << 1), 0x00000007);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012020 << 1), 0x00000007);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013020 << 1), 0x00000007);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020020 << 1), 0x00000007);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110020 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111020 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112020 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113020 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00120020 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000101d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000101d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000111d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000111d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000121d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000121d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000131d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000131d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001100d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001100d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001101d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001101d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001110d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001110d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001111d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001111d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001120d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001120d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001121d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001121d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001130d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001130d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001131d0 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x001131d1 << 1), 0x00000100);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000101c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000101c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000102c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000102c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000103c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000103c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000104c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000104c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000105c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000105c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000106c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000106c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000107c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000107c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000108c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000108c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000111c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000111c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000112c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000112c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000113c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000113c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000114c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000114c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000115c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000115c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000116c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000116c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000117c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000117c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000118c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000118c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000121c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000121c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000122c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000122c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000123c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000123c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000124c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000124c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000125c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000125c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000126c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000126c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000127c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000127c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000128c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000128c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000131c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000131c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000132c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000132c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000133c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000133c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000134c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000134c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000135c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000135c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000136c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000136c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000137c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000137c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000138c0 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000138c1 << 1), 0x0000008e);
	mmio_write_16(cfg_base + 0x01000000 + (0x001100c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001100c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001101c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001101c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001102c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001102c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001103c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001103c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001104c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001104c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001105c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001105c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001106c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001106c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001107c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001107c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001108c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001108c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001110c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001110c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001111c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001111c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001112c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001112c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001113c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001113c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001114c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001114c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001115c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001115c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001116c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001116c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001117c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001117c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001118c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001118c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001120c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001120c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001121c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001121c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001122c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001122c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001123c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001123c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001124c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001124c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001125c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001125c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001126c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001126c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001127c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001127c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001128c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001128c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001130c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001130c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001131c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001131c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001132c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001132c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001133c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001133c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001134c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001134c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001135c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001135c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001136c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001136c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001137c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001137c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001138c0 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x001138c1 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010080 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010081 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010180 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010181 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011080 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011081 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011180 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011181 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012080 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012081 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012180 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012181 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013080 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013081 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013180 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013181 << 1), 0x00000453);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110080 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110081 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110180 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00110181 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111080 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111081 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111180 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00111181 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112080 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112081 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112180 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00112181 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113080 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113081 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113180 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00113181 << 1), 0x000001de);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090201 << 1), 0x00002600);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090202 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090203 << 1), 0x00003200);
	mmio_write_16(cfg_base + 0x01000000 + (0x00190201 << 1), 0x00002600);
	mmio_write_16(cfg_base + 0x01000000 + (0x00190202 << 1), 0x00000006);
	mmio_write_16(cfg_base + 0x01000000 + (0x00190203 << 1), 0x00003200);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020072 << 1), 0x00000003);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020073 << 1), 0x00000003);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100ae << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110ae << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120ae << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130ae << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100af << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110af << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120af << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130af << 1), 0x0000003e);
	mmio_write_16(cfg_base + 0x01000000 + (0x001100ae << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001110ae << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001120ae << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001130ae << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001100af << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001110af << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001120af << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x001130af << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100aa << 1), 0x00000703);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110aa << 1), 0x0000070f);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120aa << 1), 0x00000703);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130aa << 1), 0x0000070f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020077 << 1), 0x00000034);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002007c << 1), 0x00000054);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002007d << 1), 0x000002f2);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012007c << 1), 0x00000042);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012007d << 1), 0x00000bd2);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400c0 << 1), 0x0000010f);
	mmio_write_16(cfg_base + 0x01000000 + (0x000200cb << 1), 0x000061f0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090028 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000d0000 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090000 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090001 << 1), 0x00000400);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090002 << 1), 0x0000010e);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090003 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090004 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090005 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090029 << 1), 0x0000000b);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009002a << 1), 0x00000480);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009002b << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009002c << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009002d << 1), 0x00000448);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009002e << 1), 0x00000139);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009002f << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090030 << 1), 0x00000478);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090031 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090032 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090033 << 1), 0x000000e8);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090034 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090035 << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090036 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090037 << 1), 0x00000139);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090038 << 1), 0x0000000b);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090039 << 1), 0x000007c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009003a << 1), 0x00000139);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009003b << 1), 0x00000044);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009003c << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009003d << 1), 0x00000159);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009003e << 1), 0x0000014f);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009003f << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090040 << 1), 0x00000159);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090041 << 1), 0x00000047);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090042 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090043 << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090044 << 1), 0x0000004f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090045 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090046 << 1), 0x00000179);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090047 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090048 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090049 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009004a << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009004b << 1), 0x000007c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009004c << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009004d << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009004e << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009004f << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090050 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090051 << 1), 0x0000045a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090052 << 1), 0x00000009);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090053 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090054 << 1), 0x00000448);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090055 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090056 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090057 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090058 << 1), 0x00000179);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090059 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009005a << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009005b << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009005c << 1), 0x000040c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009005d << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009005e << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009005f << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090060 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090061 << 1), 0x00000048);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090062 << 1), 0x00004040);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090063 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090064 << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090065 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090066 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090067 << 1), 0x00000048);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090068 << 1), 0x00000040);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090069 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009006a << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009006b << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009006c << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009006d << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009006e << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009006f << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090070 << 1), 0x00000078);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090071 << 1), 0x00000549);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090072 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090073 << 1), 0x00000159);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090074 << 1), 0x00000d49);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090075 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090076 << 1), 0x00000159);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090077 << 1), 0x0000094a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090078 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090079 << 1), 0x00000159);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009007a << 1), 0x00000441);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009007b << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009007c << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009007d << 1), 0x00000042);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009007e << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009007f << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090080 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090081 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090082 << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090083 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090084 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090085 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090086 << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090087 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090088 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090089 << 1), 0x00000009);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009008a << 1), 0x000003c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009008b << 1), 0x00000149);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009008c << 1), 0x00000009);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009008d << 1), 0x000003c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009008e << 1), 0x00000159);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009008f << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090090 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090091 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090092 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090093 << 1), 0x000003c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090094 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090095 << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090096 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090097 << 1), 0x00000048);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090098 << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090099 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009009a << 1), 0x00000058);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009009b << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009009c << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009009d << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009009e << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009009f << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a0 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a1 << 1), 0x00000005);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a2 << 1), 0x000007c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a3 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040000 << 1), 0x00000811);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040020 << 1), 0x00000880);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040040 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040060 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040001 << 1), 0x00004008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040021 << 1), 0x00000083);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040041 << 1), 0x0000004f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040061 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040002 << 1), 0x00004040);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040022 << 1), 0x00000083);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040042 << 1), 0x00000051);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040062 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040003 << 1), 0x00000811);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040023 << 1), 0x00000880);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040043 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040063 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040004 << 1), 0x00000720);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040024 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040044 << 1), 0x00001740);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040064 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040005 << 1), 0x00000016);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040025 << 1), 0x00000083);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040045 << 1), 0x0000004b);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040065 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040006 << 1), 0x00000716);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040026 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040046 << 1), 0x00002001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040066 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040007 << 1), 0x00000716);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040027 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040047 << 1), 0x00002800);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040067 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040008 << 1), 0x00000716);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040028 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040048 << 1), 0x00000f00);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040068 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040009 << 1), 0x00000720);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040029 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040049 << 1), 0x00001400);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040069 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004000a << 1), 0x00000e08);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004002a << 1), 0x00000c15);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004004a << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004006a << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004000b << 1), 0x00000623);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004002b << 1), 0x00000015);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004004b << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004006b << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004000c << 1), 0x00004028);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004002c << 1), 0x00000080);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004004c << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004006c << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004000d << 1), 0x00000e08);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004002d << 1), 0x00000c1a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004004d << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004006d << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004000e << 1), 0x00000623);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004002e << 1), 0x0000001a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004004e << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004006e << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004000f << 1), 0x00004040);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004002f << 1), 0x00000080);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004004f << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004006f << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040010 << 1), 0x00002604);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040030 << 1), 0x00000015);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040050 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040070 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040011 << 1), 0x00000708);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040031 << 1), 0x00000005);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040051 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040071 << 1), 0x00002002);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040012 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040032 << 1), 0x00000080);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040052 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040072 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040013 << 1), 0x00002604);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040033 << 1), 0x0000001a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040053 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040073 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040014 << 1), 0x00000708);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040034 << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040054 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040074 << 1), 0x00002002);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040015 << 1), 0x00004040);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040035 << 1), 0x00000080);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040055 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040075 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040016 << 1), 0x0000060a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040036 << 1), 0x00000015);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040056 << 1), 0x00001200);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040076 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040017 << 1), 0x0000061a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040037 << 1), 0x00000015);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040057 << 1), 0x00001300);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040077 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040018 << 1), 0x0000060a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040038 << 1), 0x0000001a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040058 << 1), 0x00001200);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040078 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040019 << 1), 0x00000642);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040039 << 1), 0x0000001a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040059 << 1), 0x00001300);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040079 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004001a << 1), 0x00004808);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004003a << 1), 0x00000880);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004005a << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0004007a << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a4 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a5 << 1), 0x00000790);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a6 << 1), 0x0000011a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a7 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a8 << 1), 0x000007aa);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900a9 << 1), 0x0000002a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900aa << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ab << 1), 0x000007b2);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ac << 1), 0x0000002a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ad << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ae << 1), 0x000007c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900af << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b0 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b1 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b2 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b3 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b4 << 1), 0x000002a8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b5 << 1), 0x00000129);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b6 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b7 << 1), 0x00000370);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b8 << 1), 0x00000129);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b9 << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ba << 1), 0x000003c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900bb << 1), 0x000001a9);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900bc << 1), 0x0000000c);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900bd << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900be << 1), 0x00000199);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900bf << 1), 0x00000014);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c0 << 1), 0x00000790);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c1 << 1), 0x0000011a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c2 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c3 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c4 << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c5 << 1), 0x0000000e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c6 << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c7 << 1), 0x00000199);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c8 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900c9 << 1), 0x00008568);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ca << 1), 0x00000108);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900cb << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900cc << 1), 0x00000790);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900cd << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ce << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900cf << 1), 0x000001d8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d0 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d1 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d2 << 1), 0x00008558);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d3 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d4 << 1), 0x00000070);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d5 << 1), 0x00000788);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d6 << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d7 << 1), 0x00001ff8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d8 << 1), 0x000085a8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900d9 << 1), 0x000001e8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900da << 1), 0x00000050);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900db << 1), 0x00000798);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900dc << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900dd << 1), 0x00000060);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900de << 1), 0x000007a0);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900df << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e0 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e1 << 1), 0x00008310);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e2 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e3 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e4 << 1), 0x0000a310);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e5 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e6 << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e7 << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e8 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900e9 << 1), 0x0000006e);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ea << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900eb << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ec << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ed << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ee << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ef << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f0 << 1), 0x00008310);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f1 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f2 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f3 << 1), 0x0000a310);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f4 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f5 << 1), 0x00001ff8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f6 << 1), 0x000085a8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f7 << 1), 0x000001e8);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f8 << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900f9 << 1), 0x00000798);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900fa << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900fb << 1), 0x00000078);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900fc << 1), 0x000007a0);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900fd << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900fe << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900ff << 1), 0x00000790);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090100 << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090101 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090102 << 1), 0x00008b10);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090103 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090104 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090105 << 1), 0x0000ab10);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090106 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090107 << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090108 << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090109 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009010a << 1), 0x00000058);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009010b << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009010c << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009010d << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009010e << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009010f << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090110 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090111 << 1), 0x00008b10);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090112 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090113 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090114 << 1), 0x0000ab10);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090115 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090116 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090117 << 1), 0x000001d8);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090118 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090119 << 1), 0x00000080);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009011a << 1), 0x00000790);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009011b << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009011c << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009011d << 1), 0x000007aa);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009011e << 1), 0x0000006a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009011f << 1), 0x0000000a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090120 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090121 << 1), 0x000001e9);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090122 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090123 << 1), 0x00008080);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090124 << 1), 0x00000108);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090125 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090126 << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090127 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090128 << 1), 0x0000000c);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090129 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009012a << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009012b << 1), 0x00000009);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009012c << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009012d << 1), 0x000001a9);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009012e << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009012f << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090130 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090131 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090132 << 1), 0x00008080);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090133 << 1), 0x00000108);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090134 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090135 << 1), 0x000007aa);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090136 << 1), 0x0000006a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090137 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090138 << 1), 0x00008568);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090139 << 1), 0x00000108);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009013a << 1), 0x000000b7);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009013b << 1), 0x00000790);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009013c << 1), 0x0000016a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009013d << 1), 0x0000001f);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009013e << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009013f << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090140 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090141 << 1), 0x00008558);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090142 << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090143 << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090144 << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090145 << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090146 << 1), 0x0000000c);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090147 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090148 << 1), 0x00000068);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090149 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009014a << 1), 0x00000408);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009014b << 1), 0x00000169);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009014c << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009014d << 1), 0x00008558);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009014e << 1), 0x00000168);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009014f << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090150 << 1), 0x000003c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090151 << 1), 0x000001a9);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090152 << 1), 0x00000003);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090153 << 1), 0x00000370);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090154 << 1), 0x00000129);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090155 << 1), 0x00000020);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090156 << 1), 0x000002aa);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090157 << 1), 0x00000009);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090158 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090159 << 1), 0x00000400);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009015a << 1), 0x0000010e);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009015b << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009015c << 1), 0x000000e8);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009015d << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009015e << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009015f << 1), 0x00008140);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090160 << 1), 0x0000010c);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090161 << 1), 0x00000010);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090162 << 1), 0x00008138);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090163 << 1), 0x0000010c);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090164 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090165 << 1), 0x000007c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090166 << 1), 0x00000101);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090167 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090168 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090169 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009016a << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009016b << 1), 0x00000448);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009016c << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009016d << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009016e << 1), 0x000007c0);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009016f << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090170 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090171 << 1), 0x000000e8);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090172 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090173 << 1), 0x00000047);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090174 << 1), 0x00000630);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090175 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090176 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090177 << 1), 0x00000618);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090178 << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090179 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009017a << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009017b << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009017c << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009017d << 1), 0x000007c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009017e << 1), 0x00000109);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009017f << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090180 << 1), 0x00008140);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090181 << 1), 0x0000010c);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090182 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090183 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090184 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090185 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090186 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090187 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090188 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090189 << 1), 0x000007c8);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009018a << 1), 0x00000101);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090006 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090007 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090008 << 1), 0x00000008);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090009 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009000a << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009000b << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000d00e7 << 1), 0x00000400);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090017 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009001f << 1), 0x00000029);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090026 << 1), 0x0000006a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d0 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d1 << 1), 0x00000101);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d2 << 1), 0x00000105);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d3 << 1), 0x00000107);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d4 << 1), 0x0000010f);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d5 << 1), 0x00000202);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d6 << 1), 0x0000020a);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400d7 << 1), 0x0000020b);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002003a << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002000b << 1), 0x00000085);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002000c << 1), 0x0000010b);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002000d << 1), 0x00000a75);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002000e << 1), 0x0000002c);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012000b << 1), 0x00000021);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012000c << 1), 0x00000042);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012000d << 1), 0x0000029b);
	mmio_write_16(cfg_base + 0x01000000 + (0x0012000e << 1), 0x0000002c);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009000c << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009000d << 1), 0x00000173);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009000e << 1), 0x00000060);
	mmio_write_16(cfg_base + 0x01000000 + (0x0009000f << 1), 0x00006110);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090010 << 1), 0x00002152);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090011 << 1), 0x0000dfbd);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090012 << 1), 0x0000ffff);
	mmio_write_16(cfg_base + 0x01000000 + (0x00090013 << 1), 0x00006152);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040080 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040081 << 1), 0x00000012);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040082 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040083 << 1), 0x00000012);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040084 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00040085 << 1), 0x00000012);
	mmio_write_16(cfg_base + 0x01000000 + (0x00140080 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00140081 << 1), 0x00000012);
	mmio_write_16(cfg_base + 0x01000000 + (0x00140082 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00140083 << 1), 0x00000012);
	mmio_write_16(cfg_base + 0x01000000 + (0x00140084 << 1), 0x000000e0);
	mmio_write_16(cfg_base + 0x01000000 + (0x00140085 << 1), 0x00000012);
	mmio_write_16(cfg_base + 0x01000000 + (0x000400fd << 1), 0x0000000f);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010011 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010012 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010013 << 1), 0x00000180);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010018 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00010002 << 1), 0x00006209);
	mmio_write_16(cfg_base + 0x01000000 + (0x000100b2 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000101b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000102b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000103b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000104b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000105b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000106b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000107b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000108b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011011 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011012 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011013 << 1), 0x00000180);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011018 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00011002 << 1), 0x00006209);
	mmio_write_16(cfg_base + 0x01000000 + (0x000110b2 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000111b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000112b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000113b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000114b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000115b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000116b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000117b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000118b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012011 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012012 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012013 << 1), 0x00000180);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012018 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00012002 << 1), 0x00006209);
	mmio_write_16(cfg_base + 0x01000000 + (0x000120b2 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000121b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000122b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000123b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000124b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000125b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000126b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000127b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000128b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013011 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013012 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013013 << 1), 0x00000180);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013018 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00013002 << 1), 0x00006209);
	mmio_write_16(cfg_base + 0x01000000 + (0x000130b2 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000131b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000132b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000133b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000134b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000135b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000136b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000137b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000138b4 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020089 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020088 << 1), 0x00000019);
	mmio_write_16(cfg_base + 0x01000000 + (0x000c0080 << 1), 0x00000002);
	mmio_write_16(cfg_base + 0x01000000 + (0x000d0000 << 1), 0x00000001);
	mmio_write_16(cfg_base + 0x01000000 + (0x000d0000 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b6 << 1), 0x00000004);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b7 << 1), 0x00000000);
	mmio_write_16(cfg_base + 0x01000000 + (0x000900b8 << 1), 0x00000018);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020010 << 1), 0x0000006a);
	mmio_write_16(cfg_base + 0x01000000 + (0x00020010 << 1), 0x0000006a);
	mmio_write_16(cfg_base + 0x01000000 + (0x0002001d << 1), 0x00000001);

	/*
	 * Wait for impedance calibration to complete one round of
	 * calbiation by polling CalBusy CSR to be 0
	 */
	do {
		read_data =
		    mmio_read_16(cfg_base + 0x01000000 + (0x00020097 << 1));
	} while ((read_data & 0x00000001) != 0);
#endif
	// phy is ready for initial dfi_init_start request
	// set umctl2 to tigger dfi_init_start
	mmio_write_32(cfg_base + 0x000001b0, 0x00000060);

	// wait for dfi_init_complete to be 1
	do {
		read_data = mmio_read_32(cfg_base + 0x000001bc);
	} while ((read_data & 0x00000001) != 1);

	// deassert dfi_init_start, and enable the act on dfi_init_complete
	mmio_write_32(cfg_base + 0x000001b0, 0x00000041);

	// dynamic group0 wakeup
	mmio_write_32(cfg_base + 0x320, 0x00000001);
	do {
		read_data = mmio_read_32(cfg_base + 0x324);
	} while ((read_data & 0x00000001) != 1);

	// waiting controller in normal mode
	do {
		read_data = mmio_read_32(cfg_base + 0x004);
	} while ((read_data & 0x00000001) != 1);

	/*
	 * set selfref_en, and en_dfi_dram_clk_disable again, recover it,
	 * in reset_dut_do_training in ddrc_env
	 */
	mmio_write_32(cfg_base + 0x00000030, 0x00000000);
#if 0
#ifdef DDR_ECC_ENABLE
	/*
	 * in inline-ECC configuration, trigger the ECC Scrubber to
	 * initialize the dram (ECC protected region) close the AXI
	 * port of DDR controller, to make sure no axi transaction
	 * is accepted to DDR controller before DDR initialize is done
	 */
	mmio_write_32(cfg_base + 0x00000490, 0x00000000);
	mmio_write_32(cfg_base + 0x00000540, 0x00000000);
	mmio_write_32(cfg_base + 0x000005f0, 0x00000000);
	mmio_write_32(cfg_base + 0x000006a0, 0x00000000);
	// set SBRCTL.scrub_mode = 1, SBRCTL.scrub_interval = 0;
	/*
	 * don't need to set SBRWDATA0 again, since it has been programmed
	 * to expected value
	 */
	mmio_write_32(cfg_base + 0x00000f24, 0x04);
	// set SBRCTL.scrub_en = 0
	mmio_write_32(cfg_base + 0x00000f24, 0x05);
	// poll SBRSTAT.scrub_done = 1
	do {
		read_data = mmio_read_32(cfg_base + 0xf28);
	} while ((read_data & 0x00000002) != 0x00000002);
	// poll SBRSTAT.scrub_busy = 0
	do {
		read_data = mmio_read_32(cfg_base + 0xf28);
	} while ((read_data & 0x00000001) != 0);
	// disable SBR
	mmio_write_32(cfg_base + 0x00000f24, 0x0001ff00);
	// re-enable the axi port
	mmio_write_32(cfg_base + 0x00000490, 0x00000001);
	mmio_write_32(cfg_base + 0x00000540, 0x00000001);
	mmio_write_32(cfg_base + 0x000005f0, 0x00000001);
	mmio_write_32(cfg_base + 0x000006a0, 0x00000001);
#endif
#endif
}

void bm_ddr_init_pld(void)
{
#ifdef DDR_PHY_ENABLE
	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST0,
			BIT_MASK_TOP_SOFT_RST0_DDRC);
#endif
	ddr_init(DDR_CTRL2);
	ddr_init(DDR_CTRL0_A);
	ddr_init(DDR_CTRL0_B);
	ddr_init(DDR_CTRL1);

	//NOTICE("LPDDR4 init done\n");

#ifdef DDR_ECC_ENABLE
	sysdma_init();
	NOTICE("SYSDMA write ddr for ecc init...");
	bm_sysdma_memcpy(NS_SRAM_UNUSED_BASE, 0x100000000, 0x100000, 0);
	//NOTICE("Done.\n");
#endif
}
#endif

