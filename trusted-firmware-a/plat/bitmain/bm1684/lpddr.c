/*
 * Copyright (c) 2015-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <lib/mmio.h>
#include <common/debug.h>
#include <platform_def.h>
#include <drivers/delay_timer.h>
#include <drivers/bitmain/i2c.h>
#include <drivers/sophgo/dma/sysdma.h>
#include <bm_sd.h>
#include "bm_common.h"
#include "bm_clock.h"
#include <lib/fatfs/ff.h>
#include "lpddr.h"
#include "lpddr_init.h"

#ifdef LPDDR_DEUBG
#define lpddr_print(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define lpddr_print(fmt, ...)
#endif
#define T1D 0
#define T2D 1

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
#ifdef LPDDR_DATA_IN_SD_FLASH
static struct init_data phy_initial_data[phy_initial_data_size / sizeof(struct init_data)];
static uint16_t lpddr4x_train1d_imem[train1d_imem_size / sizeof(uint16_t)];
static uint16_t lpddr4x_train1d_dmem[train1d_dmem_size / sizeof(uint16_t)];
static uint16_t lpddr4x_train2d_imem[train2d_imem_size / sizeof(uint16_t)];
static uint16_t lpddr4x_train2d_dmem[train2d_dmem_size / sizeof(uint16_t)];
static struct dwc_reg_data phy_pie_data[phy_pie_data_size / sizeof(struct dwc_reg_data)];

static void load_ddr_setting(void)
{
	char *ptr;
	int j, k;
	char *ddr_array[DDR_ARRAY_NUM];
	int ddr_array_size[DDR_ARRAY_NUM];

	ddr_array[0] = (char *)phy_initial_data;
	ddr_array[1] = (char *)lpddr4x_train1d_imem;
	ddr_array[2] = (char *)lpddr4x_train1d_dmem;
	ddr_array[3] = (char *)lpddr4x_train2d_imem;
	ddr_array[4] = (char *)lpddr4x_train2d_dmem;
	ddr_array[5] = (char *)phy_pie_data;

	ddr_array_size[0] = sizeof(phy_initial_data);
	ddr_array_size[1] = sizeof(lpddr4x_train1d_imem);
	ddr_array_size[2] = sizeof(lpddr4x_train1d_dmem);
	ddr_array_size[3] = sizeof(lpddr4x_train2d_imem);
	ddr_array_size[4] = sizeof(lpddr4x_train2d_dmem);
	ddr_array_size[5] = sizeof(phy_pie_data);

	if (((bm_gpio_read(BIT_MASK_GPIO_BOOT_SEL) & BOOTSEL_SKIP_SD) == 0) &&
	    bm_sd_card_detect() &&
	    (bm_sd_init(0) == 0)) {
		FRESULT f_ret;
		FATFS SDC_FS;
		FIL fp;
		UINT size;

		NOTICE("found sdcard\n");
		f_ret = f_mount(&SDC_FS, "0:", 1);
		if (f_ret != FR_OK) {
			ERROR("mount SD card failed\n");
			goto sd_wrong;
		}
		f_ret = f_open(&fp, "0:ddr.bin", FA_READ);
		if (f_ret == FR_OK) {
			NOTICE("found ddr.bin\n");
			ptr = (char *)NS_SRAM_BASE;
			f_read(&fp, ptr, ddr_array_total_size, &size);
			if (size != ddr_array_total_size) {
				ERROR("DDR file size not match: %d/%d\n", size, ddr_array_total_size);
				f_close(&fp);
				f_unmount("0:");
				goto sd_wrong;
			}
			f_close(&fp);
		} else {
			ERROR("SD card has no DDR file\n");
			f_unmount("0:");
			goto sd_wrong;
		}
		f_unmount("0:");
		goto sd_good;
	}
sd_wrong:
	// if something wrong with SD, fall back to SPI flash
	ptr = (char *)(SPIF_BASE + SPIF_DDR_SETTING_OFFSET);
	NOTICE("ddr.bin data in spiflash\n");
sd_good:
	for (j = 0; j < DDR_ARRAY_NUM; j++) {
		NOTICE("DDR array %d size %d\n", j, ddr_array_size[j]);
		for (k = 0; k < ddr_array_size[j]; k++) {
		//	NOTICE("arry[%d] = 0x%x\n", k, *(ptr));
			*((char *)ddr_array[j] + k) = *(ptr++);
		}
	}
}
#endif

static inline void opdelay(uint32_t times)
{
	while (times--)
		__asm__ volatile("nop");
}

static inline void dwc_phy_apb_write16(uintptr_t base, uint32_t offset, uint16_t value)
{
	mmio_write_16(base + PHY_OFFSET + (offset << 1), value);
}

static inline uint16_t dwc_phy_apb_read16(uintptr_t base, uint32_t offset)
{
	return mmio_read_16(base + PHY_OFFSET + (offset << 1));
}

static uint32_t dwc_get_mail(uint32_t cfg_base, uint32_t mode)
{
	uint32_t mail;

	while (dwc_phy_apb_read16(cfg_base, UCT_SHANDOW_REG) &
		UCT_WRITE_PROT_SHADOW)
		;

	mail = dwc_phy_apb_read16(cfg_base, UCT_WRITE_ONLY_SHADOW_REG);

	if (mode == STREAM_MSG)
		mail |= (dwc_phy_apb_read16(cfg_base, UCT_DATWRITE_ONLY_SHADOW_REG) << 16);

	dwc_phy_apb_write16(cfg_base, DCT_WRITE_PROT_REG, 0);

	while (!(dwc_phy_apb_read16(cfg_base, UCT_SHANDOW_REG) &
		UCT_WRITE_PROT_SHADOW))
		;

	dwc_phy_apb_write16(cfg_base, DCT_WRITE_PROT_REG, 1);

	return mail;
}

static void dwc_decode_stream_msg(uint32_t cfg_base, uint32_t train_2d)
{
	uint32_t i, args __attribute__((unused));
	uint32_t str_stream_index = dwc_get_mail(cfg_base, STREAM_MSG);

	lpddr_print("%s str_stream_index 0x%08x\n", train_2d ? "2D" : "1D",
		    str_stream_index);
	i = 0;
	while (i < (str_stream_index & 0xffff)) {
		args = dwc_get_mail(cfg_base, STREAM_MSG);
		lpddr_print("args 0x%02x\n", args);
		i++;
	}
}

static void dwc_decode_major_msg(uint32_t msg)
{
	lpddr_print("dwc phy message major message type: 0x%x, %s\n", msg,
		    msg == FW_COMPLET_SUCCESS ? "success" :
						msg == FW_COMPLET_FAILED ? "failed" : "unknown");
}

#define mask_train_result(v, index, phase, result)	\
	({                                        \
		(v) &= ~(1UL << (((index) << 1) + (phase)));	\
		(v) |= (((result) & 0x1) << (((index) << 1) + (phase))); \
	})

static uint32_t failmap;
static uint32_t dwc_train_status(uint32_t cfg_base, uint32_t train_2d, uint32_t result)
{
	uint32_t pass_or_fail = result == 0xff ? 1 : 0;
	uint32_t index;

	index = cfg_base == DDR_CTRL0_A ? DDR_CTRL0_A_INDEX
		: cfg_base == DDR_CTRL0_B ? DDR_CTRL0_B_INDEX
		: cfg_base == DDR_CTRL1 ? DDR_CTRL1_INDEX
		: DDR_CTRL2_INDEX;

	mask_train_result(failmap, index, train_2d, pass_or_fail);

	return failmap;
}

static void dwc_read_msgblock_msg(uint32_t cfg_base, uint32_t train_2d)
{
	uint32_t mail;

loop:
	mail = dwc_get_mail(cfg_base, MAJOR_MSG);
	if (mail == STREAM_MSG)
		dwc_decode_stream_msg(cfg_base, train_2d);
	else
		dwc_decode_major_msg(mail);

	if (mail != 0x7 && mail != 0xff)
		goto loop;

	if (mail == 0xff) {
		ERROR("Lpddr train failed, ddr: %s, phase: %d\n",
		      cfg_base == DDR_CTRL0_A ? "0A"
		      : cfg_base == DDR_CTRL0_B ? "0B"
		      : cfg_base == DDR_CTRL1 ? "1"
		      : "2", train_2d);
	}

	dwc_train_status(cfg_base, train_2d, mail);
}

static inline void dwc_exec_fw(uint32_t cfg_base, uint32_t train_2d)
{
	lpddr_print("ddr: %s\n", cfg_base == DDR_CTRL0_A ? "0A" :
		cfg_base == DDR_CTRL0_B ? "0B" :
		cfg_base == DDR_CTRL1 ? "1" : "2");

	// DWC_DDRPHYA_APBONLY0_MicroContMuxSel
	dwc_phy_apb_write16(cfg_base, 0xd0000, 0x1);

	//1.  Reset the firmware microcontroller by writing
	// the MicroReset CSR to set the StallToMicro and
	// ResetToMicro fields to 1 (all other fields should be zero).
	// Then rewrite the CSR so that only the StallToMicro remains set
	// (all other fields should be zero).
	dwc_phy_apb_write16(cfg_base, 0xd0000, 0x1);
	// DWC_DDRPHYA_APBONLY0_MicroReset
	dwc_phy_apb_write16(cfg_base, 0xd0099, 0x9);
	// DWC_DDRPHYA_APBONLY0_MicroReset
	dwc_phy_apb_write16(cfg_base, 0xd0099, 0x1);

	// 2. Begin execution of the training firmware
	// by setting the MicroReset CSR to 4'b0000.
	dwc_phy_apb_write16(cfg_base, 0xd0099, 0x0);

	dwc_read_msgblock_msg(cfg_base, train_2d);

	// 4.Halt the microcontroller."
	// DWC_DDRPHYA_APBONLY0_MicroReset
	dwc_phy_apb_write16(cfg_base, 0xd0099, 0x1);
}

static uint32_t ddr_training(uint32_t cfg_base, uint32_t train)
{
	uint32_t i, train_addr;

	if (train == T1D) {
		//2 load 1d-imem
		train_addr = TARIN_IMEM_OFFSET;
		//Programming MemResetL to 0x2
		dwc_phy_apb_write16(cfg_base, MEM_RSETE_L, 0x2);
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 0);
		for (i = 0; i < ARRAY_SIZE(lpddr4x_train1d_imem); i++, train_addr++)
			dwc_phy_apb_write16(cfg_base, train_addr, lpddr4x_train1d_imem[i]);
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 1);

		//3 set dfi clock
		lpddr_print("phy load dmem\n");

		//4 load 1d-dmem
		train_addr = TARIN_DMEM_OFFSET;
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 0);
		for (i = 0; i < ARRAY_SIZE(lpddr4x_train1d_dmem); i++, train_addr++)
			dwc_phy_apb_write16(cfg_base, train_addr, lpddr4x_train1d_dmem[i]);
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 1);

		lpddr_print("phy run firmware\n");

		dwc_exec_fw(cfg_base, T1D);

	} else {
		//6 load 2d-imem
		train_addr = TARIN_IMEM_OFFSET;
		dwc_phy_apb_write16(cfg_base, MEM_RSETE_L, 0x2);
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 0);
		for (i = 0; i < ARRAY_SIZE(lpddr4x_train2d_imem); i++, train_addr++)
			dwc_phy_apb_write16(cfg_base, train_addr, lpddr4x_train2d_imem[i]);
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 1);

		//7 load 2d-dmem
		train_addr = TARIN_DMEM_OFFSET;
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 0);
		for (i = 0; i < ARRAY_SIZE(lpddr4x_train2d_dmem); i++, train_addr++)
			dwc_phy_apb_write16(cfg_base, train_addr, lpddr4x_train2d_dmem[i]);
		dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 1);

		dwc_exec_fw(cfg_base, T2D);
	}

	return 0;
}

static uint32_t ddr_phy_enter_mission(uint32_t cfg_base, uint32_t ddr_index)
{
	uint32_t i;
	uint32_t read_data;

	//5 set dfi clock highest
	lpddr_print("phy load pie\n");

	dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 0);
	for (i = 0; i < ARRAY_SIZE(phy_pie_data); i++)
		dwc_phy_apb_write16(cfg_base, phy_pie_data[i].offset, phy_pie_data[i].value);
	dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 1);

	lpddr_print("phy run firmware\n");

	lpddr_print("Wait for impedance calibration\n");

	// Wait for impedance calibration to complete one round
	// of calbiation by polling CalBusy CSR to be 0
	do {
		read_data = dwc_phy_apb_read16(cfg_base, 0x00020097);
	} while ((read_data & 0x00000001) != 0);
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

	// set selfref_en, and en_dfi_dram_clk_disable again,
	// recover it, in reset_dut_do_training in ddrc_env
	mmio_write_32(cfg_base + 0x00000030, 0x00000001);
	mmio_write_32(cfg_base + 0x00000030, 0x00000000);
#if 0
#ifdef __DDR_ECC_ENABLE__
	// in inline-ECC configuration, trigger the ECC
	// Scrubber to initialize the dram (ECC protected region)
	// close the AXI port of DDR controller, to make sure no axi
	// transaction is accepted to DDR controller
	// before DDR initialize is done
	mmio_write_32(cfg_base + 0x00000490, 0x00000000);
	mmio_write_32(cfg_base + 0x00000540, 0x00000000);
	mmio_write_32(cfg_base + 0x000005f0, 0x00000000);
	mmio_write_32(cfg_base + 0x000006a0, 0x00000000);
	// set SBRCTL.scrub_mode = 1, SBRCTL.scrub_interval = 0;
	// don't need to set SBRWDATA0 again, since it has been
	// programmed to expected value
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
	return 0;
}

static void ddr_pin_swap(uint32_t cfg_base, uint32_t ddr_index)
{
	uint32_t i;
	struct dwc_reg_data *pin_swap[4];

	if (bm_get_chip_id() == CHIP_BM1684) {
		pin_swap[0] = pin_swap_1684_0;
		pin_swap[1] = pin_swap_1684_1;
		pin_swap[2] = pin_swap_1684_2;
		pin_swap[3] = pin_swap_1684_3;
	} else {
		pin_swap[0] = pin_swap_1684x_0;
		pin_swap[1] = pin_swap_1684x_1;
		pin_swap[2] = pin_swap_1684x_2;
		pin_swap[3] = pin_swap_1684x_3;
	}

	//0 pin swap
	lpddr_print("phy pin swap\n");
	dwc_phy_apb_write16(cfg_base, MICRO_CONT_MUX_SEL, 0);

	if (ddr_index == DDR_CTRL0_A_INDEX) {
		for (i = 0; i < ARRAY_SIZE(pin_swap_1684_0); i++)
			dwc_phy_apb_write16(cfg_base, pin_swap[0][i].offset, pin_swap[0][i].value);
	} else if (ddr_index == DDR_CTRL0_B_INDEX) {
		for (i = 0; i < ARRAY_SIZE(pin_swap_1684_1); i++)
			dwc_phy_apb_write16(cfg_base, pin_swap[1][i].offset, pin_swap[1][i].value);
	} else if (ddr_index == DDR_CTRL1_INDEX) {
		for (i = 0; i < ARRAY_SIZE(pin_swap_1684_2); i++)
			dwc_phy_apb_write16(cfg_base, pin_swap[2][i].offset, pin_swap[2][i].value);
	} else if (ddr_index == DDR_CTRL2_INDEX) {
		for (i = 0; i < ARRAY_SIZE(pin_swap_1684_3); i++)
			dwc_phy_apb_write16(cfg_base, pin_swap[3][i].offset, pin_swap[3][i].value);
	}
}

static uint32_t ddr_phy_init(uint32_t cfg_base, uint32_t ddr_index)
{
	uint32_t i;
	uint32_t read_data;

	// 1. Assert the core_ddrc_rstn and areset_n resets
	// (ddrc reset, and axi reset)
	// 2. assert the preset
	// 3. start the clocks (pclk, core_ddrc_clk, aclk_n)
	// 4. Deassert presetn once the clocks are active and stable
	// 5. allow 128 cycle for synchronization of presetn to
	// core_ddrc_core_clk and aclk domain and to
	//    permit initialization of end logic
	// 6. Initialize the registers
	// 7. Deassert the resets

	// Assert core_ddrc_rstn, areset_n
	//bit 3:6 -> ddr0a/ddr0b/ddr1/ddr2 soft-reset
	read_data = mmio_read_32(0x50010c00);
	read_data = read_data & (~(1 << (3 + ddr_index)));
	mmio_write_32(0x50010c00, read_data);
	opdelay(50);
	// assert preset
	//bit 7:10 -> ddr0a/ddr0b/ddr1/ddr2 apb-reset
	read_data = mmio_read_32(0x50010c00);
	mmio_write_32(0x50010c00, read_data & ~(1 << (7 + ddr_index)));
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

	for (i = 0; i < ARRAY_SIZE(cfg_data); i++)
		mmio_write_32(cfg_base + cfg_data[i].offset, cfg_data[i].value);

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
	//bit 3:6 -> ddr0a/ddr0b/ddr1/ddr2 soft-reset
	read_data = mmio_read_32(0x50010c00);
	read_data = read_data | (1 << (3 + ddr_index));
	mmio_write_32(0x50010c00, read_data);
	opdelay(50);

	// enable the reigster access for dynamic register
	// APB_QUASI_DYN_G0_SLEEP
	mmio_write_32(cfg_base + 0x00000320, 0x00000000);

	// set dfi_init_complete_en, for phy initialization
	mmio_write_32(cfg_base + 0x000001b0, 0x00000040);

	//DDR_PHY_ENABLE
	ddr_pin_swap(cfg_base, ddr_index);
	lpddr_print("phy pll\n");

	//pll only for 2400
	//1 phy initial

	for (i = 0; i < ARRAY_SIZE(phy_initial_data); i++)
		dwc_phy_apb_write16(cfg_base, phy_initial_data[i].offset,
				    phy_initial_data[i].value);

	dwc_phy_apb_write16(cfg_base, 0x200ca, 0x124);
	dwc_phy_apb_write16(cfg_base, 0x200c7, 0x20);
	//dwc_phy_apb_write16(cfg_base, 0x200c5, 0xa);
	dwc_phy_apb_write16(cfg_base, 0x200cc, 0x17f);

	lpddr_print("phy initial\n");
	return 0;
}

/*
 * ddr0a/ddr0b share a hardware reset signal,
 * ddr1/ddr2 share another.
 * the initial sequency should be 0a->0b, 1->2
 * so we put 0a/0b 1/2 in 2 groups.
 */
