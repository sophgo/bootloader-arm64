#ifndef SDVT_LPC_HOST_DEFINES_H
#define SDVT_LPC_HOST_DEFINES_H
//0---------------------------------------------------------------------------------------------------
//                           SmartDV Technologies Proprietary
//            Copyright 2007-2021 SmartDV Technologies India Private Limited
//
//                               CONFIDENTIAL INFORMATION
//
//                                  All rights reserved
//
//             The use, modification, or duplication of this product is protected
//             according to SmartDV Technologies's licensing agreement.
//
//             This Intellectual property contains confidential and proprietary
//             information which are the properties of SmartDV Technologies.
//
//             Unauthorized use, disclosure, duplication, or reproduction are prohibited.
//0---------------------------------------------------------------------------------------------------
// File Name      : sdvt_lpc_host_defines.h
// Project        : LPC IIP
// Date Created   : 06-29-2021
// Description    : This is C header file for sdvt_lpc_host IP core
// Generator      : IIP Compiler Version 1.1
//0---------------------------------------------------------------------------------------------------

//0###################################################################################################
// #Defines for SYNC
//0###################################################################################################
#define SDVT_LPC_HOST_SYNC_OK                                  0b0000    // Sync Achieved with no error.
#define SDVT_LPC_HOST_SYNC_SHORT_WAIT                          0b0101    // Sync Not Achieved short wait.
#define SDVT_LPC_HOST_SYNC_LONG_WAIT                           0b0110    // Sync Not Achieved long wait.
#define SDVT_LPC_HOST_SYNC_ERROR                               0b1010    // Sync Not Achieved with error.
#define SDVT_LPC_HOST_SYNC_READ_MORE                           0b1001    // Sync Read More

//0###################################################################################################
// Defines for lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_CONTROL                                  0x0       // This register implements LPC Host control register
#define SDVT_LPC_HOST_SERIRQ_CONTROL                           0x4       // This register implements LPC host SERIRQ control register
#define SDVT_LPC_HOST_SERIRQ_IRQ_STAT                          0x8       // This register stores the IRQ frame status of SERIRQ, 0 is for IRQ0 and 31 is for IRQ31
#define SDVT_LPC_HOST_COMMAND                                  0xC       // This register implements LPC Host command register
#define SDVT_LPC_HOST_IDSEL_MADDR                              0x10      // Register to hold Firmware cycle IDSEL, Maddr fields or Memory/IO address or Peripheral address
#define SDVT_LPC_HOST_LPCPD_20MS_TIME                          0x14      // Register to control the 30 microseconds to stop/start LCLK# with respect to LPCPD#
#define SDVT_LPC_HOST_LONG_WAIT_SYNC_TIMEOUT                   0x18      // Register to control the timeout of long wait sync
#define SDVT_LPC_HOST_PERIPHERAL_COMMAND                       0x1C      // This register implements LPC Host peripheral command received
#define SDVT_LPC_HOST_FIFO_STATUS                              0x20      // This register is holds FIFO status
#define SDVT_LPC_HOST_FIFO_CTRL                                0x24      // This register controls Write, Read  and Receive FIFO flush operation
#define SDVT_LPC_HOST_IRQ_ENABLE                               0x28      // LPC Host IRQ enable register
#define SDVT_LPC_HOST_IRQ_STATUS                               0x2C      // LPC Host IRQ status register
#define SDVT_LPC_HOST_SOC_TIMEOUT                              0x30      // SOC timeout register
#define SDVT_LPC_HOST_WR_FIFO                                  0x34      // Write data FIFO
#define SDVT_LPC_HOST_RD_FIFO                                  0x38      // Read data FIFO and
#define SDVT_LPC_HOST_REQ_FIFO                                 0x3C      // DMA/Bus Master Request FIFO

//0###################################################################################################
// Defines for subfields of CSR CONTROL
//0###################################################################################################
#define SDVT_LPC_HOST_CTRL_ENABLE                              0         // Core enable or disable control
#define SDVT_LPC_HOST_CTRL_SYNC_TIMEOUT                        1         // Enable or disable SYNC timeout for long wait sync
#define SDVT_LPC_HOST_CTRL_LFRAME_TIMING                       2         // Lframe timing mode
#define SDVT_LPC_HOST_CTRL_PRESCALER                           10 : 3      // Prescaler for clock divider
#define SDVT_LPC_HOST_CTRL_IFG                                 18 : 11     // Inter frame gap
#define SDVT_LPC_HOST_CTRL_ABORT_WIDTH                         22 : 19     // Controls the width of FRAME# while doing abort
#define SDVT_LPC_HOST_CTRL_DMA_GAP                             26 : 23     // Controls the Gap between DMA and next message in number of LCLK's

