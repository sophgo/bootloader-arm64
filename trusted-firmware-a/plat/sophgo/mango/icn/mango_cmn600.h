#ifndef __MANGO_CMN600_H__
#define __MANGO_CMN600_H__

#include <mod_cmn600.h>

int mango_cmn600_init(void);
int mango_cmn600_config_ccix(struct mod_cmn600_ccix_remote_node_config *config);
int mango_cmn600_get_ccix_config(struct mod_cmn600_ccix_host_node_config *config);

#endif
