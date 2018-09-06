/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        StudentInh.h
 * Author:      xuwei.huang
 * Describe:    declaration of StudentInh
 *              
 * Created on   2017年7月4日, 下午8:20
 */

#ifndef STUDENTINH_H
#define STUDENTINH_H

#include <iostream>
#include <string>
#include <valarray>

/// 不推荐继承STL容器, 因为STL容器的析构函数都不是虚析构函数, 容易内存泄漏

class StudentInh : private std::string, private std::valarray<double>
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    typedef std::valarray<double> ArrayDb;

    /*methods for subclass*/
protected:
    std::ostream & arrayOut(std::ostream & os) const;

    /*construction function*/
public:

    StudentInh() : std::string("Null Student"), ArrayDb()
    {

    }

    explicit StudentInh(const std::string &s) : std::string(s), ArrayDb()
    {

    }

    explicit StudentInh(int n) : std::string("Nully"), ArrayDb(n)
    {

    }

    StudentInh(const std::string &s, int n) : std::string(s), ArrayDb(n)
    {

    }

    StudentInh(const std::string & s, const ArrayDb &a) : std::string(s), ArrayDb(a)
    {

    }

    StudentInh(const char * str, const double * pd, int n) : std::string(str), ArrayDb(pd, n)
    {

    }

    StudentInh(const StudentInh& orig);

    virtual ~StudentInh()
    {

    }

    /*overloaded operator function*/
public:
    StudentInh& operator=(const StudentInh& orig);

    /// output
    friend std::ostream & operator<<(std::ostream & os, const StudentInh& orig);
    /// input
    friend std::istream & operator>>(std::istream & is, StudentInh& orig);
    friend std::istream & getline(std::istream & is, StudentInh & orig);

    /*public interface*/
public:
    /// 使用using声明, 可以直接在外界通过对象.来调用max()
    using ArrayDb::max;
    using ArrayDb::min;
    
    double average() const;
    const std::string & name() const;
    double & operator[](int i);
    double operator[](int i) const;

};

#endif /* STUDENTINH_H */

