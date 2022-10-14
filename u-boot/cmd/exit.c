// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 */

#include <common.h>
#include <command.h>

static int do_exit(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
#ifdef CONFIG_ARCH_BITMAIN
	if (argc > 1)
		return simple_strtol(argv[1], NULL, 10);

	return -2;
#else
	if (argc > 1)
		return dectoul(argv[1], NULL);

	return 0;
#endif
}

U_BOOT_CMD(
	exit,	2,	1,	do_exit,
	"exit script",
	""
);
