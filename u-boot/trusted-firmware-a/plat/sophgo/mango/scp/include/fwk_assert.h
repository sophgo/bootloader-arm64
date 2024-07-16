#ifndef __FWK_ASSERT_H__
#define __FWK_ASSERT_H__

#include <assert.h>

#define fwk_assert(x)	assert(x)
#define fwk_unexpected() fwk_assert((bool)false)
#define fwk_trap()	fwk_unexpected()

#endif
