#include "thread.h"
#include <assert.h>

static void* thread_routine(void* arg_)
{
    kcy::thread_t* self = (kcy::thread_t*)arg_;
    self->tfn(self->arg);
    return NULL;
}

void kcy::thread_t::start(thread_fn* tfn_, void* arg_)
{
    tfn = tfn_;
    arg = arg_;
    int rc = pthread_create(&descriptor,NULL,thread_routine,this);
    assert(0 == rc);
}

void kcy::thread_t::stop()
{
    int rc = pthread_join(descriptor,NULL);
    assert(0 == rc  );
}