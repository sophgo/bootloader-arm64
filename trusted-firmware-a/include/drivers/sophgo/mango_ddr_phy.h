#define    DENALI_PHY_0_DATA    0x0
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_0_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_0_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_1_DATA    0x4
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_0_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2_DATA    0x8
    #define    PHY_CLK_BYPASS_OVERRIDE_0_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_0_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_3_DATA    0xc
    #define    PHY_SW_WRDQ3_SHIFT_0_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_0_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_0_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_0_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_4_DATA    0x10
    #define    PHY_SW_WRDQ7_SHIFT_0_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_0_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_0_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_0_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_5_DATA    0x14
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_0_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_0_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_0_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_0_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_6_DATA    0x18
    #define    PHY_LPBK_CONTROL_0_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_0_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_0_RW_0_2    0x3    //0x00
#define    DENALI_PHY_7_DATA    0x1c
    #define    PHY_GATE_DELAY_COMP_DISABLE_0_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_0_RW_0_1    0x1    //0x01
#define    DENALI_PHY_8_DATA    0x20
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_9_DATA    0x24
    #define    PHY_AUTO_TIMING_MARGIN_OBS_0_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_10_DATA    0x28
    #define    PHY_PRBS_PATTERN_START_0_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_0_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_0_RW_0_1    0x1    //0x01
#define    DENALI_PHY_11_DATA    0x2c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_0_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_0_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_0_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_12_DATA    0x30
    #define    PHY_X4_VREF_TRAIN_OBS_0_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_0_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_0_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_13_DATA    0x34
    #define    SC_PHY_SNAP_OBS_REGS_0_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_0_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_14_DATA    0x38
    #define    PHY_DFI40_POLARITY_0_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_0_RW_0_3    0x7    //0x02
#define    DENALI_PHY_15_DATA    0x3c
    #define    PHY_RDLVL_PATT8_0_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_16_DATA    0x40
    #define    PHY_RDLVL_PATT9_0_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_17_DATA    0x44
    #define    PHY_RDLVL_PATT10_0_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_18_DATA    0x48
    #define    PHY_RDLVL_PATT11_0_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_19_DATA    0x4c
    #define    PHY_RDLVL_PATT12_0_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_20_DATA    0x50
    #define    PHY_RDLVL_PATT13_0_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_21_DATA    0x54
    #define    PHY_RDLVL_PATT14_0_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_22_DATA    0x58
    #define    PHY_RDLVL_PATT15_0_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_23_DATA    0x5c
    #define    PHY_RDLVL_PATT0_3_MASK_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_24_DATA    0x60
    #define    PHY_RDLVL_PATT8_11_MASK_0_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_25_DATA    0x64
    #define    PHY_RDLVL_PATT12_15_MASK_0_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_26_DATA    0x68
    #define    PHY_RDDQ_ENC_OBS_SELECT_0_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_0_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_0_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_0_RW_0_3    0x7    //0x00
#define    DENALI_PHY_27_DATA    0x6c
    #define    PHY_FIFO_PTR_OBS_SELECT_0_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_0_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_0_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_0_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_28_DATA    0x70
    #define    PHY_WRLVL_CAPTURE_CNT_0_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_0_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_0_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_0_RW_0_1    0x1    //0x00
#define    DENALI_PHY_29_DATA    0x74
    #define    PHY_GTLVL_UPDT_WAIT_CNT_0_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_0_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_0_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_0_RW_0_4    0xf    //0x08
#define    DENALI_PHY_30_DATA    0x78
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_0_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_0_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_0_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_0_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_31_DATA    0x7c
    #define    PHY_RDLVL_DATA_SWIZZLE_0_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_0_RW_0_8    0xff    //0x00
#define    DENALI_PHY_32_DATA    0x80
    #define    PHY_WDQLVL_PATT_0_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_0_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_0_RW_0_8    0xff    //0x20
#define    DENALI_PHY_33_DATA    0x84
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_0_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_0_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_0_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_34_DATA    0x88
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_0_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_0_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_0_RW_0_8    0xff    //0x20
#define    DENALI_PHY_35_DATA    0x8c
    #define    PHY_WDQLVL_DATADM_MASK_0_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_36_DATA    0x90
    #define    PHY_USER_PATT0_0_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_37_DATA    0x94
    #define    PHY_USER_PATT1_0_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_38_DATA    0x98
    #define    PHY_USER_PATT2_0_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_39_DATA    0x9c
    #define    PHY_USER_PATT3_0_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_40_DATA    0xa0
    #define    PHY_NTP_MULT_TRAIN_0_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_0_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_41_DATA    0xa4
    #define    PHY_NTP_PERIOD_THRESHOLD_0_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_0_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_42_DATA    0xa8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_0_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_0_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_43_DATA    0xac
    #define    PHY_FIFO_PTR_OBS_0_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_0_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_44_DATA    0xb0
    #define    PHY_LPBK_RESULT_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_45_DATA    0xb4
    #define    PHY_MASTER_DLY_LOCK_OBS_0_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_0_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_46_DATA    0xb8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_0_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_0_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_0_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_0_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_47_DATA    0xbc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_0_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_0_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_0_RD_0_8    0xff    //0x00
#define    DENALI_PHY_48_DATA    0xc0
    #define    PHY_WR_SHIFT_OBS_0_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_0_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_0_RD_0_8    0xff    //0x00
#define    DENALI_PHY_49_DATA    0xc4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_0_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_0_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_50_DATA    0xc8
    #define    PHY_WRLVL_STATUS_OBS_0_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_51_DATA    0xcc
    #define    PHY_WRLVL_ERROR_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_52_DATA    0xd0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_0_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_0_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_53_DATA    0xd4
    #define    PHY_GTLVL_STATUS_OBS_0_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_54_DATA    0xd8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_0_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_0_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_55_DATA    0xdc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_0_RD_0_2    0x3    //0x00
#define    DENALI_PHY_56_DATA    0xe0
    #define    PHY_RDLVL_STATUS_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_57_DATA    0xe4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_0_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_0_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_58_DATA    0xe8
    #define    PHY_WDQLVL_STATUS_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_59_DATA    0xec
    #define    PHY_DQS_RATIO_X8_0_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_0_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_0_RW_0_4    0xf    //0x00
#define    DENALI_PHY_60_DATA    0xf0
    #define    PHY_DDL_MODE_0_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_61_DATA    0xf4
    #define    PHY_DDL_MASK_0_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_62_DATA    0xf8
    #define    PHY_DDL_TEST_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_63_DATA    0xfc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_64_DATA    0x100
    #define    PHY_RX_CAL_DQS_0_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_0_RW_0_8    0xff    //0x04
#define    DENALI_PHY_65_DATA    0x104
    #define    PHY_RX_CAL_X4_FDBK_0_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_0_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_66_DATA    0x108
    #define    PHY_STATIC_TOG_DISABLE_0_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_0_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_0_RW_0_1    0x1    //0x01
#define    DENALI_PHY_67_DATA    0x10c
    #define    PHY_DFE_EN_0_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_0_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_0_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_0_RW_0_1    0x1    //0x01
#define    DENALI_PHY_68_DATA    0x110
    #define    PHY_DATA_DC_ADJUST_START_0_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_0_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_0_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_0_RW_0_8    0xff    //0x08
#define    DENALI_PHY_69_DATA    0x114
    #define    PHY_DATA_DC_CAL_POLARITY_0_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_0_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_0_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_0_RW_0_8    0xff    //0x10
#define    DENALI_PHY_70_DATA    0x118
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_0_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_0_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_0_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_0_RW_0_1    0x1    //0x00
#define    DENALI_PHY_71_DATA    0x11c
    #define    PHY_SLICE_PWR_RDC_DISABLE_0_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_0_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_0_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_72_DATA    0x120
    #define    PHY_DQS_TSEL_ENABLE_0_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_0_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_0_RW_0_3    0x7    //0x01
#define    DENALI_PHY_73_DATA    0x124
    #define    PHY_VREF_INITIAL_START_POINT_0_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_0_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_0_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_74_DATA    0x128
    #define    PHY_NTP_WDQ_STEP_SIZE_0_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_0_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_0_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_0_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_75_DATA    0x12c
    #define    PHY_NTP_WDQ_STOP_0_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_0_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_76_DATA    0x130
    #define    PHY_FAST_LVL_EN_0_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_0_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_0_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_77_DATA    0x134
    #define    PHY_PAD_RX_DCD_2_0_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_0_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_0_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_0_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_78_DATA    0x138
    #define    PHY_PAD_RX_DCD_6_0_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_0_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_0_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_0_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_79_DATA    0x13c
    #define    PHY_PAD_DQS_RX_DCD_0_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_0_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_0_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_80_DATA    0x140
    #define    PHY_PAD_DSLICE_IO_CFG_0_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_81_DATA    0x144
    #define    PHY_RDDQ1_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_82_DATA    0x148
    #define    PHY_RDDQ3_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_83_DATA    0x14c
    #define    PHY_RDDQ5_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_84_DATA    0x150
    #define    PHY_RDDQ7_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_85_DATA    0x154
    #define    PHY_RX_CAL_ALL_DLY_0_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_0_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_86_DATA    0x158
    #define    PHY_RX_OFF_FIRST_STEP_0_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_0_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_0_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_0_RW_0_8    0xff    //0x03
#define    DENALI_PHY_87_DATA    0x15c
    #define    PHY_DATA_DC_CAL_CLK_SEL_0_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_0_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_0_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_0_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_88_DATA    0x160
    #define    PHY_DQS_OE_TIMING_0_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_0_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_0_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_0_RW_0_8    0xff    //0x42
#define    DENALI_PHY_89_DATA    0x164
    #define    PHY_DQS_TSEL_WR_TIMING_0_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_0_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_0_RW_0_4    0xf    //0x00
#define    DENALI_PHY_90_DATA    0x168
    #define    PHY_PAD_VREF_CTRL_DQ_0_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_0_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_91_DATA    0x16c
    #define    PHY_DQ_IE_TIMING_0_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_0_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_0_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_92_DATA    0x170
    #define    PHY_DBI_MODE_0_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_0_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_0_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_0_RW_0_8    0xff    //0x80
#define    DENALI_PHY_93_DATA    0x174
    #define    PHY_RDDATA_EN_TSEL_DLY_0_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_0_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_0_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_0_RW_0_1    0x1    //0x00
#define    DENALI_PHY_94_DATA    0x178
    #define    PHY_MASTER_DELAY_STEP_0_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_0_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_0_RW_0_4    0xf    //0x00
#define    DENALI_PHY_95_DATA    0x17c
    #define    PHY_WRLVL_DLY_STEP_0_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_0_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_0_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_0_RW_0_8    0xff    //0x42
#define    DENALI_PHY_96_DATA    0x180
    #define    PHY_GTLVL_RESP_WAIT_CNT_0_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_0_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_0_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_0_RW_0_4    0xf    //0x01
#define    DENALI_PHY_97_DATA    0x184
    #define    PHY_GTLVL_FINAL_STEP_0_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_0_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_98_DATA    0x188
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_0_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_0_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_0_RW_0_8    0xff    //0x20
#define    DENALI_PHY_99_DATA    0x18c
    #define    PHY_X4_DQ_IE_TIMING_0_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_0_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_0_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_0_RW_0_8    0xff    //0x42
#define    DENALI_PHY_100_DATA    0x190
    #define    PHY_X4_DQS_IE_TIMING_0_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_0_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_0_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_0_RW_0_8    0xff    //0x51
#define    DENALI_PHY_101_DATA    0x194
    #define    PHY_RDLVL_DLY_STEP_0_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_0_RW_0_4    0xf    //0x06
#define    DENALI_PHY_102_DATA    0x198
    #define    PHY_RDLVL_MAX_EDGE_0_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_103_DATA    0x19c
    #define    PHY_DATA_DC_INIT_DISABLE_0_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_0_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_0_RW_0_2    0x3    //0x00
#define    DENALI_PHY_104_DATA    0x1a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_0_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_105_DATA    0x1a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_0_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_0_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_0_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_0_RW_0_1    0x1    //0x01
#define    DENALI_PHY_106_DATA    0x1a8
    #define    PHY_RDDATA_EN_DLY_0_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_0_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_107_DATA    0x1ac
    #define    PHY_DQ_DM_SWIZZLE0_0_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_108_DATA    0x1b0
    #define    PHY_DQ_DM_SWIZZLE1_0_RW_0_4    0xf    //0x08
#define    DENALI_PHY_109_DATA    0x1b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_0_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_0_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_110_DATA    0x1b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_0_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_0_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_111_DATA    0x1bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_0_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_0_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_112_DATA    0x1c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_0_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_0_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_113_DATA    0x1c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_0_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_114_DATA    0x1c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_0_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_0_RW_0_2    0x3    //0x00
#define    DENALI_PHY_115_DATA    0x1cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_116_DATA    0x1d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_117_DATA    0x1d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_118_DATA    0x1d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_119_DATA    0x1dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_120_DATA    0x1e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_121_DATA    0x1e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_122_DATA    0x1e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_123_DATA    0x1ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_124_DATA    0x1f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_125_DATA    0x1f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_126_DATA    0x1f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_127_DATA    0x1fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_128_DATA    0x200
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_129_DATA    0x204
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_130_DATA    0x208
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_131_DATA    0x20c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_132_DATA    0x210
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_133_DATA    0x214
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_0_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_0_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_0_RW_0_4    0xf    //0x02
#define    DENALI_PHY_134_DATA    0x218
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_0_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_135_DATA    0x21c
    #define    PHY_GTLVL_LAT_ADJ_START_0_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_136_DATA    0x220
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_0_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_0_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_137_DATA    0x224
    #define    PHY_X4_NTP_PASS_0_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_0_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_0_RW_0_4    0xf    //0x08
#define    DENALI_PHY_138_DATA    0x228
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_0_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_139_DATA    0x22c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_0_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_0_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_140_DATA    0x230
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_0_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_0_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_141_DATA    0x234
    #define    PHY_X4_GTLVL_LAT_ADJ_START_0_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_0_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_0_RW_0_1    0x1    //0x00
#define    DENALI_PHY_142_DATA    0x238
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_0_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_143_DATA    0x23c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_0_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_0_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_0_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_0_RW_0_8    0xff    //0x20
#define    DENALI_PHY_144_DATA    0x240
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_0_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_0_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_0_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_0_RW_0_8    0xff    //0x20
#define    DENALI_PHY_145_DATA    0x244
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_0_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_0_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_0_RW_0_8    0xff    //0x20
#define    DENALI_PHY_146_DATA    0x248
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_0_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_0_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_0_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_147_DATA    0x24c
    #define    PHY_X4_DQS_FFE_0_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_0_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_0_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_0_RW_0_2    0x3    //0x00
#define    DENALI_PHY_148_DATA    0x250
    #define    PHY_RX_CAL_DQ0_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_149_DATA    0x254
    #define    PHY_RX_CAL_DQ1_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_150_DATA    0x258
    #define    PHY_RX_CAL_DQ2_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_151_DATA    0x25c
    #define    PHY_RX_CAL_DQ3_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_152_DATA    0x260
    #define    PHY_RX_CAL_DQ4_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_153_DATA    0x264
    #define    PHY_RX_CAL_DQ5_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_154_DATA    0x268
    #define    PHY_RX_CAL_DQ6_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_155_DATA    0x26c
    #define    PHY_RX_CAL_DQ7_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_156_DATA    0x270
    #define    PHY_RX_CAL_DM_0_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_157_DATA    0x274
#define    DENALI_PHY_158_DATA    0x278
#define    DENALI_PHY_159_DATA    0x27c
#define    DENALI_PHY_160_DATA    0x280
#define    DENALI_PHY_161_DATA    0x284
#define    DENALI_PHY_162_DATA    0x288
#define    DENALI_PHY_163_DATA    0x28c
#define    DENALI_PHY_164_DATA    0x290
#define    DENALI_PHY_165_DATA    0x294
#define    DENALI_PHY_166_DATA    0x298
#define    DENALI_PHY_167_DATA    0x29c
#define    DENALI_PHY_168_DATA    0x2a0
#define    DENALI_PHY_169_DATA    0x2a4
#define    DENALI_PHY_170_DATA    0x2a8
#define    DENALI_PHY_171_DATA    0x2ac
#define    DENALI_PHY_172_DATA    0x2b0
#define    DENALI_PHY_173_DATA    0x2b4
#define    DENALI_PHY_174_DATA    0x2b8
#define    DENALI_PHY_175_DATA    0x2bc
#define    DENALI_PHY_176_DATA    0x2c0
#define    DENALI_PHY_177_DATA    0x2c4
#define    DENALI_PHY_178_DATA    0x2c8
#define    DENALI_PHY_179_DATA    0x2cc
#define    DENALI_PHY_180_DATA    0x2d0
#define    DENALI_PHY_181_DATA    0x2d4
#define    DENALI_PHY_182_DATA    0x2d8
#define    DENALI_PHY_183_DATA    0x2dc
#define    DENALI_PHY_184_DATA    0x2e0
#define    DENALI_PHY_185_DATA    0x2e4
#define    DENALI_PHY_186_DATA    0x2e8
#define    DENALI_PHY_187_DATA    0x2ec
#define    DENALI_PHY_188_DATA    0x2f0
#define    DENALI_PHY_189_DATA    0x2f4
#define    DENALI_PHY_190_DATA    0x2f8
#define    DENALI_PHY_191_DATA    0x2fc
#define    DENALI_PHY_192_DATA    0x300
#define    DENALI_PHY_193_DATA    0x304
#define    DENALI_PHY_194_DATA    0x308
#define    DENALI_PHY_195_DATA    0x30c
#define    DENALI_PHY_196_DATA    0x310
#define    DENALI_PHY_197_DATA    0x314
#define    DENALI_PHY_198_DATA    0x318
#define    DENALI_PHY_199_DATA    0x31c
#define    DENALI_PHY_200_DATA    0x320
#define    DENALI_PHY_201_DATA    0x324
#define    DENALI_PHY_202_DATA    0x328
#define    DENALI_PHY_203_DATA    0x32c
#define    DENALI_PHY_204_DATA    0x330
#define    DENALI_PHY_205_DATA    0x334
#define    DENALI_PHY_206_DATA    0x338
#define    DENALI_PHY_207_DATA    0x33c
#define    DENALI_PHY_208_DATA    0x340
#define    DENALI_PHY_209_DATA    0x344
#define    DENALI_PHY_210_DATA    0x348
#define    DENALI_PHY_211_DATA    0x34c
#define    DENALI_PHY_212_DATA    0x350
#define    DENALI_PHY_213_DATA    0x354
#define    DENALI_PHY_214_DATA    0x358
#define    DENALI_PHY_215_DATA    0x35c
#define    DENALI_PHY_216_DATA    0x360
#define    DENALI_PHY_217_DATA    0x364
#define    DENALI_PHY_218_DATA    0x368
#define    DENALI_PHY_219_DATA    0x36c
#define    DENALI_PHY_220_DATA    0x370
#define    DENALI_PHY_221_DATA    0x374
#define    DENALI_PHY_222_DATA    0x378
#define    DENALI_PHY_223_DATA    0x37c
#define    DENALI_PHY_224_DATA    0x380
#define    DENALI_PHY_225_DATA    0x384
#define    DENALI_PHY_226_DATA    0x388
#define    DENALI_PHY_227_DATA    0x38c
#define    DENALI_PHY_228_DATA    0x390
#define    DENALI_PHY_229_DATA    0x394
#define    DENALI_PHY_230_DATA    0x398
#define    DENALI_PHY_231_DATA    0x39c
#define    DENALI_PHY_232_DATA    0x3a0
#define    DENALI_PHY_233_DATA    0x3a4
#define    DENALI_PHY_234_DATA    0x3a8
#define    DENALI_PHY_235_DATA    0x3ac
#define    DENALI_PHY_236_DATA    0x3b0
#define    DENALI_PHY_237_DATA    0x3b4
#define    DENALI_PHY_238_DATA    0x3b8
#define    DENALI_PHY_239_DATA    0x3bc
#define    DENALI_PHY_240_DATA    0x3c0
#define    DENALI_PHY_241_DATA    0x3c4
#define    DENALI_PHY_242_DATA    0x3c8
#define    DENALI_PHY_243_DATA    0x3cc
#define    DENALI_PHY_244_DATA    0x3d0
#define    DENALI_PHY_245_DATA    0x3d4
#define    DENALI_PHY_246_DATA    0x3d8
#define    DENALI_PHY_247_DATA    0x3dc
#define    DENALI_PHY_248_DATA    0x3e0
#define    DENALI_PHY_249_DATA    0x3e4
#define    DENALI_PHY_250_DATA    0x3e8
#define    DENALI_PHY_251_DATA    0x3ec
#define    DENALI_PHY_252_DATA    0x3f0
#define    DENALI_PHY_253_DATA    0x3f4
#define    DENALI_PHY_254_DATA    0x3f8
#define    DENALI_PHY_255_DATA    0x3fc
#define    DENALI_PHY_256_DATA    0x400
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_1_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_1_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_257_DATA    0x404
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_1_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_258_DATA    0x408
    #define    PHY_CLK_BYPASS_OVERRIDE_1_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_1_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_259_DATA    0x40c
    #define    PHY_SW_WRDQ3_SHIFT_1_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_1_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_1_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_1_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_260_DATA    0x410
    #define    PHY_SW_WRDQ7_SHIFT_1_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_1_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_1_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_1_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_261_DATA    0x414
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_1_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_1_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_1_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_1_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_262_DATA    0x418
    #define    PHY_LPBK_CONTROL_1_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_1_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_1_RW_0_2    0x3    //0x00
#define    DENALI_PHY_263_DATA    0x41c
    #define    PHY_GATE_DELAY_COMP_DISABLE_1_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_1_RW_0_1    0x1    //0x01
#define    DENALI_PHY_264_DATA    0x420
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_265_DATA    0x424
    #define    PHY_AUTO_TIMING_MARGIN_OBS_1_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_266_DATA    0x428
    #define    PHY_PRBS_PATTERN_START_1_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_1_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_1_RW_0_1    0x1    //0x01
#define    DENALI_PHY_267_DATA    0x42c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_1_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_1_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_1_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_268_DATA    0x430
    #define    PHY_X4_VREF_TRAIN_OBS_1_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_1_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_1_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_269_DATA    0x434
    #define    SC_PHY_SNAP_OBS_REGS_1_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_1_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_270_DATA    0x438
    #define    PHY_DFI40_POLARITY_1_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_1_RW_0_3    0x7    //0x02
#define    DENALI_PHY_271_DATA    0x43c
    #define    PHY_RDLVL_PATT8_1_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_272_DATA    0x440
    #define    PHY_RDLVL_PATT9_1_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_273_DATA    0x444
    #define    PHY_RDLVL_PATT10_1_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_274_DATA    0x448
    #define    PHY_RDLVL_PATT11_1_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_275_DATA    0x44c
    #define    PHY_RDLVL_PATT12_1_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_276_DATA    0x450
    #define    PHY_RDLVL_PATT13_1_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_277_DATA    0x454
    #define    PHY_RDLVL_PATT14_1_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_278_DATA    0x458
    #define    PHY_RDLVL_PATT15_1_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_279_DATA    0x45c
    #define    PHY_RDLVL_PATT0_3_MASK_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_280_DATA    0x460
    #define    PHY_RDLVL_PATT8_11_MASK_1_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_281_DATA    0x464
    #define    PHY_RDLVL_PATT12_15_MASK_1_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_282_DATA    0x468
    #define    PHY_RDDQ_ENC_OBS_SELECT_1_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_1_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_1_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_1_RW_0_3    0x7    //0x00
#define    DENALI_PHY_283_DATA    0x46c
    #define    PHY_FIFO_PTR_OBS_SELECT_1_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_1_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_1_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_1_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_284_DATA    0x470
    #define    PHY_WRLVL_CAPTURE_CNT_1_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_1_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_1_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_1_RW_0_1    0x1    //0x00
#define    DENALI_PHY_285_DATA    0x474
    #define    PHY_GTLVL_UPDT_WAIT_CNT_1_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_1_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_1_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_1_RW_0_4    0xf    //0x08
#define    DENALI_PHY_286_DATA    0x478
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_1_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_1_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_1_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_1_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_287_DATA    0x47c
    #define    PHY_RDLVL_DATA_SWIZZLE_1_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_1_RW_0_8    0xff    //0x00
#define    DENALI_PHY_288_DATA    0x480
    #define    PHY_WDQLVL_PATT_1_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_1_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_1_RW_0_8    0xff    //0x20
#define    DENALI_PHY_289_DATA    0x484
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_1_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_1_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_1_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_290_DATA    0x488
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_1_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_1_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_1_RW_0_8    0xff    //0x20
#define    DENALI_PHY_291_DATA    0x48c
    #define    PHY_WDQLVL_DATADM_MASK_1_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_292_DATA    0x490
    #define    PHY_USER_PATT0_1_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_293_DATA    0x494
    #define    PHY_USER_PATT1_1_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_294_DATA    0x498
    #define    PHY_USER_PATT2_1_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_295_DATA    0x49c
    #define    PHY_USER_PATT3_1_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_296_DATA    0x4a0
    #define    PHY_NTP_MULT_TRAIN_1_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_1_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_297_DATA    0x4a4
    #define    PHY_NTP_PERIOD_THRESHOLD_1_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_1_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_298_DATA    0x4a8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_1_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_1_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_299_DATA    0x4ac
    #define    PHY_FIFO_PTR_OBS_1_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_1_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_300_DATA    0x4b0
    #define    PHY_LPBK_RESULT_OBS_1_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_301_DATA    0x4b4
    #define    PHY_MASTER_DLY_LOCK_OBS_1_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_1_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_302_DATA    0x4b8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_1_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_1_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_1_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_1_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_303_DATA    0x4bc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_1_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_1_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_1_RD_0_8    0xff    //0x00
#define    DENALI_PHY_304_DATA    0x4c0
    #define    PHY_WR_SHIFT_OBS_1_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_1_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_1_RD_0_8    0xff    //0x00
#define    DENALI_PHY_305_DATA    0x4c4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_1_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_1_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_306_DATA    0x4c8
    #define    PHY_WRLVL_STATUS_OBS_1_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_307_DATA    0x4cc
    #define    PHY_WRLVL_ERROR_OBS_1_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_308_DATA    0x4d0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_1_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_1_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_309_DATA    0x4d4
    #define    PHY_GTLVL_STATUS_OBS_1_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_310_DATA    0x4d8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_1_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_1_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_311_DATA    0x4dc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_1_RD_0_2    0x3    //0x00
#define    DENALI_PHY_312_DATA    0x4e0
    #define    PHY_RDLVL_STATUS_OBS_1_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_313_DATA    0x4e4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_1_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_1_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_314_DATA    0x4e8
    #define    PHY_WDQLVL_STATUS_OBS_1_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_315_DATA    0x4ec
    #define    PHY_DQS_RATIO_X8_1_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_1_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_1_RW_0_4    0xf    //0x00
#define    DENALI_PHY_316_DATA    0x4f0
    #define    PHY_DDL_MODE_1_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_317_DATA    0x4f4
    #define    PHY_DDL_MASK_1_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_318_DATA    0x4f8
    #define    PHY_DDL_TEST_OBS_1_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_319_DATA    0x4fc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_1_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_320_DATA    0x500
    #define    PHY_RX_CAL_DQS_1_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_1_RW_0_8    0xff    //0x04
#define    DENALI_PHY_321_DATA    0x504
    #define    PHY_RX_CAL_X4_FDBK_1_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_1_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_322_DATA    0x508
    #define    PHY_STATIC_TOG_DISABLE_1_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_1_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_1_RW_0_1    0x1    //0x01
#define    DENALI_PHY_323_DATA    0x50c
    #define    PHY_DFE_EN_1_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_1_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_1_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_1_RW_0_1    0x1    //0x01
#define    DENALI_PHY_324_DATA    0x510
    #define    PHY_DATA_DC_ADJUST_START_1_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_1_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_1_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_1_RW_0_8    0xff    //0x08
#define    DENALI_PHY_325_DATA    0x514
    #define    PHY_DATA_DC_CAL_POLARITY_1_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_1_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_1_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_1_RW_0_8    0xff    //0x10
#define    DENALI_PHY_326_DATA    0x518
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_1_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_1_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_1_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_1_RW_0_1    0x1    //0x00
#define    DENALI_PHY_327_DATA    0x51c
    #define    PHY_SLICE_PWR_RDC_DISABLE_1_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_1_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_1_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_328_DATA    0x520
    #define    PHY_DQS_TSEL_ENABLE_1_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_1_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_1_RW_0_3    0x7    //0x01
#define    DENALI_PHY_329_DATA    0x524
    #define    PHY_VREF_INITIAL_START_POINT_1_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_1_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_1_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_330_DATA    0x528
    #define    PHY_NTP_WDQ_STEP_SIZE_1_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_1_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_1_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_1_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_331_DATA    0x52c
    #define    PHY_NTP_WDQ_STOP_1_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_1_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_332_DATA    0x530
    #define    PHY_FAST_LVL_EN_1_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_1_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_1_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_333_DATA    0x534
    #define    PHY_PAD_RX_DCD_2_1_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_1_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_1_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_1_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_334_DATA    0x538
    #define    PHY_PAD_RX_DCD_6_1_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_1_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_1_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_1_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_335_DATA    0x53c
    #define    PHY_PAD_DQS_RX_DCD_1_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_1_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_1_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_336_DATA    0x540
    #define    PHY_PAD_DSLICE_IO_CFG_1_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_337_DATA    0x544
    #define    PHY_RDDQ1_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_338_DATA    0x548
    #define    PHY_RDDQ3_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_339_DATA    0x54c
    #define    PHY_RDDQ5_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_340_DATA    0x550
    #define    PHY_RDDQ7_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_341_DATA    0x554
    #define    PHY_RX_CAL_ALL_DLY_1_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_1_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_342_DATA    0x558
    #define    PHY_RX_OFF_FIRST_STEP_1_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_1_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_1_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_1_RW_0_8    0xff    //0x03
