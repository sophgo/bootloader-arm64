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
#include <console.h>
#include <linux/compiler.h>
#include <dm/platform_data/serial_pl01x.h>
#include <asm/armv8/mmu.h>
#include <asm/arch/debug.h>
#include <asm/sections.h>
#include <linux/kernel.h>
#include <bitmain-mcu.h>
#include <misc.h>
#include <net.h>
#include <wdt.h>
#include <led.h>
#include <version_string.h>

#include "bm1684_regs.h"

#define PCIE_EP_LINKED  (1 << 2) // board has valid PCIe link to some PCIe host

static uint32_t get_chip_id(void)
{
	return mmio_read_32(0x50010000);
}

static uint32_t get_board_type(void)
{
	uint32_t type;

	if (get_chip_id() == CHIP_BM1684)
		type = mmio_read_32(0x10000FFC);
	else {
		type = mmio_read_32(0x5001021C);
	}

	if (type == BM1684_SC5_EP) {
		if (readl(0x500100b4) == 2)
			type = BM1684_SC5_MIX;
	}

	if (type == BM1684X_EP || type == BM1684X_SC7_HP300) {
		if (readl(0x500100b4) == 2)
			type = BM1684X_MIX;
	}

	return type;
}

static uint32_t __maybe_unused get_board_args(void)
{
	uint32_t args;

	if (get_chip_id() == CHIP_BM1684)
		args = mmio_read_32(0x10000FF4);
	else
		args = mmio_read_32(0x50010214);

	return args;

}

void bm_storage_boot_loader_version_uboot(void)
{
	int size = 0;

	size = strlen(version_string);
	for (int i = 0; i < size; i++) {
		mmio_write_8(0x101FB2C0 + i, version_string[i]);
	}

	if (get_chip_id() == CHIP_BM1684) {
		mmio_write_8(0x101FB2C0 + size, '\0');
	} else {
		mmio_write_8(0x101FB2C0 + size, 'X');
		mmio_write_8(0x101FB2C0 + size + 1, '\0');
	}
}

#ifdef CONFIG_PL011_SERIAL
static const struct pl01x_serial_platdata serial_platdata = {
	.base = V2M_UART0,
	.type = TYPE_PL011,
	.clock = CONFIG_PL011_CLOCK,
};

U_BOOT_DEVICE(vexpress_serials) = {
	.name = "serial_pl01x",
	.platdata = &serial_platdata,
};
#endif

