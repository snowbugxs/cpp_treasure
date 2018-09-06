/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        RandTime.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of RandTime
 *              
 * Created on   2017年6月21日, 上午10:23
 */
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "RandTime.h"

RandTime::RandTime(int rand) : m_rand(rand)
{
    srand(time(0));
    m_num = 10;
}

RandTime::~RandTime()
{

}

//std::ostream & operator<<(std::ostream & os, const RandTime& orig)
//{
//
//}
//
//std::istream & operator>>(std::istream & is, RandTime& orig)
//{
//
//}

int RandTime::getNum()
{
    setAnotherNum();
    return m_num;
}

bool RandTime::resetRand(int rand)
{
    m_rand = rand;
    return true;
}

bool RandTime::setAnotherNum()
{
    /// 好吧, 书上的例子这里没有使用 RAND_MAX , 为什么呢?
    /// 还是有问题, 这里执行出来的结果都是1, 但后面使用时不是
    /// 这样无法操作, 有问题 估计是 RAND_MAX 的问题, 
//    m_num = rand() * m_rand / RAND_MAX ;
    std::cout << "ddddddd"<< std::rand() << std::endl;
    m_num = std::rand() * double(m_rand) / RAND_MAX + 1;
    //    m_num = rand() % m_rand + 1;
    return true;
}