#define    DENALI_PHY_343_DATA    0x55c
    #define    PHY_DATA_DC_CAL_CLK_SEL_1_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_1_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_1_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_1_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_344_DATA    0x560
    #define    PHY_DQS_OE_TIMING_1_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_1_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_1_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_1_RW_0_8    0xff    //0x42
#define    DENALI_PHY_345_DATA    0x564
    #define    PHY_DQS_TSEL_WR_TIMING_1_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_1_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_1_RW_0_4    0xf    //0x00
#define    DENALI_PHY_346_DATA    0x568
    #define    PHY_PAD_VREF_CTRL_DQ_1_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_1_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_347_DATA    0x56c
    #define    PHY_DQ_IE_TIMING_1_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_1_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_1_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_348_DATA    0x570
    #define    PHY_DBI_MODE_1_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_1_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_1_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_1_RW_0_8    0xff    //0x80
#define    DENALI_PHY_349_DATA    0x574
    #define    PHY_RDDATA_EN_TSEL_DLY_1_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_1_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_1_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_1_RW_0_1    0x1    //0x00
#define    DENALI_PHY_350_DATA    0x578
    #define    PHY_MASTER_DELAY_STEP_1_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_1_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_1_RW_0_4    0xf    //0x00
#define    DENALI_PHY_351_DATA    0x57c
    #define    PHY_WRLVL_DLY_STEP_1_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_1_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_1_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_1_RW_0_8    0xff    //0x42
#define    DENALI_PHY_352_DATA    0x580
    #define    PHY_GTLVL_RESP_WAIT_CNT_1_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_1_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_1_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_1_RW_0_4    0xf    //0x01
#define    DENALI_PHY_353_DATA    0x584
    #define    PHY_GTLVL_FINAL_STEP_1_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_1_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_354_DATA    0x588
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_1_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_1_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_1_RW_0_8    0xff    //0x20
#define    DENALI_PHY_355_DATA    0x58c
    #define    PHY_X4_DQ_IE_TIMING_1_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_1_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_1_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_1_RW_0_8    0xff    //0x42
#define    DENALI_PHY_356_DATA    0x590
    #define    PHY_X4_DQS_IE_TIMING_1_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_1_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_1_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_1_RW_0_8    0xff    //0x51
#define    DENALI_PHY_357_DATA    0x594
    #define    PHY_RDLVL_DLY_STEP_1_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_1_RW_0_4    0xf    //0x06
#define    DENALI_PHY_358_DATA    0x598
    #define    PHY_RDLVL_MAX_EDGE_1_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_359_DATA    0x59c
    #define    PHY_DATA_DC_INIT_DISABLE_1_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_1_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_1_RW_0_2    0x3    //0x00
#define    DENALI_PHY_360_DATA    0x5a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_1_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_361_DATA    0x5a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_1_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_1_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_1_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_1_RW_0_1    0x1    //0x01
#define    DENALI_PHY_362_DATA    0x5a8
    #define    PHY_RDDATA_EN_DLY_1_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_1_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_363_DATA    0x5ac
    #define    PHY_DQ_DM_SWIZZLE0_1_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_364_DATA    0x5b0
    #define    PHY_DQ_DM_SWIZZLE1_1_RW_0_4    0xf    //0x08
#define    DENALI_PHY_365_DATA    0x5b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_1_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_1_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_366_DATA    0x5b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_1_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_1_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_367_DATA    0x5bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_1_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_1_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_368_DATA    0x5c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_1_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_1_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_369_DATA    0x5c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_1_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_370_DATA    0x5c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_1_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_1_RW_0_2    0x3    //0x00
#define    DENALI_PHY_371_DATA    0x5cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_372_DATA    0x5d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_373_DATA    0x5d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_374_DATA    0x5d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_375_DATA    0x5dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_376_DATA    0x5e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_377_DATA    0x5e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_378_DATA    0x5e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_379_DATA    0x5ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_380_DATA    0x5f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_381_DATA    0x5f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_382_DATA    0x5f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_383_DATA    0x5fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_384_DATA    0x600
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_385_DATA    0x604
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_386_DATA    0x608
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_387_DATA    0x60c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_388_DATA    0x610
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_389_DATA    0x614
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_1_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_1_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_1_RW_0_4    0xf    //0x02
#define    DENALI_PHY_390_DATA    0x618
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_1_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_391_DATA    0x61c
    #define    PHY_GTLVL_LAT_ADJ_START_1_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_392_DATA    0x620
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_1_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_1_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_393_DATA    0x624
    #define    PHY_X4_NTP_PASS_1_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_1_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_1_RW_0_4    0xf    //0x08
#define    DENALI_PHY_394_DATA    0x628
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_1_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_395_DATA    0x62c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_1_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_1_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_396_DATA    0x630
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_1_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_1_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_397_DATA    0x634
    #define    PHY_X4_GTLVL_LAT_ADJ_START_1_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_1_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_1_RW_0_1    0x1    //0x00
#define    DENALI_PHY_398_DATA    0x638
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_1_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_399_DATA    0x63c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_1_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_1_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_1_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_1_RW_0_8    0xff    //0x20
#define    DENALI_PHY_400_DATA    0x640
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_1_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_1_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_1_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_1_RW_0_8    0xff    //0x20
#define    DENALI_PHY_401_DATA    0x644
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_1_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_1_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_1_RW_0_8    0xff    //0x20
#define    DENALI_PHY_402_DATA    0x648
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_1_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_1_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_1_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_403_DATA    0x64c
    #define    PHY_X4_DQS_FFE_1_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_1_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_1_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_1_RW_0_2    0x3    //0x00
#define    DENALI_PHY_404_DATA    0x650
    #define    PHY_RX_CAL_DQ0_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_405_DATA    0x654
    #define    PHY_RX_CAL_DQ1_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_406_DATA    0x658
    #define    PHY_RX_CAL_DQ2_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_407_DATA    0x65c
    #define    PHY_RX_CAL_DQ3_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_408_DATA    0x660
    #define    PHY_RX_CAL_DQ4_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_409_DATA    0x664
    #define    PHY_RX_CAL_DQ5_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_410_DATA    0x668
    #define    PHY_RX_CAL_DQ6_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_411_DATA    0x66c
    #define    PHY_RX_CAL_DQ7_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_412_DATA    0x670
    #define    PHY_RX_CAL_DM_1_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_413_DATA    0x674
#define    DENALI_PHY_414_DATA    0x678
#define    DENALI_PHY_415_DATA    0x67c
#define    DENALI_PHY_416_DATA    0x680
#define    DENALI_PHY_417_DATA    0x684
#define    DENALI_PHY_418_DATA    0x688
#define    DENALI_PHY_419_DATA    0x68c
#define    DENALI_PHY_420_DATA    0x690
#define    DENALI_PHY_421_DATA    0x694
#define    DENALI_PHY_422_DATA    0x698
#define    DENALI_PHY_423_DATA    0x69c
#define    DENALI_PHY_424_DATA    0x6a0
#define    DENALI_PHY_425_DATA    0x6a4
#define    DENALI_PHY_426_DATA    0x6a8
#define    DENALI_PHY_427_DATA    0x6ac
#define    DENALI_PHY_428_DATA    0x6b0
#define    DENALI_PHY_429_DATA    0x6b4
#define    DENALI_PHY_430_DATA    0x6b8
#define    DENALI_PHY_431_DATA    0x6bc
#define    DENALI_PHY_432_DATA    0x6c0
#define    DENALI_PHY_433_DATA    0x6c4
#define    DENALI_PHY_434_DATA    0x6c8
#define    DENALI_PHY_435_DATA    0x6cc
#define    DENALI_PHY_436_DATA    0x6d0
#define    DENALI_PHY_437_DATA    0x6d4
#define    DENALI_PHY_438_DATA    0x6d8
#define    DENALI_PHY_439_DATA    0x6dc
#define    DENALI_PHY_440_DATA    0x6e0
#define    DENALI_PHY_441_DATA    0x6e4
#define    DENALI_PHY_442_DATA    0x6e8
#define    DENALI_PHY_443_DATA    0x6ec
#define    DENALI_PHY_444_DATA    0x6f0
#define    DENALI_PHY_445_DATA    0x6f4
#define    DENALI_PHY_446_DATA    0x6f8
#define    DENALI_PHY_447_DATA    0x6fc
#define    DENALI_PHY_448_DATA    0x700
#define    DENALI_PHY_449_DATA    0x704
#define    DENALI_PHY_450_DATA    0x708
#define    DENALI_PHY_451_DATA    0x70c
#define    DENALI_PHY_452_DATA    0x710
#define    DENALI_PHY_453_DATA    0x714
#define    DENALI_PHY_454_DATA    0x718
#define    DENALI_PHY_455_DATA    0x71c
#define    DENALI_PHY_456_DATA    0x720
#define    DENALI_PHY_457_DATA    0x724
#define    DENALI_PHY_458_DATA    0x728
#define    DENALI_PHY_459_DATA    0x72c
#define    DENALI_PHY_460_DATA    0x730
#define    DENALI_PHY_461_DATA    0x734
#define    DENALI_PHY_462_DATA    0x738
#define    DENALI_PHY_463_DATA    0x73c
#define    DENALI_PHY_464_DATA    0x740
#define    DENALI_PHY_465_DATA    0x744
#define    DENALI_PHY_466_DATA    0x748
#define    DENALI_PHY_467_DATA    0x74c
#define    DENALI_PHY_468_DATA    0x750
#define    DENALI_PHY_469_DATA    0x754
#define    DENALI_PHY_470_DATA    0x758
#define    DENALI_PHY_471_DATA    0x75c
#define    DENALI_PHY_472_DATA    0x760
#define    DENALI_PHY_473_DATA    0x764
#define    DENALI_PHY_474_DATA    0x768
#define    DENALI_PHY_475_DATA    0x76c
#define    DENALI_PHY_476_DATA    0x770
#define    DENALI_PHY_477_DATA    0x774
#define    DENALI_PHY_478_DATA    0x778
#define    DENALI_PHY_479_DATA    0x77c
#define    DENALI_PHY_480_DATA    0x780
#define    DENALI_PHY_481_DATA    0x784
#define    DENALI_PHY_482_DATA    0x788
#define    DENALI_PHY_483_DATA    0x78c
#define    DENALI_PHY_484_DATA    0x790
#define    DENALI_PHY_485_DATA    0x794
#define    DENALI_PHY_486_DATA    0x798
#define    DENALI_PHY_487_DATA    0x79c
#define    DENALI_PHY_488_DATA    0x7a0
#define    DENALI_PHY_489_DATA    0x7a4
#define    DENALI_PHY_490_DATA    0x7a8
#define    DENALI_PHY_491_DATA    0x7ac
#define    DENALI_PHY_492_DATA    0x7b0
#define    DENALI_PHY_493_DATA    0x7b4
#define    DENALI_PHY_494_DATA    0x7b8
#define    DENALI_PHY_495_DATA    0x7bc
#define    DENALI_PHY_496_DATA    0x7c0
#define    DENALI_PHY_497_DATA    0x7c4
#define    DENALI_PHY_498_DATA    0x7c8
#define    DENALI_PHY_499_DATA    0x7cc
#define    DENALI_PHY_500_DATA    0x7d0
#define    DENALI_PHY_501_DATA    0x7d4
#define    DENALI_PHY_502_DATA    0x7d8
#define    DENALI_PHY_503_DATA    0x7dc
#define    DENALI_PHY_504_DATA    0x7e0
#define    DENALI_PHY_505_DATA    0x7e4
#define    DENALI_PHY_506_DATA    0x7e8
#define    DENALI_PHY_507_DATA    0x7ec
#define    DENALI_PHY_508_DATA    0x7f0
#define    DENALI_PHY_509_DATA    0x7f4
#define    DENALI_PHY_510_DATA    0x7f8
#define    DENALI_PHY_511_DATA    0x7fc
#define    DENALI_PHY_512_DATA    0x800
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_2_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_2_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_513_DATA    0x804
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_2_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_514_DATA    0x808
    #define    PHY_CLK_BYPASS_OVERRIDE_2_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_2_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_515_DATA    0x80c
    #define    PHY_SW_WRDQ3_SHIFT_2_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_2_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_2_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_2_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_516_DATA    0x810
    #define    PHY_SW_WRDQ7_SHIFT_2_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_2_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_2_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_2_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_517_DATA    0x814
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_2_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_2_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_2_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_2_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_518_DATA    0x818
    #define    PHY_LPBK_CONTROL_2_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_2_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_2_RW_0_2    0x3    //0x00
#define    DENALI_PHY_519_DATA    0x81c
    #define    PHY_GATE_DELAY_COMP_DISABLE_2_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_2_RW_0_1    0x1    //0x01
#define    DENALI_PHY_520_DATA    0x820
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_2_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_521_DATA    0x824
    #define    PHY_AUTO_TIMING_MARGIN_OBS_2_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_522_DATA    0x828
    #define    PHY_PRBS_PATTERN_START_2_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_2_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_2_RW_0_1    0x1    //0x01
#define    DENALI_PHY_523_DATA    0x82c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_2_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_2_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_2_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_524_DATA    0x830
    #define    PHY_X4_VREF_TRAIN_OBS_2_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_2_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_2_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_525_DATA    0x834
    #define    SC_PHY_SNAP_OBS_REGS_2_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_2_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_526_DATA    0x838
    #define    PHY_DFI40_POLARITY_2_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_2_RW_0_3    0x7    //0x02
#define    DENALI_PHY_527_DATA    0x83c
    #define    PHY_RDLVL_PATT8_2_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_528_DATA    0x840
    #define    PHY_RDLVL_PATT9_2_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_529_DATA    0x844
    #define    PHY_RDLVL_PATT10_2_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_530_DATA    0x848
    #define    PHY_RDLVL_PATT11_2_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_531_DATA    0x84c
    #define    PHY_RDLVL_PATT12_2_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_532_DATA    0x850
    #define    PHY_RDLVL_PATT13_2_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_533_DATA    0x854
    #define    PHY_RDLVL_PATT14_2_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_534_DATA    0x858
    #define    PHY_RDLVL_PATT15_2_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_535_DATA    0x85c
    #define    PHY_RDLVL_PATT0_3_MASK_2_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_536_DATA    0x860
    #define    PHY_RDLVL_PATT8_11_MASK_2_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_537_DATA    0x864
    #define    PHY_RDLVL_PATT12_15_MASK_2_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_538_DATA    0x868
    #define    PHY_RDDQ_ENC_OBS_SELECT_2_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_2_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_2_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_2_RW_0_3    0x7    //0x00
#define    DENALI_PHY_539_DATA    0x86c
    #define    PHY_FIFO_PTR_OBS_SELECT_2_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_2_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_2_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_2_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_540_DATA    0x870
    #define    PHY_WRLVL_CAPTURE_CNT_2_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_2_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_2_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_2_RW_0_1    0x1    //0x00
#define    DENALI_PHY_541_DATA    0x874
    #define    PHY_GTLVL_UPDT_WAIT_CNT_2_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_2_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_2_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_2_RW_0_4    0xf    //0x08
#define    DENALI_PHY_542_DATA    0x878
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_2_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_2_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_2_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_2_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_543_DATA    0x87c
    #define    PHY_RDLVL_DATA_SWIZZLE_2_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_2_RW_0_8    0xff    //0x00
#define    DENALI_PHY_544_DATA    0x880
    #define    PHY_WDQLVL_PATT_2_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_2_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_2_RW_0_8    0xff    //0x20
#define    DENALI_PHY_545_DATA    0x884
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_2_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_2_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_2_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_546_DATA    0x888
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_2_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_2_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_2_RW_0_8    0xff    //0x20
#define    DENALI_PHY_547_DATA    0x88c
    #define    PHY_WDQLVL_DATADM_MASK_2_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_548_DATA    0x890
    #define    PHY_USER_PATT0_2_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_549_DATA    0x894
    #define    PHY_USER_PATT1_2_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_550_DATA    0x898
    #define    PHY_USER_PATT2_2_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_551_DATA    0x89c
    #define    PHY_USER_PATT3_2_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_552_DATA    0x8a0
    #define    PHY_NTP_MULT_TRAIN_2_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_2_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_553_DATA    0x8a4
    #define    PHY_NTP_PERIOD_THRESHOLD_2_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_2_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_554_DATA    0x8a8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_2_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_2_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_555_DATA    0x8ac
    #define    PHY_FIFO_PTR_OBS_2_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_2_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_556_DATA    0x8b0
    #define    PHY_LPBK_RESULT_OBS_2_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_557_DATA    0x8b4
    #define    PHY_MASTER_DLY_LOCK_OBS_2_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_2_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_558_DATA    0x8b8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_2_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_2_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_2_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_2_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_559_DATA    0x8bc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_2_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_2_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_2_RD_0_8    0xff    //0x00
#define    DENALI_PHY_560_DATA    0x8c0
    #define    PHY_WR_SHIFT_OBS_2_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_2_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_2_RD_0_8    0xff    //0x00
#define    DENALI_PHY_561_DATA    0x8c4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_2_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_2_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_562_DATA    0x8c8
    #define    PHY_WRLVL_STATUS_OBS_2_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_563_DATA    0x8cc
    #define    PHY_WRLVL_ERROR_OBS_2_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_564_DATA    0x8d0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_2_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_2_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_565_DATA    0x8d4
    #define    PHY_GTLVL_STATUS_OBS_2_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_566_DATA    0x8d8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_2_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_2_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_567_DATA    0x8dc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_2_RD_0_2    0x3    //0x00
#define    DENALI_PHY_568_DATA    0x8e0
    #define    PHY_RDLVL_STATUS_OBS_2_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_569_DATA    0x8e4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_2_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_2_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_570_DATA    0x8e8
    #define    PHY_WDQLVL_STATUS_OBS_2_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_571_DATA    0x8ec
    #define    PHY_DQS_RATIO_X8_2_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_2_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_2_RW_0_4    0xf    //0x00
#define    DENALI_PHY_572_DATA    0x8f0
    #define    PHY_DDL_MODE_2_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_573_DATA    0x8f4
    #define    PHY_DDL_MASK_2_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_574_DATA    0x8f8
    #define    PHY_DDL_TEST_OBS_2_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_575_DATA    0x8fc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_2_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_576_DATA    0x900
    #define    PHY_RX_CAL_DQS_2_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_2_RW_0_8    0xff    //0x04
#define    DENALI_PHY_577_DATA    0x904
    #define    PHY_RX_CAL_X4_FDBK_2_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_2_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_578_DATA    0x908
    #define    PHY_STATIC_TOG_DISABLE_2_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_2_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_2_RW_0_1    0x1    //0x01
#define    DENALI_PHY_579_DATA    0x90c
    #define    PHY_DFE_EN_2_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_2_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_2_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_2_RW_0_1    0x1    //0x01
#define    DENALI_PHY_580_DATA    0x910
    #define    PHY_DATA_DC_ADJUST_START_2_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_2_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_2_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_2_RW_0_8    0xff    //0x08
#define    DENALI_PHY_581_DATA    0x914
    #define    PHY_DATA_DC_CAL_POLARITY_2_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_2_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_2_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_2_RW_0_8    0xff    //0x10
#define    DENALI_PHY_582_DATA    0x918
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_2_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_2_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_2_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_2_RW_0_1    0x1    //0x00
#define    DENALI_PHY_583_DATA    0x91c
    #define    PHY_SLICE_PWR_RDC_DISABLE_2_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_2_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_2_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_584_DATA    0x920
    #define    PHY_DQS_TSEL_ENABLE_2_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_2_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_2_RW_0_3    0x7    //0x01
#define    DENALI_PHY_585_DATA    0x924
    #define    PHY_VREF_INITIAL_START_POINT_2_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_2_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_2_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_586_DATA    0x928
    #define    PHY_NTP_WDQ_STEP_SIZE_2_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_2_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_2_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_2_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_587_DATA    0x92c
    #define    PHY_NTP_WDQ_STOP_2_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_2_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_588_DATA    0x930
    #define    PHY_FAST_LVL_EN_2_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_2_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_2_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_589_DATA    0x934
    #define    PHY_PAD_RX_DCD_2_2_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_2_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_2_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_2_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_590_DATA    0x938
    #define    PHY_PAD_RX_DCD_6_2_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_2_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_2_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_2_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_591_DATA    0x93c
    #define    PHY_PAD_DQS_RX_DCD_2_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_2_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_2_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_592_DATA    0x940
    #define    PHY_PAD_DSLICE_IO_CFG_2_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_593_DATA    0x944
    #define    PHY_RDDQ1_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_594_DATA    0x948
    #define    PHY_RDDQ3_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_595_DATA    0x94c
    #define    PHY_RDDQ5_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_596_DATA    0x950
    #define    PHY_RDDQ7_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_597_DATA    0x954
    #define    PHY_RX_CAL_ALL_DLY_2_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_2_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_598_DATA    0x958
    #define    PHY_RX_OFF_FIRST_STEP_2_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_2_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_2_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_2_RW_0_8    0xff    //0x03
#define    DENALI_PHY_599_DATA    0x95c
    #define    PHY_DATA_DC_CAL_CLK_SEL_2_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_2_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_2_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_2_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_600_DATA    0x960
    #define    PHY_DQS_OE_TIMING_2_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_2_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_2_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_2_RW_0_8    0xff    //0x42
#define    DENALI_PHY_601_DATA    0x964
    #define    PHY_DQS_TSEL_WR_TIMING_2_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_2_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_2_RW_0_4    0xf    //0x00
#define    DENALI_PHY_602_DATA    0x968
    #define    PHY_PAD_VREF_CTRL_DQ_2_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_2_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_603_DATA    0x96c
    #define    PHY_DQ_IE_TIMING_2_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_2_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_2_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_604_DATA    0x970
    #define    PHY_DBI_MODE_2_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_2_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_2_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_2_RW_0_8    0xff    //0x80
#define    DENALI_PHY_605_DATA    0x974
    #define    PHY_RDDATA_EN_TSEL_DLY_2_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_2_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_2_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_2_RW_0_1    0x1    //0x00
#define    DENALI_PHY_606_DATA    0x978
    #define    PHY_MASTER_DELAY_STEP_2_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_2_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_2_RW_0_4    0xf    //0x00
#define    DENALI_PHY_607_DATA    0x97c
    #define    PHY_WRLVL_DLY_STEP_2_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_2_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_2_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_2_RW_0_8    0xff    //0x42
#define    DENALI_PHY_608_DATA    0x980
    #define    PHY_GTLVL_RESP_WAIT_CNT_2_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_2_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_2_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_2_RW_0_4    0xf    //0x01
#define    DENALI_PHY_609_DATA    0x984
    #define    PHY_GTLVL_FINAL_STEP_2_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_2_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_610_DATA    0x988
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_2_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_2_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_2_RW_0_8    0xff    //0x20
#define    DENALI_PHY_611_DATA    0x98c
    #define    PHY_X4_DQ_IE_TIMING_2_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_2_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_2_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_2_RW_0_8    0xff    //0x42
#define    DENALI_PHY_612_DATA    0x990
    #define    PHY_X4_DQS_IE_TIMING_2_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_2_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_2_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_2_RW_0_8    0xff    //0x51
#define    DENALI_PHY_613_DATA    0x994
    #define    PHY_RDLVL_DLY_STEP_2_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_2_RW_0_4    0xf    //0x06
#define    DENALI_PHY_614_DATA    0x998
    #define    PHY_RDLVL_MAX_EDGE_2_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_615_DATA    0x99c
    #define    PHY_DATA_DC_INIT_DISABLE_2_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_2_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_2_RW_0_2    0x3    //0x00
#define    DENALI_PHY_616_DATA    0x9a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_2_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_617_DATA    0x9a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_2_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_2_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_2_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_2_RW_0_1    0x1    //0x01
#define    DENALI_PHY_618_DATA    0x9a8
    #define    PHY_RDDATA_EN_DLY_2_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_2_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_619_DATA    0x9ac
    #define    PHY_DQ_DM_SWIZZLE0_2_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_620_DATA    0x9b0
    #define    PHY_DQ_DM_SWIZZLE1_2_RW_0_4    0xf    //0x08
#define    DENALI_PHY_621_DATA    0x9b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_2_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_2_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_622_DATA    0x9b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_2_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_2_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_623_DATA    0x9bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_2_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_2_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_624_DATA    0x9c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_2_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_2_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_625_DATA    0x9c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_2_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_626_DATA    0x9c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_2_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_2_RW_0_2    0x3    //0x00
#define    DENALI_PHY_627_DATA    0x9cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_628_DATA    0x9d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_629_DATA    0x9d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_630_DATA    0x9d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_631_DATA    0x9dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_632_DATA    0x9e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_633_DATA    0x9e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_634_DATA    0x9e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_635_DATA    0x9ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_636_DATA    0x9f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_637_DATA    0x9f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_638_DATA    0x9f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_639_DATA    0x9fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_640_DATA    0xa00
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_641_DATA    0xa04
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_642_DATA    0xa08
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_643_DATA    0xa0c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_644_DATA    0xa10
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_645_DATA    0xa14
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_2_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_2_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_2_RW_0_4    0xf    //0x02
#define    DENALI_PHY_646_DATA    0xa18
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_2_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_647_DATA    0xa1c
    #define    PHY_GTLVL_LAT_ADJ_START_2_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_648_DATA    0xa20
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_2_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_2_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_649_DATA    0xa24
    #define    PHY_X4_NTP_PASS_2_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_2_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_2_RW_0_4    0xf    //0x08
#define    DENALI_PHY_650_DATA    0xa28
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_2_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_651_DATA    0xa2c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_2_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_2_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_652_DATA    0xa30
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_2_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_2_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_653_DATA    0xa34
    #define    PHY_X4_GTLVL_LAT_ADJ_START_2_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_2_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_2_RW_0_1    0x1    //0x00
#define    DENALI_PHY_654_DATA    0xa38
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_2_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_655_DATA    0xa3c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_2_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_2_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_2_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_2_RW_0_8    0xff    //0x20
#define    DENALI_PHY_656_DATA    0xa40
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_2_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_2_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_2_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_2_RW_0_8    0xff    //0x20
#define    DENALI_PHY_657_DATA    0xa44
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_2_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_2_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_2_RW_0_8    0xff    //0x20
#define    DENALI_PHY_658_DATA    0xa48
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_2_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_2_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_2_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_659_DATA    0xa4c
    #define    PHY_X4_DQS_FFE_2_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_2_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_2_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_2_RW_0_2    0x3    //0x00
#define    DENALI_PHY_660_DATA    0xa50
    #define    PHY_RX_CAL_DQ0_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_661_DATA    0xa54
    #define    PHY_RX_CAL_DQ1_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_662_DATA    0xa58
    #define    PHY_RX_CAL_DQ2_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_663_DATA    0xa5c
    #define    PHY_RX_CAL_DQ3_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_664_DATA    0xa60
    #define    PHY_RX_CAL_DQ4_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_665_DATA    0xa64
    #define    PHY_RX_CAL_DQ5_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_666_DATA    0xa68
    #define    PHY_RX_CAL_DQ6_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_667_DATA    0xa6c
    #define    PHY_RX_CAL_DQ7_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_668_DATA    0xa70
    #define    PHY_RX_CAL_DM_2_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_669_DATA    0xa74
