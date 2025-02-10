#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdint.h>

#define SPI_FLASH_MAX_SIZE	0x4000000
#define DISK_PART_TABLE_ADDR	0x600000
#define BUFFER_SIZE		1024

#define PACK_B_PART

enum {
	CHIP_UNKNOWN = 0,
	CHIP_BM1684,
	CHIP_BM1684X,
	CHIP_MANGO,
};

enum {
	DPT_MAGIC	= 0x55aa55aa,
};

/* disk partition table */
struct part_info {
	/* disk partition table magic number */
	uint32_t magic;
	char name[32];
	uint32_t offset;
	uint32_t size;
	char reserve[4];
	/* load memory address*/
	uint64_t lma;
};

static int spi_flash_pack(int fd_spi, struct part_info *info, const char *name)
{
	int fd, i;
	unsigned char buf[BUFFER_SIZE];
	int read_len;
	int pack_size = 0;

	fd = open(name, O_RDONLY, 0);
	if (fd < 0) {
		printf("open %s failed\n", name);
		return fd;
	}

	lseek(fd_spi, info->offset, SEEK_SET);
	while ((read_len = read(fd, buf, BUFFER_SIZE)) > 0) {
		write(fd_spi, buf, read_len);
		pack_size += read_len;
	}

	close(fd);

	return pack_size;
}

int paser_and_setup_part_info(struct part_info *info,
			      const char *part_name,
			      const char *file_name,
			      uint64_t lma, int offset)
{
	struct stat file_stat;
	int len, size;
	int ret;

	memset(info, 0, sizeof(struct part_info));

	len = strlen(part_name);
	size = sizeof(info->name);

	ret = stat(file_name, &file_stat);
	if (ret || !file_stat.st_size) {
		printf("can't get file %s size %ld\n", file_name,
		       file_stat.st_size);
		return -1;
	}

	info->magic = DPT_MAGIC;
	memcpy(info->name, part_name, len > size ? size : len);
	info->offset = offset;
	info->size = file_stat.st_size;
	info->lma = lma;

	printf("%s offset:0x%x size:0x%x lma:0x%lx\n",
	       info->name, info->offset,
	       info->size, info->lma);

	if (info->offset + info->size > SPI_FLASH_MAX_SIZE) {
		printf("%s too big\n", info->name);
		return -1;
	}

	return 0;
}

static int mango_gen_spi_flash(int argc, char **argv)
{
	int part_num, fd_spi;
	struct part_info *info;
	int offset, size;
	int i, ret;

	char *part_name;
	char *file_name;
	uint64_t lma;

	fd_spi = open("./spi_flash.bin", O_CREAT | O_RDWR, 0644);
	if (fd_spi < 0) {
		printf("open spi_flash failed\n");
		return fd_spi;
	}

	part_num = (argc - 3) / 3;
	offset = DISK_PART_TABLE_ADDR + sizeof(struct part_info) * part_num;
	info = malloc(sizeof(struct part_info) * part_num);
	if (info == NULL) {
		printf("failed to malloc\n");
		close(fd_spi);
		return -1;
	}

	printf("part num = %d\n", part_num);
	for (i = 0; i < part_num; i++) {
		part_name = argv[i * 3 + 3];
		file_name = argv[i * 3 + 4];
		ret = sscanf(argv[i * 3 + 5], "0x%lx", &lma);
		if (ret < 0) {
			printf("sscanf lma error\n");
			goto failed_pack;
		}

		ret = paser_and_setup_part_info(&info[i], part_name, file_name,
						lma, offset);
		if (ret) {
			printf("failed to setup part info\n");
			goto failed_pack;
		}

		size = spi_flash_pack(fd_spi, &info[i], file_name);
		if (size <= 0) {
			printf("failed to pack spi flash\n");
			goto failed_pack;
		}
		offset += size;
	}

	/* write disk partition table */
	lseek(fd_spi, DISK_PART_TABLE_ADDR, SEEK_SET);
	write(fd_spi, info, sizeof(struct part_info) * part_num);

failed_pack:
	close(fd_spi);
	free(info);

	return ret;
}

