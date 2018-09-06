
#include <iostream>
#include "mtrie.h"
#include "clock.h"
#include <map>
#include "file_watch.h"
#include "mtrie.h"
#include "epoll.h"
#include "mysql_help.h"
using namespace std;
using namespace __gnu_cxx;
#define NDEBUG




void int_test();
file_watch fw;
int main(int argc, char** argv) {
    mysql_help sql_help;
    bool connect = sql_help.sql_connect("192.168.19.192", "tradepro", "trading", "stock_db");
    if(!connect)
        return -1;
    
    sql_insertor* in = sql_help.insert_into("ssel1_static");
    in->set_key_n_nalue("Time",12344,true);
    in->sql_command_process();
    
    
    
    int ret = 1;//= fw.add_watch("./notify.txt",IN_ACCESS | IN_ATTRIB | IN_MODIFY | IN_CLOSE_WRITE);
    assert(ret > 0);
    
    kcy::epoll_t poller;
    //kcy::epoll_t::handle_t handle = poller.add_fd(fw.get_notify_fd(), &fw);
    //poller.set_pollin(handle);
    poller.start();
    poller.wait();
    //str_test();
    int_test();
    
    
    return 0;
}

void int_test() {
    
}

