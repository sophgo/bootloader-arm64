#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <platform_def.h>
#include <lib/mmio.h>
#include <drivers/sophgo/mango_fau.h>

#define MAX_LEVEL_NUM 5

unsigned long fau_base[3] = {
	FAU0_CFG_BASE, FAU1_CFG_BASE, FAU2_CFG_BASE};
static const uint32_t K256[] = {
		0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
		0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
		0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
		0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
		0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC,
		0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
		0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7,
		0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
		0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
		0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
		0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3,
		0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
		0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5,
		0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
		0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
		0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

#define ROTATE(x, y) (((x) >> (y)) | ((x) << (32 - (y))))
#define Sigma0(x) (ROTATE((x), 2) ^ ROTATE((x), 13) ^ ROTATE((x), 22))
#define Sigma1(x) (ROTATE((x), 6) ^ ROTATE((x), 11) ^ ROTATE((x), 25))
#define sigma0(x) (ROTATE((x), 7) ^ ROTATE((x), 18) ^ ((x) >> 3))
#define sigma1(x) (ROTATE((x), 17) ^ ROTATE((x), 19) ^ ((x) >> 10))

#define Ch(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define BIG_LITTLE_SWAP32(x) ((((*(uint32_t *)&(x)) & 0xff000000) >> 24) | \
							  (((*(uint32_t *)&(x)) & 0x00ff0000) >> 8) |  \
							  (((*(uint32_t *)&(x)) & 0x0000ff00) << 8) |  \
							  (((*(uint32_t *)&(x)) & 0x000000ff) << 24))

/* Avoid undefined behavior                    */
/* https://stackoverflow.com/q/29538935/608639 */
uint32_t B2U32(uint8_t val, uint8_t sh)
{
	return ((uint32_t)val) << sh;
}

