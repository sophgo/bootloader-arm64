#include "mango_misc.h"
#include "mango_common.h"
#include "icn/mango_icn.h"
#include <gpio.h>
#include <mmio.h>
#include <delay_timer.h>
#include <platform_def.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <lib/crc16.h>
#include <lib/cli.h>
#include <i2c.h>
#include <dw_gpio.h>
#include <lib/fatfs/ff.h>

#define MANGO_FORCE_ENABLE_RISCV
/* disable SLC for a53 only */
#define MANGO_A53_SLC_OFF

#ifndef KB
#undef KB
#endif
#define KB(n)			(((n) * 1024ULL))

#ifndef MB
#undef MB
#endif
#define MB(n)			(KB(n) * 1024)

#ifdef GB
#undef GB
#endif
#define GB(n)			(MB(n) * 1024)

#define MANGO_DBGI2C_ADDR_BASE	0x40

/* BOOTROM */
#define MANGO_BOOTROM_BASE	BOOTROM_BASE
#define MANGO_BOOTROM_SIZE	BOOTROM_SIZE
#define MANGO_BOOTROM_END	(MANGO_BOOTROM_BASE + MANGO_BOOTROM_SIZE)

/* Serial Flash */
#define MANGO_FLASH0_BASE	FLASH0_BASE

/* SYS CTRL */
#define MANGO_TOP_BASE		TOP_BASE
#define MANGO_TOP_SIZE		KB(4)
#define MANGO_PINMUX_BASE	(MANGO_TOP_BASE + MANGO_TOP_SIZE)
#define MANGO_PINMUX_SIZE	KB(4)
#define MANGO_CLOCK_GATE_BASE	(MANGO_PINMUX_BASE + MANGO_PINMUX_SIZE)
#define MANGO_CLOCK_GATE_SIZE	KB(4)
#define MANGO_SOFT_RESET_BASE	(MANGO_CLOCK_GATE_BASE + MANGO_CLOCK_GATE_SIZE)

/* TOP */
#define MANGO_TOP_CHIP_VERSION_OFFSET		0x0000
#define MANGO_TOP_CONF_INFORMATION_OFFSET	0x0004
#define MANGO_TOP_MISC_CTRL_OFFSET		0x0008
#define MANGO_TOP_DEBUG_I2C_ID_OFFSET		0x0040
#define MANGO_TOP_DDR_SIZE_OFFSET		0x0054
#define MANGO_TOP_RP_CPU_VENDOR_ID_L_OFFSET	0x0340
#define MANGO_TOP_RP_CPU_VENDOR_ID_H_OFFSET	0x0344

#define MANGO_TOP_RP_CPU_APB_BASE_L_OFFSET	0x0348
#define MANGO_TOP_RP_CPU_APB_BASE_H_OFFSET	0x034c

#define MANGO_TOP_RP_CPU_RVBA_L_OFFSET		0x0350
#define MANGO_TOP_RP_CPU_RVBA_H_OFFSET		0x0354

#define MANGO_TOP_RP_CPU_SEC_ACC_OFFSET		0x360

#define MANGO_TOP_MP0_STATUS_REG_OFFSET		0x380
#define MANGO_TOP_MP0_CONTROL_REG_OFFSET	0x384

