#ifndef __MOD_CLOCK_H__
#define __MOD_CLOCK_H__

#include <fwk_id.h>

enum mod_clock_state {
    /*! The clock is stopped */
    MOD_CLOCK_STATE_STOPPED = 0,

    /*! The clock is running */
    MOD_CLOCK_STATE_RUNNING,

    /*! Number of defined clock states */
    MOD_CLOCK_STATE_COUNT
};

enum mod_clock_notification_idx {
     /*! The running state of a clock changed */
    MOD_CLOCK_NOTIFICATION_IDX_STATE_CHANGED,

     /*! The running state of a clock is about to change */
    MOD_CLOCK_NOTIFICATION_IDX_STATE_CHANGE_PENDING,

    /*! Number of defined notifications */
    MOD_CLOCK_NOTIFICATION_IDX_COUNT
};

static const fwk_id_t mod_clock_notification_id_state_changed =
    FWK_ID_NOTIFICATION_INIT(
        FWK_MODULE_IDX_CLOCK,
        MOD_CLOCK_NOTIFICATION_IDX_STATE_CHANGED);

static const fwk_id_t mod_clock_notification_id_state_change_pending =
    FWK_ID_NOTIFICATION_INIT(
        FWK_MODULE_IDX_CLOCK,
        MOD_CLOCK_NOTIFICATION_IDX_STATE_CHANGE_PENDING);

struct clock_notification_params {
    /*!
     * The state that the clock has transitioned to, or is about
     * to transition to.
     */
    enum mod_clock_state new_state;
};

#endif