/* Process multiple blocks. The caller is responsible for setting the initial */
/*  state, and the caller is responsible for padding the final block.        */
void sha256_process(uint32_t state[8], const uint8_t data[], uint32_t length)
{
	uint32_t a, b, c, d, e, f, g, h, s0, s1, T1, T2;
	uint32_t X[16], i;

	size_t blocks = length / 64;

	while (blocks--) {
		a = state[0];
		b = state[1];
		c = state[2];
		d = state[3];
		e = state[4];
		f = state[5];
		g = state[6];
		h = state[7];

		for (i = 0; i < 16; i++) {
			X[i] = B2U32(data[0], 24) | B2U32(data[1], 16) | B2U32(data[2], 8) | B2U32(data[3], 0);
			data += 4;

			T1 = h;
			T1 += Sigma1(e);
			T1 += Ch(e, f, g);
			T1 += K256[i];
			T1 += X[i];

			T2 = Sigma0(a);
			T2 += Maj(a, b, c);

			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}

		for (; i < 64; i++)	{
			s0 = X[(i + 1) & 0x0f];
			s0 = sigma0(s0);
			s1 = X[(i + 14) & 0x0f];
			s1 = sigma1(s1);

			T1 = X[i & 0xf] += s0 + s1 + X[(i + 9) & 0xf];
			T1 += h + Sigma1(e) + Ch(e, f, g) + K256[i];
			T2 = Sigma0(a) + Maj(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}

		state[0] += a;
		state[1] += b;
		state[2] += c;
		state[3] += d;
		state[4] += e;
		state[5] += f;
		state[6] += g;
		state[7] += h;
	}
}

static inline uint32_t log2N(uint32_t N)
{
	assert(N > 0 && (N & (N - 1)) == 0x0);
	uint32_t L = 0;

	while (N > 1) {
		++L;
		N = N >> 1;
	}
	return L;
}

void dump(void *p, unsigned long l)
{
	unsigned long i;

	for (i = 0; i < l; ++i) {
		if (i % 16 == 0)
			printf("\n %04lx: ", i);
		printf("%02x ", ((unsigned char *)p)[i]);
	}
	printf("\n");
}

int SDR_calc_node0(uint8_t *addr, uint8_t *repid, uint8_t layerid)
{
	uint8_t message[128];

	memset(message, 0x00, sizeof(message));
	memcpy(message, repid, 32);
	message[35] = layerid;
	message[64] = 0x80;
	message[126] = 0x02;

	/* initial state */
	uint32_t state[8] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
		0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
	sha256_process(state, message, sizeof(message));
	for (int i = 0; i < 8; i++) {
		state[i] = BIG_LITTLE_SWAP32(state[i]);
	}
	state[7] &= 0x3fffffff;
	memcpy(addr, (uint8_t *)state, 32);
	flush_dcache_range((uint64_t)addr, 32);

#ifdef DEBUG_FAU
	INFO("node0 address = %p\n", addr);
	dump(addr, 32);
#endif

	return 0;
}

int start_fau_merkel(int i)
{
	mmio_write_32(fau_base[i] + FAU_INTR_MASK, 0x0);
	mmio_write_32(fau_base[i] + FAU_MERKLE_EN, 0x1);
	return 0;
}

int wait_fau_finish_merkel(int i)
{
	while ((mmio_read_32(fau_base[i] + FAU_INTR_STATUS) & 0x02) == 0)
		;
	mmio_write_32(fau_base[i] + FAU_INTR_CLR, 0x2);
	return 0;
}

int start_fau_sdr(int i)
{
	mmio_write_32(fau_base[i] + FAU_INTR_MASK, 0x0);
	mmio_write_32(fau_base[i] + FAU_SDR_EN, 0x1);
	return 0;
}

int wait_fau_finish_sdr(int i)
{
	while ((mmio_read_32(fau_base[i] + FAU_INTR_STATUS) & 0x04) == 0)
		;
	mmio_write_32(fau_base[i] + FAU_INTR_CLR, 0x4);
	return 0;
}

int Merkle_p1_core(const uint64_t *addrs, uint8_t levels, uint32_t loops, int index)
{
	assert(levels > 1 && levels <= MAX_LEVEL_NUM);
	assert(loops > 0);
	for (uint8_t i = 0; i < levels; ++i) {
		assert((addrs[i] & 0x1f) == 0x0);
#ifdef DEBUG_FAU
		NOTICE("level%d addr= 0x%lx\n", i, addrs[i]);
#endif
	}
#ifdef DEBUG_FAU
	NOTICE("fau_base= %lx, levels = %d, loop=%d\n", fau_base[index], levels, loops);
#endif
	mmio_write_32(fau_base[index] + FAU_MERKLE_L0_ADDR_L, addrs[0]);
	mmio_write_32(fau_base[index] + FAU_MERKLE_L0_ADDR_H, addrs[0] >> 32);
	mmio_write_32(fau_base[index] + FAU_MERKLE_L1_ADDR_L, addrs[1]);
	mmio_write_32(fau_base[index] + FAU_MERKLE_L1_ADDR_H, addrs[1] >> 32);
	if (levels > 2) {
		mmio_write_32(fau_base[index] + FAU_MERKLE_L2_ADDR_L, addrs[2]);
		mmio_write_32(fau_base[index] + FAU_MERKLE_L2_ADDR_H, addrs[2] >> 32);
	}
	if (levels > 3) {
		mmio_write_32(fau_base[index] + FAU_MERKLE_L3_ADDR_L, addrs[3]);
		mmio_write_32(fau_base[index] + FAU_MERKLE_L3_ADDR_H, addrs[3] >> 32);
	}
	if (levels > 4) {
		mmio_write_32(fau_base[index] + FAU_MERKLE_L4_ADDR_L, addrs[4]);
		mmio_write_32(fau_base[index] + FAU_MERKLE_L4_ADDR_H, addrs[4] >> 32);
	}
	mmio_write_32(fau_base[index] + FAU_MERKLE_CHILD_TREE, levels << 8 | 1 << (levels - 1));
	mmio_write_32(fau_base[index] + FAU_MERKLE_HOR_LOOP_CNT, loops);
	return 0;
}

typedef struct merkle_p1_data {
	uint32_t NodeNum;
	uint8_t layer;
} merkle_p1_data_t;

int Merkle_p1_calc(uint64_t data_addr, uint64_t sector_size, int index)
{
	uint64_t time = 0;
	merkle_p1_data_t data;

	data.NodeNum = sector_size >> 5;
	data.layer = log2N(data.NodeNum) + 1;
#ifdef DEBUG_FAU
	NOTICE("data_addr = 0x%lx, sector_size=%ld, index=%d\n", data_addr, sector_size, index);
#endif
	assert(data.layer >= 2);
	uint64_t addrs[5];

	addrs[0] = data_addr;
	addrs[1] = data_addr + sector_size;
	uint64_t M = data.NodeNum >> 1;

	for (uint32_t i = 2; i < (data.layer < 5 ? data.layer : 5); ++i) {
		addrs[i] = addrs[i - 1] + M * 32UL;
		M = M >> 1;
	}
	Merkle_p1_core(addrs, data.layer < 5 ? data.layer : 5, M, index);
	time = read_cntpct_el0();
	start_fau_merkel(index);
	wait_fau_finish_merkel(index);
	time = read_cntpct_el0() - time;
	INFO("fau%d merkel calc round 1 time %ld ns\n",
	     index, (uint64_t)(time * 1000000000 / read_cntfrq_el0()));
	data.layer = data.layer - (data.layer < 5 ? data.layer : 5) + 1;
	while (data.layer > 1) {
		addrs[0] = addrs[4];
		for (uint32_t i = 1; i < (data.layer < 5 ? data.layer : 5); ++i) {
			addrs[i] = addrs[i - 1] + M * 32UL;
			M = M >> 1;
		}
		Merkle_p1_core(addrs, data.layer < 5 ? data.layer : 5, M, index);
		time = read_cntpct_el0();
		start_fau_merkel(index);
		wait_fau_finish_merkel(index);
		time = read_cntpct_el0() - time;
		INFO("fau%d merkel calc round x time %ld ns\n",
		     index, (uint64_t)(time * 1000000000 / read_cntfrq_el0()));
		data.layer = data.layer - (data.layer < 5 ? data.layer : 5) + 1;
	}

	assert(M == 1);
	return 0;
}

int Merkle_p1_parallel_calc(uint64_t data_addr0, uint64_t data_addr1, uint64_t data_addr2,
			    uint64_t sector_size0, uint64_t sector_size1, uint64_t sector_size2)
{
	merkle_p1_data_t data0;
	merkle_p1_data_t data1;
	merkle_p1_data_t data2;

	data0.NodeNum = sector_size0 >> 5;
	data0.layer = log2N(data0.NodeNum) + 1;

	assert(data0.layer >= 2);
	uint64_t addrs0[5];

	addrs0[0] = data_addr0;
	addrs0[1] = data_addr0 + sector_size0;
	uint64_t M0 = data0.NodeNum >> 1;

	for (uint32_t i = 2; i < (data0.layer < 5 ? data0.layer : 5); ++i) {
		addrs0[i] = addrs0[i - 1] + M0 * 32UL;
		M0 = M0 >> 1;
	}
	Merkle_p1_core(addrs0, data0.layer < 5 ? data0.layer : 5, M0, 0);

	data1.NodeNum = sector_size1 >> 5;
	data1.layer = log2N(data1.NodeNum) + 1;
	assert(data1.layer >= 2);
	uint64_t addrs1[5];

	addrs1[0] = data_addr1;
	addrs1[1] = data_addr1 + sector_size1;
	uint64_t M1 = data1.NodeNum >> 1;

	for (uint32_t i = 2; i < (data1.layer < 5 ? data1.layer : 5); ++i) {
		addrs1[i] = addrs1[i - 1] + M1 * 32UL;
		M1 = M1 >> 1;
	}
	Merkle_p1_core(addrs1, data1.layer < 5 ? data1.layer : 5, M1, 1);

	data2.NodeNum = sector_size2 >> 5;
	data2.layer = log2N(data2.NodeNum) + 1;
	assert(data2.layer >= 2);
	uint64_t addrs2[5];

	addrs2[0] = data_addr2;
	addrs2[1] = data_addr2 + sector_size2;
	uint64_t M2 = data2.NodeNum >> 1;

	for (uint32_t i = 2; i < (data2.layer < 5 ? data2.layer : 5); ++i) {
		addrs2[i] = addrs2[i - 1] + M2 * 32UL;
		M2 = M2 >> 1;
	}
	Merkle_p1_core(addrs2, data2.layer < 5 ? data2.layer : 5, M2, 2);

	start_fau_merkel(0);
	start_fau_merkel(1);
	start_fau_merkel(2);
	wait_fau_finish_merkel(0);
	wait_fau_finish_merkel(1);
	wait_fau_finish_merkel(2);

	data0.layer = data0.layer - (data0.layer < 5 ? data0.layer : 5) + 1;
	data1.layer = data1.layer - (data1.layer < 5 ? data1.layer : 5) + 1;
	data2.layer = data2.layer - (data2.layer < 5 ? data2.layer : 5) + 1;
	// next, parallel only for the same sector size
	while (data0.layer > 1) {
		addrs0[0] = addrs0[4];
		for (uint32_t i = 1; i < (data0.layer < 5 ? data0.layer : 5); ++i) {
			addrs0[i] = addrs0[i - 1] + M0 * 32UL;
			M0 = M0 >> 1;
		}
		Merkle_p1_core(addrs0, data0.layer < 5 ? data0.layer : 5, M0, 0);

		addrs1[0] = addrs1[4];
		for (uint32_t i = 1; i < (data1.layer < 5 ? data1.layer : 5); ++i) {
			addrs1[i] = addrs1[i - 1] + M1 * 32UL;
			M1 = M1 >> 1;
		}
		Merkle_p1_core(addrs1, data1.layer < 5 ? data1.layer : 5, M1, 1);

		addrs2[0] = addrs2[4];
		for (uint32_t i = 1; i < (data2.layer < 5 ? data2.layer : 5); ++i) {
			addrs2[i] = addrs2[i - 1] + M2 * 32UL;
			M2 = M2 >> 1;
		}
		Merkle_p1_core(addrs2, data2.layer < 5 ? data2.layer : 5, M2, 2);

		start_fau_merkel(0);
		start_fau_merkel(1);
		start_fau_merkel(2);
		wait_fau_finish_merkel(0);
		wait_fau_finish_merkel(1);
		wait_fau_finish_merkel(2);
		data0.layer = data0.layer - (data0.layer < 5 ? data0.layer : 5) + 1;
		data1.layer = data1.layer - (data1.layer < 5 ? data1.layer : 5) + 1;
		data2.layer = data2.layer - (data2.layer < 5 ? data2.layer : 5) + 1;
	}
	assert(M0 == 1);
	assert(M1 == 1);
	assert(M2 == 1);
	return 0;
}

int SDR_core(uint64_t base, uint64_t exp, uint64_t coord, uint8_t *repid,
	     uint8_t layerid, uint32_t nodeid, uint32_t loops, int index)
{
	assert(layerid >= 1 && layerid <= 11);
	assert(nodeid > 0);
	assert(nodeid + loops <= (1 << 30));
	assert((base & 0x1f) == 0x0);
	assert((exp & 0x1f) == 0x0);

#ifdef DEBUG_FAU
	NOTICE("base_addr = %lx, exp_addr=%lx, coord=%lx, layerid=%d, nodeid=%d, loops=%d\n",
	       (uint64_t)base, (uint64_t)exp, (uint64_t)coord, layerid, nodeid, loops);
	dump(repid, 32);
#endif

	mmio_write_32(fau_base[index] + FAU_SDR_LAYER, layerid);
	mmio_write_32(fau_base[index] + FAU_SDR_NODE_ID, nodeid);
	mmio_write_32(fau_base[index] + FAU_SDR_BASE_ADDR_L, base);
	mmio_write_32(fau_base[index] + FAU_SDR_BASE_ADDR_H, base >> 32);

	if (layerid >= 2) {
		mmio_write_32(fau_base[index] + FAU_SDR_EXP_ADDR_L, exp);
		mmio_write_32(fau_base[index] + FAU_SDR_EXP_ADDR_H, exp >> 32);
	}
	mmio_write_32(fau_base[index] + FAU_SDR_COORD_ADDR_L, coord);
	mmio_write_32(fau_base[index] + FAU_SDR_COORD_ADDR_H, coord >> 32);
	mmio_write_32(fau_base[index] + FAU_SDR_NODE_CNT, loops);
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID0, *((uint32_t *)repid));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID1, *((uint32_t *)repid + 1));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID2, *((uint32_t *)repid + 2));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID3, *((uint32_t *)repid + 3));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID4, *((uint32_t *)repid + 4));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID5, *((uint32_t *)repid + 5));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID6, *((uint32_t *)repid + 6));
	mmio_write_32(fau_base[index] + FAU_SDR_REP_ID7, *((uint32_t *)repid + 7));

	return 0;
}

