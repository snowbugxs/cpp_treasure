
#include <iostream>
#include "mtrie.h"
#include "clock.h"
#include <map>
#include "file_watch.h"
#include "mtrie.h"
#include "epoll.h"
#include "i_poll_events.h"
#include "mailbox.h"
//#include "mysql_help.h"

using namespace std;
using namespace __gnu_cxx;
#define NDEBUG




void int_test();
file_watch fw;
mailbox_t maibox; //可以多线程共享一个mailbox,然后线程互相通信

class epoll_test_recv : public kcy::i_poll_events
{

    virtual void in_event()
    {
        char c;
        int rc = maibox.recv(&c, 0);
        if(rc == 0)
            cout << "epoll_test_recv recv " << c << endl;
    }

    virtual void out_event()
    {

    }

    virtual void timer_event(int id_)
    {

    }
};

class epoll_test : public kcy::i_poll_events
{

    virtual void in_event()
    {
        //        char c;
        //        int rc = maibox.recv(&c, 0);
        //        if(rc == 0)
        //            cout << "recv " << c << endl;
    }

    virtual void out_event()
    {

    }

    virtual void timer_event(int id_)
    {
        cout << "timer id " << id_ << endl;
        //        maibox.send('q');
        while(true) //如果是一个单线程的发送接收, 如果发送时sleep(),那么接受线程就无法接收了
        {
            maibox.send('q');
            sleep(2);
        }

    }
};

int main(int argc, char** argv)
{
    //        mysql_help sql_help;
    //        bool connect = sql_help.sql_connect("192.168.3.100", "tradepro", "tradepro", "cpp_quantdo");
    //        if(!connect)
    //            return -1;
    //        sql_insertor* in = sql_help.insert_into("ssel1_static");
    //        in->set_key_n_nalue("Time",12344,true);
    //        in->sql_command_process();



    int ret = 1; //= fw.add_watch("./notify.txt",IN_ACCESS | IN_ATTRIB | IN_MODIFY | IN_CLOSE_WRITE);
    assert(ret > 0);

    kcy::epoll_t poller1;
    kcy::epoll_t poller2;

    epoll_test timer1;
    poller1.add_timer(2000, &timer1, 111);
    kcy::epoll_t::handle_t handle1 = poller1.add_fd(maibox.get_fd(), &timer1);
    poller1.set_pollin(handle1);

    epoll_test_recv timer2;
    poller2.add_timer(2000, &timer2, 222);
    kcy::epoll_t::handle_t handle2 = poller2.add_fd(maibox.get_fd(), &timer2);
    poller2.set_pollin(handle2);


    //kcy::epoll_t::handle_t handle = poller.add_fd(fw.get_notify_fd(), &fw);
    //poller.set_pollin(handle);
    poller1.start();
    poller2.start();

    poller1.wait(); 
    //第二个wait或者for循环之后的wait怎么执行??
    poller2.wait(); 

    //str_test();
    int_test();


    return 0;
}

void int_test()
{
    cout << "end of int_test " << endl;
}

