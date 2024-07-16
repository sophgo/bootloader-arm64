#define    DENALI_CTL_0_DATA    0x0
    #define    CONTROLLER_ID_RD_16_16    0xffff0000    //0x0000
    #define    DRAM_CLASS_RW_8_4    0xf00    //0x0a
    #define    START_RW_0_1    0x1    //0x00
#define    DENALI_CTL_1_DATA    0x4
    #define    CONTROLLER_VERSION_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_2_DATA    0x8
    #define    CONTROLLER_VERSION_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_3_DATA    0xc
    #define    WRITE_DATA_FIFO_DEPTH_RD_24_8    0xff000000    //0x00
    #define    MAX_CS_REG_RD_16_2    0x30000    //0x00
    #define    MAX_COL_REG_RD_8_4    0xf00    //0x00
    #define    MAX_ROW_REG_RD_0_5    0x1f    //0x00
#define    DENALI_CTL_4_DATA    0x10
    #define    MEMCD_RMODW_FIFO_PTR_WIDTH_RD_24_8    0xff000000    //0x00
    #define    MEMCD_RMODW_FIFO_DEPTH_RD_8_16    0xffff00    //0x0000
    #define    WRITE_DATA_FIFO_PTR_WIDTH_RD_0_8    0xff    //0x00
#define    DENALI_CTL_5_DATA    0x14
    #define    AXI0_WR_ARRAY_LOG2_DEPTH_RD_24_8    0xff000000    //0x00
    #define    AXI0_RDFIFO_LOG2_DEPTH_RD_16_8    0xff0000    //0x00
    #define    AXI0_CMDFIFO_LOG2_DEPTH_RD_8_8    0xff00    //0x00
    #define    ASYNC_CDC_STAGES_RD_0_8    0xff    //0x00
#define    DENALI_CTL_6_DATA    0x18
    #define    AXI0_WRCMD_PROC_FIFO_LOG2_DEPTH_RD_8_8    0xff00    //0x00
    #define    AXI0_TRANS_WRFIFO_LOG2_DEPTH_RD_0_8    0xff    //0x00
#define    DENALI_CTL_7_DATA    0x1c
    #define    TINIT_F0_RW_0_24    0xffffff    //0x000010
#define    DENALI_CTL_8_DATA    0x20
    #define    PHY_INDEP_TRAIN_MODE_RW_24_1    0x1000000    //0x01
    #define    TINIT_F1_RW_0_24    0xffffff    //0x000010
#define    DENALI_CTL_9_DATA    0x24
    #define    DFIBUS_FREQ_F1_RW_24_5    0x1f000000    //0x01
    #define    DFIBUS_FREQ_F0_RW_16_5    0x1f0000    //0x00
    #define    PHY_INDEP_INIT_MODE_RW_8_1    0x100    //0x00
    #define    TSREF2PHYMSTR_RW_0_6    0x3f    //0x10
#define    DENALI_CTL_10_DATA    0x28
    #define    FREQ_CHANGE_TYPE_F1_RW_8_1    0x100    //0x01
    #define    FREQ_CHANGE_TYPE_F0_RW_0_1    0x1    //0x00
#define    DENALI_CTL_11_DATA    0x2c
    #define    TRST_PWRON_RW_0_32    0xffffffff    //0x00000140
#define    DENALI_CTL_12_DATA    0x30
    #define    CKE_INACTIVE_RW_0_32    0xffffffff    //0x00000322
#define    DENALI_CTL_13_DATA    0x34
    #define    TDLL_F1_RW_16_16    0xffff0000    //0x0400
    #define    TDLL_F0_RW_0_16    0xffff    //0x0400
#define    DENALI_CTL_14_DATA    0x38
    #define    CA_PARITY_LAT_F0_RW_24_4    0xf000000    //0x06
    #define    ADDITIVE_LAT_F0_RW_16_5    0x1f0000    //0x00
    #define    WRLAT_F0_RW_8_5    0x1f00    //0x10
    #define    CASLAT_LIN_F0_RW_0_6    0x3f    //0x30
#define    DENALI_CTL_15_DATA    0x3c
    #define    TMRD_PAR_MAX_PL_F0_RW_24_8    0xff000000    //0x1e
    #define    TMOD_PAR_MAX_PL_F0_RW_16_8    0xff0000    //0x1e
    #define    TMRD_PAR_F0_RW_8_8    0xff00    //0x1e
    #define    TMOD_PAR_F0_RW_0_8    0xff    //0x1e
#define    DENALI_CTL_16_DATA    0x40
    #define    CA_PARITY_LAT_F1_RW_24_4    0xf000000    //0x06
    #define    ADDITIVE_LAT_F1_RW_16_5    0x1f0000    //0x00
    #define    WRLAT_F1_RW_8_5    0x1f00    //0x10
    #define    CASLAT_LIN_F1_RW_0_6    0x3f    //0x30
#define    DENALI_CTL_17_DATA    0x44
    #define    TMRD_PAR_MAX_PL_F1_RW_24_8    0xff000000    //0x1e
    #define    TMOD_PAR_MAX_PL_F1_RW_16_8    0xff0000    //0x1e
    #define    TMRD_PAR_F1_RW_8_8    0xff00    //0x1e
    #define    TMOD_PAR_F1_RW_0_8    0xff    //0x1e
#define    DENALI_CTL_18_DATA    0x48
    #define    TRRD_F0_RW_24_8    0xff000000    //0x05
    #define    TCCD_L_F0_RW_16_5    0x1f0000    //0x08
    #define    TCCD_RW_8_5    0x1f00    //0x04
    #define    TBST_INT_INTERVAL_RW_0_3    0x7    //0x04
#define    DENALI_CTL_19_DATA    0x4c
    #define    TRC_F0_RW_16_9    0x1ff0000    //0x004c
    #define    TRRD_DLR_F0_RW_8_8    0xff00    //0x00
    #define    TRRD_L_F0_RW_0_8    0xff    //0x08
#define    DENALI_CTL_20_DATA    0x50
    #define    TWTR_L_F0_RW_24_6    0x3f000000    //0x0c
    #define    TWTR_F0_RW_16_6    0x3f0000    //0x04
    #define    TRAS_MIN_F0_RW_0_9    0x1ff    //0x0035
#define    DENALI_CTL_21_DATA    0x54
    #define    TFAW_F0_RW_8_9    0x1ff00    //0x0023
    #define    TRP_F0_RW_0_8    0xff    //0x18
#define    DENALI_CTL_22_DATA    0x58
    #define    TRRD_F1_RW_24_8    0xff000000    //0x05
    #define    TCCD_L_F1_RW_16_5    0x1f0000    //0x08
    #define    TFAW_DLR_F0_RW_0_9    0x1ff    //0x0000
#define    DENALI_CTL_23_DATA    0x5c
    #define    TRC_F1_RW_16_9    0x1ff0000    //0x004c
    #define    TRRD_DLR_F1_RW_8_8    0xff00    //0x00
    #define    TRRD_L_F1_RW_0_8    0xff    //0x08
#define    DENALI_CTL_24_DATA    0x60
    #define    TWTR_L_F1_RW_24_6    0x3f000000    //0x0c
    #define    TWTR_F1_RW_16_6    0x3f0000    //0x04
    #define    TRAS_MIN_F1_RW_0_9    0x1ff    //0x0035
#define    DENALI_CTL_25_DATA    0x64
    #define    TFAW_F1_RW_8_9    0x1ff00    //0x0023
    #define    TRP_F1_RW_0_8    0xff    //0x18
#define    DENALI_CTL_26_DATA    0x68
    #define    TRTP_F0_RW_24_8    0xff000000    //0x0d
    #define    TCCD_DLR_RW_16_5    0x1f0000    //0x00
    #define    TFAW_DLR_F1_RW_0_9    0x1ff    //0x0000
#define    DENALI_CTL_27_DATA    0x6c
    #define    TMOD_F0_RW_16_8    0xff0000    //0x18
    #define    TMRD_F0_RW_8_8    0xff00    //0x08
    #define    TRTP_AP_F0_RW_0_8    0xff    //0x0d
#define    DENALI_CTL_28_DATA    0x70
    #define    TCKE_F0_RW_24_4    0xf000000    //0x08
    #define    TRAS_MAX_F0_RW_0_20    0xfffff    //0x01b6c0
#define    DENALI_CTL_29_DATA    0x74
    #define    TMRD_F1_RW_24_8    0xff000000    //0x08
    #define    TRTP_AP_F1_RW_16_8    0xff0000    //0x0d
    #define    TRTP_F1_RW_8_8    0xff00    //0x0d
    #define    TCKESR_F0_RW_0_8    0xff    //0x0f
#define    DENALI_CTL_30_DATA    0x78
    #define    TRAS_MAX_F1_RW_8_20    0xfffff00    //0x01b6c0
    #define    TMOD_F1_RW_0_8    0xff    //0x18
#define    DENALI_CTL_31_DATA    0x7c
    #define    RESERVED_RW_24_3    0x7000000    //0x03
    #define    RESERVED_RW_16_3    0x70000    //0x03
    #define    TCKESR_F1_RW_8_8    0xff00    //0x0f
    #define    TCKE_F1_RW_0_4    0xf    //0x08
#define    DENALI_CTL_32_DATA    0x80
    #define    TRCD_F1_RW_24_8    0xff000000    //0x19
    #define    TWR_F0_RW_16_8    0xff0000    //0x19
    #define    TRCD_F0_RW_8_8    0xff00    //0x19
    #define    WRITEINTERP_RW_0_1    0x1    //0x00
#define    DENALI_CTL_33_DATA    0x84
    #define    TMRD_PDA_RW_24_8    0xff000000    //0x18
    #define    TVREF_RW_8_16    0xffff00    //0x00f0
    #define    TWR_F1_RW_0_8    0xff    //0x19
