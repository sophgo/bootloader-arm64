#include <common.h>
#include <dm.h>
#include <errno.h>
#include <asm/io.h>
#include <dm/pinctrl.h>
#include <dm/root.h>
#include <fdtdec.h>
#include "pinctrl-bitmain.h"

DECLARE_GLOBAL_DATA_PTR;

static struct pinctrl_ops mango_pinctrl_ops = {
	.set_state	= bitmain_pinctrl_set_state,
};

static const struct bitmain_pin_data mango_pin_list[] = {
	BITMAIN_PIN_DATA(NULL,			0,	0),
};

static const struct udevice_id mango_pinctrl_ids[] = {
	{ .compatible = "sophgo,mango-pinctrl",
		.data = (ulong)mango_pin_list },
	{ }
};

U_BOOT_DRIVER(pinctrl_mango) = {
	.name		= "pinctrl_mango",
	.id		= UCLASS_PINCTRL,
	.of_match	= mango_pinctrl_ids,
	.priv_auto = sizeof(struct bitmain_pinctrl_priv),
	.ops		= &mango_pinctrl_ops,
	.probe		= bitmain_pinctrl_probe,
	.flags		= DM_FLAG_PRE_RELOC
};
