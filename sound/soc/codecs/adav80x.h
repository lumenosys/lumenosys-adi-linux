/*
 * header file for ADAV80X parts
 *
 * Copyright 2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef _ADAV80X_H
#define _ADAV80X_H

/* Clock source */
#define ADAV80X_CLK_XIN		1
#define ADAV80X_CLK_PLL1	2
#define ADAV80X_CLK_PLL2	3
#define ADAV80X_CLK_INTERNAL1	4
#define ADAV80X_CLK_INTERNAL2	5
#define ADAV80X_CLK_MCLKI	6

#if defined(CONFIG_I2C) || defined(CONFIG_I2C_MODULE)
/* ADAV80X I2C interface requires left-shifting reg addr for 1-bit */
#define ADAV80X_NUM_REGS	(0x7E << 1)

#define ADAV80X_PLAYBACK_CTRL	(0x4 << 1)
#define ADAV80X_AUX_IN_CTRL	(0x5 << 1)
#define ADAV80X_REC_CTRL	(0x6 << 1)
#define ADAV80X_AUX_OUT_CTRL	(0x7 << 1)
#define ADAV80X_GDELAY_MUTE	(0x8 << 1)

#define ADAV80X_TX_CTRL		(0xC << 1)

#define ADAV80X_DPATH_CTRL1	(0x62 << 1)
#define ADAV80X_DPATH_CTRL2	(0x63 << 1)
#define ADAV80X_DAC_CTRL1	(0x64 << 1)
#define ADAV80X_DAC_CTRL2	(0x65 << 1)
#define ADAV80X_DAC_CTRL3	(0x66 << 1)
#define ADAV80X_DAC_CTRL4	(0x67 << 1)
#define ADAV80X_DAC_L_VOL	(0x68 << 1)
#define ADAV80X_DAC_R_VOL	(0x69 << 1)
#define ADAV80X_DAC_L_PEAK_VOL	(0x6A << 1)
#define ADAV80X_DAC_R_PEAK_VOL	(0x6B << 1)

#define ADAV80X_ADC_CTRL1	(0x6E << 1)
#define ADAV80X_ADC_CTRL2	(0x6F << 1)
#define ADAV80X_ADC_L_VOL	(0x70 << 1)
#define ADAV80X_ADC_R_VOL	(0x71 << 1)
#define ADAV80X_ADC_L_PEAK_VOL	(0x72 << 1)
#define ADAV80X_ADC_R_PEAK_VOL	(0x73 << 1)
#define ADAV80X_PLL_CTRL1	(0x74 << 1)
#define ADAV80X_PLL_CTRL2	(0x75 << 1)
#define ADAV80X_ICLK_CTRL1	(0x76 << 1)
#define ADAV80X_ICLK_CTRL2	(0x77 << 1)
#define ADAV80X_PLL_CLK_SRC	(0x78 << 1)

#define ADAV80X_PLL_OUTE	(0x7A << 1)
#define ADAV80X_ALC_CTRL1	(0x7B << 1)

#elif defined(CONFIG_SPI_MASTER)
/* from 0x0 to 0x7D */
#define ADAV80X_NUM_REGS 0x7E

#define ADAV80X_PLAYBACK_CTRL	0x4
#define ADAV80X_AUX_IN_CTRL	0x5
#define ADAV80X_REC_CTRL	0x6
#define ADAV80X_AUX_OUT_CTRL	0x7
#define ADAV80X_GDELAY_MUTE	0x8

#define ADAV80X_TX_CTRL		0xC

#define ADAV80X_DPATH_CTRL1	0x62
#define ADAV80X_DPATH_CTRL2	0x63
#define ADAV80X_DAC_CTRL1	0x64
#define ADAV80X_DAC_CTRL2	0x65
#define ADAV80X_DAC_CTRL3	0x66
#define ADAV80X_DAC_CTRL4	0x67
#define ADAV80X_DAC_L_VOL	0x68
#define ADAV80X_DAC_R_VOL	0x69
#define ADAV80X_DAC_L_PEAK_VOL	0x6A
#define ADAV80X_DAC_R_PEAK_VOL	0x6B

#define ADAV80X_ADC_CTRL1	0x6E
#define ADAV80X_ADC_CTRL2	0x6F
#define ADAV80X_ADC_L_VOL	0x70
#define ADAV80X_ADC_R_VOL	0x71
#define ADAV80X_ADC_L_PEAK_VOL	0x72
#define ADAV80X_ADC_R_PEAK_VOL	0x73
#define ADAV80X_PLL_CTRL1	0x74
#define ADAV80X_PLL_CTRL2	0x75
#define ADAV80X_ICLK_CTRL1	0x76
#define ADAV80X_ICLK_CTRL2	0x77
#define ADAV80X_PLL_CLK_SRC	0x78

#define ADAV80X_PLL_OUTE	0x7A
#define ADAV80X_ALC_CTRL1	0x7B

#endif

#endif
