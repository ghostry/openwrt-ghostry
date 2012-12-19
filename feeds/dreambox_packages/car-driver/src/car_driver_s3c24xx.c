      
 /*********************************************
 *
 *    Car-Driver for S3c24xx
 *
 *    By Lintel (lintel.huang@gmail.com) 2005-2011
 *
 * 	GDKM-Embedded Lab
 *
 **********************************************/
 
#include <linux/init.h>  
#include <linux/miscdevice.h>
#include <linux/delay.h>
//#include <linux/devfs_fs_kernel.h>
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
#include <mach/regs-gpio.h>
#include <mach/hardware.h>

#include <linux/poll.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

#include <asm/uaccess.h>  

#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>

//#include <plat/gpio-cfg.h>

#define DEVICE_NAME "car"
#define DERVER_VERSION "1.01b"

//L298N连接的GPIO
#define MOTOR_LEFT_ENA 	S3C2410_GPF(0)
#define MOTOR_LEFT_ENB	S3C2410_GPF(1)

#define MOTOR_RIGHT_ENA	S3C2410_GPF(2)
#define MOTOR_RIGHT_ENB	S3C2410_GPF(3)

//四相步进电机连接的GPIO
#define STEP_MOTOR_A 	S3C2410_GPF(4)
#define STEP_MOTOR_B 	S3C2410_GPF(5)
#define STEP_MOTOR_C 	S3C2410_GPF(6)
#define STEP_MOTOR_D 	S3C2410_GPG(0)

//轻触开关连接的GPIO
#define SWITCH_LEFT	S3C2410_GPG(6)
#define SWITCH_RIGHT	S3C2410_GPG(5)

//外部设备电源开关连接的GPIO
#define POWER_SWITCH	S3C2410_GPG(7)

//红外线避障连接的GPIO
#define LASER_BARRIER	S3C2410_GPG(1)

//蜂鸣器连接的GPIO
#define SPEAKER	S3C2410_GPB(0)

//红外线人体检测连接的GPIO
#define HUMAN_SENSOR	S3C2410_GPG(3)

//超声波测距传感器链接的GPIO
#define ULTRASCHALL_SENSOR_TRING	S3C2410_GPG(10)
#define ULTRASCHALL_SENSOR_ECHO		S3C2410_GPG(11)

//循迹模块连接的GPIO
#define LASER_TRACES_LEFT	S3C2410_GPE(11)
#define LASER_TRACES_MIDDLE	S3C2410_GPG(6)
#define LASER_TRACES_RIGHT	S3C2410_GPE(13)

//温度传感器DS18B20连接的GPIO引脚
#define DS18B20_PIN   S3C2410_GPG(9)
//ds18b20命令
#define  DS18B20_SEARCH		0x00F0
#define  DS18B20_READ_ROM	0x0033
#define  DS18B20_SKIP_ROM	0x00CC
#define  DS18B20_CONVERY	0x0044  
#define  DS18B20_WRITE		0x004E
#define  DS18B20_READ		0x00BE  
#define  DS18B20_BIT_9		0x001F  
#define  DS18B20_BIT_10		0x003F  
#define  DS18B20_BIT_11		0x005F  
#define  DS18B20_BIT_12		0x007F  

//GPIO内部上拉电阻
#define S3C2410_GPIO_PULLUP 0
#define S3C2410_GPIO_PULL_NONE 1

#define GPIO_HIGH 1
#define GPIO_LOW 0

//#define debug 1


typedef unsigned char BYTE;
static BYTE data[2];
// DS18B20复位函数
BYTE DS18b20_reset(void)
{
    // 配置GPIOB0输出模式
    s3c2410_gpio_cfgpin(DS18B20_PIN, S3C2410_GPIO_OUTPUT);
   
    // 向18B20发送一个上升沿，并保持高电平状态约100微秒
    s3c2410_gpio_setpin(DS18B20_PIN,GPIO_HIGH);
    udelay(100);
   
    // 向18B20发送一个下降沿，并保持低电平状态约600微秒
    s3c2410_gpio_setpin(DS18B20_PIN,GPIO_LOW);
    udelay(600);
   
    // 向18B20发送一个上升沿，此时可释放DS18B20总线
    s3c2410_gpio_setpin(DS18B20_PIN, GPIO_HIGH);
    udelay(100);
    
    // 以上动作是给DS18B20一个复位脉冲
    // 通过再次配置GPIOB1引脚成输入状态，可以检测到DS18B20是否复位成功
    s3c2410_gpio_cfgpin(DS18B20_PIN,S3C2410_GPIO_INPUT);
   
    // 若总线在释放后总线状态为高电平，则复位失败
    if(s3c2410_gpio_getpin(DS18B20_PIN))
    return 1;
    else
    return 0;
} 

