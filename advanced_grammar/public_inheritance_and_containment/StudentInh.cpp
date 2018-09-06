/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        StudentInh.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of StudentInh
 *              
 * Created on   2017年7月4日, 下午8:20
 */

#include "StudentInh.h"

/*static member here*/

/*methods for subclass*/
std::ostream & StudentInh::arrayOut(std::ostream & os) const
{
    int i  = 0;
    int limit = ArrayDb::size();
    if(limit > 0)
    {
        for (i = 0; i < limit; ++i)
        {
            os << ArrayDb::operator[](i) << " ";
            if(i%5 == 4)
                os << std::endl;
        }
        if(i % 5 != 0)
            os << std::endl;
    }
    else
        os << "Empty array";
    
    return os;
}

/*construction function*/
/// 可以使用强制转换
StudentInh::StudentInh(const StudentInh& orig): std::string(/*(const std::string)*/orig), ArrayDb(/*(ArrayDb)*/ orig)
{

}

/*overloaded operator function*/
StudentInh& StudentInh::operator=(const StudentInh& orig)
{
    if(this == &orig)
        return *this;
    std::string::operator=(orig);
    ArrayDb::operator=(orig);
    return *this;
}

/// output

std::ostream & operator<<(std::ostream & os, const StudentInh& orig)
{
    os << "Scores for " << (const std::string &) orig << ": \n";
    orig.arrayOut(os);
    return os;
}

/// input

std::istream & operator>>(std::istream & is, StudentInh& orig)
{
    is >> (std::string &)orig;
    return is;
}

std::istream & getline(std::istream & is, StudentInh & orig)
{
    getline(is, (std::string &)orig);
    return is;
}

/*public interface*/
double StudentInh::average() const
{
    if (ArrayDb::size() > 0)
        return ArrayDb::sum() / ArrayDb::size();
    else
        return 0;
}

const std::string & StudentInh::name() const
{
    return(const std::string &) * this;
}

double & StudentInh::operator[](int i)
{
    return ArrayDb::operator[](i);
}

double StudentInh::operator[](int i) const
{
    return ArrayDb::operator[](i);
}
