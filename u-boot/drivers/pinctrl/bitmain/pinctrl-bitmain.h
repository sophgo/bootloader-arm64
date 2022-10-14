#ifndef __PINCTRL_BITMAIN_H_
#define __PINCTRL_BITMAIN__H_

#define MUX_OFFSET 4
#define MUX_MASK 0x3
#define DRV_OFFSET 6
#define DRV_MASK 0xF

struct bitmain_pin_data {
	const char *name;
	const unsigned int reg;
	const unsigned int offset; /* 0 for lower 16bits, 1 for higher 16bits */
};

#define BITMAIN_PIN_DATA(pin_name, reg_addr, reg_offset)	\
	{				\
		.name	= pin_name,	\
		.reg	= reg_addr,	\
		.offset = reg_offset	\
	}

struct bitmain_pinctrl_priv {
	unsigned long base;
	struct bitmain_pin_data *pin_list;
};

int bitmain_pinctrl_set_state(struct udevice *dev, struct udevice *config);
int bitmain_pinctrl_probe(struct udevice *dev);

#endif /* __PINCTRL_EXYNOS_H_ */