static void ddr_group_init(uint32_t group)
{
	if (group == GROUP0) {
		//phy init
		ddr_phy_init(DDR_CTRL0_A, DDR_CTRL0_A_INDEX);
		ddr_phy_init(DDR_CTRL0_B, DDR_CTRL0_B_INDEX);
		//1d train
		ddr_training(DDR_CTRL0_A, T1D);
		ddr_training(DDR_CTRL0_B, T1D);
		//2d train
		ddr_training(DDR_CTRL0_A, T2D);
		ddr_training(DDR_CTRL0_B, T2D);
	} else {
		ddr_phy_init(DDR_CTRL1, DDR_CTRL1_INDEX);
		ddr_phy_init(DDR_CTRL2, DDR_CTRL2_INDEX);

		ddr_training(DDR_CTRL1, T1D);
		ddr_training(DDR_CTRL2, T1D);

		ddr_training(DDR_CTRL1, T2D);
		ddr_training(DDR_CTRL2, T2D);
	}
}

void dwc_phy_enter_mission(void)
{
	ddr_phy_enter_mission(DDR_CTRL0_A, DDR_CTRL0_A_INDEX);
	ddr_phy_enter_mission(DDR_CTRL0_B, DDR_CTRL0_B_INDEX);
	ddr_phy_enter_mission(DDR_CTRL1, DDR_CTRL1_INDEX);
	ddr_phy_enter_mission(DDR_CTRL2, DDR_CTRL2_INDEX);
}

