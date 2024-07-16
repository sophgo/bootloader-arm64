#include <platform_def.h>
#include <mmio.h>
#include <common/debug.h>

#include <mod_cmn600.h>

#include <fwk_id.h>
#include <fwk_macros.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../mango_misc.h"

/*
 * CMN600 nodes
 */
#define NODE_ID_HND   0x84

//DDR
#define NODE_ID_SBSX0 0x10
#define NODE_ID_SBSX1 0x18
#define NODE_ID_SBSX2 0x154
#define NODE_ID_SBSX3 0x15C

#define NODE_ID_CCIX0 0x4
#define NODE_ID_CCIX1 0xC4

#define NODE_HNI_ID0  0x44  //PCIe0
#define NODE_HNI_ID1  0x100 //PCIe1
#define NODE_HNI_ID2  0x140 //PLIC
#define NODE_HNI_ID3  0x68  //FAU0
#define NODE_HNI_ID4  0xA8  //FAU1
#define NODE_HNI_ID5  0xE8  //FAU2

static const unsigned int snf_table[] = {
	NODE_ID_SBSX0, /* Maps to HN-F logical node 0 */
	NODE_ID_SBSX0, /* Maps to HN-F logical node 1 */
	NODE_ID_SBSX2, /* Maps to HN-F logical node 2 */
	NODE_ID_SBSX2, /* Maps to HN-F logical node 3 */
	NODE_ID_SBSX0, /* Maps to HN-F logical node 4 */
	NODE_ID_SBSX0, /* Maps to HN-F logical node 5 */
	NODE_ID_SBSX2, /* Maps to HN-F logical node 6 */
	NODE_ID_SBSX2, /* Maps to HN-F logical node 7 */
	NODE_ID_SBSX1, /* Maps to HN-F logical node 8 */
	NODE_ID_SBSX1, /* Maps to HN-F logical node 9 */
	NODE_ID_SBSX3, /* Maps to HN-F logical node 10 */
	NODE_ID_SBSX3, /* Maps to HN-F logical node 11 */
	NODE_ID_SBSX1, /* Maps to HN-F logical node 12 */
	NODE_ID_SBSX1, /* Maps to HN-F logical node 13 */
	NODE_ID_SBSX3, /* Maps to HN-F logical node 14 */
	NODE_ID_SBSX3, /* Maps to HN-F logical node 15 */
};

static const unsigned int hnf_table[] = {
	72,  80,  136, 144,//SBSX0
	88,  96,  152, 160,//SBSX1
	200, 208, 264, 272,//SBSX2
	216, 224, 280, 288 //SBSX3
};

static struct mod_cmn600_memory_region_map mmap[] = {
	{
		/*
		 * System cache backed region 0
		 * Map: 0x0_0000_0000 - 0x0_FFFF_FFFF (4 GB)
		 */
		.base = UINT64_C(0x000000000),
		.size = UINT64_C(4) * FWK_GIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_SYSCACHE,
	},
	{
		/*
		 * System cache backed region 1
		 * Map: 0x1_0000_0000 - 0x1_FFFF_FFFF (4 GB)
		 */
		.base = UINT64_C(0x100000000),
		.size = UINT64_C(4) * FWK_GIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_SYSCACHE,
	},
	{
		/*
		 * System cache backed region 2
		 * Map: 0x2_0000_0000 - 0x2_FFFF_FFFF (4 GB)
		 */
		.base = UINT64_C(0x200000000),
		.size = UINT64_C(4) * FWK_GIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_SYSCACHE,
	},
	{
		/*
		 * System cache backed region 3
		 * Map: 0x3_0000_0000 - 0x3_FFFF_FFFF (4 GB)
		 */
		.base = UINT64_C(0x300000000),
		.size = UINT64_C(4) * FWK_GIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_SYSCACHE,
	},
		{
		/*
		 * PCIE0 (HNI124)
		 * Map: 0x40_0000_0000 - 0x47_FFFF_FFFF (32 GB)
		 */
		.base = UINT64_C(0x4000000000),
		.size = UINT64_C(32) * FWK_GIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_IO,
		.node_id = NODE_HNI_ID0,
	},
	{
		/*
		 * PCIE1 (HNI252)
		 * Map: 0x48_0000_0000 - 0x4F_FFFF_FFFF (32 GB)
		 */
		.base = UINT64_C(0x4800000000),
		.size = UINT64_C(32) * FWK_GIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_IO,
		.node_id = NODE_HNI_ID1,
	},
	{
		/*
		 * PLIC (HNI320)
		 * Map: 0x70_9000_0000 - 0x70_97FF_FFFF (128 MB)
		 */
		.base = UINT64_C(0x7090000000),
		.size = UINT64_C(128) * FWK_MIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_IO,
		.node_id = NODE_HNI_ID2,
	},
	{
		/*
		 * FAU0 (HNI104)
		 * Map: 0x70_B800_0000 - 0x70_BBFF_FFFF (64 MB)
		 */
		.base = UINT64_C(0x70B8000000),
		.size = UINT64_C(64) * FWK_MIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_IO,
		.node_id = NODE_HNI_ID3,
	},
	{
		/*
		 * FAU1 (HNI168)
		 * Map: 0x70_BC00_0000 - 0x70_BFFF_FFFF (64 MB)
		 */
		.base = UINT64_C(0x70BC000000),
		.size = UINT64_C(64) * FWK_MIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_IO,
		.node_id = NODE_HNI_ID4,
	},
	{
		/*
		 * FAU2 (HNI232)
		 * Map: 0x70_C000_0000 - 0x70_C3FF_FFFF (64 MB)
		 */
		.base = UINT64_C(0x70C0000000),
		.size = UINT64_C(64) * FWK_MIB,
		.type = MOD_CMN600_MEMORY_REGION_TYPE_IO,
		.node_id = NODE_HNI_ID5,
	},
	{
		/* CXG */
		.base = 0,
		.size = PLAT_CHIP_ADDR_SPACE,
		.type = MOD_CMN600_REGION_TYPE_CCIX,
		.node_id = 0,
	},
};

