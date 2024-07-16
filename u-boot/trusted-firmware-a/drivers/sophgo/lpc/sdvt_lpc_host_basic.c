#ifndef SDVT_LPC_HOST_BASIC_C
#define SDVT_LPC_HOST_BASIC_C
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
// File Name      : sdvt_lpc_host_basic.c
// Project        : LPC IIP
// Date Created   : 06-29-2021
// Description    : This is simple LPC Master driver
// Generator      : IIP Compiler Version 1.1
//0---------------------------------------------------------------------------------------------------

#include <platform_def.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <mmio.h>
#include <drivers/sophgo/sdvt_lpc_host_defines.h>
#include <drivers/sophgo/sdvt_lpc_host_basic.h>

void write_reg(uint8_t    p_addr_8b, uint32_t p_data_32b)
{
	mmio_write_32(LPC_BASE + p_addr_8b, p_data_32b);
}

uint32_t read_reg(uint8_t    p_addr_8b)
{
	return mmio_read_32(LPC_BASE + p_addr_8b);
}

//0---------------------------------------------------------------------------------------------------
// init_chip :This method is used to initialize the chip
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//0---------------------------------------------------------------------------------------------------
void init_chip(struct sdvt_lpc_host_config *p_config_st)
{
	uint32_t                m_data_32b; // Register value to write
	//1-------------------------------------------------------------------------------------------------
	// Write the control register
	//1-------------------------------------------------------------------------------------------------
	write_control_reg(p_config_st);
	//1-------------------------------------------------------------------------------------------------
	// Enable all the interrupt
	//1-------------------------------------------------------------------------------------------------
	m_data_32b = p_config_st->irq_enable_18b;
	write_reg(SDVT_LPC_HOST_IRQ_ENABLE, m_data_32b);
}

//0---------------------------------------------------------------------------------------------------
// send_command :This method is used for sending command
//0---------------------------------------------------------------------------------------------------
//              p_cmd_st :Pointer to command object
//            p_addr_32b :Address to send
//            p_data_32b :Data to send
//0---------------------------------------------------------------------------------------------------
void send_command(struct sdvt_lpc_host_command *p_cmd_st, uint32_t p_addr_32b, uint32_t p_data_32b)
{
	uint32_t                m_data_32b; // Register value to write
	//1-------------------------------------------------------------------------------------------------
	// Construct the command memory data
	//1-------------------------------------------------------------------------------------------------
	m_data_32b = 1;
	m_data_32b = m_data_32b | (p_cmd_st->cmd_type_3b   << 2);
	m_data_32b = m_data_32b | (p_cmd_st->dir_b         << 5);
	m_data_32b = m_data_32b | (p_cmd_st->chan_idsel_3b << 8);
	m_data_32b = m_data_32b | (p_cmd_st->size_2b       << 11);
	m_data_32b = m_data_32b | (p_cmd_st->tc_b          << 13);
	m_data_32b = m_data_32b | (p_cmd_st->signal_b      << 14);
	m_data_32b = m_data_32b | (p_cmd_st->msize_4b      << 15);
	m_data_32b = m_data_32b | (p_cmd_st->dma_rd_more_b << 19);
	//1-------------------------------------------------------------------------------------------------
	// Program the command register
	//1-------------------------------------------------------------------------------------------------
	write_reg(SDVT_LPC_HOST_COMMAND, m_data_32b);
	m_data_32b = p_addr_32b;
	//1-------------------------------------------------------------------------------------------------
	// Program the command register
	//1-------------------------------------------------------------------------------------------------
	write_reg(SDVT_LPC_HOST_IDSEL_MADDR, m_data_32b);
	//1-------------------------------------------------------------------------------------------------
	// This is read command
	//1-------------------------------------------------------------------------------------------------
	if (((p_cmd_st->cmd_type_3b == SDVT_LPC_HOST_IO || p_cmd_st->cmd_type_3b == SDVT_LPC_HOST_MEMORY) &&
	     (p_cmd_st->dir_b == SDVT_LPC_HOST_WRITE))) {
		m_data_32b = p_data_32b;
		//2-----------------------------------------------------------------------------------------------
		// Program the command register
		//2-----------------------------------------------------------------------------------------------
		write_reg(SDVT_LPC_HOST_WR_FIFO, m_data_32b);
	}
	//1-------------------------------------------------------------------------------------------------
	// Wait for command to complete
	//1-------------------------------------------------------------------------------------------------
	wait_command_done();
}