static struct pll_freq_table freq_table[] = {
	{ FREQ_2400M, 600 * mhz }, //2400M
	{ FREQ_3600M, 900 * mhz }, //3600M
	{ FREQ_4000M, 1000 * mhz }, //4000M
	{ FREQ_4266M, 1062 * mhz }, //4266M
};

static inline void ddr_pll_setting(uint32_t freq)
{
	uint32_t i;

	for (i = 0; i < ARRAY_SIZE(freq_table); i++)
		if (freq_table[i].freq == freq)
			goto do_set;

	NOTICE("No support freq\n");
	return;

do_set:
	clk_set_rate(DPLL0_CLK, freq_table[i].rate);
	clk_set_rate(DPLL1_CLK, freq_table[i].rate);
}

static void dwc_pre_setting(uint32_t is_lpddr4, uint32_t rank, uint32_t freq, uint32_t group)
{
	uint32_t i, count;
	struct dwc_precfg_freq *cfg_freq = NULL;
	struct dwc_precfg_rank *cfg_rank = NULL;
#ifdef DDR_ECC_ENABLE
	struct init_data *cfg_ecc = NULL;
	uint32_t ecc_array_size;
#endif

	for (i = 0; i < ARRAY_SIZE(pre_cfg_rank); i++) {
		if (rank == pre_cfg_rank[i].rank_num)
			cfg_rank = &pre_cfg_rank[i];
	}

	for (i = 0; i < ARRAY_SIZE(pre_cfg_freq); i++) {
		if (freq == pre_cfg_freq[i].frequency)
			cfg_freq = &pre_cfg_freq[i];
	}

	if (!cfg_freq || !cfg_rank)
		ERROR("lpddr4/4x can't get configuration\n");

	//override phy
	for (count = 0; count < ARRAY_SIZE(cfg_freq->phy_freq_data); count++) {
		for (i = 0; i < ARRAY_SIZE(phy_initial_data); i++)
			if (phy_initial_data[i].offset == cfg_freq->phy_freq_data[count].offset) {
				phy_initial_data[i].value = cfg_freq->phy_freq_data[count].value;
				break;
			}
	}

	//override pie
	for (count = 0; count < ARRAY_SIZE(cfg_freq->pie_freq_data); count++) {
		for (i = 0; i < ARRAY_SIZE(phy_pie_data); i++)
			if (phy_pie_data[i].offset == cfg_freq->pie_freq_data[count].offset) {
				phy_pie_data[i].value = cfg_freq->pie_freq_data[count].value;
				break;
			}
	}

	//override train 1d
	for (count = 0; count < ARRAY_SIZE(cfg_freq->train1d_dmem_freq_data); count++) {
		i = cfg_freq->train1d_dmem_freq_data[count].offset;
		lpddr4x_train1d_dmem[i] = cfg_freq->train1d_dmem_freq_data[count].value;
	}

	//override train 2d
	for (count = 0; count < ARRAY_SIZE(cfg_freq->train2d_dmem_freq_data); count++) {
		i = cfg_freq->train2d_dmem_freq_data[count].offset;
		lpddr4x_train2d_dmem[i] = cfg_freq->train2d_dmem_freq_data[count].value;
	}

	//override train 1d rank
	for (count = 0; count < ARRAY_SIZE(cfg_rank->train1d_dmem_rank_data); count++) {
		i = cfg_rank->train1d_dmem_rank_data[count].offset;
		lpddr4x_train1d_dmem[i] = cfg_rank->train1d_dmem_rank_data[count].value;
	}

	//override train 2d rank
	for (count = 0; count < ARRAY_SIZE(cfg_rank->train2d_dmem_rank_data); count++) {
		i = cfg_rank->train2d_dmem_rank_data[count].offset;
		lpddr4x_train2d_dmem[i] = cfg_rank->train2d_dmem_rank_data[count].value;
	}

	//override cfg rank
	cfg_data[0].value = cfg_rank->cfg_rank;

#ifdef DDR_ECC_ENABLE
	if (rank == RANK1) {
		cfg_ecc = cfg_ecc_1rank;
		ecc_array_size = ARRAY_SIZE(cfg_ecc_1rank);
	} else if (rank == RANK2) {
		cfg_ecc = cfg_ecc_2rank;
		ecc_array_size = ARRAY_SIZE(cfg_ecc_2rank);
	}

	for (count = 0; count < ecc_array_size; count++) {
		for (i = 0; i < ARRAY_SIZE(cfg_data); i++) {
			if (cfg_data[i].offset == cfg_ecc[count].offset) {
				cfg_data[i].value = cfg_ecc[count].value;
				break;
			}
		}
	}
#endif

	/*
	 *bm1684 use old addrmap
	 */
	if (bm_get_chip_id() == CHIP_BM1684) {
		for (count = 0; count < ARRAY_SIZE(addrmap_1684); count++) {
			for (i = 0; i < ARRAY_SIZE(cfg_data); i++) {
				if (cfg_data[i].offset == addrmap_1684[count].offset) {
					cfg_data[i].value = addrmap_1684[count].value;
					break;
				}
			}
		}
	}

	/* lpddr4x/4 override cfg,
	 * default config is lpddr4x, if choose lpddr4 mode
	 * use lpddr4 mrs setting override lpddr4x's.
	 * EVB is 2rank 16GB size, others SA5/SM5/SC5 is 1rank 8GB
	 */
	if (is_lpddr4) {
		struct msg_mrs *mrs;

		if (cfg_rank->rank_num == RANK1)
			mrs = &lpddr4_1rank;
		else
			mrs = &lpddr4_2rank;

		uint8_t *data, *chan_a_offset, *chan_b_offset;
		uint32_t size = &mrs->mrxx - &mrs->mr1 + 1;

		//override train 1d mrs
		chan_a_offset = (uint8_t *)&lpddr4x_train1d_dmem
				+ mrs->train_chan_a;
		chan_b_offset = (uint8_t *)&lpddr4x_train1d_dmem
				+ mrs->train_chan_b;

		data = chan_a_offset;
		memcpy(data, &mrs->mr1, size);
		memcpy(data + size, &mrs->mr1, size);

		data = chan_b_offset;
		memcpy(data, &mrs->mr1, size);
		memcpy(data + size, &mrs->mr1, size);

		//override train 2d mrs
		chan_a_offset = (uint8_t *)&lpddr4x_train2d_dmem
				+ mrs->train_chan_a;
		chan_b_offset = (uint8_t *)&lpddr4x_train2d_dmem
				+ mrs->train_chan_b;

		data = chan_a_offset;
		memcpy(data, &mrs->mr1, size);
		memcpy(data + size, &mrs->mr1, size);

		data = chan_b_offset;
		memcpy(data, &mrs->mr1, size);
		memcpy(data + size, &mrs->mr1, size);

		//override PhyOdtImpedance and PhyVref in struct _PMU_SMB_LPDDR4X_1D_t
		data = (uint8_t *)&lpddr4x_train1d_dmem;
		data[10] = 0x28;
		data[12] = (group == GROUP0 ? 0x10 : 0x14);
		//override PhyOdtImpedance and PhyVref in struct _PMU_SMB_LPDDR4X_2D_t
		data = (uint8_t *)&lpddr4x_train2d_dmem;
		data[10] = 0x28;
		data[12] = (group == GROUP0 ? 0x10 : 0x14);
		// after changed PhyVref, this field was also changed by script
		for (i = 0; i < ARRAY_SIZE(phy_initial_data); i++) {
			if (phy_initial_data[i].offset == 0x000200b2) {
				phy_initial_data[i].value = (group == GROUP0 ? 0xd4 : 0x0104);
				break;
			}
		}
	}
}