int main(int argc, char **argv)
{
	int option, ret, fd_spi, fd_bl1, fd_fip, i, offset = 0;
	struct stat fd_statbuf;
	unsigned char raw_byte, *ptr;
	unsigned char zero_byte = 0;
	const char *chip_str = NULL;
	int chip = CHIP_UNKNOWN;

	unsigned int SPIF_OFFSET_A_BL1 = (0);
	unsigned int SPIF_OFFSET_A_PAT = (0x00020000); // 128KB
	unsigned int SPIF_OFFSET_A_FIP = (0x00030000); // 192KB
	unsigned int SPIF_OFFSET_B_BL1 = (0x00200000); // 2MB
	unsigned int SPIF_OFFSET_B_PAT = (0x00220000); // 2MB + 128KB
	unsigned int SPIF_OFFSET_B_FIP = (0x00230000); // 2MB + 192KB
	unsigned int SPIF_OFFSET_BLEND = (0x00400000); // 4MB
	unsigned int SPIF_OFFSET_ALEND = (0x01000000); // 16MB

	while ((option = getopt(argc, argv, "c:")) != -1) {
		switch (option) {
		case 'c':
			chip_str = strdup(optarg);
			if (!chip_str) {
				printf("please give chip name\n");
				return -EFAULT;
			} else if (strncmp(chip_str, "bm1684x", 7) == 0) {
				printf("chip is bm1684x\n");
				chip = CHIP_BM1684X;
			} else if (strncmp(chip_str, "bm1684", 6) == 0) {
				printf("chip is bm1684\n");
				chip = CHIP_BM1684;
			} else if (strncmp(chip_str, "mango", 5) == 0) {
				printf("chip is mango\n");
				chip = CHIP_MANGO;
			}
			break;
		}
	}

	if (chip == CHIP_UNKNOWN) {
		printf("unknown chip!\n");
		return -EINVAL;
	} else if (chip == CHIP_BM1684) {
		SPIF_OFFSET_A_FIP = (0x00040000); // 256KB
		SPIF_OFFSET_B_FIP = (0x00240000); // 2MB + 256KB
	}

	fd_spi = open("./spi_flash.bin", O_CREAT | O_RDWR, 0644);
	if (fd_spi < 0) {
		ret = errno;
		printf("open spi_flash failed %d\n", ret);
		return ret;
	}

	fd_bl1 = open("./bl1.bin", O_RDONLY, 0);
	if (fd_bl1 < 0) {
		ret = errno;
		printf("open bl1 failed %d\n", ret);
		return ret;
	}
	stat("./bl1.bin", &fd_statbuf);
	if (fd_statbuf.st_size > SPIF_OFFSET_A_PAT) {
		printf("bl1 too big %ld\n", fd_statbuf.st_size);
		return -1;
	}

	fd_fip = open("./fip.bin", O_RDONLY, 0);
	if (fd_fip < 0) {
		ret = errno;
		printf("open fip failed %d\n", ret);
		return ret;
	}
	stat("./fip.bin", &fd_statbuf);
	if (fd_statbuf.st_size > (SPIF_OFFSET_B_BL1 - SPIF_OFFSET_A_FIP)) {
		printf("fip too big %ld\n", fd_statbuf.st_size);
		return -1;
	}

	// pack bl1.bin A
	for ( ; offset < SPIF_OFFSET_A_BL1; offset++)
		write(fd_spi, &zero_byte, 1);
	stat("./bl1.bin", &fd_statbuf);
	printf("offset=0x%x, bl1.bin 0x%lx\n", offset, fd_statbuf.st_size);
	for (i = 0; i < fd_statbuf.st_size; i++) {
		read(fd_bl1, &raw_byte, 1);
		write(fd_spi, &raw_byte, 1);
		offset++;
	}

	// pack patch table A
	for ( ; offset < SPIF_OFFSET_A_PAT; offset++)
		write(fd_spi, &zero_byte, 1);
	printf("offset=0x%x, patch table\n", offset);
	// TODO

	// pack fip.bin A
	for ( ; offset < SPIF_OFFSET_A_FIP; offset++)
		write(fd_spi, &zero_byte, 1);
	stat("./fip.bin", &fd_statbuf);
	printf("offset=0x%x, fip.bin 0x%lx\n", offset, fd_statbuf.st_size);
	for (i = 0; i < fd_statbuf.st_size; i++) {
		read(fd_fip, &raw_byte, 1);
		write(fd_spi, &raw_byte, 1);
		offset++;
	}

#ifdef PACK_B_PART
	// pack bl1.bin B
	for ( ; offset < SPIF_OFFSET_B_BL1; offset++)
		write(fd_spi, &zero_byte, 1);
	stat("./bl1.bin", &fd_statbuf);
	printf("offset=0x%x, bl1.bin 0x%lx\n", offset, fd_statbuf.st_size);
	lseek(fd_bl1, 0, SEEK_SET);
	for (i = 0; i < fd_statbuf.st_size; i++) {
		read(fd_bl1, &raw_byte, 1);
		write(fd_spi, &raw_byte, 1);
		offset++;
	}

	// pack patch table B
	for ( ; offset < SPIF_OFFSET_B_PAT; offset++)
		write(fd_spi, &zero_byte, 1);
	printf("offset=0x%x, patch table\n", offset);
	// TODO

	// pack fip.bin B
	for ( ; offset < SPIF_OFFSET_B_FIP; offset++)
		write(fd_spi, &zero_byte, 1);
	stat("./fip.bin", &fd_statbuf);
	printf("offset=0x%x, fip.bin 0x%lx\n", offset, fd_statbuf.st_size);
	lseek(fd_fip, 0, SEEK_SET);
	for (i = 0; i < fd_statbuf.st_size; i++) {
		read(fd_fip, &raw_byte, 1);
		write(fd_spi, &raw_byte, 1);
		offset++;
	}
#endif

	close(fd_spi);
	close(fd_bl1);
	close(fd_fip);

	if (chip == CHIP_MANGO) {
		ret = mango_gen_spi_flash(argc, argv);
		if (ret)
			printf("failed to pack mango spi flash image\n");
		else
			printf("pack mango spi flash image done\n");
	}

	printf("offset=0x%x, end\n", offset);
	return 0;
}
