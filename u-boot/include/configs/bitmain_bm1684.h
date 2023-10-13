/*
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VEXPRESS_AEMV8A_H
#define __VEXPRESS_AEMV8A_H

//#define CONFIG_ARCH_BM1686_PLD
//#define CONFIG_ARCH_BM1686_FPGA

#define USE_GRUB 0

#ifndef __ASSEMBLY__
enum {
	CHIP_BM1684 = 0x16840000,
	CHIP_BM1684X = 0x16860000,
};

enum {
	// BM1684 boards
	BM1684_EVB_V1_2 = 6,
	BM1684_CUST_V1_1 = 4,
	BM1684_CUST_V1_3 = 33,
	BM1684_CUST_V1_4 = 34,
	BM1684_SM5_V1_1_RB = 7,
	BM1684_SM5_V1_2_RB = 17,
	BM1684_SM5_V1_2_TB = 18,
	BM1684_SM5_V2_0_TB = 19,
	BM1684_SE5_V1_1 = 5,
	BM1684_SE5_V1_3 = 8,
	BM1684_SE5_V2_0 = 23,
	BM1684_SE5_V2_1 = 22,
	BM1684_SE5_V2_5 = 26,
	BM1684_SM5M_V0_0_RB = 10,
	BM1684_SM5M_V0_1_RB = 14,
	BM1684_SM5M_V0_2_RB = 20,
	BM1684_SM5M_V3_0_RB = 30,
	BM1684_SM5M_V3_1_RB = 35,
	BM1684_SM5M_V0_0_TB = 11,
	BM1684_SM5M_V0_1_TB = 15,
	BM1684_SM5M_V0_2_TB = 21,
	BM1684_SM5M_V3_0_TB = 31,
	BM1684_SM5M_V3_1_TB = 36,
	BM1684_SE6_CTRL = 27,
	BM1684_SC5_EP = 38,
	BM1684_SC5_MIX = 39,
	BM1684_SE5_V1_4 = 40,

	// BM1684x boards
	BM1684X_PLD = 128,
	BM1684X_FPGA = 129,
	BM1684X_EVB_V0_0 = 130,
	BM1684X_EP = 131,
	BM1684X_SC7_HP300 = 132, // kept for backward compatibility
	BM1684X_MIX = 133,
	BM1684X_SM7M_V0_0_RB = 134,
	BM1684X_SM7_CTRL = 135,
	BM1684X_SM7M_V0_0_CUST_V1 = 136,
	BM1684X_SE7_V1 = 137,
	BM1684X_SM7M_V0_0_RB_CTRL = 138,
	BM1684X_SM7M_V1_0 = 139,
	BM1684X_SM7M_V1_2 = 140,
	BM1684X_SE7_V2_0 = 141,
	BM1684X_SM7_AIRBOX = 142,

};
#endif

/* CONFIG_LEGACY_IMAGE_FORMAT, moved to defconfig file */

#define CONFIG_REMAKE_ELF

/* Link Definitions, ATF loads u-boot here */
/* CONFIG_SYS_TEXT_BASE, moved to defconfig file */

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			(0x50001000)
#define GICC_BASE			(0x50002000)

/* For network descriptor, should be enabled when mmu is okay */
#define CONFIG_SYS_NONCACHED_MEMORY	BIT(20) /* 1 MiB */

/* include/generated/autoconf.h would define CONFIG_BAUDRATE from drivers/serial/Kconfig (default 115200) */

/* Physical Memory Map */
#ifdef CONFIG_ARCH_BM1686_FPGA
#define PHYS_SDRAM		(0x400000000 + 0x40000) /* skip BL31's 256KB */
#else
#define PHYS_SDRAM		(0x300000000 + 0x40000) /* skip BL31's 256KB */
#endif
#if USE_GRUB
#define PHYS_SDRAM_SIZE		(0x200000000 - 0x40000) /* ~8GB, only works on x+x+4+4 DRAM */
#else
#define PHYS_SDRAM_SIZE		(0x040000000 - 0x40000) /* ~1GB */
#endif

#define PHYS_SRAM			(0x10000000)
#define PHYS_SRAM_SIZE		(0x200000) /* 2MB */

#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM

/* Memory layout, starts from 256MB offset */
#ifdef CONFIG_ARCH_BM1686_FPGA
#define ENV_MEM_LAYOUT_SETTINGS		\
	"scriptaddr=0x400040000\0"	\
	"pxefile_addr_r=0x400040000\0"	\
	"fdt_addr_r=0x400100000\0"	\
	"kernel_addr_r=0x400280000\0"	\
	"ramdisk_addr_r=0x410000000\0"  \
	"ramdisk_addr_b=0x410400000\0"  \
	"unzip_addr=0x420000000\0"
#else
#define ENV_MEM_LAYOUT_SETTINGS		\
	"scriptaddr=0x300040000\0"	\
	"pxefile_addr_r=0x300040000\0"	\
	"fdt_addr_r=0x300100000\0"	\
	"kernel_addr_r=0x300280000\0"	\
	"ramdisk_addr_r=0x310000000\0"  \
	"ramdisk_addr_b=0x310400000\0"  \
	"unzip_addr=0x320000000\0"

#endif
/* default address for bootm command without arguments */
/* CONFIG_SYS_LOAD_ADDR, moved to defconfig file */