#define    DENALI_PHY_670_DATA    0xa78
#define    DENALI_PHY_671_DATA    0xa7c
#define    DENALI_PHY_672_DATA    0xa80
#define    DENALI_PHY_673_DATA    0xa84
#define    DENALI_PHY_674_DATA    0xa88
#define    DENALI_PHY_675_DATA    0xa8c
#define    DENALI_PHY_676_DATA    0xa90
#define    DENALI_PHY_677_DATA    0xa94
#define    DENALI_PHY_678_DATA    0xa98
#define    DENALI_PHY_679_DATA    0xa9c
#define    DENALI_PHY_680_DATA    0xaa0
#define    DENALI_PHY_681_DATA    0xaa4
#define    DENALI_PHY_682_DATA    0xaa8
#define    DENALI_PHY_683_DATA    0xaac
#define    DENALI_PHY_684_DATA    0xab0
#define    DENALI_PHY_685_DATA    0xab4
#define    DENALI_PHY_686_DATA    0xab8
#define    DENALI_PHY_687_DATA    0xabc
#define    DENALI_PHY_688_DATA    0xac0
#define    DENALI_PHY_689_DATA    0xac4
#define    DENALI_PHY_690_DATA    0xac8
#define    DENALI_PHY_691_DATA    0xacc
#define    DENALI_PHY_692_DATA    0xad0
#define    DENALI_PHY_693_DATA    0xad4
#define    DENALI_PHY_694_DATA    0xad8
#define    DENALI_PHY_695_DATA    0xadc
#define    DENALI_PHY_696_DATA    0xae0
#define    DENALI_PHY_697_DATA    0xae4
#define    DENALI_PHY_698_DATA    0xae8
#define    DENALI_PHY_699_DATA    0xaec
#define    DENALI_PHY_700_DATA    0xaf0
#define    DENALI_PHY_701_DATA    0xaf4
#define    DENALI_PHY_702_DATA    0xaf8
#define    DENALI_PHY_703_DATA    0xafc
#define    DENALI_PHY_704_DATA    0xb00
#define    DENALI_PHY_705_DATA    0xb04
#define    DENALI_PHY_706_DATA    0xb08
#define    DENALI_PHY_707_DATA    0xb0c
#define    DENALI_PHY_708_DATA    0xb10
#define    DENALI_PHY_709_DATA    0xb14
#define    DENALI_PHY_710_DATA    0xb18
#define    DENALI_PHY_711_DATA    0xb1c
#define    DENALI_PHY_712_DATA    0xb20
#define    DENALI_PHY_713_DATA    0xb24
#define    DENALI_PHY_714_DATA    0xb28
#define    DENALI_PHY_715_DATA    0xb2c
#define    DENALI_PHY_716_DATA    0xb30
#define    DENALI_PHY_717_DATA    0xb34
#define    DENALI_PHY_718_DATA    0xb38
#define    DENALI_PHY_719_DATA    0xb3c
#define    DENALI_PHY_720_DATA    0xb40
#define    DENALI_PHY_721_DATA    0xb44
#define    DENALI_PHY_722_DATA    0xb48
#define    DENALI_PHY_723_DATA    0xb4c
#define    DENALI_PHY_724_DATA    0xb50
#define    DENALI_PHY_725_DATA    0xb54
#define    DENALI_PHY_726_DATA    0xb58
#define    DENALI_PHY_727_DATA    0xb5c
#define    DENALI_PHY_728_DATA    0xb60
#define    DENALI_PHY_729_DATA    0xb64
#define    DENALI_PHY_730_DATA    0xb68
#define    DENALI_PHY_731_DATA    0xb6c
#define    DENALI_PHY_732_DATA    0xb70
#define    DENALI_PHY_733_DATA    0xb74
#define    DENALI_PHY_734_DATA    0xb78
#define    DENALI_PHY_735_DATA    0xb7c
#define    DENALI_PHY_736_DATA    0xb80
#define    DENALI_PHY_737_DATA    0xb84
#define    DENALI_PHY_738_DATA    0xb88
#define    DENALI_PHY_739_DATA    0xb8c
#define    DENALI_PHY_740_DATA    0xb90
#define    DENALI_PHY_741_DATA    0xb94
#define    DENALI_PHY_742_DATA    0xb98
#define    DENALI_PHY_743_DATA    0xb9c
#define    DENALI_PHY_744_DATA    0xba0
#define    DENALI_PHY_745_DATA    0xba4
#define    DENALI_PHY_746_DATA    0xba8
#define    DENALI_PHY_747_DATA    0xbac
#define    DENALI_PHY_748_DATA    0xbb0
#define    DENALI_PHY_749_DATA    0xbb4
#define    DENALI_PHY_750_DATA    0xbb8
#define    DENALI_PHY_751_DATA    0xbbc
#define    DENALI_PHY_752_DATA    0xbc0
#define    DENALI_PHY_753_DATA    0xbc4
#define    DENALI_PHY_754_DATA    0xbc8
#define    DENALI_PHY_755_DATA    0xbcc
#define    DENALI_PHY_756_DATA    0xbd0
#define    DENALI_PHY_757_DATA    0xbd4
#define    DENALI_PHY_758_DATA    0xbd8
#define    DENALI_PHY_759_DATA    0xbdc
#define    DENALI_PHY_760_DATA    0xbe0
#define    DENALI_PHY_761_DATA    0xbe4
#define    DENALI_PHY_762_DATA    0xbe8
#define    DENALI_PHY_763_DATA    0xbec
#define    DENALI_PHY_764_DATA    0xbf0
#define    DENALI_PHY_765_DATA    0xbf4
#define    DENALI_PHY_766_DATA    0xbf8
#define    DENALI_PHY_767_DATA    0xbfc
#define    DENALI_PHY_768_DATA    0xc00
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_3_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_3_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_769_DATA    0xc04
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_3_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_770_DATA    0xc08
    #define    PHY_CLK_BYPASS_OVERRIDE_3_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_3_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_771_DATA    0xc0c
    #define    PHY_SW_WRDQ3_SHIFT_3_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_3_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_3_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_3_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_772_DATA    0xc10
    #define    PHY_SW_WRDQ7_SHIFT_3_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_3_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_3_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_3_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_773_DATA    0xc14
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_3_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_3_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_3_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_3_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_774_DATA    0xc18
    #define    PHY_LPBK_CONTROL_3_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_3_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_3_RW_0_2    0x3    //0x00
#define    DENALI_PHY_775_DATA    0xc1c
    #define    PHY_GATE_DELAY_COMP_DISABLE_3_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_3_RW_0_1    0x1    //0x01
#define    DENALI_PHY_776_DATA    0xc20
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_3_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_777_DATA    0xc24
    #define    PHY_AUTO_TIMING_MARGIN_OBS_3_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_778_DATA    0xc28
    #define    PHY_PRBS_PATTERN_START_3_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_3_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_3_RW_0_1    0x1    //0x01
#define    DENALI_PHY_779_DATA    0xc2c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_3_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_3_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_3_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_780_DATA    0xc30
    #define    PHY_X4_VREF_TRAIN_OBS_3_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_3_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_3_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_781_DATA    0xc34
    #define    SC_PHY_SNAP_OBS_REGS_3_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_3_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_782_DATA    0xc38
    #define    PHY_DFI40_POLARITY_3_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_3_RW_0_3    0x7    //0x02
#define    DENALI_PHY_783_DATA    0xc3c
    #define    PHY_RDLVL_PATT8_3_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_784_DATA    0xc40
    #define    PHY_RDLVL_PATT9_3_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_785_DATA    0xc44
    #define    PHY_RDLVL_PATT10_3_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_786_DATA    0xc48
    #define    PHY_RDLVL_PATT11_3_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_787_DATA    0xc4c
    #define    PHY_RDLVL_PATT12_3_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_788_DATA    0xc50
    #define    PHY_RDLVL_PATT13_3_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_789_DATA    0xc54
    #define    PHY_RDLVL_PATT14_3_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_790_DATA    0xc58
    #define    PHY_RDLVL_PATT15_3_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_791_DATA    0xc5c
    #define    PHY_RDLVL_PATT0_3_MASK_3_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_792_DATA    0xc60
    #define    PHY_RDLVL_PATT8_11_MASK_3_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_793_DATA    0xc64
    #define    PHY_RDLVL_PATT12_15_MASK_3_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_794_DATA    0xc68
    #define    PHY_RDDQ_ENC_OBS_SELECT_3_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_3_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_3_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_3_RW_0_3    0x7    //0x00
#define    DENALI_PHY_795_DATA    0xc6c
    #define    PHY_FIFO_PTR_OBS_SELECT_3_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_3_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_3_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_3_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_796_DATA    0xc70
    #define    PHY_WRLVL_CAPTURE_CNT_3_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_3_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_3_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_3_RW_0_1    0x1    //0x00
#define    DENALI_PHY_797_DATA    0xc74
    #define    PHY_GTLVL_UPDT_WAIT_CNT_3_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_3_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_3_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_3_RW_0_4    0xf    //0x08
#define    DENALI_PHY_798_DATA    0xc78
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_3_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_3_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_3_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_3_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_799_DATA    0xc7c
    #define    PHY_RDLVL_DATA_SWIZZLE_3_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_3_RW_0_8    0xff    //0x00
#define    DENALI_PHY_800_DATA    0xc80
    #define    PHY_WDQLVL_PATT_3_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_3_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_3_RW_0_8    0xff    //0x20
#define    DENALI_PHY_801_DATA    0xc84
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_3_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_3_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_3_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_802_DATA    0xc88
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_3_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_3_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_3_RW_0_8    0xff    //0x20
#define    DENALI_PHY_803_DATA    0xc8c
    #define    PHY_WDQLVL_DATADM_MASK_3_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_804_DATA    0xc90
    #define    PHY_USER_PATT0_3_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_805_DATA    0xc94
    #define    PHY_USER_PATT1_3_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_806_DATA    0xc98
    #define    PHY_USER_PATT2_3_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_807_DATA    0xc9c
    #define    PHY_USER_PATT3_3_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_808_DATA    0xca0
    #define    PHY_NTP_MULT_TRAIN_3_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_3_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_809_DATA    0xca4
    #define    PHY_NTP_PERIOD_THRESHOLD_3_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_3_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_810_DATA    0xca8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_3_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_3_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_811_DATA    0xcac
    #define    PHY_FIFO_PTR_OBS_3_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_3_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_812_DATA    0xcb0
    #define    PHY_LPBK_RESULT_OBS_3_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_813_DATA    0xcb4
    #define    PHY_MASTER_DLY_LOCK_OBS_3_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_3_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_814_DATA    0xcb8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_3_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_3_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_3_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_3_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_815_DATA    0xcbc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_3_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_3_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_3_RD_0_8    0xff    //0x00
#define    DENALI_PHY_816_DATA    0xcc0
    #define    PHY_WR_SHIFT_OBS_3_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_3_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_3_RD_0_8    0xff    //0x00
#define    DENALI_PHY_817_DATA    0xcc4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_3_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_3_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_818_DATA    0xcc8
    #define    PHY_WRLVL_STATUS_OBS_3_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_819_DATA    0xccc
    #define    PHY_WRLVL_ERROR_OBS_3_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_820_DATA    0xcd0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_3_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_3_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_821_DATA    0xcd4
    #define    PHY_GTLVL_STATUS_OBS_3_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_822_DATA    0xcd8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_3_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_3_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_823_DATA    0xcdc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_3_RD_0_2    0x3    //0x00
#define    DENALI_PHY_824_DATA    0xce0
    #define    PHY_RDLVL_STATUS_OBS_3_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_825_DATA    0xce4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_3_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_3_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_826_DATA    0xce8
    #define    PHY_WDQLVL_STATUS_OBS_3_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_827_DATA    0xcec
    #define    PHY_DQS_RATIO_X8_3_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_3_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_3_RW_0_4    0xf    //0x00
#define    DENALI_PHY_828_DATA    0xcf0
    #define    PHY_DDL_MODE_3_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_829_DATA    0xcf4
    #define    PHY_DDL_MASK_3_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_830_DATA    0xcf8
    #define    PHY_DDL_TEST_OBS_3_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_831_DATA    0xcfc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_3_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_832_DATA    0xd00
    #define    PHY_RX_CAL_DQS_3_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_3_RW_0_8    0xff    //0x04
#define    DENALI_PHY_833_DATA    0xd04
    #define    PHY_RX_CAL_X4_FDBK_3_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_3_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_834_DATA    0xd08
    #define    PHY_STATIC_TOG_DISABLE_3_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_3_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_3_RW_0_1    0x1    //0x01
#define    DENALI_PHY_835_DATA    0xd0c
    #define    PHY_DFE_EN_3_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_3_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_3_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_3_RW_0_1    0x1    //0x01
#define    DENALI_PHY_836_DATA    0xd10
    #define    PHY_DATA_DC_ADJUST_START_3_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_3_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_3_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_3_RW_0_8    0xff    //0x08
#define    DENALI_PHY_837_DATA    0xd14
    #define    PHY_DATA_DC_CAL_POLARITY_3_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_3_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_3_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_3_RW_0_8    0xff    //0x10
#define    DENALI_PHY_838_DATA    0xd18
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_3_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_3_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_3_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_3_RW_0_1    0x1    //0x00
#define    DENALI_PHY_839_DATA    0xd1c
    #define    PHY_SLICE_PWR_RDC_DISABLE_3_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_3_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_3_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_840_DATA    0xd20
    #define    PHY_DQS_TSEL_ENABLE_3_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_3_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_3_RW_0_3    0x7    //0x01
#define    DENALI_PHY_841_DATA    0xd24
    #define    PHY_VREF_INITIAL_START_POINT_3_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_3_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_3_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_842_DATA    0xd28
    #define    PHY_NTP_WDQ_STEP_SIZE_3_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_3_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_3_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_3_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_843_DATA    0xd2c
    #define    PHY_NTP_WDQ_STOP_3_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_3_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_844_DATA    0xd30
    #define    PHY_FAST_LVL_EN_3_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_3_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_3_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_845_DATA    0xd34
    #define    PHY_PAD_RX_DCD_2_3_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_3_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_3_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_3_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_846_DATA    0xd38
    #define    PHY_PAD_RX_DCD_6_3_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_3_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_3_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_3_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_847_DATA    0xd3c
    #define    PHY_PAD_DQS_RX_DCD_3_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_3_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_3_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_848_DATA    0xd40
    #define    PHY_PAD_DSLICE_IO_CFG_3_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_849_DATA    0xd44
    #define    PHY_RDDQ1_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_850_DATA    0xd48
    #define    PHY_RDDQ3_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_851_DATA    0xd4c
    #define    PHY_RDDQ5_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_852_DATA    0xd50
    #define    PHY_RDDQ7_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_853_DATA    0xd54
    #define    PHY_RX_CAL_ALL_DLY_3_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_3_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_854_DATA    0xd58
    #define    PHY_RX_OFF_FIRST_STEP_3_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_3_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_3_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_3_RW_0_8    0xff    //0x03
#define    DENALI_PHY_855_DATA    0xd5c
    #define    PHY_DATA_DC_CAL_CLK_SEL_3_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_3_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_3_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_3_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_856_DATA    0xd60
    #define    PHY_DQS_OE_TIMING_3_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_3_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_3_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_3_RW_0_8    0xff    //0x42
#define    DENALI_PHY_857_DATA    0xd64
    #define    PHY_DQS_TSEL_WR_TIMING_3_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_3_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_3_RW_0_4    0xf    //0x00
#define    DENALI_PHY_858_DATA    0xd68
    #define    PHY_PAD_VREF_CTRL_DQ_3_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_3_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_859_DATA    0xd6c
    #define    PHY_DQ_IE_TIMING_3_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_3_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_3_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_860_DATA    0xd70
    #define    PHY_DBI_MODE_3_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_3_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_3_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_3_RW_0_8    0xff    //0x80
#define    DENALI_PHY_861_DATA    0xd74
    #define    PHY_RDDATA_EN_TSEL_DLY_3_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_3_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_3_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_3_RW_0_1    0x1    //0x00
#define    DENALI_PHY_862_DATA    0xd78
    #define    PHY_MASTER_DELAY_STEP_3_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_3_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_3_RW_0_4    0xf    //0x00
#define    DENALI_PHY_863_DATA    0xd7c
    #define    PHY_WRLVL_DLY_STEP_3_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_3_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_3_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_3_RW_0_8    0xff    //0x42
#define    DENALI_PHY_864_DATA    0xd80
    #define    PHY_GTLVL_RESP_WAIT_CNT_3_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_3_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_3_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_3_RW_0_4    0xf    //0x01
#define    DENALI_PHY_865_DATA    0xd84
    #define    PHY_GTLVL_FINAL_STEP_3_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_3_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_866_DATA    0xd88
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_3_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_3_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_3_RW_0_8    0xff    //0x20
#define    DENALI_PHY_867_DATA    0xd8c
    #define    PHY_X4_DQ_IE_TIMING_3_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_3_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_3_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_3_RW_0_8    0xff    //0x42
#define    DENALI_PHY_868_DATA    0xd90
    #define    PHY_X4_DQS_IE_TIMING_3_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_3_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_3_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_3_RW_0_8    0xff    //0x51
#define    DENALI_PHY_869_DATA    0xd94
    #define    PHY_RDLVL_DLY_STEP_3_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_3_RW_0_4    0xf    //0x06
#define    DENALI_PHY_870_DATA    0xd98
    #define    PHY_RDLVL_MAX_EDGE_3_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_871_DATA    0xd9c
    #define    PHY_DATA_DC_INIT_DISABLE_3_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_3_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_3_RW_0_2    0x3    //0x00
#define    DENALI_PHY_872_DATA    0xda0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_3_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_873_DATA    0xda4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_3_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_3_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_3_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_3_RW_0_1    0x1    //0x01
#define    DENALI_PHY_874_DATA    0xda8
    #define    PHY_RDDATA_EN_DLY_3_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_3_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_875_DATA    0xdac
    #define    PHY_DQ_DM_SWIZZLE0_3_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_876_DATA    0xdb0
    #define    PHY_DQ_DM_SWIZZLE1_3_RW_0_4    0xf    //0x08
#define    DENALI_PHY_877_DATA    0xdb4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_3_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_3_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_878_DATA    0xdb8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_3_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_3_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_879_DATA    0xdbc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_3_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_3_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_880_DATA    0xdc0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_3_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_3_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_881_DATA    0xdc4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_3_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_882_DATA    0xdc8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_3_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_3_RW_0_2    0x3    //0x00
#define    DENALI_PHY_883_DATA    0xdcc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_884_DATA    0xdd0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_885_DATA    0xdd4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_886_DATA    0xdd8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_887_DATA    0xddc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_888_DATA    0xde0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_889_DATA    0xde4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_890_DATA    0xde8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_891_DATA    0xdec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_892_DATA    0xdf0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_893_DATA    0xdf4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_894_DATA    0xdf8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_895_DATA    0xdfc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_896_DATA    0xe00
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_897_DATA    0xe04
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_898_DATA    0xe08
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_899_DATA    0xe0c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_900_DATA    0xe10
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_901_DATA    0xe14
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_3_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_3_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_3_RW_0_4    0xf    //0x02
#define    DENALI_PHY_902_DATA    0xe18
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_3_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_903_DATA    0xe1c
    #define    PHY_GTLVL_LAT_ADJ_START_3_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_904_DATA    0xe20
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_3_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_3_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_905_DATA    0xe24
    #define    PHY_X4_NTP_PASS_3_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_3_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_3_RW_0_4    0xf    //0x08
#define    DENALI_PHY_906_DATA    0xe28
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_3_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_907_DATA    0xe2c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_3_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_3_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_908_DATA    0xe30
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_3_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_3_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_909_DATA    0xe34
    #define    PHY_X4_GTLVL_LAT_ADJ_START_3_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_3_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_3_RW_0_1    0x1    //0x00
#define    DENALI_PHY_910_DATA    0xe38
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_3_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_911_DATA    0xe3c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_3_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_3_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_3_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_3_RW_0_8    0xff    //0x20
#define    DENALI_PHY_912_DATA    0xe40
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_3_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_3_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_3_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_3_RW_0_8    0xff    //0x20
#define    DENALI_PHY_913_DATA    0xe44
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_3_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_3_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_3_RW_0_8    0xff    //0x20
#define    DENALI_PHY_914_DATA    0xe48
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_3_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_3_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_3_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_915_DATA    0xe4c
    #define    PHY_X4_DQS_FFE_3_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_3_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_3_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_3_RW_0_2    0x3    //0x00
#define    DENALI_PHY_916_DATA    0xe50
    #define    PHY_RX_CAL_DQ0_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_917_DATA    0xe54
    #define    PHY_RX_CAL_DQ1_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_918_DATA    0xe58
    #define    PHY_RX_CAL_DQ2_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_919_DATA    0xe5c
    #define    PHY_RX_CAL_DQ3_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_920_DATA    0xe60
    #define    PHY_RX_CAL_DQ4_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_921_DATA    0xe64
    #define    PHY_RX_CAL_DQ5_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_922_DATA    0xe68
    #define    PHY_RX_CAL_DQ6_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_923_DATA    0xe6c
    #define    PHY_RX_CAL_DQ7_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_924_DATA    0xe70
    #define    PHY_RX_CAL_DM_3_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_925_DATA    0xe74
#define    DENALI_PHY_926_DATA    0xe78
#define    DENALI_PHY_927_DATA    0xe7c
#define    DENALI_PHY_928_DATA    0xe80
#define    DENALI_PHY_929_DATA    0xe84
#define    DENALI_PHY_930_DATA    0xe88
#define    DENALI_PHY_931_DATA    0xe8c
#define    DENALI_PHY_932_DATA    0xe90
#define    DENALI_PHY_933_DATA    0xe94
#define    DENALI_PHY_934_DATA    0xe98
#define    DENALI_PHY_935_DATA    0xe9c
#define    DENALI_PHY_936_DATA    0xea0
#define    DENALI_PHY_937_DATA    0xea4
#define    DENALI_PHY_938_DATA    0xea8
#define    DENALI_PHY_939_DATA    0xeac
#define    DENALI_PHY_940_DATA    0xeb0
#define    DENALI_PHY_941_DATA    0xeb4
#define    DENALI_PHY_942_DATA    0xeb8
#define    DENALI_PHY_943_DATA    0xebc
#define    DENALI_PHY_944_DATA    0xec0
#define    DENALI_PHY_945_DATA    0xec4
#define    DENALI_PHY_946_DATA    0xec8
#define    DENALI_PHY_947_DATA    0xecc
#define    DENALI_PHY_948_DATA    0xed0
#define    DENALI_PHY_949_DATA    0xed4
#define    DENALI_PHY_950_DATA    0xed8
#define    DENALI_PHY_951_DATA    0xedc
#define    DENALI_PHY_952_DATA    0xee0
#define    DENALI_PHY_953_DATA    0xee4
#define    DENALI_PHY_954_DATA    0xee8
#define    DENALI_PHY_955_DATA    0xeec
#define    DENALI_PHY_956_DATA    0xef0
#define    DENALI_PHY_957_DATA    0xef4
#define    DENALI_PHY_958_DATA    0xef8
#define    DENALI_PHY_959_DATA    0xefc
#define    DENALI_PHY_960_DATA    0xf00
#define    DENALI_PHY_961_DATA    0xf04
#define    DENALI_PHY_962_DATA    0xf08
#define    DENALI_PHY_963_DATA    0xf0c
#define    DENALI_PHY_964_DATA    0xf10
#define    DENALI_PHY_965_DATA    0xf14
#define    DENALI_PHY_966_DATA    0xf18
#define    DENALI_PHY_967_DATA    0xf1c
#define    DENALI_PHY_968_DATA    0xf20
#define    DENALI_PHY_969_DATA    0xf24
#define    DENALI_PHY_970_DATA    0xf28
#define    DENALI_PHY_971_DATA    0xf2c
#define    DENALI_PHY_972_DATA    0xf30
#define    DENALI_PHY_973_DATA    0xf34
#define    DENALI_PHY_974_DATA    0xf38
#define    DENALI_PHY_975_DATA    0xf3c
#define    DENALI_PHY_976_DATA    0xf40
#define    DENALI_PHY_977_DATA    0xf44
#define    DENALI_PHY_978_DATA    0xf48
#define    DENALI_PHY_979_DATA    0xf4c
#define    DENALI_PHY_980_DATA    0xf50
#define    DENALI_PHY_981_DATA    0xf54
#define    DENALI_PHY_982_DATA    0xf58
#define    DENALI_PHY_983_DATA    0xf5c
#define    DENALI_PHY_984_DATA    0xf60
#define    DENALI_PHY_985_DATA    0xf64
#define    DENALI_PHY_986_DATA    0xf68
#define    DENALI_PHY_987_DATA    0xf6c
#define    DENALI_PHY_988_DATA    0xf70
#define    DENALI_PHY_989_DATA    0xf74
#define    DENALI_PHY_990_DATA    0xf78
#define    DENALI_PHY_991_DATA    0xf7c
#define    DENALI_PHY_992_DATA    0xf80
#define    DENALI_PHY_993_DATA    0xf84
#define    DENALI_PHY_994_DATA    0xf88
#define    DENALI_PHY_995_DATA    0xf8c
#define    DENALI_PHY_996_DATA    0xf90
#define    DENALI_PHY_997_DATA    0xf94
#define    DENALI_PHY_998_DATA    0xf98
#define    DENALI_PHY_999_DATA    0xf9c
#define    DENALI_PHY_1000_DATA    0xfa0
#define    DENALI_PHY_1001_DATA    0xfa4
#define    DENALI_PHY_1002_DATA    0xfa8
#define    DENALI_PHY_1003_DATA    0xfac
#define    DENALI_PHY_1004_DATA    0xfb0
#define    DENALI_PHY_1005_DATA    0xfb4
#define    DENALI_PHY_1006_DATA    0xfb8
#define    DENALI_PHY_1007_DATA    0xfbc
#define    DENALI_PHY_1008_DATA    0xfc0
#define    DENALI_PHY_1009_DATA    0xfc4
#define    DENALI_PHY_1010_DATA    0xfc8
#define    DENALI_PHY_1011_DATA    0xfcc
#define    DENALI_PHY_1012_DATA    0xfd0
#define    DENALI_PHY_1013_DATA    0xfd4
#define    DENALI_PHY_1014_DATA    0xfd8
#define    DENALI_PHY_1015_DATA    0xfdc
#define    DENALI_PHY_1016_DATA    0xfe0
#define    DENALI_PHY_1017_DATA    0xfe4
#define    DENALI_PHY_1018_DATA    0xfe8
#define    DENALI_PHY_1019_DATA    0xfec
#define    DENALI_PHY_1020_DATA    0xff0
#define    DENALI_PHY_1021_DATA    0xff4
#define    DENALI_PHY_1022_DATA    0xff8
#define    DENALI_PHY_1023_DATA    0xffc
#define    DENALI_PHY_1024_DATA    0x1000
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_4_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_4_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_1025_DATA    0x1004
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_4_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1026_DATA    0x1008
    #define    PHY_CLK_BYPASS_OVERRIDE_4_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_4_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_1027_DATA    0x100c
    #define    PHY_SW_WRDQ3_SHIFT_4_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_4_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_4_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_4_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1028_DATA    0x1010
    #define    PHY_SW_WRDQ7_SHIFT_4_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_4_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_4_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_4_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1029_DATA    0x1014
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_4_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_4_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_4_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_4_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1030_DATA    0x1018
    #define    PHY_LPBK_CONTROL_4_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_4_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_4_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1031_DATA    0x101c
    #define    PHY_GATE_DELAY_COMP_DISABLE_4_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_4_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1032_DATA    0x1020
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_4_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1033_DATA    0x1024
    #define    PHY_AUTO_TIMING_MARGIN_OBS_4_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_1034_DATA    0x1028
    #define    PHY_PRBS_PATTERN_START_4_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_4_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_4_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1035_DATA    0x102c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_4_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_4_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_4_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1036_DATA    0x1030
    #define    PHY_X4_VREF_TRAIN_OBS_4_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_4_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_4_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1037_DATA    0x1034
    #define    SC_PHY_SNAP_OBS_REGS_4_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_4_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_1038_DATA    0x1038
    #define    PHY_DFI40_POLARITY_4_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_4_RW_0_3    0x7    //0x02
#define    DENALI_PHY_1039_DATA    0x103c
    #define    PHY_RDLVL_PATT8_4_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_1040_DATA    0x1040
    #define    PHY_RDLVL_PATT9_4_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_1041_DATA    0x1044
    #define    PHY_RDLVL_PATT10_4_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_1042_DATA    0x1048
    #define    PHY_RDLVL_PATT11_4_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_1043_DATA    0x104c
    #define    PHY_RDLVL_PATT12_4_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_1044_DATA    0x1050
    #define    PHY_RDLVL_PATT13_4_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_1045_DATA    0x1054
    #define    PHY_RDLVL_PATT14_4_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_1046_DATA    0x1058
    #define    PHY_RDLVL_PATT15_4_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_1047_DATA    0x105c
    #define    PHY_RDLVL_PATT0_3_MASK_4_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1048_DATA    0x1060
    #define    PHY_RDLVL_PATT8_11_MASK_4_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_1049_DATA    0x1064
    #define    PHY_RDLVL_PATT12_15_MASK_4_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_1050_DATA    0x1068
    #define    PHY_RDDQ_ENC_OBS_SELECT_4_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_4_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_4_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_4_RW_0_3    0x7    //0x00
#define    DENALI_PHY_1051_DATA    0x106c
    #define    PHY_FIFO_PTR_OBS_SELECT_4_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_4_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_4_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_4_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1052_DATA    0x1070
    #define    PHY_WRLVL_CAPTURE_CNT_4_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_4_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_4_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_4_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1053_DATA    0x1074
    #define    PHY_GTLVL_UPDT_WAIT_CNT_4_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_4_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_4_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_4_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1054_DATA    0x1078
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_4_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_4_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_4_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_4_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_1055_DATA    0x107c
    #define    PHY_RDLVL_DATA_SWIZZLE_4_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_4_RW_0_8    0xff    //0x00
#define    DENALI_PHY_1056_DATA    0x1080
    #define    PHY_WDQLVL_PATT_4_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_4_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_4_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1057_DATA    0x1084
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_4_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_4_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_4_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_1058_DATA    0x1088
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_4_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_4_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_4_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1059_DATA    0x108c
    #define    PHY_WDQLVL_DATADM_MASK_4_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_1060_DATA    0x1090
    #define    PHY_USER_PATT0_4_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1061_DATA    0x1094
    #define    PHY_USER_PATT1_4_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1062_DATA    0x1098
    #define    PHY_USER_PATT2_4_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1063_DATA    0x109c
    #define    PHY_USER_PATT3_4_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1064_DATA    0x10a0
    #define    PHY_NTP_MULT_TRAIN_4_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_4_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_1065_DATA    0x10a4
    #define    PHY_NTP_PERIOD_THRESHOLD_4_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_4_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_1066_DATA    0x10a8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_4_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_4_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_1067_DATA    0x10ac
    #define    PHY_FIFO_PTR_OBS_4_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_4_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_1068_DATA    0x10b0
    #define    PHY_LPBK_RESULT_OBS_4_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1069_DATA    0x10b4
    #define    PHY_MASTER_DLY_LOCK_OBS_4_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_4_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_1070_DATA    0x10b8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_4_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_4_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_4_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_4_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_1071_DATA    0x10bc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_4_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_4_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_4_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1072_DATA    0x10c0
    #define    PHY_WR_SHIFT_OBS_4_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_4_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_4_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1073_DATA    0x10c4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_4_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_4_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1074_DATA    0x10c8
    #define    PHY_WRLVL_STATUS_OBS_4_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_1075_DATA    0x10cc
    #define    PHY_WRLVL_ERROR_OBS_4_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1076_DATA    0x10d0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_4_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_4_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_1077_DATA    0x10d4
    #define    PHY_GTLVL_STATUS_OBS_4_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_1078_DATA    0x10d8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_4_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_4_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1079_DATA    0x10dc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_4_RD_0_2    0x3    //0x00
