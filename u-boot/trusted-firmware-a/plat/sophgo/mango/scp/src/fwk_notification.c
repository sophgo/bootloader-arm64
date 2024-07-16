#include <fwk_port.h>
#include <fwk_status.h>

int fwk_notification_subscribe(fwk_id_t notification_id, fwk_id_t source_id,
			       fwk_id_t target_id)
{
	VERBOSE("DUMMY NOTIFICATION SUBSCRIBE\n");
	return FWK_SUCCESS;
}
