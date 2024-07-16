/*
 * Copyright (c) 2016-2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __BM_SPI_H__
#define __BM_SPI_H__

#define SPI_CMD_WREN            0x06
#define SPI_CMD_WRDI            0x04
#define SPI_CMD_RDID            0x9F
#define SPI_CMD_RDSR            0x05
#define SPI_CMD_WRSR            0x01
#define SPI_CMD_READ            0x03
#define SPI_CMD_FAST_READ       0x0B
#define SPI_CMD_PP              0x02
#define SPI_CMD_SE              0xD8
#define SPI_CMD_BE              0xC7

#define SPI_STATUS_WIP          (0x01 << 0)
#define SPI_STATUS_WEL          (0x01 << 1)
#define SPI_STATUS_BP0          (0x01 << 2)
#define SPI_STATUS_BP1          (0x01 << 3)
#define SPI_STATUS_BP2          (0x01 << 4)
#define SPI_STATUS_SRWD         (0x01 << 7)

#define SPI_FLASH_BLOCK_SIZE             256
#define SPI_TRAN_CSR_ADDR_BYTES_SHIFT    8
#define SPI_MAX_FIFO_DEPTH               8

/* register definitions */
#define REG_SPI_CTRL                     0x000
#define REG_SPI_CE_CTRL                  0x004
#define REG_SPI_DLY_CTRL                 0x008
#define REG_SPI_DMMR                     0x00C
#define REG_SPI_TRAN_CSR                 0x010
#define REG_SPI_TRAN_NUM                 0x014
#define REG_SPI_FIFO_PORT                0x018
#define REG_SPI_FIFO_PT                  0x020
#define REG_SPI_INT_STS                  0x028
#define REG_SPI_INT_EN                   0x02C

/* bit definition */
#define BIT_SPI_CTRL_CPHA                    (0x01 << 12)
#define BIT_SPI_CTRL_CPOL                    (0x01 << 13)
#define BIT_SPI_CTRL_HOLD_OL                 (0x01 << 14)
#define BIT_SPI_CTRL_WP_OL                   (0x01 << 15)
#define BIT_SPI_CTRL_LSBF                    (0x01 << 20)
#define BIT_SPI_CTRL_SRST                    (0x01 << 21)
#define BIT_SPI_CTRL_SCK_DIV_SHIFT           0
#define BIT_SPI_CTRL_FRAME_LEN_SHIFT         16

#define BIT_SPI_CE_CTRL_CEMANUAL             (0x01 << 0)
#define BIT_SPI_CE_CTRL_CEMANUAL_EN          (0x01 << 1)

#define BIT_SPI_CTRL_FM_INTVL_SHIFT          0
#define BIT_SPI_CTRL_CET_SHIFT               8

#define BIT_SPI_DMMR_EN                      (0x01 << 0)

#define BIT_SPI_TRAN_CSR_TRAN_MODE_RX        (0x01 << 0)
#define BIT_SPI_TRAN_CSR_TRAN_MODE_TX        (0x01 << 1)
#define BIT_SPI_TRAN_CSR_CNTNS_READ          (0x01 << 2)
#define BIT_SPI_TRAN_CSR_FAST_MODE           (0x01 << 3)
#define BIT_SPI_TRAN_CSR_BUS_WIDTH_1_BIT     (0x0 << 4)
#define BIT_SPI_TRAN_CSR_BUS_WIDTH_2_BIT     (0x01 << 4)
#define BIT_SPI_TRAN_CSR_BUS_WIDTH_4_BIT     (0x02 << 4)
#define BIT_SPI_TRAN_CSR_DMA_EN              (0x01 << 6)
#define BIT_SPI_TRAN_CSR_MISO_LEVEL          (0x01 << 7)
#define BIT_SPI_TRAN_CSR_ADDR_BYTES_NO_ADDR  (0x0 << 8)
#define BIT_SPI_TRAN_CSR_WITH_CMD            (0x01 << 11)
#define BIT_SPI_TRAN_CSR_FIFO_TRG_LVL_1_BYTE (0x0 << 12)
#define BIT_SPI_TRAN_CSR_FIFO_TRG_LVL_2_BYTE (0x01 << 12)
#define BIT_SPI_TRAN_CSR_FIFO_TRG_LVL_4_BYTE (0x02 << 12)
#define BIT_SPI_TRAN_CSR_FIFO_TRG_LVL_8_BYTE (0x03 << 12)
#define BIT_SPI_TRAN_CSR_GO_BUSY             (0x01 << 15)

#define BIT_SPI_TRAN_CSR_TRAN_MODE_MASK      0x0003
#define BIT_SPI_TRAN_CSR_ADDR_BYTES_MASK     0x0700
#define BIT_SPI_TRAN_CSR_FIFO_TRG_LVL_MASK   0x3000

#define BIT_SPI_INT_TRAN_DONE                (0x01 << 0)
#define BIT_SPI_INT_RD_FIFO                  (0x01 << 2)
#define BIT_SPI_INT_WR_FIFO                  (0x01 << 3)
#define BIT_SPI_INT_RX_FRAME                 (0x01 << 4)
#define BIT_SPI_INT_TX_FRAME                 (0x01 << 5)

#define BIT_SPI_INT_TRAN_DONE_EN             (0x01 << 0)
#define BIT_SPI_INT_RD_FIFO_EN               (0x01 << 2)
#define BIT_SPI_INT_WR_FIFO_EN               (0x01 << 3)
#define BIT_SPI_INT_RX_FRAME_EN              (0x01 << 4)
#define BIT_SPI_INT_TX_FRAME_EN              (0x01 << 5)

#define SPI_ID_M25P128          0x00182020
#define SPI_ID_N25Q128          0x0018ba20
#define SPI_ID_GD25LQ128        0x001860c8

size_t spi_flash_read_blocks(int lba, uintptr_t buf, size_t size);
size_t spi_flash_write_blocks(int lba, const uintptr_t buf, size_t size);

void bm_spi_init(unsigned long base);
int bm_spi_flash_program(uint8_t *src_buf, uint32_t base, uint32_t size);
int bm_spi_flash_read(uint8_t *dst_buf, uint32_t addr, uint32_t size);

uint32_t bm_spi_read_id(unsigned long spi_base);

void bm_spi_flash_read_sector(unsigned long spi_base, uint32_t addr, uint8_t *buf);
int bm_spi_flash_erase_sector(unsigned long spi_base, uint32_t addr);
int bm_spi_flash_program_sector(unsigned long spi_base, uint32_t addr);

#endif	/* __BM_SPI_H__ */
