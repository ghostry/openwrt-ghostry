/*
 * Car Test Program
 * 
 * by Lintel 2011
 * 
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <curses.h>
#include <termios.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	int cmd;
	int ret;
	int fd;

	unsigned char buf[2];
	float result;
#if 0
	if (argc != 3 || sscanf(argv[1], "%d", &led_no) != 1 || sscanf(argv[2],"%d", &on) != 1 ||
			on < 0 || on > 1 || led_no < 0 || led_no > 3) {
		fprintf(stderr, "Usage: leds led_no 0|1\n");
		exit(1);
	}

	fd = open("/dev/leds0", 0);
	if (fd < 0) {
		fd = open("/dev/leds", 0);
	}
	if (fd < 0) {
		perror("open device leds");
		exit(1);
	}
#endif
	fd = open("/dev/car0", 0);
	if (fd < 0) {
		fd = open("/dev/car", 0);
	}
	if (fd < 0) {
		perror("open device car");
		exit(1);
	}
	  
	 printf("input cmds:\n");
	while (1)
	{
	 scanf("%c",&cmd);	
	 if (cmd=='q')
	   break;
	 else if(cmd=='t')
	 {
	    read(fd, buf, 1);
            result = (float)buf[0];
            result /= 16;
            result += ((float)buf[1] * 16); 
            printf("Current temperature %.1f `C\r\n", result);
	 }
	 else
	 {
//	 printf("inputed:%d \n",cmd);	 
	ret=ioctl(fd,cmd);
	 printf("ret=%d\n",ret);
	 }
	};
	
	
	close(fd);

	return 0;
}

