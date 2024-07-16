#define    DENALI_PI_0_DATA    0x0
    #define    PI_DRAM_CLASS_RW_8_4    0xf00    //0x0a
    #define    PI_START_RW_0_1    0x1    //0x00
#define    DENALI_PI_1_DATA    0x4
    #define    PI_VERSION_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_2_DATA    0x8
    #define    PI_VERSION_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_3_DATA    0xc
    #define    PI_ID_RD_0_16    0xffff    //0x0000
#define    DENALI_PI_4_DATA    0x10
#define    DENALI_PI_5_DATA    0x14
    #define    PI_NOTCARE_PHYUPD_RW_16_2    0x30000    //0x00
    #define    PI_INIT_LVL_EN_RW_8_1    0x100    //0x01
    #define    PI_NORMAL_LVL_SEQ_RW_0_1    0x1    //0x01
#define    DENALI_PI_6_DATA    0x18
    #define    PI_DFI_VERSION_RW_24_1    0x1000000    //0x01
    #define    RESERVED_RW_D_16_8    0xff0000    //0x64
    #define    PI_TCMD_GAP_RW_0_16    0xffff    //0x0000
#define    DENALI_PI_7_DATA    0x1c
    #define    PI_DFI_PHYMSTR_STATE_SEL_R_RW_16_1    0x10000    //0x00
    #define    PI_DFI_PHYMSTR_CS_STATE_R_RW_8_1    0x100    //0x00
    #define    PI_DFI_PHYMSTR_TYPE_RW_0_2    0x3    //0x00
#define    DENALI_PI_8_DATA    0x20
    #define    PI_TDFI_PHYMSTR_MAX_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_9_DATA    0x24
    #define    PI_TDFI_PHYMSTR_RESP_RD_0_20    0xfffff    //0x000000
#define    DENALI_PI_10_DATA    0x28
    #define    PI_TDFI_PHYUPD_RESP_RD_0_20    0xfffff    //0x000000
#define    DENALI_PI_11_DATA    0x2c
    #define    PI_TDFI_PHYUPD_MAX_RD_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_12_DATA    0x30
    #define    PI_RANK_NUM_PER_CKE_RW_24_5    0x1f000000    //0x00
    #define    PI_CS_MAP_RW_D_16_2    0x30000    //0x03
    #define    RESERVED_RW_8_1    0x100    //0x00
    #define    PI_SW_RST_N_RW_D_0_1    0x1    //0x01
#define    DENALI_PI_13_DATA    0x34
    #define    PI_DDR4_DIMM_CID1_MAP_RW_24_2    0x3000000    //0x00
    #define    PI_DDR4_DIMM_CID0_MAP_RW_16_2    0x30000    //0x00
    #define    PI_DDR4_DIMM_3DS_PIN_MUXING_EN_RW_8_1    0x100    //0x00
    #define    PI_SRX_LVL_TARGET_CS_EN_RW_0_1    0x1    //0x00
#define    DENALI_PI_14_DATA    0x38
    #define    PI_MCAREF_FORWARD_ONLY_RW_24_1    0x1000000    //0x01
    #define    PI_PREAMBLE_SUPPORT_RW_16_2    0x30000    //0x00
    #define    PI_TMPRR_RW_8_4    0xf00    //0x01
    #define    PI_LOGICAL_CS_MAP_RW_0_2    0x3    //0x00
#define    DENALI_PI_15_DATA    0x3c
    #define    PI_TREF_INTERVAL_RW_8_20    0xfffff00    //0x000005
    #define    RESERVED_RW_0_1    0x1    //0x00
#define    DENALI_PI_16_DATA    0x40
    #define    PI_SWLVL_OP_DONE_RD_24_1    0x1000000    //0x00
    #define    PI_SWLVL_LOAD_WR_16_1    0x10000    //0x00
    #define    PI_ON_DFIBUS_RD_8_1    0x100    //0x00
    #define    PI_3DS_AREF_MODE_RW_0_1    0x1    //0x01
#define    DENALI_PI_17_DATA    0x44
    #define    PI_SW_WRLVL_RESP_3_RD_24_1    0x1000000    //0x00
    #define    PI_SW_WRLVL_RESP_2_RD_16_1    0x10000    //0x00
    #define    PI_SW_WRLVL_RESP_1_RD_8_1    0x100    //0x00
    #define    PI_SW_WRLVL_RESP_0_RD_0_1    0x1    //0x00
#define    DENALI_PI_18_DATA    0x48
    #define    PI_SW_WRLVL_RESP_7_RD_24_1    0x1000000    //0x00
    #define    PI_SW_WRLVL_RESP_6_RD_16_1    0x10000    //0x00
    #define    PI_SW_WRLVL_RESP_5_RD_8_1    0x100    //0x00
    #define    PI_SW_WRLVL_RESP_4_RD_0_1    0x1    //0x00
#define    DENALI_PI_19_DATA    0x4c
    #define    PI_SW_WRLVL_RESP_11_RD_24_1    0x1000000    //0x00
    #define    PI_SW_WRLVL_RESP_10_RD_16_1    0x10000    //0x00
    #define    PI_SW_WRLVL_RESP_9_RD_8_1    0x100    //0x00
    #define    PI_SW_WRLVL_RESP_8_RD_0_1    0x1    //0x00
#define    DENALI_PI_20_DATA    0x50
    #define    PI_SW_WRLVL_RESP_15_RD_24_1    0x1000000    //0x00
    #define    PI_SW_WRLVL_RESP_14_RD_16_1    0x10000    //0x00
    #define    PI_SW_WRLVL_RESP_13_RD_8_1    0x100    //0x00
    #define    PI_SW_WRLVL_RESP_12_RD_0_1    0x1    //0x00
#define    DENALI_PI_21_DATA    0x54
    #define    PI_SW_RDLVL_RESP_1_RD_24_2    0x3000000    //0x00
    #define    PI_SW_RDLVL_RESP_0_RD_16_2    0x30000    //0x00
    #define    PI_SW_WRLVL_RESP_17_RD_8_1    0x100    //0x00
    #define    PI_SW_WRLVL_RESP_16_RD_0_1    0x1    //0x00
#define    DENALI_PI_22_DATA    0x58
    #define    PI_SW_RDLVL_RESP_5_RD_24_2    0x3000000    //0x00
    #define    PI_SW_RDLVL_RESP_4_RD_16_2    0x30000    //0x00
    #define    PI_SW_RDLVL_RESP_3_RD_8_2    0x300    //0x00
    #define    PI_SW_RDLVL_RESP_2_RD_0_2    0x3    //0x00
#define    DENALI_PI_23_DATA    0x5c
    #define    PI_SW_RDLVL_RESP_9_RD_24_2    0x3000000    //0x00
    #define    PI_SW_RDLVL_RESP_8_RD_16_2    0x30000    //0x00
    #define    PI_SW_RDLVL_RESP_7_RD_8_2    0x300    //0x00
    #define    PI_SW_RDLVL_RESP_6_RD_0_2    0x3    //0x00
