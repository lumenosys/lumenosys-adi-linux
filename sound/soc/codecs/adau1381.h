/*
 * header file fortone adau1381 sound chip
 *
 * Copyright 2010 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */


#ifndef __ADAU1381_H__
#define __ADAU1381_H__

struct adau1381_setup_data {
	unsigned short i2c_bus;
	unsigned short i2c_address;
};

struct adau1381_mode_register {
	u16  regaddress;
	u16  regvalue;
};

#define RESET_REGISTER_COUNT 40
#define MODE_REGISTER_COUNT 1

#define MASTER_MODE 1
#ifdef MASTER_MODE
/* IIS mater mode*/
#define ADAU_SRPT_CTRL0		0x01
#else
/* IIS slave mode*/
#define ADAU_SRPT_CTRL0 	0x00
#endif

/* adau1381_set_dai_sysclk clk_id */
#define ADAU1381_MCLK_ID	0
#define ADAU1381_BCLK_ID	0x33

#define ADAU1381_MCLK_RATE	12288000

#define ADAU1381_PLL_FREQ_441	45158400
#define ADAU1381_PLL_FREQ_48	49152000


/* ADAU1381 control registers */
#define ADAU_FIRSTREG	0x4000

#define ADAU_CLKCTRL 	0x4000
#define ADAU_RGUCTRL	0x4001
#define ADAU_PLLCTRL	0x4002
#define ADAU_RECCTRL	0x4008
#define ADAU_RECPWRM	0x4009
#define ADAU_RECGAIL	0x400E
#define ADAU_RECGAIR	0x400F
#define ADAU_RECMBIA	0x4010
#define ADAU_SPRTCT0	0x4015
#define ADAU_SPRTCT1	0x4016
#define ADAU_CONVCT0	0x4017
#define ADAU_CONVCT1	0x4018
#define ADAU_ADCCTL0	0x4019
#define ADAU_LADCATT	0x401A
#define ADAU_RADCATT	0x401B
#define ADAU_PLMLCTL	0x401C
#define ADAU_PLMRCTL	0x401E
#define ADAU_PLBMCTL	0x401F
#define ADAU_PLBCAMP	0x4020
#define ADAU_RLOMUTE	0x4025
#define ADAU_LLOMUTE	0x4026
#define ADAU_PLSPCTL	0x4027
#define ADAU_ZXDETCT	0x4028
#define ADAU_PLBPWRM	0x4029
#define ADAU_DACCTRL	0x402A
#define ADAU_LDACATT	0x402B
#define ADAU_RDACATT	0x402C
#define ADAU_SERPAD0	0x402D
#define ADAU_SERPAD1	0x402E
#define ADAU_COMPAD0	0x402F
#define ADAU_COMPAD1	0x4030
#define ADAU_MCKOCTL	0x4031
#define ADAU_DIGPWR0	0x4080
#define ADAU_DIGPWR1	0x4081
#define ADAU_FRMRATE	0x40EB
#define ADAU_INPRCON	0x40F2
#define ADAU_OUPRCON	0x40F3
#define ADAU_PINCONF	0x40F4
#define ADAU_ENGIRUN	0x40F6
#define ADAU_SAMRATE	0x40F8


#define ADAU_LASTREG	0x40F8

#define ADAU_NUMCACHEREG	40

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
#define RECPWRM_RUN_PWR		0x00
#define PLBPWRM_RUN_PWR		0x03
#define DAPM_LINE_DEF		0xE6
#define DAPM_HP_DEF		0xE7
#define PLB_MUTE_MASK		0x03

#define ADAU1381_BITSFRAM_32	0x4000
#define ADAU1381_BITSFRAM_48	0x8000

/*playback output control*/
#define ADAU1381_VOLUME_MASK 0xFC
#define ADAU1381_VOLUME_BITS 0x2
#define ADAU1381_MUTE_MASK 0x02
#define ADAU1381_MUTE_BITS 0x1
#define ADAU1381_ADVOL_MASK 0xff

/*
 * Reset Mode - ADC capture/DAC playback
 * (AInput mixers 0db, AOuput mixers 0db, HP out ON)
*/
static struct adau1381_mode_register adau1381_reset[RESET_REGISTER_COUNT] = {
	/* mute outputs */
	{ADAU_RGUCTRL, 0x00},
	{ADAU_RECCTRL, 0x00},
	{ADAU_RECPWRM, 0x00},
	{ADAU_RECGAIL, 0x07},
	{ADAU_RECGAIR, 0x07},
	{ADAU_RECMBIA, RECMBIA_DISABLE},
	{ADAU_SPRTCT0, ADAU_SRPT_CTRL0},
	{ADAU_SPRTCT1, 0x21}, /*0x21 = 32bclocks frame, 0x41 = 48*/
	{ADAU_CONVCT0, 0x00},
	{ADAU_CONVCT1, 0x00},
	{ADAU_ADCCTL0, 0x00},
	{ADAU_LADCATT, 0x00},
	{ADAU_RADCATT, 0x00},
	{ADAU_PLMLCTL, 0x20},
	{ADAU_PLMRCTL, 0x20},
	{ADAU_PLBMCTL, 0x00},
	{ADAU_PLBCAMP, 0x00},
	{ADAU_RLOMUTE, 0x02},
	{ADAU_LLOMUTE, 0x02},
	{ADAU_PLSPCTL, 0x01},
	{ADAU_ZXDETCT, 0x01},
	{ADAU_PLBPWRM, 0x00},
	{ADAU_DACCTRL, 0x03},
	{ADAU_LDACATT, 0x00},
	{ADAU_RDACATT, 0x00},
	{ADAU_SERPAD0, 0xAA},
	{ADAU_SERPAD1, 0x00},
	{ADAU_COMPAD0, 0xAA},
	{ADAU_COMPAD1, 0x00},
	{ADAU_MCKOCTL, 0x00},
};

static struct adau1381_mode_register adau1381_mode0[MODE_REGISTER_COUNT] = {
	/*analog mic*/
	{ADAU_RECCTRL, 0x00},
};

static struct adau1381_mode_register adau1381_mode1[MODE_REGISTER_COUNT] = {
	/*digital mic*/
	{ADAU_RECCTRL, 0x10},
};

static struct adau1381_mode_register *adau1381_mode_registers[] = {
	adau1381_mode0,
	adau1381_mode1,
};

extern struct snd_soc_dai adau1381_dai;
extern struct snd_soc_codec_device soc_codec_dev_adau1381;

#endif