/* CONFIG_NR_DRAM_BANKS, moved to defconfig file */
/* CONFIG_SYS_MEMTEST_START, moved to defconfig file */
/* CONFIG_SYS_MEMTEST_END, moved to defconfig file */

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"netdev=eth0\0"		\
	"consoledev=ttyS0\0"	\
	"baudrate=115200\0"	\
	"othbootargs=earlycon user_debug=31 \0"		\
	"nfsargs=setenv bootargs root=/dev/nfs init=/init rw "				\
		"nfsroot=${serverip}:${rootpath},v3,tcp "					\
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}:${netdev}:off "	\
		"console=${consoledev},${baudrate} ${othbootargs};\0"				\
	ENV_MEM_LAYOUT_SETTINGS								\
	BOOTENV										\
	"scan_dev_for_boot_part="                                         \
	"part list ${devtype} ${devnum} -bootable devplist; "     \
	"env exists devplist || setenv devplist 1 0; "              \
	"for distro_bootpart in ${devplist}; do "                 \
		"if fstype ${devtype} "                           \
				"${devnum}:${distro_bootpart} "   \
				"bootfstype; then "               \
			"run scan_dev_for_boot; "                 \
		"fi; "                                            \
	"done; "                                                  \
	"setenv devplist\0"					  \
	\
	"boot_scripts=boot.scr.emmc boot.scr.sd boot.scr\0"				\
	"grubcmd=load mmc 1:3 ${fdt_addr_r} /boot/${dtb_name};"			\
		"load mmc 1:1 ${kernel_addr_r} /EFI/ubuntu/grubaa64.efi;"		\
		"bootefi ${kernel_addr_r} ${fdt_addr_r}\0"

#undef CONFIG_BOOTCOMMAND
#if USE_GRUB
#define CONFIG_BOOTCOMMAND "run grubcmd"
#else
#define CONFIG_BOOTCOMMAND "run distro_bootcmd"
#endif
#include <config_distro_bootcmd.h>

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 1) \
	func(MMC, mmc, 0)

#ifdef CONFIG_ARCH_BM1686_PLD
#define CONFIG_RAMBOOTCOMMAND						\
	"setenv bootargs console=${consoledev},9600 ${othbootargs};"	\
	"bootm ${ramdisk_addr_r}#config-pcb${board_type};"
#else
#define CONFIG_RAMBOOTCOMMAND						\
	"setenv bootargs console=${consoledev},${baudrate} ${othbootargs};"	\
	"bootm ${ramdisk_addr_r}#config-pcb${board_type};"
#endif

#define CONFIG_RECBOOTCOMMAND							\
	"setenv bootargs console=${consoledev},${baudrate} ${othbootargs};"	\
	"load mmc 0:2 ${ramdisk_addr_r} recovery.itb;"				\
	"bootm ${ramdisk_addr_r}#config-pcb${board_type};"

#define CONFIG_PCIEBOOTCOMMAND									\
	"setenv bootargs console=${consoledev},${baudrate} clk_ignore_unused ${othbootargs};"   \
	"bootm ${ramdisk_addr_r}#config-pcb${board_type};"

#define CONFIG_IPADDR			192.168.1.250
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_GATEWAYIP		192.168.1.1
#define CONFIG_SERVERIP			192.168.1.100
#define CONFIG_HOSTNAME			"unknown"
#define CONFIG_ROOTPATH			"/home/share/nfsroot"

#define BM_SPIF_BASE			0x06000000

#if CONFIG_IS_ENABLED(MMC_HS200_SUPPORT)
#define MMC_SUPPORTS_TUNING
#endif

/*
 * below definitions should be one hot, it specifies the location of env.
 */
/* CONFIG_ENV_IS_IN_XXX, moved to defconfig file */

#if defined(CONFIG_ENV_IS_IN_SPI_FLASH)
/*
 * env_relocate_spec uses memalign to alloc buffer for reading ENV from
 * SPI flash. during test, if we free(buf) after set_default_env(), seems
 * there will be memory corruption, caused Ethernet receiving wrong data.
 * so we use a fixed buffer instead of memalign~
 */
#define BM_SPIF_BUFFER_ADDR		(PHYS_SDRAM + PHYS_SDRAM_SIZE)
#define CONFIG_ENV_OFFSET		0x1C0000 // 2MB - 256KB
#define CONFIG_ENV_SECT_SIZE		0x10000  // 64KB
#elif defined(CONFIG_ENV_IS_IN_FAT)
/*
 * otherwise, emmc 1st partition which is fat32 format.
 * file name, uboot.env.
 * note: mmc device 0 is on board emmc, mmc device 1 is sd card controller.
 */
/* FAT_ENV_INTERFACE="mmc", moved to defconfig file */
/* FAT_ENV_DEVICE_AND_PART="0:1", moved to defconfig file */
/* FAT_ENV_FILE="uboot.env", moved to defconfig file */
#else
#error env location not specified
#endif
/*
 * SPIF driver can not handle xfer larger than 65535bytes, so the buffer size
 * must not exceed 64KB. and if it's large, himport_r in env_import seems would
 * corrupt other's memory, caused Ethernet receiving wrong data. so here we
 * only alloced 8KB, and actually used less than 2KB~
 */
/* CONFIG_ENV_SIZE=0x2000, 8KB, moved to defconfig file */

#define BM_UPDATE_FW_START_ADDR             (PHYS_SDRAM + PHYS_SDRAM_SIZE + 0x10000000)
#define BM_UPDATE_FW_NAME                   "update.img"
#define BM_UPDATE_FW_FILLBUF_SIZE           (1024 * 512)

#ifndef __ASSEMBLY__
void board_before_jump_linux(void);
#endif

#endif /* __VEXPRESS_AEMV8A_H */
