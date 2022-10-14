#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>

typedef unsigned int uint;
typedef uint8_t u8;

struct i2c_msg {
	uint addr;
	uint flags;
	uint len;
	u8 *buf;
};

enum dm_i2c_msg_flags {
	I2C_M_TEN               = 0x0010, /* ten-bit chip address */
	I2C_M_RD                = 0x0001, /* read data, from slave to master */
	I2C_M_STOP              = 0x8000, /* send stop after this message */
	I2C_M_NOSTART           = 0x4000, /* no start before this message */
	I2C_M_REV_DIR_ADDR      = 0x2000, /* invert polarity of R/W bit */
	I2C_M_IGNORE_NAK        = 0x1000, /* continue after NAK */
	I2C_M_NO_RD_ACK         = 0x0800, /* skip the Ack bit on reads */
	I2C_M_RECV_LEN          = 0x0400, /* length is first received byte */
};

/* designware i2c init data */
struct i2c_info {
	unsigned long base, freq, speed;
	unsigned long dev[4];
};

int i2c_init(struct i2c_info *info, int n);
int i2c_xfer(int i2c, struct i2c_msg *msg, int nmsgs);
int i2c_smbus_read_byte(int i2c, unsigned char addr,
			unsigned char cmd, unsigned char *data);
int i2c_smbus_write_byte(int i2c, unsigned char addr,
			 unsigned char cmd, unsigned char data);
int i2c_smbus_read(int i2c, unsigned char addr, unsigned int len,
		   unsigned char cmd, unsigned char *data);

#endif
