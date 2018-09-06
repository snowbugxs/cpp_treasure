/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年5月25日, 上午9:00
 */

//mixtypes.cpp -- some type combinations

#include <iostream>

typedef struct antarctica_years_end
{
    int year;
    int month;
    double time;
}antarctica;

//typedef antarctica_years_end antarctica;

int main()
{
    using namespace std;
    
    antarctica s01, s02, s03;
    s01.year = 1999;
    s03.year = 1997;
    antarctica *pa = &s02;
    pa->year = 1998;
    antarctica trio[3];
    trio[0].year = 2003;
    trio[1].year = 2004;
    trio[2].year = 2005;
    //数组名是数组的首地址, 也是数组第一个元素的地址, 可以直接->调用第一个元素,
    //数组名 + 1 ,就是向后偏移一个数组元素的距离, 然后就是新数组的首地址和新数组第一个元素的首地址, 可以直接->调用
    //注意运算符优先级加的(), 而不是运算逻辑的()
    cout << "trio->year  " << trio->year << endl;
    cout << "(trio+1)->year " << (trio+1)->year << "  可以使用, 但netbeans显示报错,编译通过" << endl;
    
    const antarctica *arp[3] = {&s01, &s02, &s03};
    cout << "const antarctica *arp[3] = {&s01, &s02, &s03};" <<endl;
    cout << "arp[1]->year  " << arp[1]->year << endl;
    cout << "(*(arp+1))->year  " << (*(arp+1))->year << endl;
    cout << "(*(arp+2))->year  " <<(*(arp+2))->year << endl;
    const antarctica **ppa = arp;
    const antarctica **ppb = arp;
    cout << "const antarctica **ppb = arp;" << endl;
    //or use 
    //auto ppb = arp;
    cout << "(*ppa)->year  " << (*ppa)->year << endl;
    cout << "(*(ppb+2))->year  " << (*(ppb+2))->year << endl;
    
    
    return 0;
}


