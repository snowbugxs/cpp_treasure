/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   firstdefine.cpp
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 * 
 * Created on 2017年3月10日, 下午4:18
 */

#include "firstdefine.h"
#define  TEST 

#ifdef  TEST

#define ELSEFUNC(test) \
else\
{\
    cout<<"test参数不对!"<<endl;\
}



firstdefine::firstdefine() {
    
    if(false)
    {
    
    }
    ELSEFUNC(testtest)
    
}

firstdefine::firstdefine(const firstdefine& orig) {
}

firstdefine::~firstdefine() {
}

#endif



