/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <platform_def.h>
#include <arch_helpers.h>
#include <common/debug.h>
#include <lib/psci/psci.h>
#include <lib/mmio.h>
#include <plat/common/platform.h>
#include <drivers/bitmain/i2c.h>
#include <spinlock.h>

#include "bm_common.h"

/*
 * The secure entry point to be used on warm reset.
 */
static unsigned long secure_entrypoint;
static uintptr_t g_ncore_base;

extern void plat_non_primary_suspend(void);
extern void plat_primary_suspend(void);

/* Make composite power state parameter till power level 0 */
#if PSCI_EXTENDED_STATE_ID

#define bm_make_pwrstate_lvl0(lvl0_state, pwr_lvl, type) \
		(((lvl0_state) << PSTATE_ID_SHIFT) | \
		 ((type) << PSTATE_TYPE_SHIFT))
#else
#define bm_make_pwrstate_lvl0(lvl0_state, pwr_lvl, type) \
		(((lvl0_state) << PSTATE_ID_SHIFT) | \
		 ((pwr_lvl) << PSTATE_PWR_LVL_SHIFT) | \
		 ((type) << PSTATE_TYPE_SHIFT))
#endif /* PSCI_EXTENDED_STATE_ID */

#define bm_make_pwrstate_lvl1(lvl1_state, lvl0_state, pwr_lvl, type) \
		(((lvl1_state) << PLAT_LOCAL_PSTATE_WIDTH) | \
		 bm_make_pwrstate_lvl0(lvl0_state, pwr_lvl, type))

/*
 *  The table storing the valid idle power states. Ensure that the
 *  array entries are populated in ascending order of state-id to
 *  enable us to use binary search during power state validation.
 *  The table must be terminated by a NULL entry.
 */
static const unsigned int bm_pm_idle_states[] = {
	/* State-id - 0x01 */
	bm_make_pwrstate_lvl1(PLAT_LOCAL_STATE_RUN, PLAT_LOCAL_STATE_RET,
			      MPIDR_AFFLVL0, PSTATE_TYPE_STANDBY),
	/* State-id - 0x02 */
	bm_make_pwrstate_lvl1(PLAT_LOCAL_STATE_RUN, PLAT_LOCAL_STATE_OFF,
			      MPIDR_AFFLVL0, PSTATE_TYPE_POWERDOWN),
	/* State-id - 0x22 */
	bm_make_pwrstate_lvl1(PLAT_LOCAL_STATE_OFF, PLAT_LOCAL_STATE_OFF,
			      MPIDR_AFFLVL1, PSTATE_TYPE_POWERDOWN),
	0,
};

/* set ncore enable/disable for cluster1/2 */
void bm_ncore_enable_cluster(int32_t en)
{
	uint32_t value, mask;

	mask = ((1 << PLATFORM_CLUSTER_COUNT) - 1);
	if (en) {
		value = mmio_read_32(g_ncore_base + NCORE_DIRUCASER0);
		mmio_write_32(g_ncore_base + NCORE_DIRUCASER0, value | mask);
		mmio_write_32(g_ncore_base + NCORE_DIRUMRHER, 0x1);
		mmio_write_32(g_ncore_base + NCORE_DIRUSFER, 0x1);

		value = mmio_read_32(g_ncore_base + NCORE_CSADSER);
		mmio_write_32(g_ncore_base + NCORE_CSADSER, value | mask);
	} else {
		value = mmio_read_32(g_ncore_base + NCORE_DIRUCASER0);
		mmio_write_32(g_ncore_base + NCORE_DIRUCASER0, value & ~mask);
		mmio_write_32(g_ncore_base + NCORE_DIRUMRHER, 0);
		mmio_write_32(g_ncore_base + NCORE_DIRUSFER, 0);

		value = mmio_read_32(g_ncore_base + NCORE_CSADSER);
		mmio_write_32(g_ncore_base + NCORE_CSADSER, value & ~mask);
	}
}

void bm_ncore_init(uintptr_t ncore_base)
{
	g_ncore_base = ncore_base;
}

/*******************************************************************************
 * Platform handler called to check the validity of the power state
 * parameter. The power state parameter has to be a composite power state.
 ******************************************************************************/