#define DDR_FREQ_INFO(freq) \
		(freq) == FREQ_2400M ? "2400M" \
		: (freq) == FREQ_3600M ? "3600M" \
		: (freq) == FREQ_4000M ? "4000M" \
		: (freq) == FREQ_4266M ? "4266M" \
		: "?"

#ifdef DDR_ECC_ENABLE
static void ddr_1684_init_ecc(uint32_t rank, int interleave_mode)
{
	uint64_t size;

	if (interleave_mode == 0) {
		// init ddr0a0b ecc
		size = GROUP0_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2)
			: (DDR_RANK_SIZE << 2) - (DDR_RANK_SIZE >> 1);

		bm_sysdma_memcpy(NS_SRAM_BASE, NS_DRAM0_BASE, size, 0);
	} else {
		size = GROUP0_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE - (DDR_RANK_SIZE >> 3))
			: (DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2);

		// init ddr0a ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM0_BASE, size, 0);

		// init ddr0b ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM0_BASE + (DDR_RANK_SIZE << 1), size, 0);
	}

	size = GROUP1_RANK(rank) == RANK1 ?
		(DDR_RANK_SIZE - (DDR_RANK_SIZE >> 3))
		: (DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2);

	// init ddr1 ecc
	bm_sysdma_memcpy(NS_SRAM_BASE,
			 NS_DRAM1_BASE, size, 0);

	// init ddr2 ecc
	bm_sysdma_memcpy(NS_SRAM_BASE,
			 NS_DRAM2_BASE, size, 0);
}

