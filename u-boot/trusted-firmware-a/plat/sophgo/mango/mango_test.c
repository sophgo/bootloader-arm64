#include <common/debug.h>
#include <platform_def.h>
#include <lib/cli.h>
#include <lib/mmio.h>
#include <drivers/sophgo/mango_fau.h>
#include <drivers/sophgo/sdvt_lpc_host_defines.h>
#include <drivers/sophgo/sdvt_lpc_host_basic.h>
#include <drivers/sophgo/mango_pcie.h>
#include <drivers/sophgo/mango_rxu.h>
#include "mango_misc.h"

#define TEST_8M
#define TEST_CHECK // used for mmu on, if mmu off need lots of time
#define TEST_SPLIT
#define TEST_PARALLEL
#define SYS_SOFT_RESET_1 0x7030013004 // bit 12 11 10 for fau2 fau1 fau0
#define SOFT_RESET_FAU0 (1 << 10)
#define SOFT_RESET_FAU1 (1 << 11)
#define SOFT_RESET_FAU2 (1 << 12)

#define READ_REG(x) (*(volatile unsigned int *)(x))
#define WRITE_REG(x, y) (*(volatile unsigned int *)(x)) = y
#define PLD_FILE1_OFFSET 0x100000000//4G
#define PLD_FILE2_OFFSET 0x380000000//14G

#ifdef TEST_8M
#define FILE_SECTOR_SIZE 8388608
#define PICE_FILE_ADDR 0
#define PICE_FILE_SIZE 16777184
#define COORD_ADDR PICE_FILE_ADDR + PICE_FILE_SIZE
#define COORD_ADDR_SIZE 14680064
#define REF_MERKEL_ADDR COORD_ADDR + COORD_ADDR_SIZE
#define REF_MERKEL_SIZE 16777184
#define REF_LAYER1_ADDR REF_MERKEL_ADDR + REF_MERKEL_SIZE
#define REF_LAYER1_SIZE 8388608
#define REF_LAYER2_ADDR REF_LAYER1_ADDR + REF_LAYER1_SIZE
#define REF_LAYER2_SIZE 8388608
#define PICE_FILE_ADDR1 REF_LAYER2_ADDR + REF_LAYER2_SIZE + PLD_FILE1_OFFSET
#define PICE_FILE_SIZE1 16777184
#define PICE_FILE_ADDR2 PICE_FILE_ADDR1 + PICE_FILE_SIZE1 + PLD_FILE2_OFFSET - PLD_FILE1_OFFSET
#define PICE_FILE_SIZE2 16777184

uint8_t repid[32] = {
	0x9C,	0x90,	0x87,	0x40,	0x1F,	0x6E,	0xE6,	0x67,
	0xBA,	0xF0,	0x86,	0xCA,	0xCF,	0x2F,	0x87,	0x19,
	0x70,	0x3F,	0x8F,	0x2C,	0x51,	0xBC,	0xF8,	0x97,
	0x8D,	0xAE,	0x97,	0x83,	0xB5,	0xAD,	0x04,	0x17,
};
#else
#define FILE_SECTOR_SIZE 2048
#define PICE_FILE_ADDR 0
#define PICE_FILE_SIZE 4064
#define COORD_ADDR 0xffffe0
#define COORD_ADDR_SIZE 3584
#define REF_MERKEL_ADDR 0x1dfffe0
#define REF_MERKEL_SIZE 4064
#define REF_LAYER1_ADDR 0x2dfffc0
#define REF_LAYER1_SIZE 2048
#define REF_LAYER2_ADDR 0x35FFFC0
#define REF_LAYER2_SIZE 2048
#define PICE_FILE_ADDR1 0x3DFFFC0 + PLD_FILE1_OFFSET
#define PICE_FILE_SIZE1 4064
#define PICE_FILE_ADDR2 0x4DFFFA0 + PLD_FILE2_OFFSET
#define PICE_FILE_SIZE2 4064

uint8_t repid[32] = {
	0x0D,	0x93,	0xB5,	0x9E,	0xB9,	0xC7,	0x56,	0x37,
	0xAA,	0x7F,	0x72,	0x0C,	0x83,	0xCB,	0xBB,	0xFE,
	0x1D,	0xBA,	0x68,	0xEC,	0xD7,	0x5C,	0xC1,	0xFC,
	0xDE,	0xC8,	0x51,	0xC2,	0x7A,	0xD8,	0x9C,	0x31,
};
#endif

