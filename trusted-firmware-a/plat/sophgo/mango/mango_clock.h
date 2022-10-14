#ifndef BM_CLOCK
#define BM_CLOCK

//PLL ID
#define PLL_CLK_START	0
#define MPLL_CLK	0
#define TPLL_CLK	1
#define FPLL_CLK	2
#define VPLL_CLK	3
#define DPLL0_CLK	4
#define DPLL1_CLK	5
#define PLL_CLK_END	5

/*div clock*/
#define GATE_CLK_START	6
#define GATE_CLK_EMMC_200M 6
#define GATE_CLK_SD_200M 7
#define GATE_CLK_UART_500M 8
#define GATE_CLK_EFUSE 9
#define GATE_CLK_AXI3 10
#define GATE_CLK_AXI6 11
#define GATE_CLK_AXI8 12
#define GATE_CLK_APB_TIMER 13
#define GATE_CLK_APB_EFUSE 14
#define GATE_CLK_APB_ROM 15
#define GATE_CLK_APB_GPIO 16
#define GATE_CLK_AHB_SF 17
#define GATE_CLK_APB_I2C 18
#define GATE_CLK_APB_WDT 19
#define GATE_CLK_AXI_EMMC 20
#define GATE_CLK_AXI_SD 21
#define GATE_CLK_100K_EMMC 22
#define GATE_CLK_100K_SD 23
#define GATE_CLK_GPIO_DB 24
#define GATE_CLK_A53 25
#define GATE_CLK_AXI10 26
#define GATE_CLK_RISCV 27
#define GATE_CLK_AXI_SPACC 28
#define GATE_CLK_AXI_PKA 29
#define GATE_CLK_AXI_DBG_I2C 30
#define GATE_CLK_AXISRAM 31
#define GATE_CLK_ARM 32
#define GATE_CLK_END 32

#define BM_CLK_RO	BIT(0) /* use reg divider value */
#define BM_CLK_USE_INIT_VAL	BIT(1) /* use default value */
#define BM_CLK_USE_REG_VAL	BIT(2) /* use setting value */

#define STATUS_OFFSET	0xC0
#define ENABLE_OFFSET	0xC4
#define PLL_CTRL_OFFSET	0xE8

#define PLL_STAT_LOCK_OFFSET	0x8

#define mhz	(1000000UL)
#define ghz	(1000000000UL)

#define REFDIV_MIN 1
#define REFDIV_MAX 64
#define FBDIV_MIN 16
#define FBDIV_MAX 321

#define PLL_FREQ_MIN (16 * mhz)
#define PLL_FREQ_MAX (3200 * mhz)

#define REF_CLOCK (25 * mhz)

#define TOP_PLL_CTRL(fbdiv, p1, p2, refdiv) \
	((((fbdiv) & 0xfff) << 16) | (((p2) & 0x7) << 12) | (((p1) & 0x7) << 8) | ((refdiv) & 0x1f))

enum clk_type {
	CLK_PLL,
	CLK_DIV,
	CLK_MUX,
	CLK_GATE
};

struct bm_pll_ctrl {
	unsigned long freq;

	unsigned int fbdiv;
	unsigned int postdiv1;
	unsigned int postdiv2;
	unsigned int refdiv;
};

struct bm_pll_clock {
	unsigned int id;
	char *name;
	unsigned int flags;
	unsigned int rate;

	struct bm_pll_ctrl pll;
};

struct bm_gate_clock {
	unsigned int id;
	const char *name;
	unsigned long flags;
	unsigned long offset;
	unsigned char bit_idx;
	unsigned char gate_flags;
};

int clk_set_rate(unsigned int index, unsigned long rate);
unsigned long clk_get_rate(unsigned int index);
int clk_enable(unsigned int index);
int clk_disable(unsigned int index);
int clk_is_enabled(unsigned int index);
#endif
