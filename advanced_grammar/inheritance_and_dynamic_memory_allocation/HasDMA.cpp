/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        HasDMA.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of HasDMA
 *              derived class with DMA
 *              need provide explicit copy constructor
 *              need provide explicit assignment operator
 * Created on   2017年7月3日, 下午8:15
 */

#include "HasDMA.h"

/*static member here*/


/*methods for subclass*/

/*construction function*/
HasDMA::HasDMA(const char * s, const char * l, int r) : BaseDMA(l, r)
{
    m_style = new char[strlen(s) + 1];
    strcpy(m_style, s);
}

HasDMA::HasDMA(const char * s, const BaseDMA & orig) : BaseDMA(orig)
{
    m_style = new char[strlen(s) + 1];
    strcpy(m_style, s);
}

HasDMA::HasDMA(const HasDMA& orig) : BaseDMA(orig)
{
    m_style = new char[strlen(orig.m_style) + 1];
    strcpy(m_style, orig.m_style);
}

HasDMA::~HasDMA()
{
    delete [] m_style;
}

/*overloaded operator function*/
HasDMA& HasDMA::operator=(const HasDMA& orig)
{
    if(this == &orig)
        return * this;
    delete [] m_style;
    BaseDMA::operator =(orig);
    m_style = new char[strlen(orig.m_style) + 1];
    strcpy(m_style, orig.m_style);
    return * this;
}

std::ostream & operator<<(std::ostream & os, const HasDMA& orig)
{
    os << "Style: " << orig.m_style << std::endl;
    ///     os << (const BaseDMA &) orig;
    os << (const BaseDMA) orig;
    return os;
}


/*public interface*/
