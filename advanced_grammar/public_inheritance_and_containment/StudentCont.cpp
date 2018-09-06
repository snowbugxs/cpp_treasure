/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        StudentCont.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of StudentCont
 *              defining a StudentCont class using containment
 * 
 * Created on   2017年7月4日, 下午4:46
 */

#include "StudentCont.h"

using std::endl;
using std::istream;
using std::ostream;
using std::string;

/*static member here*/

/*methods for subclass*/
std::ostream & StudentCont::arrayOut(std::ostream &os) const
{
    int i = 0;
    int limit = m_scores.size();
    if(limit > 0)
    {
        for(i = 0; i < limit; ++i)
        {
            os << m_scores[i] << " ";
            if(i % 5 == 4)
                os << endl;
        }
        if(i % 5 != 0)
            os << endl;
    }
    else
        os << "Empty array";
    
    return os;
}

/*construction function*/
StudentCont::StudentCont() : m_name("Null Student"), m_scores()
{

}

StudentCont::StudentCont(const std::string &s) : m_name(s), m_scores()
{

}

/// 这里的int n, 在 m_scores() 中标明后, 就会造成未分配array空间, 从而后面输入cin的时候段错误
StudentCont::StudentCont(int n) : m_name("Nully"), m_scores(n)
{

}

StudentCont::StudentCont(const std::string & s, int n) : m_name(s), m_scores(n)
{

}

StudentCont::StudentCont(const std::string & s, const ArrayDb & a) : m_name(s), m_scores(a)
{

}

StudentCont::StudentCont(const char * str, const double * pd, int n) : m_name(str), m_scores(pd, n)
{

}

StudentCont::StudentCont(const StudentCont& orig)
{
    m_name = orig.m_name;
    m_scores = orig.m_scores;
}

StudentCont::~StudentCont()
{

}

/*overloaded operator function*/
StudentCont& StudentCont::operator=(const StudentCont& orig)
{
    if(this == &orig)
        return *this;
    m_name = orig.m_name;
    m_scores = orig.m_scores;
    return *this;
}

std::ostream & operator<<(std::ostream & os, const StudentCont& orig)
{
    os << "Socres for "<< orig.m_name << ": \n";
    orig.arrayOut(os);
    return os;
}

std::istream & operator>>(std::istream & is, StudentCont& orig)
{
    is >> orig.m_name;
    return is;
}

std::istream & getline(std::istream & is, StudentCont & orig)
{
    getline(is, orig.m_name);
    return is;
}

/*public interface*/
double StudentCont::average()const
{
    if(m_scores.size() > 0)
        return m_scores.sum() / m_scores.size();
    else
        return 0;
}

const std::string & StudentCont::name()const
{
    return m_name;
}

double & StudentCont::operator[](int i) 
{
    return m_scores[i];
}

double StudentCont::operator[](int i) const
{
    return m_scores[i];
}