//0---------------------------------------------------------------------------------------------------
// write_control_reg :This method is used to write control register
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//0---------------------------------------------------------------------------------------------------
void write_control_reg(struct sdvt_lpc_host_config *p_config_st)
{
	uint32_t                m_data_32b; // Register value to write

	m_data_32b = 0;
	m_data_32b = m_data_32b | (p_config_st->ctrl_enable_b);
	m_data_32b = m_data_32b | (p_config_st->ctrl_sync_timeout_b  << 1);
	m_data_32b = m_data_32b | (p_config_st->ctrl_lframe_time_b   << 2);
	m_data_32b = m_data_32b | (p_config_st->ctrl_lframe_time_b   << 3);
	m_data_32b = m_data_32b | (p_config_st->ctrl_prescaler_16b   << 4);
	m_data_32b = m_data_32b | (p_config_st->ctrl_ifg_8b          << 20);
	m_data_32b = m_data_32b | (p_config_st->ctrl_abort_width_8b  << 28);
	write_reg(SDVT_LPC_HOST_CONTROL, m_data_32b);
}

//0---------------------------------------------------------------------------------------------------
// enable_chip :This method is used to enable/disable chip
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//            p_enable_b :1 means enable, 0 means disable
//0---------------------------------------------------------------------------------------------------
void enable_chip(struct sdvt_lpc_host_config *p_config_st, uint8_t p_enable_b)
{
	p_config_st->ctrl_enable_b = p_enable_b;
	write_control_reg(p_config_st);
}

//0---------------------------------------------------------------------------------------------------
// mask_irq :This method is used to mask the IRQ
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//            p_mask_18b :Interrupts to mask
//0---------------------------------------------------------------------------------------------------
void mask_irq(struct sdvt_lpc_host_config *p_config_st, uint32_t p_mask_18b)
{
	uint32_t                m_new_mask_18b; // New register mask

	m_new_mask_18b = read_reg(SDVT_LPC_HOST_IRQ_ENABLE) & ~p_mask_18b;
	p_config_st->irq_enable_18b = m_new_mask_18b;
	write_reg(SDVT_LPC_HOST_IRQ_ENABLE, m_new_mask_18b);
}

//0---------------------------------------------------------------------------------------------------
// unmask_irq :This method is used to unmask the IRQ
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//            p_mask_18b :Interrupts to mask
//0---------------------------------------------------------------------------------------------------
void unmask_irq(struct sdvt_lpc_host_config *p_config_st, uint32_t p_mask_18b)
{
	uint32_t                m_new_mask_18b; // New register mask

	m_new_mask_18b = read_reg(SDVT_LPC_HOST_IRQ_ENABLE) | p_mask_18b;
	p_config_st->irq_enable_18b = m_new_mask_18b;
	write_reg(SDVT_LPC_HOST_IRQ_ENABLE, m_new_mask_18b);
}

//0---------------------------------------------------------------------------------------------------
// reset_chip :This method is used to reset the chip
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//0---------------------------------------------------------------------------------------------------
void reset_chip(struct sdvt_lpc_host_config *p_config_st)
{
	enable_chip(p_config_st, 0);
	mask_irq(p_config_st, 0xFFFFFFFF);
	enable_chip(p_config_st, 1);
}

