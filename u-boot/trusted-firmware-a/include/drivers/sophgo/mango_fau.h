#ifndef __MANGO_FAU_H__
#define __MANGO_FAU_H__

//#define DEBUG_FAU

#define FAU_INTR_STATUS 0x00
#define FAU_INTR_MASK 0x04
#define FAU_INTR_RAW 0x08
#define FAU_INTR_CLR 0x0C

#define FAU_MERKLE_EN 0x20
#define FAU_MERKLE_RST 0x24
#define FAU_MERKLE_L0_ADDR_L 0x28
#define FAU_MERKLE_L0_ADDR_H 0x2C
#define FAU_MERKLE_L1_ADDR_L 0x30
#define FAU_MERKLE_L1_ADDR_H 0x34
#define FAU_MERKLE_L2_ADDR_L 0x38
#define FAU_MERKLE_L2_ADDR_H 0x3C
#define FAU_MERKLE_L3_ADDR_L 0x40
#define FAU_MERKLE_L3_ADDR_H 0x44
#define FAU_MERKLE_L4_ADDR_L 0x48
#define FAU_MERKLE_L4_ADDR_H 0x4C
#define FAU_MERKLE_CHILD_TREE 0x50
#define FAU_MERKLE_HOR_LOOP_CNT 0x54

#define FAU_SDR_EN 0x80
#define FAU_SDR_RST 0x84
#define FAU_SDR_LAYER 0x88
#define FAU_SDR_NODE_ID 0x8C
#define FAU_SDR_BASE_ADDR_L 0x90
#define FAU_SDR_BASE_ADDR_H 0x94
#define FAU_SDR_EXP_ADDR_L 0x98
#define FAU_SDR_EXP_ADDR_H 0x9C
#define FAU_SDR_COORD_ADDR_L 0xA0
#define FAU_SDR_COORD_ADDR_H 0xA4
#define FAU_SDR_NODE_CNT 0xA8
#define FAU_SDR_REP_ID0 0xB0
#define FAU_SDR_REP_ID1 0xB4
#define FAU_SDR_REP_ID2 0xB8
#define FAU_SDR_REP_ID3 0xBC
#define FAU_SDR_REP_ID4 0xC0
#define FAU_SDR_REP_ID5 0xC4
#define FAU_SDR_REP_ID6 0xC8
#define FAU_SDR_REP_ID7 0xCC

void dump(void *p, unsigned long l);
int start_fau_merkel(int i);
int wait_fau_finish_merkel(int i);
int start_fau_sdr(int i);
int wait_fau_finish_sdr(int i);

int Merkle_p1_core(const uint64_t *addrs, uint8_t levels, uint32_t loops, int index);
int Merkle_p1_calc(uint64_t data_addr, uint64_t sector_size, int index);
int SDR_calc_node0(uint8_t *addr, uint8_t *repid, uint8_t layerid);
int SDR_core(uint64_t base, uint64_t exp, uint64_t coord, uint8_t *repid,
	     uint8_t layerid, uint32_t nodeid, uint32_t loops, int index);
int SDR_calc(uint8_t *base, uint8_t *exp, uint8_t *coord, uint8_t *repid,
	     uint8_t layerid, uint32_t nodeid, uint32_t loops, int index);

int Merkle_p1_parallel_calc(uint64_t data_addr0, uint64_t data_addr1, uint64_t data_addr2, uint64_t sector_size0,
			    uint64_t sector_size1, uint64_t sector_size2);
int SDR_parallel_calc(uint8_t *base0, uint8_t *exp0, uint8_t *base1, uint8_t *exp1, uint8_t *base2, uint8_t *exp2,
		      uint8_t *coord, uint8_t *repid, uint8_t layerid, uint32_t nodeid, uint32_t loops);

#endif

