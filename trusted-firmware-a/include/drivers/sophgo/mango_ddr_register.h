#ifndef __MANGO_DDR_REGISTER_H__
#define __MANGO_DDR_REGISTER_H__

#include <stdint.h>

#define CTRL_REG_COUNT         431
#define PHY_REG_COUNT          2450
#define PI_REG_COUNT           204

extern uint32_t ctl_registers[CTRL_REG_COUNT];
extern uint32_t phy_registers[PHY_REG_COUNT];
extern uint32_t pi_registers[PI_REG_COUNT];

#endif