int SDR_calc(uint8_t *base, uint8_t *exp, uint8_t *coord, uint8_t *repid,
	     uint8_t layerid, uint32_t nodeid, uint32_t loops, int index)
{

	int ret = 0;
	uint64_t time = 0;

	assert(layerid >= 1 && layerid <= 11);
	assert(nodeid > 0);
	assert(nodeid + loops <= (1 << 30));
	assert(((uint64_t)base & 0x1f) == 0x0);
	assert(((uint64_t)coord & 0x1f) == 0x0);
	if (layerid > 1)
		assert(((uint64_t)exp & 0x1f) == 0x0);

#ifdef DEBUG_FAU
	NOTICE("base_addr = %lx, exp_addr=%lx, coord=%lx, layerid=%d, nodeid=%d, loops=%d\n",
	       (uint64_t)base, (uint64_t)exp, (uint64_t)coord, layerid, nodeid, loops);
#endif
	uint64_t coord_index = (uint64_t)coord + nodeid * 56UL;

	ret = SDR_core((uint64_t)base, (uint64_t)exp, coord_index, repid, layerid, nodeid, loops, index);
	time = read_cntpct_el0();
	start_fau_sdr(index);
	wait_fau_finish_sdr(index);
	time = read_cntpct_el0() - time;
	INFO("fau%d sdr calc time %ld ns\n", index, (uint64_t)(time * 1000000000 / read_cntfrq_el0()));
	return ret;
}

