/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        ATMScene.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of ATMScene
 *              
 * Created on   2017年6月21日, 下午7:04
 */

#include "ATMScene.h"
#include <ctime>
#include <cstdlib>

ATMScene::ATMScene(const ATMScene& orig)
{

}

ATMScene& ATMScene::operator=(const ATMScene& orig)
{

}

bool ATMScene::newCustomer(double x)
{
    /// 这样使用, 不知道为什么 会有一半的纪律小于1, 真是奇怪
    int yy = std::rand() * x / RAND_MAX;
    std::cout << yy << "  ";
    return( yy < 1);

    /// 看来不是这个原因, 应该是队伍满了, 从而导致的人出去了.
    //    int xx = rand();
    //    std:: cout << xx % (int(x)+1) << "  ";
    //    return (xx % (int(x)+1) <= 1);
}

bool ATMScene::getReady()
{
    m_min_per_cust = MIN_PER_HR / m_per_hour_peo;
    return true;
}

bool ATMScene::getResult()
{
    m_per_wait_time = m_wait_time_all / m_server_peo;
    m_per_line_len = m_line_len_all / (m_hour * MIN_PER_HR);
    return true;
}

bool ATMScene::report()
{
    std::cout << "\n";
    std::cout << "客户总人数:      " << m_all_people << std::endl;
    std::cout << "接待总人数:      " << m_accept_peo << std::endl;
    std::cout << "服务总人数:      " << m_server_peo << std::endl;
    std::cout << "拒绝总人数:      " << m_reject_peo << std::endl;
    std::cout << "队列平均长度:    " << m_per_line_len << std::endl;
    std::cout << "客户平均等待:    " << m_per_wait_time << std::endl;
    std::cout << "\n";

    return true;
}

ATMScene::ATMScene()
{
    m_max_len = 10;
    m_hour = 3;
    m_per_hour_peo = 10;

    m_wait_time = 0;
    m_min_per_cust = 0;

    m_all_people = 0;
    m_accept_peo = 0;
    m_server_peo = 0;
    m_reject_peo = 0;
    m_wait_time_all = 0;
    m_per_wait_time = 0;
    m_line_len_all = 0;
    m_per_line_len = 0;

    /// 这样试行不行啊? 这样试验是可以的, 但是RAND_MAX的宏不行
    std::srand(time(NULL));
}

ATMScene::~ATMScene()
{

}

std::ostream & operator<<(std::ostream & os, const ATMScene& orig)
{
    os << "\n";
    os << "客户总人数:      " << orig.m_all_people << std::endl;
    os << "接待总人数:      " << orig.m_accept_peo << std::endl;
    os << "服务总人数:      " << orig.m_server_peo << std::endl;
    os << "拒绝总人数:      " << orig.m_reject_peo << std::endl;
    os << "队列平均长度:    " << orig.m_per_line_len << std::endl;
    os << "客户平均等待:    " << orig.m_per_wait_time << std::endl;
    os << "\n";

    return os;
}

std::istream & operator>>(std::istream & is, ATMScene& orig)
{
    std::cout << "请输入队列长度限制: \n";
    is >> orig.m_max_len;
    if(!is)
    {
        orig.m_max_len = 10;
        while(is && is.get() != '\n')
            continue;
    }
    std::cout << "请输入模拟小时数: \n";
    is >> orig.m_hour;
    if(!is)
    {
        orig.m_hour = 3;
        while(is && is.get() != '\n')
            continue;
    }
    std::cout << "请输入每小时平均人数: \n";
    is >> orig.m_per_hour_peo;
    if(!is)
    {
        orig.m_per_hour_peo = 10;
        while(is && is.get() != '\n')
            continue;
    }

    return is;
}

bool ATMScene::run()
{
    getReady();

    LineQueue line(m_max_len);
    ::Item item;

    for(int nowTime = 0; nowTime < m_hour * MIN_PER_HR; ++nowTime)
    {
        if(newCustomer(m_min_per_cust))
        {
            m_all_people++;
            if(line.isFull())
                m_reject_peo++;
            else
            {
                m_accept_peo++;
                item.setTime(nowTime);
                std::cout << "test" << item.getProTime() << std::endl;
                /// 可不可以设计为使用 外来的对象来插入队列, line 不去重新分配空间??
                line.enQueue(item);
            }
            /// 这里出现了巨大失误啊, 这怎么能放在 if(newCustomer(m_min_per_cust)) 中, 时间计数应该每次循环都回去减少, 而这里尽然忽略了
            /// 代码逻辑的错误, 要仔细, 困在这里的2天时间真是浪费了
            //            if(m_wait_time <= 0 && !line.isEmpty())
            //            {
            //                line.deQueue(item);
            //                m_wait_time = item.getProTime();
            ////                m_wait_time = 2;
            //
            //                m_wait_time_all = nowTime - item.getArrTime();
            //                m_server_peo++;
            //            }
            //            if(m_wait_time > 0)
            //                m_wait_time--;
            //            m_line_len_all += line.queueCount();
        }
        if(m_wait_time <= 0 && !line.isEmpty())
        {
            line.deQueue(item);
            m_wait_time = item.getProTime();
            m_wait_time_all += nowTime - item.getArrTime();
            m_server_peo++;
        }
        if(m_wait_time > 0)
            m_wait_time--;
        m_line_len_all += line.queueCount();
    }

    getResult();
    report();
}

bool ATMScene::setStartCon(int len, int hour, int perPeo)
{
    m_max_len = len;
    m_hour = hour;
    m_per_hour_peo = perPeo;
    return true;
}



