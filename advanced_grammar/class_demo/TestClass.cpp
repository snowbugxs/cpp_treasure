/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestClass.cpp
 * Author: xuwei.huang
 * 
 * Created on 2017年5月16日, 上午10:49
 */

#include "TestClass.h"
#include <iostream>
using namespace std;

TestClass::TestClass()
{
    m_num = 1212;
    cout << "TestClass()   " << this << endl;
}

TestClass::TestClass(int num)
{
    m_num = num;
    cout << "TestClass(int num)   " << this << endl;
}
TestClass::TestClass(int testNum, int sourceNum):sourceClass(sourceNum)
{
    m_num = testNum;
    cout << "TestClass(int testNum, int sourceNum)   " << this << endl;
}


TestClass::TestClass(const TestClass& orig)
{
}

TestClass::~TestClass()
{
}

void TestClass::printNum()
{
    cout << "m_num = " << m_num << endl;
    sourceClass.printNum();
    
}

