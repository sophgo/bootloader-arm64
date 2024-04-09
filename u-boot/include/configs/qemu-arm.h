/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2017 Tuomas Tynkkynen
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/* Physical memory map */
#define CFG_SYS_SDRAM_BASE		0x40000000

/* For timer, QEMU emulates an ARMv7/ARMv8 architected timer */

#define CFG_RAMBOOTCOMMAND						\
	"setenv bootargs console=ttyAMA0,115200 earlycon user_debug=31;"	\
	"bootm 0x44000000#config;"

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND CFG_RAMBOOTCOMMAND

#endif /* __CONFIG_H */