//步进电机励磁表
static  unsigned int step_motor_right_table[][4] =
{
    /* A B C D  四相八拍 正向*/
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1},
};

static  unsigned int step_motor_left_table[][4] =
{
    /* A B C D  四相八拍 反向*/
    {1,0,0,0},
    {1,0,0,1},
    {0,0,0,1},
    {0,0,1,1},
    {0,0,1,0},
    {0,1,1,0},
    {0,1,0,0},
    {1,1,0,0},
};

/*GPIO设备表*/
static unsigned int motor_table [] =
{
    MOTOR_LEFT_ENA,
    MOTOR_LEFT_ENB,
    MOTOR_RIGHT_ENA,
    MOTOR_RIGHT_ENB
};

static unsigned int step_motor_table [] =
{
    STEP_MOTOR_A,
    STEP_MOTOR_B,
    STEP_MOTOR_C,
    STEP_MOTOR_D
};

static unsigned int laser_traces_table[] =
{
    LASER_TRACES_LEFT,
    LASER_TRACES_MIDDLE,
    LASER_TRACES_RIGHT
};

static unsigned int other_sensor_input_table[] =
{
    SWITCH_LEFT,
    SWITCH_RIGHT,

    LASER_BARRIER,

    HUMAN_SENSOR,

    ULTRASCHALL_SENSOR_ECHO

};

static unsigned int other_sensor_output_table[] =
{
    ULTRASCHALL_SENSOR_TRING,

    SPEAKER,

    POWER_SWITCH
};



/*
初始化GPIO接口
 */