#define    DENALI_CTL_34_DATA    0x88
    #define    TDAL_F0_RW_24_8    0xff000000    //0x32
    #define    TRAS_LOCKOUT_RW_16_1    0x10000    //0x01
    #define    CONCURRENTAP_RW_8_1    0x100    //0x01
    #define    AP_RW_0_1    0x1    //0x00
#define    DENALI_CTL_35_DATA    0x8c
    #define    TRP_AB_F1_0_RW_24_8    0xff000000    //0x18
    #define    TRP_AB_F0_0_RW_16_8    0xff0000    //0x18
    #define    BSTLEN_RW_D_8_3    0x700    //0x03
    #define    TDAL_F1_RW_0_8    0xff    //0x32
#define    DENALI_CTL_36_DATA    0x90
    #define    LOGICAL_CS_MAP_RW_24_2    0x3000000    //0x00
    #define    MEM_3DS_SUPPORT_EN_RW_16_1    0x10000    //0x00
    #define    TRP_AB_F1_1_RW_8_8    0xff00    //0x18
    #define    TRP_AB_F0_1_RW_0_8    0xff    //0x18
#define    DENALI_CTL_37_DATA    0x94
    #define    ADDRESS_INVERSION_RW_24_2    0x3000000    //0x00
    #define    ADDRESS_MIRRORING_RW_16_2    0x30000    //0x00
    #define    REG_DIMM_ENABLE_RW_8_1    0x100    //0x00
    #define    PRECHARGE_DLR_RW_0_8    0xff    //0x08
#define    DENALI_CTL_38_DATA    0x98
    #define    PDA_INVERT_DEV_CS1_RW_16_16    0xffff0000    //0x0000
    #define    PDA_INVERT_DEV_CS0_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_39_DATA    0x9c
    #define    RESERVED_RW_24_1    0x1000000    //0x01
    #define    OPTIMAL_RMODW_EN_RW_16_1    0x10000    //0x01
    #define    PDA_INVERT_ECC_DEV_CS1_RW_8_2    0x300    //0x00
    #define    PDA_INVERT_ECC_DEV_CS0_RW_0_2    0x3    //0x00
#define    DENALI_CTL_40_DATA    0xa0
    #define    CWW_SW_PROMOTE_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0000
    #define    RDIMM_CWW_ERROR_STATUS_RD_8_1    0x100    //0x00
    #define    NO_MEMORY_DM_RW_0_1    0x1    //0x00
#define    DENALI_CTL_41_DATA    0xa4
    #define    RDIMM_TMRD_RW_24_8    0xff000000    //0x08
    #define    RDIMM_CWW_REQ_WR_16_1    0x10000    //0x00
    #define    CWW_SW_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_42_DATA    0xa8
    #define    RDIMM_CTL_F0_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_43_DATA    0xac
    #define    RDIMM_CTL_F0_0_RW_0_32    0xffffffff    //0x40400608
#define    DENALI_CTL_44_DATA    0xb0
    #define    RDIMM_CTL_F0_0_RW_0_32    0xffffffff    //0x00610100
#define    DENALI_CTL_45_DATA    0xb4
    #define    RDIMM_CTL_F0_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_46_DATA    0xb8
    #define    RDIMM_CTL_F0_0_RW_0_32    0xffffffff    //0x000000
#define    DENALI_CTL_47_DATA    0xbc
    #define    RDIMM_CTL_F1_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_48_DATA    0xc0
    #define    RDIMM_CTL_F1_0_RW_0_32    0xffffffff    //0x40400608
#define    DENALI_CTL_49_DATA    0xc4
    #define    RDIMM_CTL_F1_0_RW_0_32    0xffffffff    //0x00610100
#define    DENALI_CTL_50_DATA    0xc8
    #define    RDIMM_CTL_F1_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_51_DATA    0xcc
    #define    RDIMM_CTL_F1_0_RW_0_32    0xffffffff    //0x000000
#define    DENALI_CTL_52_DATA    0xd0
    #define    RDIMM_CTL_F0_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_53_DATA    0xd4
    #define    RDIMM_CTL_F0_1_RW_0_32    0xffffffff    //0x40400608
#define    DENALI_CTL_54_DATA    0xd8
    #define    RDIMM_CTL_F0_1_RW_0_32    0xffffffff    //0x00610100
#define    DENALI_CTL_55_DATA    0xdc
    #define    RDIMM_CTL_F0_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_56_DATA    0xe0
    #define    RDIMM_CTL_F0_1_RW_0_32    0xffffffff    //0x000000
#define    DENALI_CTL_57_DATA    0xe4
    #define    RDIMM_CTL_F1_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_58_DATA    0xe8
    #define    RDIMM_CTL_F1_1_RW_0_32    0xffffffff    //0x40400608
#define    DENALI_CTL_59_DATA    0xec
    #define    RDIMM_CTL_F1_1_RW_0_32    0xffffffff    //0x00610100
#define    DENALI_CTL_60_DATA    0xf0
    #define    RDIMM_CTL_F1_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_61_DATA    0xf4
    #define    RDIMM_CTL_F1_1_RW_0_32    0xffffffff    //0x000000
#define    DENALI_CTL_62_DATA    0xf8
    #define    RDIMM_DFS_CW_MAP_F0_RW_0_27    0x7ffffff    //0x07fbff3f
#define    DENALI_CTL_63_DATA    0xfc
    #define    RDIMM_DFS_CW_MAP_F1_RW_0_27    0x7ffffff    //0x07fbff3f
#define    DENALI_CTL_64_DATA    0x100
    #define    RDIMM_DFS_SKIP_PWR_DN_WAIT_RW_0_1    0x1    //0x01
#define    DENALI_CTL_65_DATA    0x104
    #define    RDIMM_CW_MAP_RW_0_27    0x7ffffff    //0x07fbff3f
#define    DENALI_CTL_66_DATA    0x108
    #define    RDIMM_TSTAB_F0_RW_8_24    0xffffff00    //0x001f40
    #define    RDIMM_CW_HOLD_CKE_EN_RW_0_1    0x1    //0x00
#define    DENALI_CTL_67_DATA    0x10c
    #define    CS_MAP_DIMM_0_RW_24_2    0x3000000    //0x03
    #define    RDIMM_TSTAB_F1_RW_0_24    0xffffff    //0x001f40
#define    DENALI_CTL_68_DATA    0x110
    #define    DDR4_DIMM_CID1_MAP_RW_24_2    0x3000000    //0x00
    #define    DDR4_DIMM_CID0_MAP_RW_16_2    0x30000    //0x00
    #define    DDR4_DIMM_3DS_PIN_MUXING_EN_RW_8_1    0x100    //0x00
    #define    CS_MAP_DIMM_1_RW_0_2    0x3    //0x00
#define    DENALI_CTL_69_DATA    0x114
    #define    RDIMM_TMRD_L2_RW_24_6    0x3f000000    //0x20
    #define    RDIMM_TMRD_L_RW_16_5    0x1f0000    //0x10
    #define    RANK0_MAP_DIMM_1_RW_8_2    0x300    //0x00
    #define    RANK0_MAP_DIMM_0_RW_0_2    0x3    //0x01
#define    DENALI_CTL_70_DATA    0x118
    #define    RDIMM_TCPDED_RW_8_4    0xf00    //0x01
    #define    RDIMM_TMRC_RW_0_5    0x1f    //0x10
#define    DENALI_CTL_71_DATA    0x11c
    #define    RDIMM_CWW_INIT_MAP_CKE_LOW_RW_0_27    0x7ffffff    //0x00000000
#define    DENALI_CTL_72_DATA    0x120
    #define    RDIMM_CKE_PWR_DN_DFS_DELAY_RW_0_16    0xffff    //0x0010
#define    DENALI_CTL_73_DATA    0x124
    #define    CA_PARITY_ERROR_INJECT_RW_0_27    0x7ffffff    //0x00000000
#define    DENALI_CTL_74_DATA    0x128
    #define    TREF_ENABLE_RW_24_1    0x1000000    //0x01
    #define    AREF_STATUS_RD_16_1    0x10000    //0x00
    #define    AREFRESH_WR_8_1    0x100    //0x00
    #define    CA_PARITY_ERROR_RD_0_1    0x1    //0x00
#define    DENALI_CTL_75_DATA    0x12c
    #define    TRFC_F0_RW_16_10    0x3ff0000    //0x0100
    #define    CS_COMPARISON_FOR_REFRESH_DEPTH_RW_8_6    0x3f00    //0x10
    #define    RESERVED_RW_0_3    0x7    //0x03
#define    DENALI_CTL_76_DATA    0x130
    #define    TREF_F0_RW_0_20    0xfffff    //0x0030c0
#define    DENALI_CTL_77_DATA    0x134
    #define    TRFC_F1_RW_16_10    0x3ff0000    //0x0100
    #define    TRFC_DLR_F0_RW_0_10    0x3ff    //0x0080
#define    DENALI_CTL_78_DATA    0x138
    #define    TREF_F1_RW_0_20    0xfffff    //0x0030c0
#define    DENALI_CTL_79_DATA    0x13c
    #define    TRFC_DLR_F1_RW_0_10    0x3ff    //0x0080
#define    DENALI_CTL_80_DATA    0x140
    #define    TREF_INTERVAL_RW_0_20    0xfffff    //0x000005
#define    DENALI_CTL_81_DATA    0x144
    #define    TPDEX_F1_RW_16_16    0xffff0000    //0x0010
    #define    TPDEX_F0_RW_0_16    0xffff    //0x0010
#define    DENALI_CTL_82_DATA    0x148
    #define    TXPDLL_F1_RW_16_16    0xffff0000    //0x0027
    #define    TXPDLL_F0_RW_0_16    0xffff    //0x0027
