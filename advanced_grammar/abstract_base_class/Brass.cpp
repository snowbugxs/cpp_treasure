/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        Brass.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of Brass
 *              
 * Created on   2017年7月4日, 上午10:13
 */

#include "Brass.h"

/*static member here*/


/*methods for subclass*/

/*construction function*/
Brass::Brass(const std::string & s, long an, double bal) : AcctABC(s, an, bal)
{

}

Brass::Brass(const Brass& orig) : AcctABC(orig)
{

}

Brass::~Brass()
{

}

/*overloaded operator function*/
Brass& Brass::operator=(const Brass& orig)
{
    if (this == &orig)
        return *this;
    AcctABC::operator=(orig);
    return *this;
}

void Brass::withdraw(double amt)
{
    if (amt < 0)
        std::cout << "Withdrawal amount must be positive; " << " withdraw cancelled.\n";
    else if (amt <= balance())
        AcctABC::withdraw(amt);
    else
        std::cout << "Withdrawal amount of $" << amt << "exceeds your balance.\n" << "Withdrawal cancelled.\n";
}

/// 这里的viewAcct如果加入const在之后, 那么就会编译报错
/// 将‘const Brass’作为‘const std::string& AcctABC::fullName()’的‘this’实参时丢弃了类型限定
void Brass::viewAcct()const
{
    Formatting f = setFormat();
    /// 这里 fullName() 函数一开始定义的时候没有加尾部const, 不能保证fullName()内部不修改值
    std::cout << "Brass Client: " << this->fullName() << std::endl;
    std::cout << "Account Number: " << acctNum() << std::endl;
    std::cout << "Balance: $" << balance() << std::endl;
    restore(f);
}


/*public interface*/
