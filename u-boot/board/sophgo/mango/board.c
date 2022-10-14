/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 * Sharma Bhupesh <bhupesh.sharma@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <dm.h>
#include <malloc.h>
#include <errno.h>
#include <netdev.h>
#include <asm/io.h>
#include <linux/compiler.h>
#include <dm/platform_data/serial_pl01x.h>
#include <asm/armv8/mmu.h>
#include <asm/arch/debug.h>
#include <asm/sections.h>
#include <linux/kernel.h>
#include <bitmain-mcu.h>
#include <misc.h>
#include <net.h>
#include <spi_flash.h>
#include <wdt.h>

#include "mango_regs.h"

#define KERNEL_IMAGE_NAME	"arm64_Image"
#define RAMDISK_IMAGE_NAME	"initramfs_arm64.img"
#define DISK_PART_TABLE_ADDR	0x600000

DECLARE_GLOBAL_DATA_PTR;
#ifdef CONFIG_ARCH_MANGO_PLD
int GET_BOARD_TYPE;
#elif defined(CONFIG_ARCH_MANGO_FPGA)
int GET_BOARD_TYPE = 1;
#endif

enum {
	DPT_MAGIC	= 0x55aa55aa,
};

struct sf_part_info {
	/* disk partition table magic number */
	uint32_t magic;
	char name[32];
	uint32_t offset;
	uint32_t size;
	char reserve[4];
	/* load memory address*/
	uint64_t lma;
};

static int mango_get_sf_part_info(uint32_t addr, struct sf_part_info *info)
{
	int ret;
	struct spi_flash *flash;

	flash = spi_flash_probe(CONFIG_SF_DEFAULT_BUS, CONFIG_SF_DEFAULT_CS,
				CONFIG_SF_DEFAULT_SPEED, CONFIG_SF_DEFAULT_MODE);
	if (!flash) {
		printf("Error - unable to probe SPI flash.\n");
		return -1;
	}

	ret = spi_flash_read(flash, addr, sizeof(struct sf_part_info), (unsigned
			     char *)info);
	if (ret) {
		printf("Error - unable to read MAC address from SPI flash.\n");
		return -1;
	}

	if (info->magic != DPT_MAGIC) {
		printf("bad partition magic %x\n", info->magic);
		return -1;
	}

	return ret;
}

static int mango_get_sf_part_info_by_name(uint32_t addr, const char *name,
					  struct sf_part_info *info)
{
	int ret;
	int offset = addr;

	do {
		ret = mango_get_sf_part_info(offset, info);
		offset += sizeof(struct sf_part_info);

	} while (!ret && memcmp(info->name, name, strlen(name)));

	printf("%s: start:0x%x size:0x%x lma:0x%llx\n", info->name,
	       info->offset, info->size, info->lma);

	return ret;
}

static int mango_setup_kernel_env(const char *name)
{
	int ret;
	struct sf_part_info info;

	ret = mango_get_sf_part_info_by_name(DISK_PART_TABLE_ADDR,
					     name, &info);
	if (ret) {
		printf("failed to get %s partition info\n", name);
		return ret;
	}

	env_set_hex("kernel_addr_r", info.lma);
	env_set_hex("sf_kernel_offset", info.offset);
	env_set_hex("kernel_size", info.size);

	return 0;
}

static int mango_setup_dtb_env(const char *name)
{
	int ret;
	struct sf_part_info info;

	ret = mango_get_sf_part_info_by_name(DISK_PART_TABLE_ADDR,
					     name, &info);
	if (ret) {
		printf("failed to get %s partition info\n", name);
		return ret;
	}

	env_set_hex("fdt_addr_r", info.lma);
	env_set_hex("sf_dtb_offset", info.offset);
	env_set_hex("dtb_size", info.size);

	return 0;
}

static int mango_setup_ramdisk_env(const char *name)
{
	int ret;
	struct sf_part_info info;

	ret = mango_get_sf_part_info_by_name(DISK_PART_TABLE_ADDR,
					     name, &info);
	if (ret) {
		printf("failed to get %s partition info\n", name);
		return ret;
	}

	env_set_hex("ramdisk_addr_r", info.lma);
	env_set_hex("sf_ramdisk_offset", info.offset);
	env_set_hex("ramdisk_size", info.size);

	return 0;
}

static int mango_setup_bootenv(void)
{
	int ret;

	ret = mango_setup_kernel_env(KERNEL_IMAGE_NAME);
	if (ret)
		return ret;

	ret = mango_setup_dtb_env(env_get("dtb_name"));
	if (ret)
		return ret;

	ret = mango_setup_ramdisk_env(RAMDISK_IMAGE_NAME);
	if (ret)
		return ret;

	return 0;
}

