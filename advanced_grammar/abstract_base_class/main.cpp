/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2017年7月4日, 上午9:00
 */

#include <iostream>
#include <string>
#include "AcctABC.h"
#include "Brass.h"
#include "BrassPlus.h"

const int CLIENTS = 4;

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv)
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::string;
    
    AcctABC * pClients[CLIENTS];
    string temp;
    long tempNum;
    double tempBal;
    char kind;
    for(int i = 0; i < CLIENTS; ++i)
    {
        cout << "Enter client's name: ";
        getline(cin, temp);
        cout << "Enter clients's account number: ";
        cin >> tempNum;
        cout << "Enter opening balance: $";
        cin >> tempBal;
        cout << "Enter 1 for Brass Account or 2 for BrassPlus Account: ";
        while(cin >> kind && (kind != '1' && kind != '2'))
            cout << "Enter either 1 or 2: ";
        if('1' == kind)
            pClients[i] = new Brass(temp, tempNum, tempBal);
        else
        {
            double tmax, trate;
            cout << "Enter the overdraft limit: $";
            cin >> tmax;
            cout << "Enter the interest rate as a decimal fraction: ";
            cin >> trate;
            pClients[i] = new BrassPlus(temp, tempNum, tempBal, tmax, trate);
        }
        while (cin.get() != '\n')
            continue;
    }
    cout << "\n\n";
    
    for(int i = 0; i < CLIENTS; ++i)
    {
        pClients[i]->viewAcct();
        cout << endl;
    }
    
    for(int i = 0; i < CLIENTS; ++i)
    {
        delete pClients[i];
    }
    
    cout << "Done. \n";
    
    return 0;
}