static int bm_validate_power_state(unsigned int power_state, psci_power_state_t *req_state)
{
	unsigned int state_id;
	int i;

	assert(req_state);

	/*
	 *  Currently we are using a linear search for finding the matching
	 *  entry in the idle power state array. This can be made a binary
	 *  search if the number of entries justify the additional complexity.
	 */
	for (i = 0; !!bm_pm_idle_states[i]; i++) {
		if (power_state == bm_pm_idle_states[i])
			break;
	}

	/* Return error if entry not found in the idle state array */
	if (!bm_pm_idle_states[i])
		return PSCI_E_INVALID_PARAMS;

	i = 0;
	state_id = psci_get_pstate_id(power_state);

	/* Parse the State ID and populate the state info parameter */
	while (state_id) {
		req_state->pwr_domain_state[i++] = state_id &
						PLAT_LOCAL_PSTATE_MASK;
		state_id >>= PLAT_LOCAL_PSTATE_WIDTH;
	}

	return PSCI_E_SUCCESS;
}

/*******************************************************************************
 * Platform handler called to check the validity of the non secure
 * entrypoint.
 ******************************************************************************/
static int bm_validate_ns_entrypoint(uintptr_t entrypoint)
{
	/*
	 * Check if the non secure entrypoint lies within the non
	 * secure DRAM.
	 */
	if ((entrypoint >= NS_DRAM_BASE) &&
	    (entrypoint < (NS_DRAM_BASE + NS_DRAM_SIZE)))
		return PSCI_E_SUCCESS;
	return PSCI_E_INVALID_ADDRESS;
}

/*
 * don't use spin lock, as:
 * 1. during boot up, seconday cores' dcache is disabled, check calling of
 *    bl31_plat_enable_mmu in bl31_entrypoint.S
 * 2. during suspend, dcache also will be disabled for cores to be powered
 *    off, check cortex_a53_core_pwr_dwn (called by prepare_cpu_pwr_dwn)
 * spin lock uses ldaxr, which needs dcache being enabled.
 */
DEFINE_BAKERY_LOCK(console_lock);

static void print_entry(const char *caller)
{
	unsigned int idx = plat_my_core_pos();

	bakery_lock_get(&console_lock);
	NOTICE("CPU%d %s\n", idx, caller);
	bakery_lock_release(&console_lock);
}

/*******************************************************************************
 * Platform handler called when a CPU is about to enter standby.
 ******************************************************************************/
static void bm_cpu_standby(plat_local_state_t cpu_state)
{
	print_entry(__func__);

	assert(cpu_state == PLAT_LOCAL_STATE_RET);

	/*
	 * Enter standby state
	 * dsb is good practice before using wfi to enter low power states
	 */
	dsb();
	wfi();
}

/*******************************************************************************
 * Platform handler called when a power domain is about to be turned on. The
 * mpidr determines the CPU to be turned on.
 ******************************************************************************/
static int bm_pwr_domain_on(u_register_t mpidr)
{
	int rc = PSCI_E_SUCCESS;
	unsigned int pos = plat_core_pos_by_mpidr(mpidr);
	uint64_t *hold_base = (uint64_t *)PLAT_BM_HOLD_BASE;

	print_entry(__func__);

	hold_base[pos] = PLAT_BM_HOLD_STATE_GO;
	dsb();
	sev();

	return rc;
}

/*******************************************************************************
 * Platform handler called when a power domain is about to be turned off. The
 * target_state encodes the power state that each level should transition to.
 ******************************************************************************/
void bm_pwr_domain_off(const psci_power_state_t *target_state)
{
	print_entry(__func__);
}

/*******************************************************************************
 * Platform handler called when a power domain is about to be suspended. The
 * target_state encodes the power state that each level should transition to.
 ******************************************************************************/
void bm_pwr_domain_suspend(const psci_power_state_t *target_state)
{
	print_entry(__func__);
}

/*******************************************************************************
 * Platform handler called when a power domain has just been powered on after
 * being turned off earlier. The target_state encodes the low power state that
 * each level has woken up from.
 ******************************************************************************/
