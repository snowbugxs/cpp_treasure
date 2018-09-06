/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        GameStatus.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of GameStatus
 *              
 * Created on   2017年6月20日, 上午11:05
 */

#include "GameStatus.h"

GameStatus::GameStatus()
{
    m_name = "corssfire";
    m_comp = "tencent";
    m_date = "20070502";
    m_sales = 10000000;
}

GameStatus::GameStatus(const std::string name, const std::string comp, const std::string date, const double sales) : m_name(name), m_comp(comp), m_date(date), m_sales(sales)
{

}

GameStatus::GameStatus(const GameStatus& orig)
{
    m_name = orig.m_name;
    m_comp = orig.m_comp;
    m_date = orig.m_date;
    m_sales = orig.m_sales;
}

GameStatus::~GameStatus()
{

}

/// 不能这样定义为一个转换为string类的转换函数
//std::string GameStatus::operator=()
//{
//    std::string str;
//    str = m_name + m_comp + m_date;
//    return str;
//}

GameStatus::operator std::string()
{
    std::string str;
    str = m_name + m_comp + m_date;
    return str;
}

GameStatus::operator double()
{
    return m_sales;
}

GameStatus& GameStatus::operator=(const GameStatus& orig)
{
    if(&orig == this)
        return *this;
    m_name = orig.m_name;
    m_comp = orig.m_comp;
    m_date = orig.m_date;
    m_sales = orig.m_sales;
    return *this;
}

/// 注意算法问题, 相等的才向后进行比较, 小于的直接返回true, 大于直接false

bool GameStatus::operator<(const GameStatus & b) const
{
    if(m_name < b.m_name)
        return true;
    else if(m_name == b.m_name)
    {
        if(m_comp < b.m_comp)
            return true;
        else if(m_comp == b.m_comp)
        {
            if(m_date < b.m_date)
                return true;
            else if(m_date == b.m_date)
            {
                if(m_sales < b.m_sales)
                    return true;
            }
        }
    }
    return false;
}

std::ostream & operator<<(std::ostream & os, const GameStatus & orig)
{
    os << "GameName:  " << orig.m_name;
    os << "      Company:  " << orig.m_comp;
    os << "      Date:  " << orig.m_date;
    os << "      Sales:  " << orig.m_sales;
    os << std::endl;
}

std::istream & operator>>(std::istream & is, GameStatus & orig)
{
    std::cout << "game name: \n";
    is >> orig.m_name;
    std::cout << "game company: \n";
    is >> orig.m_comp;
    std::cout << "release date: \n";
    is >> orig.m_date;
    std::cout << "sell money: \n";
    is >> orig.m_sales;
    return is;
}

