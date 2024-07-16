#ifndef SDVT_LPC_HOST_BASIC_H
#define SDVT_LPC_HOST_BASIC_H
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
// File Name      : sdvt_lpc_host_basic.h
// Project        : LPC IIP
// Date Created   : 06-29-2021
// Description    : This is simple LPC Master driver header file
// Generator      : IIP Compiler Version 1.1
//0---------------------------------------------------------------------------------------------------
struct sdvt_lpc_host_command {
	uint8_t                 cmd_type_3b; // Holds the Command type to send
	uint8_t                 dir_b; // Holds the Direction of command
	uint8_t                 chan_idsel_3b; // Holds the DMA channel or IDSEL
	uint8_t                 size_2b; // Holds the Number of bytes to transfeer
	uint8_t                 tc_b; // Holds the DMA TC bit
	uint8_t                 signal_b; // Holds the Signal value to drive
	uint8_t                 msize_4b; // Holds the MSIZE value for Firmware commands
	uint8_t                 dma_rd_more_b; // Holds the DMA read more bit
	uint32_t                irq_18b; // Holds the IRQ Status
};

struct sdvt_lpc_host_config {
	uint8_t                 ctrl_enable_b; // Core enable control
	uint8_t                 ctrl_sync_timeout_b; // Core sync timeout enable
	uint8_t                 ctrl_lframe_time_b; // Core LFRAME timing control
	uint16_t                ctrl_prescaler_16b; // Core prescaler is used to divide i_clk to get desired o_scl clock
	uint8_t                 ctrl_ifg_8b; // Core inter frame gap counts between two transfers
	uint8_t                 ctrl_abort_width_8b; // Core abort width
	uint32_t                irq_enable_18b; // Master IRQ enable register
};

//0---------------------------------------------------------------------------------------------------
// write_reg :#This is for register write
//0---------------------------------------------------------------------------------------------------
//             p_addr_8b :#Register address to write
//            p_data_32b :#Register data to write
//0---------------------------------------------------------------------------------------------------
extern void write_reg(uint8_t p_addr_8b, uint32_t p_data_32b);

//0---------------------------------------------------------------------------------------------------
// read_reg :#This is for register read
//0---------------------------------------------------------------------------------------------------
//               returns :#Return the read data
//             p_addr_8b :#Register address to read
//0---------------------------------------------------------------------------------------------------
extern uint32_t read_reg(uint8_t p_addr_8b);

//0---------------------------------------------------------------------------------------------------
// init_chip :#This method is used to initialize the chip
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//0---------------------------------------------------------------------------------------------------
extern void init_chip(struct sdvt_lpc_host_config *p_config_st);

//0---------------------------------------------------------------------------------------------------
// send_command :#This method is used for sending command
//0---------------------------------------------------------------------------------------------------
//              p_cmd_st :#Pointer to command object
//            p_addr_32b :#Address to send
//            p_data_32b :#Data to send
//0---------------------------------------------------------------------------------------------------
extern void send_command(struct sdvt_lpc_host_command *p_cmd_st, uint32_t p_addr_32b, uint32_t p_data_32b);

//0---------------------------------------------------------------------------------------------------
// write_control_reg :#This method is used to write control register
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//0---------------------------------------------------------------------------------------------------
extern void write_control_reg(struct sdvt_lpc_host_config *p_config_st);

//0---------------------------------------------------------------------------------------------------
// enable_chip :#This method is used to enable/disable chip
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//            p_enable_b :#1 means enable, 0 means disable
//0---------------------------------------------------------------------------------------------------
extern void enable_chip(struct sdvt_lpc_host_config *p_config_st, uint8_t p_enable_b);

//0---------------------------------------------------------------------------------------------------
// mask_irq :#This method is used to mask the IRQ
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//            p_mask_18b :#Interrupts to mask
//0---------------------------------------------------------------------------------------------------
extern void mask_irq(struct sdvt_lpc_host_config *p_config_st, uint32_t p_mask_18b);

//0---------------------------------------------------------------------------------------------------
// unmask_irq :#This method is used to unmask the IRQ
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//            p_mask_18b :#Interrupts to mask
//0---------------------------------------------------------------------------------------------------
extern void unmask_irq(struct sdvt_lpc_host_config *p_config_st, uint32_t p_mask_18b);

//0---------------------------------------------------------------------------------------------------
// reset_chip :#This method is used to reset the chip
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//0---------------------------------------------------------------------------------------------------
extern void reset_chip(struct sdvt_lpc_host_config *p_config_st);

//0---------------------------------------------------------------------------------------------------
// wait_command_done :#This method is used for waiting for completion of request
//0---------------------------------------------------------------------------------------------------
//             parameter :No parameter
//0---------------------------------------------------------------------------------------------------
extern void wait_command_done(void);

//0---------------------------------------------------------------------------------------------------
// irq_handler :#This method is used to handle the interrupts
//0---------------------------------------------------------------------------------------------------
//              p_cmd_st :#Pointer to command object
//0---------------------------------------------------------------------------------------------------
extern void irq_handler (struct sdvt_lpc_host_command *p_cmd_st);

//0---------------------------------------------------------------------------------------------------
// print_config :#This method is used to print all config registers
//0---------------------------------------------------------------------------------------------------
//           p_config_st :#Pointer to config object
//0---------------------------------------------------------------------------------------------------
extern void print_config(struct sdvt_lpc_host_config *p_config_st);

//0---------------------------------------------------------------------------------------------------
// print_command :#This method is used to print command being sent
//0---------------------------------------------------------------------------------------------------
//              p_mode_i :#0, print command, 1 print status also
//              p_cmd_st :#Pointer to command object
//0---------------------------------------------------------------------------------------------------
extern void print_command(int p_mode_i, struct sdvt_lpc_host_command *p_cmd_st);

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
