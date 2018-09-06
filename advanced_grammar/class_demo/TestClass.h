/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestClass.h
 * Author: xuwei.huang
 *
 * Created on 2017年5月16日, 上午10:49
 */

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "SourceClass.h"

class TestClass
{
public:
    TestClass();
    TestClass(int num);
    TestClass(int testNum, int sourceNum);
    TestClass(const TestClass& orig);
    virtual ~TestClass();
    void printNum();
private:
    SourceClass sourceClass;
    int m_num;

};

#endif /* TESTCLASS_H */

