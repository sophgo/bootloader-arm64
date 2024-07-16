#ifndef __FWK_EVENT_H__
#define __FWK_EVENT_H__

#include <fwk_id.h>

#define FWK_EVENT_PARAMETERS_SIZE 16

struct fwk_event {
    /*! Identifier of the event source */
    fwk_id_t source_id;

    /*! Identifier of the event target */
    fwk_id_t target_id;
    fwk_id_t id;

    /*! Table of event parameters */
    uint8_t params[FWK_EVENT_PARAMETERS_SIZE];
};

#endif
