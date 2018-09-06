/* 
 * File:   mailbox.h
 * Author: kcy
 * 
 * 线程间通讯的信箱: 比如 两个线程共享一个map,不安全, 
 * A线程使用mailbox发送信息给B线程,通知它自己对map增删操作,从而线程安全共享map
 * 
 * Created on 2016年1月21日, 下午2:41
 */

#ifndef MAILBOX_H
#define MAILBOX_H

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
    // char可以换成其他的模板类, 从而完成功能的扩展
    typedef ypipe_t<char, 10> cpipe_t;
    cpipe_t cpipe;
    signaler_t signaler;
    mutex_t sync;
    bool active;
};

#endif /* MAILBOX_H */

