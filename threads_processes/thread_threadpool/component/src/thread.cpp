#include "thread.h"
#include <assert.h>


void* kcy::thread_routine(void* arg_)
{
    //arg_是传过来的this指针,也就是 thread_t 类及其子类对象的指针
    kcy::thread_t* self = (kcy::thread_t*)arg_;
    
    //typedef void (thread_fn) (void*); 函数指针类型
    //thread_fn* tfn; 是一个函数指针, 传过来的工作线程启动函数指针
    // 启动函数指针() , 就是函数调用, arg是穿送过来的参数
    self->tfn(self->arg);
    return NULL;
}

void kcy::thread_t::start(thread_fn* tfn_, void* arg_)
{
    tfn = tfn_;
    arg = arg_;
    int rc = pthread_create(&descriptor, NULL, thread_routine, this);
    assert(0 == rc);
}

void kcy::thread_t::stop()
{
    int rc = pthread_join(descriptor, NULL);
    assert(0 == rc);
}