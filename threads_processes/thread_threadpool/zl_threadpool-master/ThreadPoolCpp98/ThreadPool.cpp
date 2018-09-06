#include "ThreadPool.h" 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

namespace zl
{

    ThreadPool::ThreadPool(int threadNum)
    {
        isRunning_ = true;
        threadsNum_ = threadNum;
        createThreads();
    }

    ThreadPool::~ThreadPool()
    {
        stop(); /// 这里析构函数调用了一次stop(), 所以打印了两次
        for (std::deque<Task*>::iterator it = taskQueue_.begin(); it != taskQueue_.end(); ++it)
        {
            delete *it;
        }
        taskQueue_.clear();
    }

    /// 创建线程池

    int ThreadPool::createThreads()
    {
        /// 如果是静态类型初始化可以使用 PTHREAD_MUTEX_INITIALIZER 来初始化 (就像int一样的写法)
        pthread_mutex_init(&mutex_, NULL); /// 初始化互斥量(同步锁)
        /// 静态使用 PTHREAD_COND_INITIALIZER 初始化
        pthread_cond_init(&condition_, NULL); /// 初始化条件变量
        threads_ = (pthread_t*) malloc(sizeof(pthread_t) * threadsNum_);
        for (int i = 0; i < threadsNum_; i++)
        {
            /// 创建线程   返回线程id   ,  线程参数,  线程启动函数,  启动函数的参数(void *类型)
            pthread_create(&threads_[i], NULL, threadFunc, this);
        }
        return 0;
    }

    size_t ThreadPool::addTask(Task *task)
    {
        pthread_mutex_lock(&mutex_);
        taskQueue_.push_back(task);
        int size = taskQueue_.size();
        pthread_mutex_unlock(&mutex_);
        /// 发送条件, 使得处于 pthread_cond_wait(&condition_) 状态的线程接收, 从wait中恢复处理工作
        /// 一个 signal 只能唤醒一个 wait 状态的线程
        /// broadcast 可以唤醒所有 wait 的线程
        pthread_cond_signal(&condition_);
        return size;
    }

    void ThreadPool::stop()
    {
        /// 打印主线程号
        printf("主线程[%lu] \n", pthread_self());
        printf("main 使用 break 为什么会打印两次?, 因为析构函数又调用了一次stop()函数 \n");
        
        if (!isRunning_)
        {
            return;
        }

        isRunning_ = false;
        /// broadcast 可以唤醒所有 wait 的线程
        pthread_cond_broadcast(&condition_);

        /// 主线程逐个等待所有线程返回, 再接着往下执行
        /// 线程使用 pthread_exit() 显式结束 或者 自然运行完毕结束
        /// pthread_exit(&str) 可以返回相应的结果
        /// pthread_cancel(id) 取消线程
        /// pthread_cancel调用并不等待线程终止，它只提出请求。线程在取消请求(pthread_cancel)发出后会继续运行，
        /// 直到到达某个取消点(CancellationPoint)。取消点是线程检查是否被取消并按照请求进行动作的一个位置.
        /// 线程取消点  http://www.cnblogs.com/lijunamneg/archive/2013/01/25/2877211.html
        for (int i = 0; i < threadsNum_; i++)
        {
            /// 可以使用 指针(接受地址)代替 NULL 从而获得线程 pthread_exit() 的参数
            pthread_join(threads_[i], NULL);
        }

        free(threads_);
        threads_ = NULL;

        /// 销毁互斥量和条件变量
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&condition_);
    }

    int ThreadPool::size()
    {
        /// 使用局部变量, 并对 taskQueue_ 上锁保证重入性
        pthread_mutex_lock(&mutex_);
        int size = taskQueue_.size();
        pthread_mutex_unlock(&mutex_);
        return size;
    }

    /// 获取下一个待处理的任务
    Task* ThreadPool::take()
    {
        Task* task = NULL;
        while (!task)
        {
            /// 注意:下面的每步处理都需要解锁，　不能一直占用资源
            pthread_mutex_lock(&mutex_);
            while (taskQueue_.empty() && isRunning_)
            {
                /// 任务队列为空, 且正在运行态, 那么线程池调度线程阻塞 wait 中, wait同时会unlock锁
                pthread_cond_wait(&condition_, &mutex_);
            }

            /// 结束wait状态的线程运行到这里, 检查是否是 stopall 唤醒 还是 有任务
            if (!isRunning_)
            {
                /// broadcast信号, 所以直接退出
                pthread_mutex_unlock(&mutex_);

                break;
            }
            else if (taskQueue_.empty())
            {
                /// signal信号, 但是任务队列已被处理完, 然后continue, 继续到 pthread_cond_wait 状态等待
                pthread_mutex_unlock(&mutex_);
                continue;
            }

            /// 开始处理任务
            assert(!taskQueue_.empty());
            task = taskQueue_.front();
            taskQueue_.pop_front();
            pthread_mutex_unlock(&mutex_);
        }
        return task;
    }

    /// 工作线程启动函数
    void* ThreadPool::threadFunc(void* arg)
    {
        pthread_t tid = pthread_self();
        /// C++ 类型转换,  等同于 (ThreadPool *)arg
        ThreadPool* pool = static_cast<ThreadPool*> (arg);
        /// 持续取出任务队列中的任务执行
        while (pool->isRunning_)
        {
            Task* task = pool->take();
            if (!task)
            {
                /// 该线程池有缺陷, 工作线程并没有在无任务时休眠, 而是直接退出结束了
                /// to do
                printf("thread %lu will exit\n", tid);
                break;
            }

            assert(task);
            task->run();
        }
        return 0;
    }

}