#define    DENALI_CTL_83_DATA    0x14c
    #define    TXSNR_F0_RW_16_16    0xffff0000    //0x0110
    #define    TXSR_F0_RW_0_16    0xffff    //0x0400
#define    DENALI_CTL_84_DATA    0x150
    #define    TXSNR_F1_RW_16_16    0xffff0000    //0x0110
    #define    TXSR_F1_RW_0_16    0xffff    //0x0400
#define    DENALI_CTL_85_DATA    0x154
    #define    TXPR_F1_RW_16_16    0xffff0000    //0x0110
    #define    TXPR_F0_RW_0_16    0xffff    //0x0110
#define    DENALI_CTL_86_DATA    0x158
    #define    CKE_DELAY_RW_24_3    0x7000000    //0x03
    #define    ENABLE_QUICK_SREFRESH_RW_16_1    0x10000    //0x01
    #define    RESERVED_RW_8_1    0x100    //0x00
    #define    PWRUP_SREFRESH_EXIT_RW_0_1    0x1    //0x00
#define    DENALI_CTL_87_DATA    0x15c
    #define    DFS_ZQ_EN_RW_16_1    0x10000    //0x01
    #define    DFS_STATUS_RD_8_2    0x300    //0x00
    #define    RESERVED_WR_0_4    0xf    //0x00
#define    DENALI_CTL_88_DATA    0x160
    #define    DFS_PROMOTE_THRESHOLD_F1_RW_16_16    0xffff0000    //0x0000
    #define    DFS_PROMOTE_THRESHOLD_F0_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_89_DATA    0x164
    #define    RESERVED_RW_24_8    0xff000000    //0x40
    #define    RESERVED_RW_16_3    0x70000    //0x02
    #define    RESERVED_RW_8_3    0x700    //0x01
    #define    ZQ_STATUS_LOG_RD_0_1    0x1    //0x00
#define    DENALI_CTL_90_DATA    0x168
    #define    UPD_CTRLUPD_NORM_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0003
    #define    RESERVED_RW_8_8    0xff00    //0x80
    #define    RESERVED_RW_0_8    0xff    //0x10
#define    DENALI_CTL_91_DATA    0x16c
    #define    UPD_CTRLUPD_TIMEOUT_F0_RW_16_16    0xffff0000    //0x0005
    #define    UPD_CTRLUPD_HIGH_THRESHOLD_F0_RW_0_16    0xffff    //0x0004
#define    DENALI_CTL_92_DATA    0x170
    #define    UPD_PHYUPD_DFI_PROMOTE_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0000
    #define    UPD_CTRLUPD_SW_PROMOTE_THRESHOLD_F0_RW_0_16    0xffff    //0x0004
#define    DENALI_CTL_93_DATA    0x174
    #define    UPD_CTRLUPD_HIGH_THRESHOLD_F1_RW_16_16    0xffff0000    //0x0004
    #define    UPD_CTRLUPD_NORM_THRESHOLD_F1_RW_0_16    0xffff    //0x0003
#define    DENALI_CTL_94_DATA    0x178
    #define    UPD_CTRLUPD_SW_PROMOTE_THRESHOLD_F1_RW_16_16    0xffff0000    //0x0004
    #define    UPD_CTRLUPD_TIMEOUT_F1_RW_0_16    0xffff    //0x0005
#define    DENALI_CTL_95_DATA    0x17c
    #define    UPD_PHYUPD_DFI_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_96_DATA    0x180
    #define    TDFI_PHYMSTR_MAX_F0_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_97_DATA    0x184
    #define    TDFI_PHYMSTR_MAX_TYPE0_F0_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_98_DATA    0x188
    #define    TDFI_PHYMSTR_MAX_TYPE1_F0_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_99_DATA    0x18c
    #define    TDFI_PHYMSTR_MAX_TYPE2_F0_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_100_DATA    0x190
    #define    TDFI_PHYMSTR_MAX_TYPE3_F0_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_101_DATA    0x194
    #define    PHYMSTR_DFI4_PROMOTE_THRESHOLD_F0_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_102_DATA    0x198
    #define    TDFI_PHYMSTR_RESP_F0_RW_0_20    0xfffff    //0x015540
#define    DENALI_CTL_103_DATA    0x19c
    #define    TDFI_PHYMSTR_MAX_F1_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_104_DATA    0x1a0
    #define    TDFI_PHYMSTR_MAX_TYPE0_F1_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_105_DATA    0x1a4
    #define    TDFI_PHYMSTR_MAX_TYPE1_F1_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_106_DATA    0x1a8
    #define    TDFI_PHYMSTR_MAX_TYPE2_F1_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_107_DATA    0x1ac
    #define    TDFI_PHYMSTR_MAX_TYPE3_F1_RW_0_32    0xffffffff    //0x000c3000
#define    DENALI_CTL_108_DATA    0x1b0
    #define    PHYMSTR_DFI4_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_109_DATA    0x1b4
    #define    PHYMSTR_NO_AREF_RW_24_1    0x1000000    //0x00
    #define    TDFI_PHYMSTR_RESP_F1_RW_0_20    0xfffff    //0x015540
#define    DENALI_CTL_110_DATA    0x1b8
    #define    PPR_CONTROL_RW_24_1    0x1000000    //0x00
    #define    PHYMSTR_TRAIN_AFTER_INIT_COMPLETE_RW_16_1    0x10000    //0x00
    #define    PHYMSTR_DFI_VERSION_4P0V1_RW_8_1    0x100    //0x00
    #define    PHYMSTR_ERROR_STATUS_RD_0_2    0x3    //0x00
#define    DENALI_CTL_111_DATA    0x1bc
    #define    PPR_COMMAND_MRW_RW_8_4    0xf00    //0x00
    #define    PPR_COMMAND_WR_0_3    0x7    //0x00
#define    DENALI_CTL_112_DATA    0x1c0
    #define    PPR_BANK_ADDRESS_RW_24_4    0xf000000    //0x00
    #define    PPR_ROW_ADDRESS_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_113_DATA    0x1c4
    #define    PPR_CID_ADDRESS_RW_8_2    0x300    //0x00
    #define    PPR_CS_ADDRESS_RW_0_1    0x1    //0x00
#define    DENALI_CTL_114_DATA    0x1c8
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_115_DATA    0x1cc
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_116_DATA    0x1d0
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_117_DATA    0x1d4
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_118_DATA    0x1d8
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_119_DATA    0x1dc
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_120_DATA    0x1e0
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_121_DATA    0x1e4
    #define    PPR_DATA_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_122_DATA    0x1e8
    #define    PPR_ECC_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_123_DATA    0x1ec
    #define    CKSRX_F0_RW_24_8    0xff000000    //0x10
    #define    CKSRE_F0_RW_16_8    0xff0000    //0x16
    #define    LOWPOWER_REFRESH_ENABLE_RW_8_2    0x300    //0x00
    #define    PPR_STATUS_RD_0_2    0x3    //0x00
#define    DENALI_CTL_124_DATA    0x1f0
    #define    LPI_CTRL_IDLE_WAKEUP_F0_RW_24_4    0xf000000    //0x00
    #define    LP_CMD_WR_16_7    0x7f0000    //0x00
    #define    CKSRX_F1_RW_8_8    0xff00    //0x10
    #define    CKSRE_F1_RW_0_8    0xff    //0x16
#define    DENALI_CTL_125_DATA    0x1f4
    #define    LPI_PD_WAKEUP_F0_RW_24_4    0xf000000    //0x01
    #define    LPI_SR_LONG_MCCLK_GATE_WAKEUP_F0_RW_16_4    0xf0000    //0x0a
    #define    LPI_SR_LONG_WAKEUP_F0_RW_8_4    0xf00    //0x09
    #define    LPI_SR_SHORT_WAKEUP_F0_RW_0_4    0xf    //0x07
#define    DENALI_CTL_126_DATA    0x1f8
    #define    LPI_SR_LONG_WAKEUP_F1_RW_24_4    0xf000000    //0x09
    #define    LPI_SR_SHORT_WAKEUP_F1_RW_16_4    0xf0000    //0x07
    #define    LPI_CTRL_IDLE_WAKEUP_F1_RW_8_4    0xf00    //0x00
    #define    LPI_TIMER_WAKEUP_F0_RW_0_4    0xf    //0x0e
#define    DENALI_CTL_127_DATA    0x1fc
    #define    LPI_WAKEUP_EN_RW_24_6    0x3f000000    //0x2f
    #define    LPI_TIMER_WAKEUP_F1_RW_16_4    0xf0000    //0x0e
    #define    LPI_PD_WAKEUP_F1_RW_8_4    0xf00    //0x01
    #define    LPI_SR_LONG_MCCLK_GATE_WAKEUP_F1_RW_0_4    0xf    //0x0a
#define    DENALI_CTL_128_DATA    0x200
    #define    LPI_TIMER_COUNT_RW_8_12    0xfff00    //0x0003
    #define    LPI_CTRL_REQ_EN_RW_0_1    0x1    //0x01
#define    DENALI_CTL_129_DATA    0x204
    #define    LP_STATE_RD_24_7    0x7f000000    //0x00
    #define    TDFI_LP_RESP_RW_16_3    0x70000    //0x07
    #define    LPI_WAKEUP_TIMEOUT_RW_0_12    0xfff    //0x0004
#define    DENALI_CTL_130_DATA    0x208
    #define    LP_AUTO_MEM_GATE_EN_RW_16_3    0x70000    //0x00
    #define    LP_AUTO_EXIT_EN_RW_8_4    0xf00    //0x00
    #define    LP_AUTO_ENTRY_EN_RW_0_4    0xf    //0x00
