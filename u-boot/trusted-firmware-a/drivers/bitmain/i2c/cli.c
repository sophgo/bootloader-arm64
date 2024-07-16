#include <console.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <i2c.h>
#include <cli.h>

void cmd_read(int argc, char * const argv[])
{
	int i2c = strtoul(argv[2], NULL, 0);
	int addr = strtoul(argv[3], NULL, 0);
	int cmd = strtoul(argv[4], NULL, 0);
	u8 data;

	if (i2c_smbus_read_byte(i2c, addr, cmd, &data))
		printf("i2c read device failed\n");
	else
		printf("0x%02x\n", data);
}

void cmd_write(int argc, char * const argv[])
{
	int i2c = strtoul(argv[2], NULL, 0);
	int addr = strtoul(argv[3], NULL, 0);
	int cmd = strtoul(argv[4], NULL, 0);
	int data = strtoul(argv[5], NULL, 0);

	if (i2c_smbus_write_byte(i2c, addr, cmd, data))
		printf("i2c write device failed\n");
}

void cmd_dump(int argc, char * const argv[])
{
	int i;
	int i2c = strtoul(argv[2], NULL, 0);
	int addr = strtoul(argv[3], NULL, 0);
	int err;

	u8 data[256];

	err = i2c_smbus_read(i2c, addr, 256, 0, data);
	if (err) {
		if (err == -ENODEV)
			printf("i2c%d no such device\n", i2c);
		else
			printf("i2c%d access device failed\n", i2c);
		return;
	}

	for (i = 0; i < 256; ++i) {
		if (i % 16 == 0)
			printf("\n");
		printf("%02x ", data[i]);
	}
	printf("\n");
}

int i2c_cmd(int argc, char * const argv[])
{
	char *cmd;

	cmd = argv[1];

	if (strcmp(cmd, "read") == 0) {
		cmd_read(argc, argv);
	} else if (strcmp(cmd, "write") == 0) {
		cmd_write(argc, argv);
	} else if (strcmp(cmd, "dump") == 0) {
		cmd_dump(argc, argv);
	} else {
		printf("invalid command\n");
		printf("valid commands are: read, write, dump\n");
	}

	return 0;
}

