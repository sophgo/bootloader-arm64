#ifndef __BM_REGS_H
#define __BM_REGS_H

#include "mmio.h"

#define TOP_BASE	0x50010000
#define PINMUX_BASE	(TOP_BASE + 0x400)

#define PINMUX_PCIEE    0x0
#define PINMUX_SPIF     0x1
#define PINMUX_EMMC     0x2
#define PINMUX_SDIO     0x3
#define PINMUX_RGMII0   0x4
#define PINMUX_RGMII1   0x5
#define PINMUX_PWM1     0x6
#define PINMUX_FAN0     0x7
#define PINMUX_FAN1     0x8
#define PINMUX_IIC0     0x9
#define PINMUX_IIC1     0xa
#define PINMUX_IIC2     0xb
#define PINMUX_UART0    0xc
#define PINMUX_UART1    0xd
#define PINMUX_UART2    0xe

#define IRQ_LEVEL       0
#define IRQ_EDGE        3

#endif