#define    DENALI_PI_24_DATA    0x60
    #define    PI_SW_RDLVL_RESP_13_RD_24_2    0x3000000    //0x00
    #define    PI_SW_RDLVL_RESP_12_RD_16_2    0x30000    //0x00
    #define    PI_SW_RDLVL_RESP_11_RD_8_2    0x300    //0x00
    #define    PI_SW_RDLVL_RESP_10_RD_0_2    0x3    //0x00
#define    DENALI_PI_25_DATA    0x64
    #define    PI_SW_RDLVL_RESP_17_RD_24_2    0x3000000    //0x00
    #define    PI_SW_RDLVL_RESP_16_RD_16_2    0x30000    //0x00
    #define    PI_SW_RDLVL_RESP_15_RD_8_2    0x300    //0x00
    #define    PI_SW_RDLVL_RESP_14_RD_0_2    0x3    //0x00
#define    DENALI_PI_26_DATA    0x68
    #define    PI_SWLVL_WR_SLICE_0_WR_24_1    0x1000000    //0x00
    #define    PI_SWLVL_EXIT_WR_16_1    0x10000    //0x00
    #define    PI_SWLVL_START_WR_8_1    0x100    //0x00
    #define    PI_SW_LEVELING_MODE_RW_0_3    0x7    //0x00
#define    DENALI_PI_27_DATA    0x6c
    #define    PI_SWLVL_WR_SLICE_1_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_0_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_0_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_0_WR_0_1    0x1    //0x00
#define    DENALI_PI_28_DATA    0x70
    #define    PI_SWLVL_WR_SLICE_2_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_1_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_1_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_1_WR_0_1    0x1    //0x00
#define    DENALI_PI_29_DATA    0x74
    #define    PI_SWLVL_WR_SLICE_3_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_2_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_2_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_2_WR_0_1    0x1    //0x00
#define    DENALI_PI_30_DATA    0x78
    #define    PI_SWLVL_WR_SLICE_4_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_3_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_3_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_3_WR_0_1    0x1    //0x00
#define    DENALI_PI_31_DATA    0x7c
    #define    PI_SWLVL_WR_SLICE_5_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_4_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_4_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_4_WR_0_1    0x1    //0x00
#define    DENALI_PI_32_DATA    0x80
    #define    PI_SWLVL_WR_SLICE_6_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_5_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_5_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_5_WR_0_1    0x1    //0x00
#define    DENALI_PI_33_DATA    0x84
    #define    PI_SWLVL_WR_SLICE_7_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_6_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_6_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_6_WR_0_1    0x1    //0x00
#define    DENALI_PI_34_DATA    0x88
    #define    PI_SWLVL_WR_SLICE_8_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_7_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_7_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_7_WR_0_1    0x1    //0x00
#define    DENALI_PI_35_DATA    0x8c
    #define    PI_SWLVL_WR_SLICE_9_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_8_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_8_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_8_WR_0_1    0x1    //0x00
#define    DENALI_PI_36_DATA    0x90
    #define    PI_SWLVL_WR_SLICE_10_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_9_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_9_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_9_WR_0_1    0x1    //0x00
#define    DENALI_PI_37_DATA    0x94
    #define    PI_SWLVL_WR_SLICE_11_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_10_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_10_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_10_WR_0_1    0x1    //0x00
#define    DENALI_PI_38_DATA    0x98
    #define    PI_SWLVL_WR_SLICE_12_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_11_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_11_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_11_WR_0_1    0x1    //0x00
#define    DENALI_PI_39_DATA    0x9c
    #define    PI_SWLVL_WR_SLICE_13_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_12_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_12_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_12_WR_0_1    0x1    //0x00
#define    DENALI_PI_40_DATA    0xa0
    #define    PI_SWLVL_WR_SLICE_14_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_13_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_13_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_13_WR_0_1    0x1    //0x00
#define    DENALI_PI_41_DATA    0xa4
    #define    PI_SWLVL_WR_SLICE_15_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_14_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_14_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_14_WR_0_1    0x1    //0x00
#define    DENALI_PI_42_DATA    0xa8
    #define    PI_SWLVL_WR_SLICE_16_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_15_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_15_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_15_WR_0_1    0x1    //0x00
#define    DENALI_PI_43_DATA    0xac
    #define    PI_SWLVL_WR_SLICE_17_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_16_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_16_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_16_WR_0_1    0x1    //0x00
#define    DENALI_PI_44_DATA    0xb0
    #define    PI_SWLVL_SM2_START_WR_24_1    0x1000000    //0x00
    #define    PI_SW_WDQLVL_RESP_17_RD_16_2    0x30000    //0x00
    #define    PI_SWLVL_VREF_UPDATE_SLICE_17_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_RD_SLICE_17_WR_0_1    0x1    //0x00
#define    DENALI_PI_45_DATA    0xb4
    #define    PI_DFI40_POLARITY_RW_24_1    0x1000000    //0x00
    #define    PI_SEQUENTIAL_LVL_REQ_WR_16_1    0x10000    //0x00
    #define    PI_SWLVL_SM2_RD_WR_8_1    0x100    //0x00
    #define    PI_SWLVL_SM2_WR_WR_0_1    0x1    //0x00
#define    DENALI_PI_46_DATA    0xb8
    #define    PI_WLMRD_RW_24_6    0x3f000000    //0x28
    #define    PI_WLDQSEN_RW_16_6    0x3f0000    //0x0d
    #define    PI_WRLVL_CS_RW_8_1    0x100    //0x00
    #define    PI_WRLVL_REQ_WR_0_1    0x1    //0x00
#define    DENALI_PI_47_DATA    0xbc
    #define    PI_WRLVL_DISABLE_DFS_RW_24_1    0x1000000    //0x00
    #define    PI_WRLVL_ON_SREF_EXIT_RW_16_1    0x10000    //0x00
    #define    PI_WRLVL_INTERVAL_RW_0_16    0xffff    //0x0000
#define    DENALI_PI_48_DATA    0xc0
    #define    PI_WRLVL_ROTATE_RW_24_1    0x1000000    //0x00
    #define    PI_WRLVL_RESP_MASK_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_49_DATA    0xc4
    #define    PI_TDFI_WRLVL_EN_RW_24_8    0xff000000    //0x32
    #define    PI_WRLVL_ERROR_STATUS_RD_16_1    0x10000    //0x00
    #define    PI_WRLVL_ON_MPD_EXIT_RW_8_1    0x100    //0x00
    #define    PI_WRLVL_CS_MAP_RW_0_2    0x3    //0x03
#define    DENALI_PI_50_DATA    0xc8
    #define    PI_TDFI_WRLVL_RESP_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_51_DATA    0xcc
    #define    PI_TDFI_WRLVL_MAX_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_52_DATA    0xd0
    #define    PI_ADDRESS_MIRRORING_RW_24_2    0x3000000    //0x00
    #define    PI_TODTH_RD_RW_16_4    0xf0000    //0x06
    #define    PI_TODTH_WR_RW_8_4    0xf00    //0x06
    #define    PI_WRLVL_STROBE_NUM_RW_0_5    0x1f    //0x02
