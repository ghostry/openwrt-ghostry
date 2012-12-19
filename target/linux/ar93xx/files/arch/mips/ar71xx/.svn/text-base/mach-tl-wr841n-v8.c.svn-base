/*
 *  Atheros WR841N_V8 board (WASP SoC) support
 *
 *  Copyright (C) 2010-2011 Jaiganesh Narayanan <jnarayanan@atheros.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>

#include <asm/mach-ar71xx/ar71xx.h>

#include "machtype.h"
#include "devices.h"
#include "dev-m25p80.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-usb.h"
#include "dev-ar9xxx-wmac.h"
#include "dev-db120-pci.h"

#define WR841N_V8_GPIO_LED_USB	11
#define WR841N_V8_GPIO_LED_WLAN_5G	12
#define WR841N_V8_GPIO_LED_WLAN_2G	13
#define WR841N_V8_GPIO_LED_STATUS	14
#define WR841N_V8_GPIO_LED_WPS	15

#define WR841N_V8_GPIO_BTN_SW1	16

#define WR841N_V8_CALDATA_OFFSET	0x1000
#define WR841N_V8_WMAC_MAC_OFFSET	0x1002

#define WR841N_V8_KEYS_POLL_INTERVAL	20	/* msecs */
#define WR841N_V8_KEYS_DEBOUNCE_INTERVAL	3

#ifdef CONFIG_MTD_PARTITIONS
static struct mtd_partition wr841n_v8_partitions[] = {
	{
		.name		= "u-boot",
		.offset		= 0,
		.size		= 0x040000,
	//	.mask_flags	= MTD_WRITEABLE,
	}, {
		.name		= "kernel",
		.offset		= 0x040000,
		.size		= 0x140000,
	}, {
		.name		= "rootfs",
		.offset		= 0x180000,
		.size		= 0x270000,
	}, {
		.name		= "art",
		.offset		= 0x3f0000,
		.size		= 0x010000,
		.mask_flags	= MTD_WRITEABLE,
	}, {
		.name		= "firmware",
		.offset		= 0x040000,
		.size		= 0x3b0000,
	}
};
#endif /* CONFIG_MTD_PARTITIONS */

static struct flash_platform_data wr841n_v8_flash_data = {
#ifdef CONFIG_MTD_PARTITIONS
	.parts		= wr841n_v8_partitions,
	.nr_parts	= ARRAY_SIZE(wr841n_v8_partitions),
#endif
};

static struct gpio_led wr841n_v8_leds_gpio[] __initdata = {
	{
		.name		= "wr841n_v8:green:status",
		.gpio		= WR841N_V8_GPIO_LED_STATUS,
		.active_low	= 1,
	}, {
		.name		= "wr841n_v8:green:wps",
		.gpio		= WR841N_V8_GPIO_LED_WPS,
		.active_low	= 1,
	}, {
		.name		= "wr841n_v8:green:wlan-5g",
		.gpio		= WR841N_V8_GPIO_LED_WLAN_5G,
		.active_low	= 1,
	}, {
		.name		= "wr841n_v8:green:wlan-2g",
		.gpio		= WR841N_V8_GPIO_LED_WLAN_2G,
		.active_low	= 1,
	}, {
		.name		= "wr841n_v8:green:usb",
		.gpio		= WR841N_V8_GPIO_LED_USB,
		.active_low	= 1,
	}
};

static struct gpio_button wr841n_v8_gpio_keys[] __initdata = {
	{
		.desc		= "sw1",
		.type		= EV_KEY,
		.code		= BTN_0,
		.threshold = WR841N_V8_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= WR841N_V8_GPIO_BTN_SW1,
		.active_low	= 1,
	}
};

static void __init wr841n_v8_setup(void)
{
	u8 *art = (u8 *) KSEG1ADDR(0x1fff0000);

	ar71xx_add_device_usb();

	ar71xx_add_device_m25p80(&wr841n_v8_flash_data);

	ar71xx_add_device_leds_gpio(-1, ARRAY_SIZE(wr841n_v8_leds_gpio),
					wr841n_v8_leds_gpio);

	ar71xx_register_gpio_keys_polled(-1, WR841N_V8_KEYS_POLL_INTERVAL,
					 ARRAY_SIZE(wr841n_v8_gpio_keys),
					 wr841n_v8_gpio_keys);


	/* ar71xx_eth1_data.has_ar7240_switch = 1;
	ar71xx_init_mac(ar71xx_eth0_data.mac_addr, mac, 0);
	ar71xx_init_mac(ar71xx_eth1_data.mac_addr, mac, 1);

	// WAN port 
	ar71xx_eth0_data.phy_if_mode = PHY_INTERFACE_MODE_RMII;
	ar71xx_eth0_data.speed = SPEED_100;
	ar71xx_eth0_data.duplex = DUPLEX_FULL;
	//ar71xx_eth0_data.phy_mask = BIT(4);

	// LAN ports 
	ar71xx_eth1_data.phy_if_mode = PHY_INTERFACE_MODE_RMII;
	ar71xx_eth1_data.speed = SPEED_1000;
	ar71xx_eth1_data.duplex = DUPLEX_FULL;

	ar71xx_add_device_mdio(0x0);
	ar71xx_add_device_eth(1);
	ar71xx_add_device_eth(0);
	*/

	ar9xxx_add_device_wmac(art + WR841N_V8_CALDATA_OFFSET,
				art + WR841N_V8_WMAC_MAC_OFFSET);

	db120_pci_init();
}

MIPS_MACHINE(AR71XX_MACH_TL_WR841N_V8, "TL-WR841N-V8", "TP-LINK WR841N_V8", wr841n_v8_setup);
