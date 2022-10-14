#ifndef __FWK_NOTIFICATION_H__
#define __FWK_NOTIFICATION_H__

#include <fwk_id.h>

int fwk_notification_subscribe(fwk_id_t notification_id, fwk_id_t source_id,
			       fwk_id_t target_id);

#endif
