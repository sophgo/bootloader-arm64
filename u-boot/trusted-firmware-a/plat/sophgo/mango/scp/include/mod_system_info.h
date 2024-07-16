#ifndef __MOD_SYSTEM_INFO_H__
#define __MOD_SYSTEM_INFO_H__

#include <fwk_id.h>

#include <stdbool.h>
#include <stdint.h>

struct mod_system_info {
    uint32_t product_id;
    uint32_t config_id;
    bool multi_chip_mode;
    uint8_t chip_id;
    const char *name;
};

struct mod_system_info_config {
    fwk_id_t system_info_driver_module_id;
    fwk_id_t system_info_driver_data_api_id;
};

struct mod_system_info_get_driver_data_api {
    struct mod_system_info *(*get_driver_data)(void);
};

struct mod_system_info_get_info_api {
    int (*get_system_info)(const struct mod_system_info **sys_info);
};

enum mod_system_info_api_idx {
    MOD_SYSTEM_INFO_GET_API_IDX,
    MOD_SYSTEM_INFO_API_COUNT
};

#endif
