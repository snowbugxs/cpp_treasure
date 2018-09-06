/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        BaseDMA.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of BaseDMA
 *              
 * Created on   2017年7月3日, 下午7:17
 */

#include <string.h>

#include "BaseDMA.h"

/*static member here*/


/*methods for subclass*/

/*construction function*/
BaseDMA::BaseDMA(const char * l, int r)
{
    m_label = new char[strlen(l) + 1];
    strcpy(m_label, l);
    m_rating = r;
}

BaseDMA::BaseDMA(const BaseDMA& orig)
{
    m_label = new char[strlen(orig.m_label) + 1];
    strcpy(m_label, orig.m_label);
    m_rating = orig.m_rating;
}

BaseDMA::~BaseDMA()
{
    delete m_label;
}

/*overloaded operator function*/
BaseDMA& BaseDMA::operator=(const BaseDMA& orig)
{
    if(this == &orig)
        return *this;
    delete [] m_label;
    m_label = new char[strlen(orig.m_label) + 1];
    strcpy(m_label, orig.m_label);
    m_rating = orig.m_rating;
    return * this;
}

std::ostream & operator<<(std::ostream & os, const BaseDMA& orig)
{
    os << "Label: " << orig.m_label << std::endl;
    os << "Rating: " << orig.m_rating << std::endl;
    return os;
}


/*public interface*/
