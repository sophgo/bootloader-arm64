#include <assert.h>
#include <platform_def.h>
#include <arch.h>
#include <arch_helpers.h>
#include <common/bl_common.h>
#include <lib/mmio.h>
#include <lib/cli.h>
#include <drivers/generic_delay_timer.h>
#include <plat/common/platform.h>
#include <drivers/sophgo/mango_rxu.h>
#include <platform_def.h>
#include <drivers/delay_timer.h>

#define RXU_NUM		32
#define DATASET_ADDR_PA	0x40000000
#define RXU_MEM_SIZE	(4 * 1024 * 1024)

#define GOLDEN_HASH_NUM		1000

#ifndef KB
#undef KB
#endif
#define KB(n)			(((n) * 1024ULL))
/* SYS CTRL */
#define MANGO_TOP_BASE		TOP_BASE
#define MANGO_TOP_SIZE		KB(4)
#define MANGO_PINMUX_BASE	(MANGO_TOP_BASE + MANGO_TOP_SIZE)
#define MANGO_PINMUX_SIZE	KB(4)
#define MANGO_CLOCK_GATE_BASE	(MANGO_PINMUX_BASE + MANGO_PINMUX_SIZE)
#define MANGO_CLOCK_GATE_SIZE	KB(4)
#define MANGO_SOFT_RESET_BASE	(MANGO_CLOCK_GATE_BASE + MANGO_CLOCK_GATE_SIZE)

#define SOFTWARE_RESET_REGISTER1	MANGO_SOFT_RESET_BASE + 0x4
#define RXU_RESET_SHIFT1		13
#define SOFTWARE_RESET_REGISTER2	MANGO_SOFT_RESET_BASE + 0x8
#define RXU_RESET_SHIFT2		19

/*
 * rxu register define
 */
#define CTRL0			0
#define FPRC_SET_SHIFT		16
#define FPRC_SET_MASK		0x00010000
#define FPRC_VALUE_SHIFT	17
#define FPRC_VALUE_MASK		0x00060000

#define MISC_CONFIG0		0x5

#define DATASET_ADDR		0x18

#define A0L			0x320
#define A0H			0x328
#define A1L			0x330
#define A1H			0x338
#define A2L			0x340
#define A2H			0x348
#define A3L			0x350
#define A3H			0x358

#define MSG_VLD_NONCE		0x54c
#define PREFETCH_INST_ADDR	0x548
#define MSG_VALUE		0x5d0
#define MSG_START_NONCE		0x620
#define MSG_DIFF		0x624

#define MSG_NONCE_CTRL		0x628
#define MSG_ID_SHIFT		0
#define MSG_ID_MASK		0x000000ff
#define MSG_LEN_SHIFT		8
#define MSG_LEN_MASK		0x0000ff00
#define NONCE_INCR_SHIFT	16
#define NONCE_INCR_MASK		0xffff0000

#define CTRL1			0x62c
#define MSG_HASH_ID_SHIFT	0
#define MSG_HASH_ID_MASK	0xff
#define MSG_VLD_SHIFT		8
#define MSG_VLD_MASK		0x00000100
#define MSG_HASH_VLD_SHIFT	13
#define MSG_HASH_VLD_MASK	0x00002000

#define PREF_DDR_ID_SHIFT	22
#define PREF_DDR_ID_MASK	0x00c00000

#define MSG_HASH_VALUE		0x630

