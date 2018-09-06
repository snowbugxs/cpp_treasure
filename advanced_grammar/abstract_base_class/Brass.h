/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        Brass.h
 * Author:      xuwei.huang
 * Describe:    declaration of Brass
 *              
 * Created on   2017年7月4日, 上午10:13
 */

#ifndef BRASS_H
#define BRASS_H

#include <iostream>
#include "AcctABC.h"

class Brass : public AcctABC
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:

    /*methods for subclass*/
protected:

    /*construction function*/
public:
    Brass(const std::string & s = "Nullbody", long an = -1, double bal = 0.0);
    Brass(const Brass& orig);
    virtual ~Brass();

    /*overloaded operator function*/
public:
    Brass& operator=(const Brass& orig);

    /*public interface*/
public:
    virtual void withdraw(double amt);
    virtual void viewAcct()const;

};

#endif /* BRASS_H */

