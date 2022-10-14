/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <common/desc_image_load.h>
#include <platform_def.h>

#include "bm_common.h"

/*******************************************************************************
 * This function is a wrapper of a common function which flushes the data
 * structures so that they are visible in memory for the next BL image.
 ******************************************************************************/
void plat_flush_next_bl_params(void)
{
	flush_bl_params_desc();
}

/*
 * for BM1684:
 * bl_mem_params_desc_ptr was pointed to bl2_mem_params_descs.
 * bl2_mem_params_descs and next_bl_params will be used by BL1, and passed
 * on to BL31. these two may be overlapped with BL1 RW, so we need to relocate
 * them to a safe position.
 */

/*******************************************************************************
 * This function is a wrapper of a common function which returns the list of
 * loadable images.
 ******************************************************************************/
bl_load_info_t *plat_get_bl_image_load_info(void)
{
	if (bm_get_chip_id() == CHIP_BM1684) {
		bl_mem_params_node_t *new_descs = (bl_mem_params_node_t *)BL1_PARAM_SAVE;

		memcpy(new_descs, bl_mem_params_desc_ptr,
		       bl_mem_params_desc_num * sizeof(bl_mem_params_node_t));
		bl_mem_params_desc_ptr = new_descs;
	}
	return get_bl_load_info_from_mem_params_desc();
}

/*******************************************************************************
 * This function is a wrapper of a common function which returns the data
 * structures of the next BL image.
 ******************************************************************************/
bl_params_t *plat_get_next_bl_params(void)
{
	if (bm_get_chip_id() == CHIP_BM1684) {
		bl_params_t *old_params;
		bl_params_t *new_params = (bl_params_t *)(BL1_PARAM_SAVE +
			bl_mem_params_desc_num * sizeof(bl_mem_params_node_t));

		old_params = get_next_bl_params_from_mem_params_desc();
		memcpy(new_params, old_params, sizeof(bl_params_t));
		return new_params;
	} else {
		return get_next_bl_params_from_mem_params_desc();
	}
}