#define    DENALI_PI_53_DATA    0xd4
    #define    RESERVED_RW_0_2    0x3    //0x00
#define    DENALI_PI_54_DATA    0xd8
    #define    PI_CA_PARITY_ERROR_INJECT_RW_0_27    0x7ffffff    //0x00000000
#define    DENALI_PI_55_DATA    0xdc
    #define    PI_RDLVL_GATE_REQ_WR_24_1    0x1000000    //0x00
    #define    PI_RDLVL_REQ_WR_16_1    0x10000    //0x00
    #define    RESERVED_RW_8_4    0xf00    //0x00
    #define    RESERVED_RW_0_3    0x7    //0x00
#define    DENALI_PI_56_DATA    0xe0
    #define    PI_RDLVL_PAT_2_RW_24_8    0xff000000    //0xad
    #define    PI_RDLVL_PAT_1_RW_16_8    0xff0000    //0xaa
    #define    PI_RDLVL_PAT_0_RW_8_8    0xff00    //0x55
    #define    PI_RDLVL_CS_RW_0_1    0x1    //0x00
#define    DENALI_PI_57_DATA    0xe4
    #define    PI_RDLVL_PAT_6_RW_24_8    0xff000000    //0x95
    #define    PI_RDLVL_PAT_5_RW_16_8    0xff0000    //0x95
    #define    PI_RDLVL_PAT_4_RW_8_8    0xff00    //0x6a
    #define    PI_RDLVL_PAT_3_RW_0_8    0xff    //0x52
#define    DENALI_PI_58_DATA    0xe8
    #define    PI_RDLVL_DISABLE_DFS_RW_24_1    0x1000000    //0x00
    #define    PI_RDLVL_ON_SREF_EXIT_RW_16_1    0x10000    //0x00
    #define    PI_RDLVL_SEQ_EN_RW_8_4    0xf00    //0x00
    #define    PI_RDLVL_PAT_7_RW_0_8    0xff    //0xad
#define    DENALI_PI_59_DATA    0xec
    #define    PI_RDLVL_GATE_ON_MPD_EXIT_RW_24_1    0x1000000    //0x00
    #define    PI_RDLVL_ON_MPD_EXIT_RW_16_1    0x10000    //0x00
    #define    PI_RDLVL_GATE_DISABLE_DFS_RW_8_1    0x100    //0x00
    #define    PI_RDLVL_GATE_ON_SREF_EXIT_RW_0_1    0x1    //0x00
#define    DENALI_PI_60_DATA    0xf0
    #define    PI_RDLVL_GATE_CS_MAP_RW_24_2    0x3000000    //0x03
    #define    PI_RDLVL_CS_MAP_RW_16_2    0x30000    //0x03
    #define    PI_RDLVL_GATE_ROTATE_RW_8_1    0x100    //0x00
    #define    PI_RDLVL_ROTATE_RW_0_1    0x1    //0x00
#define    DENALI_PI_61_DATA    0xf4
    #define    PI_TDFI_RDLVL_RR_RW_0_10    0x3ff    //0x0014
#define    DENALI_PI_62_DATA    0xf8
    #define    PI_TDFI_RDLVL_RESP_RW_0_32    0xffffffff    //0x000007d0
#define    DENALI_PI_63_DATA    0xfc
    #define    PI_TDFI_RDLVL_EN_RW_24_8    0xff000000    //0x03
    #define    PI_RDLVL_RESP_MASK_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_64_DATA    0x100
    #define    PI_TDFI_RDLVL_MAX_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_65_DATA    0x104
    #define    PI_RDLVL_INTERVAL_RW_8_16    0xffff00    //0x0000
    #define    PI_RDLVL_ERROR_STATUS_RD_0_1    0x1    //0x00
#define    DENALI_PI_66_DATA    0x108
    #define    PI_RDLVL_PATTERN_NUM_RW_24_4    0xf000000    //0x01
    #define    PI_RDLVL_PATTERN_START_RW_16_4    0xf0000    //0x00
    #define    PI_RDLVL_GATE_INTERVAL_RW_0_16    0xffff    //0x0000
#define    DENALI_PI_67_DATA    0x10c
    #define    PI_REG_DIMM_ENABLE_RW_24_1    0x1000000    //0x00
    #define    PI_RD_PREAMBLE_TRAINING_EN_RW_16_1    0x10000    //0x01
    #define    PI_RDLVL_GATE_STROBE_NUM_RW_8_5    0x1f00    //0x01
    #define    PI_RDLVL_STROBE_NUM_RW_0_5    0x1f    //0x01
#define    DENALI_PI_68_DATA    0x110
    #define    PI_VREF_PDA_EN_RW_24_1    0x1000000    //0x00
    #define    PI_VREF_CS_RW_16_1    0x10000    //0x01
    #define    PI_TDFI_PHY_WRLAT_RD_8_7    0x7f00    //0x00
    #define    PI_TDFI_RDDATA_EN_RD_0_7    0x7f    //0x00
#define    DENALI_PI_69_DATA    0x114
    #define    PI_ECC_EN_RW_24_1    0x1000000    //0x01
    #define    PI_INIT_COMPLETE_TO_MC_DELAY_COUNT_RW_16_8    0xff0000    //0x0e
    #define    PI_MC_DFS_PI_SET_VREF_ENABLE_RW_8_1    0x100    //0x00
    #define    PI_VREFLVL_DISABLE_DFS_RW_0_1    0x1    //0x00
#define    DENALI_PI_70_DATA    0x118
    #define    PI_WDQLVL_BST_NUM_RW_8_3    0x700    //0x01
    #define    PI_WDQLVL_VREF_EN_RW_0_1    0x1    //0x01
#define    DENALI_PI_71_DATA    0x11c
    #define    PI_WDQLVL_ROTATE_RW_24_1    0x1000000    //0x00
    #define    PI_WDQLVL_RESP_MASK_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_72_DATA    0x120
    #define    PI_WDQLVL_REQ_WR_24_1    0x1000000    //0x00
    #define    PI_WDQLVL_VREF_NORMAL_STEPSIZE_RW_16_5    0x1f0000    //0x02
    #define    PI_WDQLVL_VREF_INITIAL_STEPSIZE_RW_8_5    0x1f00    //0x04
    #define    PI_WDQLVL_CS_MAP_RW_0_2    0x3    //0x03
#define    DENALI_PI_73_DATA    0x124
    #define    PI_TDFI_WDQLVL_EN_RW_8_8    0xff00    //0x34
    #define    PI_WDQLVL_CS_RW_0_1    0x1    //0x00