#define    DENALI_PHY_1080_DATA    0x10e0
    #define    PHY_RDLVL_STATUS_OBS_4_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1081_DATA    0x10e4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_4_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_4_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1082_DATA    0x10e8
    #define    PHY_WDQLVL_STATUS_OBS_4_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1083_DATA    0x10ec
    #define    PHY_DQS_RATIO_X8_4_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_4_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_4_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1084_DATA    0x10f0
    #define    PHY_DDL_MODE_4_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_1085_DATA    0x10f4
    #define    PHY_DDL_MASK_4_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1086_DATA    0x10f8
    #define    PHY_DDL_TEST_OBS_4_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1087_DATA    0x10fc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_4_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1088_DATA    0x1100
    #define    PHY_RX_CAL_DQS_4_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_4_RW_0_8    0xff    //0x04
#define    DENALI_PHY_1089_DATA    0x1104
    #define    PHY_RX_CAL_X4_FDBK_4_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_4_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1090_DATA    0x1108
    #define    PHY_STATIC_TOG_DISABLE_4_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_4_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_4_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1091_DATA    0x110c
    #define    PHY_DFE_EN_4_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_4_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_4_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_4_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1092_DATA    0x1110
    #define    PHY_DATA_DC_ADJUST_START_4_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_4_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_4_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_4_RW_0_8    0xff    //0x08
#define    DENALI_PHY_1093_DATA    0x1114
    #define    PHY_DATA_DC_CAL_POLARITY_4_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_4_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_4_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_4_RW_0_8    0xff    //0x10
#define    DENALI_PHY_1094_DATA    0x1118
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_4_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_4_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_4_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_4_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1095_DATA    0x111c
    #define    PHY_SLICE_PWR_RDC_DISABLE_4_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_4_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_4_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_1096_DATA    0x1120
    #define    PHY_DQS_TSEL_ENABLE_4_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_4_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_4_RW_0_3    0x7    //0x01
#define    DENALI_PHY_1097_DATA    0x1124
    #define    PHY_VREF_INITIAL_START_POINT_4_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_4_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_4_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_1098_DATA    0x1128
    #define    PHY_NTP_WDQ_STEP_SIZE_4_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_4_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_4_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_4_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_1099_DATA    0x112c
    #define    PHY_NTP_WDQ_STOP_4_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_4_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1100_DATA    0x1130
    #define    PHY_FAST_LVL_EN_4_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_4_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_4_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1101_DATA    0x1134
    #define    PHY_PAD_RX_DCD_2_4_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_4_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_4_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_4_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1102_DATA    0x1138
    #define    PHY_PAD_RX_DCD_6_4_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_4_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_4_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_4_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1103_DATA    0x113c
    #define    PHY_PAD_DQS_RX_DCD_4_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_4_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_4_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1104_DATA    0x1140
    #define    PHY_PAD_DSLICE_IO_CFG_4_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1105_DATA    0x1144
    #define    PHY_RDDQ1_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1106_DATA    0x1148
    #define    PHY_RDDQ3_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1107_DATA    0x114c
    #define    PHY_RDDQ5_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1108_DATA    0x1150
    #define    PHY_RDDQ7_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1109_DATA    0x1154
    #define    PHY_RX_CAL_ALL_DLY_4_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_4_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1110_DATA    0x1158
    #define    PHY_RX_OFF_FIRST_STEP_4_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_4_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_4_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_4_RW_0_8    0xff    //0x03
#define    DENALI_PHY_1111_DATA    0x115c
    #define    PHY_DATA_DC_CAL_CLK_SEL_4_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_4_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_4_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_4_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1112_DATA    0x1160
    #define    PHY_DQS_OE_TIMING_4_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_4_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_4_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_4_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1113_DATA    0x1164
    #define    PHY_DQS_TSEL_WR_TIMING_4_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_4_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_4_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1114_DATA    0x1168
    #define    PHY_PAD_VREF_CTRL_DQ_4_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_4_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_1115_DATA    0x116c
    #define    PHY_DQ_IE_TIMING_4_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_4_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_4_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_1116_DATA    0x1170
    #define    PHY_DBI_MODE_4_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_4_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_4_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_4_RW_0_8    0xff    //0x80
#define    DENALI_PHY_1117_DATA    0x1174
    #define    PHY_RDDATA_EN_TSEL_DLY_4_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_4_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_4_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_4_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1118_DATA    0x1178
    #define    PHY_MASTER_DELAY_STEP_4_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_4_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_4_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1119_DATA    0x117c
    #define    PHY_WRLVL_DLY_STEP_4_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_4_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_4_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_4_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1120_DATA    0x1180
    #define    PHY_GTLVL_RESP_WAIT_CNT_4_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_4_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_4_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_4_RW_0_4    0xf    //0x01
#define    DENALI_PHY_1121_DATA    0x1184
    #define    PHY_GTLVL_FINAL_STEP_4_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_4_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_1122_DATA    0x1188
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_4_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_4_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_4_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1123_DATA    0x118c
    #define    PHY_X4_DQ_IE_TIMING_4_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_4_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_4_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_4_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1124_DATA    0x1190
    #define    PHY_X4_DQS_IE_TIMING_4_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_4_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_4_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_4_RW_0_8    0xff    //0x51
#define    DENALI_PHY_1125_DATA    0x1194
    #define    PHY_RDLVL_DLY_STEP_4_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_4_RW_0_4    0xf    //0x06
#define    DENALI_PHY_1126_DATA    0x1198
    #define    PHY_RDLVL_MAX_EDGE_4_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_1127_DATA    0x119c
    #define    PHY_DATA_DC_INIT_DISABLE_4_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_4_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_4_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1128_DATA    0x11a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_4_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1129_DATA    0x11a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_4_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_4_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_4_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_4_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1130_DATA    0x11a8
    #define    PHY_RDDATA_EN_DLY_4_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_4_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_1131_DATA    0x11ac
    #define    PHY_DQ_DM_SWIZZLE0_4_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_1132_DATA    0x11b0
    #define    PHY_DQ_DM_SWIZZLE1_4_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1133_DATA    0x11b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_4_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_4_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1134_DATA    0x11b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_4_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_4_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1135_DATA    0x11bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_4_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_4_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1136_DATA    0x11c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_4_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_4_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1137_DATA    0x11c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_4_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1138_DATA    0x11c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_4_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_4_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1139_DATA    0x11cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1140_DATA    0x11d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1141_DATA    0x11d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1142_DATA    0x11d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1143_DATA    0x11dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1144_DATA    0x11e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1145_DATA    0x11e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1146_DATA    0x11e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1147_DATA    0x11ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1148_DATA    0x11f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1149_DATA    0x11f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1150_DATA    0x11f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1151_DATA    0x11fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1152_DATA    0x1200
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1153_DATA    0x1204
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1154_DATA    0x1208
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1155_DATA    0x120c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1156_DATA    0x1210
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1157_DATA    0x1214
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_4_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_4_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_4_RW_0_4    0xf    //0x02
#define    DENALI_PHY_1158_DATA    0x1218
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_4_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1159_DATA    0x121c
    #define    PHY_GTLVL_LAT_ADJ_START_4_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1160_DATA    0x1220
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_4_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_4_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1161_DATA    0x1224
    #define    PHY_X4_NTP_PASS_4_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_4_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_4_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1162_DATA    0x1228
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_4_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1163_DATA    0x122c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_4_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_4_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_1164_DATA    0x1230
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_4_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_4_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_1165_DATA    0x1234
    #define    PHY_X4_GTLVL_LAT_ADJ_START_4_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_4_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_4_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1166_DATA    0x1238
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_4_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1167_DATA    0x123c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_4_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_4_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_4_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_4_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1168_DATA    0x1240
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_4_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_4_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_4_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_4_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1169_DATA    0x1244
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_4_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_4_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_4_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1170_DATA    0x1248
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_4_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_4_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_4_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1171_DATA    0x124c
    #define    PHY_X4_DQS_FFE_4_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_4_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_4_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_4_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1172_DATA    0x1250
    #define    PHY_RX_CAL_DQ0_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1173_DATA    0x1254
    #define    PHY_RX_CAL_DQ1_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1174_DATA    0x1258
    #define    PHY_RX_CAL_DQ2_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1175_DATA    0x125c
    #define    PHY_RX_CAL_DQ3_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1176_DATA    0x1260
    #define    PHY_RX_CAL_DQ4_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1177_DATA    0x1264
    #define    PHY_RX_CAL_DQ5_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1178_DATA    0x1268
    #define    PHY_RX_CAL_DQ6_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1179_DATA    0x126c
    #define    PHY_RX_CAL_DQ7_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1180_DATA    0x1270
    #define    PHY_RX_CAL_DM_4_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1181_DATA    0x1274
#define    DENALI_PHY_1182_DATA    0x1278
#define    DENALI_PHY_1183_DATA    0x127c
#define    DENALI_PHY_1184_DATA    0x1280
#define    DENALI_PHY_1185_DATA    0x1284
#define    DENALI_PHY_1186_DATA    0x1288
#define    DENALI_PHY_1187_DATA    0x128c
#define    DENALI_PHY_1188_DATA    0x1290
#define    DENALI_PHY_1189_DATA    0x1294
#define    DENALI_PHY_1190_DATA    0x1298
#define    DENALI_PHY_1191_DATA    0x129c
#define    DENALI_PHY_1192_DATA    0x12a0
#define    DENALI_PHY_1193_DATA    0x12a4
#define    DENALI_PHY_1194_DATA    0x12a8
#define    DENALI_PHY_1195_DATA    0x12ac
#define    DENALI_PHY_1196_DATA    0x12b0
#define    DENALI_PHY_1197_DATA    0x12b4
#define    DENALI_PHY_1198_DATA    0x12b8
#define    DENALI_PHY_1199_DATA    0x12bc
#define    DENALI_PHY_1200_DATA    0x12c0
#define    DENALI_PHY_1201_DATA    0x12c4
#define    DENALI_PHY_1202_DATA    0x12c8
#define    DENALI_PHY_1203_DATA    0x12cc
#define    DENALI_PHY_1204_DATA    0x12d0
#define    DENALI_PHY_1205_DATA    0x12d4
#define    DENALI_PHY_1206_DATA    0x12d8
#define    DENALI_PHY_1207_DATA    0x12dc
#define    DENALI_PHY_1208_DATA    0x12e0
#define    DENALI_PHY_1209_DATA    0x12e4
#define    DENALI_PHY_1210_DATA    0x12e8
#define    DENALI_PHY_1211_DATA    0x12ec
#define    DENALI_PHY_1212_DATA    0x12f0
#define    DENALI_PHY_1213_DATA    0x12f4
#define    DENALI_PHY_1214_DATA    0x12f8
#define    DENALI_PHY_1215_DATA    0x12fc
#define    DENALI_PHY_1216_DATA    0x1300
#define    DENALI_PHY_1217_DATA    0x1304
#define    DENALI_PHY_1218_DATA    0x1308
#define    DENALI_PHY_1219_DATA    0x130c
#define    DENALI_PHY_1220_DATA    0x1310
#define    DENALI_PHY_1221_DATA    0x1314
#define    DENALI_PHY_1222_DATA    0x1318
#define    DENALI_PHY_1223_DATA    0x131c
#define    DENALI_PHY_1224_DATA    0x1320
#define    DENALI_PHY_1225_DATA    0x1324
#define    DENALI_PHY_1226_DATA    0x1328
#define    DENALI_PHY_1227_DATA    0x132c
#define    DENALI_PHY_1228_DATA    0x1330
#define    DENALI_PHY_1229_DATA    0x1334
#define    DENALI_PHY_1230_DATA    0x1338
#define    DENALI_PHY_1231_DATA    0x133c
#define    DENALI_PHY_1232_DATA    0x1340
#define    DENALI_PHY_1233_DATA    0x1344
#define    DENALI_PHY_1234_DATA    0x1348
#define    DENALI_PHY_1235_DATA    0x134c
#define    DENALI_PHY_1236_DATA    0x1350
#define    DENALI_PHY_1237_DATA    0x1354
#define    DENALI_PHY_1238_DATA    0x1358
#define    DENALI_PHY_1239_DATA    0x135c
#define    DENALI_PHY_1240_DATA    0x1360
#define    DENALI_PHY_1241_DATA    0x1364
#define    DENALI_PHY_1242_DATA    0x1368
#define    DENALI_PHY_1243_DATA    0x136c
#define    DENALI_PHY_1244_DATA    0x1370
#define    DENALI_PHY_1245_DATA    0x1374
#define    DENALI_PHY_1246_DATA    0x1378
#define    DENALI_PHY_1247_DATA    0x137c
#define    DENALI_PHY_1248_DATA    0x1380
#define    DENALI_PHY_1249_DATA    0x1384
#define    DENALI_PHY_1250_DATA    0x1388
#define    DENALI_PHY_1251_DATA    0x138c
#define    DENALI_PHY_1252_DATA    0x1390
#define    DENALI_PHY_1253_DATA    0x1394
#define    DENALI_PHY_1254_DATA    0x1398
#define    DENALI_PHY_1255_DATA    0x139c
#define    DENALI_PHY_1256_DATA    0x13a0
#define    DENALI_PHY_1257_DATA    0x13a4
#define    DENALI_PHY_1258_DATA    0x13a8
#define    DENALI_PHY_1259_DATA    0x13ac
#define    DENALI_PHY_1260_DATA    0x13b0
#define    DENALI_PHY_1261_DATA    0x13b4
#define    DENALI_PHY_1262_DATA    0x13b8
#define    DENALI_PHY_1263_DATA    0x13bc
#define    DENALI_PHY_1264_DATA    0x13c0
#define    DENALI_PHY_1265_DATA    0x13c4
#define    DENALI_PHY_1266_DATA    0x13c8
#define    DENALI_PHY_1267_DATA    0x13cc
#define    DENALI_PHY_1268_DATA    0x13d0
#define    DENALI_PHY_1269_DATA    0x13d4
#define    DENALI_PHY_1270_DATA    0x13d8
#define    DENALI_PHY_1271_DATA    0x13dc
#define    DENALI_PHY_1272_DATA    0x13e0
#define    DENALI_PHY_1273_DATA    0x13e4
#define    DENALI_PHY_1274_DATA    0x13e8
#define    DENALI_PHY_1275_DATA    0x13ec
#define    DENALI_PHY_1276_DATA    0x13f0
#define    DENALI_PHY_1277_DATA    0x13f4
#define    DENALI_PHY_1278_DATA    0x13f8
#define    DENALI_PHY_1279_DATA    0x13fc
#define    DENALI_PHY_1280_DATA    0x1400
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_5_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_5_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_1281_DATA    0x1404
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_5_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1282_DATA    0x1408
    #define    PHY_CLK_BYPASS_OVERRIDE_5_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_5_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_1283_DATA    0x140c
    #define    PHY_SW_WRDQ3_SHIFT_5_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_5_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_5_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_5_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1284_DATA    0x1410
    #define    PHY_SW_WRDQ7_SHIFT_5_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_5_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_5_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_5_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1285_DATA    0x1414
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_5_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_5_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_5_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_5_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1286_DATA    0x1418
    #define    PHY_LPBK_CONTROL_5_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_5_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_5_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1287_DATA    0x141c
    #define    PHY_GATE_DELAY_COMP_DISABLE_5_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_5_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1288_DATA    0x1420
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_5_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1289_DATA    0x1424
    #define    PHY_AUTO_TIMING_MARGIN_OBS_5_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_1290_DATA    0x1428
    #define    PHY_PRBS_PATTERN_START_5_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_5_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_5_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1291_DATA    0x142c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_5_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_5_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_5_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1292_DATA    0x1430
    #define    PHY_X4_VREF_TRAIN_OBS_5_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_5_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_5_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1293_DATA    0x1434
    #define    SC_PHY_SNAP_OBS_REGS_5_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_5_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_1294_DATA    0x1438
    #define    PHY_DFI40_POLARITY_5_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_5_RW_0_3    0x7    //0x02
#define    DENALI_PHY_1295_DATA    0x143c
    #define    PHY_RDLVL_PATT8_5_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_1296_DATA    0x1440
    #define    PHY_RDLVL_PATT9_5_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_1297_DATA    0x1444
    #define    PHY_RDLVL_PATT10_5_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_1298_DATA    0x1448
    #define    PHY_RDLVL_PATT11_5_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_1299_DATA    0x144c
    #define    PHY_RDLVL_PATT12_5_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_1300_DATA    0x1450
    #define    PHY_RDLVL_PATT13_5_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_1301_DATA    0x1454
    #define    PHY_RDLVL_PATT14_5_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_1302_DATA    0x1458
    #define    PHY_RDLVL_PATT15_5_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_1303_DATA    0x145c
    #define    PHY_RDLVL_PATT0_3_MASK_5_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1304_DATA    0x1460
    #define    PHY_RDLVL_PATT8_11_MASK_5_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_1305_DATA    0x1464
    #define    PHY_RDLVL_PATT12_15_MASK_5_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_1306_DATA    0x1468
    #define    PHY_RDDQ_ENC_OBS_SELECT_5_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_5_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_5_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_5_RW_0_3    0x7    //0x00
#define    DENALI_PHY_1307_DATA    0x146c
    #define    PHY_FIFO_PTR_OBS_SELECT_5_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_5_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_5_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_5_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1308_DATA    0x1470
    #define    PHY_WRLVL_CAPTURE_CNT_5_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_5_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_5_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_5_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1309_DATA    0x1474
    #define    PHY_GTLVL_UPDT_WAIT_CNT_5_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_5_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_5_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_5_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1310_DATA    0x1478
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_5_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_5_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_5_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_5_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_1311_DATA    0x147c
    #define    PHY_RDLVL_DATA_SWIZZLE_5_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_5_RW_0_8    0xff    //0x00
#define    DENALI_PHY_1312_DATA    0x1480
    #define    PHY_WDQLVL_PATT_5_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_5_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_5_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1313_DATA    0x1484
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_5_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_5_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_5_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_1314_DATA    0x1488
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_5_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_5_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_5_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1315_DATA    0x148c
    #define    PHY_WDQLVL_DATADM_MASK_5_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_1316_DATA    0x1490
    #define    PHY_USER_PATT0_5_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1317_DATA    0x1494
    #define    PHY_USER_PATT1_5_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1318_DATA    0x1498
    #define    PHY_USER_PATT2_5_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1319_DATA    0x149c
    #define    PHY_USER_PATT3_5_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1320_DATA    0x14a0
    #define    PHY_NTP_MULT_TRAIN_5_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_5_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_1321_DATA    0x14a4
    #define    PHY_NTP_PERIOD_THRESHOLD_5_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_5_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_1322_DATA    0x14a8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_5_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_5_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_1323_DATA    0x14ac
    #define    PHY_FIFO_PTR_OBS_5_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_5_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_1324_DATA    0x14b0
    #define    PHY_LPBK_RESULT_OBS_5_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1325_DATA    0x14b4
    #define    PHY_MASTER_DLY_LOCK_OBS_5_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_5_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_1326_DATA    0x14b8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_5_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_5_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_5_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_5_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_1327_DATA    0x14bc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_5_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_5_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_5_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1328_DATA    0x14c0
    #define    PHY_WR_SHIFT_OBS_5_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_5_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_5_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1329_DATA    0x14c4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_5_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_5_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1330_DATA    0x14c8
    #define    PHY_WRLVL_STATUS_OBS_5_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_1331_DATA    0x14cc
    #define    PHY_WRLVL_ERROR_OBS_5_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1332_DATA    0x14d0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_5_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_5_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_1333_DATA    0x14d4
    #define    PHY_GTLVL_STATUS_OBS_5_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_1334_DATA    0x14d8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_5_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_5_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1335_DATA    0x14dc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_5_RD_0_2    0x3    //0x00
#define    DENALI_PHY_1336_DATA    0x14e0
    #define    PHY_RDLVL_STATUS_OBS_5_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1337_DATA    0x14e4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_5_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_5_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1338_DATA    0x14e8
    #define    PHY_WDQLVL_STATUS_OBS_5_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1339_DATA    0x14ec
    #define    PHY_DQS_RATIO_X8_5_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_5_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_5_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1340_DATA    0x14f0
    #define    PHY_DDL_MODE_5_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_1341_DATA    0x14f4
    #define    PHY_DDL_MASK_5_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1342_DATA    0x14f8
    #define    PHY_DDL_TEST_OBS_5_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1343_DATA    0x14fc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_5_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1344_DATA    0x1500
    #define    PHY_RX_CAL_DQS_5_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_5_RW_0_8    0xff    //0x04
#define    DENALI_PHY_1345_DATA    0x1504
    #define    PHY_RX_CAL_X4_FDBK_5_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_5_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1346_DATA    0x1508
    #define    PHY_STATIC_TOG_DISABLE_5_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_5_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_5_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1347_DATA    0x150c
    #define    PHY_DFE_EN_5_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_5_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_5_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_5_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1348_DATA    0x1510
    #define    PHY_DATA_DC_ADJUST_START_5_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_5_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_5_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_5_RW_0_8    0xff    //0x08
#define    DENALI_PHY_1349_DATA    0x1514
    #define    PHY_DATA_DC_CAL_POLARITY_5_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_5_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_5_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_5_RW_0_8    0xff    //0x10
#define    DENALI_PHY_1350_DATA    0x1518
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_5_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_5_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_5_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_5_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1351_DATA    0x151c
    #define    PHY_SLICE_PWR_RDC_DISABLE_5_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_5_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_5_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_1352_DATA    0x1520
    #define    PHY_DQS_TSEL_ENABLE_5_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_5_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_5_RW_0_3    0x7    //0x01
#define    DENALI_PHY_1353_DATA    0x1524
    #define    PHY_VREF_INITIAL_START_POINT_5_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_5_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_5_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_1354_DATA    0x1528
    #define    PHY_NTP_WDQ_STEP_SIZE_5_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_5_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_5_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_5_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_1355_DATA    0x152c
    #define    PHY_NTP_WDQ_STOP_5_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_5_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1356_DATA    0x1530
    #define    PHY_FAST_LVL_EN_5_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_5_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_5_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1357_DATA    0x1534
    #define    PHY_PAD_RX_DCD_2_5_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_5_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_5_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_5_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1358_DATA    0x1538
    #define    PHY_PAD_RX_DCD_6_5_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_5_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_5_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_5_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1359_DATA    0x153c
    #define    PHY_PAD_DQS_RX_DCD_5_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_5_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_5_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1360_DATA    0x1540
    #define    PHY_PAD_DSLICE_IO_CFG_5_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1361_DATA    0x1544
    #define    PHY_RDDQ1_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1362_DATA    0x1548
    #define    PHY_RDDQ3_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1363_DATA    0x154c
    #define    PHY_RDDQ5_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1364_DATA    0x1550
    #define    PHY_RDDQ7_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1365_DATA    0x1554
    #define    PHY_RX_CAL_ALL_DLY_5_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_5_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1366_DATA    0x1558
    #define    PHY_RX_OFF_FIRST_STEP_5_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_5_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_5_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_5_RW_0_8    0xff    //0x03
#define    DENALI_PHY_1367_DATA    0x155c
    #define    PHY_DATA_DC_CAL_CLK_SEL_5_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_5_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_5_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_5_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1368_DATA    0x1560
    #define    PHY_DQS_OE_TIMING_5_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_5_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_5_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_5_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1369_DATA    0x1564
    #define    PHY_DQS_TSEL_WR_TIMING_5_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_5_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_5_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1370_DATA    0x1568
    #define    PHY_PAD_VREF_CTRL_DQ_5_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_5_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_1371_DATA    0x156c
    #define    PHY_DQ_IE_TIMING_5_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_5_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_5_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_1372_DATA    0x1570
    #define    PHY_DBI_MODE_5_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_5_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_5_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_5_RW_0_8    0xff    //0x80
#define    DENALI_PHY_1373_DATA    0x1574
    #define    PHY_RDDATA_EN_TSEL_DLY_5_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_5_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_5_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_5_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1374_DATA    0x1578
    #define    PHY_MASTER_DELAY_STEP_5_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_5_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_5_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1375_DATA    0x157c
    #define    PHY_WRLVL_DLY_STEP_5_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_5_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_5_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_5_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1376_DATA    0x1580
    #define    PHY_GTLVL_RESP_WAIT_CNT_5_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_5_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_5_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_5_RW_0_4    0xf    //0x01
#define    DENALI_PHY_1377_DATA    0x1584
    #define    PHY_GTLVL_FINAL_STEP_5_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_5_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_1378_DATA    0x1588
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_5_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_5_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_5_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1379_DATA    0x158c
    #define    PHY_X4_DQ_IE_TIMING_5_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_5_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_5_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_5_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1380_DATA    0x1590
    #define    PHY_X4_DQS_IE_TIMING_5_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_5_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_5_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_5_RW_0_8    0xff    //0x51
#define    DENALI_PHY_1381_DATA    0x1594
    #define    PHY_RDLVL_DLY_STEP_5_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_5_RW_0_4    0xf    //0x06
#define    DENALI_PHY_1382_DATA    0x1598
    #define    PHY_RDLVL_MAX_EDGE_5_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_1383_DATA    0x159c
    #define    PHY_DATA_DC_INIT_DISABLE_5_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_5_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_5_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1384_DATA    0x15a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_5_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1385_DATA    0x15a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_5_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_5_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_5_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_5_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1386_DATA    0x15a8
    #define    PHY_RDDATA_EN_DLY_5_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_5_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_1387_DATA    0x15ac
    #define    PHY_DQ_DM_SWIZZLE0_5_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_1388_DATA    0x15b0
    #define    PHY_DQ_DM_SWIZZLE1_5_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1389_DATA    0x15b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_5_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_5_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1390_DATA    0x15b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_5_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_5_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1391_DATA    0x15bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_5_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_5_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1392_DATA    0x15c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_5_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_5_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1393_DATA    0x15c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_5_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1394_DATA    0x15c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_5_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_5_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1395_DATA    0x15cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1396_DATA    0x15d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1397_DATA    0x15d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1398_DATA    0x15d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1399_DATA    0x15dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1400_DATA    0x15e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1401_DATA    0x15e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1402_DATA    0x15e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1403_DATA    0x15ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1404_DATA    0x15f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1405_DATA    0x15f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1406_DATA    0x15f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1407_DATA    0x15fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1408_DATA    0x1600
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1409_DATA    0x1604
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1410_DATA    0x1608
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1411_DATA    0x160c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1412_DATA    0x1610
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1413_DATA    0x1614
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_5_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_5_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_5_RW_0_4    0xf    //0x02
#define    DENALI_PHY_1414_DATA    0x1618
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_5_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1415_DATA    0x161c
    #define    PHY_GTLVL_LAT_ADJ_START_5_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1416_DATA    0x1620
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_5_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_5_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1417_DATA    0x1624
    #define    PHY_X4_NTP_PASS_5_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_5_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_5_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1418_DATA    0x1628
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_5_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1419_DATA    0x162c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_5_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_5_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_1420_DATA    0x1630
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_5_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_5_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_1421_DATA    0x1634
    #define    PHY_X4_GTLVL_LAT_ADJ_START_5_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_5_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_5_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1422_DATA    0x1638
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_5_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1423_DATA    0x163c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_5_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_5_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_5_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_5_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1424_DATA    0x1640
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_5_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_5_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_5_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_5_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1425_DATA    0x1644
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_5_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_5_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_5_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1426_DATA    0x1648
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_5_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_5_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_5_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1427_DATA    0x164c
    #define    PHY_X4_DQS_FFE_5_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_5_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_5_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_5_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1428_DATA    0x1650
    #define    PHY_RX_CAL_DQ0_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1429_DATA    0x1654
    #define    PHY_RX_CAL_DQ1_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1430_DATA    0x1658
    #define    PHY_RX_CAL_DQ2_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1431_DATA    0x165c
    #define    PHY_RX_CAL_DQ3_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1432_DATA    0x1660
    #define    PHY_RX_CAL_DQ4_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1433_DATA    0x1664
    #define    PHY_RX_CAL_DQ5_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1434_DATA    0x1668
    #define    PHY_RX_CAL_DQ6_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1435_DATA    0x166c
    #define    PHY_RX_CAL_DQ7_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1436_DATA    0x1670
    #define    PHY_RX_CAL_DM_5_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1437_DATA    0x1674
