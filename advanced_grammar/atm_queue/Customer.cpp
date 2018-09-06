/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        Customer.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of Customer
 *              
 * Created on   2017年6月21日, 上午10:00
 */


#include "Customer.h"


/// 每个人的操作时间 1~3分钟之内
RandTime Customer::randProcess(3);

Customer::Customer()
{
}

Customer::Customer(int arrive, int processTime) : m_arrive(arrive)
{
    randProcess.resetRand(processTime);
    setProcessTime();
}

Customer::Customer(const Customer& orig)
{
    m_arrive = orig.m_arrive;
    m_process_time = orig.m_process_time;
}

Customer::~Customer()
{

}

Customer& Customer::operator=(const Customer& orig)
{
    if(&orig == this)
        return *this;
    m_arrive = orig.m_arrive;
    m_process_time = orig.m_process_time;
    return *this;
}

std::ostream & operator<<(std::ostream & os, const Customer& orig)
{
    os << "到达时间 :  " << orig.m_arrive << "处理时间 :  " << orig.m_process_time << "\n";
    return os;
}

bool Customer::setTime(int arrTime, int pInterval)
{
    m_arrive = arrTime;
    randProcess.resetRand(pInterval);
    setProcessTime();
    return true;
}

int Customer::getArrTime()
{
    return m_arrive;
}

int Customer::getProTime()
{
    return m_process_time;
}

bool Customer::setProcessTime()
{
    m_process_time = randProcess.getNum();
    return true;
}

