#include "../mango_misc.h"
#include <mod_system_info.h>

static struct mod_system_info system_info;

static int mod_get_system_info(const struct mod_system_info **sys_info)
{
	struct mango_topology *tp = mango_get_topology();

	system_info.product_id = 0xffffffff;
	system_info.config_id = 0xffffffff;
	system_info.multi_chip_mode = tp->is_multi_socket;
	system_info.chip_id = tp->self;

	*sys_info = &system_info;

	return 0;
}

struct mod_system_info_get_info_api __system_info_api = {
	.get_system_info = mod_get_system_info,
};