#define    DENALI_CTL_131_DATA    0x20c
    #define    LP_AUTO_SR_SHORT_IDLE_RW_16_12    0xfff0000    //0x0000
    #define    LP_AUTO_PD_IDLE_RW_0_12    0xfff    //0x0000
#define    DENALI_CTL_132_DATA    0x210
    #define    HW_PROMOTE_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0000
    #define    LP_AUTO_SR_LONG_MC_GATE_IDLE_RW_8_8    0xff00    //0x00
    #define    LP_AUTO_SR_LONG_IDLE_RW_0_8    0xff    //0x00
#define    DENALI_CTL_133_DATA    0x214
    #define    LPC_PROMOTE_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0000
    #define    HW_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_134_DATA    0x218
    #define    LPC_SR_PHYUPD_EN_RW_24_1    0x1000000    //0x00
    #define    LPC_SR_CTRLUPD_EN_RW_16_1    0x10000    //0x00
    #define    LPC_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_135_DATA    0x21c
    #define    DFS_ENABLE_RW_24_1    0x1000000    //0x01
    #define    RESERVED_RW_16_8    0xff0000    //0x00
    #define    LPC_SR_ZQ_EN_RW_8_1    0x100    //0x01
    #define    LPC_SR_PHYMSTR_EN_RW_0_1    0x1    //0x00
#define    DENALI_CTL_136_DATA    0x220
    #define    TDFI_INIT_START_F0_RW_D_8_10    0x3ff00    //0x00c0
    #define    DFS_DLL_OFF_RW_0_2    0x3    //0x00
#define    DENALI_CTL_137_DATA    0x224
    #define    TDFI_INIT_START_F1_RW_D_16_10    0x3ff0000    //0x00c0
    #define    TDFI_INIT_COMPLETE_F0_RW_D_0_16    0xffff    //0x8000
#define    DENALI_CTL_138_DATA    0x228
    #define    DFS_PHY_REG_WRITE_EN_RW_24_1    0x1000000    //0x00
    #define    CURRENT_REG_COPY_RD_16_1    0x10000    //0x00
    #define    TDFI_INIT_COMPLETE_F1_RW_D_0_16    0xffff    //0x8000
#define    DENALI_CTL_139_DATA    0x22c
    #define    DFS_PHY_REG_WRITE_ADDR_RW_0_32    0xffffffff    //0x00001900
#define    DENALI_CTL_140_DATA    0x230
    #define    DFS_PHY_REG_WRITE_DATA_F0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_141_DATA    0x234
    #define    DFS_PHY_REG_WRITE_DATA_F1_RW_0_32    0xffffffff    //0x00000001
#define    DENALI_CTL_142_DATA    0x238
    #define    DFS_PHY_REG_WRITE_WAIT_RW_8_16    0xffff00    //0x0010
    #define    DFS_PHY_REG_WRITE_MASK_RW_0_4    0xf    //0x0e
#define    DENALI_CTL_143_DATA    0x23c
    #define    WRITE_MODEREG_RW_0_27    0x7ffffff    //0x00000000
#define    DENALI_CTL_144_DATA    0x240
    #define    MRW_PROMOTE_THRESHOLD_F0_RW_8_16    0xffff00    //0x0000
    #define    MRW_STATUS_RD_0_8    0xff    //0x00
#define    DENALI_CTL_145_DATA    0x244
    #define    RESERVED_RW_16_1    0x10000    //0x00
    #define    MRW_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_146_DATA    0x248
    #define    MR0_DATA_F0_0_RW_0_18    0x3ffff    //0x002054
#define    DENALI_CTL_147_DATA    0x24c
    #define    MR1_DATA_F0_0_RW_0_18    0x3ffff    //0x000201
#define    DENALI_CTL_148_DATA    0x250
    #define    MR2_DATA_F0_0_RW_0_18    0x3ffff    //0x000028
#define    DENALI_CTL_149_DATA    0x254
    #define    MR0_DATA_F1_0_RW_0_18    0x3ffff    //0x002054
#define    DENALI_CTL_150_DATA    0x258
    #define    MR1_DATA_F1_0_RW_0_18    0x3ffff    //0x000201
#define    DENALI_CTL_151_DATA    0x25c
    #define    MR2_DATA_F1_0_RW_0_18    0x3ffff    //0x000028
#define    DENALI_CTL_152_DATA    0x260
    #define    MRSINGLE_DATA_0_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_153_DATA    0x264
    #define    MR3_DATA_F0_0_RW_0_18    0x3ffff    //0x000400
#define    DENALI_CTL_154_DATA    0x268
    #define    MR3_DATA_F1_0_RW_0_18    0x3ffff    //0x000400
#define    DENALI_CTL_155_DATA    0x26c
    #define    MR4_DATA_F0_0_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_156_DATA    0x270
    #define    MR4_DATA_F1_0_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_157_DATA    0x274
    #define    MR5_DATA_F0_0_RW_0_18    0x3ffff    //0x000483
#define    DENALI_CTL_158_DATA    0x278
    #define    MR5_DATA_F1_0_RW_0_18    0x3ffff    //0x000483
#define    DENALI_CTL_159_DATA    0x27c
    #define    MR6_DATA_F0_0_RW_0_18    0x3ffff    //0x001000
#define    DENALI_CTL_160_DATA    0x280
    #define    MR6_DATA_F1_0_RW_0_18    0x3ffff    //0x001000
#define    DENALI_CTL_161_DATA    0x284
    #define    MR0_DATA_F0_1_RW_0_18    0x3ffff    //0x002054
#define    DENALI_CTL_162_DATA    0x288
    #define    MR1_DATA_F0_1_RW_0_18    0x3ffff    //0x000201
#define    DENALI_CTL_163_DATA    0x28c
    #define    MR2_DATA_F0_1_RW_0_18    0x3ffff    //0x000028
#define    DENALI_CTL_164_DATA    0x290
    #define    MR0_DATA_F1_1_RW_0_18    0x3ffff    //0x002054
#define    DENALI_CTL_165_DATA    0x294
    #define    MR1_DATA_F1_1_RW_0_18    0x3ffff    //0x000201
#define    DENALI_CTL_166_DATA    0x298
    #define    MR2_DATA_F1_1_RW_0_18    0x3ffff    //0x000028
#define    DENALI_CTL_167_DATA    0x29c
    #define    MRSINGLE_DATA_1_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_168_DATA    0x2a0
    #define    MR3_DATA_F0_1_RW_0_18    0x3ffff    //0x000400
#define    DENALI_CTL_169_DATA    0x2a4
    #define    MR3_DATA_F1_1_RW_0_18    0x3ffff    //0x000400
#define    DENALI_CTL_170_DATA    0x2a8
    #define    MR4_DATA_F0_1_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_171_DATA    0x2ac
    #define    MR4_DATA_F1_1_RW_0_18    0x3ffff    //0x000000
#define    DENALI_CTL_172_DATA    0x2b0
    #define    MR5_DATA_F0_1_RW_0_18    0x3ffff    //0x000483
#define    DENALI_CTL_173_DATA    0x2b4
    #define    MR5_DATA_F1_1_RW_0_18    0x3ffff    //0x000483
#define    DENALI_CTL_174_DATA    0x2b8
    #define    MR6_DATA_F0_1_RW_0_18    0x3ffff    //0x001000
#define    DENALI_CTL_175_DATA    0x2bc
    #define    BIST_GO_WR_24_1    0x1000000    //0x00
    #define    MR6_DATA_F1_1_RW_0_18    0x3ffff    //0x001000
#define    DENALI_CTL_176_DATA    0x2c0
    #define    BIST_ADDR_CHECK_RW_24_1    0x1000000    //0x01
    #define    BIST_DATA_CHECK_RW_16_1    0x10000    //0x01
    #define    ADDR_SPACE_RW_8_6    0x3f00    //0x00
    #define    BIST_RESULT_RD_0_2    0x3    //0x00
#define    DENALI_CTL_177_DATA    0x2c4
    #define    BIST_ECC_LANE_CHECK_RW_0_1    0x1    //0x01
#define    DENALI_CTL_178_DATA    0x2c8
    #define    BIST_START_ADDRESS_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_179_DATA    0x2cc
    #define    BIST_START_ADDRESS_RW_0_8    0xff    //0x00
#define    DENALI_CTL_180_DATA    0x2d0
    #define    BIST_DATA_MASK_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_181_DATA    0x2d4
    #define    BIST_DATA_MASK_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_182_DATA    0x2d8
    #define    BIST_DATA_MASK_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_183_DATA    0x2dc
    #define    BIST_DATA_MASK_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_184_DATA    0x2e0
    #define    BIST_TEST_MODE_RW_16_3    0x70000    //0x00
    #define    BIST_DATA_MASK_RW_0_32    0xffffffff    //0x0000
#define    DENALI_CTL_185_DATA    0x2e4
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_186_DATA    0x2e8
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_187_DATA    0x2ec
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_188_DATA    0x2f0
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_189_DATA    0x2f4
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_190_DATA    0x2f8
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_191_DATA    0x2fc
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_192_DATA    0x300
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_193_DATA    0x304
    #define    BIST_DATA_PATTERN_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_194_DATA    0x308
    #define    BIST_ERR_STOP_RW_16_12    0xfff0000    //0x0000
    #define    BIST_RET_STATE_RD_8_1    0x100    //0x00
    #define    BIST_RET_STATE_EXIT_WR_0_1    0x1    //0x00
#define    DENALI_CTL_195_DATA    0x30c
    #define    FWC_RW_24_1    0x1000000    //0x00
    #define    ECC_ENABLE_RW_16_2    0x30000    //0x03
    #define    BIST_ERR_COUNT_RD_0_12    0xfff    //0x0000
