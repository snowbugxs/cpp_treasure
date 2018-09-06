/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年5月25日, 上午9:51
 */

#include <iostream>
#include <vector>
//#include <array>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    // C, original C++
    double a1[4] = {1.2, 2.4, 3.6, 4.8};
    // C++ 98 STL
    vector<double> a2(4);
    // no simple way to initialize in C98
    a2[0] = 1.0/3.0;
    a2[1] = 1.0/5.0;
    a2[2] = 1.0/7.0;
    a2[3] = 1.0/9.0;
    
    //C++11  -- create and initialize array object;
    //array<double, 4> a3 = {3.14, 2.72, 1.62, 1.41};
    //array<double, 4> a4;
    //valid for array objects of name size;
    //a4 = a3;

    //use array notation
    cout << "a1[2]: " << a1[2] << " at " << &a1[2] << endl;
    cout << "a2[2]: " << a2[2] << " at " << &a2[2] << endl;
//    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
//    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;

    //misdeed , a1的位置向前偏移2个double元素, 并将20.2存储到目的地, 越界.
    a1[-2] = 20.2; //转换为 *(a1-2) = 20.2;
    cout << "a1[-2]: " <<a1[-2] << " at " << &a1[-2] << endl;
//    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
//    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;
    
    //使用at成员函数,   vector和array可以使用.
    a2.at(3) = 333;
    cout << "a2.at(3) = " << a2.at(3) << endl;
    
    return 0;
}

