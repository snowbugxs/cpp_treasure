/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年4月23日, 下午3:38
 */

#include <unistd.h>
#include <sys/types.h>         /* basic system data types */
#include <sys/socket.h>        /* basic socket definitions */
#include <netinet/in.h>        /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>         /* inet(3) functions */
#include <netdb.h>             /* gethostbyname function */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <cstdlib>

using namespace std;

//define 定义一个变量时不能加;分号结尾, 定义一个宏函数或者语句时可以加;
#define MAX_LINE 1024


bool handle(int sockfd);

/*
 * 
 */
int main(int argc, char** argv)
{
    char * serverInetAddr = "127.0.0.1";
    int serverPort = 8637;
    char buf[MAX_LINE];
    int  socketfd = -1;

    //固定格式的struct sockaddr_in  结构体,socket编程
    struct sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    //将点十制IP地址转换为二进制地址
    inet_pton(AF_INET, serverInetAddr, &serverAddr.sin_addr);

    if(2 == argc)
    {
        serverInetAddr = argv[1];
    }
    else if(3 == argc)
    {
        serverInetAddr = argv[1];
        // #include <stdlib.h>
        // int atoi (__const char *__nptr);
        serverPort = atoi(argv[2]);
    }
    else if(3 < argc)
    {
        printf("usage: echoclient <IPaddress> <Port>");
        return -1;
    }

    //SOCK_STREAM       Connectionless, unreliable datagrams of fixed maximum length
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(0 > socketfd)
    {
        perror("socket error");
        return -1;
    }

    if(connect(socketfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect error");
        return -1;
    }

    printf("welcome to echoclient\n");
    
    handle(socketfd);
    close(socketfd);
    printf("exit\n");
    exit(0);

    return 0;
}

bool handle(int sockfd)
{
    char sendline[MAX_LINE], recvline[MAX_LINE];
    int ret = -1;
    while(true)
    {
        //fgets()行缓冲,阻塞函数
        if(NULL == fgets(sendline, MAX_LINE, stdin))
        {
            break;
        }
        /*
         //也可以不用标准库的缓冲流,直接使用系统函数无缓存操作
         if (read(STDIN_FILENO, sendline, MAXLINE) == 0) 
         {
             break;//read eof
         }
        */
        
        //阻塞和非阻塞,得看文件是不是设置了 NONBLOCK  socket文件使用fcntl()
        ret = write(sockfd, sendline, strlen(sendline));
        ret = read(sockfd, recvline, MAX_LINE);
        if(0 == ret)
        {
            printf("echoclient: server terminated prematurely\n");
            break;
        }

        write(STDOUT_FILENO, recvline, ret);
        //如果用标准库的缓存流输出有时会出现问题
        //fputs(recvline, stdout);

    }
}