#ifndef __FWK_PORT_H__
#define __FWK_PORT_H__

#include <fwk_id.h>
#include <fwk_assert.h>
#include <common/debug.h>

#define NI()					\
	do {					\
		ERROR("NOT IMPLEMENTED YET\n");	\
		fwk_unexpected();		\
	} while (0)

#endif
