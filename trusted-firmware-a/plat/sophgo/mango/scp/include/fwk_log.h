#ifndef __FWK_LOG_H__
#define __FWK_LOG_H__

#include <stdio.h>

#if 0
#define fwk_log_printf(...) do { printf(__VA_ARGS__); printf("\n"); } while (0)
#else
#define fwk_log_printf(...) do {} while (0)
#endif

#define FWK_LOG_TRACE(...) fwk_log_printf(__VA_ARGS__)
#define FWK_LOG_INFO(...) fwk_log_printf(__VA_ARGS__)
#define FWK_LOG_WARN(...) fwk_log_printf(__VA_ARGS__)
#define FWK_LOG_ERR(...) fwk_log_printf(__VA_ARGS__)
#define FWK_LOG_CRIT(...) fwk_log_printf(__VA_ARGS__)

#endif
