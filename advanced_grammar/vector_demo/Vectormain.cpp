/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vectormain.cpp
 * Author: xuwei.huang
 * randwalk -- using the Vector class
 * Created on 2017年6月14日, 下午7:50
 */

#include <iostream>
#include <cstdlib>      /// rand(),  srand(), prototypes
#include <ctime>        /// time(), prototype
#include "Vector.h"

/*
 * 
 */
int main(int argc, char** argv)
{
    using namespace std;
    /// Vector is a class , can not use namespace VECTOR::Vector to declare it
    using VECTOR::Vector;

    srand(time(NULL)); /// seed random-number generator
    double direction;
    Vector step;
    Vector result(0, 0);
    unsigned long steps = 0;
    double target;
    double stepLen;

    cout << "Enter target distance (q to quit) : ";
    while(cin >> target)
    {
        cout << "Enter each step length:";
        if(!(cin >> stepLen))
        {
            break;
        }
        while(result.getY() < target)
        {
            direction = rand() % 360;
            step.reset(stepLen, direction, Vector::POL);
            result = result + step;
            ++steps;
        }
        cout << "After " << steps << " steps, the subject has the following loaction :" << endl;
        cout << result << endl;
        result.setPolMode();
        cout << " or \n" << result << endl;

        steps = 0;
        result.reset(0, 0);
        cout << "Enter target distance (q to quit) : ";
    }

    cout << "Bye" << endl;
    cin.clear();
    while(cin.get() != '\n')
    {
        continue;
    }

    return 0;
}

