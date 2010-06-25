/*
 * Blackfin On-Chip MAC Driver
 *
 * Copyright 2004-2007 Analog Devices Inc.
 *
 * Enter bugs at http://blackfin.uclinux.org/
 *
 * Licensed under the GPL-2 or later.
 */
#ifndef _LINUX_BFIN_MAC_H_
#define _LINUX_BFIN_MAC_H_

#include <linux/phy.h>

struct bfin_phydev_platform_data {
	unsigned short addr;
	unsigned short irq;
};

struct bfin_mii_bus_platform_data {
	int phydev_number;
	struct bfin_phydev_platform_data *phydev_data;
	const unsigned short *mac_peripherals;
	int phy_mode;
};

#endif