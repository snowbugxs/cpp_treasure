#include "poller_base.h"
#include "i_poll_events.h"
#include <assert.h>


kcy::poller_base_t::poller_base_t()
{
    
}
kcy::poller_base_t::~poller_base_t ()
{
    // 确保关闭时计数为0
    assert(load.get() == 0);
}

int kcy::poller_base_t::get_load()
{
    return load.get();
}

void kcy::poller_base_t::adjust_load(int amount_)
{
    if(amount_ > 0)
        load.add(amount_);
    else if(amount_ < 0)
        load.sub(-amount_);
}

void kcy::poller_base_t::add_timer(int timeout_, i_poll_events *sink_, int id_)
{
    uint64_t expiration = clock.now_ms() + timeout_;
    timer_info_t info = {sink_, id_};
    timers.insert(timers_t::value_type(expiration,info));
}

void kcy::poller_base_t::cancel_timer(i_poll_events *sink_, int id_)
{
    for(timers_t::iterator it = timers.begin(); it != timers.end(); ++it)
    {
        if(it->second.sink == sink_ && it->second.id == id_)
        {
            timers.erase(it);
            return;
        }
    }
    assert(false); //没有定时器
}

//执行定时器
uint64_t kcy::poller_base_t::execute_timers()
{
    if(timers.empty())
        return 0;
    //Get the current time.
    uint64_t current = clock.now_ms();
    
    timers_t::iterator it = timers.begin();
    while(it != timers.end())
    {
        if(it->first > current) //定时时间大于当前时间?
            return it->first - current;//未触发
        it->second.sink->timer_event(it->second.id); //触发定时器事件
        timers_t::iterator o = it;
        ++it;
        timers.erase(o);//delete the event;
    }
    return 0;
}