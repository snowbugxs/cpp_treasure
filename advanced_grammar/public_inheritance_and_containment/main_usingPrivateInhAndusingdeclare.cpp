/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    testmain
 *              compile with StudentInh.cpp
 * Created on   2017年7月4日, 下午4:15
 */

#include <iostream>
#include "StudentInh.h"

using std::cin;
using std::cout;
using std::endl;

void set(StudentInh & sc, int n);
const int pupils = 3;
const int quizzes = 5;

/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
int main(int argc, char** argv)
{
    StudentInh ada[pupils] = {StudentInh(quizzes), StudentInh(quizzes), StudentInh(quizzes)};

    int i = 0;
    for (i = 0; i < pupils; ++i)
        set(ada[i], quizzes);
    cout << "\nStudent List:\n";
    for (i = 0; i < pupils; ++i)
        cout << ada[i].name() << endl;
    cout << "\nResult:\n";
    for (i = 0; i < pupils; ++i)
    {
        cout << endl << ada[i];
        cout << "max    : " << ada[i].max() << endl;
        cout << "min    : " << ada[i].min() << endl;
        cout << "average: " << ada[i].average() << endl;
    }
    cout << "Done\n";

    return 0;
}

void set(StudentInh & sc, int n)
{
    cout << "Please enter the student's name: \n";
    getline(cin, sc);
    cout << "Please enter " << n << " quiz scores: \n";
    for (int i = 0; i < n; ++i)
    {
        cin >> sc[i];
    }
    while (cin.get() != '\n')
        continue;
}