static void ddr_1684x_init_ecc(uint32_t rank, int interleave_mode)
{
	uint64_t size;

	if (interleave_mode == 1) {
		// init ddr0a ddr0b ddr1 ddr2 ecc
		size = (GROUP0_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2)
			: (DDR_RANK_SIZE << 2) - (DDR_RANK_SIZE >> 1)) * 2;

		bm_sysdma_memcpy(NS_SRAM_BASE, NS_DRAM0_BASE, size, 0);
	} else if (interleave_mode == 0) {
		// init ddr0a0b ecc
		size = GROUP0_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2)
			: (DDR_RANK_SIZE << 2) - (DDR_RANK_SIZE >> 1);

		bm_sysdma_memcpy(NS_SRAM_BASE, NS_DRAM0_BASE, size, 0);

		size = GROUP1_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE - (DDR_RANK_SIZE >> 3))
			: (DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2);

		// init ddr1 ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM1_BASE, size, 0);
		// init ddr2 ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM2_BASE, size, 0);
	} else {
		size = GROUP0_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE - (DDR_RANK_SIZE >> 3))
			: (DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2);

		// init ddr0a ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM0_BASE, size, 0);

		// init ddr0b ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM0_BASE + (DDR_RANK_SIZE << 1), size, 0);

		size = GROUP1_RANK(rank) == RANK1 ?
			(DDR_RANK_SIZE - (DDR_RANK_SIZE >> 3))
			: (DDR_RANK_SIZE << 1) - (DDR_RANK_SIZE >> 2);

		// init ddr1 ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM1_BASE, size, 0);

		// init ddr2 ecc
		bm_sysdma_memcpy(NS_SRAM_BASE,
				 NS_DRAM2_BASE, size, 0);
	}

}
#endif