//0###################################################################################################
// Defines for subfields of CSR SERIRQ_CONTROL
//0###################################################################################################
#define SDVT_LPC_HOST_SERIRQ_CTRL_ENABLE                       0         // Controls the SERIRQ enable
#define SDVT_LPC_HOST_SERIRQ_CTRL_MODE                         1         // Controls the SERIRQ mode
#define SDVT_LPC_HOST_SERIRQ_CTRL_SWIDTH_QUIET                 5 : 2       // Controls the SERIRQ start pulse width for quiet mode
#define SDVT_LPC_HOST_SERIRQ_CTRL_SWIDTH_CONT                  9 : 6       // Controls the SERIRQ start pulse width for continous mode
#define SDVT_LPC_HOST_SERIRQ_CTRL_SLOTS                        14 : 10     // Controls the number of IRQ slots/frames between start and stop condition
#define SDVT_LPC_HOST_SERIRQ_CTRL_RES_EN                       15        // Controls the reserve frame enable/disable
#define SDVT_LPC_HOST_SERIRQ_CTRL_GAP                          31 : 16     // Controls the Gap between stop and start frame when in continuous mode

//0###################################################################################################
// Defines for subfields of CSR COMMAND
//0###################################################################################################
#define SDVT_LPC_HOST_CMD_PENDING                              0         // LPC Host command pending
#define SDVT_LPC_HOST_CMD_ABORT                                1         // LPC Host command abort in middle, can be set in middle of transfer
#define SDVT_LPC_HOST_CMD_TYPE                                 4 : 2       // LPC Host command type encoding
#define SDVT_LPC_HOST_CMD_DIR                                  5         // LPC Host command direction encoding
#define SDVT_LPC_HOST_CMD_STATUS                               7 : 6       // LPC Host command status encoding
#define SDVT_LPC_HOST_CMD_DMA_CHANNEL                          10 : 8      // LPC Host command DMA Channel encoding
#define SDVT_LPC_HOST_CMD_DMA_SIZE                             12 : 11     // LPC Host command DMA size encoding
#define SDVT_LPC_HOST_CMD_DMA_TC                               13        // LPC Host command DMA terminal count
#define SDVT_LPC_HOST_CMD_SIGNAL_VALUE                         14        // LPC Host command LPCPD/SERIRQ/CLKRUN values to drive, also control Bus master 0 or Bus master 1 while doing SDVT_LPC_HOST_BUS_MASTER command
#define SDVT_LPC_HOST_CMD_MSIZE                                18 : 15     // Firmware Msize
#define SDVT_LPC_HOST_CMD_DMA_READ_MORE                        19        // Sync response for DMA with DMA read more

//0###################################################################################################
// Defines for subfields of CSR IDSEL_MADDR
//0###################################################################################################
#define SDVT_LPC_HOST_MADDR                                    27 : 0      // Firmware Address
#define SDVT_LPC_HOST_IDSEL                                    31 : 28     // Firmware Msize

//0###################################################################################################
// Defines for subfields of CSR PERIPHERAL_COMMAND
//0###################################################################################################
#define SDVT_LPC_HOST_PCMD_TYPE                                1 : 0       // LPC Host Peripheral command type encoding
#define SDVT_LPC_HOST_PCMD_DIR                                 2         // LPC Host Peripheral command direction encoding
#define SDVT_LPC_HOST_PCMD_SIZE                                4 : 3       // LPC Host Peripheral command size of transer

