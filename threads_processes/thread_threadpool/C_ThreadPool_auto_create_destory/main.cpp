/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2017年7月16日, 下午8:05
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadpool.h"

/**
 * 实现功能
 * 1.初始化指定个数的线程
 * 2.使用链表来管理任务队列
 * 3.支持拓展动态线程
 * 4.如果闲置线程过多,动态销毁部分线程
 */





/**------------------线程池API函数----------------
 * 创建线程池
 * thread_pool_t* thread_pool_create(int num);
 * 线程的入口函数
 * void *thread_excute_route(void *arg);
 * 添加任务
 * int   thread_pool_add_worker(thread_pool_t *pool,void*(*process)(void *arg),void *arg);  
 * 如果闲置时间过久则销毁部分线程*
 * void *thread_pool_is_need_recovery(void *arg);
 * 检测是否需要拓展线程
 * void *thread_pool_is_need_extend(void *arg);
 * 等待所有的线程结束
  void  thread_pool_wait(thread_pool_t *pool);
 * 销毁线程池
  void  thread_pool_destory(thread_pool_t *pool);
 *  显示线程的状态信息
 *   void *display_thread(void *arg);
 */

/*-----------------demo------------------------*/
struct param
{
    int id;
};

void *demo(void *arg)
{
    struct param *p = (struct param*) arg;
    printf("thread[%ld] excute task %d\n", pthread_self(), p->id);
}

int main(int argc, char **argv)
{
    thread_pool_t *thread_pool = NULL;
    thread_pool = thread_pool_create(10);
    /*添加任务*/
    int i = 0;
    struct param *p = NULL;
    for (i = 0; i < 10000; i++)
    {
        p = (struct param*) malloc(sizeof(struct param));
        p->id = i;
        thread_pool_add_worker(thread_pool, demo, (void*) p);
        //free(p);
    }
    thread_pool_wait(thread_pool);
    //thread_pool_destory(thread_pool);
    return 0;
}

