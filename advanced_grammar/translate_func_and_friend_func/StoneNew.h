/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoneNew.h
 * Author: xuwei.huang
 * revised definition for the StoneNew class
 * Created on 2017年6月16日, 下午4:31
 */

#ifndef STONENEW_H
#define STONENEW_H

#include <iostream>

class StoneNew
{
public:
    /// default constructor
    StoneNew();
    /// construct from one single double parameter
    StoneNew(double lbs); /// 方案一
    /// construct from stone, lbs
    StoneNew(int stn, double lbs);
    /// construct from StoneNew object
    StoneNew(const StoneNew& orig);
    /// default destroyer
    virtual ~StoneNew();

public:
    bool show_lbs() const;
    bool show_stn() const;
    /// conversion functions
    /// 只有构造函数才能被声明为 explicit , 防止其被用于隐式转换
    //    operator int() const;
    //    operator double() const;
    //    operator long() const;

public:
    /// 重载 ostream << 输出的时候, 不可以传入const对象, 因为在函数内部改变了他们的值
    friend std::ostream & operator<<(std::ostream & os, const StoneNew & object);
    /// 方案一
    /// friend StoneNew & operator+ 和 StoneNew(double lbs) 配合实现 double + 对象
    //    friend StoneNew operator+(const StoneNew & a, const StoneNew & b);
    
    /// 方案二
    StoneNew operator+(double n);
    friend StoneNew operator+(double n, const StoneNew & a);

private:
    /// pounds per stone

    enum
    {
        LBS_PER_STN = 14
    };
    /// whole stones
    int m_stone;
    /// fractional pounds
    double m_pds_left;
    /// entire weight in pounds
    double m_pounds;

};

#endif /* STONENEW_H */