const struct fwk_module_config config_cmn600 = {
	.data = &((struct mod_cmn600_config) {
		  .base = CMN600_BASE,
		  .mesh_size_x = MANGO_MESH_SIZE_X,
		  .mesh_size_y = MANGO_MESH_SIZE_Y,
		  .hnd_node_id = 132,
		  .snf_table = snf_table,
		  .hnf_table = hnf_table,
		  .snf_count = FWK_ARRAY_SIZE(snf_table),
		  .hnf_count = FWK_ARRAY_SIZE(hnf_table),
		  .sa_count  = 0,
		  .mmap_table = mmap,
		  .mmap_count = FWK_ARRAY_SIZE(mmap),
		  .chip_addr_space = PLAT_CHIP_ADDR_SPACE,
		  .clock_id = FWK_ID_NONE_INIT,
		  .hnf_cal_mode = false,
		  }),
};

static void process_node_rni_chip0(void)
{
	uint64_t regValue;

	// PCIe-related configuration
	// rni_cfg_ctl_u_rni_nid64 Offset: 0x810A00
	regValue = mmio_read_64(0x7070810A00);
	mmio_write_64(0x7070810A00, regValue | 0x0000000000000060);

	// rni_cfg_ctl_u_rni_nid192 Offset: 0x0x1810A00
	regValue = mmio_read_64(0x7071810A00);
	mmio_write_64(0x7071810A00, regValue | 0x0000000000000060);
}

static void process_node_rni_chip1(void)
{
	uint64_t regValue;

	// PCIe-related configuration
	// rni_cfg_ctl_u_rni_nid64 Offset: 0x810A00
	regValue = mmio_read_64(0xF070810A00);
	mmio_write_64(0xF070810A00, regValue | 0x0000000000000060);

	// rni_cfg_ctl_u_rni_nid192 Offset: 0x0x1810A00
	regValue = mmio_read_64(0xF071810A00);
	mmio_write_64(0xF071810A00, regValue | 0x0000000000000060);
}

static void process_node_rni(void)
{
	if (mango_get_socket_id()) {
		process_node_rni_chip1();
	} else {
		process_node_rni_chip0();
	}
}

extern const struct fwk_module module_cmn600;
static struct mod_cmn600_ccix_config_api *cmn600_ccix_config_api;
static struct mod_cmn600_ccix_remote_node_config remote_config;

static int mango_cmn600_ccix_init(struct mod_cmn600_ccix_config_api *api)
{
	api->set_config(&remote_config);
	api->exchange_protocol_credit(remote_config.ccix_link_id);
	api->enter_system_coherency(remote_config.ccix_link_id);
	return 0;
}

int mango_cmn600_init(void)
{
	int cxg_node = ARRAY_SIZE(mmap) - 1;
	int i;
	fwk_id_t cmn600_wrapper_id =
		FWK_ID_MODULE(FWK_MODULE_IDX_CMN600_WRAPPER);
	fwk_id_t cmn600_module_id =
		FWK_ID_MODULE(FWK_MODULE_IDX_CMN600);
	fwk_id_t cmn600_api_id =
		FWK_ID_API(FWK_MODULE_IDX_CMN600,
			   MOD_CMN600_API_IDX_CCIX_CONFIG);

	struct mango_topology *tp = mango_get_topology();
	struct mod_cmn600_config *cmn600_data = config_cmn600.data;

	/* remove CXG node in single socket mode, if not transaction with
	 * address in another chip may cause system hang
	 */
	if (!tp->is_multi_socket)
		cmn600_data->mmap_count -= 1;

	if (tp->self == 0) {
		mmap[cxg_node].base = UINT64_C(0x8000000000);
		mmap[cxg_node].node_id = NODE_ID_CCIX0;
	} else {
		mmap[cxg_node].base = UINT64_C(0x0000000000);
		mmap[cxg_node].node_id = NODE_ID_CCIX1;

		for (i = 0; i < ARRAY_SIZE(mmap); ++i)
			if (mmap[i].type ==
			    MOD_CMN600_MEMORY_REGION_TYPE_SYSCACHE)
				mmap[i].base += PLAT_CHIP_ADDR_BASE(tp->self);

		/* change cmn base in top */
		mmio_write_32(TOP_BASE + REG_TOP_RP_CFGM_PERIPHBASE_L,
			      0x70000000);
		mmio_write_32(TOP_BASE + REG_TOP_RP_CFGM_PERIPHBASE_H,
			      0x000000f0);
		cmn600_data->base += PLAT_CHIP_ADDR_BASE(tp->self);
	}

	module_cmn600.init(cmn600_module_id, 0, config_cmn600.data);
	module_cmn600.bind(cmn600_module_id, 1);

	module_cmn600.start(cmn600_module_id);
	process_node_rni();

	module_cmn600.process_bind_request(cmn600_wrapper_id,
				cmn600_module_id,
				cmn600_api_id,
				(const void **)&cmn600_ccix_config_api);

	if (tp->is_multi_socket)
		mango_cmn600_ccix_init(cmn600_ccix_config_api);

	return 0;
}

