#include <mmio.h>
#include <common/debug.h>
#include "../mango_misc.h"

static inline void plic_register_write(uintptr_t addr, uint32_t value)
{
	mmio_write_32(addr, value);
}

static inline uint32_t plic_register_read(uintptr_t addr)
{
	return mmio_read_32(addr);
}

#define PLIC_MASTER_SOCKET_ID	0

#define CXG1_A4SID		1
#define PLIC_A4SID		3

#define PLIC_BASE		0x7090000000UL
#define PLIC_PRIO1		(PLIC_BASE + 0x0004)
#define PLIC_CFG_BASE		(PLIC_BASE + 0x1fe000)

#define PLIC_TARGET_ID_CTRL	(PLIC_CFG_BASE + 0)
#define PLIC_SOCKET0_CTRL	(PLIC_CFG_BASE + 4)
#define PLIC_SOCKET1_CTRL	(PLIC_CFG_BASE + 8)

#define PLIC_SOCKET0_CLUSTER_CTRL_BASE	(PLIC_CFG_BASE + 0x400)
#define PLIC_SOCKET1_CLUSTER_CTRL_BASE	(PLIC_CFG_BASE + 0x410)

#define PLIC_SOCKET0_A4SID_CTRL	(PLIC_CFG_BASE + 0x800)
#define PLIC_SOCKET1_A4SID_CTRL	(PLIC_CFG_BASE + 0x804)

#define PLIC_SOCKET_ID_SHIFT	0
#define PLIC_SOCKET_ID_MASK	(0x03 << PLIC_SOCKET_ID_SHIFT)

#define PLIC_A4SID_SHIFT	8
#define PLIC_A4SID_MASK		(0xff << PLIC_A4SID_SHIFT)

static inline void plic_setup_cluster_a4sid(uintptr_t base)
{
	uintptr_t reg;
	int i, shift;
	uint32_t tmp;

	for (i = 0; i < MANGO_CLUSTER_MAX; ++i) {
		/* 4 a4sid located in the same register */
		reg = base + i / 4 * 4;
		shift = i % 4 * 8;

		tmp = plic_register_read(reg);
		tmp &= ~(0xff << shift);
		tmp |= get_a4sid_from_cluster_id(i) << shift;
		plic_register_write(reg, tmp);
	}

}

void mango_plic_init(void)
{
	struct mango_topology *tp = mango_get_topology();
	uint32_t tmp;

	if(tp->self == 0) {
		tmp = (PLIC_MASTER_SOCKET_ID << PLIC_SOCKET_ID_SHIFT) |
			(PLIC_A4SID << PLIC_A4SID_SHIFT);
		plic_register_write(PLIC_TARGET_ID_CTRL, tmp);

		plic_setup_cluster_a4sid(PLIC_SOCKET0_CLUSTER_CTRL_BASE);

		if (!tp->is_multi_socket)
			return;

		plic_setup_cluster_a4sid(PLIC_SOCKET1_CLUSTER_CTRL_BASE);
		plic_register_write(PLIC_SOCKET0_A4SID_CTRL, 0);
		plic_register_write(PLIC_SOCKET1_A4SID_CTRL, 1);

		plic_register_write(PLIC_SOCKET0_CTRL, 0x1);
		plic_register_write(PLIC_SOCKET1_CTRL, 0x20000001);

		/* Wait PLIC to finish the connection */
		NOTICE("Wait PLIC connect\n");
		while (plic_register_read(PLIC_SOCKET1_CTRL) & (1U << 31))
			;

		NOTICE("PLIC connected\n");
		plic_register_write(PLIC_PRIO1, 0x1f);
	}
}
