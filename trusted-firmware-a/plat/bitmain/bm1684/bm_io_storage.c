/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <string.h>

#include <platform_def.h>

#include <common/bl_common.h>
#include <common/debug.h>
#include <drivers/io/io_driver.h>
#include <drivers/io/io_fip.h>
#include <drivers/io/io_memmap.h>
#include <drivers/io/io_fatfs.h>
#include <drivers/io/io_storage.h>
#include <tools_share/firmware_image_package.h>
#include <lib/mmio.h>
#include <lib/fatfs/ff.h>
#include <drivers/delay_timer.h>
#include <drivers/bitmain/bm_sd.h>
#include <drivers/bitmain/i2c.h>  // to read temprature
#include "bm_common.h"

/* IO devices */
static const io_dev_connector_t *fip_dev_con;
static uintptr_t fip_dev_handle;
static const io_dev_connector_t *memmap_dev_con;
static uintptr_t memmap_dev_handle;
static const io_dev_connector_t *sdfat_dev_con;
static uintptr_t sdfat_dev_handle;

extern size_t spif_offset;
static io_block_spec_t fip_in_spi_dmmr_block_spec = {
	.length = PLAT_BM_FIP_MAX_SIZE,
};

static const io_block_spec_t fip_in_memmap_block_spec = {
	.offset = NS_SRAM_BASE,
	.length = PLAT_BM_FIP_MAX_SIZE
};

static io_block_spec_t fip_in_sdfat_block_spec = {
	.offset = 0,
	.length = PLAT_BM_FIP_MAX_SIZE,
};

static const io_uuid_spec_t bl2_uuid_spec = {
	.uuid = UUID_TRUSTED_BOOT_FIRMWARE_BL2,
};

static const io_uuid_spec_t bl31_uuid_spec = {
	.uuid = UUID_EL3_RUNTIME_FIRMWARE_BL31,
};

static const io_uuid_spec_t bl33_uuid_spec = {
	.uuid = UUID_NON_TRUSTED_FIRMWARE_BL33,
};

static int check_fip_source(const uintptr_t spec);
static int open_fip(const uintptr_t spec);

struct plat_io_policy {
	uintptr_t *dev_handle;
	uintptr_t image_spec;
	int (*check)(const uintptr_t spec);
};

/* By default, ARM platforms load images from the FIP */
static struct plat_io_policy policies[] = {
	[FIP_IMAGE_ID] = {
		NULL,
		(uintptr_t)NULL,
		check_fip_source
	},
	[BL2_IMAGE_ID] = {
		&fip_dev_handle,
		(uintptr_t)&bl2_uuid_spec,
		open_fip
	},
	[BL31_IMAGE_ID] = {
		&fip_dev_handle,
		(uintptr_t)&bl31_uuid_spec,
		open_fip
	},
	[BL33_IMAGE_ID] = {
		&fip_dev_handle,
		(uintptr_t)&bl33_uuid_spec,
		open_fip
	},
};

static int open_fip(const uintptr_t spec)
{
	int result;
	uintptr_t local_image_handle;

	/* See if a Firmware Image Package is available */
	result = io_dev_init(fip_dev_handle, (uintptr_t)FIP_IMAGE_ID);
	if (result == 0) {
		result = io_open(fip_dev_handle, spec, &local_image_handle);
		if (result == 0) {
			VERBOSE("Using FIP\n");
			io_close(local_image_handle);
		}
	}
	return result;
}

static int open_memmap(const uintptr_t spec)
{
	int result;
	uintptr_t local_image_handle;

	result = io_dev_init(memmap_dev_handle, (uintptr_t)NULL);
	if (result == 0) {
		result = io_open(memmap_dev_handle, spec, &local_image_handle);
		if (result == 0) {
			VERBOSE("Using Memmap\n");
			io_close(local_image_handle);
		}
	}
	return result;
}

static int open_sdfat(const uintptr_t spec)
{
	int result;
	uintptr_t local_image_handle;

	result = io_dev_init(sdfat_dev_handle, (uintptr_t)NULL);
	if (result == 0) {
		result = io_open(sdfat_dev_handle, spec, &local_image_handle);
		if (result == 0) {
			VERBOSE("Using SD FAT\n");
			io_close(local_image_handle);
		}
	}
	return result;
}