int SDR_parallel_calc(uint8_t *base0, uint8_t *exp0, uint8_t *base1, uint8_t *exp1, uint8_t *base2, uint8_t *exp2,
		      uint8_t *coord, uint8_t *repid, uint8_t layerid, uint32_t nodeid, uint32_t loops)
{
	int ret = 0;
	uint64_t time = 0;

	assert(layerid >= 1 && layerid <= 11);
	assert(nodeid > 0);
	assert(nodeid + loops <= (1 << 30));
	assert(((uint64_t)base0 & 0x1f) == 0x0);
	assert(((uint64_t)coord & 0x1f) == 0x0);
	if (layerid > 1)
		assert(((uint64_t)exp0 & 0x1f) == 0x0);

	// first calc node 0
	SDR_calc_node0(base0, repid, layerid);
	SDR_calc_node0(base1, repid, layerid);
	SDR_calc_node0(base2, repid, layerid);
	// calc other node 1~G-1
	uint64_t coord_index = (uint64_t)coord + nodeid * 56UL;

	ret = SDR_core((uint64_t)base0, (uint64_t)exp0, coord_index, repid, layerid, nodeid, loops, 0);
	ret = SDR_core((uint64_t)base1, (uint64_t)exp1, coord_index, repid, layerid, nodeid, loops, 1);
	ret = SDR_core((uint64_t)base2, (uint64_t)exp2, coord_index, repid, layerid, nodeid, loops, 2);

	time = read_cntpct_el0();
	start_fau_sdr(0);
	start_fau_sdr(1);
	start_fau_sdr(2);
	wait_fau_finish_sdr(0);
	wait_fau_finish_sdr(1);
	wait_fau_finish_sdr(2);
	time = read_cntpct_el0() - time;
	INFO("fau sdr calc time %ld ns\n", (uint64_t)(time * 1000000000 / read_cntfrq_el0()));
	return ret;
}
