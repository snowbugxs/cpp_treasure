/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SourceClass.cpp
 * Author: xuwei.huang
 * 
 * Created on 2017年5月16日, 上午10:45
 */

#include "SourceClass.h"
#include <iostream>

using namespace std;

SourceClass::SourceClass()
{
    m_num = 10;
    cout << "SourceClass()  " << this << endl;
}

SourceClass::SourceClass(int num)
{
    m_num = num;
    cout << "SourceClass(int num) " << this << endl;
}

SourceClass::SourceClass(const SourceClass& orig)
{
}

SourceClass::~SourceClass()
{
}

void SourceClass::printNum()
{
    cout << "m_num = " << m_num << endl;
    cout << "SourceClass::printNum()   " << this << endl;
}