static struct mm_region vexpress64_mem_map[] = {
	{
		.virt = 0x4000000000UL,
		.phys = 0x4000000000UL,
		.size = 0x4000000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = PHYS_SDRAM,
		.phys = PHYS_SDRAM,
		.size = PHYS_SDRAM_SIZE,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = vexpress64_mem_map;

static uint32_t get_board_type(void)
{
	return mmio_read_32(BOARD_TYPE_REG);
}

int board_init(void)
{
	return 0;
}

#ifdef CONFIG_BITMAIN_WATCHDOG
static void bm_wdt_start(void)
{
	struct udevice *wdt;

	if (!uclass_get_device_by_name(UCLASS_WDT, "bm16xxwdt@69", &wdt)) {
		if (wdt_start(wdt, CONFIG_WATCHDOG_TIMEOUT_MSECS, 0))
			error("MCU watchdog start failed\n\n");
		else
			printf("MCU watchdog started\n\n");
	}
}

static void bm_wdt_stop(void)
{
	struct udevice *wdt;

	if (!uclass_get_device_by_name(UCLASS_WDT, "bm16xxwdt@69", &wdt)) {
		if (wdt_stop(wdt))
			error("MCU watchdog stop failed\n\n");
		else
			printf("MCU watchdog stopped\n\n");
	}
}

void board_before_jump_linux(void)
{
#ifdef CONFIG_BITMAIN_WATCHDOG
	char *disable_wdt = env_get("disable_wdt");
	/* donot enable watchdog on PCIE mode */
	if (!disable_wdt)
		bm_wdt_start();
#endif
}

#endif

#ifdef CONFIG_BOARD_LATE_INIT
static void __maybe_unused show_mac(void *mac)
{
	int i;

	for (i = 0; i < MCU_MAC_SIZE; ++i) {
		printf("%02x", ((uint8_t *)mac)[i]);
		if (i != MCU_MAC_SIZE - 1)
			printf(":");
	}
	printf("\n");
}

static int setup_mac(void)
{
#if !defined(CONFIG_ARCH_MANGO_PLD) && !defined(CONFIG_ARCH_MANGO_PLD_FPGA)
	int err, i;
	uint8_t mac[MCU_MAC_MAX][MCU_MAC_SIZE];
	char eth[16];
	struct udevice *mcu;

	err = uclass_get_device_by_name(UCLASS_MISC, MCU_DEV_NAME, &mcu);
	if (err) {
		error("%s: no bitmain-mcu found %d\n", __func__, err);
		return err;
	}

	err = misc_call(mcu, MCU_CALL_MAC, NULL, 0, mac, sizeof(mac));
	if (err < 0) {
		error("Failed to get MAC address\n");
		return err;
	}
	for (i = 0; i < err / MCU_MAC_SIZE; ++i) {
		if (i == 0)
			snprintf(eth, sizeof(eth), "ethaddr");
		else
			snprintf(eth, sizeof(eth), "eth%uaddr", i);
#ifdef DEBUG
		printf("%s %pM", eth, mac[i]);
#endif
		if (is_zero_ethaddr(mac[i])) {
			debug("%s mac address not specified, use default\n",
			      eth);
			continue;
		}

		if (!is_valid_ethaddr(mac[i])) {
			error("Invalid MAC address %pM\n", mac[i]);
			continue;
		}

		if (eth_env_set_enetaddr(eth, mac[i]) == -EEXIST)
			printf("MAC%d address has been set before\n", i);
	}
	return 0;
#else
	unsigned char enetaddr[ARP_HLEN];

	net_random_ethaddr(enetaddr);
	eth_env_set_enetaddr("ethaddr", enetaddr);
	printf("Warning: eth0 using random MAC address - %pM\n", enetaddr);
	return 0;
#endif
}

static void select_board(void)
{
	char buf[8];
	int board_type = get_board_type();

	snprintf(buf, sizeof(buf), "%d", board_type);
	env_set("board_type", buf);
	switch (board_type) {
	case MANGO_PLD:
		env_set("dtb_name", "mango_pld.dtb");
		break;
	case MANGO_FPGA:
		env_set("dtb_name", "mango_fpga.dtb");
		break;
	case MANGO_EVB_V0_0:
		env_set("dtb_name", "mango_evb_v0.0.dtb");
		break;
	default:
		printf("unknown board type %d\n", board_type);
		break;
	}
}

int board_late_init(void)
{
	console_record_reset_enable();
#ifdef CONFIG_BITMAIN_WATCHDOG
	/*
	 * for being compatible with old version of MCU firmware,
	 * SM5 and EVB uses designware watchdog to reboot, so if
	 * reboot into u-boot command line, MCU watchdog will timeout.
	 * hence we stop MCU watchdog first.
	 */
	bm_wdt_stop();
#endif
	select_board();
	mango_setup_bootenv();
	setup_mac();
	return 0;
}
#endif

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_SIZE;
	return 0;
}

int dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_SIZE;

	return 0;
}

/*
 * Board specific reset that is system reset.
 */
void reset_cpu(void)
{

}

#if defined(CONFIG_MULTI_DTB_FIT)
static const char * const board_names[] = {
	[MANGO_PLD] = "sophgo-mango-pld",
	[MANGO_FPGA] = "sophgo-mango-fpga",
	[MANGO_EVB_V0_0] = "sophgo-mango-evb-v0.0",
};

int board_fit_config_name_match(const char *name)
{
	int board_type = get_board_type();

	if (ARRAY_SIZE(board_names) < board_type)
		goto not_found;

	if (strcmp(name, board_names[board_type]) == 0) {
		printf("found dtb@%d: %s\n", board_type, name);
		return 0;
	}

not_found:
	return -1;
}
#endif

