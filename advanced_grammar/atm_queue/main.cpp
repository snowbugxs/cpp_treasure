/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 *              为什么总是有一半的人被拒绝服务, 队伍排满了, 为什么, 3个参数不管怎么变, 总是有一半来的人被拒绝服务????
 *              代码中的逻辑出现了巨大问题, 应该警醒, 好好的理解了源码之后再去自己实现, 不然给自己挖坑都挑不出来
 *              注意逻辑错误, 函数调用的逻辑自己要搞清楚
 *              分步骤封装, 检查无误之后, 在去下一级检查
 *              计算随机数的时候, rand()出来的都是整数, 如果*整数/整数, 那就是整除, 如果中间有个double, 那么都会转换为double类型, 结果大不相同
 *              m_num = std::rand() * double(m_rand) / RAND_MAX + 1;
 * Created on   2017年6月21日, 上午9:30
 */

#include <iostream>
#include "ATMScene.h"
#include "RandTime.h"

using namespace std;

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv)
{
    /// 可以这样使用 随机函数
//        RandTime time1;
//        time1.resetRand(8);
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;
//        cout << time1.getNum() << endl;

        ATMScene item;
        item.setStartCon(10, 100, 30);
        item.run();


    return 0;
}

