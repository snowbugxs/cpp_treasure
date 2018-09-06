/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年4月21日, 下午7:11
 */

#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>          /* basic system data types */
#include <sys/socket.h>         /* basic socket definitions */
#include <netinet/in.h>         /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>          /* inet(3) functions */
#include <sys/epoll.h>          /* epoll function */
#include <fcntl.h>              /* nonblocking */
#include <sys/resource.h>       /* setrlimit */

#include <stdlib.h> 
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAX_EPOLL_SIZE  1024
#define MAX_LINE        4096

using namespace std;

int handle(int);

/*
 * //如何设置文件非阻塞:
 * //   (1)调用open获得描述符，并指定O_NONBLOCK标志
 * //   (2)对已经打开的文件描述符，调用fcntl，打开O_NONBLOCK文件状态标志。
 * flags = fcntl( s, F_GETFL, 0 ) )
 * fcntl( s, F_SETFL, flags | O_NONBLOCK ) 
 */

bool setNonBlocking(int sockfd)
{
    if(-1 == fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK))
    {
        return false;
    }
    return true;
}

/*
 * 
 */
int main(int argc, char** argv)
{

    int serverPort = 8637;
    int listenQueue = 1024;

    int listenFd = -1;
    int connectionFd = -1;
    int currentFds = 0;
    int acceptCount = 0;
    int epollfd = -1;

    struct sockaddr_in serverAddr, clientAddr;
    socklen_t socketLen = sizeof(struct sockaddr_in);

    struct epoll_event ev;
    struct epoll_event events[MAX_EPOLL_SIZE];

    struct rlimit rt;

    char buf[MAX_LINE];

    //设置每个进程所允许打开的最大文件数
    rt.rlim_max = rt.rlim_cur = MAX_EPOLL_SIZE;
    /*
     * 设置资源的软硬限制 
     * RLMIT_NOFILE 指定比进程可打开的最大文件描述词大一的值，
     * 超出此值，将会产生EMFILE错误
     */
    if(-1 == setrlimit(RLIMIT_NOFILE, &rt))
    {
        perror("setrlimit error");
        return -1;
    }

    bzero(&serverAddr, sizeof(serverAddr));
    /*ipv4*/
    serverAddr.sin_family = AF_INET;
    /*inaddr_any*/
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*servport 8637*/
    serverAddr.sin_port = htons(serverPort);

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenFd)
    {
        perror("can't create socket file");
        return -1;
    }

    int opt = 1;
    /*
                1.设置调用close(socket)后,仍可继续重用该socket。调用close(socket)一般不会立即关闭socket，而经历TIME_WAIT的过程。
                BOOL bReuseaddr = TRUE;
                setsockopt( s, SOL_SOCKET, SO_REUSEADDR, ( const char* )&bReuseaddr, sizeof( BOOL ) );
        2. 如果要已经处于连接状态的soket在调用closesocket()后强制关闭，不经历TIME_WAIT的过程：
                BOOL bDontLinger = FALSE;
                setsockopt( s, SOL_SOCKET, SO_DONTLINGER, ( const char* )&bDontLinger, sizeof( BOOL ) );
        3.在send(),recv()过程中有时由于网络状况等原因，收发不能预期进行,可以设置收发时限：
                int nNetTimeout = 1000; //1秒
                //发送时限
                setsockopt( socket, SOL_SOCKET, SO_SNDTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
                //接收时限
                setsockopt( socket, SOL_SOCKET, SO_RCVTIMEO, ( char * )&nNetTimeout, sizeof( int ) );
     */
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /*设置sockfd非阻塞*/
    if(!setNonBlocking(listenFd))
    {
        perror("setnonblock error");
    }

    /*绑定*/
    if(-1 == bind(listenFd, (struct sockaddr*) &serverAddr, sizeof(struct sockaddr)))
    {
        perror("bind error");
        return -1;
    }

    /*监听*/
    if(-1 == listen(listenFd, listenQueue))
    {
        perror("listen error");
        return -1;
    }

    /* 创建 epoll 句柄，epoll是一个对象 */
    epollfd = epoll_create(MAX_EPOLL_SIZE);
    /*
     * 设置事件类型 EPPLLIN和EPOLLET，
     * EPOLLIN       连接到达；有数据来临；
     * EPOLLOUT      边缘触发
     * http://blog.csdn.net/yusiguyuan/article/details/15027821
     */
    ev.events = EPOLLIN | EPOLLET;
    /* 监听socket加入epoll集合里 */
    ev.data.fd = listenFd;
    
    
    /*
     * interface面向对象编程语言中接口操作的关键字，
     * 功能是把所需成员组合起来，用来装封一定功能的集合。
     * 它好比一个模板，在其中定义了对象必须实现的成员，
     * 通过类或结构来实现它。
     */
    /*
        EPOLL_CTL_ADD：       	注册新的fd到epfd中；
        EPOLL_CTL_MOD：      	修改已经注册的fd的监听事件；
        EPOLL_CTL_DEL：        	从epfd中删除一个fd；
     */
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenFd, &ev) < 0)
    {
        fprintf(stderr, "epoll set insertion error : fd = %d\n", listenFd);
        return -1;
    }
    currentFds++;

    printf("epollserver startup, port:%d, max connection is %d, backlog = %d, listenfd=%d\n",
            serverPort, MAX_EPOLL_SIZE, listenQueue, listenFd);

    int nfds = -1;
    while(true)
    {
        /*
           int epoll_wait(int epfd, struct epoll_event * events, intmaxevents, int timeout);
           等待事件的产生，类似于select()调用。参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大(数组成员的个数)，这个maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。
           该函数返回需要处理的事件数目，如返回0表示已超时。
           返回的事件集合在events数组中，数组中实际存放的成员个数是函数的返回值。返回0表示已经超时。
         */
        nfds = epoll_wait(epollfd, events, currentFds, -1);
        if(-1 == nfds)
        {
            perror("epoll_wait");
            continue;
        }
            //超时才会返回0
        else if(0 == nfds)
        {
            printf("there is no client contact\n");
        }
        else
        {
            /* 处理所有事件 */
            printf("nfds = %d\n", nfds);
            for(int n = 0; n < nfds; ++n)
            {
                printf("nfds = %d events[%d].data.fd = %d\n", nfds, n, events[n].data.fd);
                printf("总计 %d 个文件有写入 正在处理第 %d 个事件 有写入事件的文件描述符是 %d\n", nfds, n, events[n].data.fd);
                
                /* 判断响应事件的文件fd是不是正在监听的listenFd,如果是就是有新的连接接入 */
                if(events[n].data.fd == listenFd)
                {
                    connectionFd = accept(listenFd, (struct sockaddr *) &clientAddr, &socketLen);
                    if(0 > connectionFd)
                    {
                        perror("accept error");
                        continue;
                    }
                    sprintf(buf, "accept from %s:%d  listenFd = %d\n", inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port, listenFd);
                    printf("%d : %s", ++acceptCount, buf);
                    printf("有新客户端接入listenfd, 生成新socket= %d 与之交流", connectionFd);

                    //如果当前已经监听的文件描述符集合数 已经大于最大允许值,就会放弃新的连接请求
                    if(currentFds >= MAX_EPOLL_SIZE)
                    {
                        fprintf(stderr, "too many connection, more than %d \n", MAX_EPOLL_SIZE);
                        close(connectionFd);
                        continue;
                    }
                    if(setNonBlocking(connectionFd) < 0)
                    {
                        perror("setNonBlocking error");
                    }

                    //设置新连接的触发模式
                    ev.events = EPOLLIN | EPOLLET;
                    ev.data.fd = connectionFd;
                    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, connectionFd, &ev) < 0)
                    {
                        fprintf(stderr, "add socket %d to epoll failed : %s \n", connectionFd, strerror(errno));
                        return -1;
                    }
                    currentFds++;
                    printf("add socket %d to epoll \n", connectionFd);
                    printf("将新生成的 socket %d 加入 epoll  \n", connectionFd);
                    continue;
                }

                //开始逐个处理客户端发来的信息
                //如果客户端关闭或者出错,就将与之交流的自身socketfd文件移出epoll集合,并且关闭.
                if(handle(events[n].data.fd) < 0)
                {
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd, &ev);
                    currentFds--;
                    printf("现在还有 %d 文件描述符在epoll集合内", currentFds);
                }
            }
        }
    }
    //close怎么可以在循环里面?犯了低级错误了
    close(listenFd);
    return 0;
}

int handle(int connectionFd)
{
    int nread;
    char buf[MAX_LINE];
    char *responseBuf = "this is sever's response\n";
    
    //读取客户端socket流
    nread = read(connectionFd, buf, MAX_LINE);

    if(0 == nread)
    {
        printf("client sockfd %d  close the connection \n", connectionFd);
        close(connectionFd);
        return -1;
    }
    else if(0 > nread)
    {
        perror("read error");
        close(connectionFd);
        return -1;
    }

    printf("recevice client request: %s\n", buf);

    write(connectionFd, responseBuf, strlen(responseBuf));
    write(connectionFd, buf, nread);
    return 0;
}

