/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        BaseDMA.h
 * Author:      xuwei.huang
 * Describe:    declaration of BaseDMA
 *              
 * Created on   2017年7月3日, 下午7:17
 */

#ifndef BASEDMA_H
#define BASEDMA_H

#include <iostream>

class BaseDMA
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    char * m_label;
    int m_rating;

    /*methods for subclass*/
protected:

    /*construction function*/
public:
    BaseDMA(const char * l = "null", int r = 0);
    BaseDMA(const BaseDMA& orig);
    virtual ~BaseDMA();

    /*overloaded operator function*/
public:
    BaseDMA& operator=(const BaseDMA& orig);

    friend std::ostream & operator<<(std::ostream & os, const BaseDMA& orig);

    /*public interface*/
public:

};

#endif /* BASEDMA_H */