#define    DENALI_PHY_1438_DATA    0x1678
#define    DENALI_PHY_1439_DATA    0x167c
#define    DENALI_PHY_1440_DATA    0x1680
#define    DENALI_PHY_1441_DATA    0x1684
#define    DENALI_PHY_1442_DATA    0x1688
#define    DENALI_PHY_1443_DATA    0x168c
#define    DENALI_PHY_1444_DATA    0x1690
#define    DENALI_PHY_1445_DATA    0x1694
#define    DENALI_PHY_1446_DATA    0x1698
#define    DENALI_PHY_1447_DATA    0x169c
#define    DENALI_PHY_1448_DATA    0x16a0
#define    DENALI_PHY_1449_DATA    0x16a4
#define    DENALI_PHY_1450_DATA    0x16a8
#define    DENALI_PHY_1451_DATA    0x16ac
#define    DENALI_PHY_1452_DATA    0x16b0
#define    DENALI_PHY_1453_DATA    0x16b4
#define    DENALI_PHY_1454_DATA    0x16b8
#define    DENALI_PHY_1455_DATA    0x16bc
#define    DENALI_PHY_1456_DATA    0x16c0
#define    DENALI_PHY_1457_DATA    0x16c4
#define    DENALI_PHY_1458_DATA    0x16c8
#define    DENALI_PHY_1459_DATA    0x16cc
#define    DENALI_PHY_1460_DATA    0x16d0
#define    DENALI_PHY_1461_DATA    0x16d4
#define    DENALI_PHY_1462_DATA    0x16d8
#define    DENALI_PHY_1463_DATA    0x16dc
#define    DENALI_PHY_1464_DATA    0x16e0
#define    DENALI_PHY_1465_DATA    0x16e4
#define    DENALI_PHY_1466_DATA    0x16e8
#define    DENALI_PHY_1467_DATA    0x16ec
#define    DENALI_PHY_1468_DATA    0x16f0
#define    DENALI_PHY_1469_DATA    0x16f4
#define    DENALI_PHY_1470_DATA    0x16f8
#define    DENALI_PHY_1471_DATA    0x16fc
#define    DENALI_PHY_1472_DATA    0x1700
#define    DENALI_PHY_1473_DATA    0x1704
#define    DENALI_PHY_1474_DATA    0x1708
#define    DENALI_PHY_1475_DATA    0x170c
#define    DENALI_PHY_1476_DATA    0x1710
#define    DENALI_PHY_1477_DATA    0x1714
#define    DENALI_PHY_1478_DATA    0x1718
#define    DENALI_PHY_1479_DATA    0x171c
#define    DENALI_PHY_1480_DATA    0x1720
#define    DENALI_PHY_1481_DATA    0x1724
#define    DENALI_PHY_1482_DATA    0x1728
#define    DENALI_PHY_1483_DATA    0x172c
#define    DENALI_PHY_1484_DATA    0x1730
#define    DENALI_PHY_1485_DATA    0x1734
#define    DENALI_PHY_1486_DATA    0x1738
#define    DENALI_PHY_1487_DATA    0x173c
#define    DENALI_PHY_1488_DATA    0x1740
#define    DENALI_PHY_1489_DATA    0x1744
#define    DENALI_PHY_1490_DATA    0x1748
#define    DENALI_PHY_1491_DATA    0x174c
#define    DENALI_PHY_1492_DATA    0x1750
#define    DENALI_PHY_1493_DATA    0x1754
#define    DENALI_PHY_1494_DATA    0x1758
#define    DENALI_PHY_1495_DATA    0x175c
#define    DENALI_PHY_1496_DATA    0x1760
#define    DENALI_PHY_1497_DATA    0x1764
#define    DENALI_PHY_1498_DATA    0x1768
#define    DENALI_PHY_1499_DATA    0x176c
#define    DENALI_PHY_1500_DATA    0x1770
#define    DENALI_PHY_1501_DATA    0x1774
#define    DENALI_PHY_1502_DATA    0x1778
#define    DENALI_PHY_1503_DATA    0x177c
#define    DENALI_PHY_1504_DATA    0x1780
#define    DENALI_PHY_1505_DATA    0x1784
#define    DENALI_PHY_1506_DATA    0x1788
#define    DENALI_PHY_1507_DATA    0x178c
#define    DENALI_PHY_1508_DATA    0x1790
#define    DENALI_PHY_1509_DATA    0x1794
#define    DENALI_PHY_1510_DATA    0x1798
#define    DENALI_PHY_1511_DATA    0x179c
#define    DENALI_PHY_1512_DATA    0x17a0
#define    DENALI_PHY_1513_DATA    0x17a4
#define    DENALI_PHY_1514_DATA    0x17a8
#define    DENALI_PHY_1515_DATA    0x17ac
#define    DENALI_PHY_1516_DATA    0x17b0
#define    DENALI_PHY_1517_DATA    0x17b4
#define    DENALI_PHY_1518_DATA    0x17b8
#define    DENALI_PHY_1519_DATA    0x17bc
#define    DENALI_PHY_1520_DATA    0x17c0
#define    DENALI_PHY_1521_DATA    0x17c4
#define    DENALI_PHY_1522_DATA    0x17c8
#define    DENALI_PHY_1523_DATA    0x17cc
#define    DENALI_PHY_1524_DATA    0x17d0
#define    DENALI_PHY_1525_DATA    0x17d4
#define    DENALI_PHY_1526_DATA    0x17d8
#define    DENALI_PHY_1527_DATA    0x17dc
#define    DENALI_PHY_1528_DATA    0x17e0
#define    DENALI_PHY_1529_DATA    0x17e4
#define    DENALI_PHY_1530_DATA    0x17e8
#define    DENALI_PHY_1531_DATA    0x17ec
#define    DENALI_PHY_1532_DATA    0x17f0
#define    DENALI_PHY_1533_DATA    0x17f4
#define    DENALI_PHY_1534_DATA    0x17f8
#define    DENALI_PHY_1535_DATA    0x17fc
#define    DENALI_PHY_1536_DATA    0x1800
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_6_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_6_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_1537_DATA    0x1804
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_6_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1538_DATA    0x1808
    #define    PHY_CLK_BYPASS_OVERRIDE_6_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_6_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_1539_DATA    0x180c
    #define    PHY_SW_WRDQ3_SHIFT_6_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_6_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_6_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_6_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1540_DATA    0x1810
    #define    PHY_SW_WRDQ7_SHIFT_6_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_6_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_6_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_6_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1541_DATA    0x1814
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_6_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_6_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_6_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_6_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1542_DATA    0x1818
    #define    PHY_LPBK_CONTROL_6_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_6_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_6_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1543_DATA    0x181c
    #define    PHY_GATE_DELAY_COMP_DISABLE_6_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_6_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1544_DATA    0x1820
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_6_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1545_DATA    0x1824
    #define    PHY_AUTO_TIMING_MARGIN_OBS_6_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_1546_DATA    0x1828
    #define    PHY_PRBS_PATTERN_START_6_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_6_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_6_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1547_DATA    0x182c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_6_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_6_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_6_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1548_DATA    0x1830
    #define    PHY_X4_VREF_TRAIN_OBS_6_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_6_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_6_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1549_DATA    0x1834
    #define    SC_PHY_SNAP_OBS_REGS_6_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_6_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_1550_DATA    0x1838
    #define    PHY_DFI40_POLARITY_6_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_6_RW_0_3    0x7    //0x02
#define    DENALI_PHY_1551_DATA    0x183c
    #define    PHY_RDLVL_PATT8_6_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_1552_DATA    0x1840
    #define    PHY_RDLVL_PATT9_6_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_1553_DATA    0x1844
    #define    PHY_RDLVL_PATT10_6_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_1554_DATA    0x1848
    #define    PHY_RDLVL_PATT11_6_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_1555_DATA    0x184c
    #define    PHY_RDLVL_PATT12_6_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_1556_DATA    0x1850
    #define    PHY_RDLVL_PATT13_6_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_1557_DATA    0x1854
    #define    PHY_RDLVL_PATT14_6_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_1558_DATA    0x1858
    #define    PHY_RDLVL_PATT15_6_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_1559_DATA    0x185c
    #define    PHY_RDLVL_PATT0_3_MASK_6_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1560_DATA    0x1860
    #define    PHY_RDLVL_PATT8_11_MASK_6_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_1561_DATA    0x1864
    #define    PHY_RDLVL_PATT12_15_MASK_6_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_1562_DATA    0x1868
    #define    PHY_RDDQ_ENC_OBS_SELECT_6_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_6_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_6_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_6_RW_0_3    0x7    //0x00
#define    DENALI_PHY_1563_DATA    0x186c
    #define    PHY_FIFO_PTR_OBS_SELECT_6_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_6_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_6_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_6_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1564_DATA    0x1870
    #define    PHY_WRLVL_CAPTURE_CNT_6_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_6_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_6_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_6_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1565_DATA    0x1874
    #define    PHY_GTLVL_UPDT_WAIT_CNT_6_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_6_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_6_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_6_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1566_DATA    0x1878
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_6_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_6_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_6_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_6_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_1567_DATA    0x187c
    #define    PHY_RDLVL_DATA_SWIZZLE_6_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_6_RW_0_8    0xff    //0x00
#define    DENALI_PHY_1568_DATA    0x1880
    #define    PHY_WDQLVL_PATT_6_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_6_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_6_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1569_DATA    0x1884
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_6_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_6_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_6_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_1570_DATA    0x1888
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_6_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_6_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_6_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1571_DATA    0x188c
    #define    PHY_WDQLVL_DATADM_MASK_6_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_1572_DATA    0x1890
    #define    PHY_USER_PATT0_6_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1573_DATA    0x1894
    #define    PHY_USER_PATT1_6_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1574_DATA    0x1898
    #define    PHY_USER_PATT2_6_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1575_DATA    0x189c
    #define    PHY_USER_PATT3_6_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1576_DATA    0x18a0
    #define    PHY_NTP_MULT_TRAIN_6_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_6_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_1577_DATA    0x18a4
    #define    PHY_NTP_PERIOD_THRESHOLD_6_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_6_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_1578_DATA    0x18a8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_6_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_6_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_1579_DATA    0x18ac
    #define    PHY_FIFO_PTR_OBS_6_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_6_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_1580_DATA    0x18b0
    #define    PHY_LPBK_RESULT_OBS_6_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1581_DATA    0x18b4
    #define    PHY_MASTER_DLY_LOCK_OBS_6_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_6_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_1582_DATA    0x18b8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_6_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_6_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_6_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_6_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_1583_DATA    0x18bc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_6_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_6_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_6_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1584_DATA    0x18c0
    #define    PHY_WR_SHIFT_OBS_6_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_6_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_6_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1585_DATA    0x18c4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_6_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_6_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1586_DATA    0x18c8
    #define    PHY_WRLVL_STATUS_OBS_6_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_1587_DATA    0x18cc
    #define    PHY_WRLVL_ERROR_OBS_6_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1588_DATA    0x18d0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_6_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_6_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_1589_DATA    0x18d4
    #define    PHY_GTLVL_STATUS_OBS_6_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_1590_DATA    0x18d8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_6_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_6_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1591_DATA    0x18dc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_6_RD_0_2    0x3    //0x00
#define    DENALI_PHY_1592_DATA    0x18e0
    #define    PHY_RDLVL_STATUS_OBS_6_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1593_DATA    0x18e4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_6_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_6_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1594_DATA    0x18e8
    #define    PHY_WDQLVL_STATUS_OBS_6_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1595_DATA    0x18ec
    #define    PHY_DQS_RATIO_X8_6_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_6_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_6_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1596_DATA    0x18f0
    #define    PHY_DDL_MODE_6_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_1597_DATA    0x18f4
    #define    PHY_DDL_MASK_6_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1598_DATA    0x18f8
    #define    PHY_DDL_TEST_OBS_6_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1599_DATA    0x18fc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_6_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1600_DATA    0x1900
    #define    PHY_RX_CAL_DQS_6_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_6_RW_0_8    0xff    //0x04
#define    DENALI_PHY_1601_DATA    0x1904
    #define    PHY_RX_CAL_X4_FDBK_6_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_6_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1602_DATA    0x1908
    #define    PHY_STATIC_TOG_DISABLE_6_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_6_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_6_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1603_DATA    0x190c
    #define    PHY_DFE_EN_6_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_6_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_6_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_6_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1604_DATA    0x1910
    #define    PHY_DATA_DC_ADJUST_START_6_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_6_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_6_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_6_RW_0_8    0xff    //0x08
#define    DENALI_PHY_1605_DATA    0x1914
    #define    PHY_DATA_DC_CAL_POLARITY_6_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_6_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_6_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_6_RW_0_8    0xff    //0x10
#define    DENALI_PHY_1606_DATA    0x1918
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_6_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_6_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_6_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_6_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1607_DATA    0x191c
    #define    PHY_SLICE_PWR_RDC_DISABLE_6_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_6_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_6_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_1608_DATA    0x1920
    #define    PHY_DQS_TSEL_ENABLE_6_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_6_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_6_RW_0_3    0x7    //0x01
#define    DENALI_PHY_1609_DATA    0x1924
    #define    PHY_VREF_INITIAL_START_POINT_6_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_6_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_6_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_1610_DATA    0x1928
    #define    PHY_NTP_WDQ_STEP_SIZE_6_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_6_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_6_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_6_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_1611_DATA    0x192c
    #define    PHY_NTP_WDQ_STOP_6_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_6_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1612_DATA    0x1930
    #define    PHY_FAST_LVL_EN_6_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_6_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_6_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1613_DATA    0x1934
    #define    PHY_PAD_RX_DCD_2_6_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_6_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_6_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_6_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1614_DATA    0x1938
    #define    PHY_PAD_RX_DCD_6_6_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_6_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_6_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_6_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1615_DATA    0x193c
    #define    PHY_PAD_DQS_RX_DCD_6_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_6_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_6_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1616_DATA    0x1940
    #define    PHY_PAD_DSLICE_IO_CFG_6_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1617_DATA    0x1944
    #define    PHY_RDDQ1_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1618_DATA    0x1948
    #define    PHY_RDDQ3_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1619_DATA    0x194c
    #define    PHY_RDDQ5_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1620_DATA    0x1950
    #define    PHY_RDDQ7_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1621_DATA    0x1954
    #define    PHY_RX_CAL_ALL_DLY_6_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_6_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1622_DATA    0x1958
    #define    PHY_RX_OFF_FIRST_STEP_6_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_6_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_6_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_6_RW_0_8    0xff    //0x03
#define    DENALI_PHY_1623_DATA    0x195c
    #define    PHY_DATA_DC_CAL_CLK_SEL_6_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_6_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_6_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_6_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1624_DATA    0x1960
    #define    PHY_DQS_OE_TIMING_6_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_6_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_6_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_6_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1625_DATA    0x1964
    #define    PHY_DQS_TSEL_WR_TIMING_6_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_6_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_6_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1626_DATA    0x1968
    #define    PHY_PAD_VREF_CTRL_DQ_6_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_6_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_1627_DATA    0x196c
    #define    PHY_DQ_IE_TIMING_6_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_6_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_6_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_1628_DATA    0x1970
    #define    PHY_DBI_MODE_6_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_6_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_6_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_6_RW_0_8    0xff    //0x80
#define    DENALI_PHY_1629_DATA    0x1974
    #define    PHY_RDDATA_EN_TSEL_DLY_6_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_6_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_6_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_6_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1630_DATA    0x1978
    #define    PHY_MASTER_DELAY_STEP_6_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_6_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_6_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1631_DATA    0x197c
    #define    PHY_WRLVL_DLY_STEP_6_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_6_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_6_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_6_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1632_DATA    0x1980
    #define    PHY_GTLVL_RESP_WAIT_CNT_6_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_6_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_6_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_6_RW_0_4    0xf    //0x01
#define    DENALI_PHY_1633_DATA    0x1984
    #define    PHY_GTLVL_FINAL_STEP_6_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_6_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_1634_DATA    0x1988
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_6_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_6_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_6_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1635_DATA    0x198c
    #define    PHY_X4_DQ_IE_TIMING_6_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_6_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_6_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_6_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1636_DATA    0x1990
    #define    PHY_X4_DQS_IE_TIMING_6_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_6_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_6_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_6_RW_0_8    0xff    //0x51
#define    DENALI_PHY_1637_DATA    0x1994
    #define    PHY_RDLVL_DLY_STEP_6_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_6_RW_0_4    0xf    //0x06
#define    DENALI_PHY_1638_DATA    0x1998
    #define    PHY_RDLVL_MAX_EDGE_6_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_1639_DATA    0x199c
    #define    PHY_DATA_DC_INIT_DISABLE_6_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_6_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_6_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1640_DATA    0x19a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_6_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1641_DATA    0x19a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_6_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_6_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_6_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_6_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1642_DATA    0x19a8
    #define    PHY_RDDATA_EN_DLY_6_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_6_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_1643_DATA    0x19ac
    #define    PHY_DQ_DM_SWIZZLE0_6_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_1644_DATA    0x19b0
    #define    PHY_DQ_DM_SWIZZLE1_6_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1645_DATA    0x19b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_6_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_6_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1646_DATA    0x19b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_6_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_6_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1647_DATA    0x19bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_6_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_6_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1648_DATA    0x19c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_6_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_6_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1649_DATA    0x19c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_6_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1650_DATA    0x19c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_6_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_6_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1651_DATA    0x19cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1652_DATA    0x19d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1653_DATA    0x19d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1654_DATA    0x19d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1655_DATA    0x19dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1656_DATA    0x19e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1657_DATA    0x19e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1658_DATA    0x19e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1659_DATA    0x19ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1660_DATA    0x19f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1661_DATA    0x19f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1662_DATA    0x19f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1663_DATA    0x19fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1664_DATA    0x1a00
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1665_DATA    0x1a04
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1666_DATA    0x1a08
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1667_DATA    0x1a0c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1668_DATA    0x1a10
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1669_DATA    0x1a14
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_6_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_6_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_6_RW_0_4    0xf    //0x02
#define    DENALI_PHY_1670_DATA    0x1a18
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_6_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1671_DATA    0x1a1c
    #define    PHY_GTLVL_LAT_ADJ_START_6_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1672_DATA    0x1a20
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_6_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_6_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1673_DATA    0x1a24
    #define    PHY_X4_NTP_PASS_6_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_6_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_6_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1674_DATA    0x1a28
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_6_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1675_DATA    0x1a2c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_6_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_6_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_1676_DATA    0x1a30
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_6_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_6_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_1677_DATA    0x1a34
    #define    PHY_X4_GTLVL_LAT_ADJ_START_6_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_6_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_6_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1678_DATA    0x1a38
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_6_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1679_DATA    0x1a3c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_6_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_6_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_6_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_6_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1680_DATA    0x1a40
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_6_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_6_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_6_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_6_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1681_DATA    0x1a44
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_6_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_6_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_6_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1682_DATA    0x1a48
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_6_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_6_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_6_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1683_DATA    0x1a4c
    #define    PHY_X4_DQS_FFE_6_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_6_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_6_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_6_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1684_DATA    0x1a50
    #define    PHY_RX_CAL_DQ0_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1685_DATA    0x1a54
    #define    PHY_RX_CAL_DQ1_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1686_DATA    0x1a58
    #define    PHY_RX_CAL_DQ2_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1687_DATA    0x1a5c
    #define    PHY_RX_CAL_DQ3_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1688_DATA    0x1a60
    #define    PHY_RX_CAL_DQ4_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1689_DATA    0x1a64
    #define    PHY_RX_CAL_DQ5_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1690_DATA    0x1a68
    #define    PHY_RX_CAL_DQ6_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1691_DATA    0x1a6c
    #define    PHY_RX_CAL_DQ7_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1692_DATA    0x1a70
    #define    PHY_RX_CAL_DM_6_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1693_DATA    0x1a74
#define    DENALI_PHY_1694_DATA    0x1a78
#define    DENALI_PHY_1695_DATA    0x1a7c
#define    DENALI_PHY_1696_DATA    0x1a80
#define    DENALI_PHY_1697_DATA    0x1a84
#define    DENALI_PHY_1698_DATA    0x1a88
#define    DENALI_PHY_1699_DATA    0x1a8c
#define    DENALI_PHY_1700_DATA    0x1a90
#define    DENALI_PHY_1701_DATA    0x1a94
#define    DENALI_PHY_1702_DATA    0x1a98
#define    DENALI_PHY_1703_DATA    0x1a9c
#define    DENALI_PHY_1704_DATA    0x1aa0
#define    DENALI_PHY_1705_DATA    0x1aa4
#define    DENALI_PHY_1706_DATA    0x1aa8
#define    DENALI_PHY_1707_DATA    0x1aac
#define    DENALI_PHY_1708_DATA    0x1ab0
#define    DENALI_PHY_1709_DATA    0x1ab4
#define    DENALI_PHY_1710_DATA    0x1ab8
#define    DENALI_PHY_1711_DATA    0x1abc
#define    DENALI_PHY_1712_DATA    0x1ac0
#define    DENALI_PHY_1713_DATA    0x1ac4
#define    DENALI_PHY_1714_DATA    0x1ac8
#define    DENALI_PHY_1715_DATA    0x1acc
#define    DENALI_PHY_1716_DATA    0x1ad0
#define    DENALI_PHY_1717_DATA    0x1ad4
#define    DENALI_PHY_1718_DATA    0x1ad8
#define    DENALI_PHY_1719_DATA    0x1adc
#define    DENALI_PHY_1720_DATA    0x1ae0
#define    DENALI_PHY_1721_DATA    0x1ae4
#define    DENALI_PHY_1722_DATA    0x1ae8
#define    DENALI_PHY_1723_DATA    0x1aec
#define    DENALI_PHY_1724_DATA    0x1af0
#define    DENALI_PHY_1725_DATA    0x1af4
#define    DENALI_PHY_1726_DATA    0x1af8
#define    DENALI_PHY_1727_DATA    0x1afc
#define    DENALI_PHY_1728_DATA    0x1b00
#define    DENALI_PHY_1729_DATA    0x1b04
#define    DENALI_PHY_1730_DATA    0x1b08
#define    DENALI_PHY_1731_DATA    0x1b0c
#define    DENALI_PHY_1732_DATA    0x1b10
#define    DENALI_PHY_1733_DATA    0x1b14
#define    DENALI_PHY_1734_DATA    0x1b18
#define    DENALI_PHY_1735_DATA    0x1b1c
#define    DENALI_PHY_1736_DATA    0x1b20
#define    DENALI_PHY_1737_DATA    0x1b24
#define    DENALI_PHY_1738_DATA    0x1b28
#define    DENALI_PHY_1739_DATA    0x1b2c
#define    DENALI_PHY_1740_DATA    0x1b30
#define    DENALI_PHY_1741_DATA    0x1b34
#define    DENALI_PHY_1742_DATA    0x1b38
#define    DENALI_PHY_1743_DATA    0x1b3c
#define    DENALI_PHY_1744_DATA    0x1b40
#define    DENALI_PHY_1745_DATA    0x1b44
#define    DENALI_PHY_1746_DATA    0x1b48
#define    DENALI_PHY_1747_DATA    0x1b4c
#define    DENALI_PHY_1748_DATA    0x1b50
#define    DENALI_PHY_1749_DATA    0x1b54
#define    DENALI_PHY_1750_DATA    0x1b58
#define    DENALI_PHY_1751_DATA    0x1b5c
#define    DENALI_PHY_1752_DATA    0x1b60
#define    DENALI_PHY_1753_DATA    0x1b64
#define    DENALI_PHY_1754_DATA    0x1b68
#define    DENALI_PHY_1755_DATA    0x1b6c
#define    DENALI_PHY_1756_DATA    0x1b70
#define    DENALI_PHY_1757_DATA    0x1b74
#define    DENALI_PHY_1758_DATA    0x1b78
#define    DENALI_PHY_1759_DATA    0x1b7c
#define    DENALI_PHY_1760_DATA    0x1b80
#define    DENALI_PHY_1761_DATA    0x1b84
#define    DENALI_PHY_1762_DATA    0x1b88
#define    DENALI_PHY_1763_DATA    0x1b8c
#define    DENALI_PHY_1764_DATA    0x1b90
#define    DENALI_PHY_1765_DATA    0x1b94
#define    DENALI_PHY_1766_DATA    0x1b98
#define    DENALI_PHY_1767_DATA    0x1b9c
#define    DENALI_PHY_1768_DATA    0x1ba0
#define    DENALI_PHY_1769_DATA    0x1ba4
#define    DENALI_PHY_1770_DATA    0x1ba8
#define    DENALI_PHY_1771_DATA    0x1bac
#define    DENALI_PHY_1772_DATA    0x1bb0
#define    DENALI_PHY_1773_DATA    0x1bb4
#define    DENALI_PHY_1774_DATA    0x1bb8
#define    DENALI_PHY_1775_DATA    0x1bbc
#define    DENALI_PHY_1776_DATA    0x1bc0
#define    DENALI_PHY_1777_DATA    0x1bc4
#define    DENALI_PHY_1778_DATA    0x1bc8
#define    DENALI_PHY_1779_DATA    0x1bcc
#define    DENALI_PHY_1780_DATA    0x1bd0
#define    DENALI_PHY_1781_DATA    0x1bd4
#define    DENALI_PHY_1782_DATA    0x1bd8
#define    DENALI_PHY_1783_DATA    0x1bdc
#define    DENALI_PHY_1784_DATA    0x1be0
#define    DENALI_PHY_1785_DATA    0x1be4
#define    DENALI_PHY_1786_DATA    0x1be8
#define    DENALI_PHY_1787_DATA    0x1bec
#define    DENALI_PHY_1788_DATA    0x1bf0
#define    DENALI_PHY_1789_DATA    0x1bf4
#define    DENALI_PHY_1790_DATA    0x1bf8
#define    DENALI_PHY_1791_DATA    0x1bfc
#define    DENALI_PHY_1792_DATA    0x1c00
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_7_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_7_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_1793_DATA    0x1c04
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_7_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1794_DATA    0x1c08
    #define    PHY_CLK_BYPASS_OVERRIDE_7_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_7_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_1795_DATA    0x1c0c
    #define    PHY_SW_WRDQ3_SHIFT_7_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_7_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_7_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_7_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1796_DATA    0x1c10
    #define    PHY_SW_WRDQ7_SHIFT_7_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_7_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_7_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_7_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1797_DATA    0x1c14
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_7_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_7_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_7_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_7_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1798_DATA    0x1c18
    #define    PHY_LPBK_CONTROL_7_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_7_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_7_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1799_DATA    0x1c1c
    #define    PHY_GATE_DELAY_COMP_DISABLE_7_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_7_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1800_DATA    0x1c20
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_7_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1801_DATA    0x1c24
    #define    PHY_AUTO_TIMING_MARGIN_OBS_7_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_1802_DATA    0x1c28
    #define    PHY_PRBS_PATTERN_START_7_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_7_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_7_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1803_DATA    0x1c2c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_7_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_7_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_7_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1804_DATA    0x1c30
    #define    PHY_X4_VREF_TRAIN_OBS_7_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_7_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_7_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1805_DATA    0x1c34
    #define    SC_PHY_SNAP_OBS_REGS_7_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_7_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_1806_DATA    0x1c38
    #define    PHY_DFI40_POLARITY_7_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_7_RW_0_3    0x7    //0x02
#define    DENALI_PHY_1807_DATA    0x1c3c
    #define    PHY_RDLVL_PATT8_7_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_1808_DATA    0x1c40
    #define    PHY_RDLVL_PATT9_7_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_1809_DATA    0x1c44
    #define    PHY_RDLVL_PATT10_7_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_1810_DATA    0x1c48
    #define    PHY_RDLVL_PATT11_7_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_1811_DATA    0x1c4c
    #define    PHY_RDLVL_PATT12_7_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_1812_DATA    0x1c50
    #define    PHY_RDLVL_PATT13_7_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_1813_DATA    0x1c54
    #define    PHY_RDLVL_PATT14_7_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_1814_DATA    0x1c58
    #define    PHY_RDLVL_PATT15_7_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_1815_DATA    0x1c5c
    #define    PHY_RDLVL_PATT0_3_MASK_7_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1816_DATA    0x1c60
    #define    PHY_RDLVL_PATT8_11_MASK_7_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_1817_DATA    0x1c64
    #define    PHY_RDLVL_PATT12_15_MASK_7_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_1818_DATA    0x1c68
    #define    PHY_RDDQ_ENC_OBS_SELECT_7_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_7_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_7_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_7_RW_0_3    0x7    //0x00
#define    DENALI_PHY_1819_DATA    0x1c6c
    #define    PHY_FIFO_PTR_OBS_SELECT_7_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_7_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_7_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_7_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1820_DATA    0x1c70
    #define    PHY_WRLVL_CAPTURE_CNT_7_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_7_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_7_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_7_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1821_DATA    0x1c74
    #define    PHY_GTLVL_UPDT_WAIT_CNT_7_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_7_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_7_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_7_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1822_DATA    0x1c78
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_7_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_7_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_7_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_7_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_1823_DATA    0x1c7c
    #define    PHY_RDLVL_DATA_SWIZZLE_7_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_7_RW_0_8    0xff    //0x00
#define    DENALI_PHY_1824_DATA    0x1c80
    #define    PHY_WDQLVL_PATT_7_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_7_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_7_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1825_DATA    0x1c84
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_7_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_7_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_7_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_1826_DATA    0x1c88
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_7_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_7_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_7_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1827_DATA    0x1c8c
    #define    PHY_WDQLVL_DATADM_MASK_7_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_1828_DATA    0x1c90
    #define    PHY_USER_PATT0_7_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1829_DATA    0x1c94
    #define    PHY_USER_PATT1_7_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1830_DATA    0x1c98
    #define    PHY_USER_PATT2_7_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_1831_DATA    0x1c9c
    #define    PHY_USER_PATT3_7_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_1832_DATA    0x1ca0
    #define    PHY_NTP_MULT_TRAIN_7_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_7_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_1833_DATA    0x1ca4
    #define    PHY_NTP_PERIOD_THRESHOLD_7_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_7_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_1834_DATA    0x1ca8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_7_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_7_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_1835_DATA    0x1cac
    #define    PHY_FIFO_PTR_OBS_7_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_7_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_1836_DATA    0x1cb0
    #define    PHY_LPBK_RESULT_OBS_7_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1837_DATA    0x1cb4
    #define    PHY_MASTER_DLY_LOCK_OBS_7_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_7_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_1838_DATA    0x1cb8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_7_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_7_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_7_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_7_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_1839_DATA    0x1cbc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_7_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_7_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_7_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1840_DATA    0x1cc0
    #define    PHY_WR_SHIFT_OBS_7_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_7_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_7_RD_0_8    0xff    //0x00
#define    DENALI_PHY_1841_DATA    0x1cc4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_7_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_7_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1842_DATA    0x1cc8
    #define    PHY_WRLVL_STATUS_OBS_7_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_1843_DATA    0x1ccc
    #define    PHY_WRLVL_ERROR_OBS_7_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1844_DATA    0x1cd0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_7_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_7_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_1845_DATA    0x1cd4
    #define    PHY_GTLVL_STATUS_OBS_7_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_1846_DATA    0x1cd8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_7_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_7_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1847_DATA    0x1cdc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_7_RD_0_2    0x3    //0x00
