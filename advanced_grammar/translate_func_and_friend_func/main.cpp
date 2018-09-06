/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 * user-defined conversion functions
 * Created on 2017年6月16日, 下午4:29
 */


#include <iostream>
#include "StoneNew.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    using std::cout;
    using std::cin;
    using std::endl;
    StoneNew poppins(9, 9.28);
    StoneNew dance(8, 8.22);
    //    double p_wt = poppins;
    //    cout << "Convert to double => ";
    //    cout << "Poppins: " << p_wt << " pounds" << endl;
    //    cout << "Convert to int => ";
    //    cout << "Poppins: " << int (poppins) << " pounds" << endl;

    /// 如果没有定义 转为long类型的转换函数的时候, 编译器会调用其他转换函数的结果来检查是否可以给long类型赋值, int 和 double 都不是最佳匹配, 都可以给long赋值, 所以二义性
    //    long p_wt_long = poppins;
    //    cout << "Convert to long => " << p_wt_long << " pounds" << endl;


    //    cout << dance + poppins << endl;

    /// 如果重载了类-->基本类型的转换函数, 那么下面语句就有问题了
    /// dance 可以转化为 基本类型, 而 8 也可以转化为 类, 那么cout改如何输出, 二义性
    //    cout << 8 + dance << endl;

    /// 实现 基本类型 + 类对象的 运算

    /// 在禁用转换函数后, 可以成功使用
    /// 方案一: StoneNew::StoneNew(double lbs) 和  friend std::ostream & operator<<(std::ostream & os, const StoneNew & object) 配合
    cout << 8 + dance << endl;

    /// 方案二: 
    /// 使用:     StoneNew operator+(double n); 和 friend StoneNew operator+(double n, const StoneNew & a);
    cout << 8 + dance << endl;



    return 0;
}