#define    DENALI_CTL_196_DATA    0x310
    #define    XOR_CHECK_BITS_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_197_DATA    0x314
    #define    ECC_DISABLE_W_UC_ERR_RW_8_1    0x100    //0x00
    #define    ECC_WRITEBACK_EN_RW_0_1    0x1    //0x00
#define    DENALI_CTL_198_DATA    0x318
    #define    ECC_U_ADDR_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_199_DATA    0x31c
    #define    ECC_U_SYND_RD_8_8    0xff00    //0x00
    #define    ECC_U_ADDR_RD_0_32    0xffffffff    //0x00
#define    DENALI_CTL_200_DATA    0x320
    #define    ECC_U_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_201_DATA    0x324
    #define    ECC_U_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_202_DATA    0x328
    #define    ECC_C_ADDR_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_203_DATA    0x32c
    #define    ECC_C_SYND_RD_8_8    0xff00    //0x00
    #define    ECC_C_ADDR_RD_0_32    0xffffffff    //0x00
#define    DENALI_CTL_204_DATA    0x330
    #define    ECC_C_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_205_DATA    0x334
    #define    ECC_C_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_206_DATA    0x338
    #define    ECC_C_ID_RD_16_16    0xffff0000    //0x0000
    #define    ECC_U_ID_RD_0_16    0xffff    //0x0000
#define    DENALI_CTL_207_DATA    0x33c
    #define    NON_ECC_REGION_START_ADDR_0_RW_0_20    0xfffff    //0x000000
#define    DENALI_CTL_208_DATA    0x340
    #define    NON_ECC_REGION_END_ADDR_0_RW_0_20    0xfffff    //0x000000
#define    DENALI_CTL_209_DATA    0x344
    #define    NON_ECC_REGION_START_ADDR_1_RW_0_20    0xfffff    //0x000000
#define    DENALI_CTL_210_DATA    0x348
    #define    NON_ECC_REGION_ENABLE_RW_24_2    0x3000000    //0x00
    #define    NON_ECC_REGION_END_ADDR_1_RW_0_20    0xfffff    //0x000000
#define    DENALI_CTL_211_DATA    0x34c
    #define    ECC_SCRUB_LEN_RW_16_13    0x1fff0000    //0x0020
    #define    ECC_SCRUB_IN_PROGRESS_RD_8_1    0x100    //0x00
    #define    ECC_SCRUB_START_WR_0_1    0x1    //0x00
#define    DENALI_CTL_212_DATA    0x350
    #define    ECC_SCRUB_INTERVAL_RW_8_16    0xffff00    //0x03e8
    #define    ECC_SCRUB_MODE_RW_0_1    0x1    //0x00
#define    DENALI_CTL_213_DATA    0x354
    #define    ECC_SCRUB_IDLE_CNT_RW_0_16    0xffff    //0x0064
#define    DENALI_CTL_214_DATA    0x358
    #define    ECC_SCRUB_START_ADDR_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_215_DATA    0x35c
    #define    ECC_SCRUB_START_ADDR_RW_0_32    0xffffffff    //0x00
#define    DENALI_CTL_216_DATA    0x360
    #define    ECC_SCRUB_END_ADDR_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_217_DATA    0x364
    #define    CRC_MODE_RW_8_2    0x300    //0x00
    #define    ECC_SCRUB_END_ADDR_RW_0_32    0xffffffff    //0x00
#define    DENALI_CTL_218_DATA    0x368
    #define    DQ_MAP_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_219_DATA    0x36c
    #define    DQ_MAP_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_220_DATA    0x370
    #define    DQ_MAP_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_221_DATA    0x374
    #define    DQ_MAP_0_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_222_DATA    0x378
    #define    DQ_MAP_ODD_RANK_SWAP_0_RW_16_2    0x30000    //0x00
    #define    DQ_MAP_0_RW_0_32    0xffffffff    //0x0000
#define    DENALI_CTL_223_DATA    0x37c
    #define    DQ_MAP_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_224_DATA    0x380
    #define    DQ_MAP_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_225_DATA    0x384
    #define    DQ_MAP_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_226_DATA    0x388
    #define    DQ_MAP_1_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_227_DATA    0x38c
    #define    TDFI_PHY_CRC_MAX_LAT_F0_RW_24_6    0x3f000000    //0x2f
    #define    DQ_MAP_ODD_RANK_SWAP_1_RW_16_2    0x30000    //0x00
    #define    DQ_MAP_1_RW_0_32    0xffffffff    //0x0000
#define    DENALI_CTL_228_DATA    0x390
    #define    CRC_RETRY_IN_PROGRESS_RD_24_1    0x1000000    //0x00
    #define    CRC_ALERT_N_MAX_PW_RW_16_4    0xf0000    //0x05
    #define    CRC_RETRY_EN_RW_8_1    0x100    //0x01
    #define    TDFI_PHY_CRC_MAX_LAT_F1_RW_0_6    0x3f    //0x2f
#define    DENALI_CTL_229_DATA    0x394
    #define    AREF_HIGH_THRESHOLD_RW_24_5    0x1f000000    //0x15
    #define    AREF_NORM_THRESHOLD_RW_16_5    0x1f0000    //0x11
    #define    LONG_COUNT_MASK_RW_8_5    0x1f00    //0x00
    #define    CMD_BLK_SPLIT_SIZE_RW_0_1    0x1    //0x00
#define    DENALI_CTL_230_DATA    0x398
    #define    AREF_CMD_MAX_PER_TREFI_RW_16_4    0xf0000    //0x04
    #define    AREF_MAX_CREDIT_RW_8_5    0x1f00    //0x0c
    #define    AREF_MAX_DEFICIT_RW_0_5    0x1f    //0x18
#define    DENALI_CTL_231_DATA    0x39c
    #define    ZQ_CS_HIGH_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0000
    #define    ZQ_CS_NORM_THRESHOLD_F0_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_232_DATA    0x3a0
    #define    ZQ_PROMOTE_THRESHOLD_F0_RW_16_16    0xffff0000    //0x0000
    #define    ZQ_CS_TIMEOUT_F0_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_233_DATA    0x3a4
    #define    ZQ_CS_HIGH_THRESHOLD_F1_RW_16_16    0xffff0000    //0x0000
    #define    ZQ_CS_NORM_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_234_DATA    0x3a8
    #define    ZQ_PROMOTE_THRESHOLD_F1_RW_16_16    0xffff0000    //0x0000
    #define    ZQ_CS_TIMEOUT_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_235_DATA    0x3ac
    #define    ZQINIT_F0_RW_D_16_12    0xfff0000    //0x0400
    #define    TIMEOUT_TIMER_LOG_RD_8_4    0xf00    //0x00
    #define    RESERVED_RW_0_3    0x7    //0x03
#define    DENALI_CTL_236_DATA    0x3b0
    #define    ZQCS_F0_RW_16_12    0xfff0000    //0x0080
    #define    ZQCL_F0_RW_0_12    0xfff    //0x0200
#define    DENALI_CTL_237_DATA    0x3b4
    #define    ZQCL_F1_RW_16_12    0xfff0000    //0x0200
    #define    ZQINIT_F1_RW_D_0_12    0xfff    //0x0400
#define    DENALI_CTL_238_DATA    0x3b8
    #define    ZQ_REQ_PENDING_RD_24_1    0x1000000    //0x00
    #define    ZQ_REQ_WR_16_2    0x30000    //0x00
    #define    ZQCS_F1_RW_0_12    0xfff    //0x0080
#define    DENALI_CTL_239_DATA    0x3bc
    #define    ROW_DIFF_0_RW_24_3    0x7000000    //0x04
    #define    BANK_DIFF_1_RW_16_2    0x30000    //0x00
    #define    BANK_DIFF_0_RW_8_2    0x300    //0x00
    #define    ZQCS_ROTATE_RW_0_1    0x1    //0x01
#define    DENALI_CTL_240_DATA    0x3c0
    #define    CID_DIFF_0_RW_24_2    0x3000000    //0x02
    #define    COL_DIFF_1_RW_16_4    0xf0000    //0x02
    #define    COL_DIFF_0_RW_8_4    0xf00    //0x02
    #define    ROW_DIFF_1_RW_0_3    0x7    //0x04
#define    DENALI_CTL_241_DATA    0x3c4
    #define    CS_VAL_0_RW_8_16    0xffff00    //0x0000
    #define    CID_DIFF_1_RW_0_2    0x3    //0x02
#define    DENALI_CTL_242_DATA    0x3c8
    #define    CS_MSK_0_RW_16_16    0xffff0000    //0x007f
    #define    CS_VAL_1_RW_0_16    0xffff    //0x0080
#define    DENALI_CTL_243_DATA    0x3cc
    #define    RESERVED_RW_24_5    0x1f000000    //0x00
    #define    CS_LOWER_ADDR_EN_RW_16_1    0x10000    //0x00
    #define    CS_MSK_1_RW_0_16    0xffff    //0x007f
#define    DENALI_CTL_244_DATA    0x3d0
    #define    COMMAND_AGE_COUNT_RW_24_8    0xff000000    //0xff
    #define    AGE_COUNT_RW_16_8    0xff0000    //0xff
    #define    APREBIT_RW_D_8_5    0x1f00    //0x0a
    #define    RESERVED_RW_0_1    0x1    //0x00
#define    DENALI_CTL_245_DATA    0x3d4
    #define    PLACEMENT_EN_RW_24_1    0x1000000    //0x01
    #define    BANK_SPLIT_EN_RW_16_1    0x10000    //0x01
    #define    RESERVED_RW_8_1    0x100    //0x01
    #define    ADDR_CMP_EN_RW_0_1    0x1    //0x01
