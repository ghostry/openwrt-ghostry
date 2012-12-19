/*
 *  Asus WAP120NF board support
 *
 *  Copyright (C) 2012 Frederic Leroy <fredo@starox.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>

#include <asm/mach-ralink/machine.h>
#include <asm/mach-ralink/dev-gpio-buttons.h>
#include <asm/mach-ralink/dev-gpio-leds.h>
#include <asm/mach-ralink/rt305x.h>
#include <asm/mach-ralink/rt305x_regs.h>

#include "devices.h"

#define WAP120NF_GPIO_LED_POWER		9
#define WAP120NF_GPIO_LED_WIFI		8
#define WAP120NF_GPIO_LED_WPS		14

#define WAP120NF_GPIO_BUTTON_RESET	10
#define WAP120NF_GPIO_BUTTON_WPS	0
#define WAP120NF_GPIO_BUTTON_WLAN	13

#define WAP120NF_KEYS_POLL_INTERVAL	10
#define WAP120NF_KEYS_DEBOUNCE_INTERVAL (3 * WAP120NF_KEYS_POLL_INTERVAL)

const struct flash_platform_data wap120nf_flash = {
	.type		= "mx25l3205d",
};

struct spi_board_info wap120nf_spi_slave_info[] __initdata = {
	{
		.modalias	= "m25p80",
		.platform_data	= &wap120nf_flash,
		.irq		= -1,
		.max_speed_hz	= 10000000,
		.bus_num	= 0,
		.chip_select	= 0,
	},
};

static struct gpio_button wap120nf_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= BTN_0,
//		.debounce_interval = WAP120NF_KEYS_DEBOUNCE_INTERVAL,
		.threshold	= WAP120NF_KEYS_POLL_INTERVAL,
		.gpio		= WAP120NF_GPIO_BUTTON_RESET,
		.active_low	= 1,
	},
	{
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= BTN_2,
//		.debounce_interval = WAP120NF_KEYS_DEBOUNCE_INTERVAL,
		.threshold	= WAP120NF_KEYS_POLL_INTERVAL,
		.gpio		= WAP120NF_GPIO_BUTTON_WPS,
		.active_low	= 1,
	},
	{
		.desc		= "wlan",
		.type		= EV_KEY,
		.code		= BTN_1,
//		.debounce_interval = WAP120NF_KEYS_DEBOUNCE_INTERVAL,
		.threshold	= WAP120NF_KEYS_POLL_INTERVAL,
		.gpio		= WAP120NF_GPIO_BUTTON_WLAN,
		.active_low	= 1,
	}
};

static struct gpio_led wap120nf_leds_gpio[] __initdata = {
	{
		.name		= "wap120nf:power",
		.gpio		= WAP120NF_GPIO_LED_POWER,
		.active_low	= 1,
	}, {
		.name		= "wap120nf:wifi",
		.gpio		= WAP120NF_GPIO_LED_WIFI,
		.active_low	= 1,
	}, {
		.name		= "wap120nf:wps",
		.gpio		= WAP120NF_GPIO_LED_WPS,
		.active_low	= 1,
	}
};

static void __init wap120nf_init(void)
{
	rt305x_gpio_init(RT305X_GPIO_MODE_I2C |
			 RT305X_GPIO_MODE_GPIO << RT305X_GPIO_MODE_UART0_SHIFT);
	rt305x_register_spi(wap120nf_spi_slave_info,
			    ARRAY_SIZE(wap120nf_spi_slave_info));
	rt305x_esw_data.vlan_config = RT305X_ESW_VLAN_CONFIG_WLLLL;
	rt305x_register_ethernet();
	ramips_register_gpio_leds(-1, ARRAY_SIZE(wap120nf_leds_gpio),
				  wap120nf_leds_gpio);
	ramips_register_gpio_buttons(-1, WAP120NF_KEYS_POLL_INTERVAL,
				     ARRAY_SIZE(wap120nf_gpio_buttons),
				     wap120nf_gpio_buttons);
	rt305x_register_wifi();
	rt305x_register_usb();
	rt305x_register_wdt();
	rt305x_register_gpiodev();
}

MIPS_MACHINE(RAMIPS_MACH_WAP120NF, "WAP120NF", "ZyXEL WAP120NF",
	     wap120nf_init);
