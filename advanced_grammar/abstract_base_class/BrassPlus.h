/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        BrassPlus.h
 * Author:      xuwei.huang
 * Describe:    declaration of BrassPlus
 *              
 * Created on   2017年7月4日, 上午10:51
 */

#ifndef BRASSPLUS_H
#define BRASSPLUS_H

#include <iostream>
#include <string>

#include "AcctABC.h"
#include "Brass.h"

class BrassPlus : public AcctABC
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    double m_maxLoan;
    double m_rate;
    double m_owesBank;

    /*methods for subclass*/
protected:

    /*construction function*/
public:
    BrassPlus(const std::string & s = "Nullbody", long an = -1, double bal = 0.0, double ml = 500, double r = 0.10);
    BrassPlus(const Brass & ba, double ml = 500, double r = 0.1);
    BrassPlus(const BrassPlus& orig);
    virtual ~BrassPlus();

    /*overloaded operator function*/
public:
    BrassPlus& operator=(const BrassPlus& orig);


    /*public interface*/
public:
    virtual void withdraw(double amt);
    virtual void viewAcct()const;

};

#endif /* BRASSPLUS_H */

