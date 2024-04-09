/*
 * Copyright (c) 2021-2025, Sophgo Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MANGO_PCIE_H
#define MANGO_PCIE_H

#include <stdint.h>
#include <lib/utils_def.h>


#define PCIE0_MSG_FIFO_BASE    0x23fffff0000
#define PCIE1_MSG_FIFO_BASE    0x27fffff0000
#define PCIE2_MSG_FIFO_BASE    0x2bfffff0000
#define PCIE3_MSG_FIFO_BASE    0x2ffffff0000

#define PCIE_CFG_LINK0_APB     0x000000
#define PCIE_CFG_LINK1_APB     0x800000
#define PCIE_CFG_PHY_APB       0x1000000
#define PCIE_CFG_MANGO_APB     0x1800000

#define FUNC_CONFIG_REG_0            0x000000
#define FUNC_CONFIG_REG_1            0x001000
#define FUNC_CONFIG_REG_2            0x002000
#define FUNC_CONFIG_REG_3            0x003000
#define FUNC_CONFIG_REG_4            0x004000
#define FUNC_CONFIG_REG_5            0x005000
#define FUNC_CONFIG_REG_6            0x006000
#define FUNC_CONFIG_REG_7            0x007000
#define VIRTUAL_FUNC_CONFIG_REG_0    0x008000
#define VIRTUAL_FUNC_CONFIG_REG_1    0x009000
#define VIRTUAL_FUNC_CONFIG_REG_2    0x00a000
#define VIRTUAL_FUNC_CONFIG_REG_3    0x00b000
#define VIRTUAL_FUNC_CONFIG_REG_4    0x00c000
#define VIRTUAL_FUNC_CONFIG_REG_5    0x00d000
#define VIRTUAL_FUNC_CONFIG_REG_6    0x00e000
#define VIRTUAL_FUNC_CONFIG_REG_7    0x00f000
#define PCIE_PF_OFFSET               0x000000
#define PCIE_LM_OFFSET               0x100000
#define PCIE_RP_OFFSET               0x200000
#define PCIE_AXI_OFFSET              0x400000
#define PCIE_DMA_OFFSET              0x600000
#define PCIE_HAL_MGT_REG             0x040000

#define PCIE_IRS_REG0000     0x0000
#define PCIE_IRS_REG0004     0x0004
#define PCIE_IRS_REG0008     0x0008
#define PCIE_IRS_REG000C     0x000C
#define PCIE_IRS_REG0010     0x0010
#define PCIE_IRS_REG0014     0x0014
#define PCIE_IRS_REG0018     0x0018
#define PCIE_IRS_REG001C     0x001C
#define PCIE_IRS_REG0020     0x0020
#define PCIE_IRS_REG0024     0x0024
#define PCIE_IRS_REG0038     0x0038
#define PCIE_IRS_REG007C     0x007C
#define PCIE_IRS_REG0080     0x0080
#define PCIE_IRS_REG00C0     0x00C0
#define PCIE_IRS_REG00F8     0x00F8
#define PCIE_IRS_REG0160     0x0160
#define PCIE_IRS_REG0170     0x0170
#define PCIE_IRS_REG0178     0x0178
#define PCIE_IRS_REG017C     0x017C
#define PCIE_IRS_REG01A0     0x01A0
#define PCIE_IRS_REG01A4     0x01A4
#define PCIE_IRS_REG01A8     0x01A8
#define PCIE_IRS_REG01AC     0x01AC
#define PCIE_IRS_REG01C0     0x01C0
#define PCIE_IRS_REG0200     0x0200
#define PCIE_IRS_REG0204     0x0204
#define PCIE_IRS_REG0208     0x0208
#define PCIE_IRS_REG02EC     0x02EC
#define PCIE_IRS_REG02F0     0x02F0
#define PCIE_IRS_REG02F8     0x02F8
#define PCIE_IRS_REG03A0     0x03A0
#define PCIE_IRS_REG03B0     0x03B0
#define PCIE_IRS_REG03CC     0x03CC
#define PCIE_IRS_REG0400     0x0400
#define PCIE_IRS_REG0404     0x0404
#define PCIE_IRS_REG0408     0x0408
#define PCIE_IRS_REG040C     0x040C
#define PCIE_IRS_REG0418     0x0418
#define PCIE_IRS_REG041C     0x041C
#define PCIE_IRS_REG0420     0x0420
#define PCIE_IRS_REG0424     0x0424
#define PCIE_IRS_REG0844     0x0844
#define PCIE_IRS_REG0848     0x0848
#define PCIE_IRS_REG084C     0x084C
#define PCIE_IRS_REG0850     0x0850
#define PCIE_IRS_REG0858     0x0858

#define LINKX_RP_CTRL_STS_REG           0xd0
#define LINKX_PF_MSI_ADDR_L_REG         0x94
#define LINKX_PF_MSI_ADDR_H_REG         0x98
#define LINKX_PF_MSI_DATA_REG           0x9c
#define LINKX_PF_CTRL_STS_REG           0xd0
#define LINKX_PF_DEV_CAP_REG            0xC4
#define LINKX_PF_DEV_CTRL_AND_STS_REG   0xC8
#define LINKX_PF_VC_RES_CTRL_REG_0      0x4d4
#define LINKX_PF_VC_RES_CTRL_REG_1      0x4e0
#define LINKX_RP_DEV_CAP_REG            0xC4
#define LINKX_RP_DEV_CTRL_AND_STS_REG   0xC8
#define LINKX_LM_DBG_MUX_CTRL2_REG      0x234
#define LINKX_LM_PF_BAR_CFG_REG_0       0x240
#define LINKX_LM_PF_BAR_CFG_REG_1       0x244
#define LINKX_LM_PF_PHY_FUNC_CFG_REG    0x2C0
#define LINKX_LM_CCIX_CTRL_REG          0xca4
#define LINKX_RP_CMD_STS_REG            0x04
#define LINKX_LM_RC_BAR_CFG_REG         0x300
#define LINKX_RP_RC_BAR0_REG            0x10
#define LINKX_RP_RC_BAR1_REG            0x14
#define LINKX_RP_VC_RES_CTRL_REG_0      0x4d4
#define LINKX_RP_VC_RES_CTRL_REG_1      0x4e0
#define LINKX_AXI_R0_OB_AT_REG_0        0x0
#define LINKX_AXI_R0_OB_AT_REG_1        0x4
#define LINKX_AXI_R0_OB_DSPT_REG_0      0x8
#define LINKX_AXI_R0_OB_DSPT_REG_1      0xC
#define LINKX_AXI_R0_AXI_RGN_ADDR_REG_0 0x18
#define LINKX_AXI_R0_AXI_RGN_ADDR_REG_1 0x1C

#define LINKX_AXI_BAR0_RP_IB_AT_REG_L   0x800
#define LINKX_AXI_BAR0_RP_IB_AT_REG_H   0x804
#define LINKX_AXI_BAR1_RP_IB_AT_REG_L   0x808
#define LINKX_AXI_BAR1_RP_IB_AT_REG_H   0x80C

#define LINKX_PCIE_DMA_CHN0_CTRL_REG    0x0
#define LINKX_PCIE_DMA_CHN0_SP_LO_REG   0x4
#define LINKX_PCIE_DMA_CHN0_SP_HI_REG   0x8
#define LINKX_PCIE_DMA_CHN0_ATTR_LO_REG 0xC
#define LINKX_PCIE_DMA_CHN0_ATTR_HI_REG 0x10
#define LINKX_PCIE_DMA_INT_REG          0xA0
#define LINKX_PCIE_INT_EN_REG           0xA4
#define LINKX_PCIE_INT_DIS_REG          0xA8

#define CDNS_PHY_VGA_LUT_ADDR_REG		0x60E8
#define CDNS_PHY_VGA_LUT_DATA_REG		0x60E9
#define CDNS_PHY_DBG_MUX_CTRL2_REG		0x08D
#define CDNS_PHY_PIPE_FIFO_LATENCY_CTRL_REG 0x0DA
#define CNDS_PHY_G3_G4_LNK_EQ_CTRL_REG  0x0DF
#define CDNS_PHY_LNK_EQ_CTRL2_REG		0x398

#define IRS_REG0000_ENABLE_FULL_PIPE_MUX_BIT                   2
#define IRS_REG0000_LINK0_BYPASS_RMT_TX_EQ                     5
#define IRS_REG0000_REG_LINK0_PM_RESET_N_BIT                   9
#define IRS_REG0000_LINK1_CLK_ENABLE_BIT                       14
#define IRS_REG0000_PM_CLK_KICK_OFF_BIT                        15
#define IRS_REG0004_LINK0_CONFIG_ENABLE_BIT                    5
#define IRS_REG0004_LINK0_CORE_CLK_SHUTOFF_DETECT_EN_BIT       6
#define IRS_REG0004_LINK0_MODE_SELECT_BIT                      7
#define IRS_REG0004_LINK0_LINK_TRAINING_ENABLE_BIT             12
#define IRS_REG0004_LINK0_DISABLE_GEN3_DC_BALANCE_BIT          13
#define IRS_REG0038_LINK0_PWR_FAULT_N_BIT                      17
#define IRS_REG0038_LINK0_PRSNT_N_BIT                          18
#define IRS_REG007C_LINK0_VC_COUNT_BIT                         22
#define IRS_REG007C_LINK0_PCIE_TARGET_NON_POSTED_REJ_BIT       23
#define IRS_REG007C_REG_LINK0_AXI_RESET_N_BIT                  24
#define IRS_REG0080_LINK0_CLOCK_STABLE_BIT                     31
#define IRS_RGE00F8_CCIX_VC_ENABLE_BIT                         15
#define IRS_REG0160_LINK1_LINK_TRAINING_ENABLE_BIT             1
#define IRS_REG0160_LINK1_DISABLE_GEN3_DC_BALANCE_BIT          12
#define IRS_REG0160_LINK1_CORE_CLK_SHUTOFF_DETECT_EN_BIT       14
#define IRS_REG0160_LINK1_CONFIG_ENABLE_BIT                    20
#define IRS_REG0170_REG_LINK1_AXI_RESET_N_BIT                  22
#define IRS_REG0170_LINK1_PCIE_TARGET_NON_POSTED_REJ_BIT       25
#define IRS_REG0170_REG_LINK1_PM_RESET_N_BIT                   26
#define IRS_REG0178_LINK1_MODE_SELECT_BIT                      7
#define IRS_REG017C_LINK1_MGMT_RESET_N_BIT                     0
#define IRS_REG017C_LINK1_MGMT_STICKY_RESET_N_BIT              1
#define IRS_REG01C0_REG_PHY_P00_RESET_N                        0
#define IRS_REG01C0_REG_PHY_P01_RESET_N                        1
#define IRS_REG01C0_LINK1_PRSNT_N_BIT                          30
#define IRS_REG01C0_LINK1_PWR_FAULT_N_BIT                      31
#define IRS_REG02F8_PHY_RESET_N_BIT_BIT                        31
#define IRS_REG03A0_PIPE_P01_RESET_N_BIT                       0
#define IRS_REG03A0_LINK1_RESET_N_BIT                          1
#define IRS_REG03A0_PIPE_P00_RESET_N_BIT                       2
#define IRS_REG03A0_LINK0_RESET_N_BIT                          3
#define IRS_REG03A0_PCIE1_RESET_X_FROM_PAD_BIT                 10
#define IRS_REG03A0_PCIE0_RESET_X_FROM_PAD_BIT                 11
#define IRS_REG03B0_REG_CTRL1_APB_RST_BIT                      18
#define IRS_REG03B0_REG_CTRL0_APB_RST_BIT                      19
#define IRS_REG03B0_REG_PHY_APB_RST_BIT                        20
#define IRS_REG03CC_LINK0_MGMT_RESET_N_BIT                     29
#define IRS_REG03CC_LINK0_MGMT_STICKY_RESET_N_BIT              28

//#define RETRAIN_LINK_BIT                         5
#define LINK0_VC_RES_CTRL_TC_VC_MAP_BIT            0
#define LINK0_VC_RES_CTRL_VC_ENABLE_BIT            31

#define IRS_REG0000_PMA_CMN_REFCLK_DIG_DIV_MASK     GENMASK(1, 0)
#define IRS_REG0004_LINK0_LANE_COUNT_IN_MASK        GENMASK(10, 8)
#define IRS_REG0038_LINK0_MAX_EVAL_ITERATION_MASK   GENMASK(10, 4)
#define IRS_REG0038_LINK0_SUPPORTED_PRESET_MASK     GENMASK(30, 20)
#define IRS_REG0038_LINK0_PCIE_GENERATION_SEL_MASK  GENMASK(16, 14)
#define IRS_REG0080_LINK0_NEGOTIATED_SPEED          GENMASK(18, 16)
#define IRS_REG0080_LINK0_NEGOTIATED_LINK_WIDTH     GENMASK(21, 19)
#define IRS_REG0080_LINK0_LINK_STATUS_MASK          GENMASK(23, 22)
#define IRS_REG00C0_LINK0_LTSSM_STATE_MASK          GENMASK(8, 3)
#define IRS_REG0178_LINK1_PCIE_GENERATION_SEL_MASK  GENMASK(10, 8)
#define IRS_REG0178_LINK1_SUPPORTED_PRESET_MASK     GENMASK(23, 13)
#define IRS_REG0178_LINK1_LANE_COUNT_IN_MASK        GENMASK(25, 24)
#define IRS_REG0200_LINK1_NEGOTIATED_LINK_WIDTH     GENMASK(1, 0)
#define IRS_REG0200_LINK1_LINK_STATUS_MASK          GENMASK(8, 7)
#define IRS_REG0204_LINK1_LTSSM_STATE_MASK          GENMASK(8, 3)
#define IRS_REG0208_LINK1_NEGOTIATED_SPEED          GENMASK(2, 0)
#define IRS_REG02F8_PMA_CMN_REFCLK1_DIG_DIV_MASK    GENMASK(30, 29)
#define IRS_REG0858_CCIX_BUS_NUM_MASK               GENMASK(15, 0)

#define LINK0_VC_RES_CTRL_MASK                      GENMASK(30, 0)
#define LINK0_LM_CCIX_CTRL_VENDOR_ID_MASK           GENMASK(15, 0)
#define LINKX_LM_DBG_MUX_CTRL2_MAX_NP_REQ_MASK      GENMASK(22, 13)
#define LINKX_DEV_CAP_MAX_PL_MASK                   GENMASK(2, 0)
#define LINKX_DEV_CTRL_AND_STS_MPS_MASK             GENMASK(7, 5)
#define LINKX_DEV_CTRL_AND_STS_MRRS_MASK            GENMASK(14, 12)
#define LTSSM_POLLING_MAX_TIMES         10000
#define LTSSM_STATE_L0                  0x10
#define LTSSM_STATE_RECOVERY_IDLE       0xE
#define MANGO_GPIO12_FOR_PCIE_PERST     12

typedef enum {
	PCIE_ID_0 = 0x0,
	PCIE_ID_1,
	PCIE_ID_BUTT
} PCIE_ID;

typedef enum {
	PCIE_LINK0_X1 = 0x0,
	PCIE_LINK0_X2,
	PCIE_LINK0_X4,
	PCIE_LINK0_X8,
	PCIE_LINK0_X16,
	PCIE_LINK1_X1,
	PCIE_LINK1_X2,
	PCIE_LINK1_X4,
	PCIE_LINK1_X8,
	PCIE_LINK0_X8_LINK1_X8,
	PCIE_LANE_MODE_BUTT
} PCIE_LANES_MODE;

typedef enum {
	PCIE_OP_MODE_EP = 0x0,
	PCIE_OP_MODE_RC,
	PCIE_OP_MODE_CCIX,
	PCIE_OP_MODE_BUTT
} PCIE_OP_MODE;

typedef enum {
	PCIE_LINK_0 = 0x0,
	PCIE_LINK_1,
	PCIE_LINK_BUTT
} PCIE_LINK_ID;

typedef enum {
	PCIE_LINK_NO_RECEIVERS_DETECTED = 0x0,
	PCIE_LINK_LINK_TRAINNING_IN_PROGRESS,
	PCIE_LINK_DL_INIT_IN_PROGRESS,
	PCIE_LINK_DL_INIT_COMPLETED,
	PCIE_LINK_STATUS_BUTT
} PCIE_LINK_STATUS;

typedef enum {
	PCIE_LINK_WIDTH_X1 = 0x0,
	PCIE_LINK_WIDTH_X2,
	PCIE_LINK_WIDTH_X4,
	PCIE_LINK_WIDTH_X8,
	PCIE_LINK_WIDTH_X16,
	PCIE_LINK_WIDTH_BUTT
} PCIE_LINK_WIDTH;

typedef enum {
	PCIE_LINK_SPEED_2G5 = 0x0,
	PCIE_LINK_SPEED_5G,
	PCIE_LINK_SPEED_8G,
	PCIE_LINK_SPEED_16G,
	PCIE_LINK_SPEED_BUTT
} PCIE_LINK_SPEED;

typedef enum {
	PCIE_MPS_128B = 0x0,
	PCIE_MPS_256B,
	PCIE_MPS_512B,
	PCIE_MPS_1024B,
	PCIE_MPS_BUTT
} PCIE_MAX_PAYLOAD;

typedef enum {
	PCIE_MRRS_128B = 0x0,
	PCIE_MRRS_256B,
	PCIE_MRRS_512B,
	PCIE_MRRS_1024B,
	PCIE_MRRS_BUTT
} PCIE_MAX_READ_REQ_SIZE;

/** uDMA transfer direction */
typedef enum {
	/** Undefined */
	PCIE_UNDEFINED_DIR = 0U,
	/** Inbound transfer, to system memory */
	PCIE_INB_DIR = 1U,
	/** Outbound transfer, to external memory */
	PCIE_OUTB_DIR = 2U
} PCIE_TD_DIRECTION;