#define    DENALI_PI_74_DATA    0x128
    #define    PI_TDFI_WDQLVL_RESP_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_75_DATA    0x12c
    #define    PI_TDFI_WDQLVL_MAX_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_76_DATA    0x130
    #define    PI_WDQLVL_ON_MPD_EXIT_RW_24_1    0x1000000    //0x00
    #define    PI_WDQLVL_ON_SREF_EXIT_RW_16_1    0x10000    //0x00
    #define    PI_WDQLVL_INTERVAL_RW_0_16    0xffff    //0x0000
#define    DENALI_PI_77_DATA    0x134
    #define    PI_WDQLVL_NEED_SAVE_RESTORE_RW_16_2    0x30000    //0x00
    #define    PI_WDQLVL_ERROR_STATUS_RD_8_2    0x300    //0x00
    #define    PI_WDQLVL_DISABLE_DFS_RW_0_1    0x1    //0x00
#define    DENALI_PI_78_DATA    0x138
    #define    PI_WDQLVL_DRAM_LVL_START_ADDR_RW_0_32    0xffffffff    //0x00000000
#define    DENALI_PI_79_DATA    0x13c
    #define    PI_NO_MEMORY_DM_RW_16_1    0x10000    //0x00
    #define    PI_WDQLVL_DM_LEVEL_EN_RW_8_1    0x100    //0x00
    #define    PI_WDQLVL_DRAM_LVL_START_ADDR_RW_0_32    0xffffffff    //0x00
#define    DENALI_PI_80_DATA    0x140
    #define    PI_WDQLVL_NIBBLE_MODE_RW_24_1    0x1000000    //0x00
    #define    PI_SWLVL_SM2_DM_NIBBLE_START_WR_16_1    0x10000    //0x00
    #define    PI_TDFI_WDQLVL_WW_RW_0_10    0x3ff    //0x0008
#define    DENALI_PI_81_DATA    0x144
    #define    PI_WDQLVL_PDA_VREF_TRAIN_RW_8_1    0x100    //0x01
    #define    PI_WDQLVL_PDA_EN_RW_0_1    0x1    //0x00
#define    DENALI_PI_82_DATA    0x148
    #define    PI_BANK_DIFF_RW_24_2    0x3000000    //0x00
    #define    PI_DBILVL_RESP_MASK_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_83_DATA    0x14c
    #define    PI_TCCD_RW_8_5    0x1f00    //0x04
    #define    PI_ROW_DIFF_RW_0_3    0x7    //0x04
#define    DENALI_PI_84_DATA    0x150
    #define    PI_INT_STATUS_RD_0_19    0x7ffff    //0x000000
#define    DENALI_PI_85_DATA    0x154
    #define    PI_INT_ACK_WR_0_18    0x3ffff    //0x000000
#define    DENALI_PI_86_DATA    0x158
    #define    PI_BSTLEN_RW_D_24_3    0x7000000    //0x03
    #define    PI_INT_MASK_RW_0_19    0x7ffff    //0x000000
#define    DENALI_PI_87_DATA    0x15c
    #define    PI_A15_MUX_RW_D_24_5    0x1f000000    //0x0b
    #define    PI_PARITY_IN_MUX_RW_D_16_5    0x1f0000    //0x0c
    #define    PI_CMD_SWAP_EN_RW_D_8_1    0x100    //0x00
    #define    PI_LONG_COUNT_MASK_RW_0_5    0x1f    //0x00
#define    DENALI_PI_88_DATA    0x160
    #define    PI_WE_N_MUX_RW_D_24_5    0x1f000000    //0x07
    #define    PI_CAS_N_MUX_RW_D_16_5    0x1f0000    //0x08
    #define    PI_RAS_N_MUX_RW_D_8_5    0x1f00    //0x09
    #define    PI_A14_MUX_RW_D_0_5    0x1f    //0x0a
#define    DENALI_PI_89_DATA    0x164
    #define    PI_DATA_BYTE_SWAP_EN_RW_D_24_1    0x1000000    //0x00
    #define    PI_BANK_MUX_2_RW_D_16_5    0x1f0000    //0x06
    #define    PI_BANK_MUX_1_RW_D_8_5    0x1f00    //0x05
    #define    PI_BANK_MUX_0_RW_D_0_5    0x1f    //0x04
#define    DENALI_PI_90_DATA    0x168
    #define    PI_DATA_BYTE_SWAP_SLICE3_RW_D_24_5    0x1f000000    //0x03
    #define    PI_DATA_BYTE_SWAP_SLICE2_RW_D_16_5    0x1f0000    //0x02
    #define    PI_DATA_BYTE_SWAP_SLICE1_RW_D_8_5    0x1f00    //0x01
    #define    PI_DATA_BYTE_SWAP_SLICE0_RW_D_0_5    0x1f    //0x00
#define    DENALI_PI_91_DATA    0x16c
    #define    PI_DATA_BYTE_SWAP_SLICE7_RW_D_24_5    0x1f000000    //0x07
    #define    PI_DATA_BYTE_SWAP_SLICE6_RW_D_16_5    0x1f0000    //0x06
    #define    PI_DATA_BYTE_SWAP_SLICE5_RW_D_8_5    0x1f00    //0x05
    #define    PI_DATA_BYTE_SWAP_SLICE4_RW_D_0_5    0x1f    //0x04
#define    DENALI_PI_92_DATA    0x170
    #define    PI_DATA_BYTE_SWAP_SLICE11_RW_D_24_5    0x1f000000    //0x0b
    #define    PI_DATA_BYTE_SWAP_SLICE10_RW_D_16_5    0x1f0000    //0x0a
    #define    PI_DATA_BYTE_SWAP_SLICE9_RW_D_8_5    0x1f00    //0x09
    #define    PI_DATA_BYTE_SWAP_SLICE8_RW_D_0_5    0x1f    //0x08
#define    DENALI_PI_93_DATA    0x174
    #define    PI_DATA_BYTE_SWAP_SLICE15_RW_D_24_5    0x1f000000    //0x0f
    #define    PI_DATA_BYTE_SWAP_SLICE14_RW_D_16_5    0x1f0000    //0x0e
    #define    PI_DATA_BYTE_SWAP_SLICE13_RW_D_8_5    0x1f00    //0x0d
    #define    PI_DATA_BYTE_SWAP_SLICE12_RW_D_0_5    0x1f    //0x0c
#define    DENALI_PI_94_DATA    0x178
    #define    PI_CTRLUPD_REQ_PER_AREF_EN_RW_16_1    0x10000    //0x01
    #define    PI_DATA_BYTE_SWAP_SLICE17_RW_D_8_5    0x1f00    //0x11
    #define    PI_DATA_BYTE_SWAP_SLICE16_RW_D_0_5    0x1f    //0x10
#define    DENALI_PI_95_DATA    0x17c
    #define    PI_TDFI_PARIN_LAT_RW_24_3    0x7000000    //0x00
    #define    PI_UPDATE_ERROR_STATUS_RD_16_2    0x30000    //0x00
    #define    PI_TDFI_CTRLUPD_MIN_RW_0_16    0xffff    //0x0008
