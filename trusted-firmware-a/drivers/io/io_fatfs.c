/*
 * Copyright (c) 2016-2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <common/debug.h>
#include <lib/utils.h>
#include <lib/libc/errno.h>
#include <lib/fatfs/ff.h>
#include <drivers/io/io_block.h>
#include <drivers/io/io_driver.h>
#include <drivers/io/io_storage.h>
#include <drivers/io/io_fatfs.h>
#include <platform_def.h>

#define CONV_FR(a) (0 - (a)) // convert fatfs result to ATF style

typedef struct {
	int in_use; // to avoid the trouble of tracking file names
	FIL fp;
} file_state_t;

static file_state_t current_file = {0};
static FATFS SDC_FS;

static io_type_t fatfs_device_type_block(void);
static int fatfs_open(io_dev_info_t *dev_info, const uintptr_t spec, io_entity_t *entity);
static int fatfs_seek(io_entity_t *entity, int mode, signed long long offset);
static int fatfs_len(io_entity_t *entity, size_t *length);
static int fatfs_read(io_entity_t *entity, uintptr_t buffer, size_t length, size_t *length_read);
static int fatfs_close(io_entity_t *entity);
static int fatfs_dev_open(const uintptr_t dev_spec, io_dev_info_t **dev_info);
static int fatfs_dev_close(io_dev_info_t *dev_info);

static const io_dev_connector_t fatfs_dev_connector = {
	.dev_open	= fatfs_dev_open
};

static const io_dev_funcs_t fatfs_dev_funcs = {
	.type		= fatfs_device_type_block,
	.open		= fatfs_open,
	.seek		= fatfs_seek,
	.size		= fatfs_len,
	.read		= fatfs_read,
	.write		= NULL,
	.close		= fatfs_close,
	.dev_init	= NULL,
	.dev_close	= fatfs_dev_close,
};

static io_type_t fatfs_device_type_block(void)
{
	return IO_TYPE_MEMMAP;
}

static const io_dev_info_t fatfs_dev_info = {
	.funcs = &fatfs_dev_funcs,
	.info = (uintptr_t)NULL
};

static int fatfs_open(io_dev_info_t *dev_info, const uintptr_t spec,
		      io_entity_t *entity)
{
	int result = -EBUSY;
	const io_block_spec_t *block_spec = (io_block_spec_t *)spec;

	if (current_file.in_use == 0) {
		FRESULT f_ret;

		assert(block_spec != NULL);
		assert(entity != NULL);

		f_ret = f_mount(&SDC_FS, "0:", 1);
		if (f_ret != FR_OK)
			return CONV_FR(f_ret);

		f_ret = f_open(&current_file.fp, "0:fip.bin", FA_READ);
		result = CONV_FR(f_ret);
	} else {
		WARN("A FATFS file is already active. Close first.\n");
	}

	return result;
}

static int fatfs_seek(io_entity_t *entity, int mode, signed long long offset)
{
	int result = -ENOENT;

	if (mode == IO_SEEK_SET) {
		FRESULT f_ret = FR_OK;

		assert(entity != NULL);

		f_lseek(&current_file.fp, offset);
		result = CONV_FR(f_ret);
	}

	return result;
}

static int fatfs_len(io_entity_t *entity, size_t *length)
{
	assert(entity != NULL);
	assert(length != NULL);

	*length = f_size(&current_file.fp);

	return 0;
}

static int fatfs_read(io_entity_t *entity, uintptr_t buffer, size_t length,
		      size_t *length_read)
{
	FRESULT f_ret;
	UINT br;

	assert(entity != NULL);
	assert(buffer != (uintptr_t)NULL);
	assert(length_read != NULL);

	f_ret = f_read(&current_file.fp, (void *)buffer, length, &br);
	*length_read = br;

	return CONV_FR(f_ret);
}

static int fatfs_close(io_entity_t *entity)
{
	assert(entity != NULL);

	entity->info = 0;
	current_file.in_use = 0;
	f_close(&current_file.fp);
	f_unmount("0:");

	return 0;
}

static int fatfs_dev_open(const uintptr_t dev_spec, io_dev_info_t **dev_info)
{
	assert(dev_info != NULL);

	*dev_info = (io_dev_info_t *)&fatfs_dev_info;

	return 0;
}

static int fatfs_dev_close(io_dev_info_t *dev_info)
{
	assert(dev_info != NULL);

	return 0;
}

/* Exported functions */

/* Register the FAT file system with the IO abstraction */
int register_io_dev_fatfs(const io_dev_connector_t **dev_con)
{
	int result;

	assert(dev_con != NULL);

	result = io_register_device(&fatfs_dev_info);
	if (result == 0)
		*dev_con = &fatfs_dev_connector;
	return result;
}

