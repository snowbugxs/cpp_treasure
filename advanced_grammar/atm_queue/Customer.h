/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        Customer.h
 * Author:      xuwei.huang
 * Describe:    declaration of Customer
 *              
 * Created on   2017年6月21日, 上午10:00
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>

#include "RandTime.h"

class Customer
{
public:
    Customer();
    Customer(int arrive, int processTime);
    Customer(const Customer& orig);
    virtual ~Customer();

public:
    Customer& operator=(const Customer& orig);

    friend std::ostream & operator<<(std::ostream & os, const Customer& orig);

public:
    bool setTime(int arrTime, int pInterval = 3);
    int getArrTime();
    int getProTime();

private:
    bool setProcessTime();

private:
    static RandTime randProcess;

    int m_arrive; /// arrival time for customer
    int m_process_time; /// processing time for customer

};

#endif /* CUSTOMER_H */