struct cdns_reg_pairs {
	uint16_t offset;
	uint16_t value;
};

typedef struct {
	uint32_t pcie_addr_l;
	uint32_t pcie_addr_h;
	uint32_t dspt0;
	uint32_t dspt1;
	uint32_t cpu_addr_l;
	uint32_t cpu_addr_h;
} PCIE_AXI_REGION;

/** uDMA control byte bitfields */
typedef struct {
	/** Control bits */
	uint8_t control_bits;
} PCIE_CBITS;

/** uDMA transfer size and control byte */
typedef struct {
	/** Number of bytes to be transferred.  For max bulk transfer size, set to zero */
	uint32_t size : 24;
	/** Control byte */
	PCIE_CBITS ctrl_bits;
} PCIE_SZ_CTRL;

/** uDMA status bytes */
typedef struct {
	/** System (local) bus status */
	uint8_t sys_status;
	/** External (remote) bus status */
	uint8_t ext_status;
	/** uDMA channel status */
	uint8_t chnl_status;
	/** Reserved */
	uint8_t reserved_0;
} PCIE_SBYTES;

typedef struct {
	/** Low 32 bits of system address */
	uint32_t sys_lo_addr;
	/** High 32 bits of system address */
	uint32_t sys_hi_addr;
	/** Access attributes for system bus */
	uint32_t sys_attr;
	/** Low 32 bits of external address */
	uint32_t ext_lo_addr;
	/** High 32 bits of external address */
	uint32_t ext_hi_addr;
	/** Access attributes for external bus */
	uint32_t ext_attr;
	/** High 32 bits of access attributes for external bus */
	uint32_t ext_attr_hi;
	/** Transfer size and control byte */
	PCIE_SZ_CTRL size_and_ctrl;
	/** Transfer status.  This word is written by uDMA engine, and can be read to determine status. */
	PCIE_SBYTES status;
	/** Low 32bits of pointer to next descriptor in linked list */
	uint32_t next;
	/** High 32bits of pointer to next descriptor in linked list */
	uint32_t next_hi_addr;
} PCIE_XD_DESC;

