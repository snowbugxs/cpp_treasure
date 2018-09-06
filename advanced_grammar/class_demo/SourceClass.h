/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SourceClass.h
 * Author: xuwei.huang
 *
 * Created on 2017年5月16日, 上午10:45
 */

#ifndef SOURCECLASS_H
#define SOURCECLASS_H

class SourceClass
{
public:
    SourceClass();
    SourceClass(int num);
    SourceClass(const SourceClass& orig);
    virtual ~SourceClass();
    void printNum();
private:
    int m_num;

};

#endif /* SOURCECLASS_H */