#define HEAP_START0 NS_DRAM_BASE + 0x8000000
#define HEAP_END0 HEAP_START0 + 0x8000000
#define FWK_ALIGN_NEXT0(VALUE, INTERVAL) ((\
	((VALUE) + (INTERVAL) - 1) / (INTERVAL)) * (INTERVAL))

extern unsigned long fau_base[3];

/*!
 * \brief Architecture memory manager context.
 */
static struct mango_test_ctx
{
	uintptr_t heap_break;
	uintptr_t heap_end;
} mango_test_ctx = {
	.heap_break = (uintptr_t)(HEAP_START0),
	.heap_end = (uintptr_t)(HEAP_END0),
};

void *_sbrk0(intptr_t increment)
{
	void *ptr;

	if (increment == 0) {
		ptr = (void *)mango_test_ctx.heap_break;
	} else {
		uintptr_t heap_old = FWK_ALIGN_NEXT0(mango_test_ctx.heap_break, 16);
		uintptr_t heap_new = heap_old + increment;

		if (heap_new > mango_test_ctx.heap_end)	{
			ptr = (void *)-1;
		} else {
			mango_test_ctx.heap_break = heap_new;
			ptr = (void *)heap_old;
		}
	}
	return ptr;
}

void *malloc0(size_t size)
{
	void *mem = _sbrk0(size);

	if (mem == ((void *)-1))
		mem = NULL;

	return mem;
}

static uint64_t counter_value(void)
{
	return read_cntpct_el0();
}

static uint64_t counter_freq(void)
{
	return read_cntfrq_el0();
}

typedef __uint128_t uint128_t;

struct mango_test_unit {
	const char *name;
	int (*func)(void);
};

static void *memset64(void *s, uint64_t c, size_t n)
{
	int i;

	n /= 8;

	for (i = 0; i < n; ++i)
		((volatile uint64_t *)s)[i] = c;

	return s;
}

static void __unused *memset128(void *s, uint64_t lo, uint64_t hi, size_t n)
{
	int i;
	uint128_t c = ((uint128_t)hi << 64) | lo;

	n /= 16;

	for (i = 0; i < n; ++i)
		((volatile uint128_t *)s)[i] = c;

	return s;
}

/* return bandwidth */
static uint64_t mem_read_bw(void *s, size_t size)
{
	int i;
	uint128_t __unused c;
	uint64_t time;
	uint64_t bandwidth;
	size_t n = size / 16;

	time = counter_value();

	for (i = 0; i < n; ++i)
		c = ((volatile uint128_t *)s)[i];

	time = counter_value() - time;
	return bandwidth = size * counter_freq() / time;
}

/* return bandwidth */
static uint64_t mem_write_bw(void *s, size_t size)
{
	int i;

	uint64_t time;
	uint64_t bandwidth;
	size_t n = size / 16;

	time = counter_value();

	for (i = 0; i < n; ++i)
		((volatile uint128_t *)s)[i] = 0xdeadbeefUL;

	time = counter_value() - time;
	return bandwidth = size * counter_freq() / time;
}

static int mango_c2c_burst_write_test(void)
{
	unsigned long dst;
	const unsigned long size = 512;

	NOTICE("memset64 start\n");

	dst = 0x8000000000UL + NS_DRAM_BASE;
	memset64((void *)dst, 0xdeadbeef5a5a5a5aUL, size);
	flush_dcache_range(dst, size);

	NOTICE("memset64 end\n");

	return 0;
}

static int mango_ddr_bandwidth(void)
{
	unsigned long dst;
	const unsigned long size = 4 * 1024 * 1024;

	dst = NS_DRAM_BASE;

	NOTICE("DDR %016lx bandwidth start\n", dst);

	NOTICE("DDR %016lx write bandwidth %lu B/s\n", dst,
	       mem_write_bw((void *)dst, size));

	NOTICE("DDR %016lx read bandwidth %lu B/s\n", dst,
	       mem_read_bw((void *)dst, size));

	return 0;
}

uint8_t *base1;
uint8_t *base2;

