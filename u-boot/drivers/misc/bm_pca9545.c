#include <common.h>
#include <command.h>
#include <dm.h>
#include <i2c.h>
#include <misc.h>
#include <dm/device_compat.h>

#define SELECT_MUX_CH0 0xf1

static int pca9545_reg_write(struct udevice *i2c, u8 val)
{
	struct i2c_msg msg;
	u8 offset[2];
	struct dm_i2c_chip *chip = dev_get_parent_plat(i2c);

	memset(&msg, 0, sizeof(msg));
	memset(offset, 0, sizeof(offset));
	offset[0] = val;

	/* 16bits offset, big endian */
	msg.addr = chip->chip_addr;
	msg.buf = offset;
	msg.len = 1;
	msg.flags = 0;

	return dm_i2c_xfer(i2c, &msg, 1);
}

int pca9545_i2c_write(struct udevice *i2c, u8 data)
{
	dev_dbg(i2c, "%s mux select ch0\n", __func__);
	return pca9545_reg_write(i2c, data);
}

static int pca9545_i2c_probe(struct udevice *i2c)
{
	i2c_set_chip_flags(i2c, DM_I2C_CHIP_RD_ADDRESS |
	 DM_I2C_CHIP_WR_ADDRESS);

	return pca9545_i2c_write(i2c, SELECT_MUX_CH0);
}

static const struct udevice_id pca9545_i2c_dt_table[] = {
	{ .compatible = "sophgo,bm-pca9545" },
	{},
};

U_BOOT_DRIVER(pca9545) = {
	.name	= "bm-pca9545",
	.id	= UCLASS_MISC,
	.probe	= pca9545_i2c_probe,
	.of_match = pca9545_i2c_dt_table,
};