int mango_pcie_get_max_payload(PCIE_ID pcie_id, PCIE_LINK_ID link_id,
			       uint32_t func, PCIE_OP_MODE op_mode, PCIE_MAX_PAYLOAD *mps);
int mango_pcie_set_max_payload(PCIE_ID pcie_id, PCIE_LINK_ID link_id,
			       uint32_t func, PCIE_OP_MODE op_mode, PCIE_MAX_PAYLOAD mps);
int mango_pcie_set_max_read_req_size(PCIE_ID pcie_id, PCIE_LINK_ID link_id,
				     uint32_t func, PCIE_OP_MODE op_mode, PCIE_MAX_READ_REQ_SIZE mrrs);
void mango_pcie_init(PCIE_ID pcie_id, PCIE_OP_MODE op_mode, PCIE_LANES_MODE lanes, PCIE_LINK_SPEED speed);
void mango_pcie_slt_init(PCIE_ID pcie_id, PCIE_OP_MODE lk0_op_mode, PCIE_OP_MODE lk1_op_mode,
			 PCIE_LANES_MODE lanes, PCIE_LINK_SPEED speed);
int pcie_write_msi(PCIE_ID pcie_id, PCIE_LINK_ID link_id);
void mango_ccix_init(PCIE_ID pcie_id, PCIE_OP_MODE op_mode, PCIE_LINK_SPEED speed);
int pcie_udma_test(PCIE_ID pcie_id, PCIE_OP_MODE op_mode, PCIE_TD_DIRECTION dir);
#endif /* MANGO_PCIE_H */

