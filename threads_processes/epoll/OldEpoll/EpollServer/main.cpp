/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年4月17日, 下午8:28
 */

#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>       /* basic system data types */
#include <sys/socket.h>      /* basic socket definitions */
#include <netinet/in.h>      /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>       /* inet(3) functions */
#include <sys/epoll.h> /* epoll function */
#include <fcntl.h>     /* nonblocking */
#include <sys/resource.h> /*setrlimit */

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAXEPOLLSIZE 1024
#define MAXLINE 1024
using namespace std;


int handle(int connfd);

/*  (1)调用open获得描述符，并指定O_NONBLOCK标志
    (2)对已经打开的文件描述符，调用fcntl，打开O_NONBLOCK文件状态标志。
flags = fcntl( s, F_GETFL, 0 ) )
fcntl( s, F_SETFL, flags | O_NONBLOCK )   */
int setnonblocking(int sockfd)
{
    if(fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) == -1)
    {
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int servPort = 6888;
    int listenq = 1024;

    int listenfd, connfd, kdpfd, nfds, n, nread, curfds, acceptCount = 0;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    struct epoll_event ev;
    struct epoll_event events[MAXEPOLLSIZE];
    struct rlimit rt;
    char buf[MAXLINE];

    /* 设置每个进程允许打开的最大文件数 */
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
    /*设置资源的软硬限制 RLMIT_NOFILE 指定比进程可打开的最大文件描述词大一的值，超出此值，将会产生EMFILE错误*/
    if(setrlimit(RLIMIT_NOFILE, &rt) == -1)
    {
        perror("setrlimit error");
        return -1;
    }

    /*字符串部分置零*/
    bzero(&servaddr, sizeof(servaddr));
    /*ipv4*/
    servaddr.sin_family = AF_INET;
    /*inaddr_any*/
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*servport 6888*/
    servaddr.sin_port = htons(servPort);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        perror("can't create socket file");
        return -1;
    }

    int opt = 1;
    /*设置调用close(socket)后,仍可继续重用该socket。调用close(socket)一般不会立即关闭socket，而经历TIME_WAIT的过程。
        BOOL bReuseaddr = TRUE;
        setsockopt( s, SOL_SOCKET, SO_REUSEADDR, ( const char* )&bReuseaddr, sizeof( BOOL ) );*/
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    /*设置sockfd非阻塞*/
    if(setnonblocking(listenfd) < 0)
    {
        perror("setnonblock error");
    }
    /*绑定*/
    if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind error");
        return -1;
    }
    /*监听*/
    if(listen(listenfd, listenq) == -1)
    {
        perror("listen error");
        return -1;
    }
    /* 创建 epoll 句柄，把监听 socket 加入到 epoll 集合里 */
    kdpfd = epoll_create(MAXEPOLLSIZE);
    
    /*设置事件类型 EPPLLIN和EPOLLET2种，EPOLLIN       连接到达；有数据来临；
        EPOLLOUT      边缘触发*/
    ev.events = EPOLLIN | EPOLLET;
    
    /*监听socket加入epoll集合里*/
    ev.data.fd = listenfd;
    
    /*interface面向对象编程语言中接口操作的关键字，功能是把所需成员组合起来，用来装封一定功能的集合。它好比一个模板，在其中定义了对象必须实现的成员，通过类或结构来实现它。
    epoll_ctl - control interface for an epoll descriptor控制epoll描述符的集合
       EPOLL_CTL_ADD
              Register  the  target  file  descriptor fd on the epoll instance
              referred to by the file descriptor epfd and associate the  event
              event with the internal file linked to fd.
     */

    if(epoll_ctl(kdpfd, EPOLL_CTL_ADD, listenfd, &ev) < 0)
    {
        fprintf(stderr, "epoll set insertion error: fd=%d\n", listenfd);
        return -1;
    }
    curfds = 1;

    printf("epollserver startup,port %d, max connection is %d, backlog is %d listenfd=%d\n", servPort, MAXEPOLLSIZE, listenq, listenfd);

    for(;;)
    {
    /* 等待有事件发生 */
    /* epoll_wait,  epoll_pwait  -  wait  for  an  I/O  event on an epoll file descriptor*/
    /*When successful, epoll_wait() returns the number  of  file  descriptors
        ready for the requested I/O, or zero if no file descriptor became ready
        during the requested  timeout  milliseconds.   When  an  error  occurs,
        epoll_wait() returns -1 and errno is set appropriately.*/
    /*-1 timeout  The  timeout  argument  specifies  the  number  of  milliseconds   that
        epoll_wait() will block.  	为-1表示一直阻塞下去直至有I/O事件或信号 */
    /*Note  that  the timeout interval will be rounded up to the system clock
        granularity, and kernel scheduling delays mean that the blocking inter‐
        val  may  overrun by a small amount.timeout 依系统时钟间隔取整*/

        /* curfds 表示epoll集合所能遇到的最大事件数. 等后面监听的文件增加一个,就会加一
         * events 是经过epoll_wait之后所剩下来的事件集合
         * kdpfd  是epoll的句柄,或者称之为epoll对象
         * 第四个参数  是等待时间  负数为阻塞,一直等待,0为非阻塞,未读取到返回0,正数为等待时间,超时返回0
         * nfds   为返回值,错误返回-1, 超时或者非阻塞未读取到返回0, 其余返回响应事件数 */       
        nfds = epoll_wait(kdpfd, events, curfds, -1);
        if(nfds == -1)
        {
            perror("epoll_wait");
            continue;
        }
        if(nfds == 0)
        {
            /* 返回值为0,代表:
             * 1. 如果epoll_wait的第四个参数是0, 那么就是非阻塞, 暂时没有数据可以读取
             * 2. 如果epoll_wait的第四个参数是正数,那么就是等待时间, 超时了, 暂时没有数据读取
             * 3. 如果epoll_wait的第四个参数是负数,那么就是阻塞, 等待直到有事件发生 */
            printf("songshiqisongshiqi\n");
        }
        /* 处理所有事件 */
        printf("nfds=%d\n", nfds);
        for(n = 0; n < nfds; ++n)
        {
            /*这步是在判断是不是listenfd连接事件啊*/
            printf("nfds=%d events.data.fd=%d\n", nfds, events[n].data.fd);
            if(events[n].data.fd == listenfd)
            {
                connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &socklen);
                if(connfd < 0)
                {
                    perror("accept error");
                    continue;
                }

                sprintf(buf, "accept form %s:%d listenfd=%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port, listenfd);
                printf("%d:%s", ++acceptCount, buf);
                /*这里疑似有误  应为nfds nfds为需处理的i/o数，超过最大值 关闭多余*/
                /*若是nfds>max 那不是循环都在关？应该设置temp=curfds，关一次temp--，直到temp<=max才不关*/
                /*我理解有误  下文代码加入epoll集合后才算正式可处理，curfds>max，不加入epoll集合，直接关闭*/
                if(curfds >= MAXEPOLLSIZE)
                {
                    fprintf(stderr, "too many connection, more than %d\n", MAXEPOLLSIZE);
                    close(connfd);
                    continue;
                }
                if(setnonblocking(connfd) < 0)
                {
                    perror("setnonblocking error");
                }
                /*设置事件类型    EPOLLIN 连接到达；有数据来临；EPOLLET 边缘触发模式    */
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = connfd;
                if(epoll_ctl(kdpfd, EPOLL_CTL_ADD, connfd, &ev) < 0)
                {
                    fprintf(stderr, "add socket '%d' to epoll failed: %s\n", connfd, strerror(errno));
                    return -1;
                }
                curfds++;
                continue;
            }
            // 处理客户端请求
            /*handle函数判断连接 若连接 则客户端所发内容原路返回发送 未连接则返回 */
            if(handle(events[n].data.fd) < 0)
            {
                /*从epoll集合移除*/
                epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
                curfds--;

            }
        }
    }
    close(listenfd);
    return 0;
}

/*可加入http */
int handle(int connfd)
{
    int nread;
    char buf[MAXLINE];
    nread = read(connfd, buf, MAXLINE); //读取客户端socket流

    if(nread == 0)
    {
        printf("client close the connection\n");
        close(connfd); /*断了之后有事件，handle<0而移除出集合*/
        return -1;
    }
    if(nread < 0)
    {
        perror("read error");
        close(connfd);
        return -1;
    }
    write(connfd, buf, nread); //响应客户端  
    return 0;
}