int merkle_p1_test(int index)
{
	uint64_t file_addr;

	switch (index) {
	case 0:
		inv_dcache_range(PICE_FILE_ADDR, REF_MERKEL_SIZE);
		file_addr = PICE_FILE_ADDR;
		break;
	case 1:
		inv_dcache_range(PICE_FILE_ADDR1, REF_MERKEL_SIZE);
		file_addr = PICE_FILE_ADDR1;
		break;
	case 2:
		inv_dcache_range(PICE_FILE_ADDR2, REF_MERKEL_SIZE);
		file_addr = PICE_FILE_ADDR2;
		break;
	default:
		ERROR("index is wrong\n");
		return -1;
	break;
	}
	int ret = Merkle_p1_calc(file_addr, FILE_SECTOR_SIZE, index);

	if (ret != 0) {
		ERROR("fau%d merkel_tree failed\n", index);
		while (1)
			;
	} else {
		NOTICE("fau%d merkel_tree success\n", index);
	}
#ifdef TEST_CHECK
	NOTICE("cache enabled\n");
	inv_dcache_range(REF_MERKEL_ADDR, REF_MERKEL_SIZE);
	if (memcmp((void *)file_addr, (void *)REF_MERKEL_ADDR, REF_MERKEL_SIZE)) {
		ERROR("fau%d merkel_tree cmp failed\n", index);
		dump((void *)file_addr, REF_MERKEL_SIZE);
		dump((void *)REF_MERKEL_ADDR, REF_MERKEL_SIZE);
		while (1)
			;
	} else {
		NOTICE("fau%d merkel_tree cmp success\n", index);
	}
#endif
	return 0;
}

int SDR_test(int index)
{
	int ret = 0;

	NOTICE("fau%d SDR1:\n", index);
	// first calc node 0
	SDR_calc_node0(base1, repid, 1);
	// calc other node 1~G-1
	ret = SDR_calc(base1, NULL, (uint8_t *)COORD_ADDR, repid, 1, 1, FILE_SECTOR_SIZE / 32 - 1, index);
	if (ret != 0) {
		ERROR("fau%d SDR1 failed\n", index);
		while (1)
			;
		return ret;
	}
#ifdef TEST_CHECK
	inv_dcache_range((uint64_t)base1, REF_LAYER1_SIZE);
	inv_dcache_range(REF_LAYER1_ADDR, REF_LAYER1_SIZE);
	if (memcmp((void *)base1, (void *)REF_LAYER1_ADDR, REF_LAYER1_SIZE)) {
		ERROR("fau%d SDR1 cmp failed\n", index);
		while (1)
			;
	} else {
		NOTICE("fau%d SDR1 cmp success\n", index);
	}
#endif

	NOTICE("fau%d SDR2:\n", index);
	// first calc node 0
	SDR_calc_node0(base2, repid, 2);
	// calc other node 1~G-1
	ret = SDR_calc(base2, base1, (uint8_t *)(COORD_ADDR), repid, 2, 1, FILE_SECTOR_SIZE / 32 - 1, index);
	if (ret != 0) {
		ERROR("fau%d SDR2 failed\n", index);
		while (1)
			;
		return ret;
	}
#ifdef TEST_CHECK
	inv_dcache_range((uint64_t)base2, REF_LAYER2_SIZE);
	inv_dcache_range(REF_LAYER2_ADDR, REF_LAYER2_SIZE);
	if (memcmp((void *)base2, (void *)REF_LAYER2_ADDR, REF_LAYER2_SIZE)) {
		ERROR("fau%d SDR2 cmp failed\n", index);
		while (1)
			;
	} else {
		NOTICE("fau%d SDR2 cmp success\n", index);
	}
#endif
	return 0;
}