//0###################################################################################################
// Defines for subfields of CSR FIFO_STATUS
//0###################################################################################################
#define SDVT_LPC_HOST_WR_FIFO_EMPTY                            0         // HOST FIFO Status Register - Write FIFO empty
#define SDVT_LPC_HOST_WR_FIFO_FULL                             1         // HOST FIFO Status Register - Write FIFO full
#define SDVT_LPC_HOST_RD_FIFO_EMPTY                            2         // HOST FIFO Status Register - Read FIFO empty
#define SDVT_LPC_HOST_RD_FIFO_FULL                             3         // HOST FIFO Status Register - Read FIFO full
#define SDVT_LPC_HOST_REQ_FIFO_EMPTY                           4         // HOST FIFO Status Register - Request FIFO empty
#define SDVT_LPC_HOST_REQ_FIFO_FULL                            5         // HOST FIFO Status Register - Request FIFO full
#define SDVT_LPC_HOST_WR_FIFO_ELEMENTS                         10 : 6      // HOST FIFO Status Register - Write FIFO number of elements
#define SDVT_LPC_HOST_RD_FIFO_ELEMENTS                         16 : 11     // HOST FIFO Status Register - Read FIFO number of elements
#define SDVT_LPC_HOST_REQ_FIFO_ELEMENTS                        22 : 17     // HOST FIFO Status Register - Request FIFO number of elements

//0###################################################################################################
// Defines for subfields of CSR FIFO_CTRL
//0###################################################################################################
#define SDVT_LPC_HOST_WR_FIFO_FLUSH                            0         // HOST FIFO Control Register - Write FIFO flush
#define SDVT_LPC_HOST_RD_FIFO_FLUSH                            1         // HOST FIFO Control Register - Read FIFO flush
#define SDVT_LPC_HOST_REQ_FIFO_FLUSH                           2         // HOST FIFO Control Register - Request FIFO flush

//0###################################################################################################
// Defines for subfields of CSR IRQ_ENABLE
//0###################################################################################################
#define SDVT_LPC_HOST_IRQ_CMD_DONE                             0         // HOST IRQ enable Register - Command processing done interrupt
#define SDVT_LPC_HOST_IRQ_DMA_REQ                              1         // HOST IRQ enable Register - DMA request from Device/Peripherals
#define SDVT_LPC_HOST_IRQ_BUS_MASTER_REQ                       2         // HOST IRQ enable Register - Bus Master request from Device/Peripherals
#define SDVT_LPC_HOST_IRQ_DMA_ABORT_BM0                        3         // HOST IRQ enable Register - DMA abort from bus master 0
#define SDVT_LPC_HOST_IRQ_DMA_ABORT_BM1                        4         // HOST IRQ enable Register - DMA abort from bus master 1
#define SDVT_LPC_HOST_IRQ_ASSERT_CLKRUN                        5         // HOST IRQ enable Register - CLKRUN signal is asserted (Low)
#define SDVT_LPC_HOST_IRQ_ASSERT_LPME                          6         // HOST IRQ enable Register - LPME signal is asserted (Low)
#define SDVT_LPC_HOST_IRQ_ASSERT_LSMI                          7         // HOST IRQ enable Register - LSMI signal is asserted (Low)
#define SDVT_LPC_HOST_IRQ_DEASSERT_CLKRUN                      8         // HOST IRQ enable Register - CLKRUN signal is deasserted (High)
#define SDVT_LPC_HOST_IRQ_DEASSERT_LPME                        9         // HOST IRQ enable Register - LPME signal is deasserted (High)
#define SDVT_LPC_HOST_IRQ_DEASSERT_LSMI                        10        // HOST IRQ enable Register - LSMI signal is deasserted (High)
#define SDVT_LPC_HOST_IRQ_SERIRQ                               11        // HOST IRQ enable Register - SERIRQ is set by device
#define SDVT_LPC_HOST_IRQ_WR_FIFO_EMPTY                        12        // HOST IRQ enable Register - Write FIFO empty
#define SDVT_LPC_HOST_IRQ_WR_FIFO_FULL                         13        // HOST IRQ enable Register - Write FIFO full
#define SDVT_LPC_HOST_IRQ_RD_FIFO_EMPTY                        14        // HOST IRQ enable Register - Read FIFO empty
#define SDVT_LPC_HOST_IRQ_RD_FIFO_FULL                         15        // HOST IRQ enable Register - Read FIFO full
#define SDVT_LPC_HOST_IRQ_REQ_FIFO_EMPTY                       16        // HOST IRQ enable Register - Request FIFO empty
#define SDVT_LPC_HOST_IRQ_REQ_FIFO_FULL                        17        // HOST IRQ enable Register - Request FIFO full

//0###################################################################################################
// Defines for enum for csr CONTROL field CTRL_LFRAME_TIMING of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_TYPICAL                                  0         // Lframe timing is typical, one LCLK wide
#define SDVT_LPC_HOST_EXTENDED                                 1         // Lframe timing is extended, two LCLK wide

