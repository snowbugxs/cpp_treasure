/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        GroupMap.h
 * Author:      xuwei.huang
 * Describe:    declaration of GroupMap
 *              扩展容器,将容器变为类的成员变量
 *              没有完成---> 应该对map的基本功能进行进一步的封装, 然后改造成模板使用(记得模板需要装在一个文件hpp中)
 *              
 * Created on   2017年6月20日, 上午11:16
 */

#ifndef GROUPMAP_H
#define GROUPMAP_H

#include <iostream>
#include <map>
#include <memory>

class GroupMap
{
private:

    /// 类中声明的类型(typedef或者class struct等等), 都必须在上文中声明之后再使用
    //    typedef std::pair<std::string, int> myPair;

    /// 函数对象

    struct CompareFunc
    {
        /// 我去搞错了, 这是重载的<号, 不是仿函数, 仿函数重载是重载的(), 模仿的是函数调用

        /// 下面是重载的 < 号
        /// 方法一, 直接使用友元函数
        //        friend bool operator<(const std::string & a, const std::string & b)
        //        {
        //            return a < b;
        //        }

        /// 方法二, 创建一个string变量, 再使用类成员函数重载. 重载的运算符. (是对象调用运算符)
        std::string a;

        bool operator<(const std::string &b)
        {
            return a < b;
        }

    };

    /// 仿函数, 函数对象 重载()号

    class MyFunctor
    {
    public:
        bool operator()(const std::string & a, const std::string & b)
        {
            return a < b;
        }
    };




    /// map的传入参数  (key值, value值, 比较函数, 适配器)
    //    std::map<std::string, int, CompareFunc> m_map;
    /// 使用仿函数
    std::map<std::string, int, MyFunctor> m_map;


    /// 使用指针,指向外界传入的容器对象
    //    typedef std::map<std::string, int> * pMap;
    //    pMap m_pMap;

    /// 智能指针好难用啊, 可以探索一下如何使用智能指针.
    /// 在类外可以直接声明的时候  std::auto_ptr<pMap> a(m_pMap);
    //    std::auto_ptr<pMap> a;


public:
    GroupMap();
    /// 
    /// 那么如何copy 指向的容器对象呢?  使用*this = 另一个容器???
    /// 使用指针指向容器对象的地址. 
    /// 如何让外界的容器, 传入本类变成对象的容器?  泛型编程
    //    GroupMap();
    GroupMap(const GroupMap& orig);
    virtual ~GroupMap();

public:
    GroupMap& operator=(const GroupMap& orig);

    //    friend std::ostream & operator<<(std::ostream & os, const GroupMap& orig);
    //    friend std::istream & operator>>(std::istream & is, GroupMap& orig);

public:
    /// 包装容器的增删改查动作, 提供迭代器操作
    /// 增
    bool insert(const std::string & str, int b);
    /// 删
    bool deleteone();
    /// 修
    bool modify();
    /// 查
    int get(const std::string & str);
    /// 迭代器
    /// 得看一下交易核心的代码
    /// 如何自定义一个迭代器类型,或者说一个类似迭代器类型, 可以让外界用变量=接收的时候来使用??
    std::map<std::string, int, CompareFunc>::iterator getIterator();


};

#endif /* GROUPMAP_H */

