#pragma once
#include <deque>
#include <string>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// 使用C++98 语言规范实现的线程池： 面向对象做法，每一个job都是Task继承类的对象
namespace zl {

    /// 执行任务的类，设置任务数据并执行
    class Task
    {
    public:

        Task(void *arg = NULL, const std::string taskName = "")
        : arg_(arg), taskName_(taskName)
        {
        }

        virtual ~Task()
        {
        }

        /** 设置任务数据 */ 
        void setArg(void *arg)
        {
            arg_ = arg;
        }

        virtual int run() = 0;

    protected:
        void *arg_;
        std::string taskName_;
    };

    /// 线程池管理类的实现
    class ThreadPool
    {
    public:
        ThreadPool(int threadNum = 10);
        ~ThreadPool();

    public:
        size_t addTask(Task *task); /// 添加任务进任务列表
        void stop(); /// 停止所有线程
        int size(); /// 获取当前任务队列中的线程数
        Task *take(); /// 获取下一个任务处理

    private:
        int createThreads(); /// 创建工作线程
        static void *threadFunc(void *threadData); /// 线程启动函数

    private:
        ThreadPool &operator=(const ThreadPool &);
        ThreadPool(const ThreadPool &);

    private:
        volatile bool isRunning_; /// 线程退出标志
        int threadsNum_; /// 线程池中线程数
        pthread_t *threads_; /// 线程号数组

        std::deque<Task *> taskQueue_; /// 任务列表
        pthread_mutex_t mutex_; /// 线程同步锁
        pthread_cond_t condition_; /// 线程同步的条件变量
    };
}