#define    DENALI_PI_96_DATA    0x180
    #define    PI_MONITOR_SRC_SEL_0_RW_24_5    0x1f000000    //0x00
    #define    PI_MC_PWRUP_SREFRESH_EXIT_RW_16_1    0x10000    //0x00
    #define    PI_BG_ROTATE_EN_RW_8_1    0x100    //0x01
    #define    PI_COL_DIFF_RW_0_4    0xf    //0x02
#define    DENALI_PI_97_DATA    0x184
    #define    PI_MONITOR_CAP_SEL_1_RW_24_1    0x1000000    //0x01
    #define    PI_MONITOR_SRC_SEL_1_RW_16_5    0x1f0000    //0x01
    #define    PI_MONITOR_0_RD_8_8    0xff00    //0x00
    #define    PI_MONITOR_CAP_SEL_0_RW_0_1    0x1    //0x01
#define    DENALI_PI_98_DATA    0x188
    #define    PI_MONITOR_2_RD_24_8    0xff000000    //0x00
    #define    PI_MONITOR_CAP_SEL_2_RW_16_1    0x10000    //0x01
    #define    PI_MONITOR_SRC_SEL_2_RW_8_5    0x1f00    //0x02
    #define    PI_MONITOR_1_RD_0_8    0xff    //0x00
#define    DENALI_PI_99_DATA    0x18c
    #define    PI_MONITOR_SRC_SEL_4_RW_24_5    0x1f000000    //0x04
    #define    PI_MONITOR_3_RD_16_8    0xff0000    //0x00
    #define    PI_MONITOR_CAP_SEL_3_RW_8_1    0x100    //0x01
    #define    PI_MONITOR_SRC_SEL_3_RW_0_5    0x1f    //0x03
#define    DENALI_PI_100_DATA    0x190
    #define    PI_MONITOR_CAP_SEL_5_RW_24_1    0x1000000    //0x01
    #define    PI_MONITOR_SRC_SEL_5_RW_16_5    0x1f0000    //0x05
    #define    PI_MONITOR_4_RD_8_8    0xff00    //0x00
    #define    PI_MONITOR_CAP_SEL_4_RW_0_1    0x1    //0x01
#define    DENALI_PI_101_DATA    0x194
    #define    PI_MONITOR_6_RD_24_8    0xff000000    //0x00
    #define    PI_MONITOR_CAP_SEL_6_RW_16_1    0x10000    //0x01
    #define    PI_MONITOR_SRC_SEL_6_RW_8_5    0x1f00    //0x06
    #define    PI_MONITOR_5_RD_0_8    0xff    //0x00
#define    DENALI_PI_102_DATA    0x198
    #define    PI_MONITOR_7_RD_16_8    0xff0000    //0x00
    #define    PI_MONITOR_CAP_SEL_7_RW_8_1    0x100    //0x01
    #define    PI_MONITOR_SRC_SEL_7_RW_0_5    0x1f    //0x07
#define    DENALI_PI_103_DATA    0x19c
    #define    PI_MONITOR_STROBE_WR_0_8    0xff    //0x00
#define    DENALI_PI_104_DATA    0x1a0
    #define    PI_PHYMSTR_TYPE_RW_24_2    0x3000000    //0x00
    #define    RESERVED_RW_16_1    0x10000    //0x00
    #define    PI_FREQ_NUMBER_STATUS_RD_8_5    0x1f00    //0x00
    #define    PI_DLL_LOCK_RD_0_1    0x1    //0x00
#define    DENALI_PI_105_DATA    0x1a4
    #define    RESERVED_RW_24_1    0x1000000    //0x00
    #define    RESERVED_RW_16_1    0x10000    //0x00
    #define    PI_POWER_REDUC_EN_RW_8_1    0x100    //0x01
    #define    RESERVED_RW_0_1    0x1    //0x00
#define    DENALI_PI_106_DATA    0x1a8
    #define    RESERVED_RW_24_1    0x1000000    //0x00
    #define    RESERVED_RW_16_1    0x10000    //0x00
    #define    RESERVED_RW_8_1    0x100    //0x00
    #define    RESERVED_RW_0_1    0x1    //0x00
#define    DENALI_PI_107_DATA    0x1ac
    #define    RESERVED_RW_24_1    0x1000000    //0x00
    #define    RESERVED_RW_16_1    0x10000    //0x00
    #define    RESERVED_RW_8_1    0x100    //0x00
    #define    RESERVED_RW_0_1    0x1    //0x00
#define    DENALI_PI_108_DATA    0x1b0
    #define    PI_WRLVL_MAX_STROBE_PEND_RW_16_8    0xff0000    //0x01
    #define    RESERVED_RW_8_1    0x100    //0x00
    #define    RESERVED_RW_0_1    0x1    //0x00
#define    DENALI_PI_109_DATA    0x1b4
    #define    PI_TREFBW_THR_RW_0_9    0x1ff    //0x0004
#define    DENALI_PI_110_DATA    0x1b8
    #define    PI_FREQ_CHANGE_REG_COPY_RW_0_5    0x1f    //0x00
#define    DENALI_PI_111_DATA    0x1bc
    #define    PI_DISABLE_PHYMSTR_REQ_RW_24_1    0x1000000    //0x00
    #define    PI_DISCONNECT_MC_RW_16_1    0x10000    //0x00
    #define    PI_MASK_INIT_COMPLETE_RW_8_1    0x100    //0x00
    #define    PI_FREQ_SEL_FROM_REGIF_RW_0_1    0x1    //0x00
#define    DENALI_PI_112_DATA    0x1c0
    #define    PI_TVREF_F1_RW_16_16    0xffff0000    //0x00f0
    #define    PI_TVREF_F0_RW_0_16    0xffff    //0x00f0
#define    DENALI_PI_113_DATA    0x1c4
    #define    PI_TSDO_F1_RW_8_8    0xff00    //0x27
    #define    PI_TSDO_F0_RW_0_8    0xff    //0x27
#define    DENALI_PI_114_DATA    0x1c8
    #define    PI_TDELAY_RDWR_2_BUS_IDLE_F0_RW_0_8    0xff    //0x48
#define    DENALI_PI_115_DATA    0x1cc
    #define    PI_CA_PARITY_LAT_F0_RW_24_4    0xf000000    //0x06
    #define    PI_ADDITIVE_LAT_F0_RW_16_5    0x1f0000    //0x00
    #define    PI_WRLAT_F0_RW_8_5    0x1f00    //0x10
    #define    PI_TDELAY_RDWR_2_BUS_IDLE_F1_RW_0_8    0xff    //0x48
#define    DENALI_PI_116_DATA    0x1d0
    #define    PI_ADDITIVE_LAT_F1_RW_24_5    0x1f000000    //0x00
    #define    PI_WRLAT_F1_RW_16_5    0x1f0000    //0x10
    #define    PI_CASLAT_LIN_F0_RW_8_6    0x3f00    //0x30
    #define    PI_TPARITY_ERROR_CMD_INHIBIT_F0_RW_0_8    0xff    //0xcd