#define    DENALI_PHY_1848_DATA    0x1ce0
    #define    PHY_RDLVL_STATUS_OBS_7_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1849_DATA    0x1ce4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_7_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_7_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1850_DATA    0x1ce8
    #define    PHY_WDQLVL_STATUS_OBS_7_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1851_DATA    0x1cec
    #define    PHY_DQS_RATIO_X8_7_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_7_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_7_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1852_DATA    0x1cf0
    #define    PHY_DDL_MODE_7_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_1853_DATA    0x1cf4
    #define    PHY_DDL_MASK_7_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1854_DATA    0x1cf8
    #define    PHY_DDL_TEST_OBS_7_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1855_DATA    0x1cfc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_7_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_1856_DATA    0x1d00
    #define    PHY_RX_CAL_DQS_7_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_7_RW_0_8    0xff    //0x04
#define    DENALI_PHY_1857_DATA    0x1d04
    #define    PHY_RX_CAL_X4_FDBK_7_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_7_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_1858_DATA    0x1d08
    #define    PHY_STATIC_TOG_DISABLE_7_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_7_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_7_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1859_DATA    0x1d0c
    #define    PHY_DFE_EN_7_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_7_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_7_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_7_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1860_DATA    0x1d10
    #define    PHY_DATA_DC_ADJUST_START_7_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_7_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_7_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_7_RW_0_8    0xff    //0x08
#define    DENALI_PHY_1861_DATA    0x1d14
    #define    PHY_DATA_DC_CAL_POLARITY_7_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_7_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_7_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_7_RW_0_8    0xff    //0x10
#define    DENALI_PHY_1862_DATA    0x1d18
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_7_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_7_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_7_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_7_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1863_DATA    0x1d1c
    #define    PHY_SLICE_PWR_RDC_DISABLE_7_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_7_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_7_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_1864_DATA    0x1d20
    #define    PHY_DQS_TSEL_ENABLE_7_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_7_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_7_RW_0_3    0x7    //0x01
#define    DENALI_PHY_1865_DATA    0x1d24
    #define    PHY_VREF_INITIAL_START_POINT_7_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_7_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_7_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_1866_DATA    0x1d28
    #define    PHY_NTP_WDQ_STEP_SIZE_7_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_7_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_7_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_7_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_1867_DATA    0x1d2c
    #define    PHY_NTP_WDQ_STOP_7_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_7_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1868_DATA    0x1d30
    #define    PHY_FAST_LVL_EN_7_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_7_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_7_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_1869_DATA    0x1d34
    #define    PHY_PAD_RX_DCD_2_7_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_7_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_7_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_7_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1870_DATA    0x1d38
    #define    PHY_PAD_RX_DCD_6_7_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_7_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_7_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_7_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1871_DATA    0x1d3c
    #define    PHY_PAD_DQS_RX_DCD_7_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_7_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_7_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_1872_DATA    0x1d40
    #define    PHY_PAD_DSLICE_IO_CFG_7_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1873_DATA    0x1d44
    #define    PHY_RDDQ1_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1874_DATA    0x1d48
    #define    PHY_RDDQ3_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1875_DATA    0x1d4c
    #define    PHY_RDDQ5_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1876_DATA    0x1d50
    #define    PHY_RDDQ7_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1877_DATA    0x1d54
    #define    PHY_RX_CAL_ALL_DLY_7_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_7_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1878_DATA    0x1d58
    #define    PHY_RX_OFF_FIRST_STEP_7_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_7_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_7_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_7_RW_0_8    0xff    //0x03
#define    DENALI_PHY_1879_DATA    0x1d5c
    #define    PHY_DATA_DC_CAL_CLK_SEL_7_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_7_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_7_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_7_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_1880_DATA    0x1d60
    #define    PHY_DQS_OE_TIMING_7_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_7_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_7_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_7_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1881_DATA    0x1d64
    #define    PHY_DQS_TSEL_WR_TIMING_7_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_7_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_7_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1882_DATA    0x1d68
    #define    PHY_PAD_VREF_CTRL_DQ_7_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_7_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_1883_DATA    0x1d6c
    #define    PHY_DQ_IE_TIMING_7_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_7_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_7_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_1884_DATA    0x1d70
    #define    PHY_DBI_MODE_7_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_7_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_7_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_7_RW_0_8    0xff    //0x80
#define    DENALI_PHY_1885_DATA    0x1d74
    #define    PHY_RDDATA_EN_TSEL_DLY_7_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_7_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_7_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_7_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1886_DATA    0x1d78
    #define    PHY_MASTER_DELAY_STEP_7_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_7_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_7_RW_0_4    0xf    //0x00
#define    DENALI_PHY_1887_DATA    0x1d7c
    #define    PHY_WRLVL_DLY_STEP_7_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_7_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_7_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_7_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1888_DATA    0x1d80
    #define    PHY_GTLVL_RESP_WAIT_CNT_7_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_7_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_7_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_7_RW_0_4    0xf    //0x01
#define    DENALI_PHY_1889_DATA    0x1d84
    #define    PHY_GTLVL_FINAL_STEP_7_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_7_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_1890_DATA    0x1d88
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_7_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_7_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_7_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1891_DATA    0x1d8c
    #define    PHY_X4_DQ_IE_TIMING_7_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_7_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_7_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_7_RW_0_8    0xff    //0x42
#define    DENALI_PHY_1892_DATA    0x1d90
    #define    PHY_X4_DQS_IE_TIMING_7_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_7_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_7_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_7_RW_0_8    0xff    //0x51
#define    DENALI_PHY_1893_DATA    0x1d94
    #define    PHY_RDLVL_DLY_STEP_7_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_7_RW_0_4    0xf    //0x06
#define    DENALI_PHY_1894_DATA    0x1d98
    #define    PHY_RDLVL_MAX_EDGE_7_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_1895_DATA    0x1d9c
    #define    PHY_DATA_DC_INIT_DISABLE_7_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_7_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_7_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1896_DATA    0x1da0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_7_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1897_DATA    0x1da4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_7_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_7_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_7_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_7_RW_0_1    0x1    //0x01
#define    DENALI_PHY_1898_DATA    0x1da8
    #define    PHY_RDDATA_EN_DLY_7_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_7_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_1899_DATA    0x1dac
    #define    PHY_DQ_DM_SWIZZLE0_7_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_1900_DATA    0x1db0
    #define    PHY_DQ_DM_SWIZZLE1_7_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1901_DATA    0x1db4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_7_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_7_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1902_DATA    0x1db8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_7_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_7_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1903_DATA    0x1dbc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_7_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_7_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1904_DATA    0x1dc0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_7_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_7_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1905_DATA    0x1dc4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_7_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_1906_DATA    0x1dc8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_7_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_7_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1907_DATA    0x1dcc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1908_DATA    0x1dd0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1909_DATA    0x1dd4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1910_DATA    0x1dd8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1911_DATA    0x1ddc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1912_DATA    0x1de0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1913_DATA    0x1de4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1914_DATA    0x1de8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1915_DATA    0x1dec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1916_DATA    0x1df0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1917_DATA    0x1df4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1918_DATA    0x1df8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1919_DATA    0x1dfc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1920_DATA    0x1e00
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1921_DATA    0x1e04
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1922_DATA    0x1e08
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1923_DATA    0x1e0c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1924_DATA    0x1e10
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_1925_DATA    0x1e14
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_7_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_7_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_7_RW_0_4    0xf    //0x02
#define    DENALI_PHY_1926_DATA    0x1e18
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_7_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1927_DATA    0x1e1c
    #define    PHY_GTLVL_LAT_ADJ_START_7_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1928_DATA    0x1e20
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_7_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_7_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_1929_DATA    0x1e24
    #define    PHY_X4_NTP_PASS_7_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_7_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_7_RW_0_4    0xf    //0x08
#define    DENALI_PHY_1930_DATA    0x1e28
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_7_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1931_DATA    0x1e2c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_7_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_7_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_1932_DATA    0x1e30
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_7_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_7_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_1933_DATA    0x1e34
    #define    PHY_X4_GTLVL_LAT_ADJ_START_7_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_7_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_7_RW_0_1    0x1    //0x00
#define    DENALI_PHY_1934_DATA    0x1e38
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_7_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_1935_DATA    0x1e3c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_7_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_7_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_7_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_7_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1936_DATA    0x1e40
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_7_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_7_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_7_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_7_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1937_DATA    0x1e44
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_7_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_7_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_7_RW_0_8    0xff    //0x20
#define    DENALI_PHY_1938_DATA    0x1e48
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_7_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_7_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_7_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_1939_DATA    0x1e4c
    #define    PHY_X4_DQS_FFE_7_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_7_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_7_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_7_RW_0_2    0x3    //0x00
#define    DENALI_PHY_1940_DATA    0x1e50
    #define    PHY_RX_CAL_DQ0_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1941_DATA    0x1e54
    #define    PHY_RX_CAL_DQ1_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1942_DATA    0x1e58
    #define    PHY_RX_CAL_DQ2_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1943_DATA    0x1e5c
    #define    PHY_RX_CAL_DQ3_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1944_DATA    0x1e60
    #define    PHY_RX_CAL_DQ4_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1945_DATA    0x1e64
    #define    PHY_RX_CAL_DQ5_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1946_DATA    0x1e68
    #define    PHY_RX_CAL_DQ6_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1947_DATA    0x1e6c
    #define    PHY_RX_CAL_DQ7_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1948_DATA    0x1e70
    #define    PHY_RX_CAL_DM_7_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_1949_DATA    0x1e74
#define    DENALI_PHY_1950_DATA    0x1e78
#define    DENALI_PHY_1951_DATA    0x1e7c
#define    DENALI_PHY_1952_DATA    0x1e80
#define    DENALI_PHY_1953_DATA    0x1e84
#define    DENALI_PHY_1954_DATA    0x1e88
#define    DENALI_PHY_1955_DATA    0x1e8c
#define    DENALI_PHY_1956_DATA    0x1e90
#define    DENALI_PHY_1957_DATA    0x1e94
#define    DENALI_PHY_1958_DATA    0x1e98
#define    DENALI_PHY_1959_DATA    0x1e9c
#define    DENALI_PHY_1960_DATA    0x1ea0
#define    DENALI_PHY_1961_DATA    0x1ea4
#define    DENALI_PHY_1962_DATA    0x1ea8
#define    DENALI_PHY_1963_DATA    0x1eac
#define    DENALI_PHY_1964_DATA    0x1eb0
#define    DENALI_PHY_1965_DATA    0x1eb4
#define    DENALI_PHY_1966_DATA    0x1eb8
#define    DENALI_PHY_1967_DATA    0x1ebc
#define    DENALI_PHY_1968_DATA    0x1ec0
#define    DENALI_PHY_1969_DATA    0x1ec4
#define    DENALI_PHY_1970_DATA    0x1ec8
#define    DENALI_PHY_1971_DATA    0x1ecc
#define    DENALI_PHY_1972_DATA    0x1ed0
#define    DENALI_PHY_1973_DATA    0x1ed4
#define    DENALI_PHY_1974_DATA    0x1ed8
#define    DENALI_PHY_1975_DATA    0x1edc
#define    DENALI_PHY_1976_DATA    0x1ee0
#define    DENALI_PHY_1977_DATA    0x1ee4
#define    DENALI_PHY_1978_DATA    0x1ee8
#define    DENALI_PHY_1979_DATA    0x1eec
#define    DENALI_PHY_1980_DATA    0x1ef0
#define    DENALI_PHY_1981_DATA    0x1ef4
#define    DENALI_PHY_1982_DATA    0x1ef8
#define    DENALI_PHY_1983_DATA    0x1efc
#define    DENALI_PHY_1984_DATA    0x1f00
#define    DENALI_PHY_1985_DATA    0x1f04
#define    DENALI_PHY_1986_DATA    0x1f08
#define    DENALI_PHY_1987_DATA    0x1f0c
#define    DENALI_PHY_1988_DATA    0x1f10
#define    DENALI_PHY_1989_DATA    0x1f14
#define    DENALI_PHY_1990_DATA    0x1f18
#define    DENALI_PHY_1991_DATA    0x1f1c
#define    DENALI_PHY_1992_DATA    0x1f20
#define    DENALI_PHY_1993_DATA    0x1f24
#define    DENALI_PHY_1994_DATA    0x1f28
#define    DENALI_PHY_1995_DATA    0x1f2c
#define    DENALI_PHY_1996_DATA    0x1f30
#define    DENALI_PHY_1997_DATA    0x1f34
#define    DENALI_PHY_1998_DATA    0x1f38
#define    DENALI_PHY_1999_DATA    0x1f3c
#define    DENALI_PHY_2000_DATA    0x1f40
#define    DENALI_PHY_2001_DATA    0x1f44
#define    DENALI_PHY_2002_DATA    0x1f48
#define    DENALI_PHY_2003_DATA    0x1f4c
#define    DENALI_PHY_2004_DATA    0x1f50
#define    DENALI_PHY_2005_DATA    0x1f54
#define    DENALI_PHY_2006_DATA    0x1f58
#define    DENALI_PHY_2007_DATA    0x1f5c
#define    DENALI_PHY_2008_DATA    0x1f60
#define    DENALI_PHY_2009_DATA    0x1f64
#define    DENALI_PHY_2010_DATA    0x1f68
#define    DENALI_PHY_2011_DATA    0x1f6c
#define    DENALI_PHY_2012_DATA    0x1f70
#define    DENALI_PHY_2013_DATA    0x1f74
#define    DENALI_PHY_2014_DATA    0x1f78
#define    DENALI_PHY_2015_DATA    0x1f7c
#define    DENALI_PHY_2016_DATA    0x1f80
#define    DENALI_PHY_2017_DATA    0x1f84
#define    DENALI_PHY_2018_DATA    0x1f88
#define    DENALI_PHY_2019_DATA    0x1f8c
#define    DENALI_PHY_2020_DATA    0x1f90
#define    DENALI_PHY_2021_DATA    0x1f94
#define    DENALI_PHY_2022_DATA    0x1f98
#define    DENALI_PHY_2023_DATA    0x1f9c
#define    DENALI_PHY_2024_DATA    0x1fa0
#define    DENALI_PHY_2025_DATA    0x1fa4
#define    DENALI_PHY_2026_DATA    0x1fa8
#define    DENALI_PHY_2027_DATA    0x1fac
#define    DENALI_PHY_2028_DATA    0x1fb0
#define    DENALI_PHY_2029_DATA    0x1fb4
#define    DENALI_PHY_2030_DATA    0x1fb8
#define    DENALI_PHY_2031_DATA    0x1fbc
#define    DENALI_PHY_2032_DATA    0x1fc0
#define    DENALI_PHY_2033_DATA    0x1fc4
#define    DENALI_PHY_2034_DATA    0x1fc8
#define    DENALI_PHY_2035_DATA    0x1fcc
#define    DENALI_PHY_2036_DATA    0x1fd0
#define    DENALI_PHY_2037_DATA    0x1fd4
#define    DENALI_PHY_2038_DATA    0x1fd8
#define    DENALI_PHY_2039_DATA    0x1fdc
#define    DENALI_PHY_2040_DATA    0x1fe0
#define    DENALI_PHY_2041_DATA    0x1fe4
#define    DENALI_PHY_2042_DATA    0x1fe8
#define    DENALI_PHY_2043_DATA    0x1fec
#define    DENALI_PHY_2044_DATA    0x1ff0
#define    DENALI_PHY_2045_DATA    0x1ff4
#define    DENALI_PHY_2046_DATA    0x1ff8
#define    DENALI_PHY_2047_DATA    0x1ffc
#define    DENALI_PHY_2048_DATA    0x2000
    #define    PHY_IO_PAD_DELAY_TIMING_BYPASS_8_RW_16_4    0xf0000    //0x00
    #define    PHY_CLK_WR_BYPASS_SLAVE_DELAY_8_RW_0_11    0x7ff    //0x04c0
#define    DENALI_PHY_2049_DATA    0x2004
    #define    PHY_WRITE_PATH_LAT_ADD_BYPASS_8_RW_16_3    0x70000    //0x00
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_BYPASS_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2050_DATA    0x2008
    #define    PHY_CLK_BYPASS_OVERRIDE_8_RW_24_1    0x1000000    //0x00
    #define    PHY_BYPASS_TWO_CYC_PREAMBLE_8_RW_16_2    0x30000    //0x00
    #define    PHY_RDDQS_GATE_BYPASS_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0200
#define    DENALI_PHY_2051_DATA    0x200c
    #define    PHY_SW_WRDQ3_SHIFT_8_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ2_SHIFT_8_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ1_SHIFT_8_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ0_SHIFT_8_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_2052_DATA    0x2010
    #define    PHY_SW_WRDQ7_SHIFT_8_RW_24_6    0x3f000000    //0x00
    #define    PHY_SW_WRDQ6_SHIFT_8_RW_16_6    0x3f0000    //0x00
    #define    PHY_SW_WRDQ5_SHIFT_8_RW_8_6    0x3f00    //0x00
    #define    PHY_SW_WRDQ4_SHIFT_8_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_2053_DATA    0x2014
    #define    PHY_PER_CS_TRAINING_MULTICAST_EN_8_RW_D_24_1    0x1000000    //0x01
    #define    PHY_PER_RANK_CS_MAP_8_RW_16_2    0x30000    //0x03
    #define    PHY_SW_WRDQS_SHIFT_8_RW_8_4    0xf00    //0x00
    #define    PHY_SW_WRDM_SHIFT_8_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_2054_DATA    0x2018
    #define    PHY_LPBK_CONTROL_8_RW_16_9    0x1ff0000    //0x0000
    #define    PHY_CTRL_LPBK_EN_8_RW_8_2    0x300    //0x00
    #define    PHY_PER_CS_TRAINING_INDEX_8_RW_0_2    0x3    //0x00
#define    DENALI_PHY_2055_DATA    0x201c
    #define    PHY_GATE_DELAY_COMP_DISABLE_8_RW_8_1    0x100    //0x00
    #define    PHY_LPBK_DFX_TIMEOUT_EN_8_RW_0_1    0x1    //0x01
#define    DENALI_PHY_2056_DATA    0x2020
    #define    PHY_AUTO_TIMING_MARGIN_CONTROL_8_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2057_DATA    0x2024
    #define    PHY_AUTO_TIMING_MARGIN_OBS_8_RD_0_28    0xfffffff    //0x00000000
#define    DENALI_PHY_2058_DATA    0x2028
    #define    PHY_PRBS_PATTERN_START_8_RW_D_24_7    0x7f000000    //0x01
    #define    PHY_DDR4_DQ_IDLE_8_RW_8_9    0x1ff00    //0x01ff
    #define    PHY_PDA_MODE_EN_8_RW_0_1    0x1    //0x01
#define    DENALI_PHY_2059_DATA    0x202c
    #define    PHY_RDLVL_MULTI_PATT_RST_DISABLE_8_RW_24_1    0x1000000    //0x00
    #define    PHY_RDLVL_MULTI_PATT_ENABLE_8_RW_16_1    0x10000    //0x00
    #define    PHY_PRBS_PATTERN_MASK_8_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_2060_DATA    0x2030
    #define    PHY_X4_VREF_TRAIN_OBS_8_RD_16_7    0x7f0000    //0x00
    #define    PHY_VREF_TRAIN_OBS_8_RD_8_7    0x7f00    //0x00
    #define    PHY_VREF_INITIAL_STEPSIZE_8_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_2061_DATA    0x2034
    #define    SC_PHY_SNAP_OBS_REGS_8_WR_24_1    0x1000000    //0x00
    #define    PHY_GATE_ERROR_DELAY_SELECT_8_RW_16_4    0xf0000    //0x08
    #define    PHY_RDDQS_DQ_BYPASS_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00c0
#define    DENALI_PHY_2062_DATA    0x2038
    #define    PHY_DFI40_POLARITY_8_RW_8_1    0x100    //0x00
    #define    PHY_MEM_CLASS_8_RW_0_3    0x7    //0x02
#define    DENALI_PHY_2063_DATA    0x203c
    #define    PHY_RDLVL_PATT8_8_RW_0_32    0xffffffff    //0x0000AAAA
#define    DENALI_PHY_2064_DATA    0x2040
    #define    PHY_RDLVL_PATT9_8_RW_0_32    0xffffffff    //0x00005555
#define    DENALI_PHY_2065_DATA    0x2044
    #define    PHY_RDLVL_PATT10_8_RW_0_32    0xffffffff    //0x0000B5B5
#define    DENALI_PHY_2066_DATA    0x2048
    #define    PHY_RDLVL_PATT11_8_RW_0_32    0xffffffff    //0x00004A4A
#define    DENALI_PHY_2067_DATA    0x204c
    #define    PHY_RDLVL_PATT12_8_RW_0_32    0xffffffff    //0x00005656
#define    DENALI_PHY_2068_DATA    0x2050
    #define    PHY_RDLVL_PATT13_8_RW_0_32    0xffffffff    //0x0000A9A9
#define    DENALI_PHY_2069_DATA    0x2054
    #define    PHY_RDLVL_PATT14_8_RW_0_32    0xffffffff    //0x0000B7B7
#define    DENALI_PHY_2070_DATA    0x2058
    #define    PHY_RDLVL_PATT15_8_RW_0_32    0xffffffff    //0x00004848
#define    DENALI_PHY_2071_DATA    0x205c
    #define    PHY_RDLVL_PATT0_3_MASK_8_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2072_DATA    0x2060
    #define    PHY_RDLVL_PATT8_11_MASK_8_RW_0_32    0xffffffff    //0xbfbf0000
#define    DENALI_PHY_2073_DATA    0x2064
    #define    PHY_RDLVL_PATT12_15_MASK_8_RW_0_32    0xffffffff    //0x3333f7f7
#define    DENALI_PHY_2074_DATA    0x2068
    #define    PHY_RDDQ_ENC_OBS_SELECT_8_RW_24_3    0x7000000    //0x00
    #define    PHY_MASTER_DLY_LOCK_OBS_SELECT_8_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_FIFO_PTR_RST_DISABLE_8_RW_8_1    0x100    //0x00
    #define    PHY_SLAVE_LOOP_CNT_UPDATE_8_RW_0_3    0x7    //0x00
#define    DENALI_PHY_2075_DATA    0x206c
    #define    PHY_FIFO_PTR_OBS_SELECT_8_RW_24_4    0xf000000    //0x00
    #define    PHY_WR_SHIFT_OBS_SELECT_8_RW_16_4    0xf0000    //0x00
    #define    PHY_WR_ENC_OBS_SELECT_8_RW_8_4    0xf00    //0x00
    #define    PHY_RDDQS_DQ_ENC_OBS_SELECT_8_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_2076_DATA    0x2070
    #define    PHY_WRLVL_CAPTURE_CNT_8_RW_24_6    0x3f000000    //0x08
    #define    PHY_WRLVL_ALGO_8_RW_16_2    0x30000    //0x00
    #define    SC_PHY_LVL_DEBUG_CONT_8_WR_8_1    0x100    //0x00
    #define    PHY_LVL_DEBUG_MODE_8_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2077_DATA    0x2074
    #define    PHY_GTLVL_UPDT_WAIT_CNT_8_RW_24_4    0xf000000    //0x04
    #define    PHY_GTLVL_CAPTURE_CNT_8_RW_16_6    0x3f0000    //0x00
    #define    PHY_DQ_MASK_8_RW_8_8    0xff00    //0x00
    #define    PHY_WRLVL_UPDT_WAIT_CNT_8_RW_0_4    0xf    //0x08
#define    DENALI_PHY_2078_DATA    0x2078
    #define    PHY_RDLVL_RDDQS_DQ_OBS_SELECT_8_RW_24_4    0xf000000    //0x00
    #define    PHY_RDLVL_OP_MODE_8_RW_16_2    0x30000    //0x00
    #define    PHY_RDLVL_UPDT_WAIT_CNT_8_RW_8_4    0xf00    //0x04
    #define    PHY_RDLVL_CAPTURE_CNT_8_RW_0_6    0x3f    //0x08
#define    DENALI_PHY_2079_DATA    0x207c
    #define    PHY_RDLVL_DATA_SWIZZLE_8_RW_8_18    0x3ffff00    //0x00e4e4
    #define    PHY_RDLVL_DATA_MASK_8_RW_0_8    0xff    //0x00
#define    DENALI_PHY_2080_DATA    0x2080
    #define    PHY_WDQLVL_PATT_8_RW_16_3    0x70000    //0x07
    #define    PHY_WDQLVL_BURST_CNT_8_RW_8_6    0x3f00    //0x08
    #define    PHY_WDQLVL_CLK_JITTER_TOLERANCE_8_RW_0_8    0xff    //0x20
#define    DENALI_PHY_2081_DATA    0x2084
    #define    PHY_WDQLVL_DQDM_OBS_SELECT_8_RW_24_4    0xf000000    //0x00
    #define    PHY_WDQLVL_UPDT_WAIT_CNT_8_RW_16_4    0xf0000    //0x0c
    #define    PHY_WDQLVL_DQDM_SLV_DLY_JUMP_OFFSET_8_RW_0_11    0x7ff    //0x0020
#define    DENALI_PHY_2082_DATA    0x2088
    #define    SC_PHY_WDQLVL_CLR_PREV_RESULTS_8_WR_16_1    0x10000    //0x00
    #define    PHY_WDQLVL_DM_DLY_STEP_8_RW_8_4    0xf00    //0x06
    #define    PHY_WDQLVL_DQ_SLV_DELTA_8_RW_0_8    0xff    //0x20
#define    DENALI_PHY_2083_DATA    0x208c
    #define    PHY_WDQLVL_DATADM_MASK_8_RW_0_9    0x1ff    //0x0100
#define    DENALI_PHY_2084_DATA    0x2090
    #define    PHY_USER_PATT0_8_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_2085_DATA    0x2094
    #define    PHY_USER_PATT1_8_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_2086_DATA    0x2098
    #define    PHY_USER_PATT2_8_RW_0_32    0xffffffff    //0x55555555
#define    DENALI_PHY_2087_DATA    0x209c
    #define    PHY_USER_PATT3_8_RW_0_32    0xffffffff    //0xAAAAAAAA
#define    DENALI_PHY_2088_DATA    0x20a0
    #define    PHY_NTP_MULT_TRAIN_8_RW_16_1    0x10000    //0x00
    #define    PHY_USER_PATT4_8_RW_0_16    0xffff    //0x5555
#define    DENALI_PHY_2089_DATA    0x20a4
    #define    PHY_NTP_PERIOD_THRESHOLD_8_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_NTP_EARLY_THRESHOLD_8_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2090_DATA    0x20a8
    #define    PHY_NTP_PERIOD_THRESHOLD_MAX_8_RW_16_10    0x3ff0000    //0x0080
    #define    PHY_NTP_PERIOD_THRESHOLD_MIN_8_RW_0_10    0x3ff    //0x0180
#define    DENALI_PHY_2091_DATA    0x20ac
    #define    PHY_FIFO_PTR_OBS_8_RD_8_8    0xff00    //0x00
    #define    SC_PHY_MANUAL_CLEAR_8_WR_0_5    0x1f    //0x00
#define    DENALI_PHY_2092_DATA    0x20b0
    #define    PHY_LPBK_RESULT_OBS_8_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2093_DATA    0x20b4
    #define    PHY_MASTER_DLY_LOCK_OBS_8_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_LPBK_ERROR_COUNT_OBS_8_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_2094_DATA    0x20b8
    #define    PHY_RDDQS_DQ_RISE_ADDER_SLV_DLY_ENC_OBS_8_RD_24_8    0xff000000    //0x00
    #define    PHY_MEAS_DLY_STEP_VALUE_8_RD_16_8    0xff0000    //0x00
    #define    PHY_RDDQS_BASE_SLV_DLY_ENC_OBS_8_RD_8_7    0x7f00    //0x00
    #define    PHY_RDDQ_SLV_DLY_ENC_OBS_8_RD_0_7    0x7f    //0x00
#define    DENALI_PHY_2095_DATA    0x20bc
    #define    PHY_WRDQS_BASE_SLV_DLY_ENC_OBS_8_RD_24_7    0x7f000000    //0x00
    #define    PHY_RDDQS_GATE_SLV_DLY_ENC_OBS_8_RD_8_11    0x7ff00    //0x0000
    #define    PHY_RDDQS_DQ_FALL_ADDER_SLV_DLY_ENC_OBS_8_RD_0_8    0xff    //0x00
#define    DENALI_PHY_2096_DATA    0x20c0
    #define    PHY_WR_SHIFT_OBS_8_RD_16_3    0x70000    //0x00
    #define    PHY_WR_ADDER_SLV_DLY_ENC_OBS_8_RD_8_8    0xff00    //0x00
    #define    PHY_WRDQ_BASE_SLV_DLY_ENC_OBS_8_RD_0_8    0xff    //0x00
#define    DENALI_PHY_2097_DATA    0x20c4
    #define    PHY_WRLVL_HARD1_DELAY_OBS_8_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_WRLVL_HARD0_DELAY_OBS_8_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2098_DATA    0x20c8
    #define    PHY_WRLVL_STATUS_OBS_8_RD_0_23    0x7fffff    //0x000000
#define    DENALI_PHY_2099_DATA    0x20cc
    #define    PHY_WRLVL_ERROR_OBS_8_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2100_DATA    0x20d0
    #define    PHY_GTLVL_HARD1_DELAY_OBS_8_RD_16_14    0x3fff0000    //0x0000
    #define    PHY_GTLVL_HARD0_DELAY_OBS_8_RD_0_14    0x3fff    //0x0000
#define    DENALI_PHY_2101_DATA    0x20d4
    #define    PHY_GTLVL_STATUS_OBS_8_RD_0_21    0x1fffff    //0x000000
#define    DENALI_PHY_2102_DATA    0x20d8
    #define    PHY_RDLVL_RDDQS_DQ_TE_DLY_OBS_8_RD_16_10    0x3ff0000    //0x0000
    #define    PHY_RDLVL_RDDQS_DQ_LE_DLY_OBS_8_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2103_DATA    0x20dc
    #define    PHY_RDLVL_RDDQS_DQ_NUM_WINDOWS_OBS_8_RD_0_2    0x3    //0x00
