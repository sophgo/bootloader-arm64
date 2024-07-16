#include <stdbool.h>
#include <common/debug.h>
#include <delay_timer.h>
#include <drivers/sophgo/mango_pcie.h>
#include "../mango_misc.h"
#include "mango_cmn600.h"
#include "mango_plic.h"

void mango_setup_pcie(int target, struct mango_topology *tp)
{
	struct mango_socket *sock;
	struct pcie_link *link;
	int i, j;

	if (!tp->is_multi_socket)
		return;

	sock = &tp->socket[tp->self];

	for (i = 0; i < MANGO_PCIE_MAX; ++i) {

		link = &sock->link[i];

		if (link->target < 0)
			continue;

		mango_ccix_init(i, link->mode, link->speed);
		for (j = 0; j < 8; ++j)
			mango_pcie_set_max_payload(i, PCIE_LINK_0, j,
						   link->mode, PCIE_MPS_512B);
	}
}

void mango_setup_cmn(int target, struct mango_topology *tp)
{
	mango_cmn600_init();
}

void mango_setup_plic(int target, struct mango_topology *tp)
{
	mango_plic_init();
}

/* setup interconnection for single chip */
void mango_setup_icn_single(int target, struct mango_topology *tp)
{
	NOTICE("Setup PCIe\n");
	mango_setup_pcie(target, tp);
	NOTICE("Setup CMN\n");
	mango_setup_cmn(target, tp);
	NOTICE("Setup PLIC\n");
	mango_setup_plic(target, tp);
	NOTICE("Setup chip2chip link done\n");

	/* TODO: check all connections */
	/* pseudo code, assume all connections are ready */
}

/* setup InterConnectioN */
void mango_setup_icn(struct mango_topology *tp)
{
	int i;

	if (tp->is_single_spi) {
		/* TODO: */
		NOTICE("chip%d single spi mode not implemented yet\n",
		       tp->self);
		while (true)
			;

		if (tp->self == 0) {
			/* chip0 should take all the things */
			for (i = 0; i < MANGO_SOCKET_MAX; ++i)
				mango_setup_icn_single(i, tp);
		} else {
			/* other chip should not reach bl2, they should wait in
			 * bl1
			 */
			while (true) {
				ERROR("chip%d should not reach here\n",
				      tp->self);
				mdelay(500);
			}
		}
	} else {
		/* things handled by each chip */
		mango_setup_icn_single(tp->self, tp);
	}
}

