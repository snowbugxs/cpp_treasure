/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubQualification.h
 * Author: xuwei.huang
 *
 * Created on 2017年6月18日, 下午7:31
 */

#ifndef SUBQUALIFICATION_H
#define SUBQUALIFICATION_H
#include <iostream>
#include <string>


class SubQualification
{
public:
    SubQualification();
    SubQualification(const std::string &id, const std::string & name, const std::string & addr, const int volume);
    SubQualification(const SubQualification& orig);
    virtual ~SubQualification();
public:
    SubQualification operator=(const SubQualification & orig);
    bool operator<( const SubQualification & b) const;
    friend std::ostream & operator<<(std::ostream & os, const SubQualification & object);
    
private:
    std::string m_user_id;
    std::string m_user_name;
    std::string m_user_addr;
    int m_volume;
    
};

#endif /* SUBQUALIFICATION_H */

