#ifndef __FWK_MODULE_H__
#define __FWK_MODULE_H__

#include <fwk_event.h>

enum fwk_module_type {
    /*! Hardware Abstraction Layer */
    FWK_MODULE_TYPE_HAL,
    /*! Device driver */
    FWK_MODULE_TYPE_DRIVER,
    /*! Protocol */
    FWK_MODULE_TYPE_PROTOCOL,
    /*! Service provider */
    FWK_MODULE_TYPE_SERVICE,
    /*! The number of defined module types */
    FWK_MODULE_TYPE_COUNT
};

enum fwk_module_state {
    /*! The module or element has not yet been initialized */
    FWK_MODULE_STATE_UNINITIALIZED = 0,

    /*! The module or element has been initialized successfully */
    FWK_MODULE_STATE_INITIALIZED,

    /*! The module or element has bound successfully */
    FWK_MODULE_STATE_BOUND,

    /*! The module or element has started successfully */
    FWK_MODULE_STATE_STARTED,

    /*! The module or element is suspended */
    FWK_MODULE_STATE_SUSPENDED,

    /*! The number of defined module or element states */
    FWK_MODULE_STATE_COUNT
};

struct fwk_module {
    /*! Module type */
    enum fwk_module_type type;

    /*! Number of APIs defined by the module */
    unsigned int api_count;

    /*! Number of events defined by the module */
    unsigned int event_count;

    #ifdef BUILD_HAS_NOTIFICATION
    /*! Number of notifications defined by the module */
    unsigned int notification_count;
    #endif

    /*!
     * \brief Pointer to the module initialization function.
     *
     * \details This function is invoked during the initialization stage, which
     *      is the first pre-runtime stage. It is called before any module
     *      element initialization is performed. This function must not make any
     *      assumptions about the initialization state of other modules or
     *      their elements.
     *
     * \note This function is \b mandatory and must be implemented by all
     *      modules.
     *
     * \param module_id Identifier of the module being initialized.
     * \param element_count Number of module elements.
     * \param data Module-specific configuration data.
     *
     * \retval ::FWK_SUCCESS The module was initialized successfully.
     * \retval ::FWK_E_NOMEM A memory allocation failed.
     * \return One of the other module-defined error codes.
     */
    int (*init)(fwk_id_t module_id, unsigned int element_count,
                const void *data);

    /*!
     * \brief Pointer to the module element initialization function.
     *
     * \details This function is invoked once for each module element during the
     *      initialization stage. Module element initialization occurs after the
     *      call to the module initialization function and before the call to
     *      the module post-initialization function.
     *
     *      Elements are initialized in the order they are declared in the
     *      module configuration data. The initialization function must not
     *      make any assumptions about the initialization state of other modules
     *      and their elements.
     *
     * \note This function is \b mandatory for modules with elements.
     *
     * \param element_id Identifier of the module element being initialized.
     * \param sub_element_count Number of sub-elements.
     * \param data Element-specific configuration data.
     *
     * \retval ::FWK_SUCCESS The element was initialized successfully.
     * \retval ::FWK_E_NOMEM A memory allocation failed.
     * \return One of the other module-defined error codes.
     */
    int (*element_init)(fwk_id_t element_id, unsigned int sub_element_count,
         const void *data);

    /*!
     * \brief Pointer to the module post-initialization function.
     *
     * \details This function is invoked to finalize the module initialization
     *      once the module and its elements have been successfully initialized.
     *
     *      The framework does not mandate a particular purpose for this
     *      function. It may be used to deal with dependencies between elements,
     *      for example.
     *
     * \note This function is \b optional.
     *
     * \param module_id Identifier of the module element.
     *
     * \retval ::FWK_SUCCESS The module post-initialization was successful.
     * \retval ::FWK_E_NOMEM A memory allocation failed.
     * \return One of the other module-defined error codes.
     */
    int (*post_init)(fwk_id_t module_id);

    /*!
     * \brief Pointer to the bind function.
     *
     * \details This function provides a place for the module and its elements
     *      to bind to other modules and/or elements. Bindings expose APIs
     *      to other modules and elements, and form the core building block of
     *      cross-module interaction.
     *
     *      This function is called by the framework during the bind stage of
     *      the pre-runtime phase. It is called once over the module and then
     *      over all its elements in the initial binding, and a second time to
     *      allow entities with more complex binding strategies to finalize
     *      their bindings.
     *
     *      The first round of calls may be used by a module or element to
     *      discover the entities it needs to bind to, and the second round to
     *      bind to them.
     *
     * \note This function is \b optional.
     *
     * \param id Identifier of the module or element to bind.
     * \param round Current call round, \c 0 for the first round \c 1 for
     *      the second round.
     *
     * \retval ::FWK_SUCCESS The binding was successful.
     * \retval ::FWK_E_ACCESS At least one binding request was rejected.
     * \retval ::FWK_E_NOMEM A memory allocation failed.
     * \return One of the other module-defined error codes.
     */
    int (*bind)(fwk_id_t id, unsigned int round);

    /*!
     * \brief Pointer to the start function.
     *
     * \details This function is called by the framework for the module and then
     *      for all of its elements during the start stage. Elements are
     *      started in the order they are declared in the module configuration
     *      data.
     *
     *      The framework does not mandate a particular purpose for this
     *      function. It may be used to perform any final processing of the
     *      module and its elements before entering the runtime phase. A
     *      possible example of this would be a driver module that must enable
     *      an interrupt after it has completed initialization.
     *
     * \note This function is \b optional.
     *
     * \param id Identifier of the module or element to start.
     *
     * \retval ::FWK_SUCCESS The module or element was successfully started.
     * \return One of the other module-defined error codes.
     */
    int (*start)(fwk_id_t id);

