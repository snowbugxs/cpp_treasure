/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        BrassPlus.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of BrassPlus
 *              
 * Created on   2017年7月4日, 上午10:51
 */

#include "BrassPlus.h"

/*static member here*/


/*methods for subclass*/

/*construction function*/
BrassPlus::BrassPlus(const std::string & s, long an, double bal, double ml, double r) : AcctABC(s, an, bal)
{
    m_maxLoan = ml;
    m_rate = r;
    m_owesBank = 0.0;
}

/// uses implicit copy constructor

BrassPlus::BrassPlus(const Brass & ba, double ml, double r) : AcctABC(ba)
{
    m_maxLoan = ml;
    m_rate = r;
    m_owesBank = 0.0;
}

BrassPlus::BrassPlus(const BrassPlus& orig)
{
    m_maxLoan = orig.m_maxLoan;
    m_rate = orig.m_rate;
    m_owesBank = orig.m_owesBank;
}

BrassPlus::~BrassPlus()
{

}

/*overloaded operator function*/
BrassPlus& BrassPlus::operator=(const BrassPlus& orig)
{
    if (this == &orig)
        return *this;
    AcctABC::operator=(orig);
    m_maxLoan = orig.m_maxLoan;
    m_rate = orig.m_rate;
    m_owesBank = orig.m_owesBank;
    return *this;
}

/*public interface*/
void BrassPlus::withdraw(double amt)
{
    Formatting f = setFormat();
    
    double bal = balance();
    if(amt <= bal)
        AcctABC::withdraw(amt);
    else if(amt <= bal + m_maxLoan - m_owesBank)
    {
        double advance = amt - bal;
        m_owesBank += advance * (1.0 + m_rate);
        std::cout << "Bank advance: $" << advance << std::endl;
        std::cout << "Finance charge: $" <<advance * m_rate << std::endl;
        deposit(advance);
        AcctABC::withdraw(amt);
    }
    else
        std::cout << "Credit limit exceeded. Transaction cancelled.\n";
    restore(f);
}

void BrassPlus::viewAcct()const
{
    Formatting f = setFormat();
    std::cout << "BrassPlus Client: " << fullName() << std::endl;
    std::cout << "Account Number: " << acctNum() << std::endl;
    std::cout << "Balance: $" << balance() << std::endl;
    std::cout << "Maximum loan: $" << m_maxLoan << std::endl;
    std::cout << "Owed to bank: $" << m_owesBank << std::endl;
    std::cout.precision(3);
    std::cout << "Loan Rate: " << 100 * m_rate << "% \n";
    restore(f);
}