#
# Copyright (c) 2013-2019, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BM_CHIP			:=	bm1684

PLAT_INCLUDES		:=	-Iinclude/lib				\
				-Iinclude/drivers			\
				-Iinclude/drivers/bitmain		\
				-Iinclude/drivers/sophgo		\
				-Iinclude/plat/arm/common/		\
				-Iinclude/plat/arm/common/${ARCH}/	\
				-Iplat/bitmain/${BM_CHIP}/include	\
				-Ilib/fatfs				\
				-Ilib/crc

PLAT_BL_COMMON_SOURCES	:=	plat/bitmain/${BM_CHIP}/bm_common.c	\
				plat/bitmain/${BM_CHIP}/bm_console.c	\
				drivers/ti/uart/${ARCH}/16550_console.S	\
				drivers/bitmain/gpio/dw_gpio.c		\
				drivers/gpio/gpio.c

FATFS_LIB_SOURCES	:=	lib/fatfs/diskio.c			\
				lib/fatfs/ff.c				\
				lib/fatfs/ffsystem.c			\
				lib/fatfs/ffunicode.c

include lib/xlat_tables_v2/xlat_tables.mk
PLAT_BL_COMMON_SOURCES	+=	${XLAT_TABLES_LIB_SRCS}

BL1_SOURCES		+=	drivers/io/io_storage.c			\
				drivers/io/io_fip.c			\
				drivers/io/io_fatfs.c			\
				drivers/io/io_memmap.c			\
				drivers/mmc/mmc.c			\
				drivers/bitmain/bm_sd.c			\
				drivers/bitmain/bm_spif.c		\
				drivers/delay_timer/delay_timer.c	\
				drivers/delay_timer/generic_delay_timer.c	\
				plat/bitmain/${BM_CHIP}/bm_io_storage.c	\
				plat/bitmain/${BM_CHIP}/plat_helpers.S	\
				plat/bitmain/${BM_CHIP}/bm_bl1_setup.c	\
				plat/bitmain/${BM_CHIP}/bm_pcie.c	\
				lib/cpus/aarch64/aem_generic.S		\
				lib/cpus/aarch64/cortex_a53.S		\
				lib/crc/crc16.c				\
				lib/cli/cli_readline.c			\
				lib/cli/cli_simple.c			\
				lib/ymodem/ymodem.c			\
				lib/ymodem/xyzModem.c			\
				${FATFS_LIB_SOURCES}

BL2_SOURCES		+=	drivers/io/io_storage.c			\
				drivers/io/io_fip.c			\
				drivers/io/io_fatfs.c			\
				drivers/io/io_memmap.c			\
				drivers/bitmain/i2c/dw_i2c.c		\
				drivers/bitmain/bm_sd.c			\
				drivers/bitmain/bm_spif.c		\
				drivers/sophgo/dma/sysdma.c		\
				drivers/sophgo/dma/bm_dma.c		\
				drivers/mmc/mmc.c			\
				drivers/delay_timer/delay_timer.c	\
				drivers/delay_timer/generic_delay_timer.c	\
				plat/bitmain/${BM_CHIP}/bm_clock.c		\
				plat/bitmain/${BM_CHIP}/bm_io_storage.c		\
				plat/bitmain/${BM_CHIP}/plat_helpers.S		\
				plat/bitmain/${BM_CHIP}/bm_bl2_setup.c		\
				plat/bitmain/${BM_CHIP}/bm_bl2_mem_params_desc.c	\
				plat/bitmain/${BM_CHIP}/bm_image_load.c			\
				plat/bitmain/${BM_CHIP}/lpddr.c			\
				plat/bitmain/${BM_CHIP}/lpddr_pld.c		\
				plat/bitmain/${BM_CHIP}/bm_pcie.c		\
				common/desc_image_load.c			\
				lib/crc/crc16.c					\
				${FATFS_LIB_SOURCES}

include drivers/arm/gic/v2/gicv2.mk
BM_GICV2_SOURCES	:=	${GICV2_SOURCES}			\
				plat/common/plat_gicv2.c		\
				plat/bitmain/${BM_CHIP}/bm_gicv2.c

BL31_SOURCES		+=	drivers/bitmain/i2c/dw_i2c.c		\
				lib/cpus/aarch64/aem_generic.S		\
				lib/cpus/aarch64/cortex_a53.S		\
				plat/common/plat_psci_common.c		\
				drivers/delay_timer/delay_timer.c	\
				drivers/delay_timer/generic_delay_timer.c	\
				plat/bitmain/${BM_CHIP}/bm_pm.c		\
				plat/bitmain/${BM_CHIP}/topology.c	\
				plat/bitmain/${BM_CHIP}/plat_helpers.S	\
				plat/bitmain/${BM_CHIP}/plat_suspend.S	\
				plat/bitmain/${BM_CHIP}/bm_bl31_setup.c	\
				${BM_GICV2_SOURCES}

SEPARATE_CODE_AND_RODATA := 1
ENABLE_STACK_PROTECTOR	 := 0
ifneq ($(ENABLE_STACK_PROTECTOR), 0)
	PLAT_BL_COMMON_SOURCES += plat/bitmain/${BM_CHIP}/bm_stack_protector.c
endif

# Do not enable SVE
ENABLE_SVE_FOR_NS	:=	0

# Enable all errata workarounds for Cortex-A53
ERRATA_A53_819472		:= 1
ERRATA_A53_824069		:= 1
ERRATA_A53_826319		:= 1
ERRATA_A53_827319		:= 1
ERRATA_A53_835769		:= 1
ERRATA_A53_836870		:= 1
ERRATA_A53_843419		:= 1
ERRATA_A53_855873		:= 1
ERRATA_A53_1530924		:= 1

DEFINES += -DCONFIG_ARCH_BITMAIN -DCONFIG_ARCH_BM1684
export HOSTCCFLAGS_custom += -DCONFIG_ARCH_BITMAIN -DCONFIG_ARCH_BM1684
