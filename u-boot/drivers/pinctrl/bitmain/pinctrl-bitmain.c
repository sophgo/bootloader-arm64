#include <common.h>
#include <dm.h>
#include <errno.h>
#include <asm/io.h>
#include "pinctrl-bitmain.h"

DECLARE_GLOBAL_DATA_PTR;

/* given a pin-name, return the address of pin config registers */
static unsigned long pin_to_reg_addr(struct udevice *dev, const char *pin_name, unsigned int *offset)
{
	struct bitmain_pinctrl_priv *priv = dev_get_priv(dev);
	const struct bitmain_pin_data *pin_data = priv->pin_list;
	u32 idx = 0;
	*offset = 0;

	/* lookup the pin bank data using the pin bank name */
	for (idx = 0; ; idx++) {
		if (!pin_data[idx].name)
			return 0;
		if (strcmp(pin_name, pin_data[idx].name) == 0) {
			*offset = pin_data[idx].offset;
			return priv->base + pin_data[idx].reg;
		}
	}

	return 0;
}

/**
 * bitmain_pinctrl_set_state: configure a pin state.
 * dev: the pinctrl device to be configured.
 * config: the state to be configured.
 */
int bitmain_pinctrl_set_state(struct udevice *dev, struct udevice *config)
{
	const void *fdt = gd->fdt_blob;
	int node = dev_of_offset(config);
	unsigned int count, idx, pin_offset;
	unsigned int pinmux, pindrv;
	unsigned long reg, value;
	const char *name;

	count = fdt_stringlist_count(fdt, node, "bitmain,pins");
	if (count <= 0)
		return -EINVAL;

	pinmux = fdtdec_get_int(fdt, node, "bitmain,pin-mux", -1);
	pindrv = fdtdec_get_int(fdt, node, "bitmain,pin-drv", -1);

	for (idx = 0; idx < count; idx++) {
		name = fdt_stringlist_get(fdt, node, "bitmain,pins", idx, NULL);
		if (!name)
			continue;
		reg = pin_to_reg_addr(dev, name, &pin_offset);
		if (reg == 0) {
			printf("pinctrl: error unknown pin %s\n", name);
			continue;
		}
		if (pinmux != -1) {
			value = readl(reg);
			value &= ~(MUX_MASK << (MUX_OFFSET + pin_offset * 16));
			value |= ((pinmux & MUX_MASK) << (MUX_OFFSET + pin_offset * 16));
			writel(value, reg);
		}

		if (pindrv != -1) {
			value = readl(reg);
			value &= ~(DRV_MASK << (DRV_OFFSET + pin_offset * 16));
			value |= ((pindrv & DRV_MASK) << (DRV_OFFSET + pin_offset * 16));
			writel(value, reg);
		}
	}

	return 0;
}

int bitmain_pinctrl_probe(struct udevice *dev)
{
	struct bitmain_pinctrl_priv *priv;
	fdt_addr_t base;

	priv = dev_get_priv(dev);
	if (!priv)
		return -EINVAL;

	base = devfdt_get_addr(dev);
	if (base == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->base = base;
	priv->pin_list = (struct bitmain_pin_data *)dev_get_driver_data(dev);

	return 0;
}
