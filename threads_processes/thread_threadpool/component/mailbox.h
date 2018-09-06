/* 
 * File:   mailbox.h
 * Author: kcy
 *
 * Created on 2016年1月21日, 下午2:41
 */

#ifndef MAILBOX_H
#define	MAILBOX_H

#include <stddef.h>
#include "signaler.h"
#include "mutex.h"
#include "ypipe.h"
class mailbox_t
{
public:
    mailbox_t();
    ~mailbox_t();
    
    int get_fd();
    void send(const char &c_);
    int recv(char *c_, int timeout_);
    
    
private:
    typedef ypipe_t<char,10> cpipe_t;
    cpipe_t cpipe;
    signaler_t signaler;
    mutex_t sync;
    bool active;
};

#endif	/* MAILBOX_H */

