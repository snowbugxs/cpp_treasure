/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年6月17日, 下午7:09
 */
#include <iostream>
#include "String.h"
#include <ctime>
#include <cstdlib>

const int ArSize = 10;
const int MaxLen = 81;

/*
 * 
 */

int main(int argc, char** argv)
{

    //    using std::cout;
    //    using std::cin;
    //    using std::endl;
    using namespace std;
    String name;
    cout << "Hi, what's your name? \n >> ";
    cin >> name;

    cout << name << " , Please enter up to " << ArSize << " short saying <empty line to quit>: \n";
    String sayings[ArSize];
    char temp[MaxLen];
    int i = 0;
    for(i = 0; i < ArSize; ++i)
    {
        cout << i + 1 << " : ";
        /// cin.get(temp, MaxLen) 读取规定长度内容, 遇到换行符停止, 但是不会删除换行符, 残留在输入缓存中
        /// cin.get() 从输入缓存流中取出任意一个字符, 缓存流中会删除这个字符, 可以残留的换行符
        cin.get(temp, MaxLen);
        while(cin && cin.get() != '\n')
            continue;
        /// 如果是旧标准的get函数, 使用  if(!cin || temp[0] == '\0')
        /// 检查是否是空行
        if(!cin && cin.get() != '\n')
            break;
        else
            sayings[i] = temp;
    }

    int total = i;
    if(total > 0)
    {
        cout << "Here are your sayings:\n";
        for(i = 0; i < total; ++i)
        {
            cout << sayings[i][0] << ": " << sayings[i] << endl;
        }

        int shortest = 0;
        int first = 0;
        for(i = 1; i < total; ++i)
        {
            if(sayings[i].length() < sayings[shortest].length())
                shortest = i;
            if(sayings[i] < sayings[first])
            {
                first = i;
            }
        }
        cout << "Shortest saying: \n" << sayings[shortest] << endl;
        cout << "First alphabetically: \n" << sayings[first] << endl;
        cout << "This program used " << String::HowMany() << " String objects. \n";
        cout << "Bye" << endl;
        
        /// use new to create, initialize new String object
        srand(time(0));
        int choice = rand()%total;
        String * favorite = new String(sayings[choice]);
        cout << "My favorite saying: \n" << *favorite << endl;
        delete favorite;
        
    }
    else
        cout << "No input !  \nBye.\n";

    return 0;
}