#ifdef GROUP2
#include "./hwrename_1000_prepost_group2_220104.log_golden.h"
unsigned char fix_msg0[] = {
	0x0e, 0x0e, 0xda, 0x95, 0xc8, 0x8c, 0x06, 0x1c, 0xfa, 0x34, 0xeb, 0x3d,
	0xff, 0x54, 0x1d, 0x98, 0x8e, 0x2d, 0x96, 0x34, 0xe4, 0x37, 0xc6, 0x42,
	0xec, 0xff, 0x5a, 0xa4, 0xb8, 0xfa, 0x64, 0x1f, 0x8c, 0x47, 0x3c, 0x15,
	0x73, 0xca, 0x6b, 0x00, 0x00, 0x00, 0x00, 0x34, 0x39, 0xfb, 0xdf, 0xe7,
	0xec, 0xa0, 0x82, 0x92, 0xed, 0xeb, 0x83, 0x06, 0x1b, 0xd3, 0xbc, 0x41,
	0x31, 0xd8, 0x84, 0x97, 0xe2, 0x2a, 0x74, 0x1e, 0xea, 0x1f, 0x90, 0x32,
	0xa8, 0x7c, 0x55, 0x3a,
};
#else
unsigned char fix_msg0[] = {
	0x0e, 0x0e, 0xe3, 0xb6, 0xf6, 0x8c, 0x06, 0xf0, 0x8d, 0x29, 0x5b, 0x4d,
	0xa7, 0xf5, 0xf4, 0xfd, 0xa9, 0x15, 0x13, 0x43, 0x13, 0x02, 0x5b, 0x6c,
	0xcf, 0xc5, 0xc9, 0xa2, 0x69, 0x08, 0x97, 0x14, 0xa7, 0x79, 0x23, 0x9c,
	0xb6, 0xf5, 0x67, 0x00, 0x00, 0x00, 0x00, 0x8f, 0xa4, 0xdb, 0xb9, 0x33,
	0x96, 0xb6, 0x64, 0xb7, 0xbf, 0x15, 0x07, 0x4c, 0x64, 0x10, 0x4a, 0xe4,
	0x2c, 0x1a, 0x55, 0x27, 0x28, 0xd3, 0xa7, 0xdb, 0x4e, 0x39, 0xf6, 0xb8,
	0x2b, 0x1f, 0x4b, 0x01,
};
#endif

struct rxu_config {
	uint8_t msg_id;
	uint8_t msg_len;
	uint8_t diff;
	uint8_t reserve0;
	uint32_t start_nonce;
	uint16_t nonce_incr;
	uint8_t reserve1[6];
	uint64_t dataset_pa;
	int ddr_id;
	uint8_t msg[80];

	uint64_t reg;
	uint32_t result_msg_id;
	uint32_t nonce;
	uint8_t hash[32];
};

struct rxu_config rxu_dev;

static uint64_t rxu_addr(uint64_t base, unsigned int offset)
{
	return base + offset;
}

static void rxu_set_dataset(uint64_t base, uint64_t addr)
{
	mmio_write_64(rxu_addr(base, DATASET_ADDR), addr);
}

static void rxu_set_msg_value(uint64_t base, uint8_t *msg, uint8_t len)
{
	uint32_t tmp;

	memcpy((void *)rxu_addr(base, MSG_VALUE), msg, len);

	tmp = mmio_read_32(rxu_addr(base, MSG_NONCE_CTRL));
	tmp &= ~MSG_LEN_MASK;
	tmp |= (len << MSG_LEN_SHIFT) & MSG_LEN_MASK;
	mmio_write_32(rxu_addr(base, MSG_NONCE_CTRL), tmp);
}

static void rxu_set_msg_diff(uint64_t base, uint32_t diff)
{
	mmio_write_32(rxu_addr(base, MSG_DIFF), diff);
}

void rxu_set_msg_nonce_incr(uint64_t base, uint16_t incr)
{
	uint32_t tmp;

	tmp = mmio_read_32(rxu_addr(base, MSG_NONCE_CTRL));
	tmp &= ~NONCE_INCR_MASK;
	tmp |= (incr << NONCE_INCR_SHIFT) & NONCE_INCR_MASK;
	mmio_write_32(rxu_addr(base, MSG_NONCE_CTRL), tmp);
}

void rxu_set_msg_id(uint64_t base, uint8_t id)
{
	uint32_t tmp;

	tmp = mmio_read_32(rxu_addr(base, MSG_NONCE_CTRL));
	tmp &= ~MSG_ID_MASK;
	tmp |= (id << MSG_ID_SHIFT) & MSG_ID_MASK;
	mmio_write_32(rxu_addr(base, MSG_NONCE_CTRL), tmp);
}

void rxu_set_rxu_id(uint64_t base, uint8_t id)
{
	mmio_write_8(rxu_addr(base, MISC_CONFIG0), id);
}

static void rxu_set_msg_start_nonce(uint64_t base, uint32_t nonce)
{
	mmio_write_32(rxu_addr(base, MSG_START_NONCE), nonce);
}

static void rxu_start(uint64_t base)
{
	uint32_t tmp;

	tmp = mmio_read_32(rxu_addr(base, CTRL1));
	tmp |= MSG_VLD_MASK;
	mmio_write_32(rxu_addr(base, CTRL1), tmp);
}