int SDR_split_test(int index)
{
	int ret = 0;
	int i = 0;
	int loops_per_num = 0;
	uint32_t nodeid = 0;
	uint32_t loops = 0;

	loops_per_num = (FILE_SECTOR_SIZE / 32) / 4; // split to 4 sector
	// first calc node 0
	SDR_calc_node0(base1, repid, 1);
	// calc other node 1~G-1
	for (i = 0; i < 4; i++) {
		if (i == 0) {
			nodeid = 1;
			loops = loops_per_num - 1;
		} else {
			nodeid = i * loops_per_num;
			loops = loops_per_num;
		}
		ret = SDR_calc(base1, NULL, (uint8_t *)COORD_ADDR, repid, 1, nodeid, loops, index);
		if (ret != 0) {
			ERROR("fau%d SDR1 split %d failed\n", index, i);
			while (1)
				;
			return ret;
		}
	}
#ifdef TEST_CHECK
	inv_dcache_range((uint64_t)base1, REF_LAYER1_SIZE);
	inv_dcache_range(REF_LAYER1_ADDR, REF_LAYER1_SIZE);
	if (memcmp((void *)base1, (void *)REF_LAYER1_ADDR, REF_LAYER1_SIZE)) {
		ERROR("fau%d SDR1 split cmp failed\n", index);
		while (1)
			;
	} else {
		NOTICE("fau%d SDR1 split cmp success\n", index);
	}
#endif

	// first calc node 0
	SDR_calc_node0(base2, repid, 2);
	// calc other node 1~G-1
	for (i = 0; i < 4; i++) {
		if (i == 0) {
			nodeid = 1;
			loops = loops_per_num - 1;
		} else {
			nodeid = i * loops_per_num;
			loops = loops_per_num;
		}
		ret = SDR_calc(base2, base1, (uint8_t *)COORD_ADDR, repid, 2, nodeid, loops, index);
		if (ret != 0) {
			ERROR("fau%d SDR2 split %d failed\n", index, i);
			while (1)
				;
			return ret;
		}
	}
#ifdef TEST_CHECK
	inv_dcache_range((uint64_t)base2, REF_LAYER2_SIZE);
	inv_dcache_range(REF_LAYER2_ADDR, REF_LAYER2_SIZE);
	if (memcmp((void *)base2, (void *)REF_LAYER2_ADDR, REF_LAYER2_SIZE)) {
		ERROR("fau%d SDR2 split cmp failed\n", index);
		while (1)
			;
	} else {
		NOTICE("fau%d SDR2 split cmp success\n", index);
	}
#endif
	return 0;
}

static int mango_fau_module_test(int index)
{
	base1 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);
	base2 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);
	if (base1 == NULL) {
		ERROR("malloc base1 failed\n");
		while (1)
			;
	}
	if (base2 == NULL) {
		ERROR("malloc base2 failed\n");
		while (1)
			;
	} else {
		NOTICE("base1=0x%lx, base2=0x%lx\n", (uint64_t)base1, (uint64_t)base2);
	}
	NOTICE("file=0x%lx, file1=0x%lx, file2=0x%lx\n", (uint64_t)PICE_FILE_ADDR,
	       (uint64_t)PICE_FILE_ADDR1, (uint64_t)PICE_FILE_ADDR2);
	merkle_p1_test(index);
	SDR_test(index);
#ifdef TEST_SPLIT
	SDR_split_test(index);
#endif

	return 0;
}

static int mango_fau_test(void)
{
	int ret = 0;

	NOTICE("fau_test start\n");
	for (int i = 0; i < 3; i++)
		ret |= mango_fau_module_test(i);

	if (ret)
		ERROR("fau_test failed\n");
	else
		NOTICE("fau_test success\n");
	return ret;
}

int fau_module_reset(int index)
{
	uint32_t data;

	switch (index) {
	case 0:
		data = READ_REG(SYS_SOFT_RESET_1);
		data &= ~SOFT_RESET_FAU0;
		WRITE_REG(SYS_SOFT_RESET_1, data);
		NOTICE("SOFT_RESET_FAU0 0x%x, %s\n", READ_REG(SYS_SOFT_RESET_1), __func__);
		data = READ_REG(SYS_SOFT_RESET_1);
		data |= SOFT_RESET_FAU0;
		WRITE_REG(SYS_SOFT_RESET_1, data);
		NOTICE("SOFT_RESET_FAU0 0x%x, %s\n", READ_REG(SYS_SOFT_RESET_1), __func__);
		break;
	case 1:
		data = READ_REG(SYS_SOFT_RESET_1);
		data &= ~SOFT_RESET_FAU1;
		WRITE_REG(SYS_SOFT_RESET_1, data);
		NOTICE("SOFT_RESET_FAU1 0x%x, %s\n", READ_REG(SYS_SOFT_RESET_1), __func__);
		data = READ_REG(SYS_SOFT_RESET_1);
		data |= SOFT_RESET_FAU1;
		WRITE_REG(SYS_SOFT_RESET_1, data);
		NOTICE("SOFT_RESET_FAU1 0x%x, %s\n", READ_REG(SYS_SOFT_RESET_1), __func__);
		break;
	case 2:
		data = READ_REG(SYS_SOFT_RESET_1);
		data &= ~SOFT_RESET_FAU2;
		WRITE_REG(SYS_SOFT_RESET_1, data);
		NOTICE("SOFT_RESET_FAU2 0x%x, %s\n", READ_REG(SYS_SOFT_RESET_1), __func__);
		data = READ_REG(SYS_SOFT_RESET_1);
		data |= SOFT_RESET_FAU2;
		WRITE_REG(SYS_SOFT_RESET_1, data);
		NOTICE("SOFT_RESET_FAU2 0x%x, %s\n", READ_REG(SYS_SOFT_RESET_1), __func__);
		break;
	default:
		ERROR("index is wrong\n");
		return -1;
	}
	return 0;
}