#define    DENALI_CTL_246_DATA    0x3d8
    #define    CS_SAME_EN_RW_24_1    0x1000000    //0x01
    #define    RW_SAME_PAGE_EN_RW_16_1    0x10000    //0x01
    #define    RW_SAME_EN_RW_8_1    0x100    //0x01
    #define    PRIORITY_EN_RW_0_1    0x1    //0x01
#define    DENALI_CTL_247_DATA    0x3dc
    #define    SWAP_EN_RW_24_1    0x1000000    //0x01
    #define    NUM_Q_ENTRIES_ACT_DISABLE_RW_16_5    0x1f0000    //0x10
    #define    DISABLE_RW_GROUP_W_BNK_CONFLICT_RW_8_2    0x300    //0x01
    #define    W2R_SPLIT_EN_RW_0_1    0x1    //0x01
#define    DENALI_CTL_248_DATA    0x3e0
    #define    BURST_ON_FLY_BIT_RW_24_4    0xf000000    //0x0c
    #define    CS_MAP_RW_16_2    0x30000    //0x03
    #define    INHIBIT_DRAM_CMD_RW_8_1    0x100    //0x00
    #define    DISABLE_RD_INTERLEAVE_RW_0_1    0x1    //0x00
#define    DENALI_CTL_249_DATA    0x3e4
    #define    MDQS_MULT_RW_24_2    0x3000000    //0x01
    #define    MEMDATA_RATIO_1_RW_16_3    0x70000    //0x03
    #define    MEMDATA_RATIO_0_RW_8_3    0x700    //0x03
    #define    REDUC_RW_0_1    0x1    //0x00
#define    DENALI_CTL_250_DATA    0x3e8
    #define    CONTROLLER_BUSY_RD_24_1    0x1000000    //0x00
    #define    WR_ORDER_REQ_RW_16_2    0x30000    //0x00
    #define    IN_ORDER_ACCEPT_RW_8_1    0x100    //0x00
    #define    Q_FULLNESS_RW_0_5    0x1f    //0x00
#define    DENALI_CTL_251_DATA    0x3ec
    #define    PREAMBLE_SUPPORT_F0_RW_24_2    0x3000000    //0x00
    #define    CTRLUPD_AREF_HP_ENABLE_RW_16_1    0x10000    //0x01
    #define    CTRLUPD_REQ_PER_AREF_EN_RW_8_1    0x100    //0x01
    #define    CTRLUPD_REQ_WR_0_1    0x1    //0x00
#define    DENALI_CTL_252_DATA    0x3f0
    #define    RD_DBI_EN_RW_24_1    0x1000000    //0x00
    #define    WR_DBI_EN_RW_16_1    0x10000    //0x00
    #define    RD_PREAMBLE_TRAINING_EN_RW_8_1    0x100    //0x01
    #define    PREAMBLE_SUPPORT_F1_RW_0_2    0x3    //0x00
#define    DENALI_CTL_253_DATA    0x3f4
    #define    DFI_ERROR_RD_0_19    0x7ffff    //0x000000
#define    DENALI_CTL_254_DATA    0x3f8
    #define    DFI_ERROR_INFO_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_255_DATA    0x3fc
    #define    DFI_ERROR_INFO_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_256_DATA    0x400
    #define    RESERVED_WR_24_1    0x1000000    //0x00
    #define    BG_ROTATE_EN_RW_16_1    0x10000    //0x01
    #define    DFI_ERROR_INFO_RD_0_32    0xffffffff    //0x0000
#define    DENALI_CTL_257_DATA    0x404
    #define    INT_STATUS_MASTER_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_258_DATA    0x408
    #define    INT_MASK_MASTER_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_259_DATA    0x40c
    #define    INT_STATUS_TIMEOUT_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_260_DATA    0x410
    #define    INT_STATUS_LOWPOWER_RD_16_16    0xffff0000    //0x0000
    #define    INT_STATUS_ECC_RD_0_16    0xffff    //0x0000
#define    DENALI_CTL_261_DATA    0x414
    #define    RESERVED_RD_16_16    0xffff0000    //0x0000
    #define    RESERVED_RD_0_16    0xffff    //0x0000
#define    DENALI_CTL_262_DATA    0x418
    #define    INT_STATUS_USERIF_RD_16_16    0xffff0000    //0x0000
    #define    INT_STATUS_TRAINING_RD_0_16    0xffff    //0x0000
#define    DENALI_CTL_263_DATA    0x41c
    #define    INT_STATUS_DIMM_RD_24_8    0xff000000    //0x00
    #define    INT_STATUS_DFI_RD_16_8    0xff0000    //0x00
    #define    INT_STATUS_CRC_RD_8_8    0xff00    //0x00
    #define    INT_STATUS_BIST_RD_0_8    0xff    //0x00
#define    DENALI_CTL_264_DATA    0x420
    #define    INT_STATUS_MODE_RD_24_8    0xff000000    //0x00
    #define    INT_STATUS_MISC_RD_16_8    0xff0000    //0x00
    #define    INT_STATUS_INIT_RD_8_8    0xff00    //0x00
    #define    INT_STATUS_FREQ_RD_0_8    0xff    //0x00
#define    DENALI_CTL_265_DATA    0x424
    #define    INT_STATUS_PARITY_RD_0_8    0xff    //0x00
#define    DENALI_CTL_266_DATA    0x428
    #define    INT_ACK_TIMEOUT_WR_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_267_DATA    0x42c
    #define    INT_ACK_LOWPOWER_WR_16_16    0xffff0000    //0x0000
    #define    INT_ACK_ECC_WR_0_16    0xffff    //0x0000
#define    DENALI_CTL_268_DATA    0x430
    #define    RESERVED_WR_16_16    0xffff0000    //0x0000
    #define    RESERVED_WR_0_16    0xffff    //0x0000
#define    DENALI_CTL_269_DATA    0x434
    #define    INT_ACK_USERIF_WR_16_16    0xffff0000    //0x0000
    #define    INT_ACK_TRAINING_WR_0_16    0xffff    //0x0000
#define    DENALI_CTL_270_DATA    0x438
    #define    INT_ACK_DIMM_WR_24_8    0xff000000    //0x00
    #define    INT_ACK_DFI_WR_16_8    0xff0000    //0x00
    #define    INT_ACK_CRC_WR_8_8    0xff00    //0x00
    #define    INT_ACK_BIST_WR_0_8    0xff    //0x00
#define    DENALI_CTL_271_DATA    0x43c
    #define    INT_ACK_MODE_WR_24_8    0xff000000    //0x00
    #define    INT_ACK_MISC_WR_16_8    0xff0000    //0x00
    #define    INT_ACK_INIT_WR_8_8    0xff00    //0x00
    #define    INT_ACK_FREQ_WR_0_8    0xff    //0x00
#define    DENALI_CTL_272_DATA    0x440
    #define    INT_ACK_PARITY_WR_0_8    0xff    //0x00
#define    DENALI_CTL_273_DATA    0x444
    #define    INT_MASK_TIMEOUT_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_274_DATA    0x448
    #define    INT_MASK_LOWPOWER_RW_16_16    0xffff0000    //0x0000
    #define    INT_MASK_ECC_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_275_DATA    0x44c
    #define    RESERVED_RW_16_16    0xffff0000    //0x0000
    #define    RESERVED_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_276_DATA    0x450
    #define    INT_MASK_USERIF_RW_16_16    0xffff0000    //0x0000
    #define    INT_MASK_TRAINING_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_277_DATA    0x454
    #define    INT_MASK_DIMM_RW_24_8    0xff000000    //0x00
    #define    INT_MASK_DFI_RW_16_8    0xff0000    //0x00
    #define    INT_MASK_CRC_RW_8_8    0xff00    //0x00
    #define    INT_MASK_BIST_RW_0_8    0xff    //0x00
#define    DENALI_CTL_278_DATA    0x458
    #define    INT_MASK_MODE_RW_24_8    0xff000000    //0x00
    #define    INT_MASK_MISC_RW_16_8    0xff0000    //0x00
    #define    INT_MASK_INIT_RW_8_8    0xff00    //0x00
    #define    INT_MASK_FREQ_RW_0_8    0xff    //0x00
#define    DENALI_CTL_279_DATA    0x45c
    #define    INT_MASK_PARITY_RW_0_8    0xff    //0x00
#define    DENALI_CTL_280_DATA    0x460
    #define    OUT_OF_RANGE_ADDR_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_281_DATA    0x464
    #define    OUT_OF_RANGE_TYPE_RD_24_7    0x7f000000    //0x00
    #define    OUT_OF_RANGE_LENGTH_RD_8_13    0x1fff00    //0x0000
    #define    OUT_OF_RANGE_ADDR_RD_0_32    0xffffffff    //0x00
#define    DENALI_CTL_282_DATA    0x468
    #define    OUT_OF_RANGE_SOURCE_ID_RD_0_16    0xffff    //0x0000
#define    DENALI_CTL_283_DATA    0x46c
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_284_DATA    0x470
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_285_DATA    0x474
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_286_DATA    0x478
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_287_DATA    0x47c
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_288_DATA    0x480
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_289_DATA    0x484
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_290_DATA    0x488
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_291_DATA    0x48c
    #define    BIST_EXP_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_292_DATA    0x490
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_293_DATA    0x494
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_294_DATA    0x498
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_295_DATA    0x49c
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_296_DATA    0x4a0
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_297_DATA    0x4a4
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_298_DATA    0x4a8
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_299_DATA    0x4ac
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_300_DATA    0x4b0
    #define    BIST_FAIL_DATA_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_301_DATA    0x4b4
    #define    BIST_FAIL_ADDR_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_302_DATA    0x4b8
    #define    BIST_FAIL_ADDR_RD_0_32    0xffffffff    //0x00
