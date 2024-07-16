#ifndef __MOD_PPU_V1_H__
#define __MOD_PPU_V1_H__

/* NOT IMPLEMENTED */
struct mod_ppu_v1_power_state_observer_api {
    /*!
     * \brief Called after a PPU has turned on.
     *
     * \param param Generic configurable parameter.
     */
    void (*post_ppu_on)(void *param);
};

#endif
