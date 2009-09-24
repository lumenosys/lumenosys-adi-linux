/*
 * Copyright 2004-2007 Analog Devices Inc.
 *                2005 National ICT Australia (NICTA)
 *                      Aidan Williams <aidan@nicta.com.au>
 *
 * Thanks to Jamey Hicks.
 *
 * Only SMSC91C1111 was registered, may do more later.
 *
 * Licensed under the GPL-2
 */

#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/irq.h>

const char bfin_board_name[] = "Tepla-BF561";

/*
 *  Driver needs to know address, irq and flag pin.
 */
static struct resource smc91x_resources[] = {
	{
		.start	= 0x2C000300,
		.end	= 0x2C000320,
		.flags	= IORESOURCE_MEM,
	}, {
		.start	= IRQ_PROG_INTB,
		.end	= IRQ_PROG_INTB,
		.flags	= IORESOURCE_IRQ|IORESOURCE_IRQ_HIGHLEVEL,
	}, {
		.start	= IRQ_PF7,
		.end	= IRQ_PF7,
		.flags	= IORESOURCE_IRQ|IORESOURCE_IRQ_HIGHLEVEL,
	},
};

static struct platform_device smc91x_device = {
	.name          = "smc91x",
	.id            = 0,
	.num_resources = ARRAY_SIZE(smc91x_resources),
	.resource      = smc91x_resources,
};

#if defined(CONFIG_SERIAL_BFIN) || defined(CONFIG_SERIAL_BFIN_MODULE)
#ifdef CONFIG_SERIAL_BFIN_UART0
static struct resource bfin_uart0_resources[] = {
	{
		.start = 0xFFC00400,
		.end = 0xFFC004FF,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART_RX,
		.end = IRQ_UART_RX+1,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = IRQ_UART_ERROR,
		.end = IRQ_UART_ERROR,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = CH_UART_TX,
		.end = CH_UART_TX,
		.flags = IORESOURCE_DMA,
	},
	{
		.start = CH_UART_RX,
		.end = CH_UART_RX,
		.flags = IORESOURCE_DMA,
	},
#ifdef CONFIG_BFIN_UART0_CTSRTS
	{
		/*
		 * Refer to arch/blackfin/mach-xxx/include/mach/gpio.h for the GPIO map.
		 */
		.start = -1,
		.end = -1,
		.flags = IORESOURCE_IO,
	},
	{
		/*
		 * Refer to arch/blackfin/mach-xxx/include/mach/gpio.h for the GPIO map.
		 */
		.start = -1,
		.end = -1,
		.flags = IORESOURCE_IO,
	},
#endif
};

static struct platform_device bfin_uart0_device = {
	.name = "bfin-uart",
	.id = 0,
	.num_resources = ARRAY_SIZE(bfin_uart0_resources),
	.resource = bfin_uart0_resources,
};
#endif
#endif

#if defined(CONFIG_BFIN_SIR) || defined(CONFIG_BFIN_SIR_MODULE)
#ifdef CONFIG_BFIN_SIR0
static struct resource bfin_sir0_resources[] = {
	{
		.start = 0xFFC00400,
		.end = 0xFFC004FF,
		.flags = IORESOURCE_MEM,
	},
	{
		.start = IRQ_UART0_RX,
		.end = IRQ_UART0_RX+1,
		.flags = IORESOURCE_IRQ,
	},
	{
		.start = CH_UART0_RX,
		.end = CH_UART0_RX+1,
		.flags = IORESOURCE_DMA,
	},
};

static struct platform_device bfin_sir0_device = {
	.name = "bfin_sir",
	.id = 0,
	.num_resources = ARRAY_SIZE(bfin_sir0_resources),
	.resource = bfin_sir0_resources,
};
#endif
#endif

static struct platform_device *tepla_devices[] __initdata = {
	&smc91x_device,

#if defined(CONFIG_SERIAL_BFIN) || defined(CONFIG_SERIAL_BFIN_MODULE)
#ifdef CONFIG_SERIAL_BFIN_UART0
	&bfin_uart0_device,
#endif
#endif

#if defined(CONFIG_BFIN_SIR) || defined(CONFIG_BFIN_SIR_MODULE)
#ifdef CONFIG_BFIN_SIR0
	&bfin_sir0_device,
#endif
#endif
};

static int __init tepla_init(void)
{
	printk(KERN_INFO "%s(): registering device resources\n", __func__);
	return platform_add_devices(tepla_devices, ARRAY_SIZE(tepla_devices));
}

arch_initcall(tepla_init);
