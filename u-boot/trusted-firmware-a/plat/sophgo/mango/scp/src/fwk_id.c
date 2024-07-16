#include <common/debug.h>
#include <fwk_id.h>
#include <stdbool.h>
#include <fwk_port.h>

unsigned int fwk_id_get_api_idx(fwk_id_t api_id)
{
	return api_id.api.api_idx;
}

bool fwk_id_is_equal(fwk_id_t left, fwk_id_t right)
{
	return left.value == right.value;
}

bool fwk_id_is_type(fwk_id_t id, enum fwk_id_type type)
{
	return id.common.type == type;
}
