/*
 * Copyright (c) 2016-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <common/debug.h>
#include <errno.h>
#include <mmio.h>
#include <platform_def.h>
#include <string.h>

#include <drivers/sophgo/dma/sysdma.h>

#define SYSDMA_COPY_SIZE 0x100000
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

static struct slave_config mem2mem_cfg = {
	.direction = DMA_MEM_TO_MEM,
	.data_width = SLAVE_BUSWIDTH_4_BYTES,
	.src_addr_width = SLAVE_BUSWIDTH_4_BYTES,
	.dst_addr_width = SLAVE_BUSWIDTH_4_BYTES,
	.src_msize = DW_DMA_MSIZE_32,
	.dst_msize = DW_DMA_MSIZE_32,
	.device_fc = DW_DMA_FC_D_M2M,
	.src_master = DMA0,
	.dst_master = DMA0
};

static struct dma_chan channel;
static int sysdma_memory_copy(uint64_t src, uint64_t dst, uint64_t size, int channel_id)
{
	int ret;
	struct dma_chan *chan = &channel;

	chan->chan_id = channel_id;	//channel 0
	chan->config = &mem2mem_cfg;
	chan->configs = NULL;
	chan->direction = DMA_MEM_TO_MEM;

	chan->config->len = size;
	chan->config->src_addr = src;
	chan->config->dst_addr = dst;

	ret = device_alloc_chan(chan);
	if (ret < 0)
		return ret;

	ret = device_prep_dma_slave(chan);
	if (ret < 0)
		return ret;

	ret = device_issue_pending(chan);
	if (ret < 0)
		return ret;

	if (ret)
		return ret;

	return 0;
}

int bm_sysdma_memcpy(uint64_t src, uint64_t dst, uint64_t size, int channel_id)
{
	int i, ret;
	int trans_count = DIV_ROUND_UP(size, SYSDMA_COPY_SIZE);

	for (i = 0; i < trans_count; i++) {
		ret = sysdma_memory_copy(src, dst + i * SYSDMA_COPY_SIZE, SYSDMA_COPY_SIZE, 0);
		if (ret) {
			ERROR("SYSDMA memory copy failed.\n");
			return ret;
		}
	}

	return 0;
}
