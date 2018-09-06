/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: hxw <ageofempires_asia>
 *
 * Created on 2017年4月12日, 下午12:54
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    vector<int> intVector;
    list<int> intList;
    vector<int>::iterator iterVector = intVector.begin();
    /** 结论:
     * 定义迭代器初始化为空vector.begin()时,编译通过,语句执行通过;
     * 但如果对空的迭代器使用解引用,就会出错:Segmentation error
     * 
     * 定义迭代器初始化为空list.begin()时,编译通过,语句执行通过;
     * 使用这个空迭代器解引用,不会出错,值为0
     * 
     * 具体原因得看源码实现了:**/
//    cout << *iterVector <<"Null iterVector"<<endl;
    cout <<"Null vector"<<endl;
    for(vector<int>::iterator iter = intVector.begin(); iter != intVector.end(); iter ++)
    {
        cout << "Null Vector . begin()" << endl;
    }
    
    cout <<"Null vector"<<endl;
    list<int>::iterator iterList = intList.begin();
    cout << *iterList <<"      Null iterList"<<endl;
    for(list<int>::iterator iter = intList.begin(); iter != intList.end(); iter ++)
    {
        cout << "Null List . begin()" << endl;
    }
    cout <<"Null list"<<endl;
    
    

    return 0;
}