    /*!
     * \brief Pointer to the bind request processing function.
     *
     * \details This function is called by the framework when it receives a
     *      request from another entity to bind to the module, or an element of
     *      the module. It can be called only during the initialization phase
     *      once 'target_id' has been initialized and during the binding phase.
     *
     *      It allows access control, for instance, to deny certain entities
     *      access. Furthermore, in the case where the module includes different
     *      implementations of an API, it allows the module to select the
     *      implementation to provide based on the requesting entity and/or
     *      target entity.
     *
     * \note This function is \b optional.
     *
     * \param source_id Identifier of the module or element making the
     *      bind request.
     * \param target_id Identifier of the module or element to bind to.
     * \param api_id Identifier of the API to return.
     * \param [out] api Pointer to the API implementation to be used by the
     *      requester.
     *
     * \retval ::FWK_SUCCESS The binding request was accepted by the module or
     *      element.
     * \retval ::FWK_E_ACCESS The binding request was rejected by the module or
     *      element.
     * \return One of the other module-defined error codes.
     */
    int (*process_bind_request)(fwk_id_t source_id, fwk_id_t target_id,
                                fwk_id_t api_id, const void **api);

    /*!
     * \brief Process an event.
     *
     * \details This function is called by the framework for events targeting
     *      the module or one of its elements.
     *
     * \note This function is \b optional. If a response event is expected and
     *      the ::fwk_event::is_delayed_response flag is not set by the
     *      processing function then the response event is immediately and
     *      automatically sent to the event's source by the framework. If
     *      however the ::fwk_event::is_delayed_response flag is set by the
     *      processing function then the framework does not send the response
     *      event and it is the responsability of the event's target to send it
     *      at some point.
     *
     * \param event Pointer to the event to be processed.
     * \param [out] resp_event The response event to the provided event if
     *      any.
     *
     * \retval ::FWK_SUCCESS The event was processed successfully.
     * \return One of the other module-defined error codes.
     */
    int (*process_event)(const struct fwk_event *event,
                         struct fwk_event *resp_event);

    /*!
     * \brief Process a notification.
     *
     * \details This function is called by the framework when a notification is
     *      received by a module, element, or sub-element.
     *
     * \note This function is \b optional.
     *
     * \param event Pointer to the notification event to be processed.
     * \param [out] resp_event The response event to the provided event, if
     *      any.
     *
     * \retval ::FWK_SUCCESS The notification was processed successfully.
     * \return One of the other module-defined error codes.
     */
    int (*process_notification)(const struct fwk_event *event,
                                struct fwk_event *resp_event);

    /*!
     * \brief Process a signal.
     *
     * \details This function is called by the framework for signals targeting
     *      the module or one of its elements.
     *
     * \note This function is \b optional.
     *
     * \param target_id Identifier of the target module, element or sub-element.
     * \param signal_id Identifier of the signal to be sent.
     *
     * \retval ::FWK_SUCCESS The signal was processed successfully.
     * \return One of the other module-defined error codes.
     */
    int (*process_signal)(const fwk_id_t target_id, const fwk_id_t signal_id);
};

#define FWK_MODULE_STATIC_ELEMENTS(...) \
    { \
        .type = FWK_MODULE_ELEMENTS_TYPE_STATIC, \
        .table = (const struct fwk_element[])__VA_ARGS__, \
    }

#define FWK_MODULE_STATIC_ELEMENTS_PTR(TABLE) \
    { \
        .type = FWK_MODULE_ELEMENTS_TYPE_STATIC, \
        .table = TABLE, \
    }

#define FWK_MODULE_DYNAMIC_ELEMENTS(GENERATOR) \
    { \
        .type = FWK_MODULE_ELEMENTS_TYPE_DYNAMIC, \
        .generator = (GENERATOR), \
    }

enum fwk_module_elements_type {
    FWK_MODULE_ELEMENTS_TYPE_NONE, /*!< No element table. */
    FWK_MODULE_ELEMENTS_TYPE_STATIC, /*<! Static element table. */
    FWK_MODULE_ELEMENTS_TYPE_DYNAMIC, /*<! Dynamic element table. */
};

struct fwk_module_elements {
    /*!
     * \brief Element table type.
     *
     * \details Elements may be statically defined, or they can be generated
     *      once the module comes online.
     */
    enum fwk_module_elements_type type;

    /*!
     * \brief Element table data.
     */
    union {
        /*!
         * \brief Pointer to the function to get the table of element
         *      descriptions.
         *
         * \param[in] module_id Identifier of the module.
         *
         * \details The table of module element descriptions ends with an
         *      invalid element description where the pointer to the element
         *      name is equal to `NULL`.
         *
         * \warning The framework does not copy the element description data
         *      and keep a pointer to the ones returned by this function.
         *      Pointers returned by this function must thus points to data
         *      with static storage or data stored in memory allocated from
         *      the memory management component.
         *
         * \return Pointer to table of element descriptions.
         */
        const struct fwk_element *(*generator)(fwk_id_t module_id);

        /*!
         * \brief Table of element descriptions.
         *
         * \details The table of module element descriptions ends with an
         *      invalid element description where the pointer to the element
         *      name is equal to `NULL`.
         */
        const struct fwk_element *table;
    };
};

struct fwk_module_config {
    /*! Pointer to the module-specific configuration data */
    void *data;

    /*! Element table */
    struct fwk_module_elements elements;
};

int fwk_module_bind(fwk_id_t target_id, fwk_id_t api_id, const void *api);

#endif