#define    DENALI_PHY_2104_DATA    0x20e0
    #define    PHY_RDLVL_STATUS_OBS_8_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2105_DATA    0x20e4
    #define    PHY_WDQLVL_DQDM_TE_DLY_OBS_8_RD_16_11    0x7ff0000    //0x0000
    #define    PHY_WDQLVL_DQDM_LE_DLY_OBS_8_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_2106_DATA    0x20e8
    #define    PHY_WDQLVL_STATUS_OBS_8_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2107_DATA    0x20ec
    #define    PHY_DQS_RATIO_X8_8_RW_16_1    0x10000    //0x00
    #define    PHY_X4_ENC_OBS_SELECT_8_RW_8_1    0x100    //0x00
    #define    PHY_X4_SW_WRDQS_SHIFT_8_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2108_DATA    0x20f0
    #define    PHY_DDL_MODE_8_RW_0_31    0x7fffffff    //0x00000000
#define    DENALI_PHY_2109_DATA    0x20f4
    #define    PHY_DDL_MASK_8_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_2110_DATA    0x20f8
    #define    PHY_DDL_TEST_OBS_8_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2111_DATA    0x20fc
    #define    PHY_DDL_TEST_MSTR_DLY_OBS_8_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2112_DATA    0x2100
    #define    PHY_RX_CAL_DQS_8_RW_D_8_9    0x1ff00    //0x0000
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_8_RW_0_8    0xff    //0x04
#define    DENALI_PHY_2113_DATA    0x2104
    #define    PHY_RX_CAL_X4_FDBK_8_RW_D_16_9    0x1ff0000    //0x0000
    #define    PHY_RX_CAL_FDBK_8_RW_D_0_9    0x1ff    //0x0000
#define    DENALI_PHY_2114_DATA    0x2108
    #define    PHY_STATIC_TOG_DISABLE_8_RW_24_5    0x1f000000    //0x1F
    #define    PHY_PAD_RX_BIAS_EN_8_RW_8_12    0xfff00    //0x0fff
    #define    PHY_RX_CAL_DFE_EN_8_RW_0_1    0x1    //0x01
#define    DENALI_PHY_2115_DATA    0x210c
    #define    PHY_DFE_EN_8_RW_24_3    0x7000000    //0x01
    #define    PHY_INIT_VREF_TRAIN_CS_8_RW_16_4    0xf0000    //0x0f
    #define    PHY_RX_OFF_CAPTURE_CNT_8_RW_8_4    0xf00    //0x03
    #define    PHY_DFE_INIT_FALL_DATA_8_RW_0_1    0x1    //0x01
#define    DENALI_PHY_2116_DATA    0x2110
    #define    PHY_DATA_DC_ADJUST_START_8_RW_24_6    0x3f000000    //0x20
    #define    PHY_DATA_DC_WEIGHT_8_RW_16_2    0x30000    //0x00
    #define    PHY_DATA_DC_CAL_TIMEOUT_8_RW_8_8    0xff00    //0x80
    #define    PHY_DATA_DC_CAL_SAMPLE_WAIT_8_RW_0_8    0xff    //0x08
#define    DENALI_PHY_2117_DATA    0x2114
    #define    PHY_DATA_DC_CAL_POLARITY_8_RW_24_1    0x1000000    //0x00
    #define    PHY_DATA_DC_ADJUST_DIRECT_8_RW_16_1    0x10000    //0x00
    #define    PHY_DATA_DC_ADJUST_THRSHLD_8_RW_8_8    0xff00    //0x08
    #define    PHY_DATA_DC_ADJUST_SAMPLE_CNT_8_RW_0_8    0xff    //0x10
#define    DENALI_PHY_2118_DATA    0x2118
    #define    PHY_SLV_DLY_CTRL_GATE_DISABLE_8_RW_D_24_1    0x1000000    //0x00
    #define    PHY_FDBK_PWR_CTRL_8_RW_16_3    0x70000    //0x04
    #define    PHY_DATA_DC_SW_RANK_8_RW_8_4    0xf00    //0x01
    #define    PHY_DATA_DC_CAL_START_8_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2119_DATA    0x211c
    #define    PHY_SLICE_PWR_RDC_DISABLE_8_RW_16_1    0x10000    //0x00
    #define    PHY_DCC_RXCAL_CTRL_GATE_DISABLE_8_RW_D_8_1    0x100    //0x00
    #define    PHY_RDPATH_GATE_DISABLE_8_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_2120_DATA    0x2120
    #define    PHY_DQS_TSEL_ENABLE_8_RW_24_3    0x7000000    //0x01
    #define    PHY_DQ_TSEL_SELECT_8_RW_8_16    0xffff00    //0xff08
    #define    PHY_DQ_TSEL_ENABLE_8_RW_0_3    0x7    //0x01
#define    DENALI_PHY_2121_DATA    0x2124
    #define    PHY_VREF_INITIAL_START_POINT_8_RW_24_7    0x7f000000    //0x20
    #define    PHY_TWO_CYC_PREAMBLE_8_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_TSEL_SELECT_8_RW_0_16    0xffff    //0xff08
#define    DENALI_PHY_2122_DATA    0x2128
    #define    PHY_NTP_WDQ_STEP_SIZE_8_RW_24_8    0xff000000    //0x20
    #define    PHY_NTP_TRAIN_EN_8_RW_16_1    0x10000    //0x00
    #define    PHY_VREF_TRAINING_CTRL_8_RW_8_2    0x300    //0x01
    #define    PHY_VREF_INITIAL_STOP_POINT_8_RW_0_7    0x7f    //0x25
#define    DENALI_PHY_2123_DATA    0x212c
    #define    PHY_NTP_WDQ_STOP_8_RW_16_11    0x7ff0000    //0x07FF
    #define    PHY_NTP_WDQ_START_8_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_2124_DATA    0x2130
    #define    PHY_FAST_LVL_EN_8_RW_24_4    0xf000000    //0x03
    #define    PHY_NTP_WDQ_BIT_EN_8_RW_16_8    0xff0000    //0x01
    #define    PHY_X4_NTP_WDQ_START_8_RW_0_11    0x7ff    //0x0000
#define    DENALI_PHY_2125_DATA    0x2134
    #define    PHY_PAD_RX_DCD_2_8_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_1_8_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_0_8_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_TX_DCD_8_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_2126_DATA    0x2138
    #define    PHY_PAD_RX_DCD_6_8_RW_24_5    0x1f000000    //0x00
    #define    PHY_PAD_RX_DCD_5_8_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_RX_DCD_4_8_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_3_8_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_2127_DATA    0x213c
    #define    PHY_PAD_DQS_RX_DCD_8_RW_16_5    0x1f0000    //0x00
    #define    PHY_PAD_DM_RX_DCD_8_RW_8_5    0x1f00    //0x00
    #define    PHY_PAD_RX_DCD_7_8_RW_0_5    0x1f    //0x00
#define    DENALI_PHY_2128_DATA    0x2140
    #define    PHY_PAD_DSLICE_IO_CFG_8_RW_16_7    0x7f0000    //0x00
    #define    PHY_PAD_FDBK_RX_DCD_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2129_DATA    0x2144
    #define    PHY_RDDQ1_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ0_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2130_DATA    0x2148
    #define    PHY_RDDQ3_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ2_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2131_DATA    0x214c
    #define    PHY_RDDQ5_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ4_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2132_DATA    0x2150
    #define    PHY_RDDQ7_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_RDDQ6_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2133_DATA    0x2154
    #define    PHY_RX_CAL_ALL_DLY_8_RW_24_5    0x1f000000    //0x02
    #define    PHY_RX_PCLK_CLK_SEL_8_RW_16_3    0x70000    //0x00
    #define    PHY_RDDM_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2134_DATA    0x2158
    #define    PHY_RX_OFF_FIRST_STEP_8_RW_24_6    0x3f000000    //0x01
    #define    PHY_RX_OFF_TE_DELTA_MIN_8_RW_16_8    0xff0000    //0x10
    #define    PHY_RDLVL_DFE_EN_8_RW_8_3    0x700    //0x01
    #define    PHY_RX_CAL_SAMPLE_WAIT_8_RW_0_8    0xff    //0x03
#define    DENALI_PHY_2135_DATA    0x215c
    #define    PHY_DATA_DC_CAL_CLK_SEL_8_RW_24_3    0x7000000    //0x02
    #define    PHY_DFE_TE_CHG_THRSHLD_8_RW_16_8    0xff0000    //0x10
    #define    PHY_DFE_BACK_STEP_8_RW_8_8    0xff00    //0x20
    #define    PHY_RX_OFF_NEXT_STEP_8_RW_0_6    0x3f    //0x04
#define    DENALI_PHY_2136_DATA    0x2160
    #define    PHY_DQS_OE_TIMING_8_RW_24_8    0xff000000    //0x51
    #define    PHY_DQ_TSEL_WR_TIMING_8_RW_16_8    0xff0000    //0x51
    #define    PHY_DQ_TSEL_RD_TIMING_8_RW_8_8    0xff00    //0x40
    #define    PHY_DQ_OE_TIMING_8_RW_0_8    0xff    //0x42
#define    DENALI_PHY_2137_DATA    0x2164
    #define    PHY_DQS_TSEL_WR_TIMING_8_RW_16_8    0xff0000    //0x31
    #define    PHY_DQS_TSEL_RD_TIMING_8_RW_8_8    0xff00    //0x40
    #define    PHY_IO_PAD_DELAY_TIMING_8_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2138_DATA    0x2168
    #define    PHY_PAD_VREF_CTRL_DQ_8_RW_16_12    0xfff0000    //0x041f
    #define    PHY_VREF_SETTING_TIME_8_RW_0_16    0xffff    //0x0140
#define    DENALI_PHY_2139_DATA    0x216c
    #define    PHY_DQ_IE_TIMING_8_RW_24_8    0xff000000    //0x80
    #define    PHY_PER_CS_TRAINING_EN_8_RW_16_1    0x10000    //0x01
    #define    PHY_X4_PAD_VREF_CTRL_DQ_8_RW_0_12    0xfff    //0x041f
#define    DENALI_PHY_2140_DATA    0x2170
    #define    PHY_DBI_MODE_8_RW_24_2    0x3000000    //0x00
    #define    PHY_IE_MODE_8_RW_16_2    0x30000    //0x00
    #define    PHY_RDDATA_EN_IE_DLY_8_RW_8_2    0x300    //0x00
    #define    PHY_DQS_IE_TIMING_8_RW_0_8    0xff    //0x80
#define    DENALI_PHY_2141_DATA    0x2174
    #define    PHY_RDDATA_EN_TSEL_DLY_8_RW_24_5    0x1f000000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_TSEL_DLY_8_RW_16_5    0x1f0000    //0x0a
    #define    PHY_WDQLVL_RDDATA_EN_DLY_8_RW_8_5    0x1f00    //0x0b
    #define    PHY_WDQLVL_IE_ON_8_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2142_DATA    0x2178
    #define    PHY_MASTER_DELAY_STEP_8_RW_24_6    0x3f000000    //0x10
    #define    PHY_MASTER_DELAY_START_8_RW_8_11    0x7ff00    //0x0010
    #define    PHY_SW_MASTER_MODE_8_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2143_DATA    0x217c
    #define    PHY_WRLVL_DLY_STEP_8_RW_24_8    0xff000000    //0x0c
    #define    PHY_RPTR_UPDATE_8_RW_16_4    0xf0000    //0x06
    #define    PHY_MASTER_DELAY_HALF_MEASURE_8_RW_8_8    0xff00    //0x3e
    #define    PHY_MASTER_DELAY_WAIT_8_RW_0_8    0xff    //0x42
#define    DENALI_PHY_2144_DATA    0x2180
    #define    PHY_GTLVL_RESP_WAIT_CNT_8_RW_24_5    0x1f000000    //0x0f
    #define    PHY_GTLVL_DLY_STEP_8_RW_16_4    0xf0000    //0x0c
    #define    PHY_WRLVL_RESP_WAIT_CNT_8_RW_8_6    0x3f00    //0x1b
    #define    PHY_WRLVL_DLY_FINE_STEP_8_RW_0_4    0xf    //0x01
#define    DENALI_PHY_2145_DATA    0x2184
    #define    PHY_GTLVL_FINAL_STEP_8_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GTLVL_BACK_STEP_8_RW_0_10    0x3ff    //0x0140
#define    DENALI_PHY_2146_DATA    0x2188
    #define    PHY_WDQLVL_DM_SEARCH_RANGE_8_RW_16_9    0x1ff0000    //0x00f5
    #define    PHY_WDQLVL_QTR_DLY_STEP_8_RW_8_4    0xf00    //0x01
    #define    PHY_WDQLVL_DLY_STEP_8_RW_0_8    0xff    //0x20
#define    DENALI_PHY_2147_DATA    0x218c
    #define    PHY_X4_DQ_IE_TIMING_8_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQ_TSEL_WR_TIMING_8_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQ_TSEL_RD_TIMING_8_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQ_OE_TIMING_8_RW_0_8    0xff    //0x42
#define    DENALI_PHY_2148_DATA    0x2190
    #define    PHY_X4_DQS_IE_TIMING_8_RW_24_8    0xff000000    //0x80
    #define    PHY_X4_DQS_TSEL_WR_TIMING_8_RW_16_8    0xff0000    //0x31
    #define    PHY_X4_DQS_TSEL_RD_TIMING_8_RW_8_8    0xff00    //0x40
    #define    PHY_X4_DQS_OE_TIMING_8_RW_0_8    0xff    //0x51
#define    DENALI_PHY_2149_DATA    0x2194
    #define    PHY_RDLVL_DLY_STEP_8_RW_8_4    0xf00    //0x0c
    #define    PHY_X4_RPTR_UPDATE_8_RW_0_4    0xf    //0x06
#define    DENALI_PHY_2150_DATA    0x2198
    #define    PHY_RDLVL_MAX_EDGE_8_RW_0_10    0x3ff    //0x0299
#define    DENALI_PHY_2151_DATA    0x219c
    #define    PHY_DATA_DC_INIT_DISABLE_8_RW_16_2    0x30000    //0x00
    #define    PHY_WRPATH_GATE_TIMING_8_RW_8_3    0x700    //0x02
    #define    PHY_WRPATH_GATE_DISABLE_8_RW_0_2    0x3    //0x00
#define    DENALI_PHY_2152_DATA    0x21a0
    #define    PHY_DATA_DC_DQ_INIT_SLV_DELAY_8_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_DATA_DC_DQS_INIT_SLV_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2153_DATA    0x21a4
    #define    PHY_DATA_DC_DM_CLK_DIFF_THRSHLD_8_RW_24_8    0xff000000    //0x80
    #define    PHY_DATA_DC_DM_CLK_SE_THRSHLD_8_RW_16_8    0xff0000    //0x80
    #define    PHY_DATA_DC_WDQLVL_ENABLE_8_RW_8_1    0x100    //0x01
    #define    PHY_DATA_DC_WRLVL_ENABLE_8_RW_0_1    0x1    //0x01
#define    DENALI_PHY_2154_DATA    0x21a8
    #define    PHY_RDDATA_EN_DLY_8_RW_8_5    0x1f00    //0x0b
    #define    PHY_MEAS_DLY_STEP_ENABLE_8_RW_0_7    0x7f    //0x20
#define    DENALI_PHY_2155_DATA    0x21ac
    #define    PHY_DQ_DM_SWIZZLE0_8_RW_0_32    0xffffffff    //0x76543210
#define    DENALI_PHY_2156_DATA    0x21b0
    #define    PHY_DQ_DM_SWIZZLE1_8_RW_0_4    0xf    //0x08
#define    DENALI_PHY_2157_DATA    0x21b4
    #define    PHY_CLK_WRDQ1_SLAVE_DELAY_8_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ0_SLAVE_DELAY_8_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_2158_DATA    0x21b8
    #define    PHY_CLK_WRDQ3_SLAVE_DELAY_8_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ2_SLAVE_DELAY_8_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_2159_DATA    0x21bc
    #define    PHY_CLK_WRDQ5_SLAVE_DELAY_8_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ4_SLAVE_DELAY_8_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_2160_DATA    0x21c0
    #define    PHY_CLK_WRDQ7_SLAVE_DELAY_8_RW_16_11    0x7ff0000    //0x0280
    #define    PHY_CLK_WRDQ6_SLAVE_DELAY_8_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_2161_DATA    0x21c4
    #define    PHY_CLK_WRDQS_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_CLK_WRDM_SLAVE_DELAY_8_RW_0_11    0x7ff    //0x0280
#define    DENALI_PHY_2162_DATA    0x21c8
    #define    PHY_RDDQS_DQ0_RISE_SLAVE_DELAY_8_RW_8_10    0x3ff00    //0x00a0
    #define    PHY_WRLVL_THRESHOLD_ADJUST_8_RW_0_2    0x3    //0x00
#define    DENALI_PHY_2163_DATA    0x21cc
    #define    PHY_RDDQS_DQ1_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2164_DATA    0x21d0
    #define    PHY_RDDQS_DQ2_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2165_DATA    0x21d4
    #define    PHY_RDDQS_DQ3_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2166_DATA    0x21d8
    #define    PHY_RDDQS_DQ4_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2167_DATA    0x21dc
    #define    PHY_RDDQS_DQ5_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2168_DATA    0x21e0
    #define    PHY_RDDQS_DQ6_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2169_DATA    0x21e4
    #define    PHY_RDDQS_DQ7_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2170_DATA    0x21e8
    #define    PHY_RDDQS_DM_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2171_DATA    0x21ec
    #define    PHY_RDDQS_DQ0_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DM_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2172_DATA    0x21f0
    #define    PHY_RDDQS_DQ1_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ0_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2173_DATA    0x21f4
    #define    PHY_RDDQS_DQ2_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ1_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2174_DATA    0x21f8
    #define    PHY_RDDQS_DQ3_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ2_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2175_DATA    0x21fc
    #define    PHY_RDDQS_DQ4_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ3_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2176_DATA    0x2200
    #define    PHY_RDDQS_DQ5_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ4_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2177_DATA    0x2204
    #define    PHY_RDDQS_DQ6_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ5_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2178_DATA    0x2208
    #define    PHY_RDDQS_DQ7_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ6_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2179_DATA    0x220c
    #define    PHY_RDDQS_DM_VH_RISE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x00a0
    #define    PHY_RDDQS_DQ7_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2180_DATA    0x2210
    #define    PHY_RDDQS_GATE_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0033
    #define    PHY_RDDQS_DM_VH_FALL_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x00a0
#define    DENALI_PHY_2181_DATA    0x2214
    #define    PHY_WRLVL_DELAY_EARLY_THRESHOLD_8_RW_16_10    0x3ff0000    //0x01A0
    #define    PHY_WRITE_PATH_LAT_ADD_8_RW_8_3    0x700    //0x00
    #define    PHY_RDDQS_LATENCY_ADJUST_8_RW_0_4    0xf    //0x02
#define    DENALI_PHY_2182_DATA    0x2218
    #define    PHY_WRLVL_EARLY_FORCE_ZERO_8_RW_16_1    0x10000    //0x00
    #define    PHY_WRLVL_DELAY_PERIOD_THRESHOLD_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2183_DATA    0x221c
    #define    PHY_GTLVL_LAT_ADJ_START_8_RW_16_4    0xf0000    //0x01
    #define    PHY_GTLVL_RDDQS_SLV_DLY_START_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2184_DATA    0x2220
    #define    PHY_WDQLVL_DQDM_SLV_DLY_START_8_RW_16_11    0x7ff0000    //0x0200
    #define    PHY_X4_WDQLVL_DQDM_SLV_DLY_START_8_RW_0_11    0x7ff    //0x0200
#define    DENALI_PHY_2185_DATA    0x2224
    #define    PHY_X4_NTP_PASS_8_RW_16_1    0x10000    //0x00
    #define    PHY_NTP_PASS_8_RW_8_1    0x100    //0x00
    #define    PHY_NTP_WRLAT_START_8_RW_0_4    0xf    //0x08
#define    DENALI_PHY_2186_DATA    0x2228
    #define    PHY_X4_WRLVL_THRESHOLD_ADJUST_8_RW_16_2    0x30000    //0x00
    #define    PHY_X4_CLK_WRDQS_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2187_DATA    0x222c
    #define    PHY_X4_WRITE_PATH_LAT_ADD_8_RW_24_3    0x7000000    //0x00
    #define    PHY_X4_RDDQS_LATENCY_ADJUST_8_RW_16_4    0xf0000    //0x02
    #define    PHY_X4_RDDQS_GATE_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0033
#define    DENALI_PHY_2188_DATA    0x2230
    #define    PHY_X4_WRLVL_DELAY_PERIOD_THRESHOLD_8_RW_16_10    0x3ff0000    //0x0000
    #define    PHY_X4_WRLVL_DELAY_EARLY_THRESHOLD_8_RW_0_10    0x3ff    //0x01a0
#define    DENALI_PHY_2189_DATA    0x2234
    #define    PHY_X4_GTLVL_LAT_ADJ_START_8_RW_24_4    0xf000000    //0x00
    #define    PHY_X4_GTLVL_RDDQS_SLV_DLY_START_8_RW_8_10    0x3ff00    //0x0000
    #define    PHY_X4_WRLVL_EARLY_FORCE_ZERO_8_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2190_DATA    0x2238
    #define    PHY_RDLVL_RDDQS_DQ_SLV_DLY_START_8_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2191_DATA    0x223c
    #define    PHY_DATA_DC_DQ2_CLK_ADJUST_8_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ1_CLK_ADJUST_8_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ0_CLK_ADJUST_8_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQS_CLK_ADJUST_8_RW_0_8    0xff    //0x20
#define    DENALI_PHY_2192_DATA    0x2240
    #define    PHY_DATA_DC_DQ6_CLK_ADJUST_8_RW_24_8    0xff000000    //0x20
    #define    PHY_DATA_DC_DQ5_CLK_ADJUST_8_RW_16_8    0xff0000    //0x20
    #define    PHY_DATA_DC_DQ4_CLK_ADJUST_8_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ3_CLK_ADJUST_8_RW_0_8    0xff    //0x20
#define    DENALI_PHY_2193_DATA    0x2244
    #define    PHY_DSLICE_PAD_BOOSTPN_SETTING_8_RW_16_16    0xffff0000    //0x0000
    #define    PHY_DATA_DC_DM_CLK_ADJUST_8_RW_8_8    0xff00    //0x20
    #define    PHY_DATA_DC_DQ7_CLK_ADJUST_8_RW_0_8    0xff    //0x20
#define    DENALI_PHY_2194_DATA    0x2248
    #define    PHY_DSLICE_X4_PAD_RX_CTLE_SETTING_8_RW_24_6    0x3f000000    //0x00
    #define    PHY_DSLICE_X4_PAD_BOOSTPN_SETTING_8_RW_8_16    0xffff00    //0x0000
    #define    PHY_DSLICE_PAD_RX_CTLE_SETTING_8_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_2195_DATA    0x224c
    #define    PHY_X4_DQS_FFE_8_RW_24_2    0x3000000    //0x00
    #define    PHY_X4_DQ_FFE_8_RW_16_2    0x30000    //0x00
    #define    PHY_DQS_FFE_8_RW_8_2    0x300    //0x00
    #define    PHY_DQ_FFE_8_RW_0_2    0x3    //0x00
#define    DENALI_PHY_2196_DATA    0x2250
    #define    PHY_RX_CAL_DQ0_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2197_DATA    0x2254
    #define    PHY_RX_CAL_DQ1_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2198_DATA    0x2258
    #define    PHY_RX_CAL_DQ2_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2199_DATA    0x225c
    #define    PHY_RX_CAL_DQ3_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2200_DATA    0x2260
    #define    PHY_RX_CAL_DQ4_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2201_DATA    0x2264
    #define    PHY_RX_CAL_DQ5_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2202_DATA    0x2268
    #define    PHY_RX_CAL_DQ6_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2203_DATA    0x226c
    #define    PHY_RX_CAL_DQ7_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2204_DATA    0x2270
    #define    PHY_RX_CAL_DM_8_RW_D_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2205_DATA    0x2274
#define    DENALI_PHY_2206_DATA    0x2278
#define    DENALI_PHY_2207_DATA    0x227c
#define    DENALI_PHY_2208_DATA    0x2280
#define    DENALI_PHY_2209_DATA    0x2284
#define    DENALI_PHY_2210_DATA    0x2288
#define    DENALI_PHY_2211_DATA    0x228c
#define    DENALI_PHY_2212_DATA    0x2290
#define    DENALI_PHY_2213_DATA    0x2294
#define    DENALI_PHY_2214_DATA    0x2298
#define    DENALI_PHY_2215_DATA    0x229c
#define    DENALI_PHY_2216_DATA    0x22a0
#define    DENALI_PHY_2217_DATA    0x22a4
#define    DENALI_PHY_2218_DATA    0x22a8
#define    DENALI_PHY_2219_DATA    0x22ac
#define    DENALI_PHY_2220_DATA    0x22b0
#define    DENALI_PHY_2221_DATA    0x22b4
#define    DENALI_PHY_2222_DATA    0x22b8
#define    DENALI_PHY_2223_DATA    0x22bc
#define    DENALI_PHY_2224_DATA    0x22c0
#define    DENALI_PHY_2225_DATA    0x22c4
#define    DENALI_PHY_2226_DATA    0x22c8
#define    DENALI_PHY_2227_DATA    0x22cc
#define    DENALI_PHY_2228_DATA    0x22d0
#define    DENALI_PHY_2229_DATA    0x22d4
#define    DENALI_PHY_2230_DATA    0x22d8
#define    DENALI_PHY_2231_DATA    0x22dc
#define    DENALI_PHY_2232_DATA    0x22e0
#define    DENALI_PHY_2233_DATA    0x22e4
#define    DENALI_PHY_2234_DATA    0x22e8
#define    DENALI_PHY_2235_DATA    0x22ec
#define    DENALI_PHY_2236_DATA    0x22f0
#define    DENALI_PHY_2237_DATA    0x22f4
#define    DENALI_PHY_2238_DATA    0x22f8
#define    DENALI_PHY_2239_DATA    0x22fc
#define    DENALI_PHY_2240_DATA    0x2300
#define    DENALI_PHY_2241_DATA    0x2304
#define    DENALI_PHY_2242_DATA    0x2308
#define    DENALI_PHY_2243_DATA    0x230c
#define    DENALI_PHY_2244_DATA    0x2310
#define    DENALI_PHY_2245_DATA    0x2314
#define    DENALI_PHY_2246_DATA    0x2318
#define    DENALI_PHY_2247_DATA    0x231c
#define    DENALI_PHY_2248_DATA    0x2320
#define    DENALI_PHY_2249_DATA    0x2324
#define    DENALI_PHY_2250_DATA    0x2328
#define    DENALI_PHY_2251_DATA    0x232c
#define    DENALI_PHY_2252_DATA    0x2330
#define    DENALI_PHY_2253_DATA    0x2334
#define    DENALI_PHY_2254_DATA    0x2338
#define    DENALI_PHY_2255_DATA    0x233c
#define    DENALI_PHY_2256_DATA    0x2340
#define    DENALI_PHY_2257_DATA    0x2344
#define    DENALI_PHY_2258_DATA    0x2348
#define    DENALI_PHY_2259_DATA    0x234c
#define    DENALI_PHY_2260_DATA    0x2350
#define    DENALI_PHY_2261_DATA    0x2354
#define    DENALI_PHY_2262_DATA    0x2358
#define    DENALI_PHY_2263_DATA    0x235c
#define    DENALI_PHY_2264_DATA    0x2360
#define    DENALI_PHY_2265_DATA    0x2364
#define    DENALI_PHY_2266_DATA    0x2368
#define    DENALI_PHY_2267_DATA    0x236c
#define    DENALI_PHY_2268_DATA    0x2370
#define    DENALI_PHY_2269_DATA    0x2374
#define    DENALI_PHY_2270_DATA    0x2378
#define    DENALI_PHY_2271_DATA    0x237c
#define    DENALI_PHY_2272_DATA    0x2380
#define    DENALI_PHY_2273_DATA    0x2384
#define    DENALI_PHY_2274_DATA    0x2388
#define    DENALI_PHY_2275_DATA    0x238c
#define    DENALI_PHY_2276_DATA    0x2390
#define    DENALI_PHY_2277_DATA    0x2394
#define    DENALI_PHY_2278_DATA    0x2398
#define    DENALI_PHY_2279_DATA    0x239c
#define    DENALI_PHY_2280_DATA    0x23a0
#define    DENALI_PHY_2281_DATA    0x23a4
#define    DENALI_PHY_2282_DATA    0x23a8
#define    DENALI_PHY_2283_DATA    0x23ac
#define    DENALI_PHY_2284_DATA    0x23b0
#define    DENALI_PHY_2285_DATA    0x23b4
#define    DENALI_PHY_2286_DATA    0x23b8
#define    DENALI_PHY_2287_DATA    0x23bc
#define    DENALI_PHY_2288_DATA    0x23c0
#define    DENALI_PHY_2289_DATA    0x23c4
#define    DENALI_PHY_2290_DATA    0x23c8
#define    DENALI_PHY_2291_DATA    0x23cc
#define    DENALI_PHY_2292_DATA    0x23d0
#define    DENALI_PHY_2293_DATA    0x23d4
#define    DENALI_PHY_2294_DATA    0x23d8
#define    DENALI_PHY_2295_DATA    0x23dc
#define    DENALI_PHY_2296_DATA    0x23e0
#define    DENALI_PHY_2297_DATA    0x23e4
#define    DENALI_PHY_2298_DATA    0x23e8
#define    DENALI_PHY_2299_DATA    0x23ec
#define    DENALI_PHY_2300_DATA    0x23f0
#define    DENALI_PHY_2301_DATA    0x23f4
#define    DENALI_PHY_2302_DATA    0x23f8
#define    DENALI_PHY_2303_DATA    0x23fc
#define    DENALI_PHY_2304_DATA    0x2400
    #define    PHY_FREQ_SEL_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2305_DATA    0x2404
    #define    PHY_DFI40_INACTIVE_RW_24_1    0x1000000    //0x01
    #define    PHY_FREQ_SEL_INDEX_RW_16_1    0x10000    //0x00
    #define    PHY_FREQ_SEL_MULTICAST_EN_RW_8_1    0x100    //0x01
    #define    PHY_FREQ_SEL_FROM_REGIF_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_2306_DATA    0x2408
    #define    PHY_SW_GRP3_SHIFT_0_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_0_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_0_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_0_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2307_DATA    0x240c
    #define    PHY_SW_GRP3_SHIFT_1_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_1_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_1_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_1_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2308_DATA    0x2410
    #define    PHY_SW_GRP3_SHIFT_2_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_2_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_2_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_2_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2309_DATA    0x2414
    #define    PHY_SW_GRP3_SHIFT_3_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_3_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_3_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_3_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2310_DATA    0x2418
    #define    PHY_SW_GRP3_SHIFT_4_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_4_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_4_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_4_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2311_DATA    0x241c
    #define    PHY_SW_GRP3_SHIFT_5_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_5_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_5_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_5_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2312_DATA    0x2420
    #define    PHY_SW_GRP3_SHIFT_6_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_6_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_6_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_6_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2313_DATA    0x2424
    #define    PHY_SW_GRP3_SHIFT_7_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_7_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_7_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_7_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2314_DATA    0x2428
    #define    PHY_SW_GRP3_SHIFT_8_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_GRP2_SHIFT_8_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_GRP1_SHIFT_8_RW_8_4    0xf00    //0x00
    #define    PHY_SW_GRP0_SHIFT_8_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2315_DATA    0x242c
    #define    PHY_GRP_BYPASS_OVERRIDE_RW_24_1    0x1000000    //0x00
    #define    PHY_SW_GRP_BYPASS_SHIFT_RW_16_4    0xf0000    //0x05
    #define    PHY_GRP_BYPASS_SLAVE_DELAY_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2316_DATA    0x2430
    #define    PHY_ADRCTL_MASTER_DLY_LOCK_OBS_SELECT_RW_24_4    0xf000000    //0x00
    #define    PHY_ADRCTL_MANUAL_CLEAR_WR_16_2    0x30000    //0x00
    #define    PHY_MANUAL_UPDATE_PHYUPD_ENABLE_RW_D_8_1    0x100    //0x01
    #define    SC_PHY_MANUAL_UPDATE_WR_0_1    0x1    //0x00