static void rxu_set_ddr_id(uint64_t base, int ddr_id)
{
	uint32_t tmp;

	if (ddr_id > 3)
		printf("rxu set ddr id error ddr_id =%d\n", ddr_id);

	tmp = mmio_read_32(rxu_addr(base, CTRL1));
	tmp &= ~PREF_DDR_ID_MASK;
	tmp |= ddr_id << PREF_DDR_ID_SHIFT;
	mmio_write_32(rxu_addr(base, CTRL1), tmp);
}

void rxu_get_hash(uint64_t base, unsigned int *id, uint32_t *nonce, void *hash)
{
	*id = (mmio_read_32(rxu_addr(base, CTRL1)) & MSG_HASH_ID_MASK)
		>> MSG_HASH_ID_SHIFT;
	*nonce = mmio_read_32(rxu_addr(base, MSG_VLD_NONCE));
	memcpy(hash, (void *)rxu_addr(base, MSG_HASH_VALUE), 32);
}

int rxu_result_ready(uint64_t base)
{
	return !!(mmio_read_32(rxu_addr(base, CTRL1)) & MSG_HASH_VLD_MASK);
}

void rxu_set_hash_vld(uint64_t base, unsigned int val)
{
	unsigned int ret = mmio_read_32(rxu_addr(base, CTRL1));

	if (val)
		ret |= MSG_HASH_VLD_MASK;
	else
		ret &= ~MSG_HASH_VLD_MASK;

	mmio_write_32(rxu_addr(base, CTRL1), ret);

	ret = mmio_read_32(rxu_addr(base, CTRL1));
	if (ret & MSG_HASH_VLD_MASK)
		printf("hash vld error\n");
}

void rxu_printf_prefetch_inst_addr(uint64_t base)
{
	static uint32_t old_value = 0xffffffff;
	unsigned int new_value = 0;

	new_value = mmio_read_32(rxu_addr(base, PREFETCH_INST_ADDR));
	if (new_value != old_value) {
		old_value = new_value;
		printf("%08x\n", new_value);
	}

	printf("%016lx\n", mmio_read_64(rxu_addr(base, A0L)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A0H)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A1L)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A1H)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A2L)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A2H)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A3L)));
	printf("%016lx\n", mmio_read_64(rxu_addr(base, A3H)));
}

void rxu_printf_all_reg(uint64_t base)
{
	uint32_t tmp;
	unsigned char buf[128];

	tmp = mmio_read_32(rxu_addr(base, MSG_NONCE_CTRL));
	tmp &= MSG_ID_MASK;
	tmp = tmp >> MSG_ID_SHIFT;
	printf("%s[%d] msg id=%d\n", __func__, __LINE__, tmp);

	tmp = mmio_read_32(rxu_addr(base, MSG_NONCE_CTRL));
	tmp &= MSG_LEN_MASK;
	tmp = tmp >> MSG_LEN_SHIFT;

	memcpy(buf, (void *)rxu_addr(base, MSG_VALUE), tmp);
	for (int k = 0; k < tmp; k++) {
		if (k % 16 == 0 && k != 0)
			printf("\n");
		printf("%02x ", buf[k]);
	}
	printf("\n");
}

void rxu_config(struct rxu_config *rxu, int rxu_id)
{
	uint64_t base_offset;

	base_offset = rxu_id * RXU_MEM_SIZE;

	rxu_set_rxu_id(rxu->reg + base_offset, rxu_id);
	rxu_set_ddr_id(rxu->reg + base_offset, rxu->ddr_id);
	rxu_set_msg_id(rxu->reg + base_offset, rxu->msg_id);
	rxu_set_msg_diff(rxu->reg + base_offset, rxu->diff);
	rxu_set_msg_start_nonce(rxu->reg + base_offset, rxu->start_nonce + rxu_id);
	rxu_set_dataset(rxu->reg + base_offset, rxu->dataset_pa);
	rxu_set_msg_value(rxu->reg + base_offset, rxu->msg, rxu->msg_len);
	rxu_set_msg_nonce_incr(rxu->reg + base_offset, rxu->nonce_incr);

	rxu_start(rxu->reg + base_offset);
}

int rxu_get_result(struct rxu_config *rxu, int rxu_id)
{
	uint64_t rxu_base = rxu_dev.reg + rxu_id * RXU_MEM_SIZE;

	if (rxu_result_ready(rxu_base)) {
		rxu_get_hash(rxu_base, &rxu->result_msg_id, &rxu->nonce, rxu_dev.hash);
		rxu_set_hash_vld(rxu_base, 0);

		return 1;
	}

	return 0;
}