//0###################################################################################################
// Defines for enum for csr SERIRQ_CONTROL field SERIRQ_CTRL_MODE of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_CONTINUOUS_MODE                          0         // SERIRQ Continuous (Idle) Mode
#define SDVT_LPC_HOST_QUIET_MODE                               1         // SERIRQ Quiet (Active) Mode

//0###################################################################################################
// Defines for enum for csr COMMAND field CMD_TYPE of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_IO                                       0         // Field type cycle type I/O
#define SDVT_LPC_HOST_MEMORY                                   1         // Field type cycle type Memory
#define SDVT_LPC_HOST_DMA                                      2         // Field type cycle type DMA
#define SDVT_LPC_HOST_FIRMWARE                                 3         // Field type cycle type Firmware
#define SDVT_LPC_HOST_BUS_MASTER                               4         // Field type cycle type Bus Master
#define SDVT_LPC_HOST_DRIVE_LPCPD                              5         // Drive the LPCPD# signal with given value
#define SDVT_LPC_HOST_DRIVE_CLKRUN                             6         // Drive the CLKRUN# signal with given value
#define SDVT_LPC_HOST_DRIVE_LPME                               7         // Drive the LPME# signal with given value

//0###################################################################################################
// Defines for enum for csr COMMAND field CMD_DIR of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_READ                                     0         // Field cycle direction read
#define SDVT_LPC_HOST_WRITE                                    1         // Field cycle direction write

//0###################################################################################################
// Defines for enum for csr COMMAND field CMD_STATUS of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_SYNC_STAT_TIMEOUT                        1         // Field indicating sync Timeout
#define SDVT_LPC_HOST_SYNC_STAT_ERROR                          2         // Field indicating sync Error

//0###################################################################################################
// Defines for enum for csr COMMAND field CMD_DMA_CHANNEL of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_DMA_CHANNEL_0                            0         // DMA Channel 0
#define SDVT_LPC_HOST_DMA_CHANNEL_1                            1         // DMA Channel 1
#define SDVT_LPC_HOST_DMA_CHANNEL_2                            2         // DMA Channel 2
#define SDVT_LPC_HOST_DMA_CHANNEL_3                            3         // DMA Channel 3
#define SDVT_LPC_HOST_DMA_CHANNEL_5                            5         // DMA Channel 5
#define SDVT_LPC_HOST_DMA_CHANNEL_6                            6         // DMA Channel 6
#define SDVT_LPC_HOST_DMA_CHANNEL_7                            7         // DMA Channel 7

//0###################################################################################################
// Defines for enum for csr COMMAND field CMD_DMA_SIZE of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_DMA_SIZE_8B                              0         // DMA transfer size is 8 bits
#define SDVT_LPC_HOST_DMA_SIZE_16B                             1         // DMA transfer size is 16 bits
#define SDVT_LPC_HOST_DMA_SIZE_32B                             3         // DMA transfer size is 32 bits

//0###################################################################################################
// Defines for enum for csr COMMAND field CMD_MSIZE of lpc_host
//0###################################################################################################
#define SDVT_LPC_HOST_MSIZE_1B                                 0         // Firmware transfer size is 1 byte
#define SDVT_LPC_HOST_MSIZE_2B                                 1         // Firmware transfer size is 2 bytes
#define SDVT_LPC_HOST_MSIZE_4B                                 2         // Firmware transfer size is 4 bytes
#define SDVT_LPC_HOST_MSIZE_16B                                4         // Firmware transfer size is 16 bytes
#define SDVT_LPC_HOST_MSIZE_128B                               7         // Firmware transfer size is 128 bytes

//0---------------------------------------------------------------------------------------------------
//                           SmartDV Technologies Proprietary
//            Copyright 2007-2021 SmartDV Technologies India Private Limited
//
//                               CONFIDENTIAL INFORMATION
//
//                                  All rights reserved
//
//             The use, modification, or duplication of this product is protected
//             according to SmartDV Technologies's licensing agreement.
//
//             This Intellectual property contains confidential and proprietary
//             information which are the properties of SmartDV Technologies.
//
//             Unauthorized use, disclosure, duplication, or reproduction are prohibited.
//0---------------------------------------------------------------------------------------------------
#endif