#define    DENALI_CTL_303_DATA    0x4bc
    #define    PORT_CMD_ERROR_ADDR_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_CTL_304_DATA    0x4c0
    #define    PORT_CMD_ERROR_TYPE_RD_24_3    0x7000000    //0x00
    #define    PORT_CMD_ERROR_ID_RD_8_16    0xffff00    //0x0000
    #define    PORT_CMD_ERROR_ADDR_RD_0_32    0xffffffff    //0x00
#define    DENALI_CTL_305_DATA    0x4c4
    #define    ODT_WR_MAP_CS1_RW_24_2    0x3000000    //0x02
    #define    ODT_RD_MAP_CS1_RW_16_2    0x30000    //0x01
    #define    ODT_WR_MAP_CS0_RW_8_2    0x300    //0x01
    #define    ODT_RD_MAP_CS0_RW_0_2    0x3    //0x02
#define    DENALI_CTL_306_DATA    0x4c8
    #define    TODTL_2CMD_F1_RW_24_8    0xff000000    //0x15
    #define    TODTH_RD_F0_RW_16_4    0xf0000    //0x06
    #define    TODTH_WR_F0_RW_8_4    0xf00    //0x06
    #define    TODTL_2CMD_F0_RW_0_8    0xff    //0x15
#define    DENALI_CTL_307_DATA    0x4cc
    #define    ODT_EN_F1_RW_24_1    0x1000000    //0x01
    #define    ODT_EN_F0_RW_16_1    0x10000    //0x01
    #define    TODTH_RD_F1_RW_8_4    0xf00    //0x06
    #define    TODTH_WR_F1_RW_0_4    0xf    //0x06
#define    DENALI_CTL_308_DATA    0x4d0
    #define    R2R_DIFFCS_DLY_F0_RW_D_24_5    0x1f000000    //0x03
    #define    RD_TO_ODTH_F1_RW_16_5    0x1f0000    //0x08
    #define    RD_TO_ODTH_F0_RW_8_5    0x1f00    //0x08
    #define    RESERVED_RW_0_5    0x1f    //0x00
#define    DENALI_CTL_309_DATA    0x4d4
    #define    R2R_DIFFCS_DLY_F1_RW_D_24_5    0x1f000000    //0x03
    #define    W2W_DIFFCS_DLY_F0_RW_D_16_5    0x1f0000    //0x05
    #define    W2R_DIFFCS_DLY_F0_RW_D_8_5    0x1f00    //0x01
    #define    R2W_DIFFCS_DLY_F0_RW_D_0_5    0x1f    //0x03
#define    DENALI_CTL_310_DATA    0x4d8
    #define    R2R_SAMECS_DLY_RW_24_5    0x1f000000    //0x00
    #define    W2W_DIFFCS_DLY_F1_RW_D_16_5    0x1f0000    //0x05
    #define    W2R_DIFFCS_DLY_F1_RW_D_8_5    0x1f00    //0x01
    #define    R2W_DIFFCS_DLY_F1_RW_D_0_5    0x1f    //0x03
#define    DENALI_CTL_311_DATA    0x4dc
    #define    W2W_SAMECS_DLY_RW_24_5    0x1f000000    //0x00
    #define    W2R_SAMECS_DLY_RW_16_5    0x1f0000    //0x00
    #define    R2W_SAMECS_DLY_F1_RW_D_8_5    0x1f00    //0x02
    #define    R2W_SAMECS_DLY_F0_RW_D_0_5    0x1f    //0x02
#define    DENALI_CTL_312_DATA    0x4e0
    #define    SWLVL_EXIT_WR_24_1    0x1000000    //0x00
    #define    SWLVL_START_WR_16_1    0x10000    //0x00
    #define    SWLVL_LOAD_WR_8_1    0x100    //0x00
    #define    SW_LEVELING_MODE_RW_0_3    0x7    //0x00
#define    DENALI_CTL_313_DATA    0x4e4
    #define    VREF_PDA_EN_RW_24_1    0x1000000    //0x00
    #define    VREF_EN_RW_16_1    0x10000    //0x00
    #define    VREF_CS_RW_8_1    0x100    //0x01
    #define    SWLVL_OP_DONE_RD_0_1    0x1    //0x00
#define    DENALI_CTL_314_DATA    0x4e8
    #define    VREF_VAL_DEV1_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV0_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV0_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_DFS_EN_RW_0_1    0x1    //0x00
#define    DENALI_CTL_315_DATA    0x4ec
    #define    VREF_VAL_DEV3_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV2_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV2_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV1_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_316_DATA    0x4f0
    #define    VREF_VAL_DEV5_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV4_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV4_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV3_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_317_DATA    0x4f4
    #define    VREF_VAL_DEV7_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV6_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV6_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV5_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_318_DATA    0x4f8
    #define    VREF_VAL_DEV9_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV8_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV8_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV7_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_319_DATA    0x4fc
    #define    VREF_VAL_DEV11_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV10_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV10_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV9_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_320_DATA    0x500
    #define    VREF_VAL_DEV13_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV12_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV12_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV11_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_321_DATA    0x504
    #define    VREF_VAL_DEV15_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV14_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV14_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV13_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_322_DATA    0x508
    #define    VREF_VAL_ECC_DEV1_0_F0_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_ECC_DEV0_1_F0_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_ECC_DEV0_0_F0_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV15_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_323_DATA    0x50c
    #define    VREF_VAL_DEV1_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV0_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV0_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_ECC_DEV1_1_F0_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_324_DATA    0x510
    #define    VREF_VAL_DEV3_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV2_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV2_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV1_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_325_DATA    0x514
    #define    VREF_VAL_DEV5_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV4_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV4_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV3_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_326_DATA    0x518
    #define    VREF_VAL_DEV7_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV6_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV6_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV5_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_327_DATA    0x51c
    #define    VREF_VAL_DEV9_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV8_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV8_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV7_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_328_DATA    0x520
    #define    VREF_VAL_DEV11_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV10_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV10_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV9_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_329_DATA    0x524
    #define    VREF_VAL_DEV13_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV12_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV12_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV11_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_330_DATA    0x528
    #define    VREF_VAL_DEV15_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_DEV14_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_DEV14_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV13_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_331_DATA    0x52c
    #define    VREF_VAL_ECC_DEV1_0_F1_RW_24_7    0x7f000000    //0x67
    #define    VREF_VAL_ECC_DEV0_1_F1_RW_16_7    0x7f0000    //0x67
    #define    VREF_VAL_ECC_DEV0_0_F1_RW_8_7    0x7f00    //0x67
    #define    VREF_VAL_DEV15_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_332_DATA    0x530
    #define    VREF_SW_PROMOTE_THRESHOLD_F0_RW_8_16    0xffff00    //0x0000
    #define    VREF_VAL_ECC_DEV1_1_F1_RW_0_7    0x7f    //0x67
#define    DENALI_CTL_333_DATA    0x534
    #define    AXI0_FIXED_PORT_PRIORITY_ENABLE_RW_24_1    0x1000000    //0x00
    #define    AXI0_ALL_STROBES_USED_ENABLE_RW_16_1    0x10000    //0x00
    #define    VREF_SW_PROMOTE_THRESHOLD_F1_RW_0_16    0xffff    //0x0000
#define    DENALI_CTL_334_DATA    0x538
    #define    PORT_ADDR_PROTECTION_EN_RW_24_1    0x1000000    //0x01
    #define    AXI0_FIFO_TYPE_REG_RW_16_2    0x30000    //0x00
    #define    AXI0_W_PRIORITY_RW_8_4    0xf00    //0x08
    #define    AXI0_R_PRIORITY_RW_0_4    0xf    //0x08
#define    DENALI_CTL_335_DATA    0x53c
    #define    AXI0_ADDRESS_RANGE_ENABLE_RW_0_1    0x1    //0x00
#define    DENALI_CTL_336_DATA    0x540
    #define    AXI0_START_ADDR_0_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_337_DATA    0x544
    #define    AXI0_END_ADDR_0_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_338_DATA    0x548
    #define    AXI0_START_ADDR_1_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_339_DATA    0x54c
    #define    AXI0_END_ADDR_1_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_340_DATA    0x550
    #define    AXI0_START_ADDR_2_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_341_DATA    0x554
    #define    AXI0_END_ADDR_2_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_342_DATA    0x558
    #define    AXI0_START_ADDR_3_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_343_DATA    0x55c
    #define    AXI0_END_ADDR_3_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_344_DATA    0x560
    #define    AXI0_START_ADDR_4_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_345_DATA    0x564
    #define    AXI0_END_ADDR_4_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_346_DATA    0x568
    #define    AXI0_START_ADDR_5_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_347_DATA    0x56c
    #define    AXI0_END_ADDR_5_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_348_DATA    0x570
    #define    AXI0_START_ADDR_6_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_349_DATA    0x574
    #define    AXI0_END_ADDR_6_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_350_DATA    0x578
    #define    AXI0_START_ADDR_7_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_351_DATA    0x57c
    #define    AXI0_END_ADDR_7_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_352_DATA    0x580
    #define    AXI0_START_ADDR_8_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_353_DATA    0x584
    #define    AXI0_END_ADDR_8_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_354_DATA    0x588
    #define    AXI0_START_ADDR_9_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_355_DATA    0x58c
    #define    AXI0_END_ADDR_9_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_356_DATA    0x590
    #define    AXI0_START_ADDR_10_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_357_DATA    0x594
    #define    AXI0_END_ADDR_10_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_358_DATA    0x598
    #define    AXI0_START_ADDR_11_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_359_DATA    0x59c
    #define    AXI0_END_ADDR_11_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_360_DATA    0x5a0
    #define    AXI0_START_ADDR_12_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_361_DATA    0x5a4
    #define    AXI0_END_ADDR_12_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_362_DATA    0x5a8
    #define    AXI0_START_ADDR_13_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_363_DATA    0x5ac
    #define    AXI0_END_ADDR_13_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_364_DATA    0x5b0
    #define    AXI0_START_ADDR_14_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_365_DATA    0x5b4
    #define    AXI0_END_ADDR_14_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_366_DATA    0x5b8
    #define    AXI0_START_ADDR_15_RW_0_26    0x3ffffff    //0x00000000
