#include "mailbox.h"

mailbox_t::mailbox_t()
{
    bool ok = cpipe.read(NULL);
    assert(!ok);
    active = false;
}

mailbox_t::~mailbox_t()
{
    sync.lock();
    sync.unlock();
}

int mailbox_t::get_fd()
{
    return signaler.get_fd();
}

void mailbox_t::send(const char& c_)
{
    sync.lock();
    cpipe.write(c_,false);
    bool ok = cpipe.flush();
    sync.unlock();
    if(!ok)
        signaler.send();
}

int mailbox_t::recv(char* c_, int timeout_)
{
    if(active)
    {
        bool ok = cpipe.read(c_);
        if(ok)
            return 0;
        active = false;
        signaler.recv();
    }
    
    int rc = signaler.wait(timeout_);
    if(rc != 0 && (errno == EAGAIN || errno == EINTR))
        return -1;
    
    active = true;
    
    assert(rc == 0);
    bool ok = cpipe.read(c_);
    assert(ok);
    return 0;
}