//0---------------------------------------------------------------------------------------------------
// wait_command_done :This method is used for waiting for completion of request
//0---------------------------------------------------------------------------------------------------
//             parameter :No parameter
//0---------------------------------------------------------------------------------------------------
void wait_command_done(void)
{
	uint32_t                m_data_32b; // Command control register

	m_data_32b   = read_reg(SDVT_LPC_HOST_COMMAND);
	m_data_32b   = ((m_data_32b & 0x00000001) == 0) ? 1 : 0;
	//1-------------------------------------------------------------------------------------------------
	// Command is pending
	//1-------------------------------------------------------------------------------------------------
	while (m_data_32b == 0) {
		m_data_32b = read_reg(SDVT_LPC_HOST_COMMAND);
		m_data_32b = ((m_data_32b & 0x00000001) == 0) ? 1 : 0;
	}
}

//0---------------------------------------------------------------------------------------------------
// irq_handler :This method is used to handle the interrupts
//0---------------------------------------------------------------------------------------------------
//              p_cmd_st :Pointer to command object
//0---------------------------------------------------------------------------------------------------
void irq_handler (struct sdvt_lpc_host_command *p_cmd_st)
{
	uint32_t                m_rd_status_18b; // Status 1 reg

	m_rd_status_18b = read_reg(SDVT_LPC_HOST_IRQ_STATUS);
	write_reg(SDVT_LPC_HOST_IRQ_STATUS, m_rd_status_18b);
	p_cmd_st->irq_18b = m_rd_status_18b;
}

//0---------------------------------------------------------------------------------------------------
// print_config :This method is used to print all config registers
//0---------------------------------------------------------------------------------------------------
//           p_config_st :Pointer to config object
//0---------------------------------------------------------------------------------------------------
void print_config(struct sdvt_lpc_host_config *p_config_st)
{
	printf("INFO : %s :: ENABLE                  :: 0x%x\n", __func__,
	       p_config_st->ctrl_enable_b);
	printf("INFO : %s :: SYNC_TIMEOUT_ENABLE     :: 0x%x\n", __func__,
	       p_config_st->ctrl_sync_timeout_b);
	printf("INFO : %s :: LFRAME_TIMING           :: 0x%x\n", __func__,
	       p_config_st->ctrl_lframe_time_b);
	printf("INFO : %s :: PRESCALER               :: 0x%x\n", __func__,
	       p_config_st->ctrl_prescaler_16b);
	printf("INFO : %s :: INTER_FRAME_GAP         :: 0x%x\n", __func__,
	       p_config_st->ctrl_ifg_8b);
	printf("INFO : %s :: ABORT_WIDTH             :: 0x%x\n", __func__,
	       p_config_st->ctrl_abort_width_8b);
	printf("INFO : %s :: IRQ_ENABLE              :: 0x%x\n", __func__,
	       p_config_st->irq_enable_18b);
}

//0---------------------------------------------------------------------------------------------------
// print_command :This method is used to print command being sent
//0---------------------------------------------------------------------------------------------------
//              p_mode_i :0, print command, 1 print status also
//              p_cmd_st :Pointer to command object
//0---------------------------------------------------------------------------------------------------
void print_command(int p_mode_i, struct sdvt_lpc_host_command *p_cmd_st)
{
	printf("INFO : %s :: CMD_TYPE          :: 0x%x\n", __func__, p_cmd_st->cmd_type_3b);
	printf("INFO : %s :: CMD_DIR           :: 0x%x\n", __func__, p_cmd_st->dir_b);
	printf("INFO : %s :: CHANNEL_IDSEL     :: 0x%x\n", __func__, p_cmd_st->chan_idsel_3b);
	printf("INFO : %s :: SIZE              :: 0x%x\n", __func__, p_cmd_st->size_2b);
	printf("INFO : %s :: TC_BIT            :: 0x%x\n", __func__, p_cmd_st->tc_b);
	printf("INFO : %s :: SIGNAL_VALUE      :: 0x%x\n", __func__, p_cmd_st->signal_b);
	printf("INFO : %s :: MSIZE             :: 0x%x\n", __func__, p_cmd_st->msize_4b);
	printf("INFO : %s :: DMA_READ_MORE     :: 0x%x\n", __func__, p_cmd_st->dma_rd_more_b);
}

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
