/*
 *  ZBT AP8100RT board support by lintel
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
#define AP8100RT_GPIO_BUTTON_RESET	14 

#define AP8100RT_GPIO_LED_POWER		8
#define AP8100RT_GPIO_LED_WLAN		9


#define AP8100RT_BUTTONS_POLL_INTERVAL	10
#define SZ_128K				0x020000
#define SZ_1M				0x100000
#define BLOCK_SZ_128K			SZ_128K
#define FLASH_SIZE			BLOCK_SZ_128K*128

#ifdef CONFIG_MTD_PARTITIONS
static struct mtd_partition ap8100rt_partitions[] = {

	{
		.name	= "u-boot",
		.offset	= 0,
		.size	= SZ_128K * 2,
	}, {
		.name	= "u-boot-env",
		.offset	= SZ_128K * 2,
		.size	= SZ_128K,
	}, {
		.name	= "factory",
		.offset	= SZ_128K * 3,
		.size	= SZ_128K,
	}, {
		.name	= "kernel",
		.offset	= SZ_128K * 4,
		.size	= SZ_1M,
	}, {
		.name	= "rootfs",
		.offset	= SZ_1M + SZ_128K * 4,
		.size	= FLASH_SIZE - (SZ_1M + SZ_128K * 4), 
	}, {
		.name	= "firmware",
		.offset	= SZ_128K * 4,
		.size	= FLASH_SIZE - (SZ_128K * 4), 
	}, {
		.name	= "fullflash",
		.offset	= 0x000000,
		.size	= FLASH_SIZE,
	}
};

#endif /* CONFIG_MTD_PARTITIONS */

static struct physmap_flash_data ap8100rt_flash_data = {
#ifdef CONFIG_MTD_PARTITIONS
	.nr_parts	= ARRAY_SIZE(ap8100rt_partitions),
	.parts		= ap8100rt_partitions,
#endif
};

static struct gpio_led ap8100rt_led_pins[] = {
   	{
		.name		= "ap8100rt:power",
		.gpio		= AP8100RT_GPIO_LED_POWER,
		.active_low	= 1,
		.default_trigger= "default-on",
	},{
		.name		= "ap8100rt:wlan",
		.gpio		= AP8100RT_GPIO_LED_WLAN,
		.active_low	= 1,
	},
};

static struct gpio_led_platform_data ap8100rt_led_data = {
	.leds		= ap8100rt_led_pins,
	.num_leds	= ARRAY_SIZE(ap8100rt_led_pins),
};

static struct platform_device ap8100rt_leds = {
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= {
		.platform_data	= &ap8100rt_led_data,
	}
};


static struct gpio_button ap8100rt_buttons[] __initdata = {

	{
/*
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = FONERA20N_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= FONERA20N_GPIO_BUTTON_RESET,
		.active_low	= 1,
*/
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= BTN_0,
		.gpio		= AP8100RT_GPIO_BUTTON_RESET,
		.active_low	= 1,
		.threshold      = AP8100RT_BUTTONS_POLL_INTERVAL,
	}
		
};


static void __init ap8100rt_init(void)
{
	rt305x_gpio_init(RT305X_GPIO_MODE_GPIO << RT305X_GPIO_MODE_UART0_SHIFT | RT305X_GPIO_MODE_I2C);
	
//	rt305x_register_flash(0, &ap8100rt_flash_data);
	rt305x_register_flash(0);
#if 0
	ramips_register_gpio_leds(-1, ARRAY_SIZE(ap8100rt_leds_gpio),
				  ap8100rt_leds_gpio);
	ramips_register_gpio_buttons(-1, AP8100RT_BUTTONS_POLL_INTERVAL,
				     ARRAY_SIZE(ap8100rt_gpio_buttons),
				     ap8100rt_gpio_buttons);
#else
	platform_device_register(&ap8100rt_leds);
	ramips_register_gpio_buttons(-1, AP8100RT_BUTTONS_POLL_INTERVAL,
                              ARRAY_SIZE(ap8100rt_buttons),
			      ap8100rt_buttons);
#endif

	rt305x_esw_data.vlan_config = RT305X_ESW_VLAN_CONFIG_VLAN_ALL;
	rt305x_register_ethernet();
	rt305x_register_wifi();
	rt305x_register_wdt();
	rt305x_register_usb();
	rt305x_register_gpiodev();
}

MIPS_MACHINE(RAMIPS_MACH_AP8100RT, "AP8100RT", "ZBT AP8100RT",
	     ap8100rt_init);
