/*
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VEXPRESS_AEMV8A_H
#define __VEXPRESS_AEMV8A_H

#define CONFIG_ARCH_MANGO_PLD
//#define CONFIG_ARCH_MANGO_FPGA

#ifndef __ASSEMBLY__
enum {
	MANGO_PLD = 0,
	MANGO_FPGA = 1,
	MANGO_EVB_V0_0 = 2,
};
#endif

/* CONFIG_LEGACY_IMAGE_FORMAT, moved to defconfig file */

#define CONFIG_REMAKE_ELF

/* Link Definitions, ATF loads u-boot here */
/* CONFIG_SYS_TEXT_BASE, moved to defconfig file */

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			(0x7031001000)
#define GICC_BASE			(0x7031002000)

/* For network descriptor, should be enabled when mmu is okay */
#define CONFIG_SYS_NONCACHED_MEMORY	BIT(20) /* 1 MiB */

/* include/generated/autoconf.h would define CONFIG_BAUDRATE from drivers/serial/Kconfig (default 115200) */

/* Physical Memory Map */
#define PHYS_SDRAM		(0x0000000000)
#define PHYS_SDRAM_SIZE		(0x0040000000) /* 1GB */

#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM

#define SYS_CTRL_BASE		0x7030010000
#define BOARD_TYPE_REG		(SYS_CTRL_BASE + 0x23C) // GP_REG31
#define BM_SPIF_BASE		0x7002180000

/* Memory layout, starts from 256MB offset */
#define ENV_MEM_LAYOUT_SETTINGS		\
	"scriptaddr=0x0a000000\0"	\
	"pxefile_addr_r=0x0a000000\0"  \
	"kernel_addr_r=0x00180000\0"	\
	"sf_kernel_offset=0x0\0"	\
	"kernel_size=0x0\0"		\
	"ramdisk_addr_r=0x03000000\0"	\
	"sf_ramdisk_offset=0x0\0"	\
	"ramdisk_size=0x0\0"		\
	"fdt_addr_r=02000000\0"		\
	"sf_dtb_offset=0x0\0"		\
	"dtb_size=0x0\0"


/* default address for bootm command without arguments */
/* CONFIG_SYS_LOAD_ADDR, moved to defconfig file */

/* CONFIG_NR_DRAM_BANKS, moved to defconfig file */
/* CONFIG_SYS_MEMTEST_START, moved to defconfig file */
/* CONFIG_SYS_MEMTEST_END, moved to defconfig file */

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"consoledev=ttyS1\0"		\
	"baudrate=115200\0"		\
	"othbootargs=earlycon\0"	\
	ENV_MEM_LAYOUT_SETTINGS		\
	BOOTENV							\
	"scan_dev_for_boot_part="                               \
	"part list ${devtype} ${devnum} -bootable devplist; "   \
	"env exists devplist || setenv devplist 1 0; "          \
	"for distro_bootpart in ${devplist}; do "                 \
		"if fstype ${devtype} "                           \
				"${devnum}:${distro_bootpart} "   \
				"bootfstype; then "               \
			"run scan_dev_for_boot; "                 \
		"fi; "                                            \
	"done; "                                                  \
	"setenv devplist\0"					  \
	\
	"boot_scripts=boot.scr.sd boot.scr\0"

#define BOOT_TARGET_DEVICES_SPI(func) func(SPI, spi, na)
#define BOOTENV_DEV_NAME_SPI(devtypeu, devtypel, instance) \
	"spi "
#define BOOTENV_DEV_SPI(devtypeu, devtypel, instance) \
	"bootcmd_spi=sf probe && " \
	"sf read ${kernel_addr_r} ${sf_kernel_offset} ${kernel_size} && " \
	"sf read ${fdt_addr_r} ${sf_dtb_offset} ${dtb_size} && " \
	"sf read ${ramdisk_addr_r} ${sf_ramdisk_offset} ${ramdisk_size} && " \
	"setenv bootargs console=${consoledev},${baudrate} ${othbootargs} && " \
	"booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r};\0"

#define CONFIG_BOOTCOMMAND "run distro_bootcmd"
#include <config_distro_bootcmd.h>

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 1) \
	BOOT_TARGET_DEVICES_SPI(func)

#define CONFIG_IPADDR			192.168.1.250
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_GATEWAYIP		192.168.1.1
#define CONFIG_SERVERIP			192.168.1.100
#define CONFIG_HOSTNAME			"unknown"
#define CONFIG_ROOTPATH			"/home/share/nfsroot"



#ifndef __ASSEMBLY__
void board_before_jump_linux(void);
#endif

#endif /* __VEXPRESS_AEMV8A_H */
