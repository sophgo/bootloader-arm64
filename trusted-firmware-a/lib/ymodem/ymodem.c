// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2000-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

/*
 * Serial up- and download support
 */
#include <platform_def.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <drivers/delay_timer.h>

#include "xyzModem.h"

#define __ALIGN_MASK(x, mask)	(((x) + (mask)) & ~(mask))
#define ALIGN(x, a)		__ALIGN_MASK((x), (typeof(x))(a) - 1)

ulong load_serial_ymodem(ulong offset)
{
	int size;
	int err;
	int res;
	connection_info_t info;
	char ymodemBuf[1024];
	ulong store_addr = ~0;
	ulong addr = 0;

	size = 0;
	info.mode = xyzModem_ymodem;
	res = xyzModem_stream_open(&info, &err);
	if (!res) {

		while ((res =
			xyzModem_stream_read(ymodemBuf, 1024, &err)) > 0) {
			store_addr = addr + offset;
			size += res;
			addr += res;
			memcpy((char *)(store_addr), ymodemBuf, res);

		}

	} else {
		printf("%s\n", xyzModem_error(err));
	}

	xyzModem_stream_close(&err);
	xyzModem_stream_terminate(false, &getcxmodem);

	flush_dcache_range(offset, ALIGN(size, ARCH_DMA_MINALIGN));

	printf("## Total Size      = 0x%08x = %d Bytes\n", size, size);

	return offset;
}
