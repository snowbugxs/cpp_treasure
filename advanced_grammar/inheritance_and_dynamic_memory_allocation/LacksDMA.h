/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        LacksDMA.h
 * Author:      xuwei.huang
 * Describe:    declaration of LacksDMA
 *              derived class without DMA
 *              uses implicit copy constructor
 *              uses implicit assignment operator              
 * Created on   2017年7月3日, 下午7:43
 */

#ifndef LACKSDMA_H
#define LACKSDMA_H

#include "BaseDMA.h"
#include <iostream>
#include <cstring>

class LacksDMA : public BaseDMA
{
    /*predefine here*/ /*static member shoud be palced front*/

    /*private data member*/
private:
    enum { COL_LEN = 40};
    char m_color[COL_LEN];

    /*methods for subclass*/
protected:

    /*construction function*/
public:
    LacksDMA(const char * c = "blank", const char * l = "null", int r = 0);
    LacksDMA(const char * c, const BaseDMA & orig);
    LacksDMA(const LacksDMA& orig);
    virtual ~LacksDMA();

    /*overloaded operator function*/
public:
    LacksDMA& operator=(const LacksDMA& orig);

    friend std::ostream & operator<<(std::ostream & os, const LacksDMA& orig);

    /*public interface*/
public:

};

#endif /* LACKSDMA_H */