static int mango_fau_module_reset_test(int index)
{
	uint32_t data1;
	uint32_t data2;

	merkle_p1_test(index);
	SDR_test(index);

	NOTICE("FAU_MERKLE_L1_ADDR_L is 0x%x\n", READ_REG(fau_base[index] + FAU_MERKLE_L1_ADDR_L));
	NOTICE("FAU_SDR_COORD_ADDR_L is 0x%x\n", READ_REG(fau_base[index] + FAU_SDR_COORD_ADDR_L));
	fau_module_reset(index);
	data1 = READ_REG(fau_base[index] + FAU_MERKLE_L1_ADDR_L);
	data2 = READ_REG(fau_base[index] + FAU_SDR_COORD_ADDR_L);
	NOTICE("FAU_MERKLE_L1_ADDR_L is 0x%x\n", data1);
	NOTICE("FAU_SDR_COORD_ADDR_L is 0x%x\n", data2);
	if (data1 == 0 && data2 == 0) {
		NOTICE("reset fau%d success\n", index);
	} else {
		ERROR("reset fau%d fail\n", index);
		while (1)
			;
	}
	merkle_p1_test(index);
	SDR_test(index);

	return 0;
}

static int mango_fau_reset_test(void)
{
	int ret = 0;

	NOTICE("fau_test start\n");
	for (int i = 0; i < 3; i++)
		ret |= mango_fau_module_reset_test(i);

	if (ret)
		ERROR("fau_reset_test failed\n");
	else
		NOTICE("fau_reset_test success\n");
	return ret;
}

#ifdef TEST_PARALLEL
static int mango_fau_parallel_test(void)
{
	int ret = 0;
	uint64_t time;

	NOTICE("fau_parallel_test start\n");
	time = counter_value();
	ret = Merkle_p1_parallel_calc(PICE_FILE_ADDR, PICE_FILE_ADDR1, PICE_FILE_ADDR2, FILE_SECTOR_SIZE,
				      FILE_SECTOR_SIZE, FILE_SECTOR_SIZE);
	time = counter_value() - time;
	NOTICE("fau_parallel merkel_tree calc time %ld ns\n", (uint64_t)(time * 1000000000 / counter_freq()));
	if (ret != 0) {
		ERROR("fau_parallel merkel_tree failed\n");
		while (1)
			;
		return ret;
	}

#ifdef TEST_CHECK
	inv_dcache_range(PICE_FILE_ADDR, REF_MERKEL_SIZE);
	inv_dcache_range(PICE_FILE_ADDR1, REF_MERKEL_SIZE);
	inv_dcache_range(PICE_FILE_ADDR2, REF_MERKEL_SIZE);
	inv_dcache_range(REF_MERKEL_ADDR, REF_MERKEL_SIZE);
	if (memcmp((void *)PICE_FILE_ADDR, (void *)REF_MERKEL_ADDR, REF_MERKEL_SIZE)) {
		ERROR("fau%d merkel_tree cmp0 failed\n", 0);
		while (1)
			;
	}
	if (memcmp((void *)PICE_FILE_ADDR1, (void *)REF_MERKEL_ADDR, REF_MERKEL_SIZE)) {
		ERROR("fau%d merkel_tree cmp1 failed\n", 1);
		while (1)
			;
	}
	if (memcmp((void *)PICE_FILE_ADDR2, (void *)REF_MERKEL_ADDR, REF_MERKEL_SIZE)) {
		ERROR("fau%d merkel_tree cmp2 failed\n", 2);
		while (1)
			;
	} else {
		NOTICE("fau_parallel merkel_tree cmp success\n");
	}
#endif

	uint8_t *base01 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);

	if (base01 == NULL) {
		ERROR("malloc base01 failed\n");
		while (1)
			;
	}
	uint8_t *base02 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);

	if (base02 == NULL) {
		ERROR("malloc base02 failed\n");
		while (1)
			;
	}
	uint8_t *base11 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);

	if (base11 == NULL) {
		ERROR("malloc base11 failed\n");
		while (1)
			;
	}
	uint8_t *base12 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);

	if (base12 == NULL) {
		ERROR("malloc base12 failed\n");
		while (1)
			;
	}
	uint8_t *base21 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);

	if (base21 == NULL) {
		ERROR("malloc base21 failed\n");
		while (1)
			;
	}
	uint8_t *base22 = (uint8_t *)malloc0(FILE_SECTOR_SIZE);

	if (base22 == NULL) {
		ERROR("malloc base22 failed\n");
		while (1)
			;
	} else {
		NOTICE("base01=0x%lx, base02=0x%lx, base11=0x%lx, base12=0x%lx, base21=0x%lx, base22=0x%lx\n",
		       (uint64_t)base01, (uint64_t)base02, (uint64_t)base11, (uint64_t)base12,
		       (uint64_t)base21, (uint64_t)base22);
	}

	NOTICE("fau_parallel sdr1:\n");
	ret = SDR_parallel_calc(base01, NULL, base11, NULL, base21, NULL, (uint8_t *)COORD_ADDR, repid, 1, 1,
				FILE_SECTOR_SIZE / 32 - 1);
	if (ret != 0) {
		ERROR("fau_parallel sdr1 failed\n");
		while (1)
			;
	}
