#include <common.h>
#include <dm.h>
#include <errno.h>
#include <asm/io.h>
#include <dm/pinctrl.h>
#include <dm/root.h>
#include <fdtdec.h>
#include "pinctrl-bitmain.h"

DECLARE_GLOBAL_DATA_PTR;

static struct pinctrl_ops bm1684_pinctrl_ops = {
	.set_state	= bitmain_pinctrl_set_state,
};

static const struct bitmain_pin_data bm1684_pin_list[] = {
	BITMAIN_PIN_DATA("GPIO76",		0x6C,	0), /* PWM1 */
	BITMAIN_PIN_DATA("GPIO29",		0xC4,	0), /* DBG_I2C_SCL */
	BITMAIN_PIN_DATA("GPIO30",		0xC4,	1), /* DBG_I2C_SDA */
	BITMAIN_PIN_DATA("GPIO31",		0xC8,	0), /* DBG_I2C_OEs */
	BITMAIN_PIN_DATA("IIC2_SDA",		0x78,	1), /* I2C2_SDA */
	BITMAIN_PIN_DATA("IIC2_SCL",		0x7C,	0), /* I2C2_SCL */

	BITMAIN_PIN_DATA(NULL,			0,	0),
};

static const struct udevice_id bm1684_pinctrl_ids[] = {
	{ .compatible = "bitmain,bm1684-pinctrl",
		.data = (ulong)bm1684_pin_list },
	{ }
};

U_BOOT_DRIVER(pinctrl_bm1684) = {
	.name		= "pinctrl_bm1684",
	.id		= UCLASS_PINCTRL,
	.of_match	= bm1684_pinctrl_ids,
	.priv_auto = sizeof(struct bitmain_pinctrl_priv),
	.ops		= &bm1684_pinctrl_ops,
	.probe		= bitmain_pinctrl_probe,
	.flags		= DM_FLAG_PRE_RELOC
};