#define    DENALI_PI_117_DATA    0x1d4
    #define    PI_CASLAT_LIN_F1_RW_16_6    0x3f0000    //0x30
    #define    PI_TPARITY_ERROR_CMD_INHIBIT_F1_RW_8_8    0xff00    //0xcd
    #define    PI_CA_PARITY_LAT_F1_RW_0_4    0xf    //0x06
#define    DENALI_PI_118_DATA    0x1d8
    #define    PI_TRFC_F0_RW_0_10    0x3ff    //0x0100
#define    DENALI_PI_119_DATA    0x1dc
    #define    PI_TREF_F0_RW_0_20    0xfffff    //0x0030c0
#define    DENALI_PI_120_DATA    0x1e0
    #define    PI_TRFC_F1_RW_0_10    0x3ff    //0x0100
#define    DENALI_PI_121_DATA    0x1e4
    #define    PI_TREF_F1_RW_0_20    0xfffff    //0x0030c0
#define    DENALI_PI_122_DATA    0x1e8
    #define    PI_TRFC_DLR_F1_RW_16_10    0x3ff0000    //0x0080
    #define    PI_TRFC_DLR_F0_RW_0_10    0x3ff    //0x0080
#define    DENALI_PI_123_DATA    0x1ec
    #define    PI_WRLVL_EN_F1_RW_24_2    0x3000000    //0x01
    #define    PI_WRLVL_EN_F0_RW_16_2    0x30000    //0x01
    #define    PI_TDFI_CTRL_DELAY_F1_RW_D_8_4    0xf00    //0x04
    #define    PI_TDFI_CTRL_DELAY_F0_RW_D_0_4    0xf    //0x04
#define    DENALI_PI_124_DATA    0x1f0
    #define    PI_TDFI_WRLVL_WW_F1_RW_16_10    0x3ff0000    //0x001c
    #define    PI_TDFI_WRLVL_WW_F0_RW_0_10    0x3ff    //0x001c
#define    DENALI_PI_125_DATA    0x1f4
    #define    PI_ODT_EN_F1_RW_24_1    0x1000000    //0x01
    #define    PI_TODTL_2CMD_F1_RW_16_8    0xff0000    //0x15
    #define    PI_ODT_EN_F0_RW_8_1    0x100    //0x01
    #define    PI_TODTL_2CMD_F0_RW_0_8    0xff    //0x15
#define    DENALI_PI_126_DATA    0x1f8
    #define    PI_RDLVL_EN_F0_RW_24_2    0x3000000    //0x01
    #define    PI_RD_TO_ODTH_F1_RW_16_5    0x1f0000    //0x08
    #define    PI_RD_TO_ODTH_F0_RW_8_5    0x1f00    //0x08
    #define    RESERVED_RW_0_5    0x1f    //0x00
#define    DENALI_PI_127_DATA    0x1fc
    #define    PI_TWR_MPR_F0_RW_24_8    0xff000000    //0x18
    #define    PI_RDLVL_GATE_EN_F1_RW_16_2    0x30000    //0x01
    #define    PI_RDLVL_EN_F1_RW_8_2    0x300    //0x01
    #define    PI_RDLVL_GATE_EN_F0_RW_0_2    0x3    //0x01
#define    DENALI_PI_128_DATA    0x200
    #define    PI_RDLVL_DFE_EN_F0_RW_24_2    0x3000000    //0x00
    #define    PI_RDLVL_RXCAL_EN_F0_RW_16_2    0x30000    //0x00
    #define    PI_RDLVL_PAT0_EN_F0_RW_8_2    0x300    //0x00
    #define    PI_TWR_MPR_F1_RW_0_8    0xff    //0x18
#define    DENALI_PI_129_DATA    0x204
    #define    PI_RDLVL_DFE_EN_F1_RW_24_2    0x3000000    //0x00
    #define    PI_RDLVL_RXCAL_EN_F1_RW_16_2    0x30000    //0x00
    #define    PI_RDLVL_PAT0_EN_F1_RW_8_2    0x300    //0x00
    #define    PI_RDLVL_MULTI_EN_F0_RW_0_2    0x3    //0x00
#define    DENALI_PI_130_DATA    0x208
    #define    PI_WRLAT_ADJ_F0_RW_24_7    0x7f000000    //0x13
    #define    PI_RDLAT_ADJ_F1_RW_16_7    0x7f0000    //0x13
    #define    PI_RDLAT_ADJ_F0_RW_8_7    0x7f00    //0x13
    #define    PI_RDLVL_MULTI_EN_F1_RW_0_2    0x3    //0x00
#define    DENALI_PI_131_DATA    0x20c
    #define    PI_VREF_EN_F0_RW_24_2    0x3000000    //0x01
    #define    PI_TDFI_PHY_WRDATA_F1_RW_16_3    0x70000    //0x03
    #define    PI_TDFI_PHY_WRDATA_F0_RW_8_3    0x700    //0x03
    #define    PI_WRLAT_ADJ_F1_RW_0_7    0x7f    //0x13
#define    DENALI_PI_132_DATA    0x210
    #define    PI_TDFI_WDQLVL_WR_F0_RW_8_10    0x3ff00    //0x002a
    #define    PI_VREF_EN_F1_RW_0_2    0x3    //0x01
#define    DENALI_PI_133_DATA    0x214
    #define    PI_WDQLVL_VREF_INITIAL_STOP_POINT_F0_RW_24_7    0x7f000000    //0x1e
    #define    PI_WDQLVL_VREF_INITIAL_START_POINT_F0_RW_16_7    0x7f0000    //0x1a
    #define    PI_TDFI_WDQLVL_RW_F0_RW_0_10    0x3ff    //0x0050
#define    DENALI_PI_134_DATA    0x218
    #define    PI_WDQLVL_RDLAT_ADJ_F0_RW_24_7    0x7f000000    //0x13
    #define    PI_WDQLVL_CL_F0_RW_16_5    0x1f0000    //0x0b
    #define    PI_WDQLVL_EN_F0_RW_8_2    0x300    //0x00
    #define    PI_WDQLVL_VREF_DELTA_F0_RW_0_4    0xf    //0x01
#define    DENALI_PI_135_DATA    0x21c
    #define    PI_TDFI_WDQLVL_WR_F1_RW_8_10    0x3ff00    //0x002a
    #define    PI_WDQLVL_WRLAT_ADJ_F0_RW_0_7    0x7f    //0x13
#define    DENALI_PI_136_DATA    0x220
    #define    PI_WDQLVL_VREF_INITIAL_STOP_POINT_F1_RW_24_7    0x7f000000    //0x1e
    #define    PI_WDQLVL_VREF_INITIAL_START_POINT_F1_RW_16_7    0x7f0000    //0x1a
    #define    PI_TDFI_WDQLVL_RW_F1_RW_0_10    0x3ff    //0x0050
