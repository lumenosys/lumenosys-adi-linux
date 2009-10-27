/*
 * header file fortone adau1761 sound chip
 *
 * Copyright 2009 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */


#ifndef __ADAU1761_H__
#define __ADAU1761_H__

struct adau1761_setup_data {
	unsigned short i2c_bus;
	unsigned short i2c_address;
};

struct adau1761_mode_register {
	u16  regaddress;
	u16  regvalue;
};

#define RESET_REGISTER_COUNT 54
#define MODE_REGISTER_COUNT 10

/* DSP program patch for ADAU1761 ADC IIS 16bit mode */
#define ADAU1716_ADC_SOFT_PATCH 1
#define MASTER_MODE 1
#ifdef MASTER_MODE
/* IIS mater mode*/
#define ADAU_SRPT_CTRL0		0x01
#else
/* IIS slave mode*/
#define ADAU_SRPT_CTRL0 	0x00
#endif

/* adau1761_set_dai_sysclk clk_id */
#define ADAU1761_MCLK_ID	0
#define ADAU1761_BCLK_ID	0x33

#define ADAU1761_MCLK_RATE	12288000

#define ADAU1761_PLL_FREQ_441	45158400
#define ADAU1761_PLL_FREQ_48	49152000

/* ADAU1761 Memory */
#define ADAU_PROGRAM	0x0800
#define ADAU_PARAMS	0x0000
#define ADAU_PROGSIZE	0x0400
#define ADAU_PARASIZE	0x0400

/* ADAU1761 control registers */
#define ADAU_FIRSTREG	0x4000

#define ADAU_CLKCTRL 	0x4000
#define ADAU_PLLCTRL	0x4002
#define ADAU_MICCTRL	0x4008
#define ADAU_RECPWRM	0x4009
#define ADAU_RECMLC0	0x400A
#define ADAU_RECMLC1	0x400B
#define ADAU_RECMRC0	0x400C
#define ADAU_RECMRC1	0x400D
#define ADAU_RECVLCL	0x400E
#define ADAU_RECVLCR	0x400F

#define ADAU_RECMBIA	0x4010
#define ADAU_ALCCTR0	0x4011
#define ADAU_ALCCTR1	0x4012
#define ADAU_ALCCTR2	0x4013
#define ADAU_ALCCTR3	0x4014
#define ADAU_SPRTCT0	0x4015
#define ADAU_SPRTCT1	0x4016
#define ADAU_CONVCT0	0x4017
#define ADAU_CONVCT1	0x4018
#define ADAU_ADCCTL0	0x4019
#define ADAU_ADCCTL1	0x401A
#define ADAU_ADCCTL2	0x401B
#define ADAU_PLBMLC0	0x401C
#define ADAU_PLBMLC1	0x401D
#define ADAU_PLBMRC0	0x401E
#define ADAU_PLBMRC1	0x401F

#define ADAU_PLBMLLO	0x4020
#define ADAU_PLBMRLO	0x4021
#define ADAU_PLBLRMC	0x4022
#define ADAU_PLBHPVL	0x4023
#define ADAU_PLBHPVR	0x4024
#define ADAU_PLBLOVL	0x4025
#define ADAU_PLBLOVR	0x4026
#define ADAU_PLBMNOC	0x4027
#define ADAU_PLBCTRL	0x4028
#define ADAU_PLBPWRM	0x4029

#define ADAU_DACCTL0	0x402A
#define ADAU_DACCTL1	0x402B
#define ADAU_DACCTL2	0x402C
#define ADAU_SERPAD0	0x402D
#define ADAU_SERPAD1	0x402E
#define ADAU_COMPAD0	0x402F
#define ADAU_COMPAD1	0x4030
#define ADAU_MCLKPAD	0x4031

/* DSP Core */
#define ADAU_DSP_CRC	0x40C0
#define ADAU_DSP_GPI	0x40C6
#define ADAU_NON_MOD	0x40E9
#define ADAU_WATCGDG	0x40D0
#define ADAU_DSP_SR0	0x40EA
#define ADAU_DSP_SR1	0x40EB

#define ADAU_INP_ROT	0x40F2
#define ADAU_OUT_ROT	0x40F3
#define ADAU_SER_DAT	0x40F4
#define ADAU_DSP_ENA	0x40F5
#define ADAU_DSP_RUN	0x40F6
#define ADAU_DSP_SLW	0x40F7
#define ADAU_SER_SRT	0x40F8
#define ADAU_CLK_EN0	0x40F9
#define ADAU_CLK_EN1	0x40FA

