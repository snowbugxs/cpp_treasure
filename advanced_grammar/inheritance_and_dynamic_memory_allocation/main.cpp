/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    使用动态内存分配的派生类, 需要提供显式的复制构造和赋值函数
 *              在复制构造函数的初始化列表中调用基类构造函数, 传递参数
 *              在赋值函数中通过基类名::operator=(), 调用基类的赋值运算符
 * Created on   2017年7月3日, 下午7:17
 */

#include <iostream>

#include "BaseDMA.h"
#include "LacksDMA.h"
#include "HasDMA.h"

using namespace std;

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv)
{
    using std::cout;
    using std::endl;
    
    BaseDMA shirt("Portabelly", 8);
    LacksDMA balloon("red", "Blimpo", 4);
    HasDMA map("Mercator", "Buffalo Keys", 5);
    
    cout << "Displaying baseDMA object: \n";
    cout << shirt << endl;
    cout << "Displaying lacksDMA object: \n";
    cout << balloon << endl;
    cout << "Displaying hasDMA object: \n";
    cout << map << endl;
    
    LacksDMA balloon2(balloon);
    LacksDMA balloon3;
    balloon3 = balloon2;
    cout << "Result of LacksDMA copy: \n";
    cout << balloon2 << endl;
    cout << "Result of LacksDMA assignment: \n";
    cout << balloon3 << endl;
    
    HasDMA map2(map);
    HasDMA map3;
    map3 = map2;
    cout << "Result of HasDMA copy: \n";
    cout << map2 << endl;
    cout << "Result of HasDMA assignment: \n";
    cout << map3 << endl;
    return 0;
}

