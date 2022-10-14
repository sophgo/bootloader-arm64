#include <mod_timer.h>
#include <delay_timer.h>
#include <common/debug.h>
#include <fwk_status.h>

static int mod_timer_wait(fwk_id_t dev_id, uint32_t ms,
	 bool (*cond)(void*), void *data)
{
	uint64_t expr;

	expr = timeout_init_us(ms * 1000);

	do {
		if (cond(data))
			return FWK_SUCCESS;

	} while (timeout_elapsed(expr));

	ERROR("timer timeout\n");

	return FWK_E_TIMEOUT;
}

struct mod_timer_api __timer_api = {
	.wait = mod_timer_wait,
};

