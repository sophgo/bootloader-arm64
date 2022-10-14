// #define CLI

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <mmio.h>
#include <delay_timer.h>
#include <arch_helpers.h>
#include <errno.h>
#include <utils_def.h>
#include <i2c.h>

#define CMD_BUF_MAX 512

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef u8 uchar;
typedef unsigned long ulong;

#include "i2c.h"
#include "dw_i2c.h"

static inline void writel(u32 val, void *io)
{
	mmio_write_32((uintptr_t)io, val);
}

static inline u32 readl(void *io)
{
	return mmio_read_32((uintptr_t)io);
}

static inline ulong raw_timer_us(void)
{
	return read_cntpct_el0() * 1000 * 1000 / read_cntfrq_el0();
}

static inline ulong get_timer_us(ulong base)
{
	return raw_timer_us() - base;
}

/* using u-boot style get_timer instead of atf style */
#define get_timer get_timer_us

#if 0
#define printf ERROR
#define debug VERBOSE
#else
#define debug printf
#endif

/* end of u-boot porting */

struct dw_scl_sda_cfg {
	u32 ss_hcnt;
	u32 fs_hcnt;
	u32 ss_lcnt;
	u32 fs_lcnt;
	u32 sda_hold;
};

struct dw_i2c {
	unsigned int i2c_clk_frq;
	struct i2c_regs *regs;
	struct dw_scl_sda_cfg *scl_sda_cfg;
};

static void dw_i2c_enable(struct i2c_regs *i2c_base, bool enable)
{
	u32 ena = enable ? IC_ENABLE_0B : 0;
	int timeout = 100;

	do {
		writel(ena, &i2c_base->ic_enable);
		if ((readl(&i2c_base->ic_enable_status) & IC_ENABLE_0B) == ena)
			return;

		/*
		 * Wait 10 times the signaling period of the highest I2C
		 * transfer supported by the driver (for 400KHz this is
		 * 25us) as described in the DesignWare I2C databook.
		 */
		udelay(25);
	} while (timeout--);

	printf("timeout in %sabling I2C adapter\n", enable ? "en" : "dis");
}

/*
 * i2c_set_bus_speed - Set the i2c speed
 * @speed:	required i2c speed
 *
 * Set the i2c speed.
 */
static unsigned int __dw_i2c_set_bus_speed(struct dw_i2c *i2c,
					   unsigned int speed)
{
	int i2c_spd;
	unsigned int clk_freq;
	unsigned int cntl;
	unsigned int hcnt, lcnt;
	struct i2c_regs *i2c_base = i2c->regs;
	struct dw_scl_sda_cfg *scl_sda_cfg = i2c->scl_sda_cfg;

	clk_freq = i2c->i2c_clk_frq ? (i2c->i2c_clk_frq / 1000000) : IC_CLK;

	if (speed >= I2C_MAX_SPEED)
		i2c_spd = IC_SPEED_MODE_MAX;
	else if (speed >= I2C_FAST_SPEED)
		i2c_spd = IC_SPEED_MODE_FAST;
	else
		i2c_spd = IC_SPEED_MODE_STANDARD;

	/* to set speed cltr must be disabled */
	dw_i2c_enable(i2c_base, false);

	cntl = (readl(&i2c_base->ic_con) & (~IC_CON_SPD_MSK));

	switch (i2c_spd) {
	case IC_SPEED_MODE_MAX:
		cntl |= IC_CON_SPD_SS | IC_CON_RE;
		if (scl_sda_cfg) {
			hcnt = scl_sda_cfg->fs_hcnt;
			lcnt = scl_sda_cfg->fs_lcnt;
		} else {
			hcnt = (clk_freq * MIN_HS_SCL_HIGHTIME) / NANO_TO_MICRO;
			lcnt = (clk_freq * MIN_HS_SCL_LOWTIME) / NANO_TO_MICRO;
		}
		writel(hcnt, &i2c_base->ic_hs_scl_hcnt);
		writel(lcnt, &i2c_base->ic_hs_scl_lcnt);
		break;

	case IC_SPEED_MODE_STANDARD:
		cntl |= IC_CON_SPD_SS;
		if (scl_sda_cfg) {
			hcnt = scl_sda_cfg->ss_hcnt;
			lcnt = scl_sda_cfg->ss_lcnt;
		} else {
			hcnt = (clk_freq * MIN_SS_SCL_HIGHTIME) / NANO_TO_MICRO;
			lcnt = (clk_freq * MIN_SS_SCL_LOWTIME) / NANO_TO_MICRO;
		}
		writel(hcnt, &i2c_base->ic_ss_scl_hcnt);
		writel(lcnt, &i2c_base->ic_ss_scl_lcnt);
		break;

	case IC_SPEED_MODE_FAST:
	default:
		cntl |= IC_CON_SPD_FS;
		if (scl_sda_cfg) {
			hcnt = scl_sda_cfg->fs_hcnt;
			lcnt = scl_sda_cfg->fs_lcnt;
		} else {
			hcnt = (clk_freq * MIN_FS_SCL_HIGHTIME) / NANO_TO_MICRO;
			lcnt = (clk_freq * MIN_FS_SCL_LOWTIME) / NANO_TO_MICRO;
		}
		writel(hcnt, &i2c_base->ic_fs_scl_hcnt);
		writel(lcnt, &i2c_base->ic_fs_scl_lcnt);
		break;
	}

	/* always working in master mode and enable restart */
	writel(cntl | IC_CON_RE | IC_CON_MM, &i2c_base->ic_con);

	/* Configure SDA Hold Time if required */
	if (scl_sda_cfg)
		writel(scl_sda_cfg->sda_hold, &i2c_base->ic_sda_hold);

	/* Enable back i2c now speed set */
	dw_i2c_enable(i2c_base, true);

	return 0;
}

