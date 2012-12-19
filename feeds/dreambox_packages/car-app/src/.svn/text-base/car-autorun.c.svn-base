#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <curses.h>
#define debug 1
#define AREC 128

unsigned int count=AREC;
int fd;

unsigned char buf[2];
float result;

//ioctl(fd,cmd);
void msleep(int s)
{
    usleep(1000*s);
}

void sensor_power_on(void)
{
      while(ioctl(fd,'p'));
}
//步进电机左转
unsigned int step_motor_left(void)
{
    int i;
    printf("step motor turn left.\n");
    for(i=0; i<AREC; i++)
    {
        ioctl (fd,'4');
	count--;
    }
}

//步进电机右转
unsigned int step_motor_right(void)
{
    int i;
    printf("step motor turn right.\n");
    for(i=0; i<AREC; i++)
    {
        ioctl (fd,'6');
	count++;
    }
}

unsigned int step_motor_reset(void)
{
    int i;
    printf("step motor reset.\n");
      if (count==0)
      step_motor_right();
      else
      step_motor_left();
}

void get_temperature(void)
{
            read(fd, buf, 1);
            result = (float)buf[0];
            result /= 16;
            result += ((float)buf[1] * 16); 
            printf("Current temperature %.1f `C\r\n", result);
	    msleep(5);
}

int main(void)
{    
    char cmd='3';
    int ret;

    int mark=0;
    int i;
    char rec='1';


    //打开设备
    fd = open("/dev/car0", 0);
    if (fd < 0)
    {
        fd = open("/dev/car", 0);
    }
    if (fd < 0)
    {
        perror("open device car");
        exit(1);
    }
    //打开传感器电源
    sensor_power_on();
    //开始无限循环
    while (1)
    {
        if (ioctl(fd,'8')!=1)
        {
            ioctl(fd,'5');
            mark=0;
        }
        else if (ioctl(fd,'8')==1)
        {
            ioctl(fd,'0'); //停下
            //左转
	    step_motor_left();

            if (ioctl(fd,'8')==1)
            {
                cmd='3';
            }

            //复位
            step_motor_reset();

            //右转
            step_motor_right();
            if (ioctl(fd,'8')==1)
            {
                cmd='1';
            }
            //复位
           step_motor_reset();

            ioctl(fd,cmd);
            msleep(400);
            sleep(1);
            ioctl(fd,'5');
        }
        else if (ioctl(fd,'7')==1)
        {
            ioctl (fd,'3'); //右转

            msleep(400);
            sleep(1);
            ioctl(fd,'5');
        }
        else if (ioctl(fd,'9')==1)
        {
            ioctl (fd,'1'); //左转
            msleep(400);
            sleep(1);

        }
        else
        {
            ioctl (fd,'5');
        }
	get_temperature();        
       msleep(10); //暂停10ms

    };
    return 0;
}