static int car_devices_init(void)
{
    int i,error=0;

    printk("Initializing Temperature Sensor(DS18B20)...");
    if(DS18b20_reset())
     printk("failed!\n");
    else
     printk("success!\n"); 
	
//初始化所有电机连接的GPIO
    printk("Initializing Car motors...");
    for (i = 0; i < 4; i++)
    {

        if(gpio_is_valid(motor_table[i])==-EINVAL)
        {
            printk("ERROR,GPIO %d used by other devices !\n",motor_table[i]);
            error++;
            break;
        }
        if(gpio_is_valid(step_motor_table[i])==-EINVAL)
        {
            printk("ERROR,GPIO %d used by other devices !\n",step_motor_table[i]);
            error++;
            break;
        }
        //上拉GPIO
        s3c2410_gpio_pullup(motor_table[i],S3C2410_GPIO_PULLUP);
//        s3c2410_gpio_pullup(step_motor_table[i], S3C2410_GPIO_PULL_NONE);
//	msleep(1);
	s3c2410_gpio_pullup(step_motor_table[i],S3C2410_GPIO_PULLUP);
	
        //设置为输出
        s3c2410_gpio_cfgpin(motor_table[i], S3C2410_GPIO_OUTPUT);
//	msleep(1);
        s3c2410_gpio_cfgpin(step_motor_table[i],S3C2410_GPIO_OUTPUT);
        //设置默认值为低电平
        gpio_set_value(motor_table[i],0);
//	msleep(1);
        gpio_set_value(step_motor_table[i],0);  
    }
    if(error)
    {
        printk("Fail!\n");
        return -EINVAL;
    }
    else
    {
        printk("OK!\n");
        error=0;
    }

    /*初始化循迹模块连接的GPIO*/
    printk("Initializing laser traces...");
    for (i = 0; i < 3; i++)
    {
        if(gpio_is_valid(laser_traces_table[i])==-EINVAL)
        {
            printk("\nERROR,GPIO %d used by other devices !\n",laser_traces_table[i]);
            error++;
            break;
        }

        //设置为输出
        s3c2410_gpio_cfgpin(laser_traces_table[i], S3C2410_GPIO_INPUT);
        //下拉GPIO
        s3c2410_gpio_pullup(laser_traces_table[i], S3C2410_GPIO_PULL_NONE);
    }
    if(error)
    {
        printk("Fail!\n");
        return -EINVAL;
    }
    else
    {
        printk("OK!\n");
        error=0;
    }


    /*初始化其他输入设备连接的GPIO*/
    printk("Initializing other input sensor...");
    for (i = 0; i < 5; i++)
    {
        if(gpio_is_valid(other_sensor_input_table[i])==-EINVAL)
        {
            printk("\nERROR,GPIO %d used by other devices !\n",other_sensor_input_table[i]);
            error++;
            break;
        }

        //设置为输出
        s3c2410_gpio_cfgpin(other_sensor_input_table[i], S3C2410_GPIO_INPUT);
        //下拉GPIO
        s3c2410_gpio_pullup(other_sensor_input_table[i], S3C2410_GPIO_PULL_NONE);
    }
    if(error)
    {
        printk("Fail!\n");
        return -EINVAL;
    }
    else
    {
        printk("OK!\n");
        error=0;
    }

    /*初始化其他输出设备的GPIO*/

    printk("Initializing other output devices...");
    for (i = 0; i < 3; i++)
    {
        if(gpio_is_valid(other_sensor_output_table[i])==-EINVAL)
        {
            printk("\nERROR,GPIO %d used by other devices !\n",other_sensor_output_table[i]);
            error++;
            break;
        }
        //设置为输出
        s3c2410_gpio_cfgpin(other_sensor_output_table[i], S3C2410_GPIO_OUTPUT);
        //下拉GPIO
        s3c2410_gpio_pullup(other_sensor_output_table[i], S3C2410_GPIO_PULLUP);
    }
    if(error)
    {
        printk("Fail!\n");
        return -EINVAL;
    }
    else
    {
        printk("OK!\n");
        error=0;
    }


    return error;
};





/*
 *
 * 函数名称:set_car_motor_status
 * 入口参数：无符号整数
 * 	8 前进
 *  4左	 5停	6右
 * 	2后退
 * 返回值:无
 *
 */

static void set_motor_status(unsigned int status)
{
    switch(status)
    {
        //电机停
    case 5:
        gpio_set_value(MOTOR_LEFT_ENA,0);
        gpio_set_value(MOTOR_LEFT_ENB,0);
        gpio_set_value(MOTOR_RIGHT_ENA,0);
        gpio_set_value(MOTOR_RIGHT_ENB,0);
        break;
        //电机向前
    case 8:
        gpio_set_value(MOTOR_LEFT_ENA,1);
        gpio_set_value(MOTOR_LEFT_ENB,0);
        gpio_set_value(MOTOR_RIGHT_ENA,1);
        gpio_set_value(MOTOR_RIGHT_ENB,0);
        break;
        //电机向后
    case 2:
        gpio_set_value(MOTOR_LEFT_ENA,0);
        gpio_set_value(MOTOR_LEFT_ENB,1);
        gpio_set_value(MOTOR_RIGHT_ENA,0);
        gpio_set_value(MOTOR_RIGHT_ENB,1);
        break;
        //电机向左
    case 4:
        gpio_set_value(MOTOR_LEFT_ENA,0);
        gpio_set_value(MOTOR_LEFT_ENB,1);
        gpio_set_value(MOTOR_RIGHT_ENA,1);
        gpio_set_value(MOTOR_RIGHT_ENB,0);
        break;
        //电机向右
    case 6:
        gpio_set_value(MOTOR_LEFT_ENA,1);
        gpio_set_value(MOTOR_LEFT_ENB,0);
        gpio_set_value(MOTOR_RIGHT_ENA,0);
        gpio_set_value(MOTOR_RIGHT_ENB,1);
        break;
    }
};


/*-----------------------------------------------------------
 *
 * 函数名称:set_car_step_motor_status
 * 功能:控制步进电机的转动方向，每次步进角度为5.625度
 * 入口参数：无符号整数
 *
 *  4左	  	6右
 *
 * 返回值:无
 *-----------------------------------------------------------
 */
