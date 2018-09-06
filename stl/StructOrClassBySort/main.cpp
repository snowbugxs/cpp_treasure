/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年6月18日, 下午7:30
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "SubQualification.h"

using namespace std;

bool comparision(const SubQualification & a, const SubQualification & b)
{
    return a < b;
}

/**
 * main
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{
    vector<SubQualification> subQuaVector;
    SubQualification test1("100001", "200001", "300001", 20);
    subQuaVector.push_back(test1);
    SubQualification test2("100001", "200001", "300001", 200);
    subQuaVector.push_back(test2);
    SubQualification test3("100002", "200002", "300002", 30);
    subQuaVector.push_back(test3);
    SubQualification test4("100002", "200001", "300005", 50);
    subQuaVector.push_back(test4);
    SubQualification test5("100003", "200005", "300002", 150);
    subQuaVector.push_back(test5);
    SubQualification test6("100003", "200005", "300002", 150);
    subQuaVector.push_back(test6);
    vector<SubQualification>::iterator iter = subQuaVector.begin();
    for(iter; iter != subQuaVector.end(); ++iter)
    {
        cout << *iter;
    }
    cout << endl;

    sort(subQuaVector.begin(), subQuaVector.end(), comparision);
    for(iter = subQuaVector.begin(); iter != subQuaVector.end(); ++iter)
    {
        cout << *iter;
    }

    /// 使用set来装载自定义的类对象, 必须提供重载的比较函数, 不然无法使用. set会自动排序, 而排序就必须得有排序的比较函数
    /// 使用set来检查是否有重复元素, 使用返回值来判定(也可以使用.size()来判定, 不过多做了一步, 浪费了性能)
    set<SubQualification> subSet;
    pair < set<SubQualification>::iterator, bool> pairRe = subSet.insert(test1);
    pairRe = subSet.insert(test5);
    pairRe = subSet.insert(test6);
    if(false == pairRe.second)
    {
        cout << "插入失败" << endl;
    }


    return 0;
}

