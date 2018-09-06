/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        ATMScene.h
 * Author:      xuwei.huang
 * Describe:    declaration of ATMScene
 *              
 * Created on   2017年6月21日, 下午7:04
 */

#ifndef ATMSCENE_H
#define ATMSCENE_H

#include <iostream>

#include "LineQueue.h"
#include "Customer.h"

class ATMScene
{
private:

    enum
    {
        MIN_PER_HR = 60
    };
private:
    int m_max_len; /// 队列长度限制
    double m_hour; /// 模拟的小时数
    int m_per_hour_peo; /// 每小时的平均人数

    int m_wait_time; /// 模拟用户操作时间 -- 当前客户剩余的操作时间

    int m_min_per_cust; /// 平均每几分钟来一个客人
    int m_all_people; /// 客户总人数
    int m_accept_peo; /// 接待总人数
    int m_server_peo; /// 服务总人数
    int m_reject_peo; /// 被拒绝的总人数
    double m_wait_time_all; /// 客户总计等待时间
    double m_per_wait_time; /// 客户平均等待时间
    double m_line_len_all; /// 队列累计长度
    double m_per_line_len; /// 队列平均长度


private:
    /// 不做实现, 设为私有成员, 不允许外界调用
    ATMScene(const ATMScene& orig);
    ATMScene& operator=(const ATMScene& orig);
    bool newCustomer(double x);
    bool getReady();
    bool getResult();
    bool report();
    
public:
    ATMScene();
    virtual ~ATMScene();

public:

    friend std::ostream & operator<<(std::ostream & os, const ATMScene& orig);
    friend std::istream & operator>>(std::istream & is, ATMScene& orig);

public:
    bool setStartCon(int len, int hour, int perPeo);
    bool run();

};

#endif /* ATMSCENE_H */

