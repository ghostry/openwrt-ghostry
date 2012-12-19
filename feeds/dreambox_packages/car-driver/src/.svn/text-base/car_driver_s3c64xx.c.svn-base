/*********************************************
 * 
 *    Car-Driver for S3c64xx
 * 
 *    By Lintel (lintel.huang@gmail.com) 2005-2011  
 * 
 * 	GDKM-Embedded Lab
 * 
 **********************************************/


#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <asm/irq.h>
//#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>

#include <mach/map.h>
#include <mach/regs-clock.h>
#include <mach/regs-gpio.h>
#include <mach/gpio.h>

//#include <linux/gpio.h>

#include <plat/gpio-cfg.h>
#include <mach/gpio-bank-e.h>
#include <mach/gpio-bank-m.h>

#define DEVICE_NAME "car"

#define MOTOR_LEFT_ENA 	S3C64XX_GPE(1)
#define MOTOR_LEFT_ENB	S3C64XX_GPE(2)

#define MOTOR_RIGHT_ENA	S3C64XX_GPE(3)
#define MOTOR_RIGHT_ENB	S3C64XX_GPE(4)

#define LASER_BARRIER_LEFT	S3C64XX_GPM(0)
#define LASER_BARRIER_RIGHT	S3C64XX_GPM(1)

#define LASER_TRACES_LEFT	S3C64XX_GPM(2)
#define LASER_TRACES_MIDDLE	S3C64XX_GPM(3)
#define LASER_TRACES_RIGHT	S3C64XX_GPM(4)

//#define debug 1

static unsigned long motor_table [] = {
	MOTOR_LEFT_ENA,
	MOTOR_LEFT_ENB,
	MOTOR_RIGHT_ENA,
	MOTOR_RIGHT_ENB
};


static unsigned long laser_table [] = {
	LASER_BARRIER_LEFT,
	LASER_BARRIER_RIGHT,
	LASER_TRACES_LEFT,
	LASER_TRACES_MIDDLE,
	LASER_TRACES_RIGHT
};

static int car_motor_init(void)
{
  int ret=0,i;
  	for (i = 0; i < 4; i++) 
	{
	    
		if(gpio_is_valid(motor_table[i])==-EINVAL)
		{
		  printk("ERROR,GPIO used by other devices ! \n");
		  break;
		}
		//上拉GPIO
	  s3c_gpio_setpull(motor_table[i], S3C_GPIO_PULL_UP);
	  //设置为输出
	  s3c_gpio_cfgpin(motor_table[i], S3C_GPIO_OUTPUT);
	  //设置默认值为低电平
	  gpio_set_value(motor_table[i],0);
	 
	}
	
  return ret;
};

static int car_laser_init(void)
{
  int ret=0,i;
  	for (i = 0; i < 5; i++) 
	{
	    
		if(gpio_is_valid(laser_table[i])==-EINVAL)
		{
		  printk("ERROR,GPIO used by other devices ! \n");
		  break;
		}

	  //设置为输出
	  s3c_gpio_cfgpin(laser_table[i], S3C_GPIO_INPUT);
	  //下拉GPIO
	  s3c_gpio_setpull(laser_table[i], S3C_GPIO_PULL_NONE);
	}
	
  return ret;
};

static void car_motor_status(void)
{
	printk("MOTOR_LEFT_ENA=%d\nMOTOR_LEFT_ENB=%d\nMOTOR_RIGHT_ENA=%d\nMOTOR_RIGHT_ENB=%d\n",
	gpio_get_value(MOTOR_LEFT_ENA),
	gpio_get_value(MOTOR_LEFT_ENB),
	gpio_get_value(MOTOR_RIGHT_ENA),
	gpio_get_value(MOTOR_RIGHT_ENB));
	
};

static void car_motor_run(void)
{
  	gpio_set_value(MOTOR_LEFT_ENA,1);
	gpio_set_value(MOTOR_RIGHT_ENA,1);
};


static void car_motor_stop(void)
{
#if debug
	 car_motor_status();
#endif
  	gpio_set_value(MOTOR_LEFT_ENA,0);
  	gpio_set_value(MOTOR_LEFT_ENB,0);
	gpio_set_value(MOTOR_RIGHT_ENA,0);
	gpio_set_value(MOTOR_RIGHT_ENB,0);
	
};


static void car_motor_back(void)
{
  	gpio_set_value(MOTOR_LEFT_ENB,1);
	gpio_set_value(MOTOR_RIGHT_ENB,1);
};

static void car_motor_left(void)
{
  	gpio_set_value(MOTOR_LEFT_ENB,1);
	gpio_set_value(MOTOR_RIGHT_ENA,1);
};

static void car_motor_right(void)
{
 	gpio_set_value(MOTOR_LEFT_ENA,1);
	gpio_set_value(MOTOR_RIGHT_ENB,1);
};



#if 0
static int car_laser_read(struct file *filp, char __user *buff, size_t count, loff_t *offp)
{
    unsigned long err;
    gpio_get_value(unsigned gpio);


    return err ? -EFAULT : min(sizeof(key_values), count);
}
#endif

static long car_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
#if debug
	printk("cmd=%c\n",cmd);
#endif
	long ret=0;
	switch(cmd)
	{
	  case '0':	case 0:
	  car_motor_stop();
	  break;
	  
	  case '1':	case 1:
	  car_motor_stop();
	  car_motor_left();
	  break;
	  
	  case '2':	case 2:
	  car_motor_stop();
	  car_motor_back();
	  break;
	  
	  case '3':	case 3:
	  car_motor_stop();
	  car_motor_right();
	  break;

 	  case '5':	case 5:
	  car_motor_stop();
	  car_motor_run();  
	  break;
	  
	  case '4':	case 4:	
	  ret=!gpio_get_value(LASER_BARRIER_LEFT);
	  break;
	    
	  case '6':	case 6:
	  ret=!gpio_get_value(LASER_BARRIER_RIGHT);
	  break;
	  
	  case '7':	case 7:
	  ret=gpio_get_value(LASER_TRACES_LEFT);
	  break;
	  
	  case '8':	case 8:
	  ret=gpio_get_value(LASER_TRACES_MIDDLE);
	  break; 
	  
	  case '9':	case 9:
	  ret=gpio_get_value(LASER_TRACES_RIGHT);
	  break;

#if 0
		tmp = readl(S3C64XX_GPKDAT);
		tmp &= ~(1 << (4 + arg));
		tmp |= ( (!cmd) << (4 + arg) );
		writel(tmp, S3C64XX_GPKDAT);
#endif
		//printk (DEVICE_NAME": %d %d\n", arg, cmd);
//		return 0;
	default:
		return -EINVAL;
	}
	return ret;
}

static struct file_operations dev_fops = {
	.owner			= THIS_MODULE,
	.unlocked_ioctl	= car_ioctl,
//	.release =   car_laser_close, 
//	.read    =   car_laser_read,
};

static struct miscdevice misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &dev_fops,
};

static int __init dev_init(void)
{
	int ret;
#if 0
	{
		unsigned tmp;
		tmp = readl(S3C64XX_GPKCON);
		tmp = (tmp & ~(0xffffU<<16))|(0x1111U<<16);
		writel(tmp, S3C64XX_GPKCON);
		
		tmp = readl(S3C64XX_GPKDAT);
		tmp |= (0xF << 4);
		writel(tmp, S3C64XX_GPKDAT);
	}
#endif
	car_motor_init();
	car_laser_init();
//	car_motor_run();
	ret = misc_register(&misc);

	printk (DEVICE_NAME"\tinitialized\n");

	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc);
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lintel.");