#define ADAU_LASTREG	0x40FA
#define ADAU_NUMCACHEREG	251

/* Register field definitions */
/* Clock Control */
#define CLKCTRL_SRC_MCLK	0x0
#define CLKCTRL_SRC_PLL		0x8
#define CLKCTRL_FRQ_256		0x0
#define CLKCTRL_FRQ_512		0x2
#define CLKCTRL_FRQ_768		0x4
#define CLKCTRL_FRQ_1024	0x6
#define CLKCTRL_DISABLE		0x0
#define CLKCTRL_ENABLE		0x1

/* PLL Control -- 6 bytes*/
/*Bytes 5-6*/
#define PLLCTRL_DEN_MSB		0x00
#define PLLCTRL_DEN_LSB		0x00
/*Bytes 3-4*/
#define PLLCTRL_NUM_MSB		0x00
#define PLLCTRL_NUM_LSB		0x00
/*Byte 2*/
#define PLLCTRL_INTPART_R2	0x10
#define PLLCTRL_INTPART_R3	0x18
#define PLLCTRL_INTPART_R4	0x20
#define PLLCTRL_INTPART_R5	0x28
#define PLLCTRL_INTPART_R6	0x30
#define PLLCTRL_INTPART_R7	0x38
#define PLLCTRL_INTPART_R8	0x40
#define PLLCTRL_INPUT_DIV1	0x00
#define PLLCTRL_INPUT_DIV2	0x02
#define PLLCTRL_INPUT_DIV3	0x04
#define PLLCTRL_INPUT_DIV4	0x06
#define PLLCTRL_TYPE_INT	0x0
#define PLLCTRL_TYPE_FRAC	0x1
/*Byte 1*/
#define PLLCTRL_DISABLE		0x0
#define PLLCTRL_ENABLE		0x1

/*ADC*/
#define ADCCTL_DISABLE_MASK	0xFC
#define ADCCTL_ENABLE_MASK	0x03

/*MIC*/
#define RECMBIA_DISABLE		0x00
#define RECMBIA_ENABLE		0x01
#define RECVLC_DISABLE_MASK	0xFC
#define RECVLC_ENABLE_MASK	0x03

#define RECMLC_MIC_0DB		0x08
#define RECMLC_MIC_20DB		0x10
#define RECMLC_LINE_0DB		0x05

/* PWN MNGMNT */
#define RECPWRM_LOW_PWR		0x0E
#define PLBPWRM_LOW_PWR		0x5C
#define PLBCTRL_POP_LPWR	0x10
#define PLBCTRL_POP_OFF		0x06
#define PLBCTRL_POP_ON		0x00
#define CLK_EN1_MASTER		0x03
#define CLK_EN1_SLAVE		0x01
#define CLK_EN1_OFF		0x00
#define CLK_EN0_OFF		0x00
#define CLK_EN0_ON		0x5F
#define RECPWRM_RUN_PWR		0x00
#define PLBPWRM_RUN_PWR		0x03
#define DAPM_LINE_DEF		0xE6
#define DAPM_HP_DEF		0xE7
#define PLB_MUTE_MASK		0x03

#define ADAU1761_BITSFRAM_32	0x4000
#define ADAU1761_BITSFRAM_48	0x8000

/*playback output control*/
#define ADAU1761_VOLUME_MASK 0xFC
#define ADAU1761_VOLUME_BITS 0x2
#define ADAU1761_MUTE_MASK 0x02
#define ADAU1761_MUTE_BITS 0x1
#define ADAU1761_ADVOL_MASK 0xff

/*
 * Reset Mode - ADC capture/DAC playback, dsp core disabled
 * (AInput mixers 0db, AOuput mixers 0db, HP out ON, DSP core OFF)
*/
static struct adau1761_mode_register adau1761_reset[RESET_REGISTER_COUNT] = {
	/* mute outputs */
	{ADAU_PLBMNOC, 0xE5},
	{ADAU_PLBHPVL, 0x01},
	{ADAU_PLBHPVR, 0x01},
	{ADAU_PLBLOVL, 0x00},
	{ADAU_PLBLOVR, 0x00},