#define MANGO_TOP_REG(name) \
	(MANGO_TOP_BASE + MANGO_TOP_ ## name ## _OFFSET)

/* unified address of top register */
#define MANGO_TOP_REG_UA(sid, name) \
	(PLAT_CHIP_ADDR_BASE(sid) + MANGO_TOP_REG(name))

#define MANGO_DDR_PA_MAX_BITS		40
#define MANGO_TOP_DDR_SIZE_SHIFT	8

/* PIN MUX */
#define MANGO_PIN_CFG_DRIVE_BY_IP		(1 << 11)
#define MANGO_PIN_CFG_SCHMITT_TRIGGER_ENABLE	(1 << 10)
#define MANGO_PIN_CFG_PULL_ENABLE		(1 << 0)
#define MANGO_PIN_CFG_PULL_UP			(1 << 1)
#define MANGO_PIN_CFG_DRIVING_SEL(n)		((n) << 6)
#define MANGO_PIN_CFG_PINMUX_SEL(n)		((n) << 4)

#define MANGO_PINMUX_GPIO0			(109)
#define MANGO_PINMUX_GPIO1			(110)
#define MANGO_PINMUX_GPIO2			(111)
#define MANGO_PINMUX_GPIO3			(112)

/* RISC-V Firmware */
#define MANGO_RVFW_OFFSET	(MB(4) + KB(256))
#define MANGO_RVFW_SIZE		(MB(4))
/* "RVFW" */
#define MANGO_RVFW_TAG		0x57465652

/* load zsbl from spi flash */
#define DISK_PART_TABLE_ADDR	0x600000
#define CONV_FR(a) (0 - (a)) // convert fatfs result to ATF style

enum {
	DPT_MAGIC	= 0x55aa55aa,
};

int mango_get_socket_id(void)
{
	return (mmio_read_32(MANGO_TOP_REG(CONF_INFORMATION)) >> 16) & 0x03;
}

static int mango_is_multi_socket_mode(void)
{
	return mmio_read_32(MANGO_TOP_REG(CONF_INFORMATION)) >> 15;
}

static int mango_is_single_spi_mode(void)
{
	return (mmio_read_32(MANGO_TOP_REG(CONF_INFORMATION)) >> 7) & 1;
}

static int mango_is_a53_master_mode(void)
{
	return (mmio_read_32(MANGO_TOP_REG(CONF_INFORMATION)) >> 6) & 1;
}

uint32_t mango_is_skip_cli_delay(void)
{
	return mmio_read_32(MANGO_TOP_REG(CONF_INFORMATION)) &
			    BOOTSEL_SKIP_CLI_DELAY;
}

static int mango_pin_init(int pin, int cfg)
{
	int offset, shift;
	uint32_t value;
	uintptr_t reg;

	offset = (pin / 2) * 4;
	shift = (pin % 2) * 16;
	reg = MANGO_PINMUX_BASE + offset;

	value = mmio_read_32(reg);
	value &= 0xffff << shift;
	value |= cfg << shift;
	mmio_write_32(reg, value);

	return 0;
}

/* warning: only apply to heartbeat pins */
static void mango_pin_init_gpo(int pin, int gpio)
{
	gpio_set_direction(gpio, GPIO_DIR_OUT);
	/* drive by ip,
	 * disable schmitt trigger
	 * pull down
	 * default drive strength 8
	 * pinmux set to gpio
	 */
	mango_pin_init(pin,
		       MANGO_PIN_CFG_DRIVE_BY_IP |
		       MANGO_PIN_CFG_PULL_ENABLE |
		       MANGO_PIN_CFG_DRIVING_SEL(8) |
		       MANGO_PIN_CFG_PINMUX_SEL(0));
}

/* warning: only apply to heartbeat pins */
static void mango_pin_init_gpi(int pin, int gpio)
{
	gpio_set_direction(gpio, GPIO_DIR_IN);
	/* drive by ip,
	 * enable schmitt trigger
	 * pull down
	 * default drive strength 8
	 * pinmux set to gpio
	 */
	mango_pin_init(pin,
		       MANGO_PIN_CFG_DRIVE_BY_IP |
		       MANGO_PIN_CFG_SCHMITT_TRIGGER_ENABLE |
		       MANGO_PIN_CFG_PULL_ENABLE |
		       MANGO_PIN_CFG_DRIVING_SEL(8) |
		       MANGO_PIN_CFG_PINMUX_SEL(0));
}

static void mango_set_dbgi2c_addr(int addr)
{
	mmio_write_32(MANGO_TOP_REG(DEBUG_I2C_ID), (1 << 7) | addr);
}

void mango_bl1_multi_socket_init(void)
{
	int socket_id;
	int pin;
	int i;

	socket_id = mango_get_socket_id();

	mango_set_dbgi2c_addr(MANGO_DBGI2C_ADDR_BASE + socket_id);

	for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
		pin = MANGO_PINMUX_GPIO0 + i;
		if (i == socket_id)
			mango_pin_init_gpo(pin, i);
		else
			mango_pin_init_gpi(pin, i);
	}

	gpio_set_value(socket_id, GPIO_LEVEL_HIGH);

	/* continue booting bl2 if we are in single spi mode */
	/* in multi spi mode, chips should init cmn, ccix and pcie by itself */
	if (mango_is_single_spi_mode() && socket_id)
		cli_loop(0);
}

