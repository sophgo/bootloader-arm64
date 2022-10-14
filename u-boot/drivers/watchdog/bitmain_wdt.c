#include <common.h>
#include <wdt.h>
#include <dm.h>
#include <i2c.h>

/* magic number for different type of watchdogs, no need now */
/* this byte is used to handle some different software implementations of wdt */
#define WDT_MAGIC_REG	(0)
/* write 1 to this register will enable watchdog */
#define WDT_ENABLE_REG	(1)
/* write to this register will result in reloading timeout to counter */
#define WDT_RELOAD_REG	(2)
/* offset 3 is reserved */
/* write to this register */
#define WDT_TIMEOUT_REG	(4)
#define WDT_COUNTER_REG	(8)

#define WDT_ENABLE	(1)
#define WDT_DISABLE	(0)
#define WDT_RELOAD	(1)

static int wdt_set_counter(struct udevice *i2c, u32 counter)
{
	u8 byte[5];
	int err;
	struct dm_i2c_chip *chip = dev_get_parent_plat(i2c);
	struct i2c_msg msg;

	byte[0] = WDT_TIMEOUT_REG;
	byte[1] = counter & 0xff;
	byte[2] = (counter >> 8) & 0xff;
	byte[3] = (counter >> 16) & 0xff;
	byte[4] = (counter >> 24) & 0xff;

	msg.addr = chip->chip_addr;
	msg.buf = byte;
	msg.len = sizeof(byte);
	msg.flags = 0;

	err = dm_i2c_xfer(i2c, &msg, 1);
	if (err)
		return err;

	return dm_i2c_reg_write(i2c, WDT_RELOAD_REG, WDT_RELOAD);
}

static int bm_wdt_start(struct udevice *i2c, u64 timeout, ulong flags)
{
	int err;

	err = wdt_set_counter(i2c, DIV_ROUND_UP(timeout, 1000));
	if (err)
		return err;

	return dm_i2c_reg_write(i2c, WDT_ENABLE_REG, WDT_ENABLE);
}

static int bm_wdt_stop(struct udevice *i2c)
{
	return dm_i2c_reg_write(i2c, WDT_ENABLE_REG, WDT_DISABLE);
}

static int bm_wdt_ping(struct udevice *i2c)
{
	return dm_i2c_reg_write(i2c, WDT_RELOAD_REG, WDT_RELOAD);
}

static int bm_wdt_expr(struct udevice *i2c, ulong flags)
{
	return bm_wdt_start(i2c, 0, flags);
}

static int bm_wdt_probe(struct udevice *i2c)
{
	int err;

	i2c_set_chip_flags(i2c, DM_I2C_CHIP_RD_ADDRESS |
			   DM_I2C_CHIP_WR_ADDRESS);

	/* reset watchdog to given status */
	err = bm_wdt_stop(i2c);
	if (err)
		return err;

	return wdt_set_counter(i2c, 0xffffffff);
}

static const struct udevice_id bm_wdt_ids[] = {
	{ .compatible = "bitmain,bm16xx-wdt" },
	{},
};

static const struct wdt_ops bm_wdt_ops = {
	.start = bm_wdt_start,
	.reset = bm_wdt_ping,
	.stop = bm_wdt_stop,
	.expire_now = bm_wdt_expr,
};

U_BOOT_DRIVER(wdt) = {
	.name	= "bitmain-watchdog",
	.id	= UCLASS_WDT,
	.probe	= bm_wdt_probe,
	.of_match = bm_wdt_ids,
	.ops	= &bm_wdt_ops,
};

#if defined(CONFIG_HW_WATCHDOG)

#error "hardware watchdog will slow down your system"

void hw_watchdog_enable(void)
{
	struct udevice *wdt;

	if (uclass_get_device_by_name(UCLASS_WDT, "bm16xxwdt", &wdt))
		return;

	wdt_start(wdt, CONFIG_WATCHDOG_TIMEOUT_MSECS, 0);
}

void hw_watchdog_disable(void)
{
	struct udevice *wdt;

	if (uclass_get_device_by_name(UCLASS_WDT, "bm16xxwdt", &wdt))
		return;

	wdt_stop(wdt);
}

void hw_watchdog_reset(void)
{
	struct udevice *wdt;

	if (uclass_get_device_by_name(UCLASS_WDT, "bm16xxwdt", &wdt))
		return;

	wdt_reset(wdt);
}

void hw_watchdog_init(void)
{
	struct udevice *wdt;
	int err;

	err = uclass_get_device_by_name(UCLASS_WDT, "bm16xxwdt", &wdt);
	if (err)
		return;

	if (wdt_start(wdt, CONFIG_WATCHDOG_TIMEOUT_MSECS, 0))
		return;
}

#endif
