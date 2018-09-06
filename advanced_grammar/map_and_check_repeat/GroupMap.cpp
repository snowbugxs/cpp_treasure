/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        GroupMap.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of GroupMap
 *              
 * Created on   2017年6月20日, 上午11:16
 */

#include "GroupMap.h"

GroupMap::GroupMap()
{
    //    a = new (std::map<std::string, int>)();
}

GroupMap::GroupMap(const GroupMap& orig)
{
    m_map = orig.m_map;
    //    m_pMap = orig.m_pMap;
}

GroupMap::~GroupMap()
{
    //    delete m_pMap;
}

GroupMap& GroupMap::operator=(const GroupMap& orig)
{
    if(this == &orig)
        return *this;
    /// 如何深复制一个容器对象(包括容器存储的所有对象)
    /// 直接构造函数中已有的容器 = orig.容器, 就是深复制
    m_map = orig.m_map;
    /// 浅复制, 定义一个容器对象的指针. 在构造函数中传入一个容器对象,使用指针指向. 
    /// 浅复制的时候就直接使用指针赋值就行. 两个指针指向了一个容器
    //    m_pMap = orig.m_pMap;
    return *this;
}

//std::ostream & operator<<(std::ostream & os, const GroupMap& orig)
//{
//
//}
//
//std::istream & operator>>(std::istream & is, GroupMap& orig)
//{
//
//}


