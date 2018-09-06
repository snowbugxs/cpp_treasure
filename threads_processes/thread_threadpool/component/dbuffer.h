/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dbuffer.h
 * Author: kcy
 *
 * Created on 2016年10月18日, 下午2:01
 */

#ifndef DBUFFER_H
#define DBUFFER_H

#include <stdlib.h>
#include <stddef.h>
#include <algorithm>

#include "mutex.h"
#include "blob.h"

class dbuffer
{
public:
    inline dbuffer()
    :back(&storage[0])
    ,front(&storage[1])
    ,has_msg(false)
    {
    
    }
 
    inline ~dbuffer()
    {
    }
    
    inline void write(const blob_t &value_)
    {
        blob_t &xvalue = const_cast<blob_t&>(value_);
        back->assign(xvalue);
        if(sync.try_lock())
        {
            std::swap(back,front);
            has_msg = true;
            sync.unlock();
        }
    }
    
    inline bool read( blob_t *value_)
    {
        if(!value_)
            return false;
        {
            scoped_lock_t lock(sync);
            if(!has_msg)
                return false;
            
            *value_ = *front;
            has_msg = false;
            return true;
        }
    }
    
    inline bool check_read()
    {
        scoped_lock_t lock(sync);
        return has_msg;
    }
    
    inline bool probe(bool (*fn)(blob_t&))
    {
        scoped_lock_t lock(sync);
        return (*fn)(*front);
    }
    
private:
    blob_t storage[2];
    blob_t *back, *front;
    
    mutex_t sync;
    bool has_msg;
    
    
};

#endif /* DBUFFER_H */

