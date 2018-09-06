/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoneNew.cpp
 * Author: xuwei.huang
 * 
 * Created on 2017年6月16日, 下午4:31
 */

#include "StoneNew.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

StoneNew::StoneNew()
{
    m_stone = m_pds_left = m_pounds = 0;
}

/// 该构造函数如果加入 explicit 声明, 则只能使用显式声明
/// 转换构造函数, 单个基本类型, 可以默认转换调用
/// 方案一

/*explicit*/ StoneNew::StoneNew(double lbs)
{
    m_stone = int(lbs) / LBS_PER_STN;
    m_pds_left = int(lbs) % LBS_PER_STN + lbs - int(lbs);
    m_pounds = lbs;
}

StoneNew::StoneNew(int stn, double lbs)
{
    m_stone = stn;
    m_pds_left = lbs;
    m_pounds = m_stone * LBS_PER_STN + lbs;
}

StoneNew::StoneNew(const StoneNew& orig)
{
    m_stone = orig.m_stone;
    m_pds_left = orig.m_pds_left;
    m_pounds = orig.m_pounds;
}

StoneNew::~StoneNew()
{
}

bool StoneNew::show_lbs() const
{
    cout << "total  " << m_pounds << " pounds" << endl;
    return true;
}

bool StoneNew::show_stn() const
{
    cout << "total  " << m_stone << "stone " << m_pds_left << " pounds" << endl;
    return true;
}


/// conversion functions

//StoneNew::operator int() const
//{
//    return int(m_pounds);
//}
//
//StoneNew::operator double() const
//{
//    return m_pounds;
//}
//
//StoneNew::operator long() const
//{
//    return long(m_pounds);
//}

/// 重载 ostream << 输出的时候, 不可以传入const对象, 因为在函数内部改变了他们的值

std::ostream & operator<<(std::ostream & os, const StoneNew & object)
{
    os << "total  " << object.m_pounds << " pounds";
    os << "or  " << object.m_stone << "stone ";
    os << object.m_pds_left << " pounds" << endl;
    return os;
}

/// 方案一

//StoneNew operator+(const StoneNew & a, const StoneNew & b)
//{
//    // 这样返回了临时变量的引用, 直接错误, 如果是 new 方法可以这样做, 不然还是直接返回新对象
//    //    return StoneNew(a.m_pounds + b.m_pounds);
//    return StoneNew(a.m_stone + b.m_stone, a.m_pds_left + b.m_pds_left);
//}


/// 方案二

StoneNew StoneNew::operator+(double n)
{
    return StoneNew(m_pounds + n);
}
/// 方案二

StoneNew operator+(double n, const StoneNew & a)
{
    return StoneNew(a.m_stone, a.m_pds_left + n);
}



