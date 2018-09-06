/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        GameStatus.h
 * Author:      xuwei.huang
 * Describe:    declaration of GameStatus
 *              
 * Created on   2017年6月20日, 上午11:05
 */

#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include <iostream>
#include <string>

class GameStatus
{
public:
    GameStatus();
    GameStatus(const std::string name, const std::string comp, const std::string date, const double sales);
    GameStatus(const GameStatus& orig);
    virtual ~GameStatus();

public:
    /// 不能这样定义为一个转换为string类的转换函数
    //    std::string operator=();
    
    /// 应该这样定义 转换为string 类的转换函数
    operator std::string();
    operator double();

    GameStatus& operator=(const GameStatus& orig);
    bool operator<(const GameStatus & b) const;

    friend std::ostream & operator<<(std::ostream & os, const GameStatus& orig);
    friend std::istream & operator>>(std::istream & is, GameStatus& orig);

private:
    std::string m_name;
    std::string m_comp;
    std::string m_date;
    double m_sales;

};

#endif /* GAMESTATUS_H */

