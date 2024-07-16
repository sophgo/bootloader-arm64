#include <mmio.h>
#include <gpio.h>
#include <stdlib.h>

unsigned long DW_GPIO_BASE, DW_GPIO_PORT_SIZE, DW_GPIO_PORT_WIDTH;

#define DW_GPIOA_DR_OFFSET	0x00
#define DW_GPIOA_DDR_OFFSET	0x04
#define DW_GPIOA_EXT_OFFSET	0x50

/* mango gpio range from 0 to 92 */

static int dw_gpio_get_direction(int gpio)
{
	int ctrl, shift;
	uintptr_t reg;

	ctrl = gpio / DW_GPIO_PORT_WIDTH;
	shift = gpio % DW_GPIO_PORT_WIDTH;

	reg = DW_GPIO_BASE + DW_GPIO_PORT_SIZE * ctrl
		+ DW_GPIOA_DDR_OFFSET;

	return ((mmio_read_32(reg) >> shift) & 1) ? GPIO_DIR_OUT : GPIO_DIR_IN;
}

static void dw_gpio_set_direction(int gpio, int dir)
{
	int ctrl, shift;
	uintptr_t reg;

	ctrl = gpio / DW_GPIO_PORT_WIDTH;
	shift = gpio % DW_GPIO_PORT_WIDTH;

	reg = DW_GPIO_BASE + DW_GPIO_PORT_SIZE * ctrl
		+ DW_GPIOA_DDR_OFFSET;

	if (dir == GPIO_DIR_IN)
		mmio_clrbits_32(reg, 1 << shift);
	else
		mmio_setbits_32(reg, 1 << shift);
}

static void dw_gpio_set_value(int gpio, int value)
{
	int ctrl, shift;
	uintptr_t reg;

	ctrl = gpio / DW_GPIO_PORT_WIDTH;
	shift = gpio % DW_GPIO_PORT_WIDTH;

	reg = DW_GPIO_BASE + DW_GPIO_PORT_SIZE * ctrl
		+ DW_GPIOA_DR_OFFSET;

	if (value == GPIO_LEVEL_HIGH)
		mmio_setbits_32(reg, 1 << shift);
	else
		mmio_clrbits_32(reg, 1 << shift);
}

static int dw_gpio_get_value(int gpio)
{
	int ctrl, shift;
	uintptr_t reg;

	ctrl = gpio / DW_GPIO_PORT_WIDTH;
	shift = gpio % DW_GPIO_PORT_WIDTH;

	reg = DW_GPIO_BASE + DW_GPIO_PORT_SIZE * ctrl
		+ DW_GPIOA_EXT_OFFSET;

	return ((mmio_read_32(reg) >> shift) & 1) ?
		GPIO_LEVEL_HIGH : GPIO_LEVEL_LOW;
}

/* pull function is configured by top pinmux */
static const gpio_ops_t dw_gpio_ops = {
	.get_direction = dw_gpio_get_direction,
	.set_direction = dw_gpio_set_direction,
	.get_value = dw_gpio_get_value,
	.set_value = dw_gpio_set_value,
	.set_pull = NULL,
	.get_pull = NULL,
};

void dw_gpio_init(unsigned long base, unsigned long size, unsigned long width)
{
	DW_GPIO_BASE = base;
	DW_GPIO_PORT_SIZE = size;
	DW_GPIO_PORT_WIDTH = width;

	gpio_init(&dw_gpio_ops);
}
