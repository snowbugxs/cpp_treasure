/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        HasDMA.h
 * Author:      xuwei.huang
 * Describe:    declaration of HasDMA
 *              derived class with DMA
 *              need provide explicit copy constructor
 *              need provide explicit assignment operator             
 * Created on   2017年7月3日, 下午8:15
 */

#ifndef HASDMA_H
#define HASDMA_H
#include "BaseDMA.h"
#include <iostream>
#include <cstring>

class HasDMA : public BaseDMA
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    char * m_style;
    
    /*methods for subclass*/
protected:

    /*construction function*/
public:
    HasDMA(const char * s = "none", const char * l = "null", int r = 0);
    HasDMA(const char * s, const BaseDMA & orig);
    HasDMA(const HasDMA& orig);
    virtual ~HasDMA();

    /*overloaded operator function*/
public:
    HasDMA& operator=(const HasDMA& orig);

    friend std::ostream & operator<<(std::ostream & os, const HasDMA& orig);

    /*public interface*/
public:

};

#endif /* HASDMA_H */

