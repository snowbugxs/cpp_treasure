/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        AcctABC.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of AcctABC
 *              
 * Created on   2017年7月4日, 上午9:01
 */

#include "AcctABC.h"

/*static member here*/

/*methods for subclass*/
AcctABC::Formatting AcctABC::setFormat()const
{
    /// set up ###.## format
    Formatting f;
    f.flag = std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    f.pr = std::cout.precision(2);
    return f;
}

void AcctABC::restore(Formatting & f) const
{
    std::cout.setf(f.flag, std::ios_base::floatfield);
    std::cout.precision(f.pr);
}

/*construction function*/
AcctABC::AcctABC(const std::string &s, long an, double bal)
{
    m_fullName = s;
    m_acctNum = an;
    m_balance = bal;
}

AcctABC::AcctABC(const AcctABC& orig)
{
    m_fullName = orig.m_fullName;
    m_acctNum = orig.m_acctNum;
    m_balance = orig.m_balance;
}

AcctABC::~AcctABC()
{

}

/*overloaded operator function*/
AcctABC& AcctABC::operator=(const AcctABC& orig)
{
    if (this == &orig)
        return *this;
    this->m_fullName = orig.m_fullName;
    this->m_acctNum = orig.m_acctNum;
    this->m_balance = orig.m_balance;
    return *this;
}

void AcctABC::deposit(double amt)
{
    if (amt < 0)
        std::cout << "Negative deposit not allowed; " << "deposit is cancelled.\n";
    else
        m_balance += amt;
}

void AcctABC::withdraw(double amt)
{
    do
    {
        if (amt < 0)
        {
            std::cout << "Negative withdraw not allowed; " << "withdraw is cancelled.\n";
            break;
        }
        if (m_balance - amt < 0)
        {
            std::cout << "Balance is not enough; " << "withdraw is cancelled.\n";
            break;
        }
        m_balance -= amt;
    } while (0);
    return;
}

/// 纯虚函数可以不实现
//void AcctABC::ViewAcct() const
//{
//
//}

/*public interface*/