#define CONUT  4
static void set_step_motor(unsigned int status)
{
    int i,j,loop;
    switch(status)
    {
      
    case 4:
        //步进电机内部电机正转一圈
        for(loop=0;loop<CONUT;loop++)
        {
        for (i=0; i<sizeof(step_motor_right_table)/sizeof(step_motor_right_table[0]);i++)
        {
            for(j=0;j<sizeof(step_motor_table)/sizeof(step_motor_table[0]); j++)
            {
                gpio_set_value(step_motor_table[j],step_motor_right_table[i][j]);
//		printk("Set GPIO %d to %d \n",step_motor_table[j],step_motor_right_table[i][j]);
            }
//           printk("\n");
            msleep(2);
        }
	}
 //        printk("\n");
        break;
    case 6:
        for(loop=0;loop<CONUT;loop++)
        {
        //步进电机内部电机反转一圈
        for (i=0; i<sizeof(step_motor_right_table)/sizeof(step_motor_right_table[0]);i++)
        {
            for(j=0;j<sizeof(step_motor_table)/sizeof(step_motor_table[0]); j++)
            {
                gpio_set_value(step_motor_table[j],step_motor_left_table[i][j]);
//		printk("Set GPIO %d to %d \n",step_motor_table[j],step_motor_left_table[i][j]);
            }
//            printk("\n");
            msleep(2);
        }
	}
        break;
    }
}

void DS18b20_write_byte (BYTE byte)
{
    BYTE i;
    // 配置GPIOB1为输出模式
    s3c2410_gpio_cfgpin(DS18B20_PIN,S3C2410_GPIO_OUTPUT);

    // 写“1”时隙：
    //     保持总线在低电平1微秒到15微秒之间
    //     然后再保持总线在高电平15微秒到60微秒之间
    //     理想状态: 1微秒的低电平然后跳变再保持60微秒的高电平
    //
    // 写“0”时隙：
    //     保持总线在低电平15微秒到60微秒之间
    //     然后再保持总线在高电平1微秒到15微秒之间
    //     理想状态: 60微秒的低电平然后跳变再保持1微秒的高电平
    for (i = 0; i < 8; i++)
    {
        s3c2410_gpio_setpin(DS18B20_PIN,GPIO_LOW); udelay(1);
        if(byte & GPIO_HIGH)
        {
             // 若byte变量的D0位是1，则需向总线上写“1”
             // 根据写“1”时隙规则，电平在此处翻转为高
             s3c2410_gpio_setpin(DS18B20_PIN, GPIO_HIGH);
        }
        else
        {
             // 若byte变量的D0位是0，则需向总线上写“0”
             // 根据写“0”时隙规则，电平在保持为低
             // s3c2410_gpio_setpin(DS18B20_PIN, LOW);
        }
        // 电平状态保持60微秒
        udelay(60);

        s3c2410_gpio_setpin(DS18B20_PIN,GPIO_HIGH);
        udelay(15);
	
        byte >>= 1;
    }
    s3c2410_gpio_setpin(DS18B20_PIN, GPIO_HIGH);
}

/*DS18b20 读取函数 */
BYTE DS18b20_read_byte (void)
{
    BYTE i = 0;
    BYTE byte = 0;
    // 读“1”时隙：
    //     若总线状态保持在低电平状态1微秒到15微秒之间
    //     然后跳变到高电平状态且保持在15微秒到60微秒之间
    //      就认为从DS18B20读到一个“1”信号
    //     理想情况: 1微秒的低电平然后跳变再保持60微秒的高电平
    //
    // 读“0”时隙：
    //     若总线状态保持在低电平状态15微秒到30微秒之间
    //     然后跳变到高电平状态且保持在15微秒到60微秒之间
    //     就认为从DS18B20读到一个“0”信号
    //     理想情况: 15微秒的低电平然后跳变再保持46微秒的高电平
    for (i = 0; i < 8; i++)
    {
        s3c2410_gpio_cfgpin(DS18B20_PIN, S3C2410_GPIO_OUTPUT);
        s3c2410_gpio_setpin(DS18B20_PIN,GPIO_LOW);

        udelay(1);
        byte >>= 1;

        s3c2410_gpio_setpin(DS18B20_PIN, GPIO_HIGH);
        s3c2410_gpio_cfgpin(DS18B20_PIN,S3C2410_GPIO_INPUT);

        // 若总线在我们设它为低电平之后若1微秒之内变为高
        // 则认为从DS18B20处收到一个“1”信号
        // 因此把byte的D7为置“1”
        if (s3c2410_gpio_getpin(DS18B20_PIN)) byte |= 0x80;
        udelay(60);
    }
    return byte;      
}

