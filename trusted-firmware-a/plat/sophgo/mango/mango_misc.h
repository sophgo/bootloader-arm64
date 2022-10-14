#ifndef __MANGO_MISC_H__
#define __MANGO_MISC_H__

#include <cdefs.h>
#include <stdint.h>

#include <drivers/sophgo/mango_pcie.h>

#define MANGO_SOCKET_MAX	2
#define MANGO_PCIE_MAX		2
#define MANGO_DDRCTL_MAX	4
#define MANGO_CLUSTER_MAX	16
#define MANGO_CORES_PER_CLUSTER	4
#define MANGO_CORE_MAX		(MANGO_CLUSTER_MAX * MANGO_CORES_PER_CLUSTER)

#define MANGO_DDR0_BASE		0x00000000UL
#define MANGO_DDR0_SIZE		GB(64)

#define MANGO_MESH_SIZE_X	6
#define MANGO_MESH_SIZE_Y	6

#define MANGO_CLUSTER0_X	1
#define MANGO_CLUSTER0_Y	1

#define MANGO_CLUSTER_MESH_SIZE_X	4
#define MANGO_CLUSTER_MESH_SIZE_Y	4

struct pcie_link {
	int target;
	int mode;
	int speed;
};

struct mango_socket {
	int present;
	int rv_map[MANGO_CLUSTER_MAX];
	struct pcie_link link[MANGO_PCIE_MAX];
};

struct mango_ddrctl {
	unsigned long mem, size;
};

struct mango_topology {
	int is_multi_socket;
	int is_single_spi;
	int self;
	int online_chip_num;
	struct mango_socket socket[MANGO_SOCKET_MAX];
	struct mango_ddrctl ddrctl[MANGO_DDRCTL_MAX];
};

void mango_bl1_multi_socket_init(void);
void mango_bl2_multi_socket_init(void);

struct mango_topology *mango_get_topology(void);

/* declared here for removing coding style check warning */
void __dead2 plat_secondary_cold_boot_setup(void);

int mango_get_socket_id(void);
void mango_set_rp_sys_en(int sid, int en);
uint32_t mango_is_skip_cli_delay(void);

static inline unsigned int get_a4sid_from_xy(unsigned int x, unsigned int y)
{
	return (x - MANGO_CLUSTER0_X) + (y * MANGO_CLUSTER_MESH_SIZE_X);
}

static inline unsigned int get_cluster_id_from_xy(unsigned int x,
						  unsigned int y)
{
	return (x - MANGO_CLUSTER0_X) * MANGO_CLUSTER_MESH_SIZE_Y +
		(y - MANGO_CLUSTER0_Y);
}

static inline void get_xy_from_cluster_id(unsigned int cid,
					  unsigned int *x, unsigned int *y)
{
	*x = cid / MANGO_CLUSTER_MESH_SIZE_Y + MANGO_CLUSTER0_X;
	*y = cid % MANGO_CLUSTER_MESH_SIZE_X + MANGO_CLUSTER0_Y;
}

static inline unsigned int get_a4sid_from_cluster_id(unsigned int cid)
{
	unsigned int x, y;

	get_xy_from_cluster_id(cid, &x, &y);

	return get_a4sid_from_xy(x, y);
}

static inline int get_xp_index_from_xy(int x, int y)
{
	return MANGO_MESH_SIZE_Y * (MANGO_MESH_SIZE_X - 1 - x) +
		(MANGO_MESH_SIZE_Y - 1 - y);
}

static inline int get_xp_index_from_cluster_id(int cid)
{
	unsigned int x, y;

	get_xy_from_cluster_id(cid, &x, &y);

	return get_xp_index_from_xy(x, y);
}

#endif
