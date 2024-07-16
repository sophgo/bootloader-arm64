/*
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <lib/mmio.h>
#include <common/debug.h>
#include <platform_def.h>

#include "mango_clock.h"

#define do_div(n, base)                           \
	({                                        \
		unsigned long __base = (base);         \
		unsigned long __rem;                   \
		__rem = ((unsigned long)(n)) % __base; \
		(n) = ((unsigned long)(n)) / __base;   \
		__rem;                            \
	})

struct bm_pll_clock bm1684_root_pll_clks[] = {
	{
		.id = MPLL_CLK,
		.name = "mpll_clock",
	},
	{
		.id = DPLL0_CLK,
		.name = "dpll0_clock",
	},
	{
		.id = DPLL1_CLK,
		.name = "dpll1_clock",
	},
};

struct bm_gate_clock bm1684_gate_clks[] = {
	{ GATE_CLK_APB_ROM, "clk_gate_rom", 0, 0x800, 30, 0 },
	{ GATE_CLK_AXISRAM, "clk_gate_axisram", 0, 0x804, 11, 0 },
};

#define POSTDIV_RESULT_INDEX 2
static int postdiv1_2[][3] = {
	{ 2, 4, 8 },  { 3, 3, 9 },  { 2, 5, 10 }, { 2, 6, 12 }, { 2, 7, 14 },
	{ 3, 5, 15 }, { 4, 4, 16 }, { 3, 6, 18 }, { 4, 5, 20 }, { 3, 7, 21 },
	{ 4, 6, 24 }, { 5, 5, 25 }, { 4, 7, 28 }, { 5, 6, 30 }, { 5, 7, 35 },
	{ 6, 6, 36 }, { 6, 7, 42 }, { 7, 7, 49 },
};

static inline unsigned long abs_diff(unsigned long a, unsigned long b)
{
	return (a > b) ? (a - b) : (b - a);
}

static int pll_get_postdiv_1_2(unsigned long rate, unsigned long prate,
			       unsigned int fbdiv, unsigned int refdiv,
			       unsigned int *postdiv1, unsigned int *postdiv2)
{
	int index = 0;
	int ret = 0;
	unsigned long tmp0;

	/* calculate (parent_rate/refdiv)
	 * and result save to prate
	 */
	tmp0 = prate;
	do_div(tmp0, refdiv);

	/* calcuate ((parent_rate/REFDIV) x FBDIV)
	 * and result save to prate
	 */
	tmp0 *= fbdiv;

	/* calcuate (((parent_rate/REFDIV) x FBDIV)/input_rate)
	 * and result save to prate
	 * here *prate is (POSTDIV1*POSTDIV2)
	 */
	do_div(tmp0, rate);

	/* calculate div1 and div2 value */
	if (tmp0 <= 7) {
		/* (div1 * div2) <= 7, no need to use array search */
		*postdiv1 = tmp0;
		*postdiv2 = 1;
	} else {
		/* (div1 * div2) > 7, use array search */
		for (index = 0; index < ARRAY_SIZE(postdiv1_2); index++) {
			if (tmp0 > postdiv1_2[index][POSTDIV_RESULT_INDEX])
				continue;
			else
				break; /* found it */
		}
		if (index < ARRAY_SIZE(postdiv1_2)) {
			*postdiv1 = postdiv1_2[index][1];
			*postdiv2 = postdiv1_2[index][0];
		} else {
			WARN("%s out of postdiv array range!\n", __func__);
			ret = -1;
		}
	}

	return ret;
}

static int get_pll_ctl_setting(struct bm_pll_ctrl *best, unsigned long req_rate)
{
	int ret;
	unsigned int fbdiv, refdiv, fref, postdiv1, postdiv2;
	unsigned long tmp = 0, foutvco;

	fref = REF_CLOCK;

	for (refdiv = REFDIV_MIN; refdiv < REFDIV_MAX + 1; refdiv++) {
		for (fbdiv = FBDIV_MIN; fbdiv < FBDIV_MAX + 1; fbdiv++) {
			foutvco = fref * fbdiv / refdiv;
			/* check fpostdiv pfd */
			if (foutvco < PLL_FREQ_MIN || foutvco > PLL_FREQ_MAX ||
			    (fref / refdiv) < 10)
				continue;

			ret = pll_get_postdiv_1_2(req_rate, fref, fbdiv, refdiv,
						  &postdiv1, &postdiv2);
			if (ret)
				continue;

			tmp = foutvco / (postdiv1 * postdiv2);
			if (abs_diff(tmp, req_rate) <
			    abs_diff(best->freq, req_rate)) {
				best->freq = tmp;
				best->refdiv = refdiv;
				best->fbdiv = fbdiv;
				best->postdiv1 = postdiv1;
				best->postdiv2 = postdiv2;
				if (tmp == req_rate)
					return 0;
			}
			continue;
		}
	}

	return 0;
}

