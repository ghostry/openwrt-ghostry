/*
 * MGB100 devices setup
 */
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/i2c-gpio.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/mtd/physmap.h>
#include <linux/clocksource.h>
#include <linux/jiffies.h>
#include <linux/gpio_keys.h>
#include <linux/input.h>

#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/device.h>
#include <linux/version.h>
#include <linux/mtd/map.h>
#include <linux/mtd/mtd.h>
#include <linux/root_dev.h>


#define MGB100_KEY_SHUTDOWN    0
#define MGB100_KEY_BACKUP      1
#define MGB100_LED_USB2        2
#define MGB100_LED_USB1        3
#define MGB100_LED_BACKUP      4
#define MGB100_LED_HDFILL      5

#define NSEC_PER_JIFFY	((u32)((((u64)NSEC_PER_SEC)<<8)/ACTHZ))
#define JIFFIES_SHIFT	8

// jiffies clock skew, seconds per hour
static int jiffskew;
static unsigned long jiff_last;
static int adj;
static int adj_last;

static cycle_t jiffskew_read(void)
{
    if( jiffies != jiff_last ) {
        adj_last += jiffskew;
        if( adj_last >= 3600 ) {
            ++adj;
            adj_last -= 3600;
        }else if( adj_last <= -3600 ) {
            --adj;
            adj_last += 3600;
        }
        ++jiff_last;
        if( jiff_last != jiffies ) {
            printk(KERN_WARNING "jiffskew: jiff_last=%lu, jiffies=%lu\n",
                    jiff_last, jiffies);
            jiff_last = jiffies;
        }
    }
    return (cycle_t) jiffies + adj;
}

static struct clocksource clocksource_jiffskew = {
	.name		= "jiffskew",
	.rating		= 115,
	.read		= jiffskew_read,
	.mask		= 0xffffffff, /*32bits*/
	.mult		= NSEC_PER_JIFFY << JIFFIES_SHIFT,
	.shift		= JIFFIES_SHIFT,
};

static int __init jiffskew_setup(char* str)
{
    if(str && !jiffskew) {
        jiffskew = simple_strtol(str, NULL, 0);
        if( jiffskew ) {
            jiff_last = jiffies;
            clocksource_register(&clocksource_jiffskew);
            printk(KERN_INFO "jiffskew clocksource loaded\n");
        }
    }
    return 1;
}

__setup("jiffskew=", jiffskew_setup);

static struct gpio_led mgb100_led_pins[] = {
	{
		.name		= "USB1",
		.gpio		= MGB100_LED_USB1,
		.active_low	= true,
	},
	{
		.name		= "USB2",
		.gpio		= MGB100_LED_USB2 ,
		.active_low	= true,
	},
	{
		.name		= "BACKUP",
		.gpio		= MGB100_LED_BACKUP,
		.active_low	= true,
	},
	{
		.name		= "HDD_Status",
		.gpio		= MGB100_LED_HDFILL,
		.active_low	= true,
	},
};

static struct gpio_led_platform_data mgb100_led_data = {
	.num_leds		= ARRAY_SIZE(mgb100_led_pins),
	.leds			= mgb100_led_pins,
};

static struct platform_device mgb100_leds = {
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platform_data	= &mgb100_led_data,
};


static struct resource gpiodev_resource = {
	.start			= 0xFFFFFFFF,
};


/* Button */
static struct gpio_keys_button rdc321x_gpio_btn[] = {
	{
		.gpio = MGB100_KEY_SHUTDOWN,
		.code = BTN_0,
		.desc = "KEY_SHUTDOWN",
		.active_low = 1,
                .type = EV_SW,
	},	{
		.gpio = MGB100_KEY_BACKUP,
		.code = BTN_1,
		.desc = "KEY_BACKUP",
		.active_low = 1,
                .type = EV_SW,
	},
};

static struct gpio_keys_platform_data rdc321x_gpio_btn_data = {
	.buttons = rdc321x_gpio_btn,
	.nbuttons = ARRAY_SIZE(rdc321x_gpio_btn),
};

static struct platform_device rdc321x_button = {
	.name = "gpio-keys",
	.id = -1,
	.dev = {
		.platform_data = &rdc321x_gpio_btn_data,
	}
};





static struct i2c_gpio_platform_data mgb100_i2c_gpio_data = {
	.sda_pin		= 16,
	.scl_pin		= 17,
};

static struct platform_device mgb100_i2c_gpio = {
	.name			= "i2c-gpio",
	.id			= 0,
	.dev	 = {
		.platform_data	= &mgb100_i2c_gpio_data,
	},
};

static struct i2c_board_info mgb100_i2c_devices[] = {
    {
        I2C_BOARD_INFO("pcf8563", 0x51),
    },
};

static struct mtd_partition mgb100_nor_partitions[] = {
	{
		.name		= "kernel",
		.size		= 0x100000,
		.offset		= 0x0,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "rootfs",
//		.size		= 0x280000,
		.size		= 0x2E0000,

		.offset		= 0x100000,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , 
//{
//		.name		= "var (jffs2)",
//		.size		= 0x60000,
//		.offset		= 0x380000,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
//	} ,

 {
		.name		= "Redboot (low part)",
		.size		= 0x18000,
		.offset		= 0x003e0000,
		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "MAC and device ID",
		.size		= 0x02000,
		.offset		= 0x003f8000,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "Redboot (high part)",
		.size		= 0x06000,
		.offset		= 0x003fa000,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "Redboot(full)",
		.size		= 0x20000,
		.offset		= 0x03e0000,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "linux",
		.size		= 0x003e0000,
		.offset		= 0,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "fullflash",
		.size		= 0x00400000,
		.offset		= 0,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} , {
		.name		= "rootfs-full",
//		.size		= 0x280000,
		.size		= 0x2E0000,
		.offset		= 0x100000,
//		.mask_flags	= MTD_WRITEABLE  /* force read-only */
	} 

};

static struct physmap_flash_data mgb100_nor_flash_data[] = {
	{
		.width		= 2,	/* bankwidth in bytes */
		.parts		= mgb100_nor_partitions,
		.nr_parts	= ARRAY_SIZE(mgb100_nor_partitions)
	}
};

static struct resource mgb100_nor_resource = {
	.start	= 0xffc00000,
	.end	= 0xffffffff,
	.flags	= IORESOURCE_MEM,
};

static struct platform_device mgb100_nor = {
	.name	= "physmap-flash",
	.id	= -1,
	.dev	= {
		.platform_data = mgb100_nor_flash_data,
	},
	.resource = &mgb100_nor_resource,
	.num_resources = 1,
};

static struct platform_device *mgb100_devices[] __initdata = {
	&mgb100_leds,
	&mgb100_i2c_gpio,
        &mgb100_nor,
	&rdc321x_button,

};

static int __init mgb100_devices_setup(void)
{
	i2c_register_board_info(0, mgb100_i2c_devices,
				ARRAY_SIZE(mgb100_i2c_devices));
	platform_device_register_simple("GPIODEV", 0, &gpiodev_resource, 1);
	platform_add_devices(mgb100_devices, ARRAY_SIZE(mgb100_devices));
	return 0;
}
__initcall(mgb100_devices_setup);