#define    DENALI_PI_137_DATA    0x224
    #define    PI_WDQLVL_RDLAT_ADJ_F1_RW_24_7    0x7f000000    //0x13
    #define    PI_WDQLVL_CL_F1_RW_16_5    0x1f0000    //0x0b
    #define    PI_WDQLVL_EN_F1_RW_8_2    0x300    //0x00
    #define    PI_WDQLVL_VREF_DELTA_F1_RW_0_4    0xf    //0x01
#define    DENALI_PI_138_DATA    0x228
    #define    PI_TRTP_F0_RW_24_8    0xff000000    //0x0d
    #define    PI_RD_DBI_LEVEL_EN_F1_RW_16_2    0x30000    //0x00
    #define    PI_RD_DBI_LEVEL_EN_F0_RW_8_2    0x300    //0x00
    #define    PI_WDQLVL_WRLAT_ADJ_F1_RW_0_7    0x7f    //0x13
#define    DENALI_PI_139_DATA    0x22c
    #define    PI_TWTR_F0_RW_24_6    0x3f000000    //0x0c
    #define    PI_TCCD_L_F0_RW_16_5    0x1f0000    //0x08
    #define    PI_TRCD_F0_RW_8_8    0xff00    //0x19
    #define    PI_TRP_F0_RW_0_8    0xff    //0x18
#define    DENALI_PI_140_DATA    0x230
    #define    PI_TRAS_MAX_F0_RW_8_20    0xfffff00    //0x018ae0
    #define    PI_TWR_F0_RW_0_8    0xff    //0x19
#define    DENALI_PI_141_DATA    0x234
    #define    PI_TMOD_F0_RW_24_8    0xff000000    //0x18
    #define    PI_TMRD_F0_RW_16_8    0xff0000    //0x08
    #define    PI_TRAS_MIN_F0_RW_0_9    0x1ff    //0x0035
#define    DENALI_PI_142_DATA    0x238
    #define    PI_TRP_F1_RW_24_8    0xff000000    //0x18
    #define    PI_TRTP_F1_RW_16_8    0xff0000    //0x0d
    #define    PI_TMRD_PAR_F0_RW_8_8    0xff00    //0x1e
    #define    PI_TMOD_PAR_F0_RW_0_8    0xff    //0x1e
#define    DENALI_PI_143_DATA    0x23c
    #define    PI_TWR_F1_RW_24_8    0xff000000    //0x19
    #define    PI_TWTR_F1_RW_16_6    0x3f0000    //0x0c
    #define    PI_TCCD_L_F1_RW_8_5    0x1f00    //0x08
    #define    PI_TRCD_F1_RW_0_8    0xff    //0x19
#define    DENALI_PI_144_DATA    0x240
    #define    PI_TRAS_MAX_F1_RW_0_20    0xfffff    //0x018ae0
#define    DENALI_PI_145_DATA    0x244
    #define    PI_TMOD_F1_RW_24_8    0xff000000    //0x18
    #define    PI_TMRD_F1_RW_16_8    0xff0000    //0x08
    #define    PI_TRAS_MIN_F1_RW_0_9    0x1ff    //0x0035
#define    DENALI_PI_146_DATA    0x248
    #define    PI_TMRD_PAR_F1_RW_8_8    0xff00    //0x1e
    #define    PI_TMOD_PAR_F1_RW_0_8    0xff    //0x1e
#define    DENALI_PI_147_DATA    0x24c
    #define    PI_TDFI_CTRLUPD_MAX_F0_RW_0_21    0x1fffff    //0x006180
#define    DENALI_PI_148_DATA    0x250
    #define    PI_TDFI_CTRLUPD_INTERVAL_F0_RW_0_32    0xffffffff    //0x0003cf00
#define    DENALI_PI_149_DATA    0x254
    #define    PI_TDFI_CTRLUPD_MAX_F1_RW_0_21    0x1fffff    //0x006180
#define    DENALI_PI_150_DATA    0x258
    #define    PI_TDFI_CTRLUPD_INTERVAL_F1_RW_0_32    0xffffffff    //0x0003cf00
#define    DENALI_PI_151_DATA    0x25c
    #define    PI_ODT_WR_MAP_CS0_RW_24_2    0x3000000    //0x01
    #define    PI_ODT_RD_MAP_CS0_RW_16_2    0x30000    //0x02
    #define    PI_MEMDATA_RATIO_1_RW_8_3    0x700    //0x03
    #define    PI_MEMDATA_RATIO_0_RW_0_3    0x7    //0x03
#define    DENALI_PI_152_DATA    0x260
    #define    PI_PDA_INVERT_DEV_CS0_RW_16_16    0xffff0000    //0x0000
    #define    PI_ODT_WR_MAP_CS1_RW_8_2    0x300    //0x02
    #define    PI_ODT_RD_MAP_CS1_RW_0_2    0x3    //0x01
#define    DENALI_PI_153_DATA    0x264
    #define    PI_PDA_INVERT_ECC_DEV_CS1_RW_24_2    0x3000000    //0x00
    #define    PI_PDA_INVERT_DEV_CS1_RW_8_16    0xffff00    //0x0000
    #define    PI_PDA_INVERT_ECC_DEV_CS0_RW_0_2    0x3    //0x00
#define    DENALI_PI_154_DATA    0x268
    #define    PI_VREF_VAL_DEV1_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV1_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV0_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV0_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_155_DATA    0x26c
    #define    PI_VREF_VAL_DEV3_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV3_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV2_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV2_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_156_DATA    0x270
    #define    PI_VREF_VAL_DEV5_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV5_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV4_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV4_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_157_DATA    0x274
    #define    PI_VREF_VAL_DEV7_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV7_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV6_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV6_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_158_DATA    0x278
    #define    PI_VREF_VAL_DEV9_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV9_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV8_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV8_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_159_DATA    0x27c
    #define    PI_VREF_VAL_DEV11_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV11_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV10_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV10_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_160_DATA    0x280
    #define    PI_VREF_VAL_DEV13_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV13_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV12_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV12_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_161_DATA    0x284
    #define    PI_VREF_VAL_DEV15_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_DEV15_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_DEV14_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_DEV14_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_162_DATA    0x288
    #define    PI_VREF_VAL_ECC_DEV1_1_RW_24_7    0x7f000000    //0x67
    #define    PI_VREF_VAL_ECC_DEV1_0_RW_16_7    0x7f0000    //0x67
    #define    PI_VREF_VAL_ECC_DEV0_1_RW_8_7    0x7f00    //0x67
    #define    PI_VREF_VAL_ECC_DEV0_0_RW_0_7    0x7f    //0x67
#define    DENALI_PI_163_DATA    0x28c
    #define    PI_MR6_VREF_0_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_0_0_RD_16_6    0x3f0000    //0x00
    #define    PI_SLICE_PER_DEV_1_RW_8_2    0x300    //0x01
    #define    PI_SLICE_PER_DEV_0_RW_0_2    0x3    //0x01
