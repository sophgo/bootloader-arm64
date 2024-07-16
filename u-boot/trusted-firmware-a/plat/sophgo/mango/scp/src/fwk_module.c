#include <fwk_port.h>
#include <fwk_id.h>
#include <fwk_module_idx.h>
#include <mod_timer.h>
#include <mod_system_info.h>
#include <common/debug.h>
#include <errno.h>

extern struct mod_system_info_get_info_api __system_info_api;
extern struct mod_timer_api __timer_api;

struct fwk_port_api {
	fwk_id_t target_id;
	fwk_id_t api_id;
	void *api;
};

struct fwk_port_api fwk_port_api[] = {
	{
		.target_id = FWK_ID_ELEMENT(FWK_MODULE_IDX_TIMER, 0),
		.api_id =
		FWK_ID_API(FWK_MODULE_IDX_TIMER, MOD_TIMER_API_IDX_TIMER),
		.api = &__timer_api,
	},
	{
		.target_id = FWK_ID_MODULE(FWK_MODULE_IDX_SYSTEM_INFO),
		.api_id = FWK_ID_API(FWK_MODULE_IDX_SYSTEM_INFO,
				     MOD_SYSTEM_INFO_GET_API_IDX),
		.api = &__system_info_api,
	},
};

int fwk_module_bind(fwk_id_t target_id, fwk_id_t api_id, const void *api)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fwk_port_api); ++i) {
		if (fwk_port_api[i].target_id.value == target_id.value &&
		    fwk_port_api[i].api_id.value == api_id.value) {
			if (!fwk_port_api[i].api) {
				ERROR("unbind api\n");
				return -ENOSYS;
			} else {
				*(void **)api = fwk_port_api[i].api;
			}
		}
	}

	return 0;
}