/* bl2 setup */

/* count in us */
#define MANGO_SOCKET_CHECK_TIMEOUT	(1000)

static struct mango_topology topology;

static int build_if_present(struct mango_socket *socket,
			    int rc_socket, int rc_port,
			    int ep_socket, int ep_port,
			    int speed)
{
	if (!socket[rc_socket].present || !socket[ep_socket].present)
		return false;

	socket[rc_socket].link[rc_port].target = ep_socket;
	socket[rc_socket].link[rc_port].mode = PCIE_OP_MODE_RC;
	socket[rc_socket].link[rc_port].speed = speed;

	socket[ep_socket].link[ep_port].target = rc_socket;
	socket[ep_socket].link[ep_port].mode = PCIE_OP_MODE_EP;
	socket[ep_socket].link[ep_port].speed = speed;

	return true;
}

void mango_show_topology(struct mango_topology *tp)
{
	int i, j;
	struct mango_socket *socket = tp->socket;
	struct pcie_link *link;

	const char *pcie_speed_table[] = {
		[PCIE_LINK_SPEED_2G5] = "gen1 2.5GT/s",
		[PCIE_LINK_SPEED_5G] = "gen2 5GT/s",
		[PCIE_LINK_SPEED_8G] = "gen3 8GT/s",
		[PCIE_LINK_SPEED_16G] = "gen4 16GT/s",
	};

	printf("Socket id %d, online chip number %d\n",
	       tp->self, tp->online_chip_num);

	if (tp->online_chip_num == 1)
		return;

	for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
		if (socket[i].present) {
			printf("Socket%d is present\n", i);
		} else {
			printf("Socket%d is not present\n", i);
			continue;
		}

		for (j = 0; j < MANGO_PCIE_MAX; ++j) {
			link = &socket[i].link[j];
			printf("    ");
			if (link->target < 0)
				printf("Port%d no link\n", j);
			else
				printf("Port%d --> Socket%d %s %s\n",
				       j, link->target,
				       link->mode == PCIE_OP_MODE_RC ?
				       "RC" : "EP",
				       pcie_speed_table[link->speed]);
		}

		printf("RISC-V map:");
		for (j = 0; j < ARRAY_SIZE(socket[i].rv_map); ++j)
			printf(" %c", socket[i].rv_map[j] ? 'O' : 'X');
		printf("\n");
	}
}

/* TODO: valid risc-v cluster information should get from efuse */
static int valid_rv_map[MANGO_CLUSTER_MAX] = {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void mango_build_rv_map(struct mango_topology *tp)
{
	/* TODO: get valid risc-v cluster map from efuse */
	int i;
	struct mango_socket *socket;

	for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
		socket = &tp->socket[i];
		memcpy(socket->rv_map, valid_rv_map, sizeof(socket->rv_map));
	}
}

void mango_build_topology(struct mango_topology *tp)
{
	uint64_t expr;
	int i, j;
	int present;
	struct mango_socket *socket = tp->socket;

	/* init socket topology to single mode */
	tp->is_multi_socket = mango_is_multi_socket_mode();
	tp->is_single_spi = mango_is_single_spi_mode();
	tp->self = mango_get_socket_id();

	tp->online_chip_num = 1;
	tp->socket[tp->self].present = true;
	for (i = 0; i < MANGO_SOCKET_MAX; ++i)
		for (j = 0; j < MANGO_PCIE_MAX; ++j)
			socket[i].link[j].target = -1;

	mango_build_rv_map(tp);

	NOTICE("Chip%d working at %s socket, %s spi mode\n",
	       tp->self,
	       tp->is_multi_socket ? "multi" : "single",
	       tp->is_single_spi ? "single" : "multi");

	if (!tp->is_multi_socket)
		return;

	/* multi socket mode */

	present = 1;

	expr = timeout_init_us(MANGO_SOCKET_CHECK_TIMEOUT);

	do {
		for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
			if (!socket[i].present) {
				if (gpio_get_value(i) == GPIO_LEVEL_HIGH) {
					socket[i].present = true;
					++present;
				}
			}
		}

		/* we have found all chips */
		if (present == MANGO_SOCKET_MAX)
			break;

	} while (timeout_elapsed(expr));

	tp->online_chip_num = present;

	build_if_present(socket, 0, PCIE_ID_0, 1, PCIE_ID_1,
			 PCIE_LINK_SPEED_16G);
}