void DS18b20_proc(void)        
{
    while(DS18b20_reset());
   
    udelay(120);
   
    DS18b20_write_byte(DS18B20_SKIP_ROM);
    DS18b20_write_byte(DS18B20_CONVERY);
   
    udelay(5);
   
    while(DS18b20_reset());
    udelay(200);
   
    DS18b20_write_byte(DS18B20_SKIP_ROM);
    DS18b20_write_byte(DS18B20_READ);
   
    data[0] = DS18b20_read_byte();
    data[1] = DS18b20_read_byte();
} 

static ssize_t s3c2440_18b20_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
    DS18b20_proc();

    buf[0] = data[0];
    buf[1] = data[1];
   
    return 1;
}

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
    printk("cmd:char=%c dec=%d\n",cmd,cmd);
#endif
    long ret=0;
    switch(cmd)
    {
    case '0':
    case 0:
        set_motor_status(5);
        break;

    case '1':
    case 1:
        set_motor_status(4);
        break;

    case '2':
    case 2:
        set_motor_status(2);
        break;

    case '3':
    case 3:
        set_motor_status(6);
        break;

    case '5':
    case 5:
        set_motor_status(8);
        break;

    case '4':
    case 4:
        set_step_motor(4);
        break;
    case '6':
    case 6:
        set_step_motor(6);
        break;
    case '7':
    case 7:
        ret=!gpio_get_value(SWITCH_LEFT);
        break;
    case '8':
    case 8:
	ret=!gpio_get_value(LASER_BARRIER);
        break;
    case '9':
    case 9:
        ret=!gpio_get_value(SWITCH_RIGHT);
        break;
    case 'f':
        gpio_set_value(SPEAKER,!gpio_get_value(SPEAKER));
	ret=gpio_get_value(SPEAKER)==1? printk(DEVICE_NAME"\tSPEAKER ON.\n"):printk(DEVICE_NAME"\tSPEAKER OFF.\n") ;
	ret=gpio_get_value(POWER_SWITCH);
        break;
    case 'p':
        gpio_set_value(POWER_SWITCH,!gpio_get_value(POWER_SWITCH));
	gpio_get_value(POWER_SWITCH)==0? printk(DEVICE_NAME"\tSensor PowerON.\n"):printk(DEVICE_NAME"\tSensor PowerOFF.\n") ;
	ret=gpio_get_value(POWER_SWITCH);
        break;
    case 'h':
        ret=!gpio_get_value(HUMAN_SENSOR);
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

static struct file_operations dev_fops =
{
    .owner			= THIS_MODULE,
    .unlocked_ioctl	= car_ioctl,
//	.release =   car_laser_close,
	.read    =   s3c2440_18b20_read,
//    .open	= car_devices_init,
};

static struct miscdevice misc =
{
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &dev_fops,
};

static int __init dev_init(void)
{
    int ret;
    printk ("WiFi Car-Driver %s \tBy Lintel 2011\n",DERVER_VERSION);
    car_devices_init();

//	car_motor_run();
    ret = misc_register(&misc);
    if (!ret)
        printk (DEVICE_NAME"\tinitialized\n");
    else
        printk (DEVICE_NAME"\tinitialize error !\n");
    return ret;
}

static void __exit dev_exit(void)
{
    if(!misc_deregister(&misc))
        printk (DEVICE_NAME"\tunloaded.\n");
    else
        printk (DEVICE_NAME"\tunload error!\n");
}

module_init(dev_init);
module_exit(dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lintel");
MODULE_DESCRIPTION("S3C2410/S3C2440 WiFi-Car Driver");