static void pll_set_freq(struct bm_pll_clock *pll, unsigned long rate)
{
	unsigned int enable, status;
	unsigned int div, status_id;
	struct bm_pll_ctrl pll_ctrl = { 0 };

	if (pll->id == FPLL_CLK)
		status_id = 3;
	else if (pll->id == VPLL_CLK)
		status_id = 2;
	else
		status_id = pll->id;

	get_pll_ctl_setting(&pll_ctrl, rate);

	div = TOP_PLL_CTRL(pll_ctrl.fbdiv, pll_ctrl.postdiv1, pll_ctrl.postdiv2,
			   pll_ctrl.refdiv);

	enable = mmio_read_32(TOP_BASE + ENABLE_OFFSET);
	mmio_write_32(TOP_BASE + ENABLE_OFFSET, enable & ~(0x1 << status_id));
	mmio_write_32(TOP_BASE + PLL_CTRL_OFFSET + (pll->id << 2), div);

	status = mmio_read_32(TOP_BASE + STATUS_OFFSET);
	while (!((status >> (PLL_STAT_LOCK_OFFSET + status_id)) & 0x1))
		status = mmio_read_32(TOP_BASE + STATUS_OFFSET);

	status = mmio_read_32(TOP_BASE + STATUS_OFFSET);
	while ((status >> status_id) & 0x1)
		status = mmio_read_32(TOP_BASE + STATUS_OFFSET);

	mmio_write_32(TOP_BASE + ENABLE_OFFSET, enable | (0x1 << pll->id));
}

static unsigned long pll_get_freq(struct bm_pll_clock *pll)
{
	return ((REF_CLOCK / pll->pll.refdiv) * pll->pll.fbdiv) /
	       (pll->pll.postdiv1 * pll->pll.postdiv2);
}

static inline void *find_clk_by_index(unsigned int index)
{
	unsigned int i;

	if (index >= PLL_CLK_START && index <= PLL_CLK_END)
		for (i = 0; i < ARRAY_SIZE(bm1684_root_pll_clks); i++)
			if (bm1684_root_pll_clks[i].id == index)
				return (void *)&bm1684_root_pll_clks[i];

	if (index >= GATE_CLK_START && index <= GATE_CLK_END)
		for (i = 0; i < ARRAY_SIZE(bm1684_gate_clks); i++)
			if (bm1684_gate_clks[i].id == index)
				return (void *)&bm1684_gate_clks[i];

	return NULL;
}

static inline void clk_gate_endisable(struct bm_gate_clock *gate, unsigned char en)
{
	if (en)
		mmio_setbits_32(TOP_BASE + gate->offset, 1 << gate->bit_idx);
	else
		mmio_clrbits_32(TOP_BASE + gate->offset, 1 << gate->bit_idx);
}

int clk_set_rate(unsigned int index, unsigned long rate)
{
	void *clk;

	clk = find_clk_by_index(index);

	if (index >= PLL_CLK_START && index <= PLL_CLK_END)
		pll_set_freq((struct bm_pll_clock *)clk, rate);

	return 0;
}

unsigned long clk_get_rate(unsigned int index)
{
	void *clk;

	clk = find_clk_by_index(index);

	if (index >= PLL_CLK_START && index <= PLL_CLK_END)
		return pll_get_freq((struct bm_pll_clock *)clk);

	return 0;
}

/*
 * these function are used in BL31, clock may be changed by kernel,
 * so don't rely on ref_count, just be carefull when you gate a clock
 */
int clk_enable(unsigned int index)
{
	struct bm_gate_clock *gate;

	gate = find_clk_by_index(index);
	if (!gate)
		return -1;

	clk_gate_endisable(gate, 1);

	return 0;
}

int clk_disable(unsigned int index)
{
	struct bm_gate_clock *gate;

	gate = find_clk_by_index(index);
	if (!gate)
		return -1;
	clk_gate_endisable(gate, 0);

	return 0;
}

int clk_is_enabled(unsigned int index)
{
	struct bm_gate_clock *gate;

	gate = find_clk_by_index(index);
	if (!gate)
		return -1;

	if (mmio_read_32(TOP_BASE + gate->offset) & (1 << gate->bit_idx))
		return 1;
	else
		return 0;
}