static int check_fip_source(const uintptr_t spec)
{
	int result = -ENOENT;
	int fip_src = mmio_read_32(FIP_SOURCE_REG);
	int wdted = 0;

	if (bm_get_chip_id() == CHIP_BM1684)
		wdted = mmio_read_32(BOOT_STAGE_REG) == BOOT_WDTED;
	else
		wdted = mmio_read_32(TOP_BASE + REG_TOP_WDT_RST_STATUS) == 1;

	switch (fip_src) {
	case FIP_SRC_SPIF:
		if (wdted && (spif_offset == SPIF_OFFSET_A_FIP)) {
			spif_offset = SPIF_OFFSET_B_FIP;
			NOTICE("Try SPIF section B\n");
		}
		fip_in_spi_dmmr_block_spec.offset = SPIF_BASE + spif_offset;
		result = open_memmap((uintptr_t)&fip_in_spi_dmmr_block_spec);
		if (result == 0) {
			NOTICE("Locate FIP in SPI flash (DMMR)\n");
			policies[FIP_IMAGE_ID].dev_handle = &memmap_dev_handle;
			policies[FIP_IMAGE_ID].image_spec = (uintptr_t)&fip_in_spi_dmmr_block_spec;
		}
		break;
	case FIP_SRC_SRAM:
		result = open_memmap((uintptr_t)&fip_in_memmap_block_spec);
		if (result == 0) {
			NOTICE("Locate FIP in memory\n");
			policies[FIP_IMAGE_ID].dev_handle = &memmap_dev_handle;
			policies[FIP_IMAGE_ID].image_spec = (uintptr_t)&fip_in_memmap_block_spec;
		}
		break;
	case FIP_SRC_SDFT:
		result = open_sdfat((uintptr_t)&fip_in_sdfat_block_spec);
		if (result == 0) {
			NOTICE("Locate FIP in SD FAT\n");
			policies[FIP_IMAGE_ID].dev_handle = &sdfat_dev_handle;
			policies[FIP_IMAGE_ID].image_spec = (uintptr_t)&fip_in_sdfat_block_spec;
		}
		break;
	default:
		ERROR("illegal fip source 0x%x\n", fip_src);
		break;
	};

	return result;
}

static void setup_io_dev(void)
{
	int io_result;

	io_result = register_io_dev_fip(&fip_dev_con);
	assert(io_result == 0);

	io_result = register_io_dev_memmap(&memmap_dev_con);
	assert(io_result == 0);

	io_result = register_io_dev_fatfs(&sdfat_dev_con);
	assert(io_result == 0);

	/* Open connections to devices and cache the handles */
	io_result = io_dev_open(fip_dev_con, (uintptr_t)NULL,
				&fip_dev_handle);
	assert(io_result == 0);

	io_result = io_dev_open(memmap_dev_con, (uintptr_t)NULL,
				&memmap_dev_handle);
	assert(io_result == 0);

	io_result = io_dev_open(sdfat_dev_con, (uintptr_t)NULL,
				&sdfat_dev_handle);
	assert(io_result == 0);

	/* Ignore improbable errors in release builds */
	(void)io_result;
}

void tmp451_read_temprature(uint8_t *local, uint8_t *remote)
{
	uint8_t l = 0, r = 0;

	i2c_smbus_write_byte(0, 0x4c, 9, 0x80);	   // range 0 - 127
	i2c_smbus_write_byte(0, 0x4c, 0x11, 0x00); // offset 0
	i2c_smbus_read_byte(0, 0x4c, 1, &r);
	*remote = r & 0x7f;
	i2c_smbus_read_byte(0, 0x4c, 0, &l);
	*local = l & 0x7f;
}

inline uint16_t swap_endian_16(uint16_t raw)
{
	return (raw << 8) | (raw >> 8);
}

void update_registers_for_mcu(void)
{
	static struct bm_sc7pro_sbus_regs_t regs;
	uint8_t remote_temp, local_temp;

	regs.reserved_a[0] += 1;
	if (mmio_read_32(BM1684X_DRIVER_PROBE_FLAG) == 1) {
		NOTICE("driver active now, skip\n");
		return; /* driver installed, nothing to do */
	}
	/* read temprature from iic and write to sram */
	tmp451_read_temprature(&local_temp, &remote_temp);
	NOTICE("read iic remote temp %d, local temp %d\n", remote_temp, local_temp);
	regs.board_temp = local_temp;
	regs.chip_temp = remote_temp;
	regs.fan_speed = 0xff;
	regs.board_power = 0xff;
	regs.vendor_id_device = swap_endian_16(BM1684X_DEVICE_ID);
	regs.vendor_id_vendor = swap_endian_16(BM1684X_VENDOR_ID);
	regs.firmware_ver_chip = swap_endian_16(0xdead);
	regs.firmware_ver_major = 0xbe;
	regs.firmware_ver_minor = 0xef;
	for (int i = 0; i < sizeof(regs) / 4; i++) {
		mmio_write_32(BM1684X_SMBUS_REG_BASE + i * 4, ((uint32_t *)&regs)[i]);
	}
}

