#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp, *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8;
	unsigned char data[8] = {0};
	int len, read_len;

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("open %s error\n", argv[1]);
		return -1;
	}

	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	fp1 = fopen("ddr1.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp2 = fopen("ddr2.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp3 = fopen("ddr3.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp4 = fopen("ddr4.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp5 = fopen("ddr5.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp6 = fopen("ddr6.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp7 = fopen("ddr7.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}
	fp8 = fopen("ddr8.text", "w+");
	if (fp1 == NULL) {
		printf("open ddr1.text error\n");
		return -1;
	}

	for (int j = 0; j < len; j += 8) {
		memset(data, 0, 8);
		read_len = fread(data, 1, 8, fp);
		if (read_len != 8)
			printf("------------------------------read len=%d\n", read_len);

		for (int k = 0; k < 8; k++) {
			switch (k) {
			case 0:
				fwrite(&(data[0]), 1, 1, fp1);
				break;
			case 1:
				fwrite(&(data[1]), 1, 1, fp2);
				break;
			case 2:
				fwrite(&(data[2]), 1, 1, fp3);
				break;
			case 3:
				fwrite(&(data[3]), 1, 1, fp4);
				break;
			case 4:
				fwrite(&(data[4]), 1, 1, fp5);
				break;
			case 5:
				fwrite(&(data[5]), 1, 1, fp6);
				break;
			case 6:
				fwrite(&(data[6]), 1, 1, fp7);
				break;
			case 7:
				fwrite(&(data[7]), 1, 1, fp8);
				break;
			default:
				break;
			}
		}
	}

	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
	fclose(fp7);
	fclose(fp8);

	return 0;
}
