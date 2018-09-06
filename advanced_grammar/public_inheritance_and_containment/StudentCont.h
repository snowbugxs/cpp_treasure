/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        StudentCont.h
 * Author:      xuwei.huang
 * Describe:    declaration of StudentCont
 *              defining a StudentCont class using containment
 *              包含版本提供了被显式命名的对象成员, 而私有继承提供了无名称的子对象成员
 *              
 * Created on   2017年7月4日, 下午4:46
 */

#ifndef STUDENTCONT_H
#define STUDENTCONT_H

#include <iostream>
#include <string>
#include <valarray>

class StudentCont
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    typedef std::valarray<double> ArrayDb;
    std::string m_name;
    ArrayDb m_scores; /// contained object

    /*methods for subclass*/
protected:
    std::ostream & arrayOut(std::ostream &os)const;

    /*construction function*/
public:
    StudentCont();
    explicit StudentCont(const std::string &s);
    explicit StudentCont(int n);
    StudentCont(const std::string & s, int n);
    StudentCont(const std::string & s, const ArrayDb & a);
    StudentCont(const char * str, const double * pd, int n);
    StudentCont(const StudentCont& orig);
    virtual ~StudentCont();

    /*overloaded operator function*/
public:
    StudentCont& operator=(const StudentCont& orig);

    /// output
    friend std::ostream & operator<<(std::ostream & os, const StudentCont& orig);
    /// input
    friend std::istream & operator>>(std::istream & is, StudentCont& orig);
    friend std::istream & getline(std::istream & is, StudentCont & orig);

    /*public interface*/
public:
    double average() const;
    const std::string & name() const;
    double & operator[](int i);
    double operator[](int i) const;

};

#endif /* STUDENTCONT_H */

