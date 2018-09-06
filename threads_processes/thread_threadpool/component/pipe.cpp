/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pipe.cpp
 * Author: kcy
 * 
 * Created on 2016年10月14日, 上午10:16
 */

#include "pipe.h"
#include "ypipe.h"
#include <assert.h>

int pipepair(object_t* parents_[2], pipe_t* pipes_[2], int hwms_[2], bool conflate_[2])
{
    
}


pipe_t::pipe_t(object_t *parent_, upipe_t *inpipe_, upipe_t *outpipe_,
            int inhwm_, int outhwm_, bool conflate_) {
    
}


pipe_t::~pipe_t() {
}

