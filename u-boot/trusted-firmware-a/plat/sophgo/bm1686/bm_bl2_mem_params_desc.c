/*
 * Copyright (c) 2017-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>

#include <common/desc_image_load.h>
#include <plat/common/platform.h>

/*******************************************************************************
 * Following descriptor provides BL image/ep information that gets used
 * by BL2 to load the images and also subset of this information is
 * passed to next BL image. The image loading sequence is managed by
 * populating the images in required loading order. The image execution
 * sequence is managed by populating the `next_handoff_image_id` with
 * the next executable image id.
 ******************************************************************************/
static bl_mem_params_node_t bl2_mem_params_descs[] = {
	/* Fill BL31 related information */
	{ .image_id = BL31_IMAGE_ID,

	  SET_STATIC_PARAM_HEAD(ep_info, PARAM_EP, VERSION_2,
				entry_point_info_t,
				SECURE | EXECUTABLE | EP_FIRST_EXE),
	  .ep_info.pc = BL31_BASE,
	  .ep_info.spsr = SPSR_64(MODE_EL3, MODE_SP_ELX,
				  DISABLE_ALL_EXCEPTIONS),
# if DEBUG
	  .ep_info.args.arg1 = BM_BL31_PLAT_PARAM_VAL,
# endif
	  SET_STATIC_PARAM_HEAD(image_info, PARAM_EP, VERSION_2, image_info_t,
				IMAGE_ATTRIB_PLAT_SETUP),
	  .image_info.image_base = BL31_BASE,
	  .image_info.image_max_size = BL31_LIMIT - BL31_BASE,

	  .next_handoff_image_id = BL33_IMAGE_ID,
	},

	/* Fill BL33 related information */
	{ .image_id = BL33_IMAGE_ID,
	  SET_STATIC_PARAM_HEAD(ep_info, PARAM_EP, VERSION_2,
				entry_point_info_t, NON_SECURE | EXECUTABLE),
	  .ep_info.pc = NS_IMAGE_OFFSET,

	  SET_STATIC_PARAM_HEAD(image_info, PARAM_EP, VERSION_2, image_info_t,
				0),
	  .image_info.image_base = NS_IMAGE_OFFSET,
	  .image_info.image_max_size = NS_IMAGE_MAX_SIZE,

	  .next_handoff_image_id = INVALID_IMAGE_ID,
	}
};

REGISTER_BL_IMAGE_DESCS(bl2_mem_params_descs)