void mango_set_rv_vendor_id(uint64_t id)
{
	mmio_write_32(MANGO_TOP_REG(RP_CPU_VENDOR_ID_L), id & 0xffffffff);
	mmio_write_32(MANGO_TOP_REG(RP_CPU_VENDOR_ID_H), (id >> 32));
}

void mango_set_rv_apb_base(uint64_t base)
{
	mmio_write_32(MANGO_TOP_REG(RP_CPU_APB_BASE_L), base & 0xffffffff);
	mmio_write_32(MANGO_TOP_REG(RP_CPU_APB_BASE_H), (base >> 32));
}

void mango_set_rv_reset_addr(int sid, uint64_t addr)
{
	mmio_write_32(MANGO_TOP_REG_UA(sid, RP_CPU_RVBA_L), addr & 0xffffffff);
	mmio_write_32(MANGO_TOP_REG_UA(sid, RP_CPU_RVBA_H), (addr >> 32));
}

void mango_set_rv_cluster_id(int cluster, uint32_t id)
{
	uintptr_t base = MANGO_TOP_REG(MP0_STATUS_REG) + cluster * 8;

	mmio_write_32(base, id);
}

void mango_set_rv_cluster_en(int cluster, int en)
{
	uintptr_t base = MANGO_TOP_REG(MP0_CONTROL_REG) + cluster * 8;
	uint32_t tmp;
	uint32_t mask;

	mmio_write_32(base, !!en);

	base = MANGO_TOP_REG(MISC_CTRL);
	tmp = mmio_read_32(base);
	mask = 1 << (cluster + 16);
	if (en)
		tmp &= ~mask;
	else
		tmp |= mask;
	mmio_write_32(base, tmp);
}

/* let risc-v cores issue secure transaction */
void mango_set_rv_sec_acc(int sec)
{
	mmio_write_32(MANGO_TOP_REG(RP_CPU_SEC_ACC), !!sec);
}

void mango_set_rp_sys_en(int sid, int en)
{
	uintptr_t reg = PLAT_CHIP_ADDR_BASE(sid) + MANGO_SOFT_RESET_BASE;
	const uint32_t rp_sys_mask = 1 << 1;

	if (en)
		mmio_setbits_32(reg, rp_sys_mask);
	else
		mmio_clrbits_32(reg, rp_sys_mask);
}

/* TODO: now we use thead manufacture id, because thead ice should use it.
 * change it if we allocate a manufactures id from jedec
 */
static const uint8_t MANGO_JEDEC_MANUFACTURES_ID[] = {
	0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f,
	0x7f, 0x7f, 0x7f, 0x37,
};

struct mango_rvfw_desc {
	uint32_t tag;
	uint32_t crc16;
	uint32_t offset;
	uint32_t size;
	uint64_t base;
};

int load_rvfw(unsigned long mango_rvfw_desc_addr, struct mango_rvfw_desc *desc)
{
	memcpy(desc, (void *)mango_rvfw_desc_addr,
	       sizeof(struct mango_rvfw_desc));

	if (desc->tag != MANGO_RVFW_TAG) {
		ERROR("Wrong risc-v firmware tag\n");
		return -EINVAL;
	}

	/* load from lma to vma */
	memcpy((void *)desc->base,
	       (void *)(mango_rvfw_desc_addr + desc->offset), desc->size);

	if (desc->crc16 != crc16_ccitt(0, (void *)desc->base, desc->size)) {
		ERROR("Bad crc\n");
		return -EINVAL;

	}

	return 0;
}

