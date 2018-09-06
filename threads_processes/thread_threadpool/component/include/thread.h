/* 
 * File:   thread.h
 * Author: kcy
 *
 * Created on 2015年12月7日, 上午11:12
 */

#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
namespace kcy {
    //定义一个函数指针类型, 工作线程的启动函数.
    typedef void (thread_fn) (void*);
    
    static void* thread_routine(void* arg_);

    class thread_t
    {
    public:
        inline thread_t()
        {
        }
        void start(thread_fn* tfn_, void* arg_);
        void stop();

        thread_fn* tfn;
        void* arg;
        
    private:
        //系统分配的线程ID, 自动分配, 需要系统默认构造分配的变量,不需要在构造函数中声明
        pthread_t descriptor;

        //将类的拷贝构造函数和赋值函数声明,但为空
        thread_t(const thread_t&);
        const thread_t& operator=(const thread_t&);
    };
}


#endif /* THREAD_H */

