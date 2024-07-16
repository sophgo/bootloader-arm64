#ifndef __FWK_ID_H__
#define __FWK_ID_H__

#include <stdint.h>
#include <stdbool.h>

/* Identifier type */
enum __fwk_id_type {
    /*
     * Invalid variant.
     *
     * This type is used to catch some classes of missing-initialization errors,
     * and should not be used to initialize new identifiers.
     */
    __FWK_ID_TYPE_INVALID,

    /*
     * None variant.
     *
     * This type is used when an id needs to be explicitly initialized to not
     * refer to any entity.
     */
    __FWK_ID_TYPE_NONE,

    /* Module */
    __FWK_ID_TYPE_MODULE,

    /* Element */
    __FWK_ID_TYPE_ELEMENT,

    /* Sub-element */
    __FWK_ID_TYPE_SUB_ELEMENT,

    /* API */
    __FWK_ID_TYPE_API,

    /* Event */
    __FWK_ID_TYPE_EVENT,

    /* Notification */
    __FWK_ID_TYPE_NOTIFICATION,

    /* Signal */
    __FWK_ID_TYPE_SIGNAL,

    /* Number of defined types */
    __FWK_ID_TYPE_COUNT,
};

enum fwk_id_type {
    /*! None */
    FWK_ID_TYPE_NONE = __FWK_ID_TYPE_NONE,
    /*! Module */
    FWK_ID_TYPE_MODULE = __FWK_ID_TYPE_MODULE,
    /*! Element */
    FWK_ID_TYPE_ELEMENT = __FWK_ID_TYPE_ELEMENT,
    /*! Sub-element */
    FWK_ID_TYPE_SUB_ELEMENT = __FWK_ID_TYPE_SUB_ELEMENT,
    /*! API */
    FWK_ID_TYPE_API = __FWK_ID_TYPE_API,
    /*! Event */
    FWK_ID_TYPE_EVENT = __FWK_ID_TYPE_EVENT,
    /*! Notification */
    FWK_ID_TYPE_NOTIFICATION = __FWK_ID_TYPE_NOTIFICATION,
    /*! Signal */
    FWK_ID_TYPE_SIGNAL = __FWK_ID_TYPE_SIGNAL,
};

/*
 * Generic identifier.
 *
 * This type should be treated as though it is a variant, but where the type
 * switches on all the fields _after_ module_idx. The `type` and `module_idx`
 * fields use the same mask in both variants, but prefer to access them through
 * the \c common field in agnostic code.
 *
 * This identifier fits within the `uint32_t` type, and so should generally be
 * passed by value.
 */
union __fwk_id {
    uint32_t value; /* Integer value */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t reserved : 20; /* Reserved */
    } common; /* Common fields */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t element_idx : 12; /* Element index */
        uint32_t reserved : 8; /* Reserved */
    } element; /* Element variant */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t element_idx : 12; /* Element index */
        uint32_t sub_element_idx : 8; /* Sub-element index */
    } sub_element; /* Sub-element variant */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t api_idx : 4; /* API index */
        uint32_t reserved : 16; /* Reserved */
    } api; /* API variant */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t event_idx : 6; /* Event index */
        uint32_t reserved : 14; /* Reserved */
    } event; /* Event variant */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t signal_idx : 6; /* Signal index */
        uint32_t reserved : 14; /* Reserved */
    } signal; /* Signal variant */

    struct {
        uint32_t type : 4; /* Identifier type */
        uint32_t module_idx : 8; /* Module index */
        uint32_t notification_idx : 6; /* Notification index */
        uint32_t reserved : 14; /* Reserved */
    } notification; /* Notification variant */
};

/*!
 * \brief Generic identifier.
 */
typedef union __fwk_id fwk_id_t;

/*!
 * \brief Generic optional identifier.
 *
 * \details Optionals identifiers are fwk_id_t elements which can be left
 *      undefined. This are only intended to be used for configuration
 *      proposes and should not be used to bypass fwk_id_t checks.
 */
typedef fwk_id_t fwk_optional_id_t;

#define FWK_ID_MODULE_INIT(MODULE_IDX) \
    { \
        .common = { \
            .type = (uint32_t)__FWK_ID_TYPE_MODULE, \
            .module_idx = (uint32_t)MODULE_IDX, \
        }, \
    }

#define FWK_ID_ELEMENT_INIT(MODULE_IDX, ELEMENT_IDX) \
    { \
        .element = { \
            .type = (uint32_t)__FWK_ID_TYPE_ELEMENT, \
            .module_idx = (uint32_t)MODULE_IDX, \
            .element_idx = (uint32_t)ELEMENT_IDX, \
        }, \
    }

#define FWK_ID_ELEMENT(MODULE_IDX, ELEMENT_IDX) \
    ((fwk_id_t)FWK_ID_ELEMENT_INIT(MODULE_IDX, ELEMENT_IDX))

#define FWK_ID_API_INIT(MODULE_IDX, API_IDX) \
    { \
        .api = { \
            .type = (uint32_t)__FWK_ID_TYPE_API, \
            .module_idx = (uint32_t)MODULE_IDX, \
            .api_idx = (uint32_t)API_IDX, \
        }, \
    }

#define FWK_ID_API(MODULE_IDX, API_IDX) \
    ((fwk_id_t)FWK_ID_API_INIT(MODULE_IDX, API_IDX))

#define FWK_ID_NONE_INIT \
    { \
         .common = { \
             .type = (uint32_t)__FWK_ID_TYPE_NONE, \
         }, \
     }

#define FWK_ID_NONE ((fwk_id_t)FWK_ID_NONE_INIT)

#define FWK_ID_MODULE_INIT(MODULE_IDX) \
    { \
        .common = { \
            .type = (uint32_t)__FWK_ID_TYPE_MODULE, \
            .module_idx = (uint32_t)MODULE_IDX, \
        }, \
    }

#define FWK_ID_MODULE(MODULE_IDX) ((fwk_id_t)FWK_ID_MODULE_INIT(MODULE_IDX))

#define FWK_ID_NOTIFICATION_INIT(MODULE_IDX, NOTIFICATION_IDX) \
    { \
        .notification = { \
            .type = (uint32_t)__FWK_ID_TYPE_NOTIFICATION, \
            .module_idx = (uint32_t)MODULE_IDX, \
            .notification_idx = (uint32_t)NOTIFICATION_IDX, \
        }, \
    }


unsigned int fwk_id_get_api_idx(fwk_id_t api_id);
bool fwk_id_is_equal(fwk_id_t left, fwk_id_t right);
bool fwk_id_is_type(fwk_id_t id, enum fwk_id_type type);

#endif
