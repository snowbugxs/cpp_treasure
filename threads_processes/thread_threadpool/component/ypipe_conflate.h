/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ypipe_conflate.h
 * Author: kcy
 *
 * Created on 2016年10月18日, 下午1:54
 */

#ifndef YPIPE_CONFLATE_H
#define YPIPE_CONFLATE_H
#include "dbuffer.h"
#include "ypipe_base.h"

template <typename T, int N> 
class ypipe_conflate : public ypipe_base_t<T,N>
{
public:
    ypipe_conflate();
    ypipe_conflate(const ypipe_conflate& orig);
    virtual ~ypipe_conflate();
private:

};

#endif /* YPIPE_CONFLATE_H */