/*
 * i2c_setaddress - Sets the target slave address
 * @i2c_addr:	target i2c address
 *
 * Sets the target slave address.
 */
static void i2c_setaddress(struct i2c_regs *i2c_base, unsigned int i2c_addr)
{
	/* Disable i2c */
	dw_i2c_enable(i2c_base, false);

	writel(i2c_addr, &i2c_base->ic_tar);

	/* Enable i2c */
	dw_i2c_enable(i2c_base, true);
}

/*
 * i2c_flush_rxfifo - Flushes the i2c RX FIFO
 *
 * Flushes the i2c RX FIFO
 */
static void i2c_flush_rxfifo(struct i2c_regs *i2c_base)
{
	while (readl(&i2c_base->ic_status) & IC_STATUS_RFNE)
		readl(&i2c_base->ic_cmd_data);
}

/*
 * i2c_wait_for_bb - Waits for bus busy
 *
 * Waits for bus busy
 */
static int i2c_wait_for_bb(struct i2c_regs *i2c_base)
{
	unsigned long start_time_bb = get_timer(0);

	while ((readl(&i2c_base->ic_status) & IC_STATUS_MA) ||
	       !(readl(&i2c_base->ic_status) & IC_STATUS_TFE)) {

		/* Evaluate timeout */
		if (get_timer(start_time_bb) > (unsigned long)(I2C_BYTE_TO_BB))
			return 1;
	}

	return 0;
}

static int i2c_xfer_init(struct i2c_regs *i2c_base, uchar chip, uint addr,
			 int alen)
{
	if (i2c_wait_for_bb(i2c_base))
		return 1;

	i2c_setaddress(i2c_base, chip);
	while (alen) {
		alen--;
		/* high byte address going out first */
		writel((addr >> (alen * 8)) & 0xff,
		       &i2c_base->ic_cmd_data);
	}
	return 0;
}

static int i2c_xfer_finish(struct i2c_regs *i2c_base)
{
	ulong start_stop_det;

	/* send stop bit */
	writel(1 << 9, &i2c_base->ic_cmd_data);

	start_stop_det = get_timer(0);

	while (1) {
		if ((readl(&i2c_base->ic_raw_intr_stat) & IC_STOP_DET)) {
			readl(&i2c_base->ic_clr_stop_det);
			break;
		} else if (get_timer(start_stop_det) > I2C_STOPDET_TO) {
			break;
		}
	}

	if (i2c_wait_for_bb(i2c_base)) {
		printf("Timed out waiting for bus\n");
		return 1;
	}

	i2c_flush_rxfifo(i2c_base);

	return 0;
}

/*
 * __dw_i2c_init - Init function
 * @speed:	required i2c speed
 * @slaveaddr:	slave address for the device
 *
 * Initialization function.
 */
static void __dw_i2c_init(struct dw_i2c *i2c, int speed, int slaveaddr)
{
	struct i2c_regs *i2c_base = i2c->regs;
	/* Disable i2c */
	dw_i2c_enable(i2c_base, false);

	writel((IC_CON_SD | IC_CON_SPD_FS | IC_CON_MM), &i2c_base->ic_con);
	writel(IC_RX_TL, &i2c_base->ic_rx_tl);
	writel(IC_TX_TL, &i2c_base->ic_tx_tl);
	writel(IC_STOP_DET, &i2c_base->ic_intr_mask);
	__dw_i2c_set_bus_speed(i2c, speed);
	writel(slaveaddr, &i2c_base->ic_sar);
	/* Enable i2c */
	dw_i2c_enable(i2c_base, true);
}

