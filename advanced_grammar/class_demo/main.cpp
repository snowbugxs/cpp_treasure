/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年5月16日, 上午9:49
 */
#include <iostream>
#include <cstdlib>
#include "SourceClass.h"
#include "TestClass.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    TestClass testClass0;
    testClass0.printNum();
    
    TestClass testClass1(20);
    testClass1.printNum();
    
    TestClass testClass2(30, 60);
    testClass2.printNum();
    
    TestClass * pTestClass0 = new TestClass;
    pTestClass0->printNum();

    return 0;
}