#define    DENALI_CTL_367_DATA    0x5bc
    #define    AXI0_END_ADDR_15_RW_0_26    0x3ffffff    //0x03ffffff
#define    DENALI_CTL_368_DATA    0x5c0
    #define    AXI0_RANGE_RID_CHECK_BITS_0_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_0_RW_0_2    0x3    //0x03
#define    DENALI_CTL_369_DATA    0x5c4
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_0_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_0_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_370_DATA    0x5c8
    #define    AXI0_RANGE_PROT_BITS_1_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_0_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_371_DATA    0x5cc
    #define    AXI0_RANGE_WID_CHECK_BITS_1_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_1_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_372_DATA    0x5d0
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_1_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_1_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_373_DATA    0x5d4
    #define    AXI0_RANGE_RID_CHECK_BITS_2_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_2_RW_0_2    0x3    //0x03
#define    DENALI_CTL_374_DATA    0x5d8
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_2_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_2_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_375_DATA    0x5dc
    #define    AXI0_RANGE_PROT_BITS_3_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_2_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_376_DATA    0x5e0
    #define    AXI0_RANGE_WID_CHECK_BITS_3_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_3_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_377_DATA    0x5e4
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_3_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_3_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_378_DATA    0x5e8
    #define    AXI0_RANGE_RID_CHECK_BITS_4_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_4_RW_0_2    0x3    //0x03
#define    DENALI_CTL_379_DATA    0x5ec
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_4_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_4_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_380_DATA    0x5f0
    #define    AXI0_RANGE_PROT_BITS_5_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_4_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_381_DATA    0x5f4
    #define    AXI0_RANGE_WID_CHECK_BITS_5_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_5_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_382_DATA    0x5f8
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_5_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_5_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_383_DATA    0x5fc
    #define    AXI0_RANGE_RID_CHECK_BITS_6_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_6_RW_0_2    0x3    //0x03
#define    DENALI_CTL_384_DATA    0x600
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_6_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_6_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_385_DATA    0x604
    #define    AXI0_RANGE_PROT_BITS_7_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_6_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_386_DATA    0x608
    #define    AXI0_RANGE_WID_CHECK_BITS_7_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_7_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_387_DATA    0x60c
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_7_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_7_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_388_DATA    0x610
    #define    AXI0_RANGE_RID_CHECK_BITS_8_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_8_RW_0_2    0x3    //0x03
#define    DENALI_CTL_389_DATA    0x614
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_8_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_8_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_390_DATA    0x618
    #define    AXI0_RANGE_PROT_BITS_9_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_8_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_391_DATA    0x61c
    #define    AXI0_RANGE_WID_CHECK_BITS_9_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_9_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_392_DATA    0x620
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_9_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_9_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_393_DATA    0x624
    #define    AXI0_RANGE_RID_CHECK_BITS_10_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_10_RW_0_2    0x3    //0x03
#define    DENALI_CTL_394_DATA    0x628
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_10_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_10_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_395_DATA    0x62c
    #define    AXI0_RANGE_PROT_BITS_11_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_10_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_396_DATA    0x630
    #define    AXI0_RANGE_WID_CHECK_BITS_11_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_11_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_397_DATA    0x634
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_11_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_11_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_398_DATA    0x638
    #define    AXI0_RANGE_RID_CHECK_BITS_12_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_12_RW_0_2    0x3    //0x03
#define    DENALI_CTL_399_DATA    0x63c
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_12_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_12_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_400_DATA    0x640
    #define    AXI0_RANGE_PROT_BITS_13_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_12_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_401_DATA    0x644
    #define    AXI0_RANGE_WID_CHECK_BITS_13_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_13_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_402_DATA    0x648
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_13_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_13_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_403_DATA    0x64c
    #define    AXI0_RANGE_RID_CHECK_BITS_14_RW_8_16    0xffff00    //0xffff
    #define    AXI0_RANGE_PROT_BITS_14_RW_0_2    0x3    //0x03
#define    DENALI_CTL_404_DATA    0x650
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_14_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_WID_CHECK_BITS_14_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_405_DATA    0x654
    #define    AXI0_RANGE_PROT_BITS_15_RW_16_2    0x30000    //0x03
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_14_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_406_DATA    0x658
    #define    AXI0_RANGE_WID_CHECK_BITS_15_RW_16_16    0xffff0000    //0xffff
    #define    AXI0_RANGE_RID_CHECK_BITS_15_RW_0_16    0xffff    //0xffff
#define    DENALI_CTL_407_DATA    0x65c
    #define    AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_15_RW_16_16    0xffff0000    //0x000f
    #define    AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_15_RW_0_16    0xffff    //0x000f
#define    DENALI_CTL_408_DATA    0x660
    #define    DLL_RST_DELAY_RW_16_16    0xffff0000    //0x0000
    #define    MEM_RST_VALID_RD_8_1    0x100    //0x00
    #define    CKE_STATUS_RD_0_2    0x3    //0x00
#define    DENALI_CTL_409_DATA    0x664
    #define    TDFI_PHY_RDLAT_F0_RW_D_24_7    0x7f000000    //0x26
    #define    UPDATE_ERROR_STATUS_RD_16_7    0x7f0000    //0x00
    #define    TDFI_PHY_WRLAT_RD_8_7    0x7f00    //0x00
    #define    DLL_RST_ADJ_DLY_RW_0_8    0xff    //0x00
#define    DENALI_CTL_410_DATA    0x668
    #define    DRAM_CLK_DISABLE_RW_16_2    0x30000    //0x00
    #define    TDFI_RDDATA_EN_RD_8_7    0x7f00    //0x00
    #define    TDFI_PHY_RDLAT_F1_RW_D_0_7    0x7f    //0x26
#define    DENALI_CTL_411_DATA    0x66c
    #define    TDFI_CTRLUPD_MIN_RW_0_16    0xffff    //0x000a
#define    DENALI_CTL_412_DATA    0x670
    #define    TDFI_CTRLUPD_MAX_F0_RW_0_21    0x1fffff    //0x006180
#define    DENALI_CTL_413_DATA    0x674
    #define    TDFI_PHYUPD_TYPE0_F0_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_414_DATA    0x678
    #define    TDFI_PHYUPD_TYPE1_F0_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_415_DATA    0x67c
    #define    TDFI_PHYUPD_TYPE2_F0_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_416_DATA    0x680
    #define    TDFI_PHYUPD_TYPE3_F0_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_417_DATA    0x684
    #define    TDFI_PHYUPD_RESP_F0_RW_0_23    0x7fffff    //0x012480
#define    DENALI_CTL_418_DATA    0x688
    #define    TDFI_CTRLUPD_INTERVAL_F0_RW_0_32    0xffffffff    //0x0003cf00
#define    DENALI_CTL_419_DATA    0x68c
    #define    WRLAT_ADJ_F0_RW_8_7    0x7f00    //0x13
    #define    RDLAT_ADJ_F0_RW_0_7    0x7f    //0x13
#define    DENALI_CTL_420_DATA    0x690
    #define    TDFI_CTRLUPD_MAX_F1_RW_0_21    0x1fffff    //0x006180
#define    DENALI_CTL_421_DATA    0x694
    #define    TDFI_PHYUPD_TYPE0_F1_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_422_DATA    0x698
    #define    TDFI_PHYUPD_TYPE1_F1_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_423_DATA    0x69c
    #define    TDFI_PHYUPD_TYPE2_F1_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_424_DATA    0x6a0
    #define    TDFI_PHYUPD_TYPE3_F1_RW_0_32    0xffffffff    //0x00000200
#define    DENALI_CTL_425_DATA    0x6a4
    #define    TDFI_PHYUPD_RESP_F1_RW_0_23    0x7fffff    //0x012480
#define    DENALI_CTL_426_DATA    0x6a8
    #define    TDFI_CTRLUPD_INTERVAL_F1_RW_0_32    0xffffffff    //0x0003cf00
#define    DENALI_CTL_427_DATA    0x6ac
    #define    TDFI_CTRL_DELAY_F1_RW_D_24_4    0xf000000    //0x02
    #define    TDFI_CTRL_DELAY_F0_RW_D_16_4    0xf0000    //0x02
    #define    WRLAT_ADJ_F1_RW_8_7    0x7f00    //0x13
    #define    RDLAT_ADJ_F1_RW_0_7    0x7f    //0x13
#define    DENALI_CTL_428_DATA    0x6b0
    #define    TDFI_PHY_WRDATA_F1_RW_24_3    0x7000000    //0x03
    #define    TDFI_PHY_WRDATA_F0_RW_16_3    0x70000    //0x03
    #define    TDFI_DRAM_CLK_ENABLE_RW_8_4    0xf00    //0x03
    #define    TDFI_DRAM_CLK_DISABLE_RW_0_4    0xf    //0x02
#define    DENALI_CTL_429_DATA    0x6b4
    #define    TDFI_WRCSLAT_F1_RW_24_7    0x7f000000    //0x0f
    #define    TDFI_RDCSLAT_F1_RW_16_7    0x7f0000    //0x19
    #define    TDFI_WRCSLAT_F0_RW_8_7    0x7f00    //0x0f
    #define    TDFI_RDCSLAT_F0_RW_0_7    0x7f    //0x19
#define    DENALI_CTL_430_DATA    0x6b8
    #define    TDFI_WRDATA_DELAY_RW_8_8    0xff00    //0x05
    #define    TDFI_PARIN_LAT_RW_0_3    0x7    //0x00

