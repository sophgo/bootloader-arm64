/*
 * Copyright (c) 2016-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <common/debug.h>
#include <errno.h>
#include <mmio.h>
#include <platform_def.h>
#include <string.h>
#include <utils.h>
#include <delay_timer.h>
#include <arch_helpers.h>
#include <drivers/sophgo/dma/sysdma.h>

#define LLI_SIZE	0x40
#define TIMEOUT		1000000 //us

/*
 * A lli item/descriptor can trans 0x100000 * 32 * 32 bits data
 * one DMA transfer data size = block ts * signle size * src width =
 * single transaction size byte(SRC_TR_WIDTH/8) *
 * SRC_MSIZE(Source Burst Transaction Length, 0 - 1024) *
 * BLOCK_TS(0 - 0x100000)
 * MAX size one DMA transfer = 0x100000 * 32 * (32 / 8) = 128MB
 * here, choose SRC_MSIZE = 32
 * lli list take mem size = (Total mem size / (0x100000 * 32 * 4)) * 0x40
 */
#define LLI_GET_SIZE (32 * 0x40) //32 * 128MB

#define min_t(type, x, y) ({				\
		type __min1 = (x);                      \
		type __min2 = (y);                      \
		__min1 < __min2 ? __min1 : __min2; })

#define do_div(n, base) ({					\
	uint64_t __base = (base);				\
	uint64_t __rem;						\
	__rem = ((uint64_t)(n)) % __base;			\
	(n) = ((uint64_t)(n)) / __base;				\
	__rem;							\
})

static uint64_t *llp_addr_first;
static uint64_t *llp_addr_prev;
static int mmu_enable_stat;
static void dump_lli_content(uint64_t *llp_first, int count)
{
	int i;
	uint64_t *llp = llp_first;

	for (i = 0; i < count; i++, llp += 4) {
		NOTICE("lli			: %d, %p\n", i, llp);
		NOTICE("sar			: 0x%lx\n", *llp++);
		NOTICE("dar			: 0x%lx\n", *llp++);
		NOTICE("block ts		: 0x%lx\n", *llp++);
		NOTICE("llp			: 0x%lx\n", *llp++);
		NOTICE("ctl			: 0x%lx\n", *llp);
		NOTICE("\n");
	}
}

static uint8_t lli_desc[LLI_GET_SIZE + LLI_SIZE];
static void *llp_desc_get(void)
{
	uint64_t *addr = (uint64_t *)lli_desc;

	if ((uint64_t)addr & (LLI_SIZE - 1))
		addr = (uint64_t *)(((uint64_t)addr + LLI_SIZE) & (~(LLI_SIZE - 1)));

	return addr;
}

static void llp_desc_put(void *addr)
{
	//free(addr);
}

void dma_turn_off(void)
{
	DMAC_WRITE(DMAC_CFGREG, 0x0);
}

void dma_turn_on(void)
{
	DMAC_WRITE(DMAC_CFGREG, DMAC_CFG_DMA_EN | DMAC_CFG_DMA_INT_EN);
}

int device_alloc_chan(struct dma_chan *chan)
{
	u64 chan_en;

	if (chan->chan_id > DMAC_DMA_MAX_NR_CHANNELS) {
		ERROR("%s invalid channel id\n", __func__);
		return -1;
	}

	chan_en = DMAC_READ(DMAC_CHENREG);
	INFO("%s, chan_en=0x%lx\n", __func__, chan_en);
	if (chan_en & (1 << chan->chan_id)) {
		ERROR("%s channel busy\n", __func__);
		return -1;
	}

	return 0;
}

void device_free_chan(struct dma_chan *chan)
{
}

static inline void sysdma_flush_data(uint64_t addr, uint64_t size)
{
	if (mmu_enable_stat)
		inv_dcache_range((uint64_t)addr, size);
}

