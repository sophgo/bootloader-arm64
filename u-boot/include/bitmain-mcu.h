#ifndef __BITMAIN_MCU_H__
#define __BITMAIN_MCU_H__

/*
 * bitmain mcu device driver impliments u-boot misc driver model
 * function return number of byte write on success, otherwise nagtive error number
 * MCU_CALL_ID:
 *	tx_msg should be NULL, tx_size should be 0,
 *	rx_msg return one byte mcu id, rx_size return 1
 * MCU_CALL_MAC:
 *	tx_msg should be NULL, tx_size should be 0,
 *	rx_msg return 48bit mac address array, rx_size return [n * (48 / 8)] bytes,
 *	where n is number of mac addresses
 * MCU_CALL_CMD:
 *	tx_msg should be NULL, tx_size should be 0,
 *	rx_msg return one byte abort boot status,
 *		0: means no abort boot request
 *		1: means some one request abort boot
 *		eg. SA5 MPU want SoC stay on command line when u-boot stage
 *		It MPU can send a message to MCU, and MCU set a flag in register.
 *		SoC should check this flag, if flag is set, it should enter
 *		u-boot command line
 *		rx_size return 1
 * MCU_CALL_SN:
 *	tx_msg should be NULL, tx_size should be 0,
 *	rx_msg return 4bytes SN, rx_size return 4.
 */

#define MCU_MAC_SIZE		(48 / 8)
#define MCU_MAC_MAX		(4)
#define MCU_SN_MAX		(32)

enum {
	MCU_CALL_ID = 0,
	MCU_CALL_MAC,
	MCU_CALL_CMD,
	MCU_CALL_SN,
};

enum {
	MCU_CMD_NOP = 0,	/* no special command should be execute */
	MCU_CMD_ABORTBOOT,	/* soc should abort auto-boot flow and enter command line */
	MCU_CMD_RECOVERY,	/* soc should boot to recovery mode instead of normal mode */
};

enum {
	MCU_BM1684_EVB = 0,
	MCU_BM1684_SM5_TB = 1,
	MCU_BM1684_SC5 = 2,
	MCU_BM1684_SE5_V1 = 3,
	MCU_BM1684_SM5_PB = 4,
	MCU_BM1684_SM5_RB = 5,
	MCU_BM1684_SC5T = 7,
	MCU_BM1684_SC5H = 8,
	MCU_BM1684_SC5P = 9,
	MCU_BM1684_SM5M_PB = 11,
	MCU_BM1684_SM5M_RB = 12,
	MCU_BM1684_SM5M_TB = 13,
	MCU_BM1684_SE5_V2 = 14,
	MCU_BM1684_SE6_CTRL = 15,
};

enum {
	MCU_BM1684X_EVB = 0x20,
	MCU_BM1684X_SE8_CTRL = 0x31,
	MCU_BM1684X_SE8_CUST_V1 = 0x32,
};

enum {
	MCU_MANGO_EVB = 0x80,
};

#define MCU_DEV_NAME	"bm16xxmcu@17"

#endif
