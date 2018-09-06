#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "ThreadPool.h"  

class MyTask : public zl::Task
{
public:

    MyTask()
    {
    }

    virtual int run()
    {
        printf("thread[%lu] : %s\n", pthread_self(), (char*) this->arg_);
        sleep(1);
        return 0;
    }
};

int main()
{

    char szTmp[] = "hello world";

    MyTask taskObj;
    taskObj.setArg((void*) szTmp);

    printf("主线程 [%lu] \n", pthread_self());

    zl::ThreadPool threadPool(5);
    for (int i = 0; i < 20; i++)
    {
        threadPool.addTask(&taskObj);
        /// 主线程刚刚插入任务, 工作线程就已经启动了
        //        printf(" %d tasks need to process\n", threadPool.size());
    }
    printf("there are still %d tasks need to process\n", threadPool.size());

    while (1)
    {
        printf("there are still %d tasks need to process\n", threadPool.size());
        if (threadPool.size() == 0)
        {
            sleep(3);
            threadPool.stop();
            printf("主线程 while [%lu] \n", pthread_self());
            printf("Now I will exit from main\n");
//            exit(0);
            // to do  : 为什么使用exit()就会打印两次
                        break;
        }
        sleep(2);
    }
    //    sleep(2);

    return 0;
} 