void sg_rxu_core_en(int rxu_id, int en)
{
	if (en) {
		if (rxu_id <= 18)
			mmio_setbits_32(SOFTWARE_RESET_REGISTER1, 1 << (rxu_id + RXU_RESET_SHIFT1));
		else
			mmio_setbits_32(SOFTWARE_RESET_REGISTER2, 1 << (rxu_id - RXU_RESET_SHIFT2));
	} else {
		if (rxu_id <= 18)
			mmio_clrbits_32(SOFTWARE_RESET_REGISTER1, 1 << (rxu_id + RXU_RESET_SHIFT1));
		else
			mmio_clrbits_32(SOFTWARE_RESET_REGISTER2, 1 << (rxu_id - RXU_RESET_SHIFT2));
	}
}

void sg_rxu_reset(int rxu_num)
{
	int i;

	printf("rxu reset\n");
	for (i = 0; i < rxu_num; i++) {
		sg_rxu_core_en(i, 0);
		udelay(1);
		sg_rxu_core_en(i, 1);
	}
}

void sg_rxu_clock_gate(uint64_t base, int en)
{
	unsigned char ret = mmio_read_8(rxu_addr(base, CTRL0));

	if (en)
		ret |= 0x1 << 6;
	else
		ret &= ~(0x1 << 6);

	mmio_write_8(rxu_addr(base, CTRL0), ret);
}

void rxu_clock_gate_test(struct rxu_config *rxu)
{
	static int first;
	int rxu_id;

	if (rxu->nonce % 50 == 0 && first == 0) {
		first = 1;

		__asm__ volatile("dsb sy\n"
				::: "memory"
				);

		for (rxu_id = 0; rxu_id < RXU_NUM; rxu_id++) {
			printf("rxu clock off\n");
			sg_rxu_clock_gate(rxu->reg + rxu_id * RXU_MEM_SIZE, 1);
			udelay(500);
			printf("rxu clock on\n");
			sg_rxu_clock_gate(rxu->reg + rxu_id * RXU_MEM_SIZE, 0);
		}

		__asm__ volatile("dsb sy\n"
				::: "memory"
				);
	}
}

void sg_rxu_test(void)
{
	int rxu_id;

	sg_rxu_reset(RXU_NUM);

	rxu_dev.msg_id = 0;
	rxu_dev.msg_len = sizeof(fix_msg0);
	rxu_dev.diff = 0;
	rxu_dev.start_nonce = 0;
	rxu_dev.nonce_incr = RXU_NUM;
	rxu_dev.dataset_pa = DATASET_ADDR_PA;
	memcpy(rxu_dev.msg, fix_msg0, sizeof(fix_msg0));
	rxu_dev.reg = RPU_CFG;

	for (rxu_id = 0; rxu_id < RXU_NUM; rxu_id++) {
		if (rxu_id < 16) {
			rxu_dev.dataset_pa = 0x0040000000;
			rxu_dev.ddr_id = 0;
		} else {
			rxu_dev.dataset_pa = 0x2040000000;
			rxu_dev.ddr_id = 2;
		}
		rxu_config(&rxu_dev, rxu_id);
	}

	printf("msg_id = %d diff =%d msg len=%d:\n", rxu_dev.msg_id, rxu_dev.diff,  rxu_dev.msg_len);

	while (true) {

		for (rxu_id = 0; rxu_id < RXU_NUM; rxu_id++) {
			if (rxu_get_result(&rxu_dev, rxu_id)) {
				if (rxu_dev.msg_id != rxu_dev.result_msg_id)
					printf("msg id not match\n");

#ifdef RXU_CMP_GOLDEN
				if (rxu_dev.nonce < 1000 &&
				    memcmp(rxu_dev.hash, &golden_hash[rxu_dev.nonce * 32], 32)) {
					rxu_printf_prefetch_inst_addr(rxu_dev.reg + rxu_id * RXU_MEM_SIZE);
				}
#endif

				printf("rxu[%d], result_msg_id=%d, nonce=%d hash:\n",
				       rxu_id, rxu_dev.result_msg_id, rxu_dev.nonce);
				for (int k = 0; k < 32; k++) {
					printf("%02x", rxu_dev.hash[k]);
				}
				printf("\n");
			}
		}
	}
}

