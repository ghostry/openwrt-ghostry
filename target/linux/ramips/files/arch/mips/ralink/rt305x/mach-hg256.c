/*
 *  HuaWei HG256 board support by lintel
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
#include <linux/leds.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>

#include <asm/mach-ralink/machine.h>
#include <asm/mach-ralink/dev-gpio-buttons.h>
#include <asm/mach-ralink/dev-gpio-leds.h>
#include <asm/mach-ralink/rt305x.h>
#include <asm/mach-ralink/rt305x_regs.h>

#include "devices.h"

/*
 Note:
 GPIO [6:3] is share with SPI interface,so,if use for gpio,must disable the SPI.
 see datasheet Page NO.37.
 */
#define HG256_GPIO_BUTTON_RESET		4 
#define HG256_GPIO_BUTTON_WPS		10
#define HG256_GPIO_BUTTON_WLAN		0

#define HG256_GPIO_LED_POWER		8
#define HG256_GPIO_LED_USB		9
#define HG256_GPIO_LED_INTERNET		14
#define HG256_GPIO_LED_WLAN		12
#define HG256_GPIO_LED_ARI		13
#define HG256_GPIO_LED_VOICE		5


#define HG256_BUTTONS_POLL_INTERVAL	10
#define SZ_128K				0x020000
#define SZ_1M				0x100000
#define BLOCK_SZ_128K			SZ_128K
#define FLASH_SIZE			BLOCK_SZ_128K*128

#ifdef CONFIG_MTD_PARTITIONS
static struct mtd_partition hg256_partitions[] = {

	{
		.name	= "u-boot",
		.offset	= 0,
		.size	= SZ_128K,
//		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "kernel",
		.offset	= SZ_128K,
		.size	= SZ_1M,
	}, {
		.name	= "rootfs",
		.offset	= SZ_128K + SZ_1M,
		.size	= (SZ_1M * 8) - (SZ_128K * 2 + SZ_1M),
	}, {
		.name	= "firmware",
		.offset	= SZ_128K,
		.size	= (SZ_1M * 8) - (SZ_128K * 2),
	}, {
		.name	= "factory",
		.offset	= SZ_1M * 8 - SZ_128K,
		.size	= SZ_128K,
//		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "fullflash",
		.offset	= 0,
		.size	= 8 * SZ_1M,
	}
};
#endif /* CONFIG_MTD_PARTITIONS */

static struct physmap_flash_data hg256_flash_data = {
#ifdef CONFIG_MTD_PARTITIONS
	.nr_parts	= ARRAY_SIZE(hg256_partitions),
	.parts		= hg256_partitions,
#endif
};

static struct gpio_led hg256_led_pins[] = {
   	{
		.name		= "hg256:power",
		.gpio		= HG256_GPIO_LED_POWER,
		.active_low	= 1,
		.default_trigger= "default-on",
	}, {
		.name		= "hg256:internet",
		.gpio		= HG256_GPIO_LED_INTERNET,
		.active_low	= 1,
	}, {
		.name		= "hg256:wlan",
		.gpio		= HG256_GPIO_LED_WLAN,
		.active_low	= 1,
	}, {
		.name		= "hg256:usb",
		.gpio		= HG256_GPIO_LED_USB,
		.active_low	= 1,
	}, {
		.name		= "hg256:ari",
		.gpio		= HG256_GPIO_LED_ARI,
		.active_low	= 1,
	}, {
		.name		= "hg256:voice",
		.gpio		= HG256_GPIO_LED_VOICE,
		.active_low	= 1,
	}
};

static struct gpio_led_platform_data hg256_led_data = {
	.leds		= hg256_led_pins,
	.num_leds	= ARRAY_SIZE(hg256_led_pins),
};

static struct platform_device hg256_leds = {
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= {
		.platform_data	= &hg256_led_data,
	}
};


static struct gpio_button hg256_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= BTN_0,
		.gpio		= HG256_GPIO_BUTTON_RESET,
		.active_low	= 1,
		.threshold      = HG256_BUTTONS_POLL_INTERVAL,
//		.debounce_interval = 100,
	}, {
		.desc		= "wlan",
		.type		= EV_KEY,
		.code		= BTN_1,
		.gpio		= HG256_GPIO_BUTTON_WLAN,
		.active_low	= 1,
		.threshold      = HG256_BUTTONS_POLL_INTERVAL,
//		.debounce_interval = 100,
	}, {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= BTN_2,
		.gpio		= HG256_GPIO_BUTTON_WPS,
		.active_low	= 1,
		.threshold      = HG256_BUTTONS_POLL_INTERVAL,
//		.debounce_interval = 100,
	}
		
};


static void __init hg256_init(void)
{
	rt305x_gpio_init(RT305X_GPIO_MODE_GPIO << RT305X_GPIO_MODE_UART0_SHIFT | RT305X_GPIO_MODE_SPI | RT305X_GPIO_MODE_MDIO);
//	rt305x_gpio_init(RT305X_GPIO_MODE_GPIO << RT305X_GPIO_MODE_UART0_SHIFT | RT305X_GPIO_MODE_SPI );
	
//	rt305x_register_flash(0, &hg256_flash_data);
	rt305x_register_flash(0);
#if 0
	ramips_register_gpio_leds(-1, ARRAY_SIZE(hg256_leds_gpio),
				  hg256_leds_gpio);
	ramips_register_gpio_buttons(-1, HG256_BUTTONS_POLL_INTERVAL,
				     ARRAY_SIZE(hg256_gpio_buttons),
				     hg256_gpio_buttons);
#else
	platform_device_register(&hg256_leds);
	ramips_register_gpio_buttons(-1, HG256_BUTTONS_POLL_INTERVAL,
                              ARRAY_SIZE(hg256_buttons),
			      hg256_buttons);
#endif

	rt305x_esw_data.vlan_config = RT305X_ESW_VLAN_CONFIG_WLLLL;
	rt305x_register_ethernet();
	rt305x_register_wifi();
	rt305x_register_wdt();
	rt305x_register_usb();
	rt305x_register_gpiodev();
}

MIPS_MACHINE(RAMIPS_MACH_HG256, "HG256", "HuaWei HG256",
	     hg256_init);
