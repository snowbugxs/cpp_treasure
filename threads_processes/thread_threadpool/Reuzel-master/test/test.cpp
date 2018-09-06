//
// test.cpp
//
// Copyright (c) 2017 Jiawei Feng
//

#include "../src/ThreadPool.h"
#include "../src/CountDownLatch.h"
#include <stdio.h>
#include <pthread.h>
#include <string>
#include <unistd.h>

void print()
{
    printf("current pthread = %d\n", Reuzel::CurrentThread::gettid());
}

void printString(const std::string &taskId)
{
    printf("current pthread = %d %s\n",
            Reuzel::CurrentThread::gettid(), taskId.c_str());
    usleep(50 * 1000);
}

void test(int maxSize)
{
    printf("Test ThreadPool with max queue size = %d\n", maxSize);
    Reuzel::ThreadPool pool("MainThreadPool");
    pool.setMaxQueueSize(maxSize);
    pool.start(5);

    printf("Adding print task\n");
    pool.addTask(print);
    pool.addTask(print);

    printf("Adding printString tast\n");
    for (int i = 0; i < 20; ++i) {
        std::string taskId("task - ");
        taskId += std::to_string(i);
        pool.addTask(std::bind(printString, taskId));
    }

    Reuzel::CountDownLatch latch(1);
    pool.addTask([&](){ latch.countDown(); });
    latch.wait();
    pool.stop();
}

int main()
{
//    test(0);
//    test(1);
    test(5);
//    test(10);
//    test(50);
}