static void prepare_memory_to_memory(struct dma_chan *chan)
{
	uint64_t ctl;
	static unsigned int first_lli = 1;
	uint64_t *llp_addr;
	size_t offset;
	size_t xfer_count;
	unsigned int trans_width;
	struct slave_config *config = chan->config;
	struct slave_config **configs = chan->configs;

	dma_turn_off();

doo:
	if (configs)
		config = *configs++;
	trans_width = config->data_width;
	ctl = DWC_CTL_SRC_MSIZE(config->src_maxburst)
		| DWC_CTL_DST_MSIZE(config->dst_maxburst)
		| DWC_CTL_SMS(0)
		| DWC_CTL_DMS(0)
		| DWC_CTL_SRC_WIDTH(trans_width)
		| DWC_CTL_DST_WIDTH(trans_width)
		| DWC_CTL_SRC_INC
		| DWC_CTL_DST_INC;

	config->llp_phy_start = (u64 *)llp_desc_get();
	llp_addr = config->llp_phy_start;
	config->lli_count = 0;
	for (offset = 0; offset < config->len; offset = (offset +
		    (xfer_count << trans_width))) {
		xfer_count = min_t(size_t, ((config->len - offset)
			    >> trans_width) ? : 1, MAX_BLOCK_TX);
		LLI_WRITE(llp_addr, LLI_OFFSET_SAR, config->src_addr + offset);
		LLI_WRITE(llp_addr, LLI_OFFSET_DAR, config->dst_addr + offset);
		ctl |= DWC_CTL_SHADOWREG_OR_LLI_VALID;
		LLI_WRITE(llp_addr, LLI_OFFSET_CTL, ctl);
		LLI_WRITE(llp_addr, LLI_OFFSET_BTS, xfer_count - 1);

		if (first_lli)
			llp_addr_first = llp_addr;
		else
			LLI_WRITE(llp_addr_prev, LLI_OFFSET_LLP,
				  (uint64_t)llp_addr | DMA0);

		sysdma_flush_data((uint64_t)llp_addr, LLI_SIZE);
		llp_addr_prev = llp_addr;
		first_lli = 0;
		llp_addr += (LLI_SIZE >> 3);
		config->lli_count++;
	}

	if (configs && *configs)
		goto doo;

	LLI_WRITE(llp_addr_prev, LLI_OFFSET_CTL, ctl |
		DWC_CTL_SHADOWREG_OR_LLI_LAST);
	sysdma_flush_data((uint64_t)llp_addr_prev, LLI_SIZE);
}

static void prepare_memory_to_device(struct dma_chan *chan)
{
	uint64_t ctl;
	static unsigned int first_lli = 1;
	uint64_t *llp_addr;
	size_t offset;
	size_t xfer_count;
	unsigned int trans_width;
	struct slave_config *config = chan->config;

	dma_turn_off();

	ctl = DWC_CTL_SRC_MSIZE(config->src_msize)
		| DWC_CTL_DST_MSIZE(config->dst_msize)
		| DWC_CTL_SMS(config->src_master)
		| DWC_CTL_DMS(config->dst_master)
		| DWC_CTL_SRC_WIDTH(config->src_addr_width)
		| DWC_CTL_DST_WIDTH(config->dst_addr_width)
		| DWC_CTL_SRC_INC
		| DWC_CTL_DST_FIX;

	config->llp_phy_start = (u64 *)llp_desc_get();
	llp_addr = config->llp_phy_start;
	trans_width = 0x2;
	for (offset = 0; offset < config->len; offset = (offset + (xfer_count
			<< trans_width))) {
		xfer_count = min_t(size_t, (config->len - offset)
		       >> trans_width, MAX_BLOCK_TX);
		LLI_WRITE(llp_addr, LLI_OFFSET_SAR, config->src_addr + offset);
		LLI_WRITE(llp_addr, LLI_OFFSET_DAR, config->reg);
		LLI_WRITE(llp_addr, LLI_OFFSET_CTL, ctl |
			DWC_CTL_SHADOWREG_OR_LLI_VALID);
		LLI_WRITE(llp_addr, LLI_OFFSET_BTS, xfer_count - 1);

		if (first_lli)
			llp_addr_first = llp_addr;
		else
			LLI_WRITE(llp_addr_prev, LLI_OFFSET_LLP,
				  (uint64_t)llp_addr | config->src_master);

		sysdma_flush_data((uint64_t)llp_addr, LLI_SIZE);
		llp_addr_prev = llp_addr;
		first_lli = 0;
		llp_addr += LLI_SIZE;
	}

	LLI_WRITE(llp_addr_prev, LLI_OFFSET_CTL, ctl |
	       DWC_CTL_SHADOWREG_OR_LLI_LAST);
	sysdma_flush_data((uint64_t)llp_addr_prev, LLI_SIZE);
}

static void prepare_device_to_memory(struct dma_chan *chan)
{
	uint64_t ctl;
	static unsigned int first_lli = 1;
	uint64_t *llp_addr;
	size_t offset;
	size_t xfer_count;
	unsigned int trans_width;
	struct slave_config *config = chan->config;

	dma_turn_off();

	ctl = DWC_CTL_SRC_MSIZE(config->src_msize)
		| DWC_CTL_DST_MSIZE(config->dst_msize)
		| DWC_CTL_SMS(config->src_master)
		| DWC_CTL_DMS(config->dst_master)
		| DWC_CTL_SRC_WIDTH(config->src_addr_width)
		| DWC_CTL_DST_WIDTH(config->dst_addr_width)
		| DWC_CTL_SRC_FIX
		| DWC_CTL_DST_INC;

	config->llp_phy_start = (u64 *)llp_desc_get();
	llp_addr = config->llp_phy_start;
	trans_width = 0x2;
	for (offset = 0; offset < config->len; offset = (offset + (xfer_count
			<< trans_width))) {
		xfer_count = min_t(size_t, (config->len - offset) >>
		       trans_width, MAX_BLOCK_TX);
		LLI_WRITE(llp_addr, LLI_OFFSET_SAR, config->reg);
		LLI_WRITE(llp_addr, LLI_OFFSET_DAR, config->src_addr + offset);
		LLI_WRITE(llp_addr, LLI_OFFSET_CTL, ctl |
		       DWC_CTL_SHADOWREG_OR_LLI_VALID);
		LLI_WRITE(llp_addr, LLI_OFFSET_BTS, xfer_count - 1);

		if (first_lli)
			llp_addr_first = llp_addr;
		else
			LLI_WRITE(llp_addr_prev, LLI_OFFSET_LLP,
				  (uint64_t)llp_addr | config->src_master);

		sysdma_flush_data((uint64_t)llp_addr, LLI_SIZE);
		llp_addr_prev = llp_addr;
		first_lli = 0;
		llp_addr += LLI_SIZE;
	}

	LLI_WRITE(llp_addr_prev, LLI_OFFSET_CTL, ctl |
		DWC_CTL_SHADOWREG_OR_LLI_LAST);
	sysdma_flush_data((uint64_t)llp_addr_prev, LLI_SIZE);
}