void bm_ddr_init_asic(void)
{
	int err;
	unsigned char is_lpddr4 = false;
	uint32_t board, freq, rank;
	uint32_t is_evb = 0;
	static uint32_t fail_count;

	board = mmio_read_32(BOARD_TYPE_REG);
	switch (board) {
	case BM1684_CUST_V1_3:
	case BM1684X_EVB_V0_0:
		rank = GROUP_RANK(RANK2, RANK2);
		freq = FREQ_4000M;
		break;
	case BM1684_EVB_V1_2:
		rank = GROUP_RANK(RANK1, RANK2);
		freq = FREQ_4000M;
		is_evb = 1;
		break;
	case BM1684_SM5_V1_1_RB:
	case BM1684_CUST_V1_1:
	case BM1684_SM5_V1_2_RB:
	case BM1684_SM5_V1_2_TB:
	case BM1684_SE5_V1_1:
	case BM1684_SE5_V2_0:
	case BM1684_SM5M_V0_0_RB:
	case BM1684_SM5M_V0_0_TB:
	case BM1684_SM5M_V0_1_RB:
	case BM1684_SM5M_V0_1_TB:
	case BM1684_SE6_CTRL:
	case BM1684_SC5_EP:
		rank = GROUP_RANK(RANK1, RANK2);
		freq = FREQ_4000M;
		break;
	case BM1684_SM5M_V3_0_RB:
	case BM1684_SM5M_V3_0_TB:
	case BM1684_SE5_V2_1:
		rank = GROUP_RANK(RANK1, RANK2);
		freq = FREQ_3600M;
		break;
	case BM1684_SE5_V2_5:
	case BM1684_CUST_V1_4:
	case BM1684_SM5M_V3_1_RB:
	case BM1684_SM5M_V3_1_TB:
	case BM1684_SM5M_V0_2_RB:
	case BM1684_SM5M_V0_2_TB:
		rank = GROUP_RANK(RANK1, RANK1);
		freq = FREQ_3600M;
		break;
	default:
		ERROR("unknown type(%d) for DDR init\n", board);
		return;
	};

#ifdef LPDDR_DATA_IN_SD_FLASH
	load_ddr_setting();
#endif

	err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
				  DDR_TYPE_REG, &is_lpddr4);
	if (err) {
		ERROR("read board type failed with error %d\n", err);
		is_lpddr4 = is_lpddr4 && (!is_evb);
	}

	is_lpddr4 = is_lpddr4 && (!is_evb); // assume EVB always using LPDDR4X

	NOTICE("LPDDR%s(rank: %d + %d, freq: %s) init start\n",
	       is_lpddr4 ? "4" : "4x", GROUP0_RANK(rank), GROUP1_RANK(rank),
	       DDR_FREQ_INFO(freq));

	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST0, BIT_MASK_TOP_SOFT_RST0_DDRC);

	ddr_pll_setting(freq);

start:
	dwc_pre_setting(is_lpddr4, GROUP0_RANK(rank), freq, GROUP0);
	ddr_group_init(GROUP0);

	dwc_pre_setting(is_lpddr4, GROUP1_RANK(rank), freq, GROUP1);
	ddr_group_init(GROUP1);

	if (failmap) {
		failmap = 0;
		fail_count++;
		ERROR("Lpddr train %d times still fail, retry!\n", fail_count);
		goto start;
	}

	dwc_phy_enter_mission();

#ifdef DDR_ECC_ENABLE
	sysdma_init();
	NOTICE("SYSDMA write ddr for ecc init...\n");
	if (bm_get_chip_id() == CHIP_BM1684)
	/* default interleave mode 0 for bm1684 */
		ddr_1684_init_ecc(rank, 0);
	else
	/* default interleave mode 1 for bm1684x */
		ddr_1684x_init_ecc(rank, 1);

#endif
	NOTICE("Done.\n");
	/* wait for ddr stable */
	mdelay(200);
}

