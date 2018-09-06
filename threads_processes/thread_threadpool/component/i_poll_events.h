/* 
 * File:   i_poll_events.hpp
 * Author: kcy
 *
 * Created on 2015年12月7日, 上午10:04
 */

#ifndef I_POLL_EVENTS_H
#define	I_POLL_EVENTS_H
namespace kcy
{
    struct i_poll_events
    {
        virtual ~i_poll_events(){}
        
        virtual void in_event() = 0;
        
        virtual void out_event() = 0;
        
        virtual void timer_event(int id_) = 0;
    };
}


#endif	/* I_POLL_EVENTS_H */

