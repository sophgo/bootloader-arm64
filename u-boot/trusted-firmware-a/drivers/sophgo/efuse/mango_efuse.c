#include <lib/mmio.h>
#include <platform_def.h>

#ifdef EFUSE_TEST
static uint32_t efuse_raw_read(uint32_t address)
{
	uint32_t reg_val;
	int loop = 100;

	if (address > ((1 << EFUSE_NUM_ADDRESS_BITS) - 1))
		return 0;

	if (address == 0 || address == 1) { // embedded read
		mmio_write_32(EFUSE0_BASE + REG_EFUSE_ADR, address);
		reg_val = mmio_read_32(EFUSE0_BASE + REG_EFUSE_MODE);
		reg_val &= ~0x3;
		reg_val |= 0x2;
		mmio_write_32(EFUSE0_BASE + REG_EFUSE_MODE, reg_val);
		while (mmio_read_32(EFUSE0_BASE + REG_EFUSE_MODE) & 0x3) {
			if (loop-- > 0)
				mdelay(1);
			else
				break;
		}
		reg_val = mmio_read_32(EFUSE0_BASE + REG_EFUSE_RD_DATA);
	} else { // sram read
		mmio_write_32(EFUSE0_BASE + REG_EFUSE_ECCSRAM_ADR, address - 2);
		reg_val = mmio_read_32(EFUSE0_BASE + REG_EFUSE_ECCSRAM_RDPORT);
	}
	return reg_val;
}

static void efuse_set_bit(uint32_t address, uint32_t bit_i)
{
	const uint32_t address_mask = (1 << EFUSE_NUM_ADDRESS_BITS) - 1;
	uint32_t adr_val;
	int loop = 100;

	if (address > ((1 << EFUSE_NUM_ADDRESS_BITS) - 1))
		return;

	// embedded write
	adr_val = (address & address_mask) | ((bit_i & 0x1f) << EFUSE_NUM_ADDRESS_BITS);
	mmio_write_32(EFUSE0_BASE + REG_EFUSE_ADR, adr_val);
	mmio_setbits_32(EFUSE0_BASE + REG_EFUSE_MODE, 0x3);
	while (mmio_read_32(EFUSE0_BASE + REG_EFUSE_MODE) & 0x3) {
		if (loop-- > 0)
			mdelay(1);
		else
			break;
	}
}

static void efuse_raw_write(uint32_t address, uint32_t val)
{
	int i;

	for (i = 0; i < 32; i++) {
		if ((val >> i) & 1)
			efuse_set_bit(address, i);
	}
}

void mango_efuse_write(uint32_t address, uint32_t val)
{
	efuse_raw_write(address, val);
}

void mango_efuse_init(void)
{
	uint32_t reg_val;
	int loop = 100;

	// wait eFuse controller idle
	while (mmio_read_32(EFUSE0_BASE + REG_EFUSE_MODE) & 0x3) {
		if (loop-- > 0)
			mdelay(1);
		else
			break;
	}

	// SRAM loading, do it once when bootup
	reg_val = mmio_read_32(EFUSE0_BASE + REG_EFUSE_MODE);
	reg_val = reg_val | (0x3U << 30) | (0x1U << 28);
	mmio_write_32(EFUSE0_BASE + REG_EFUSE_MODE, reg_val);
	loop = 100;
	while (mmio_read_32(EFUSE0_BASE + REG_EFUSE_MODE) & (0x1U << 31)) {
		if (loop-- > 0)
			mdelay(1);
		else
			break;
	}
}
#endif
