#ifndef __FWK_MODULE_IDX_H__
#define __FWK_MODULE_IDX_H__

#include <fwk_id.h>

enum fwk_module_idx {
    FWK_MODULE_IDX_ARMV7M_MPU = 0,
    FWK_MODULE_IDX_PL011 = 1,
    FWK_MODULE_IDX_CMN600 = 2,
    FWK_MODULE_IDX_APCONTEXT = 3,
    FWK_MODULE_IDX_POWER_DOMAIN = 4,
    FWK_MODULE_IDX_PPU_V1 = 5,
    FWK_MODULE_IDX_PPU_V0 = 6,
    FWK_MODULE_IDX_SYSTEM_POWER = 7,
    FWK_MODULE_IDX_N1SDP_PLL = 8,
    FWK_MODULE_IDX_N1SDP_I2C = 9,
    FWK_MODULE_IDX_N1SDP_DMC620 = 10,
    FWK_MODULE_IDX_N1SDP_DDR_PHY = 11,
    FWK_MODULE_IDX_MHU = 12,
    FWK_MODULE_IDX_SMT = 13,
    FWK_MODULE_IDX_SCMI = 14,
    FWK_MODULE_IDX_SDS = 15,
    FWK_MODULE_IDX_PIK_CLOCK = 16,
    FWK_MODULE_IDX_CSS_CLOCK = 17,
    FWK_MODULE_IDX_CLOCK = 18,
    FWK_MODULE_IDX_GTIMER = 19,
    FWK_MODULE_IDX_TIMER = 20,
    FWK_MODULE_IDX_N1SDP_SCP2PCC = 21,
    FWK_MODULE_IDX_N1SDP_SENSOR = 22,
    FWK_MODULE_IDX_SENSOR = 23,
    FWK_MODULE_IDX_SCMI_POWER_DOMAIN = 24,
    FWK_MODULE_IDX_SCMI_SENSOR = 25,
    FWK_MODULE_IDX_SCMI_SYSTEM_POWER = 26,
    FWK_MODULE_IDX_SCMI_MANAGEMENT = 27,
    FWK_MODULE_IDX_SCMI_CCIX_CONFIG = 28,
    FWK_MODULE_IDX_FIP = 29,
    FWK_MODULE_IDX_N1SDP_TIMER_SYNC = 30,
    FWK_MODULE_IDX_N1SDP_C2C = 31,
    FWK_MODULE_IDX_N1SDP_REMOTE_PD = 32,
    FWK_MODULE_IDX_N1SDP_PCIE = 33,
    FWK_MODULE_IDX_SSC = 34,
    FWK_MODULE_IDX_SYSTEM_INFO = 35,
    FWK_MODULE_IDX_N1SDP_SYSTEM = 36,
    FWK_MODULE_IDX_CMN600_WRAPPER = 37,
    FWK_MODULE_IDX_COUNT = 38,
};

static const fwk_id_t fwk_module_id_armv7m_mpu = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_ARMV7M_MPU);
static const fwk_id_t fwk_module_id_pl011 = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_PL011);
static const fwk_id_t fwk_module_id_cmn600 = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_CMN600);
static const fwk_id_t fwk_module_id_apcontext = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_APCONTEXT);
static const fwk_id_t fwk_module_id_power_domain = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_POWER_DOMAIN);
static const fwk_id_t fwk_module_id_ppu_v1 = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_PPU_V1);
static const fwk_id_t fwk_module_id_ppu_v0 = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_PPU_V0);
static const fwk_id_t fwk_module_id_system_power = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SYSTEM_POWER);
static const fwk_id_t fwk_module_id_n1sdp_pll = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_PLL);
static const fwk_id_t fwk_module_id_n1sdp_i2c = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_I2C);
static const fwk_id_t fwk_module_id_n1sdp_dmc620 = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_DMC620);
static const fwk_id_t fwk_module_id_n1sdp_ddr_phy = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_DDR_PHY);
static const fwk_id_t fwk_module_id_mhu = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_MHU);
static const fwk_id_t fwk_module_id_smt = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SMT);
static const fwk_id_t fwk_module_id_scmi = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SCMI);
static const fwk_id_t fwk_module_id_sds = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SDS);
static const fwk_id_t fwk_module_id_pik_clock = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_PIK_CLOCK);
static const fwk_id_t fwk_module_id_css_clock = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_CSS_CLOCK);
static const fwk_id_t fwk_module_id_clock = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_CLOCK);
static const fwk_id_t fwk_module_id_gtimer = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_GTIMER);
static const fwk_id_t fwk_module_id_timer = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_TIMER);
static const fwk_id_t fwk_module_id_n1sdp_scp2pcc = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_SCP2PCC);
static const fwk_id_t fwk_module_id_n1sdp_sensor = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_SENSOR);
static const fwk_id_t fwk_module_id_sensor = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SENSOR);
static const fwk_id_t fwk_module_id_scmi_power_domain = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SCMI_POWER_DOMAIN);
static const fwk_id_t fwk_module_id_scmi_sensor = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SCMI_SENSOR);
static const fwk_id_t fwk_module_id_scmi_system_power = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SCMI_SYSTEM_POWER);
static const fwk_id_t fwk_module_id_scmi_management = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SCMI_MANAGEMENT);
static const fwk_id_t fwk_module_id_scmi_ccix_config = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SCMI_CCIX_CONFIG);
static const fwk_id_t fwk_module_id_fip = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_FIP);
static const fwk_id_t fwk_module_id_n1sdp_timer_sync = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_TIMER_SYNC);
static const fwk_id_t fwk_module_id_n1sdp_c2c = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_C2C);
static const fwk_id_t fwk_module_id_n1sdp_remote_pd = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_REMOTE_PD);
static const fwk_id_t fwk_module_id_n1sdp_pcie = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_PCIE);
static const fwk_id_t fwk_module_id_ssc = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SSC);
static const fwk_id_t fwk_module_id_system_info = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_SYSTEM_INFO);
static const fwk_id_t fwk_module_id_n1sdp_system = FWK_ID_MODULE_INIT(FWK_MODULE_IDX_N1SDP_SYSTEM);



#endif
