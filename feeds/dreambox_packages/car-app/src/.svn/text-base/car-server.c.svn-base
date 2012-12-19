#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

#include<signal.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SERVER_PORT    6666
#define LENGTH_OF_LISTEN_QUEUE 1000
#define BUFFER_SIZE 1024
#define CMD_MAX_SIZE 2

int write_io(char cmd)
{
	int fd;
  	fd = open("/dev/car0", 0);
	if (fd < 0) {
		fd = open("/dev/car", 0);
	}
	if (fd < 0) {
		perror("open device car");
//	exit(1);
	}
	 ioctl(fd,cmd,1);
	 close(fd);
}

int main(int argc, char **argv)
{
    //设置一个socket地址结构server_addr,代表服务器internet地址, 端口
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr)); //把一段内存区的内容全部设置为0
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    //创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }
    else
        printf("Create Socket OK! \n");

    {
        int opt =1;
        setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    }

    //把socket和socket地址结构联系起来
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed!", SERVER_PORT);
        exit(1);
    }
    else
        printf("Server Bind Port OK! \n");
    //server_socket用于监听
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
    {
        printf("Server Listen Failed!");
        exit(1);
    }
    else
        printf("Server Listening ...\n");
    while (1) //服务器端要一直运行
    {
	signal(SIGPIPE, SIG_IGN);
        //定义客户端的socket地址结构client_addr
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

        //接受一个到server_socket代表的socket的一个连接
        //如果没有连接请求,就等待到有连接请求--这是accept函数的特性
        //accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
        //new_server_socket代表了服务器和客户端之间的一个通信通道
        //accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中
	
        printf("Wait for Client connect...\n");
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }
        else
            printf("Client connected from:%s\n",inet_ntoa(client_addr.sin_addr));
        char buffer[BUFFER_SIZE];
	
while (1)
{
        bzero(buffer, BUFFER_SIZE);
        length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
        if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }
        char cmd[CMD_MAX_SIZE+1];
        bzero(cmd, CMD_MAX_SIZE+1);
        strncpy(cmd, buffer, strlen(buffer)>CMD_MAX_SIZE?CMD_MAX_SIZE:strlen(buffer));

        //打印客户端命令
        printf("Recieved CMD dec:%d\n",cmd[0]);
	printf("Recieved CMD char:%c\n",cmd[0]);
	write_io(cmd[0]);
        //向客户端发送返回信息0，以说明命令执行完成。
        char return_ok='0';

        if(send(new_server_socket,&return_ok,sizeof(return_ok),0)<0)
        {
            printf("Send OK Failed.\n");
	    printf("Maybe Client is disconnected..\n");
            break;
        }
        else
            printf("Command return OK finished.\n");
}
#if 0
        FILE * fp = fopen(cmd,"r");
        if(NULL == fp )
        {
            printf("File:\t%s Not Found\n", cmd);
        }
        else
        {
            bzero(buffer, BUFFER_SIZE);
            int file_block_length = 0;
//            while( (file_block_length = read(fp,buffer,BUFFER_SIZE))>0)
            while( (file_block_length = fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0)
            {
                printf("file_block_length = %d\n",file_block_length);
                //发送buffer中的字符串到new_server_socket,实际是给客户端
                if(send(new_server_socket,buffer,file_block_length,0)<0)
                {
                    printf("Send File:\t%s Failed\n", cmd);
                    break;
                }
                bzero(buffer, BUFFER_SIZE);
            }
//            close(fp);
            fclose(fp);
            printf("File:\t%s Transfer Finished\n",cmd);
        }
#endif
        //关闭与客户端的连接
        close(new_server_socket);
    }
    //关闭监听用的socket
    close(server_socket);
    
    return 0;
}