int device_prep_dma_slave(struct dma_chan *chan)
{
	int direction = chan->direction;

	switch (direction) {
	case DMA_MEM_TO_MEM:
		prepare_memory_to_memory(chan);
		break;
	case DMA_MEM_TO_DEV:
		prepare_memory_to_device(chan);
		break;
	case DMA_DEV_TO_MEM:
		prepare_device_to_memory(chan);
		break;
	default:
		ERROR("%s direction error\n", __func__);
		return -1;
	}

	return 0;
}

#define REG(x)  (*(volatile unsigned int *)(x))
int device_issue_pending(struct dma_chan *chan)
{
	int direction;
	uint64_t cfg = 0, val;
	int timeout = 0;
	struct slave_config *config;

	dma_turn_on();

	config = chan->config;
	direction = chan->direction;
	if (direction == DMA_MEM_TO_DEV) {
		cfg = DWC_CFG_SRC_OSR_LMT(15UL)
		| DWC_CFG_DST_OSR_LMT(15UL)
		| DWC_CFG_CH_PRIOR(7UL)
		| DWC_CFG_DST_MULTBLK_TYPE(3)
		| DWC_CFG_SRC_MULTBLK_TYPE(3)
		| DWC_CFG_TT_FC(1UL)
		| DWC_CFG_HS_SEL_SRC_HW
		| DWC_CFG_HS_SEL_DST_HW
		| DWC_CFG_SRC_PER((uint64_t)config->src_handshake_id)
		| DWC_CFG_DST_PER((uint64_t)config->dst_handshake_id);
	} else if (direction == DMA_DEV_TO_MEM) {
		cfg = DWC_CFG_SRC_OSR_LMT(15UL)
		| DWC_CFG_DST_OSR_LMT(15UL)
		| DWC_CFG_CH_PRIOR(7UL)
		| DWC_CFG_DST_MULTBLK_TYPE(3)
		| DWC_CFG_SRC_MULTBLK_TYPE(3)
		| DWC_CFG_TT_FC(2UL)
		| DWC_CFG_HS_SEL_SRC_HW
		| DWC_CFG_HS_SEL_DST_HW
		| DWC_CFG_SRC_PER((uint64_t)config->src_handshake_id)
		| DWC_CFG_DST_PER((uint64_t)config->dst_handshake_id);

	} else if (direction == DMA_MEM_TO_MEM) {
		cfg = DWC_CFG_SRC_OSR_LMT(15UL)
		| DWC_CFG_DST_OSR_LMT(15UL)
		| DWC_CFG_CH_PRIOR(7UL)
		| DWC_CFG_DST_MULTBLK_TYPE(3)
		| DWC_CFG_SRC_MULTBLK_TYPE(3)
		| DWC_CFG_TT_FC(0UL);

	}

	DMA_CHAN_WRITE(chan->chan_id, DWC_CHAN_CFG_OFFSET, cfg);
	DMA_CHAN_WRITE(chan->chan_id, DWC_CHAN_LLP_OFFSET,
		       (uint64_t)config->llp_phy_start | config->src_master);

	val = ((1 << chan->chan_id) << 8 | (1 << chan->chan_id));
	DMAC_WRITE(DMAC_CHENREG, val);
	do {
		udelay(1);
		timeout += 1;
	} while (((1 << chan->chan_id) & DMAC_READ(DMAC_CHENREG)) &&
		timeout < TIMEOUT);

	if (timeout >= TIMEOUT) {
		ERROR("%s, DMA transfer failed chan_en = 0x%lx\n",
		      __func__, DMAC_READ(DMAC_CHENREG));
		dump_lli_content(config->llp_phy_start, config->lli_count);
		return -1;
	}

	dma_turn_off();
	llp_desc_put(llp_addr_first);

	return 0;
}

int sysdma_init(void)
{
	mmu_enable_stat = 1;

	return 0;
}
