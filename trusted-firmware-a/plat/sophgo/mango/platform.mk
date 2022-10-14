#
# Copyright (c) 2013-2019, ARM Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

BM_CHIP			:= mango

#MANGO_ENABLE_BL2_TEST	?= yes

# uncomment this for cmn working witout system level cache (l3)
# TF_CFLAGS += -DCONFIG_CMN_DISABLE_SLC
#

PLAT_PATH := plat/sophgo/${BM_CHIP}

CMN600_PATH := ${PLAT_PATH}/icn/cmn600
CMN600_INC := -I$(CMN600_PATH)/src -I$(CMN600_PATH)/include
SCP_PATH := $(PLAT_PATH)/scp
SCP_INC := -I$(SCP_PATH)/include

PLAT_INCLUDES		:=	-Iinclude/lib				\
				-Iinclude/drivers			\
				-Iinclude/drivers/bitmain		\
				-Iinclude/plat/arm/common/		\
				-Iinclude/plat/arm/common/${ARCH}	\
				-Iplat/sophgo/${BM_CHIP}/include	\
				-Ilib/fatfs				\
				-Ilib/crc				\
				$(CMN600_INC) 				\
				$(SCP_INC)

PLAT_BL_COMMON_SOURCES	:=	plat/sophgo/${BM_CHIP}/mango_common.c		\
				plat/sophgo/${BM_CHIP}/mango_console.c		\
				plat/sophgo/${BM_CHIP}/mango_misc.c		\
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
				plat/sophgo/${BM_CHIP}/mango_io_storage.c	\
				plat/sophgo/${BM_CHIP}/plat_helpers.S		\
				plat/sophgo/${BM_CHIP}/mango_bl1_setup.c	\
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
				drivers/mmc/mmc.c			\
				drivers/delay_timer/delay_timer.c	\
				drivers/delay_timer/generic_delay_timer.c	\
				plat/sophgo/${BM_CHIP}/mango_clock.c		\
				plat/sophgo/${BM_CHIP}/mango_io_storage.c	\
				plat/sophgo/${BM_CHIP}/plat_helpers.S		\
				plat/sophgo/${BM_CHIP}/mango_bl2_setup.c	\
				plat/sophgo/${BM_CHIP}/mango_bl2_mem_params_desc.c	\
				plat/sophgo/${BM_CHIP}/mango_image_load.c	\
				drivers/sophgo/pcie/mango_pcie.c	\
				drivers/sophgo/ddr/mango_ddr.c 		\
				drivers/sophgo/ddr/mango_ddr_pld.c	\
				drivers/sophgo/ddr/mango_ddr_asic.c	\
				$(wildcard ${PLAT_PATH}/icn/*.c)	\
				$(wildcard ${PLAT_PATH}/icn/direct_config/*.c)	\
				$(wildcard $(CMN600_PATH)/src/*.c)	\
				$(wildcard $(SCP_PATH)/src/*.c)		\
				common/desc_image_load.c		\
				lib/crc/crc16.c				\
				lib/cli/cli_readline.c			\
				lib/cli/cli_simple.c			\
				lib/ymodem/ymodem.c			\
				lib/ymodem/xyzModem.c			\
				${FATFS_LIB_SOURCES}

ifeq ($(strip $(MANGO_ENABLE_BL2_TEST)), yes)
TF_CFLAGS += -DMANGO_ENABLE_BL2_TEST
BL2_SOURCES		+=	plat/sophgo/$(BM_CHIP)/mango_test.c	\
				drivers/sophgo/fau/mango_fau.c		\
				drivers/sophgo/lpc/sdvt_lpc_host_basic.c \
				drivers/sophgo/rxu/mango_rxu.c
endif

include drivers/arm/gic/v2/gicv2.mk
MANGO_GICV2_SOURCES	:=	${GICV2_SOURCES}			\
				plat/common/plat_gicv2.c		\
				plat/sophgo/${BM_CHIP}/mango_gicv2.c

BL31_SOURCES		+=	drivers/bitmain/i2c/dw_i2c.c		\
				lib/cpus/aarch64/aem_generic.S		\
				lib/cpus/aarch64/cortex_a53.S		\
				plat/common/plat_psci_common.c		\
				drivers/delay_timer/delay_timer.c	\
				drivers/delay_timer/generic_delay_timer.c	\
				drivers/arm/cci/cci.c			\
				plat/sophgo/${BM_CHIP}/mango_pm.c	\
				plat/sophgo/${BM_CHIP}/topology.c	\
				plat/sophgo/${BM_CHIP}/plat_helpers.S	\
				plat/sophgo/${BM_CHIP}/plat_suspend.S	\
				plat/sophgo/${BM_CHIP}/mango_bl31_setup.c	\
				${MANGO_GICV2_SOURCES}

SEPARATE_CODE_AND_RODATA := 1
ENABLE_STACK_PROTECTOR	 := 0
ifneq ($(ENABLE_STACK_PROTECTOR), 0)
	PLAT_BL_COMMON_SOURCES +=plat/sophgo/${BM_CHIP}/mango_stack_protector.c
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

TF_CFLAGS_aarch64 += -DCONFIG_ARCH_BITMAIN -DCONFIG_ARCH_MANGO
export HOSTCCFLAGS_custom += -DCONFIG_ARCH_BITMAIN -DCONFIG_ARCH_MANGO
