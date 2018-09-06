/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PackageSet.hpp
 * Author: xuwei.huang
 * 
 *          1. C++模板的分开编译问题:
 *                  C++模板类的编写: C++模板的声明和实现必须都在同一个文件, 分开就会报错. 
 *                  ///解决方案:
 *                  1. 将模板类的声明和定义写在同一个头文件中 (推荐)
 *                  2. 分为.h和.cpp文件后, 在.h文件的尾部加上 #include "...cpp" (有些无法支持)
 *                  3. 在.cpp文件中使用 export 关键字 (未找到例子)
 *
 *          2. STL中的组件是拿来进行组合复用的，不是拿来继承的..
 *                  C++不要继承标准容器类, 因为所有的标准容器类的析构函数都不是虚析构函数. 继承后, 如果使用基类指针指向子类对象, 
 *                  那么在对象消亡的时候, 基类指针只会调用基类的析构函数, 却不会调用子类的析构函数, 造成内存泄漏
 *                   ///扩展方法:
 *                  1. 使用类成员变量进行组合
 *                  2. 使用 iterator 进行扩展
 *
 * Created on 2017年6月20日, 上午11:04
 */

#ifndef PACKAGESET_HPP
#define PACKAGESET_HPP


#include <set>

template<class T>
class PackageSet:public std::set<T>
{
public:
    PackageSet();
    PackageSet(const PackageSet& orig);
    virtual ~PackageSet();
};

template<class T>
PackageSet<T>::PackageSet()
{

}

template<class T>
PackageSet<T>::PackageSet(const PackageSet& orig)
{

}
template<class T>
PackageSet<T>::~PackageSet()
{

}



#endif /* PACKAGESET_HPP */