static struct mm_region vexpress64_mem_map[] = {
	{
		.virt = 0x0UL,
		.phys = 0x0UL,
		.size = 0x80000000UL, // 2GB
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

static void pinmux_config(int io_type)
{
	switch (io_type) {
	case PINMUX_PCIEE:
		break;
	case PINMUX_SPIF:
		break;
	case PINMUX_EMMC:
		break;
	case PINMUX_SDIO:
		break;
	case PINMUX_RGMII0:
		mmio_clrsetbits_32(PINMUX_BASE + 0x28, (0x3 << 20) | (0xf << 22),
				   (0x1 << 20) | (0x4 << 22)); /* RGMII0_TXD0 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x2c, (0x3 << 20) | (0xf << 22) |
				   (0x3 << 4) | (0xf << 6), (0x1 << 20) | (0x4 << 22) |
				   (0x1 << 4) | (0x4 << 6)); /* RGMII0_TXD1 RGMII0_TXD2 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x30, (0x3 << 20) | (0x3 << 4) | (0xf << 6),
				   (0x1 << 20) | (0x1 << 4) | (0x4 << 6)); /* RGMII0_TXCTRL RGMII0_TXD3 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x34, (0x3 << 20) |
				   (0x3 << 4), (0x1 << 20) | (0x1 << 4)); /* RGMII0_RXD0 RGMII0_RXD1 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x38, (0x3 << 20) |
				   (0x3 << 4), (0x1 << 20) | (0x1 << 4)); /* RGMII0_RXD3 RGMII0_RXD2 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x3c,  (0x3 << 20) | (0xf << 22) | (0x3 << 4),
				   (0x1 << 20) | (0x5 << 22) | (0x1 << 4)); /* RGMII0_RXCTRL RGMII0_TXC */
		mmio_clrsetbits_32(PINMUX_BASE + 0x40, (0x3 << 20) | (0x3 << 4),
				   (0x1 << 20) | (0x1 << 4)); /* RGMII0_RXC RGMII0_REFCLK0 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x44, (0x3 << 20) | (0xf << 22) | (0x3 << 4),
				   (0x1 << 20) | (0x4 << 22) | (0x1 << 4)); /* RGMII0_IRQ RGMII0_MDC */
		mmio_clrsetbits_32(PINMUX_BASE + 0x48, (0x3 << 4) | (0xf << 6),
				   (0x1 << 4) | (0x2 << 6)); /* RGMII0_MDIO */
#ifdef CONFIG_ARCH_BM1686_FPGA
		mmio_clrsetbits_32(PINMUX_BASE + 0x8c, (0x3 << 20), (0x1 << 20)); /* GPIO2 PHY RESET */
#endif
		break;
	case PINMUX_RGMII1:
		mmio_clrsetbits_32(PINMUX_BASE + 0x48, (0x3 << 20) | (0xf << 22),
				   (0x1 << 20) | (0x4 << 22)); /* RGMII1_TXD0 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x4c, (0x3 << 20) | (0xf << 22) |
				   (0x3 << 4) | (0xf << 6), (0x1 << 20) | (0x4 << 22) |
				   (0x1 << 4) | (0x4 << 6)); /* RGMII1_TXD1 RGMII1_TXD2 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x50, (0x3 << 20) | (0x3 << 4) | (0xf << 6),
				   (0x1 << 20) | (0x1 << 4) | (0x4 << 6)); /* RGMII1_TXCTRL RGMII1_TXD3 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x54, (0x3 << 20) |
				   (0x3 << 4), (0x1 << 20) | (0x1 << 4)); /* RGMII1_RXD0 RGMII1_RXD1 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x58, (0x3 << 20) |
				   (0x3 << 4), (0x1 << 20) | (0x1 << 4)); /* RGMII1_RXD3 RGMII1_RXD2 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x5c,  (0x3 << 20) | (0xf << 22) | (0x3 << 4),
				   (0x1 << 20) | (0x5 << 22) | (0x1 << 4)); /* RGMII1_RXCTRL RGMII1_TXC */
		mmio_clrsetbits_32(PINMUX_BASE + 0x60, (0x3 << 20) | (0x3 << 4),
				   (0x1 << 20) | (0x1 << 4)); /* RGMII1_RXC RGMII1_REFCLK0 */
		mmio_clrsetbits_32(PINMUX_BASE + 0x64, (0x3 << 20) | (0xf << 22) | (0x3 << 4),
				   (0x1 << 20) | (0x4 << 22) | (0x1 << 4)); /* RGMII1_IRQ RGMII1_MDC */
		mmio_clrsetbits_32(PINMUX_BASE + 0x68, (0x3 << 4) | (0xf << 6),
				   (0x1 << 4) | (0x2 << 6)); /* RGMII1_MDIO */
#ifdef CONFIG_ARCH_BM1686_FPGA
		mmio_clrsetbits_32(PINMUX_BASE + 0x90, (0x3 << 4), (0x1 << 4)); /* GPIO3 PHY RESET */
#endif
		break;
	case PINMUX_UART0:
		break;
	default:
		break;
	}
}

int board_init(void)
{
	pinmux_config(PINMUX_RGMII0);
	pinmux_config(PINMUX_RGMII1);

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

static int setup_mux(void)
{
	int err;
	struct udevice *mux;
	/*
	 * enable probe pca9545 mux,
	 * for se6 mux switch to CH0(rtc)
	 */
	err = uclass_get_device_by_name(UCLASS_MISC, "mux@70", &mux);
	if (err) {
		error("No mux found\n");
		return err;
	}

	return 0;
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
#if !defined(CONFIG_ARCH_BM1686_PLD) && !defined(CONFIG_ARCH_BM1686_FPGA)
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

	if (get_chip_id() == CHIP_BM1684)
		env_set("chip_type", "bm1684");
	else if (get_chip_id() == CHIP_BM1684X)
		env_set("chip_type", "bm1684x");
	else
		env_set("chip_type", "unknown");

	snprintf(buf, sizeof(buf), "%d", board_type);
	env_set("board_type", buf);

	switch (board_type) {
	case BM1684_EVB_V1_2:
		env_set("dtb_name", "bm1684_evb_v1.2.dtb");
		break;
	case BM1684_CUST_V1_1:
		env_set("dtb_name", "bm1684_cust_v1.1.dtb");
		break;
	case BM1684_CUST_V1_3:
		env_set("dtb_name", "bm1684_cust_v1.3.dtb");
		break;
	case BM1684_CUST_V1_4:
		env_set("dtb_name", "bm1684_cust_v1.4.dtb");
		break;
	case BM1684_SM5_V1_1_RB:
		env_set("dtb_name", "bm1684_sm5_v1.1_rb.dtb");
		break;
	case BM1684_SM5_V1_2_RB:
		env_set("dtb_name", "bm1684_sm5_v1.2_rb.dtb");
		break;
	case BM1684_SM5_V1_2_TB:
		env_set("dtb_name", "bm1684_sm5_v1.2_tb.dtb");
		break;
	case BM1684_SM5_V2_0_TB:
		env_set("dtb_name", "bm1684_sm5_v2.0_tb.dtb");
		break;
	case BM1684_SE5_V1_1:
		env_set("dtb_name", "bm1684_se5_v1.1.dtb");
		break;
	case BM1684_SE5_V1_3:
		env_set("dtb_name", "bm1684_se5_v1.3.dtb");
		break;
	case BM1684_SE5_V1_4:
		env_set("dtb_name", "bm1684_se5_v1.4.dtb");
		break;
	case BM1684_SE5_V2_0:
		env_set("dtb_name", "bm1684_se5_v2.0.dtb");
	case BM1684_SE5_V2_1:
		env_set("dtb_name", "bm1684_se5_v2.1.dtb");
		break;
	case BM1684_SE5_V2_5:
		env_set("dtb_name", "bm1684_se5_v2.5.dtb");
		break;
	case BM1684_SM5M_V0_0_TB:
		env_set("dtb_name", "bm1684_sm5m_v0.0_tb.dtb");
		break;
	case BM1684_SM5M_V0_1_TB:
		env_set("dtb_name", "bm1684_sm5m_v0.1_tb.dtb");
		break;
	case BM1684_SM5M_V0_2_TB:
		env_set("dtb_name", "bm1684_sm5m_v0.2_tb.dtb");
		break;
	case BM1684_SM5M_V3_0_TB:
		env_set("dtb_name", "bm1684_sm5m_v3.0_tb.dtb");
		break;
	case BM1684_SM5M_V3_1_TB:
		env_set("dtb_name", "bm1684_sm5m_v3.1_tb.dtb");
		break;
	case BM1684_SM5M_V0_0_RB:
		env_set("dtb_name", "bm1684_sm5m_v0.0_rb.dtb");
		break;
	case BM1684_SM5M_V0_1_RB:
		env_set("dtb_name", "bm1684_sm5m_v0.1_rb.dtb");
		break;
	case BM1684_SM5M_V0_2_RB:
		env_set("dtb_name", "bm1684_sm5m_v0.2_rb.dtb");
		break;
	case BM1684_SM5M_V3_0_RB:
		env_set("dtb_name", "bm1684_sm5m_v3.0_rb.dtb");
		break;
	case BM1684_SM5M_V3_1_RB:
		env_set("dtb_name", "bm1684_sm5m_v3.1_rb.dtb");
		break;
	case BM1684_SE6_CTRL:
		env_set("dtb_name", "bm1684_se6_ctrl.dtb");
		break;
	case BM1684_SC5_EP:
		env_set("dtb_name", "bm1684_sc5_ep.dtb");
		env_set("disable_wdt", "enable");
		env_set("bootcmd", CONFIG_PCIEBOOTCOMMAND);
		break;
	case BM1684_SC5_MIX:
		env_set("dtb_name", "bm1684_sc5_mix.dtb");
		env_set("disable_wdt", "enable");
		env_set("bootcmd", CONFIG_PCIEBOOTCOMMAND);
		break;
	case BM1684X_PLD:
		env_set("dtb_name", "bm1684x_pld.dtb");
		break;
	case BM1684X_FPGA:
		env_set("dtb_name", "bm1684x_fpga.dtb");
		break;
	case BM1684X_EVB_V0_0:
		env_set("dtb_name", "bm1684x_evb_v0.0.dtb");
		break;
	case BM1684X_SM7M_V0_0_RB:
		env_set("dtb_name", "bm1684x_sm7m_v0.0.dtb");
		break;
	case BM1684X_SM7M_V0_0_RB_CTRL:
		env_set("dtb_name", "bm1684x_sm7m_v0.0_ctrl.dtb");
		break;
	case BM1684X_SM7_CTRL:
		mmio_setbits_32(0x50029000, 0x1); /* set fan run */
		env_set("dtb_name", "bm1684x_sm7_ctrl.dtb");
		break;
	case BM1684X_SM7M_V0_0_CUST_V1:
		env_set("dtb_name", "bm1684x_sm7m_v0.0_cust_v1.dtb");
		break;
	case BM1684X_SM7M_V1_0:
		env_set("dtb_name", "bm1684x_sm7m_v1.0.dtb");
		break;
	case BM1684X_SM7M_V1_2:
		env_set("dtb_name", "bm1684x_sm7m_v1.2.dtb");
		break;
	case BM1684X_EP:
	case BM1684X_SC7_HP300:
		env_set("dtb_name", "bm1684x_ep.dtb");
		env_set("disable_wdt", "enable");
		env_set("bootcmd", CONFIG_PCIEBOOTCOMMAND);
		break;
	case BM1684X_MIX:
		env_set("dtb_name", "bm1684x_mix.dtb");
		env_set("disable_wdt", "enable");
		env_set("bootcmd", CONFIG_PCIEBOOTCOMMAND);
		break;
	case BM1684X_SE7_V1:
		env_set("dtb_name", "bm1684x_se7_v1.dtb");
		break;
	case BM1684X_SE7_V2_0:
		env_set("dtb_name", "bm1684x_se7_v2_0.dtb");
		break;
	case BM1684X_SM7_AIRBOX:
		env_set("dtb_name", "bm1684x_sm7_airbox.dtb");
		break;
	case BM1684X_SM7M_V1_0_RB_CTRL:
		env_set("dtb_name", "bm1684x_sm7m_v0.0_ctrl.dtb");
		break;
	default:
		printf("unknown board type %d\n", board_type);
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

	setup_mac();
	setup_mux();
	env_set("recboot", CONFIG_RECBOOTCOMMAND);
	bm_storage_boot_loader_version_uboot();
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
	gd->bd->bi_dram[1].start = PHYS_SRAM;
	gd->bd->bi_dram[1].size =  PHYS_SRAM_SIZE;
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
	[BM1684_EVB_V1_2] = "bitmain-bm1684-evb-v1.2",
	[BM1684_CUST_V1_1] = "bitmain-bm1684-cust-v1",
	[BM1684_CUST_V1_3] = "bitmain-bm1684-cust-v1",
	[BM1684_CUST_V1_4] = "bitmain-bm1684-cust-v1",
	[BM1684_SM5_V1_1_RB] = "bitmain-bm1684-sm5-v1",
	[BM1684_SM5_V1_2_RB] = "bitmain-bm1684-sm5-v1",
	[BM1684_SM5_V1_2_TB] = "bitmain-bm1684-sm5-v1",
	[BM1684_SM5_V2_0_TB] = "bitmain-bm1684-sm5-v1",
	[BM1684_SE5_V1_1] = "bitmain-bm1684-se5-v1.1",
	[BM1684_SE5_V1_3] = "bitmain-bm1684-se5-v1.1",
	[BM1684_SE5_V1_4] = "bitmain-bm1684-se5-v1.1",
	[BM1684_SE5_V2_0] = "bitmain-bm1684-se5-v2",
	[BM1684_SE5_V2_1] = "bitmain-bm1684-se5-v2",
	[BM1684_SE5_V2_5] = "bitmain-bm1684-se5-v2",
	[BM1684_SM5M_V0_0_TB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V0_1_TB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V0_2_TB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V3_0_TB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V3_1_TB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V0_0_RB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V0_1_RB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V0_2_RB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V3_0_RB] = "bitmain-bm1684-sm5m",
	[BM1684_SM5M_V3_1_RB] = "bitmain-bm1684-sm5m",
	[BM1684_SE6_CTRL] = "bitmain-bm1684-se6-ctrl",
	[BM1684_SC5_EP] = "bitmain-bm1684-evb-v1.2",
	[BM1684_SC5_MIX] = "bitmain-bm1684-evb-v1.2",

	[BM1684X_PLD] = "bitmain-bm1684x-pld",
	[BM1684X_FPGA] = "bitmain-bm1684x-fpga",
	[BM1684X_EVB_V0_0] = "bitmain-bm1684x-evb-v0.0",
	[BM1684X_EP] = "bitmain-bm1684x-ep",
	[BM1684X_SC7_HP300] = "bitmain-bm1684x-ep",
	[BM1684X_MIX] = "bitmain-bm1684x-ep",
	[BM1684X_SM7M_V0_0_RB] = "bitmain-bm1684x-sm7m-v0.0",
	[BM1684X_SM7M_V0_0_RB_CTRL] = "bitmain-bm1684x-sm7m-ctrl",
	[BM1684X_SM7_CTRL] = "bitmain-bm1684x-sm7-ctrl",
	[BM1684X_SM7M_V0_0_CUST_V1] = "bitmain-bm1684x-sm7m-v0.0-cust-v1",
	[BM1684X_SE7_V1] = "bitmain-bm1684x-se7-v1",
	[BM1684X_SM7M_V1_0] = "bitmain-bm1684x-sm7m-v1.0",
	[BM1684X_SM7M_V1_2] = "bitmain-bm1684x-sm7m-v1.0",
	[BM1684X_SE7_V2_0] = "bitmain-bm1684x-sm7m-v1.0",
	[BM1684X_SM7_AIRBOX] = "bitmain-bm1684x-sm7m-v0.0-cust-v1",
	[BM1684X_SM7M_V1_0_RB_CTRL] = "bitmain-bm1684x-sm7m-v1.0-ctrl",
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