#define    DENALI_PHY_2317_DATA    0x2434
    #define    PHY_ADRCTL_SNAP_OBS_REGS_WR_24_1    0x1000000    //0x00
    #define    PHY_ADRCTL_SLAVE_LOOP_CNT_UPDATE_RW_16_3    0x70000    //0x00
    #define    PHY_ADRCTL_MASTER_DLY_LOCK_OBS_RD_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2318_DATA    0x2438
    #define    PHY_CLK_DC_WEIGHT_RW_24_2    0x3000000    //0x00
    #define    PHY_CLK_DC_CAL_TIMEOUT_RW_16_8    0xff0000    //0x80
    #define    PHY_CLK_DC_CAL_SAMPLE_WAIT_RW_8_8    0xff00    //0x08
    #define    PHY_DFI_PHYUPD_TYPE_RW_0_2    0x3    //0x01
#define    DENALI_PHY_2319_DATA    0x243c
    #define    PHY_CLK_DC_ADJUST_THRSHLD_RW_24_8    0xff000000    //0x08
    #define    PHY_CLK_DC_ADJUST_SAMPLE_CNT_RW_16_8    0xff0000    //0x10
    #define    PHY_CLK_DC_ADJUST_START_RW_8_6    0x3f00    //0x20
    #define    PHY_CLK_DC_FREQ_CHG_ADJ_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2320_DATA    0x2440
    #define    SC_PHY_UPDATE_CLK_CAL_VALUES_WR_24_1    0x1000000    //0x00
    #define    PHY_CLK_DC_CAL_START_RW_16_1    0x10000    //0x00
    #define    PHY_CLK_DC_CAL_POLARITY_RW_8_1    0x100    //0x00
    #define    PHY_CLK_DC_ADJUST_DIRECT_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2321_DATA    0x2444
    #define    PHY_SW_TXIO_CTRL_2_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_TXIO_CTRL_1_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_TXIO_CTRL_0_RW_8_4    0xf00    //0x00
    #define    PHY_CONTINUOUS_CLK_CAL_UPDATE_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2322_DATA    0x2448
    #define    PHY_SW_TXIO_CTRL_6_RW_24_4    0xf000000    //0x00
    #define    PHY_SW_TXIO_CTRL_5_RW_16_4    0xf0000    //0x00
    #define    PHY_SW_TXIO_CTRL_4_RW_8_4    0xf00    //0x00
    #define    PHY_SW_TXIO_CTRL_3_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2323_DATA    0x244c
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_0_RW_24_4    0xf000000    //0x06
    #define    PHY_MEMCLK_SW_TXIO_CTRL_RW_16_1    0x10000    //0x00
    #define    PHY_SW_TXIO_CTRL_8_RW_8_4    0xf00    //0x00
    #define    PHY_SW_TXIO_CTRL_7_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2324_DATA    0x2450
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_4_RW_24_4    0xf000000    //0x0f
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_3_RW_16_4    0xf0000    //0x0f
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_2_RW_8_4    0xf00    //0x0f
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_1_RW_0_4    0xf    //0x0e
#define    DENALI_PHY_2325_DATA    0x2454
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_8_RW_24_4    0xf000000    //0x0f
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_7_RW_16_4    0xf0000    //0x0f
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_6_RW_8_4    0xf00    //0x0f
    #define    PHY_ADRCTL_SW_TXPWR_CTRL_5_RW_0_4    0xf    //0x0f
#define    DENALI_PHY_2326_DATA    0x2458
    #define    PHY_BYTE_DISABLE_STATIC_TOG_DISABLE_RW_16_1    0x10000    //0x01
    #define    PHY_TOP_STATIC_TOG_DISABLE_RW_8_1    0x100    //0x01
    #define    PHY_MEMCLK_SW_TXPWR_CTRL_RW_0_1    0x1    //0x01
#define    DENALI_PHY_2327_DATA    0x245c
    #define    PHY_MEMCLK_STATIC_TOG_DISABLE_RW_24_1    0x1000000    //0x01
    #define    PHY_ADRCTL_STATIC_TOG_DISABLE_RW_16_4    0xf0000    //0x0f
    #define    PHY_STATIC_TOG_CONTROL_RW_0_16    0xffff    //0x0004
#define    DENALI_PHY_2328_DATA    0x2460
    #define    PHY_CLK_SWITCH_OBS_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2329_DATA    0x2464
    #define    PHY_PLL_WAIT_RW_0_16    0xffff    //0x0064
#define    DENALI_PHY_2330_DATA    0x2468
    #define    PHY_SW_PLL_BYPASS_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2331_DATA    0x246c
    #define    PHY_SET_DFI_INPUT_3_RW_D_24_4    0xf000000    //0x00
    #define    PHY_SET_DFI_INPUT_2_RW_D_16_4    0xf0000    //0x00
    #define    PHY_SET_DFI_INPUT_1_RW_D_8_4    0xf00    //0x00
    #define    PHY_SET_DFI_INPUT_0_RW_D_0_4    0xf    //0x00
#define    DENALI_PHY_2332_DATA    0x2470
    #define    PHY_SET_DFI_INPUT_7_RW_D_24_4    0xf000000    //0x00
    #define    PHY_SET_DFI_INPUT_6_RW_D_16_4    0xf0000    //0x00
    #define    PHY_SET_DFI_INPUT_5_RW_D_8_4    0xf00    //0x00
    #define    PHY_SET_DFI_INPUT_4_RW_D_0_4    0xf    //0x00
#define    DENALI_PHY_2333_DATA    0x2474
    #define    PHY_CLK_DC_INIT_DISABLE_RW_24_1    0x1000000    //0x00
    #define    PHY_CLK_DC_ADJUST_1_RW_16_8    0xff0000    //0x20
    #define    PHY_CLK_DC_ADJUST_0_RW_8_8    0xff00    //0x20
    #define    PHY_SET_DFI_INPUT_8_RW_D_0_4    0xf    //0x00
#define    DENALI_PHY_2334_DATA    0x2478
    #define    PHY_USE_PLL_DSKEWCALLOCK_RW_24_1    0x1000000    //0x01
    #define    PHY_PLL_CTRL_OVERRIDE_RW_8_16    0xffff00    //0x0004
    #define    PHY_CLK_DC_DM_THRSHLD_RW_0_8    0xff    //0x80
#define    DENALI_PHY_2335_DATA    0x247c
    #define    SC_PHY_PLL_SPO_CAL_SNAP_OBS_WR_24_2    0x3000000    //0x00
    #define    PHY_PLL_SPO_CAL_CTRL_RW_0_19    0x7ffff    //0x050000
#define    DENALI_PHY_2336_DATA    0x2480
    #define    PHY_PLL_OBS_0_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_2337_DATA    0x2484
    #define    PHY_PLL_SPO_CAL_OBS_0_RD_0_17    0x1ffff    //0x000000
#define    DENALI_PHY_2338_DATA    0x2488
    #define    PHY_PLL_OBS_1_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_2339_DATA    0x248c
    #define    PHY_PLL_TESTOUT_SEL_RW_24_1    0x1000000    //0x01
    #define    PHY_PLL_SPO_CAL_OBS_1_RD_0_17    0x1ffff    //0x000000
#define    DENALI_PHY_2340_DATA    0x2490
    #define    PHY_LS_IDLE_EN_RW_16_1    0x10000    //0x01
    #define    PHY_LP_WAKEUP_RW_8_8    0xff00    //0x07
    #define    PHY_TCKSRE_WAIT_RW_0_4    0xf    //0x0b
#define    DENALI_PHY_2341_DATA    0x2494
    #define    PHY_TDFI_PHY_WRDELAY_RW_16_1    0x10000    //0x00
    #define    PHY_LP_CTRLUPD_CNTR_CFG_RW_0_10    0x3ff    //0x0054
#define    DENALI_PHY_2342_DATA    0x2498
    #define    PHY_TST_CLK_PAD_CTRL_RW_0_32    0xffffffff    //0x04102000
#define    DENALI_PHY_2343_DATA    0x249c
    #define    PHY_PAD_FDBK_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2344_DATA    0x24a0
    #define    PHY_PAD_X4_FDBK_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2345_DATA    0x24a4
    #define    PHY_PAD_DATA_TERM_RW_0_17    0x1ffff    //0x004410
#define    DENALI_PHY_2346_DATA    0x24a8
    #define    PHY_PAD_DQS_TERM_RW_0_17    0x1ffff    //0x004410
#define    DENALI_PHY_2347_DATA    0x24ac
    #define    PHY_PAD_ADDR_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2348_DATA    0x24b0
    #define    PHY_PAD_CLK_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2349_DATA    0x24b4
    #define    PHY_PAD_ERR_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2350_DATA    0x24b8
    #define    PHY_PAD_CKE_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2351_DATA    0x24bc
    #define    PHY_PAD_RST_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2352_DATA    0x24c0
    #define    PHY_PAD_CS_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2353_DATA    0x24c4
    #define    PHY_PAD_ODT_TERM_RW_0_18    0x3ffff    //0x004410
#define    DENALI_PHY_2354_DATA    0x24c8
    #define    PHY_ADRCTL_RX_CAL_RW_0_10    0x3ff    //0x0000
#define    DENALI_PHY_2355_DATA    0x24cc
    #define    PHY_TST_CLK_PAD_CTRL2_RW_0_24    0xffffff    //0x000000
#define    DENALI_PHY_2356_DATA    0x24d0
    #define    PHY_TST_CLK_PAD_CTRL3_RW_0_22    0x3fffff    //0x040000
#define    DENALI_PHY_2357_DATA    0x24d4
    #define    PHY_TST_CLK_PAD_CTRL4_RW_0_27    0x7ffffff    //0x00000000
#define    DENALI_PHY_2358_DATA    0x24d8
    #define    PHY_CAL_START_0_WR_24_1    0x1000000    //0x00
    #define    PHY_CAL_CLEAR_0_WR_16_1    0x10000    //0x00
    #define    PHY_CAL_MODE_0_RW_0_13    0x1fff    //0x0044
#define    DENALI_PHY_2359_DATA    0x24dc
    #define    PHY_CAL_INTERVAL_COUNT_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2360_DATA    0x24e0
    #define    PHY_CAL_RESULT_OBS_0_RD_8_24    0xffffff00    //0x000000
    #define    PHY_CAL_SAMPLE_WAIT_0_RW_0_8    0xff    //0x08
#define    DENALI_PHY_2361_DATA    0x24e4
    #define    PHY_CAL_RESULT2_OBS_0_RD_0_24    0xffffff    //0x000000
#define    DENALI_PHY_2362_DATA    0x24e8
    #define    PHY_CAL_RESULT4_OBS_0_RD_0_24    0xffffff    //0x000000
#define    DENALI_PHY_2363_DATA    0x24ec
    #define    PHY_CAL_RESULT5_OBS_0_RD_0_24    0xffffff    //0x000000
#define    DENALI_PHY_2364_DATA    0x24f0
    #define    PHY_CAL_RESULT6_OBS_0_RD_0_24    0xffffff    //0x000000
#define    DENALI_PHY_2365_DATA    0x24f4
    #define    PHY_CAL_CPTR_CNT_0_RW_24_7    0x7f000000    //0x03
    #define    PHY_CAL_RESULT7_OBS_0_RD_0_24    0xffffff    //0x000000
#define    DENALI_PHY_2366_DATA    0x24f8
    #define    PHY_CAL_DBG_CFG_0_RW_24_1    0x1000000    //0x00
    #define    PHY_CAL_RCV_FINE_ADJ_0_RW_16_8    0xff0000    //0x00
    #define    PHY_CAL_PD_FINE_ADJ_0_RW_8_8    0xff00    //0x00
    #define    PHY_CAL_PU_FINE_ADJ_0_RW_0_8    0xff    //0x00
#define    DENALI_PHY_2367_DATA    0x24fc
    #define    SC_PHY_PAD_DBG_CONT_0_WR_0_1    0x1    //0x00
#define    DENALI_PHY_2368_DATA    0x2500
    #define    PHY_CAL_RESULT3_OBS_0_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2369_DATA    0x2504
    #define    PHY_CAL_SLOPE_ADJ_0_RW_D_8_20    0xfffff00    //0x041020
    #define    PHY_ADRCTL_PVT_MAP_0_RW_0_8    0xff    //0x35
#define    DENALI_PHY_2370_DATA    0x2508
    #define    PHY_CAL_SLOPE_ADJ_PASS2_0_RW_D_0_20    0xfffff    //0x041020
#define    DENALI_PHY_2371_DATA    0x250c
    #define    PHY_CAL_TWO_PASS_CFG_0_RW_D_0_25    0x1ffffff    //0x01c98c98
#define    DENALI_PHY_2372_DATA    0x2510
    #define    PHY_CAL_RANGE_PASS1_PU_MAX_DELTA_0_RW_D_24_6    0x3f000000    //0x3f
    #define    PHY_CAL_SW_CAL_CFG_0_RW_0_23    0x7fffff    //0x400000
#define    DENALI_PHY_2373_DATA    0x2514
    #define    PHY_CAL_RANGE_PASS2_PD_MAX_DELTA_0_RW_D_24_6    0x3f000000    //0x3f
    #define    PHY_CAL_RANGE_PASS2_PU_MAX_DELTA_0_RW_D_16_6    0x3f0000    //0x3f
    #define    PHY_CAL_RANGE_PASS1_RX_MAX_DELTA_0_RW_D_8_5    0x1f00    //0x1f
    #define    PHY_CAL_RANGE_PASS1_PD_MAX_DELTA_0_RW_D_0_6    0x3f    //0x3f
#define    DENALI_PHY_2374_DATA    0x2518
    #define    PHY_CAL_RANGE_PASS1_RX_MIN_DELTA_0_RW_24_5    0x1f000000    //0x1f
    #define    PHY_CAL_RANGE_PASS1_PD_MIN_DELTA_0_RW_16_6    0x3f0000    //0x3f
    #define    PHY_CAL_RANGE_PASS1_PU_MIN_DELTA_0_RW_8_6    0x3f00    //0x3f
    #define    PHY_CAL_RANGE_PASS2_RX_MAX_DELTA_0_RW_D_0_5    0x1f    //0x1f
#define    DENALI_PHY_2375_DATA    0x251c
    #define    PHY_CAL_RANGE_PASS2_RX_MIN_DELTA_0_RW_16_5    0x1f0000    //0x1f
    #define    PHY_CAL_RANGE_PASS2_PD_MIN_DELTA_0_RW_8_6    0x3f00    //0x3f
    #define    PHY_CAL_RANGE_PASS2_PU_MIN_DELTA_0_RW_0_6    0x3f    //0x3f
#define    DENALI_PHY_2376_DATA    0x2520
    #define    PHY_AC_LPBK_ERR_CLEAR_WR_24_1    0x1000000    //0x00
    #define    PHY_ADRCTL_MANUAL_UPDATE_WR_16_1    0x10000    //0x00
    #define    PHY_PAD_ATB_CTRL_RW_0_16    0xffff    //0x0000
#define    DENALI_PHY_2377_DATA    0x2524
    #define    PHY_AC_LPBK_ENABLE_RW_8_9    0x1ff00    //0x0000
    #define    PHY_AC_LPBK_OBS_SELECT_RW_0_4    0xf    //0x00
#define    DENALI_PHY_2378_DATA    0x2528
    #define    PHY_AC_PRBS_PATTERN_MASK_RW_24_4    0xf000000    //0x00
    #define    PHY_AC_PRBS_PATTERN_START_RW_D_16_7    0x7f0000    //0x01
    #define    PHY_AC_LPBK_CONTROL_RW_0_9    0x1ff    //0x0000
#define    DENALI_PHY_2379_DATA    0x252c
    #define    PHY_AC_LPBK_RESULT_OBS_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2380_DATA    0x2530
    #define    PHY_AC_CLK_LPBK_CONTROL_RW_16_6    0x3f0000    //0x00
    #define    PHY_AC_CLK_LPBK_ENABLE_RW_8_2    0x300    //0x00
    #define    PHY_AC_CLK_LPBK_OBS_SELECT_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2381_DATA    0x2534
    #define    PHY_TOP_PWR_RDC_DISABLE_RW_D_24_1    0x1000000    //0x00
    #define    PHY_AC_PWR_RDC_DISABLE_RW_16_1    0x10000    //0x00
    #define    PHY_AC_CLK_LPBK_RESULT_OBS_RD_0_16    0xffff    //0x0000
#define    DENALI_PHY_2382_DATA    0x2538
    #define    PHY_AC_SLV_DLY_CTRL_GATE_DISABLE_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_2383_DATA    0x253c
    #define    PHY_DDL_AC_ENABLE_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2384_DATA    0x2540
    #define    PHY_DDL_AC_MODE_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_PHY_2385_DATA    0x2544
    #define    PHY_DDL_AC_MASK_RW_0_6    0x3f    //0x00
#define    DENALI_PHY_2386_DATA    0x2548
    #define    PHY_DDL_AC_TEST_OBS_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2387_DATA    0x254c
    #define    PHY_DDL_TRACK_UPD_THRESHOLD_AC_RW_16_8    0xff0000    //0x04
    #define    PHY_INIT_UPDATE_CONFIG_RW_8_3    0x700    //0x07
    #define    PHY_DDL_AC_TEST_INDEX_RW_0_2    0x3    //0x00
#define    DENALI_PHY_2388_DATA    0x2550
    #define    PHY_ERR_STATUS_RW_24_3    0x7000000    //0x00
    #define    PHY_ERR_MASK_EN_RW_16_3    0x70000    //0x00
    #define    PHY_CA_PARITY_ERR_PULSE_MIN_RW_0_16    0xffff    //0x0000
#define    DENALI_PHY_2389_DATA    0x2554
    #define    PHY_DS0_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2390_DATA    0x2558
    #define    PHY_DS1_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2391_DATA    0x255c
    #define    PHY_DS2_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2392_DATA    0x2560
    #define    PHY_DS3_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2393_DATA    0x2564
    #define    PHY_DS4_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2394_DATA    0x2568
    #define    PHY_DS5_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2395_DATA    0x256c
    #define    PHY_DS6_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2396_DATA    0x2570
    #define    PHY_DS7_DQS_ERR_COUNTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PHY_2397_DATA    0x2574
    #define    PHY_AC_INIT_COMPLETE_OBS_RD_8_17    0x1ffff00    //0x000000
    #define    PHY_DLL_RST_EN_RW_D_0_2    0x3    //0x02
#define    DENALI_PHY_2398_DATA    0x2578
    #define    PHY_ERR_IE_RW_24_1    0x1000000    //0x01
    #define    PHY_UPDATE_MASK_RW_16_1    0x10000    //0x00
    #define    PHY_DS_INIT_COMPLETE_OBS_RD_0_9    0x1ff    //0x0000
#define    DENALI_PHY_2399_DATA    0x257c
    #define    PHY_GRP_SHIFT_OBS_SELECT_RW_16_6    0x3f0000    //0x00
    #define    PHY_GRP_SLV_DLY_ENC_OBS_SELECT_RW_8_7    0x7f00    //0x00
    #define    PHY_AC_DCC_RXCAL_CTRL_GATE_DISABLE_RW_D_0_1    0x1    //0x00
#define    DENALI_PHY_2400_DATA    0x2580
    #define    PHY_GRP_SHIFT_OBS_RD_16_2    0x30000    //0x00
    #define    PHY_GRP_SLV_DLY_ENC_OBS_RD_0_11    0x7ff    //0x0000
#define    DENALI_PHY_2401_DATA    0x2584
    #define    PHY_PAD_CAL_IO_CFG_0_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PHY_2402_DATA    0x2588
    #define    PHY_PAD_ACS_RX_PCLK_CLK_SEL_RW_24_3    0x7000000    //0x00
    #define    PHY_PAD_ACS_IO_CFG_RW_0_17    0x1ffff    //0x000000
#define    DENALI_PHY_2403_DATA    0x258c
    #define    PHY_PAD_ADR_RX_PCLK_CLK_SEL_RW_24_3    0x7000000    //0x00
    #define    PHY_PAD_ADR_IO_CFG_RW_0_19    0x7ffff    //0x000000
#define    DENALI_PHY_2404_DATA    0x2590
    #define    PHY_PLL_BYPASS_RW_0_1    0x1    //0x00
#define    DENALI_PHY_2405_DATA    0x2594
    #define    PHY_LOW_FREQ_SEL_RW_16_1    0x10000    //0x00
    #define    PHY_PLL_CTRL_RW_0_13    0x1fff    //0x1142
#define    DENALI_PHY_2406_DATA    0x2598
    #define    PHY_ADRCTL_SW_MASTER_MODE_RW_16_4    0xf0000    //0x00
    #define    PHY_PAD_VREF_CTRL_AC_RW_0_12    0xfff    //0x0400
#define    DENALI_PHY_2407_DATA    0x259c
    #define    PHY_ADRCTL_MASTER_DELAY_WAIT_RW_24_8    0xff000000    //0x42
    #define    PHY_ADRCTL_MASTER_DELAY_STEP_RW_16_6    0x3f0000    //0x08
    #define    PHY_ADRCTL_MASTER_DELAY_START_RW_0_11    0x7ff    //0x0010
#define    DENALI_PHY_2408_DATA    0x25a0
    #define    PHY_GRP0_SLAVE_DELAY_0_RW_8_10    0x3ff00    //0x0100
    #define    PHY_ADRCTL_MASTER_DELAY_HALF_MEASURE_RW_0_8    0xff    //0x3e
#define    DENALI_PHY_2409_DATA    0x25a4
    #define    PHY_GRP2_SLAVE_DELAY_0_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2410_DATA    0x25a8
    #define    PHY_GRP0_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_0_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2411_DATA    0x25ac
    #define    PHY_GRP2_SLAVE_DELAY_1_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2412_DATA    0x25b0
    #define    PHY_GRP0_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_1_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2413_DATA    0x25b4
    #define    PHY_GRP2_SLAVE_DELAY_2_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2414_DATA    0x25b8
    #define    PHY_GRP0_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_2_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2415_DATA    0x25bc
    #define    PHY_GRP2_SLAVE_DELAY_3_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2416_DATA    0x25c0
    #define    PHY_GRP0_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_3_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2417_DATA    0x25c4
    #define    PHY_GRP2_SLAVE_DELAY_4_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2418_DATA    0x25c8
    #define    PHY_GRP0_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_4_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2419_DATA    0x25cc
    #define    PHY_GRP2_SLAVE_DELAY_5_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2420_DATA    0x25d0
    #define    PHY_GRP0_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_5_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2421_DATA    0x25d4
    #define    PHY_GRP2_SLAVE_DELAY_6_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2422_DATA    0x25d8
    #define    PHY_GRP0_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_6_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2423_DATA    0x25dc
    #define    PHY_GRP2_SLAVE_DELAY_7_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP1_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2424_DATA    0x25e0
    #define    PHY_GRP0_SLAVE_DELAY_8_RW_16_10    0x3ff0000    //0x0100
    #define    PHY_GRP3_SLAVE_DELAY_7_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2425_DATA    0x25e4
    #define    PHY_GRP1_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2426_DATA    0x25e8
    #define    PHY_GRP2_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2427_DATA    0x25ec
    #define    PHY_GRP3_SLAVE_DELAY_8_RW_0_10    0x3ff    //0x0100
#define    DENALI_PHY_2428_DATA    0x25f0
    #define    PHY_CLK_DC_CAL_CLK_SEL_RW_0_3    0x7    //0x02
#define    DENALI_PHY_2429_DATA    0x25f4
    #define    PHY_PAD_FDBK_DRIVE_RW_0_30    0x3fffffff    //0x000200ff
#define    DENALI_PHY_2430_DATA    0x25f8
    #define    PHY_PAD_FDBK_DRIVE2_RW_0_19    0x7ffff    //0x020008
#define    DENALI_PHY_2431_DATA    0x25fc
    #define    PHY_PAD_X4_FDBK_DRIVE_RW_0_30    0x3fffffff    //0x000200ff
#define    DENALI_PHY_2432_DATA    0x2600
    #define    PHY_PAD_X4_FDBK_DRIVE2_RW_0_19    0x7ffff    //0x020008
#define    DENALI_PHY_2433_DATA    0x2604
    #define    PHY_PAD_DATA_DRIVE_RW_0_31    0x7fffffff    //0x08000800
#define    DENALI_PHY_2434_DATA    0x2608
    #define    PHY_PAD_DQS_DRIVE_RW_0_32    0xffffffff    //0x00000100
#define    DENALI_PHY_2435_DATA    0x260c
    #define    PHY_PAD_ADDR_DRIVE_RW_0_30    0x3fffffff    //0x00010011
#define    DENALI_PHY_2436_DATA    0x2610
    #define    PHY_PAD_ADDR_DRIVE2_RW_0_28    0xfffffff    //0x01ffff00
#define    DENALI_PHY_2437_DATA    0x2614
    #define    PHY_PAD_CLK_DRIVE_RW_0_32    0xffffffff    //0x000100ff
#define    DENALI_PHY_2438_DATA    0x2618
    #define    PHY_PAD_CLK_DRIVE2_RW_0_19    0x7ffff    //0x008011
#define    DENALI_PHY_2439_DATA    0x261c
    #define    PHY_PAD_ERR_DRIVE_RW_0_30    0x3fffffff    //0x00010011
#define    DENALI_PHY_2440_DATA    0x2620
    #define    PHY_PAD_ERR_DRIVE2_RW_0_28    0xfffffff    //0x01ffff00
#define    DENALI_PHY_2441_DATA    0x2624
    #define    PHY_PAD_CKE_DRIVE_RW_0_30    0x3fffffff    //0x00010011
#define    DENALI_PHY_2442_DATA    0x2628
    #define    PHY_PAD_CKE_DRIVE2_RW_0_28    0xfffffff    //0x01ffff00
#define    DENALI_PHY_2443_DATA    0x262c
    #define    PHY_PAD_RST_DRIVE_RW_0_30    0x3fffffff    //0x00010011
#define    DENALI_PHY_2444_DATA    0x2630
    #define    PHY_PAD_RST_DRIVE2_RW_0_28    0xfffffff    //0x01ffff00
#define    DENALI_PHY_2445_DATA    0x2634
    #define    PHY_PAD_CS_DRIVE_RW_0_30    0x3fffffff    //0x00010011
#define    DENALI_PHY_2446_DATA    0x2638
    #define    PHY_PAD_CS_DRIVE2_RW_0_28    0xfffffff    //0x01ffff00
#define    DENALI_PHY_2447_DATA    0x263c
    #define    PHY_PAD_ODT_DRIVE_RW_0_30    0x3fffffff    //0x00010011
#define    DENALI_PHY_2448_DATA    0x2640
    #define    PHY_PAD_ODT_DRIVE2_RW_0_28    0xfffffff    //0x01ffff00
#define    DENALI_PHY_2449_DATA    0x2644
    #define    PHY_CAL_SETTLING_PRD_0_RW_24_7    0x7f000000    //0x20
    #define    PHY_CAL_VREF_SWITCH_TIMER_0_RW_8_16    0xffff00    //0x0400
    #define    PHY_CAL_CLK_SELECT_0_RW_0_3    0x7    //0x00