#ifdef TEST_CHECK
	inv_dcache_range((uint64_t)base01, REF_LAYER1_SIZE);
	inv_dcache_range((uint64_t)base11, REF_LAYER1_SIZE);
	inv_dcache_range((uint64_t)base21, REF_LAYER1_SIZE);
	inv_dcache_range(REF_LAYER1_ADDR, REF_LAYER1_SIZE);

	NOTICE("fau_parallel sdr1 test verify\n");
	if (memcmp((void *)base01, (void *)REF_LAYER1_ADDR, REF_LAYER1_SIZE)) {
		ERROR("fau%d SDR1 cmp0 failed\n", 0);
		while (1)
			;
	}
	if (memcmp((void *)base11, (void *)REF_LAYER1_ADDR, REF_LAYER1_SIZE)) {
		ERROR("fau%d SDR1 cmp1 failed\n", 1);
		while (1)
			;
	}
	if (memcmp((void *)base21, (void *)REF_LAYER1_ADDR, REF_LAYER1_SIZE)) {
		ERROR("fau%d SDR1 cmp2 failed\n", 2);
		while (1)
			;
	} else {
		NOTICE("fau_parallel sdr1 cmp success\n");
	}
#endif

	NOTICE("fau_parallel sdr2:\n");
	ret = SDR_parallel_calc(base02, base01, base12, base11, base22, base21, (uint8_t *)(COORD_ADDR), repid, 2, 1,
				FILE_SECTOR_SIZE / 32 - 1);
	if (ret != 0) {
		ERROR("fau_parallel failed\n");
		while (1)
			;
	}
#ifdef TEST_CHECK
	inv_dcache_range((uint64_t)base02, REF_LAYER2_SIZE);
	inv_dcache_range((uint64_t)base12, REF_LAYER2_SIZE);
	inv_dcache_range((uint64_t)base22, REF_LAYER2_SIZE);
	inv_dcache_range(REF_LAYER2_ADDR, REF_LAYER2_SIZE);

	if (memcmp((void *)base02, (void *)REF_LAYER2_ADDR, REF_LAYER2_SIZE)) {
		ERROR("fau%d SDR2 cmp0 failed\n", 0);
		while (1)
			;
	}
	if (memcmp((void *)base12, (void *)REF_LAYER2_ADDR, REF_LAYER2_SIZE)) {
		ERROR("fau%d SDR2 cmp1 failed\n", 1);
		while (1)
			;
	}
	if (memcmp((void *)base22, (void *)REF_LAYER2_ADDR, REF_LAYER2_SIZE)) {
		ERROR("fau%d SDR2 cmp2 failed\n", 2);
		while (1)
			;
	} else {
		NOTICE("fau_parallel sdr2 cmp success\n");
	}
