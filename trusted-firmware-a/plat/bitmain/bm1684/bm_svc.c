/*
 * Copyright (c) 2014-2022, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <stdint.h>

#include <common/debug.h>
#include <common/runtime_svc.h>
#include <lib/el3_runtime/cpu_data.h>
#include <smccc_helpers.h>

/* BM Standard Service Calls version numbers */
#define BM_SVC_MAJOR_VER 1
#define BM_SVC_MINOR_VER 1

#define BM_SVC_CALL_NUMBER 2

/* SMC function IDs for BM Service queries */
#define BM_SVC_CALL_COUNT		0x82000040
#define BM_SVC_UID			    0x82000041
/*					0x8400ff02 is reserved */
#define BM_SVC_VERSION		0x82000043

/* Setup Standard Services */
static int32_t bm_svc_setup(void)
{
	int ret = 0;

    /* efuse initialisation */
    // efuse_setup();

	/* TRNG initialisation */
	// trng_setup();

    /* SPACC initialisation */
    // spacc_setup();

    /* PKA initialisation */
    // pka_setup();

	return ret;
}

/*
 * Top-level Standard Service SMC handler. This handler will in turn dispatch
 * calls to BM SMC handler
 */
static uintptr_t bm_svc_smc_handler(uint32_t smc_fid, u_register_t x1,
				    u_register_t x2, u_register_t x3,
				    u_register_t x4, void *cookie,
				    void *handle, u_register_t flags)
{
	uint64_t ret;
	uint32_t r1 = (uint32_t)x1;
	uint32_t r2 = (uint32_t)x2;
	uint32_t r3 = (uint32_t)x3;

	switch (smc_fid) {
	case BM_SVC_CALL_COUNT:
		ret = BM_SVC_CALL_NUMBER;
		SMC_RET1(handle, ret);

	case BM_SVC_VERSION:
		ret = BM_SVC_MAJOR_VER | BM_SVC_MINOR_VER;
		SMC_RET1(handle, ret);

	case BM_SVC_UID:
		r1 = 0x66;
		r2 = 0x77;
		r3 = 0x88;
		ret = BM_SVC_MAJOR_VER | BM_SVC_MINOR_VER;
		SMC_RET4(handle, ret, r1, r2, r3);

	default:
		SMC_RET1(handle, SMC_UNK);
	}
}

/* Register Standard Service Calls as runtime service */
DECLARE_RT_SVC(bm_svc,
	       OEN_SIP_START,
	       OEN_SIP_END,
	       SMC_TYPE_FAST,
	       bm_svc_setup,
	       bm_svc_smc_handler
);