void mango_load_rvfw(void)
{
	int err, i;
	struct mango_rvfw_desc desc;
	struct mango_topology *tp;
	uint64_t reset_vector;

	NOTICE("Loading risc-v firmware\n");

	err = load_rvfw(MANGO_FLASH0_BASE + MANGO_RVFW_OFFSET, &desc);
	if (err) {
		ERROR("Load main risc-v firmware failed, try backup\n");
		err = load_rvfw(MANGO_FLASH0_BASE + MANGO_RVFW_OFFSET +
				MANGO_RVFW_SIZE, &desc);
		if (err) {
			ERROR("Load backup risc-v firmware failed\n");
			ERROR("Fallback to bootrom\n");
#ifdef MANGO_FORCE_ENABLE_RISCV
			NOTICE("Continue booting rp on palladium\n");
#else
			return;
#endif
		}
	}

	reset_vector = err ? RV_BOOTROM_BASE : desc.base;
	tp = mango_get_topology();

	for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
		if (tp->socket[i].present) {
			mango_set_rv_reset_addr(i, reset_vector);
			mango_set_rp_sys_en(i, true);
		}
	}
}

void mango_setup_rpsys(void)
{
	int i, socket_id, id;
	uint32_t vendor_id;

	/* socket id is 0, always means local chip */
	mango_set_rp_sys_en(0, false);

	/* config risc-v vendor id */
	for (i = 0; MANGO_JEDEC_MANUFACTURES_ID[i] == 0x7f; ++i)
		;

	vendor_id = (i << 7) | (MANGO_JEDEC_MANUFACTURES_ID[i] & ~0x80);

	mango_set_rv_vendor_id(vendor_id);
	mango_set_rv_sec_acc(true);

	/* enable all rv
	 * TODO: we should check valid risc-v maps to determin which set of
	 * risc-v can be bring up
	 */
	socket_id = mango_get_socket_id();
	for (i = 0; i < MANGO_CLUSTER_MAX; ++i) {
		id = socket_id * MANGO_CLUSTER_MAX + i;
		mango_set_rv_cluster_id(i, id);
		mango_set_rv_cluster_en(i, valid_rv_map[i]);
	}
}

unsigned long __attribute__((weak)) mango_get_ddr_channel_size(int channel)
{
	return GB(4);
}

static inline uint32_t mango_top_ddr_size_val(unsigned long size)
{
	int i;

	for (i = MANGO_DDR_PA_MAX_BITS; i >= 0; --i)
		if (size & (1UL << i))
			break;

	return MANGO_DDR_PA_MAX_BITS - i;
}

void mango_build_ddr_map(struct mango_topology *tp)
{
	int i;
	uint32_t top_ddr_size_cfg = 0;

	/* TODO: get dimm size connected with each ddr channel */

	for (i = 0; i < MANGO_DDRCTL_MAX; ++i) {
		tp->ddrctl[i].mem = MANGO_DDR0_BASE + i * MANGO_DDR0_SIZE;
		tp->ddrctl[i].size = mango_get_ddr_channel_size(i);

		top_ddr_size_cfg |=
			mango_top_ddr_size_val(tp->ddrctl[i].size) <<
			(MANGO_TOP_DDR_SIZE_SHIFT * i);
	}

	mmio_write_32(MANGO_TOP_REG(DDR_SIZE), top_ddr_size_cfg);
}

/* get global mango topology */
struct mango_topology *mango_get_topology(void)
{
	return &topology;
}

/* init i2c driver for accessing spd */
static struct i2c_info i2c_info[] = {
	{ I2C0_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C1_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C2_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C3_BASE, 100 * 1000 * 1000, 100 * 1000 },
};

void mango_init_misc_ctrl(void)
{
	uint32_t tmp;

	/* disable all HAD entry */
	tmp = 0xffffU << 16;
#ifdef MANGO_A53_SLC_OFF
	/* a53 to cmn transaction always non-cacheable */
	tmp |= 1 << 4;
#endif
	mmio_write_32(MANGO_TOP_REG(MISC_CTRL), tmp);
}

struct part_info {
	/* disk partition table magic number */
	uint32_t magic;
	char name[32];
	uint32_t offset;
	uint32_t size;
	char reserve[4];
	/* load memory address*/
	uint64_t lma;
};

static int mango_get_part_info(uint32_t addr, struct part_info *info)
{
	int ret;

	ret = plat_spif_read((uint64_t)info, addr, sizeof(struct part_info));
	if (ret)
		return ret;

	if (info->magic != DPT_MAGIC) {
		ERROR("bad partition magic\n");
		return -EINVAL;
	}

	return ret;
}