#endif

	if (ret)
		ERROR("fau_parallel_test failed\n");
	else
		NOTICE("fau_parallel_test success\n");
	return ret;
}
#endif

static struct mango_test_unit mango_test_list[] = {
	{"c2c burst write", mango_c2c_burst_write_test},
	{"ddr bandwidth mmu on", mango_ddr_bandwidth},
	{"filecoin P1 test", mango_fau_test},
#ifdef TEST_PARALLEL
	{"filecoin P1 parallel test", mango_fau_parallel_test},
#endif
	{"filecoin P1 reset test", mango_fau_reset_test},
};

static struct mango_test_unit mango_test_list_mmu_off[] = {
	{"ddr bandwidth mmu off", mango_ddr_bandwidth},
};

static int mango_test(struct mango_test_unit *list, unsigned int count)
{
	int i, err = 0, tmp;
	struct mango_test_unit *t;

	for (i = 0; i < count; ++i) {
		t = &list[i];

		NOTICE("test case: %s\n", t->name);
		tmp = t->func();
		err |= tmp;
		if (tmp)
			NOTICE("test fail with error code %d\n", tmp);
		else
			NOTICE("test case: %s pass\n", t->name);
	}

	return err;
}

void mango_test_mmu_off(void)
{
	int err;

	NOTICE("MANGO BL2 TEST WITH MMU OFF START\n");
	err = mango_test(mango_test_list_mmu_off,
			ARRAY_SIZE(mango_test_list_mmu_off));
	NOTICE("MANGO BL2 TEST MMU OFF END\n");

	if (err)
		NOTICE("mango bl2 test failed\n");
}

int plat_cli_cmd_process(int flag, int argc, char *const argv[])
{
#ifdef MANGO_ENABLE_BL2_TEST
#ifdef MANGO_HAS_PCIE
	if (test_cmd("msi")) {
		uint32_t pcie_id, link_id;

		if (argc < 3)
			return -1;

		pcie_id = simple_strtoul(argv[1], NULL, 16);
		link_id = simple_strtoul(argv[2], NULL, 16);
		pcie_write_msi(pcie_id, link_id);

		return 0;
	}

	if (test_cmd("pcie_dma")) {
		uint32_t pcie_id, op_mode;
		uint32_t dir = 0;

		if (argc < 3)
			return -1;

		pcie_id = simple_strtoul(argv[1], NULL, 16);
		op_mode = simple_strtoul(argv[2], NULL, 16);
		dir = simple_strtoul(argv[3], NULL, 16);
		pcie_udma_test(pcie_id, op_mode, dir);

		return 0;
	}
#endif
	if (test_cmd("lpc")) {
		struct sdvt_lpc_host_config config = {
			.ctrl_enable_b = 1,
			.ctrl_sync_timeout_b = 1,
			.ctrl_lframe_time_b = 0,
			.ctrl_prescaler_16b = 0xC8, // 20M / 200 = 100K
			.ctrl_ifg_8b = 4, // default
			.ctrl_abort_width_8b = 4, // default
			.irq_enable_18b = 0,
		};

		struct sdvt_lpc_host_command command = {
			.cmd_type_3b = SDVT_LPC_HOST_MEMORY,
			.dir_b = SDVT_LPC_HOST_READ,
			.chan_idsel_3b = 0,
			.size_2b = 1,
			.tc_b = 0,
			.signal_b = 0,
			.msize_4b = 0,
			.dma_rd_more_b = 0,
			.irq_18b = 0,
		};

		print_config(&config);
		init_chip(&config);
		send_command(&command, 0xFFB0E100, 0);
		NOTICE("0x%x\n", mmio_read_32(LPC_BASE + SDVT_LPC_HOST_RD_FIFO));
		return 0;
	}

	if (test_cmd("rxu")) {
		/* rxu depend on riscv reset */
		mango_set_rp_sys_en(0, true);
		sg_rxu_test();
		return 0;
	}

	if (test_cmd("ddr_test")) {
		int err;

		NOTICE("MANGO BL2 TEST START\n");
		err = mango_test(mango_test_list, ARRAY_SIZE(mango_test_list));
		NOTICE("MANGO BL2 TEST END\n");

		if (err)
			NOTICE("mango bl2 test failed\n");

		return 0;
	}

	return -1;
#else
	return 0;
#endif
}