static int designware_i2c_xfer(struct dw_i2c *i2c, struct i2c_msg *msg,
			       int nmsgs)
{
	uint16_t cmd_buf[CMD_BUF_MAX];
	uint8_t data_buf[CMD_BUF_MAX];
	int i, j, k, l, err;
	uint32_t status;
	struct i2c_regs *regs;

	if (nmsgs <= 0)
		return 0;

	if (i2c_xfer_init(i2c->regs, msg[0].addr, 0, 0))
		return -EIO;

	regs = i2c->regs;

	/* stream messages */
	k = 0, l = 0;
	for (i = 0; i < nmsgs; ++i) {
		for (j = 0; j < msg[i].len; ++j) {
			if (msg[i].flags & I2C_M_RD) {
				cmd_buf[k] = IC_CMD;
				++l;
			} else {
				cmd_buf[k] = msg[i].buf[j];
			}
			++k;
			if (k > CMD_BUF_MAX) {
				printf("too many commands\n");
				return -ENOMEM;
			}
		}
	}

	j = 0;
	for (i = 0; i < k || j < l;) {

		/* check tx abort */
		if (readl(&regs->ic_raw_intr_stat) & IC_TX_ABRT) {
			err = (readl(&regs->ic_tx_abrt_source) &
			       IC_ABRT_7B_ADDR_NOACK) ?
				-ENODEV : -EIO;

			/* clear abort source */
			readl(&regs->ic_clr_tx_abrt);
			goto finish;
		}

		status = readl(&regs->ic_status);
		/* transmit fifo not full, push one command if we have not sent
		 * all commands out
		 */
		if ((status & IC_STATUS_TFNF) && (i < k)) {
			writel(cmd_buf[i], &regs->ic_cmd_data);
			++i;
		}

		/* receive data if receive fifo not empty and if we have not
		 * receive enough data
		 */
		if ((status & IC_STATUS_RFNE) && (j < l)) {
			data_buf[j] = readl(&regs->ic_cmd_data);
			++j;
		}
	}

	k = 0;
	for (i = 0; i < nmsgs; ++i) {
		if ((msg[i].flags & I2C_M_RD) == 0)
			continue;

		for (j = 0; j < msg[i].len; ++j) {
			msg[i].buf[j] = data_buf[k];
			++k;
			if (k > l) {
				printf("software logic error\n");
				err = -EFAULT;
				goto finish;
			}
		}
	}

	err = 0;

finish:
	i2c_xfer_finish(regs);

	return err;
}

static int designware_i2c_init(struct dw_i2c *i2c, void *reg,
			       unsigned long freq, unsigned long speed)
{
	i2c->regs = reg;
	i2c->i2c_clk_frq = freq;

	__dw_i2c_init(i2c, speed, 0);

	return 0;
}

static struct i2c_info *i2c_info;

int i2c_init(struct i2c_info *info, int n)
{
	int i, err;

	i2c_info = info;

	for (i = 0; i < n; ++i) {
		err = designware_i2c_init((void *)&i2c_info[i].dev,
					  (void *)i2c_info[i].base,
					  i2c_info[i].freq,
					  i2c_info[i].speed);
		if (err)
			return err;
	}

	return 0;
}

int i2c_xfer(int i2c, struct i2c_msg *msg, int nmsgs)
{
	return designware_i2c_xfer((void *)&i2c_info[i2c].dev, msg, nmsgs);
}

int i2c_smbus_read_byte(int i2c, unsigned char addr,
			unsigned char cmd, unsigned char *data)
{
	struct i2c_msg msg[2];

	memset(msg, 0, sizeof(msg));

	msg[0].addr = addr;
	msg[0].flags = 0; /* 7bit address */
	msg[0].len = 1;
	msg[0].buf = &cmd;

	msg[1].addr = addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = 1;
	msg[1].buf = data;

	return i2c_xfer(i2c, msg, 2);
}

int i2c_smbus_read(int i2c, unsigned char addr, unsigned int len,
		   unsigned char cmd, unsigned char *data)
{
	struct i2c_msg msg[2];

	memset(msg, 0, sizeof(msg));

	msg[0].addr = addr;
	msg[0].flags = 0; /* 7bit address */
	msg[0].len = 1;
	msg[0].buf = &cmd;

	msg[1].addr = addr;
	msg[1].flags = I2C_M_RD;
	msg[1].len = len;
	msg[1].buf = data;

	return i2c_xfer(i2c, msg, 2);
}

int i2c_smbus_write_byte(int i2c, unsigned char addr,
			 unsigned char cmd, unsigned char data)
{
	struct i2c_msg msg;
	u8 buf[2];

	memset(&msg, 0, sizeof(msg));

	buf[0] = cmd;
	buf[1] = data;

	msg.addr = addr;
	msg.flags = 0; /* 7bit address */
	msg.len = 2;
	msg.buf = buf;

	return i2c_xfer(i2c, &msg, 1);
}