	{ADAU_DSP_RUN, 0x00},
	{ADAU_DSP_ENA, 0x00},
	{ADAU_MICCTRL, 0x00},
	{ADAU_RECPWRM, 0x00},
	{ADAU_RECMLC0, 0x01},
	{ADAU_RECMLC1, RECMLC_MIC_0DB},
	{ADAU_RECMRC0, 0x01},
	{ADAU_RECMRC1, RECMLC_MIC_0DB},
	{ADAU_RECVLCL, 0x82},
	{ADAU_RECVLCR, 0x82},
	{ADAU_RECMBIA, RECMBIA_DISABLE},
	{ADAU_ALCCTR0, 0x00},
	{ADAU_ALCCTR1, 0x00},
	{ADAU_ALCCTR2, 0x00},
	{ADAU_ALCCTR3, 0x1F},
	{ADAU_SPRTCT0, ADAU_SRPT_CTRL0},
	{ADAU_SPRTCT1, 0x21}, /*0x21 = 32bclocks frame, 0x41 = 48*/
	{ADAU_CONVCT0, 0x00},
	{ADAU_CONVCT1, 0x00},
	{ADAU_ADCCTL0, 0x00},
	{ADAU_ADCCTL1, 0x00},
	{ADAU_ADCCTL2, 0x00},
	{ADAU_PLBMLC0, 0x21},
	{ADAU_PLBMLC1, 0x00},
	{ADAU_PLBMRC0, 0x41},
	{ADAU_PLBMRC1, 0x00},
	{ADAU_PLBMLLO, 0x03},
	{ADAU_PLBMRLO, 0x09},
	{ADAU_PLBLRMC, 0x01},
	{ADAU_PLBCTRL, 0x00},
	{ADAU_PLBPWRM, 0x00},
	{ADAU_DACCTL0, 0x03},
	{ADAU_DACCTL1, 0x00},
	{ADAU_DACCTL2, 0x00},
	{ADAU_DSP_CRC, 0x00},
	{ADAU_DSP_GPI, 0x00},
	{ADAU_DSP_SR1, 0x07},
	{ADAU_SERPAD0, 0xAA},
	{ADAU_SERPAD1, 0x00},
	{ADAU_COMPAD0, 0xAA},
	{ADAU_COMPAD1, 0x00},
	{ADAU_MCLKPAD, 0x0A},
	{ADAU_INP_ROT, 0x01},
#ifdef ADAU1716_ADC_SOFT_PATCH
	{ADAU_OUT_ROT, 0x00},
#else
	{ADAU_OUT_ROT, 0x01},
#endif
	{ADAU_SER_SRT, 0x00},
	{ADAU_DSP_SLW, 0x00},
	{ADAU_SER_DAT, 0x00},
	{ADAU_CLK_EN0, 0x5F},
	{ADAU_CLK_EN1, 0x01},
};

/*
 * Default Mode
 * Analog microphones, ADC capture/DAC playback, dsp core disabled
 * (AInput mixers ON, AOuput mixers ON, HP out ON)
*/
static struct adau1761_mode_register adau1761_mode0[MODE_REGISTER_COUNT] = {
	/* mute outputs */
	{ADAU_PLBHPVL, 0x03},
	{ADAU_PLBHPVR, 0x03},
	{ADAU_PLBLOVL, 0x02},
	{ADAU_PLBLOVR, 0x02},
	{ADAU_PLBMNOC, 0xE5},

	{ADAU_CLK_EN0, 0x5F},
	{ADAU_CLK_EN1, 0x01},

	/*analog mic*/
	{ADAU_RECVLCL, 0x82},
	{ADAU_RECVLCR, 0x82},
	{ADAU_MICCTRL, 0x00},
};

/*
 * Digital Microphone mode,
 * IIS Master, ADC capture/DAC playback, dsp core disabled
 * (AInput mixers OFF, AOuput mixers ON, HP out ON)
 */
static struct adau1761_mode_register adau1761_mode1[MODE_REGISTER_COUNT] = {
	/* mute outputs */
	{ADAU_PLBHPVL, 0x03},
	{ADAU_PLBHPVR, 0x03},
	{ADAU_PLBLOVL, 0x02},
	{ADAU_PLBLOVR, 0x02},
	{ADAU_PLBMNOC, 0xE5},

	{ADAU_CLK_EN0, 0x5F},
	{ADAU_CLK_EN1, 0x03},

	/*digital mic*/
	{ADAU_RECVLCL, 0x00},
	{ADAU_RECVLCR, 0x00},
	{ADAU_MICCTRL, 0x20},
};

static struct adau1761_mode_register *adau1761_mode_registers[] = {
	adau1761_mode0,
	adau1761_mode1,
};

extern struct snd_soc_dai adau1761_dai;
extern struct snd_soc_codec_device soc_codec_dev_adau1761;

#endif
