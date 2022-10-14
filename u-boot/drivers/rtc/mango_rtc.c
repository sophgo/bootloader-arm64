// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright (C) 2021, sophgo - All Rights Reserved
 */
#include <common.h>
#include <clk.h>
#include <dm.h>
#include <rtc.h>
#include <asm/io.h>
#include <linux/iopoll.h>
/*********************************************************************/
/*register 32bit*/
#define MANGO_RTC_CCVR	0x00/*rtc_counter: rtc counter valu */
#define MANGO_RTC_CMR	0x04/*interrupt when reg val match rtc_counter*/
#define MANGO_RTC_CLR	0x08/*reg val is rtc_counter can be updated */
#define MANGO_RTC_CCR	0x0C/*counter control reg*/
#define MANGO_RTC_STAT	0x10/*interrupt status reg*/
#define MANGO_RTC_CPSR	0x20/*reg val is rtc_pre_counter max */
#define MANGO_RTC_CPCVR	0x24/*reg val is rtc_pre_counter*/

#define _RTC_COMP_VERSION	0X1C /*apb rtc version*/

/*reg RTC_CCR control bit*/
#define RTC_IEN_BIT	0x00
#define RTC_MASK_BIT	0X01
#define RTC_EN_BIT	0X02
#define RTC_WEN_BIT	0X03
#define RTC_PSCLR_EN_BIT	0X04
#define RTC_DEFAULT_TIME	0x01

struct mango_rtc_priv {
	void __iomem *base;
	unsigned int rtc_counter;
};

static int mango_rtc_get(struct udevice *dev, struct rtc_time *tm)
{
	ulong time;
	struct mango_rtc_priv *priv = dev_get_priv(dev);

	time = readl((void *)(priv->base + MANGO_RTC_CCVR));
	rtc_to_tm(time, tm);
	return 0;
}

static int mango_rtc_set(struct udevice *dev, const struct rtc_time *tm)
{
	ulong time;
	struct mango_rtc_priv *priv = dev_get_priv(dev);

	time = rtc_mktime(tm);
	writel(time, (void *)(priv->base + MANGO_RTC_CLR));
	return 0;
}

static int mango_rtc_reset(struct udevice *dev)
{
	struct mango_rtc_priv *priv = dev_get_priv(dev);

	writel(RTC_DEFAULT_TIME, (void *)(priv->base + MANGO_RTC_CLR));
	return 0;

}

static int mango_rtc_init(struct udevice *dev)
{
	unsigned long val;
	unsigned long RTC_COUNTER_MATCH = 0x10;
	unsigned long RTC_PRESCLR_VALUE = 0x7fff;
	struct mango_rtc_priv *priv = dev_get_priv(dev);

	/*config CCR*/
	val = readl((void *)(priv->base + MANGO_RTC_CCR));
	/*enable rtc_pre_counter*/
	val |= (1 << RTC_PSCLR_EN_BIT);
	/*no clean rtc_counter*/
	val &= ~(1 << RTC_WEN_BIT);
	/*disable rtc*/
	val &= ~(1 << RTC_EN_BIT);
	/*disable mask*/
	val &= ~(1 << RTC_MASK_BIT);
	/*disable interrupt*/
	val &= ~(1 << RTC_IEN_BIT);
	/*insert config*/
	writel(val, (void *)(priv->base + MANGO_RTC_CCR));

	/*config CMR*/
	writel(RTC_COUNTER_MATCH, (void *)(priv->base + MANGO_RTC_CMR));

	/*config CPSR*/
	writel(RTC_PRESCLR_VALUE, (void *)(priv->base + MANGO_RTC_CPSR));

	/*config CLR*/
	writel(RTC_DEFAULT_TIME, (void *)(priv->base + MANGO_RTC_CLR));

	/*enable rtc*/
	val = readl((void *)(priv->base + MANGO_RTC_CCR));
	val |= (1 << RTC_EN_BIT);
	writel(val, (void *)(priv->base + MANGO_RTC_CCR));
	return 0;
}

static int mango_rtc_probe(struct udevice *dev)
{
	return mango_rtc_init(dev);
}

static int mango_rtc_ofdata_to_platdata(struct udevice *dev)
{
	struct mango_rtc_priv *priv = dev_get_priv(dev);

	debug("%s:base =%p\n", __func__, priv->base);
	priv->base = (void __iomem *)dev_read_addr(dev);

	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);
	priv->rtc_counter = dev_read_u32_default(dev, "rtc-counter", 0);

	return 0;

}

static const struct rtc_ops mango_rtc_ops = {
	.get = mango_rtc_get,
	.set = mango_rtc_set,
	.reset = mango_rtc_reset,
};

static const struct udevice_id mango_rtc_ids[] = {
	{ .compatible = "sophgo,mango-rtc" },
	{ }
};

U_BOOT_DRIVER(mango_rtc) = {
	.name	= "mango-rtc",
	.id	= UCLASS_RTC,
	.probe	= mango_rtc_probe,
	.of_match = mango_rtc_ids,
	.ops	= &mango_rtc_ops,
	.priv_auto = sizeof(struct mango_rtc_priv),
	.of_to_plat = mango_rtc_ofdata_to_platdata,
};
