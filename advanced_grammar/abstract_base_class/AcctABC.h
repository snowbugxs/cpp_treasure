/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        AcctABC.h
 * Author:      xuwei.huang
 * Describe:    declaration of AcctABC
 *              
 * Created on   2017年7月4日, 上午9:01
 */

#ifndef ACCTABC_H
#define ACCTABC_H

#include <iostream>
#include <string>

class AcctABC
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    std::string m_fullName;
    long m_acctNum;
    double m_balance;

    /*methods for subclass*/
protected:

    struct Formatting
    {
        std::ios_base::fmtflags flag;
        std::streamsize pr;
    };

    /// 如果要保证 m_fullName 的引用不被修改, 那么返回值应该是const引用, 调用的函数fullName()也应该是const调用
    const std::string & fullName() const
    {
        return m_fullName;
    }

    long acctNum()const
    {
        return m_acctNum;
    }

    Formatting setFormat()const;
    void restore(Formatting & f) const;

    /*construction function*/
public:
    AcctABC(const std::string &s = "Nullbody", long an = -1, double bal = 0);
    AcctABC(const AcctABC& orig);
    virtual ~AcctABC();

    /*overloaded operator function*/
public:
    AcctABC& operator=(const AcctABC& orig);


    /*public interface*/
public:
    void deposit(double amt);
    virtual void withdraw(double amt) = 0;

    double balance()const
    {
        return m_balance;
    }

    virtual void viewAcct()const = 0;

};

#endif /* ACCTABC_H */

