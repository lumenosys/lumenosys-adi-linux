/*
 * AD7160 touchscreen (bus interfaces)
 *
 * Copyright (C) 2010 Michael Hennerich, Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef _AD7160_H_
#define _AD7160_H_

#include <linux/types.h>

#define AD7160_REG_AFE_DEVID			0x40050114
#define AD7160_REG_DEVICE_ID			0x40051700
#define AD7160_REG_REV_ID			0x40051704
#define AD7160_REG_FW_REV			0x40051708
#define AD7160_REG_FP_AFE_AMB			0x4005170C
#define AD7160_REG_LP_AFE_AMB			0x40051710
#define AD7160_REG_DMA_RAM_ADDR_CTRL		0x40051714
#define AD7160_REG_DMA_CTRL			0x40051718
#define AD7160_REG_AFE_DAC_OFFS_CTRL		0x4005171C
#define AD7160_REG_LPM_CTRL			0x40051720
#define AD7160_REG_BOOT_MODE_CTRL		0x40051724
#define AD7160_REG_FINGER_ACT_CTRL		0x40051738
#define AD7160_REG_XY_NB_SENSORS		0x4005173C
#define AD7160_REG_XY_RES			0x40051740
#define AD7160_REG_POSITION_WINDOW_CTRL		0x40051744
#define AD7160_REG_INT_GEST_EN_CTRL		0x4005175C
#define AD7160_REG_HORZ_VERT_GEST_CTRL		0x40051760
#define AD7160_REG_PINCH_CTRL			0x40051764
#define AD7160_REG_ROT_CTRL			0x40051768
#define AD7160_REG_HAPTIC_CTRL			0x40051780
#define AD7160_REG_HAPTIC_EFFECT1_CTRL		0x40051784
#define AD7160_REG_HAPTIC_EFFECT2_CTRL		0x40051788
#define AD7160_REG_HAPTIC_EFFECT3_CTRL1		0x4005178C
#define AD7160_REG_HAPTIC_EFFECT3_CTRL2		0x40051790
#define AD7160_REG_HAPTIC_EFFECT4_CTRL1		0x40051794
#define AD7160_REG_HAPTIC_EFFECT4_CTRL2		0x40051798
#define AD7160_REG_HAPTIC_EFFECT5_CTRL1		0x4005179C
#define AD7160_REG_HAPTIC_EFFECT5_CTRL2		0x400517A0
#define AD7160_REG_HAPTIC_EFFECT5_CTRL3		0x400517A4
#define AD7160_REG_HAPTIC_EFFECT6_CTRL1		0x400517A8
#define AD7160_REG_HAPTIC_EFFECT6_CTRL2		0x400517AC
#define AD7160_REG_HAPTIC_EFFECT6_CTRL3		0x400517B0
#define AD7160_REG_AFE_OFFS_ADJ_STAT		0x400517DC
#define AD7160_REG_PRESSURE_STAT		0x400517E0
#define AD7160_REG_FINGER_ACT_STAT		0x400517E4
#define AD7160_REG_GEST_STAT			0x400517E8
#define AD7160_REG_NB_FINGERS			0x400517EC
#define AD7160_REG_POS_DATA_STATUS1		0x400517F0
#define AD7160_REG_ABS_MT_TOUCH_STATUS1		0x400517F4
#define AD7160_REG_POS_DATA_STATUS2		0x400517F8
#define AD7160_REG_ABS_MT_TOUCH_STATUS2		0x400517FC
#define AD7160_REG_POS_DATA_STATUS3		0x40051800
#define AD7160_REG_ABS_MT_TOUCH_STATUS3		0x40051804
#define AD7160_REG_POS_DATA_STATUS4		0x40051808
#define AD7160_REG_ABS_MT_TOUCH_STATUS4		0x4005180C
#define AD7160_REG_POS_DATA_STATUS5		0x40051810
#define AD7160_REG_ABS_MT_TOUCH_STATUS5		0x40051814
#define AD7160_REG_POS_DATA_STATUS6		0x40051818
#define AD7160_REG_ABS_MT_TOUCH_STATUS6		0x4005181C
#define AD7160_REG_POS_DATA_STATUS7		0x40051820
#define AD7160_REG_ABS_MT_TOUCH_STATUS7		0x40051824
#define AD7160_REG_POS_DATA_STATUS8		0x40051828
#define AD7160_REG_ABS_MT_TOUCH_STATUS8		0x4005182C
#define AD7160_REG_POS_DATA_STATUS9		0x40051830
#define AD7160_REG_ABS_MT_TOUCH_STATUS9		0x40051834
#define AD7160_REG_POS_DATA_STATUS10		0x40051838
#define AD7160_REG_ABS_MT_TOUCH_STATUS10	0x4005183C
#define AD7160_REG_STAGE_READ_INDEX		0x40051868
#define AD7160_REG_STAGE_READ_SLF_CDC		0x4005186C
#define AD7160_REG_STAGE_READ_SLF_AMB		0x40051870
#define AD7160_REG_STAGE_READ_SLF_OFFS		0x40051874
#define AD7160_REG_STAGE_READ_HSTAT		0x40051878
#define AD7160_REG_STAGE_READ_PROX		0x4005187C
#define AD7160_REG_DEMO_CTRL_STAT		0x400517B4

#define REG_SIZE_BYTES		4
#define MAX_NUM_FINGERS		10
#define MAX_DATA_CNT		(MAX_NUM_FINGERS * 2)

struct ad7160;

struct ad7160_bus_ops {
	int (*read) (void *dev, u32 reg);
	int (*multi_read) (void *dev, u32 first_reg, u32 count, u32 *buf);
	int (*write) (void *dev, u32 reg, u32 val);
	int (*multi_write_bytes) (void *dev, u32 count, u8 *buf);
	void (*wakeup) (void *dev);
};

struct ad7160_bus_data {
	void *client;
	int irq;
	const struct ad7160_bus_ops *bops;
};

void ad7160_suspend(struct device *dev);
void ad7160_resume(struct device *dev);
int ad7160_probe(struct device *dev, struct ad7160_bus_data *bdata, u32 devid, u16 bustype);
int ad7160_remove(struct device *dev);

#if defined(CONFIG_TOUCHSCREEN_AD7160_RAW) || defined(CONFIG_TOUCHSCREEN_AD7160_RAW_MODULE)
int ad7160_probe_raw(struct device *dev, struct ad7160_bus_data *bdata, u32 devid, u16 bustype);
int ad7160_remove_raw(struct device *dev);
void ad7160_feed_raw(void);
#else
static inline void ad7160_feed_raw(void)
{
}

static inline int ad7160_probe_raw(struct device *dev, struct ad7160_bus_data *bdata, u32 devid, u16 bustype)
{
	return 0;
}

static inline int ad7160_remove_raw(struct device *dev)
{
	return 0;
}

#endif /* CONFIG_AD7160_RAW_DATA_IFACE */
#endif /* _AD7160_H_ */
