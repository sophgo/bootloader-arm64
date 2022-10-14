#ifndef __MOD_TIMER_H__
#define __MOD_TIMER_H__

#include <fwk_id.h>

/*!
 * \addtogroup GroupModules Modules
 * \{
 */

/*!
 * \defgroup GroupModuleTimer Timer HAL
 *
 * \brief Hardware Abstraction Layer for Timers.
 *
 * \details Provides functionality for setting timer events, tracking elapsed
 *      time, and synchronously delaying execution.
 *
 * \{
 */

/*!
 * \brief Timer module API indicies
 */
enum mod_timer_api_idx {
    /*! Timer API index */
    MOD_TIMER_API_IDX_TIMER,

    /*! Alarm API index */
    MOD_TIMER_API_IDX_ALARM,

    /*! Number of APIs */
    MOD_TIMER_API_COUNT,
};

/*!
 * \brief Timer HAL interface
 */
struct mod_timer_api {
    /*!
     * \brief Get the frequency of a given timer.
     *
     * \details Get the frequency in Hertz (Hz) that a timer is running at.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param[out] frequency The timer frequency.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_PARAM The frequency pointer was invalid.
     * \retval One of the other specific error codes described by the framework.
     */
    int (*get_frequency)(fwk_id_t dev_id, uint32_t *frequency);

    /*!
     * \brief Get a counter timestamp that represents a given time period in
     *      microseconds (µS).
     *
     * \note The value of the resulting timestamp is only valid for the given
     *      device, since other timer devices may operate at different rates.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param microseconds Period, in microseconds.
     * \param[out] timestamp The resulting counter timestamp.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_PARAM The timestamp pointer was invalid.
     * \retval One of the other specific error codes described by the framework.
     */
    int (*time_to_timestamp)(fwk_id_t dev_id,
                             uint32_t microseconds,
                             uint64_t *timestamp);

    /*!
     * \brief Get the current counter value of a given timer.
     *
     * \details Directly returns the counter value of the timer at the present
     *      moment.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param[out] counter The counter value.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_PARAM The counter pointer was invalid.
     * \retval One of the other specific error codes described by the framework.
     */
    int (*get_counter)(fwk_id_t dev_id, uint64_t *counter);

    /*!
     * \brief Delay execution by synchronously waiting for a specified amount
     *      of time.
     *
     * \details Blocks the calling thread for the specified amount of time.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param microseconds The amount of time, given in microseconds, to delay.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval One of the other specific error codes described by the framework.
     */
    int (*delay)(fwk_id_t dev_id, uint32_t microseconds);

    /*!
     * \brief Delay execution, waiting until a given condition is true or until
     *      a given timeout period has been exceeded, whichever occurs first.
     *
     * \note The calling thread is blocked until either condition has been met.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param microseconds Maximum amount of time, in microseconds, to wait for
     *      the given condition to be met.
     * \param cond Pointer to the function that evaluates the condition and
     *      which returns a boolean value indicating if it has been met or not.
     *      The condition function is called repeatedly until it returns true,
     *      or until the timeout period has elapsed.
     * \param data Pointer passed to the condition function when it is called.
     *
     * \retval ::FWK_SUCCESS The condition was met before the timeout period
     *      elapsed.
     * \retval ::FWK_E_TIMEOUT The timeout period elapsed before the condition
     *      was met.
     * \retval One of the other specific error codes described by the framework.
     */
    int (*wait)(fwk_id_t dev_id,
                uint32_t microseconds,
                bool (*cond)(void*),
                void *data);

    /*!
     * \brief Get the time difference, expressed in timer ticks, between the
     *      current timer counter value and the given timestamp. This represents
     *      the remaining number of ticks until the given timestamp is reached.
     *
     * \note If the given timestamp is in the past then the remaining_ticks is
     *      set to zero.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param timestamp Timestamp to compare to the current timer value.
     * \param[out] remaining_ticks The remaining number of ticks before
     *      the timer value reaches the given timestamp.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_PARAM The remaining_ticks pointer was invalid.
     * \retval One of the other specific error codes described by the framework.
     *
     * \note remaining_ticks is also a timestamp.
     */
    int (*remaining)(fwk_id_t dev_id,
                     uint64_t timestamp,
                     uint64_t *remaining_ticks);

    /*!
     * \brief Get the number of ticks before the next alarm trigger of a given
     *      timer.
     *
     * \warning If the timer has no active alarm, \p remaining_ticks is not
     *      initialized.
     *
     * \param dev_id Element identifier that identifies the timer device.
     * \param [out] has_alarm \c true if the timer has an active alarm,
     *      otherwise \c false.
     * \param [out] remaining_ticks Number of ticks between now and the next
     *      alarm trigger of the timer identified by \p dev_id.
     *
     * \retval ::FWK_SUCCESS Operation succeeded.
     * \retval ::FWK_E_PARAM One of the parameters is invalid.
     * \return One of the other specific error codes described by the framework.
     */
    int (*get_next_alarm_remaining)(fwk_id_t dev_id,
                                    bool *has_alarm,
                                    uint64_t *remaining_ticks);
};

#endif