static int mango_get_part_info_by_name(uint32_t addr, const char *name,
				       struct part_info *info)
{
	int ret;

	do {
		ret = mango_get_part_info(addr, info);

		addr += sizeof(struct part_info);

	} while (!ret && memcmp(info->name, name, strlen(name)));

	return ret;
}

static int mango_load_from_sf(uint64_t lma, uint32_t start, int size)
{
	return plat_spif_read(lma, start, size);
}

static int mango_load_image_sf(uint32_t addr, const char *name,
			       struct part_info *info)
{
	int ret;

	ret = mango_get_part_info_by_name(addr, name, info);
	if (ret) {
		ERROR("failed to get %s partition info\n", name);
		return ret;
	}

	NOTICE("load %s image from sf 0x%x to memory 0x%lx size %d\n", name,
	       info->offset, info->lma, info->size);

	ret = mango_load_from_sf(info->lma, info->offset, info->size);
	if (ret) {
		ERROR("failed to load %s image form spi flash\n", name);
		return ret;
	}

	return 0;
}

static int mango_load_image_sd(const char *name)
{
	static FATFS SDC_FS;
	FIL fp;
	size_t length;
	UINT br;
	FRESULT f_ret;
	int result = -ENOENT;

	f_ret = f_mount(&SDC_FS, "0:", 1);
	if (f_ret != FR_OK)
		return CONV_FR(f_ret);

	f_ret = f_open(&fp, "0:zsbl.bin", FA_READ);
	result = CONV_FR(f_ret);
	if (result) {
		NOTICE("failed to open %s\n", name);
		f_unmount("0:");
		return result;
	}

	length = f_size(&fp);
	f_ret = f_read(&fp, (void *)ZSBL_BASE, length, &br);
	result = CONV_FR(f_ret);
	if (result || length != br)
		NOTICE("failed to read %s\n", name);

	f_close(&fp);
	f_unmount("0:");

	flush_dcache_range(ZSBL_BASE, length);

	return result;
}

static int mango_load_zsbl(void)
{
	int i, ret;
	struct part_info info;
	struct mango_topology *tp;
	int fip_src;

	fip_src = mmio_read_32(FIP_SOURCE_REG);
	if (fip_src == FIP_SRC_SDFT)
		ret = mango_load_image_sd(ZSBL_IMAGE_NAME);
	else
		ret = mango_load_image_sf(DISK_PART_TABLE_ADDR, ZSBL_IMAGE_NAME, &info);
	if (ret) {
		ERROR("failed to load %s image %d\n", ZSBL_IMAGE_NAME, ret);
#ifdef MANGO_FORCE_ENABLE_RISCV
		NOTICE("Continue booting rp on palladium\n");
#else
		return;
#endif
	}

	tp = mango_get_topology();

	for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
		if (tp->socket[i].present) {
			if (fip_src == FIP_SRC_SDFT)
				mango_set_rv_reset_addr(i, ZSBL_BASE);
			else
				mango_set_rv_reset_addr(i, info.lma);
			mango_set_rp_sys_en(i, true);
		}
	}

	return 0;
}

void mango_bl2_multi_socket_init(void)
{
	int i;

	mango_init_misc_ctrl();

	i2c_init(i2c_info, ARRAY_SIZE(i2c_info));

	mango_build_ddr_map(&topology);

	mango_build_topology(&topology);

	mango_show_topology(&topology);

	mango_setup_icn(&topology);

	mango_setup_rpsys();

	if (topology.self) {
		NOTICE("Chip%d enter sleep mode\n", topology.self);
		cli_loop(0);
	}

	/* now, only socket0 core0 works */
	if (!mango_is_a53_master_mode()) {
		mango_load_zsbl();
		NOTICE("RISC-V only mode\n");
		cli_loop(0);

		NOTICE("Disable RISC-V subsystem\n");
		for (i = 0; i < MANGO_SOCKET_MAX; ++i) {
			if (topology.socket[i].present)
				mango_set_rp_sys_en(i, false);
		}
		NOTICE("Continue booting\n");
	} else
		NOTICE("A53 master mode\n");
}

