/*
 *  ASUS RT-N13U b2 board support
 *
 *  Copyright (C) 2012 lintel<lintel.huang@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/physmap.h>

#include <asm/mach-ralink/machine.h>
#include <asm/mach-ralink/dev-gpio-buttons.h>
#include <asm/mach-ralink/dev-gpio-leds.h>
#include <asm/mach-ralink/rt305x.h>
#include <asm/mach-ralink/rt305x_regs.h>

#include "devices.h"

#define RT_N13U_GPIO_BUTTON_RESET	10
#define RT_N13U_GPIO_BUTTON_WPS		0

#define RT_N13U_GPIO_LED_POWER		7
#define RT_N13U_GPIO_LED_WIFI		8


#define RT_N13U_BUTTONS_POLL_INTERVAL	10

#ifdef CONFIG_MTD_PARTITIONS
static struct mtd_partition rt_n13u_partitions[] = {
	{
		.name	= "u-boot",
		.offset	= 0,
		.size	= 0x030000,
		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "u-boot-env",
		.offset	= 0x030000,
		.size	= 0x010000,
		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "factory",
		.offset	= 0x040000,
		.size	= 0x010000,
		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "kernel",
		.offset	= 0x050000,
		.size	= 0x0a0000,
	}, {
		.name	= "rootfs",
		.offset	= 0x150000,
		.size	= 0x6b0000,
	}, {
		.name	= "firmware",
		.offset	= 0x050000,
		.size	= 0x7b0000,
	}
};
#endif /* CONFIG_MTD_PARTITIONS */

static struct physmap_flash_data rt_n13u_flash_data = {
#ifdef CONFIG_MTD_PARTITIONS
	.nr_parts	= ARRAY_SIZE(rt_n13u_partitions),
	.parts		= rt_n13u_partitions,
#endif
};

static struct gpio_led rt_n13u_leds_gpio[] __initdata = {
	{
		.name		= "rt-n13:power",
		.gpio		= RT_N13U_GPIO_LED_POWER,
		.active_low	= 1,
	}, {
		.name		= "rt-n13:wifi",
		.gpio		= RT_N13U_GPIO_LED_WIFI,
		.active_low	= 1,
	}
};

static struct gpio_button rt_n13u_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= BTN_0,
		.threshold	= RT_N13U_BUTTONS_POLL_INTERVAL,
		.gpio		= RT_N13U_GPIO_BUTTON_RESET,
		.active_low	= 1,
	}, {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= BTN_1,
		.threshold	= RT_N13U_BUTTONS_POLL_INTERVAL,
		.gpio		= RT_N13U_GPIO_BUTTON_WPS,
		.active_low	= 1,
	},
};

static void __init rt_n13u_init(void)
{
	rt305x_gpio_init(RT305X_GPIO_MODE_GPIO << RT305X_GPIO_MODE_UART0_SHIFT);

//	rt305x_register_flash(0, &rt_n13u_flash_data);
	rt305x_register_flash(0);

	ramips_register_gpio_leds(-1, ARRAY_SIZE(rt_n13u_leds_gpio),
				  rt_n13u_leds_gpio);

	ramips_register_gpio_buttons(-1, RT_N13U_BUTTONS_POLL_INTERVAL,
				     ARRAY_SIZE(rt_n13u_gpio_buttons),
				     rt_n13u_gpio_buttons);

	rt305x_esw_data.vlan_config = RT305X_ESW_VLAN_CONFIG_LLLLW;
	rt305x_register_ethernet();
	rt305x_register_wifi();
	rt305x_register_wdt();
	rt305x_register_usb();
	rt305x_register_gpiodev();
}

MIPS_MACHINE(RAMIPS_MACH_RT_N13U, "RT-N13U", "ASUS RT-N13",
	     rt_n13u_init);
