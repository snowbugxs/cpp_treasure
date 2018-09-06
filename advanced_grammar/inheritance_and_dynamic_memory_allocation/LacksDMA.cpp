/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        LacksDMA.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of LacksDMA
 *              derived class without DMA
 *              uses implicit copy constructor
 *              uses implicit assignment operator
 * Created on   2017年7月3日, 下午7:43
 */

#include "LacksDMA.h"

/*static member here*/


/*methods for subclass*/

/*construction function*/
/// 对于基类的对象部分采用初始化参数列表  : 基类名(), 就是基类构造函数

LacksDMA::LacksDMA(const char * c, const char * l, int r) : BaseDMA(l, r)
{
    strncpy(m_color, c, COL_LEN - 1);
    m_color[COL_LEN - 1] = '\0';
}

LacksDMA::LacksDMA(const char * c, const BaseDMA & orig) : BaseDMA(orig)
{
    strncpy(m_color, c, COL_LEN - 1);
    m_color[COL_LEN - 1] = '\0';
}

/// 这里可以不提供特殊的复制构造函数
/// 因为本类中没有分配空间, 可以直接使用默认复制构造函数的成员复制
/// 成员复制的时候会首先调用成员类本身的特殊复制构造函数, 如果没有就是用默认的复制构造函数

LacksDMA::LacksDMA(const LacksDMA& orig) : BaseDMA(orig)
{
    strncpy(m_color, orig.m_color, COL_LEN - 1);
    m_color[COL_LEN - 1] = '\0';
}

LacksDMA::~LacksDMA()
{

}

/*overloaded operator function*/
LacksDMA& LacksDMA::operator=(const LacksDMA& orig)
{
    if(this == &orig)
        return * this;
    /// 这里不能返回临时变量的引用
    //    return LacksDMA(orig);

    /// 需要调用基类的赋值运算符重载
    BaseDMA::operator=(orig);
    std::strncpy(m_color, orig.m_color, COL_LEN - 1);
    return * this;
}

std::ostream & operator<<(std::ostream & os, const LacksDMA& orig)
{
    os << "Color: " << orig.m_color << std::endl;
    os << (const BaseDMA) orig;
    return os;
}


/*public interface*/
