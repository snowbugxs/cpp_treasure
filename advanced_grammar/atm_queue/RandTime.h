/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        RandTime.h
 * Author:      xuwei.huang
 * Describe:    declaration of RandTime
 *              
 * Created on   2017年6月21日, 上午10:23
 */

#ifndef RANDTIME_H
#define RANDTIME_H

#include <iostream>

class RandTime
{
public:
    RandTime(int rand = 10);
    virtual ~RandTime();

private:
    /// 禁止使用复制构造函数和赋值运算符
    RandTime(const RandTime& orig);
    RandTime& operator=(const RandTime& orig);

    //    friend std::ostream & operator<<(std::ostream & os, const RandTime& orig);
    //    friend std::istream & operator>>(std::istream & is, RandTime& orig);

public:
    int getNum();
    bool resetRand(int rand);

private:
    bool setAnotherNum();
    
private:
    int m_rand;
    int m_num;

};

#endif /* RANDTIME_H */