void bm_pwr_domain_on_finish(const psci_power_state_t *target_state)
{
	print_entry(__func__);

	assert(target_state->pwr_domain_state[MPIDR_AFFLVL0] ==
					PLAT_LOCAL_STATE_OFF);

	bm_ncore_enable_cluster(BM_CORE_UP);
	bm_pwr_gic_on_finish();
}

/*******************************************************************************
 * Platform handler called when a power domain has just been powered on after
 * having been suspended earlier. The target_state encodes the low power state
 * that each level has woken up from.
 ******************************************************************************/
void bm_pwr_domain_suspend_finish(const psci_power_state_t *target_state)
{
	print_entry(__func__);
	bm_ncore_enable_cluster(BM_CORE_UP);
}

/*******************************************************************************
 * Handler called at the end of the power domain suspend sequence. The
 * target_state encodes the power state that each level should transition to.
 ******************************************************************************/
__dead2 void bm_pwr_domain_pwr_down_wfi(const psci_power_state_t
					     *target_state)
{
	uint32_t idx = plat_my_core_pos();

	print_entry(__func__);

	if (idx > 0) {
		/* for non-primary CPU, we jump to Rom for mailbox polling */
		plat_non_primary_suspend();
	} else {
		plat_primary_suspend();
	}

	panic();
}

static struct i2c_info i2c_info[] = {
	{ I2C0_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C1_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C2_BASE, 100 * 1000 * 1000, 100 * 1000 },
};

/*******************************************************************************
 * Platform handlers to shutdown/reboot the system
 ******************************************************************************/
static void __dead2 bm_system_off(void)
{
	print_entry(__func__);

#ifdef MCU_I2C_DEV
	/* control mcu to power off bm1684 */
	mmio_setbits_32(TOP_BASE + REG_TOP_CLOCK_ENABLE1,  (1 << 3)); // enable iic clock
	i2c_init(i2c_info, ARRAY_SIZE(i2c_info));
	i2c_smbus_write_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
			     INSTRUCT_REG, POWER_OFF_CMD);
#endif
	while (1)
		wfi();
}

static void __dead2 bm_system_reset(void)
{
	print_entry(__func__);

#ifdef MCU_I2C_DEV
	NOTICE("MCU reset: power off&on\n");
	mmio_setbits_32(TOP_BASE + REG_TOP_CLOCK_ENABLE1,  (1 << 3)); // enable iic clock
	i2c_init(i2c_info, ARRAY_SIZE(i2c_info));
	i2c_smbus_write_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
			     INSTRUCT_REG, REBOOT_CMD);
#else
	bm_wdt_reset();
#endif
	while (1)
		wfi();
}

void bm_get_sys_suspend_power_state(psci_power_state_t *req_state)
{
	int32_t i;

	for (i = MPIDR_AFFLVL0; i <= PLAT_MAX_PWR_LVL; i++)
		req_state->pwr_domain_state[i] = PLAT_MAX_OFF_STATE;
}

static const plat_psci_ops_t bm_psci_pm_ops = {
	.cpu_standby = bm_cpu_standby,
	.pwr_domain_on = bm_pwr_domain_on,
	.pwr_domain_off = bm_pwr_domain_off,
	.pwr_domain_suspend = bm_pwr_domain_suspend,
	.pwr_domain_on_finish = bm_pwr_domain_on_finish,
	.pwr_domain_suspend_finish = bm_pwr_domain_suspend_finish,
	.pwr_domain_pwr_down_wfi = bm_pwr_domain_pwr_down_wfi,
	.system_off = bm_system_off,
	.system_reset = bm_system_reset,
	.validate_power_state = bm_validate_power_state,
	.get_sys_suspend_power_state = bm_get_sys_suspend_power_state,
	.validate_ns_entrypoint = bm_validate_ns_entrypoint
};

int plat_setup_psci_ops(uintptr_t sec_entrypoint,
			const plat_psci_ops_t **psci_ops)
{
	uintptr_t *mailbox = (void *)PLAT_BM_TRUSTED_MAILBOX_BASE;

	*mailbox = sec_entrypoint;
	secure_entrypoint = (unsigned long)sec_entrypoint;
	*psci_ops = &bm_psci_pm_ops;

	return 0;
}
