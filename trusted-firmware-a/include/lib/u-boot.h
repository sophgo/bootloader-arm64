/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * workaround for code from u-boot
 */

#ifndef __UBOOT_H_
#define __UBOOT_H_

#include <drivers/console.h>

extern console_t *console_list;
extern uint8_t console_state;
int console_try_getc(void);

#define CONFIG_SYS_CBSIZE	64
#define CONFIG_SYS_MAXARGS	4
#define CONFIG_SYS_PROMPT	"# "
#define ARCH_DMA_MINALIGN	CACHE_WRITEBACK_GRANULE

#define puts printf
#define putc console_putc
#define getchar console_try_getc
#define getcxmodem console_try_getc

#undef EOF /* defined in stdio.h */

typedef unsigned long ulong;

static inline int isblank(char c)
{
	return (c == ' ' || c == '\t');
}

static inline int islower(char c)
{
	return (c >= 'a' && c <= 'z');
}

static inline int isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline int isxdigit(char c)
{
	return (isdigit(c) ||
		(c >= 'A' && c <= 'F') ||
		(c >= 'a' && c <= 'f'));
}

static inline char toupper(char c)
{
	return (c - 0x20 * ((c >= 'a') && (c <= 'z')));
}

#endif
