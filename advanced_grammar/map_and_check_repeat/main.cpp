/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    STL中的组件是拿来进行组合复用的，不是拿来继承的..
 *              C++模板的分开编译问题..
 * Created on   2017年6月19日, 下午7:01
 */

#include <iostream>
#include "GameStatus.h"
#include "PackageSet.hpp"

#include <set>
#include <map>

using namespace std;

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv)
{

    GameStatus game1("lol", "tencent", "20100403", 88888888);
    GameStatus game2("king of glory", "tencent", "20130506", 43532664);
    GameStatus game3("lol", "tencent", "20100403", 88888888);


    ////////////
    cout << "Below is set " << endl;

    PackageSet<GameStatus> gameSet;
    pair < PackageSet<GameStatus>::iterator, bool> isTheSame;
    gameSet.insert(game1);
    gameSet.insert(game2);
    isTheSame = gameSet.insert(game3);
    isTheSame = gameSet.insert(game3);
    if(false == isTheSame.second)
    {
        cout << "相同元素插入失败" << endl;
    }
    else
    {
        cout << "相同元素插入成功" << endl;
    }
    cout << "set size: " << gameSet.size() << endl;


    ////////////
    cout << endl << "Below is multi set" << endl;

    multiset<GameStatus> gameMultiSet;
    multiset<GameStatus>::iterator isGood;
    isGood = gameMultiSet.insert(game1);
    isGood = gameMultiSet.insert(game2);
    isGood = gameMultiSet.insert(game3);

    /// 这个迭代器如何使用呢? 算了这个先不纠结了
    //    string str = *isGood;

    /// multiset的insert返回值怎么使用??, 能用于判断是否插入成功吗?

    //    double thisnumber = isGood->operator double();
    //    cout << thisnumber << endl;
    //    if(NULL == *isGood)
    //    {
    //        cout << "相同元素插入失败" << endl;
    //    }
    //    else
    //    {
    //        cout << "相同元素插入成功" << endl;
    //    }
    cout << "multiset size: " << gameMultiSet.size() << endl;


    ////////////
    cout << endl << "Below is Map test" << endl;

    map<string, double> gameMap;
    string gameStr1 = game1;
    double num1 = game1;
    string gameStr2 = game2;
    double num2 = game2;
    string gameStr3 = game3;
    double num3 = game3;
    typedef pair<string, double> pairSB;
    typedef pair < map<string, double>::iterator, bool> pairIB;
    pairIB isSuccess;
    isSuccess = gameMap.insert(pairSB(gameStr1, num1));
    gameMap[gameStr2] = num2;
    cout << "gameMap size : " << gameMap.size() << endl;
    isSuccess = gameMap.insert(pairSB(gameStr3, num3));
    if(false == isSuccess.second)
    {
        cout << "相同元素插入失败" << endl;
    }
    else
    {
        cout << "相同元素插入成功" << endl;
    }
    if(false == isSuccess.second)
    {
        cout << "插入失败, 那就叠加值" << endl;
        cout << "原来的值:  " << gameMap.at(gameStr3) << endl;
        gameMap.find(gameStr3)->second += num3;
        cout << "叠加后值:  " << gameMap.at(gameStr3) << endl;
    }
    cout << "gameMap size : " << gameMap.size() << endl;


    ////////////
    cout << endl << "Below is multimap test" << endl;
    multimap<string, double> gameMultiMap;
    gameMultiMap.insert(pair<string, double>(gameStr1, num1));
    /// multimap 无法使用下标表示, 因为键值不唯一
    //    gameMultiMap[gameStr2] = num2;
    gameMultiMap.insert(pair<string, double>(gameStr2, num2));
    gameMultiMap.insert(pair<string, double>(gameStr3, num3));

    cout << "gameMultiMap size : " << gameMultiMap.size() << endl;



    return 0;
}