void bm_locate_next_image(void)
{
#ifdef IMAGE_BL1
	/*
	 * BL1 can bootup from:
	 *     1. SPI flash, default option
	 *     2. SD card, by card detection
	 *     3. SRAM, by boot_sel pin, or by manually changed FIP_SOURCE_REG
	 */
	int fip_src = FIP_SRC_SPIF;

	if (mmio_read_32(FIP_SOURCE_REG) == FIP_SRC_SRAM)
		goto setup;

	if (((bm_gpio_read(BIT_MASK_GPIO_BOOT_SEL) & BOOTSEL_SKIP_SD) == 0) &&
	    bm_sd_card_detect() &&
	    (bm_sd_init(0) == 0)) {
		FRESULT f_ret;
		FATFS SDC_FS;
		FIL fp;

		f_ret = f_mount(&SDC_FS, "0:", 1);
		if (f_ret == FR_OK) {
			f_ret = f_open(&fp, "0:fip.bin", FA_OPEN_EXISTING);
			if (f_ret == FR_OK) {
				NOTICE("boot from SD\n");
				fip_src = FIP_SRC_SDFT;
				f_close(&fp);
			} else {
				NOTICE("fip not found on SD\n");
			}
			f_unmount("0:");
		}
	} else if (bm_gpio_read(BIT_MASK_GPIO_BOOT_SEL) & BOOTSEL_FORCE_SRAM) {
		fip_src = FIP_SRC_SRAM;
	}

	mmio_write_32(FIP_SOURCE_REG, fip_src);

setup:
	setup_io_dev();
#else
	/*
	 * BL2 can bootup from:
	 *     1. SPI flash, by BL1 parameter
	 *     2. SD card, by BL1 parameter
	 *     3. SRAM, by BL1 parameter or PCIe link;
	 *              no need to wait for fip being loaded if BL2 itself is
	 *              from RAM boot.
	 */
	int fip_src, bl1_ramboot;

	if (bm_get_chip_id() == CHIP_BM1684) {
		/*
		 * boot ROM lack of the following flow, only support SD and SPIF boot.
		 */
		fip_src = FIP_SRC_SPIF;

		if (((bm_gpio_read(BIT_MASK_GPIO_BOOT_SEL) & BOOTSEL_SKIP_SD) == 0) &&
		    bm_sd_card_detect() &&
		    (bm_sd_init(0) == 0)) {
			FRESULT f_ret;
			FATFS SDC_FS;
			FIL fp;

			f_ret = f_mount(&SDC_FS, "0:", 1);
			if (f_ret == FR_OK) {
				f_ret = f_open(&fp, "0:fip.bin", FA_OPEN_EXISTING);
				if (f_ret == FR_OK) {
					NOTICE("boot from SD\n");
					fip_src = FIP_SRC_SDFT;
					f_close(&fp);
				} else {
					NOTICE("fip not found on SD\n");
				}
				f_unmount("0:");
			}
		}

		bl1_ramboot = 0;
	} else {
		fip_src = mmio_read_32(FIP_SOURCE_REG);
		bl1_ramboot = (fip_src == FIP_SRC_SRAM);

		if (fip_src == FIP_SRC_SDFT && bm_sd_init(0))
			// something wrong with SD, fall back to SPI flash
			fip_src = FIP_SRC_SPIF;
	}

	if ((mmio_read_32(BOOT_ARGS_REG) & PCIE_EP_LINKED) &&
	    !(mmio_read_32(BOOT_ARGS_REG) & SOC_EP))
		fip_src = FIP_SRC_SRAM;

	mmio_write_32(FIP_SOURCE_REG, fip_src);

	if (!bl1_ramboot && fip_src == FIP_SRC_SRAM) {
		NOTICE("Waiting for FIP in position\n");
		bm_wdt_stop();
		while (1) {
			/* if driver was not installed, we update smbus registers so bmc can
			 * still read board temprature and other stuff
			 */
			update_registers_for_mcu();

			if (mmio_read_32(BOOT_ARGS_REG) & FIP_LOADED) {
				NOTICE("FIP is in position\n");
				mmio_clrbits_32(BOOT_ARGS_REG, FIP_LOADED);
				break;
			}
			mdelay(100);
		}
	}

	setup_io_dev();
#endif
}

int plat_try_next_boot_source(void)
{
	int fip_src = mmio_read_32(FIP_SOURCE_REG);

	if (fip_src != FIP_SRC_SPIF)
		return 0;

	if (spif_offset == SPIF_OFFSET_A_FIP) {
		spif_offset = SPIF_OFFSET_B_FIP;
		NOTICE("Try SPIF section B\n");
		return 1;
	} else {
		return 0;
	}
}

/*
 * Return an IO device handle and specification which can be used to access
 * an image. Use this to enforce platform load policy
 */
int plat_get_image_source(unsigned int image_id, uintptr_t *dev_handle,
			  uintptr_t *image_spec)
{
	int result;
	const struct plat_io_policy *policy;

	assert(image_id < ARRAY_SIZE(policies));

	policy = &policies[image_id];
	result = policy->check(policy->image_spec);
	if (result == 0) {
		*image_spec = policy->image_spec;
		*dev_handle = *(policy->dev_handle);
	} else {
		ERROR("No suitable image source for %d\n", image_id);
	}

	return result;
}
