#include "stdio.h"
#include "sys/types.h"
#include "sys/ioctl.h"
#include "stdlib.h"
#include "termios.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "sys/time.h"

main()
{
    int fd;
    unsigned char buf[2];
    float result;

    if ((fd=open("/dev/car",O_RDWR | O_NDELAY | O_NOCTTY)) < 0)
    {
        printf("Open Device DS18B20 failed.\r\n");
        exit(1);
    }
    else
    {
        printf("Open Device DS18B20 successed.\r\n");
        while(1)
        {
            read(fd, buf, 1);
            result = (float)buf[0];
            result /= 16;
            result += ((float)buf[1] * 16);
     
            printf("%.1f `C\r\n", result);
            sleep(1);
        }
        close(fd);
    }
}