#define    DENALI_PI_164_DATA    0x290
    #define    PI_MR6_VREF_2_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_2_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_1_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_1_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_165_DATA    0x294
    #define    PI_MR6_VREF_4_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_4_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_3_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_3_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_166_DATA    0x298
    #define    PI_MR6_VREF_6_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_6_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_5_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_5_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_167_DATA    0x29c
    #define    PI_MR6_VREF_8_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_8_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_7_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_7_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_168_DATA    0x2a0
    #define    PI_MR6_VREF_10_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_10_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_9_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_9_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_169_DATA    0x2a4
    #define    PI_MR6_VREF_12_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_12_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_11_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_11_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_170_DATA    0x2a8
    #define    PI_MR6_VREF_14_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_14_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_13_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_13_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_171_DATA    0x2ac
    #define    PI_MR6_VREF_16_1_RD_24_6    0x3f000000    //0x00
    #define    PI_MR6_VREF_16_0_RD_16_6    0x3f0000    //0x00
    #define    PI_MR6_VREF_15_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_15_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_172_DATA    0x2b0
    #define    PI_CKE_MUX_1_RW_D_24_5    0x1f000000    //0x10
    #define    PI_CKE_MUX_0_RW_D_16_5    0x1f0000    //0x0f
    #define    PI_MR6_VREF_17_1_RD_8_6    0x3f00    //0x00
    #define    PI_MR6_VREF_17_0_RD_0_6    0x3f    //0x00
#define    DENALI_PI_173_DATA    0x2b4
    #define    PI_CID_MUX_1_RW_D_24_5    0x1f000000    //0x12
    #define    PI_CID_MUX_0_RW_D_16_5    0x1f0000    //0x11
    #define    PI_CS_MUX_1_RW_D_8_5    0x1f00    //0x0e
    #define    PI_CS_MUX_0_RW_D_0_5    0x1f    //0x0d
#define    DENALI_PI_174_DATA    0x2b8
    #define    PI_RESET_N_MUX_1_RW_D_24_5    0x1f000000    //0x01
    #define    PI_RESET_N_MUX_0_RW_D_16_5    0x1f0000    //0x00
    #define    PI_ODT_MUX_1_RW_D_8_5    0x1f00    //0x03
    #define    PI_ODT_MUX_0_RW_D_0_5    0x1f    //0x02
#define    DENALI_PI_175_DATA    0x2bc
    #define    PI_RANK0_MAP_DIMM_1_RW_24_2    0x3000000    //0x00
    #define    PI_RANK0_MAP_DIMM_0_RW_16_2    0x30000    //0x01
    #define    PI_CS_MAP_DIMM_1_RW_8_2    0x300    //0x00
    #define    PI_CS_MAP_DIMM_0_RW_0_2    0x3    //0x03
#define    DENALI_PI_176_DATA    0x2c0
    #define    PI_MR0_DATA_F0_0_RW_0_18    0x3ffff    //0x002054
#define    DENALI_PI_177_DATA    0x2c4
    #define    PI_MR1_DATA_F0_0_RW_0_18    0x3ffff    //0x000201
#define    DENALI_PI_178_DATA    0x2c8
    #define    PI_MR2_DATA_F0_0_RW_0_18    0x3ffff    //0x000028
#define    DENALI_PI_179_DATA    0x2cc
    #define    PI_MR3_DATA_F0_0_RW_0_18    0x3ffff    //0x000400
#define    DENALI_PI_180_DATA    0x2d0
    #define    PI_MR4_DATA_F0_0_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_181_DATA    0x2d4
    #define    PI_MR5_DATA_F0_0_RW_0_18    0x3ffff    //0x000483
#define    DENALI_PI_182_DATA    0x2d8
    #define    PI_MR6_DATA_F0_0_RW_0_18    0x3ffff    //0x001000
#define    DENALI_PI_183_DATA    0x2dc
    #define    PI_MR0_DATA_F1_0_RW_0_18    0x3ffff    //0x002054
#define    DENALI_PI_184_DATA    0x2e0
    #define    PI_MR1_DATA_F1_0_RW_0_18    0x3ffff    //0x000201
#define    DENALI_PI_185_DATA    0x2e4
    #define    PI_MR2_DATA_F1_0_RW_0_18    0x3ffff    //0x000028
#define    DENALI_PI_186_DATA    0x2e8
    #define    PI_MR3_DATA_F1_0_RW_0_18    0x3ffff    //0x000400
#define    DENALI_PI_187_DATA    0x2ec
    #define    PI_MR4_DATA_F1_0_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_188_DATA    0x2f0
    #define    PI_MR5_DATA_F1_0_RW_0_18    0x3ffff    //0x000483
#define    DENALI_PI_189_DATA    0x2f4
    #define    PI_MR6_DATA_F1_0_RW_0_18    0x3ffff    //0x001000
#define    DENALI_PI_190_DATA    0x2f8
    #define    PI_MR0_DATA_F0_1_RW_0_18    0x3ffff    //0x002054
#define    DENALI_PI_191_DATA    0x2fc
    #define    PI_MR1_DATA_F0_1_RW_0_18    0x3ffff    //0x000201
#define    DENALI_PI_192_DATA    0x300
    #define    PI_MR2_DATA_F0_1_RW_0_18    0x3ffff    //0x000028
#define    DENALI_PI_193_DATA    0x304
    #define    PI_MR3_DATA_F0_1_RW_0_18    0x3ffff    //0x000400
#define    DENALI_PI_194_DATA    0x308
    #define    PI_MR4_DATA_F0_1_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_195_DATA    0x30c
    #define    PI_MR5_DATA_F0_1_RW_0_18    0x3ffff    //0x000483
#define    DENALI_PI_196_DATA    0x310
    #define    PI_MR6_DATA_F0_1_RW_0_18    0x3ffff    //0x001000
#define    DENALI_PI_197_DATA    0x314
    #define    PI_MR0_DATA_F1_1_RW_0_18    0x3ffff    //0x002054
#define    DENALI_PI_198_DATA    0x318
    #define    PI_MR1_DATA_F1_1_RW_0_18    0x3ffff    //0x000201
#define    DENALI_PI_199_DATA    0x31c
    #define    PI_MR2_DATA_F1_1_RW_0_18    0x3ffff    //0x000028
#define    DENALI_PI_200_DATA    0x320
    #define    PI_MR3_DATA_F1_1_RW_0_18    0x3ffff    //0x000400
#define    DENALI_PI_201_DATA    0x324
    #define    PI_MR4_DATA_F1_1_RW_0_18    0x3ffff    //0x000000
#define    DENALI_PI_202_DATA    0x328
    #define    PI_MR5_DATA_F1_1_RW_0_18    0x3ffff    //0x000483
#define    DENALI_PI_203_DATA    0x32c
    #define    PI_MR6_DATA_F1_1_RW_0_18    0x3ffff    //0x001000

