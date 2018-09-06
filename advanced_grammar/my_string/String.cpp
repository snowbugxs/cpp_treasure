/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   String.cpp
 * Author: xuwei.huang
 * 
 * Created on 2017年6月17日, 下午7:09
 */

#include <cstring>
#include "String.h"

using std::cout;
using std::cin;

/// initializing static class member
int String::num_strings = 0;

int String::HowMany()
{
    return num_strings;
}


String::String()
{
    ++num_strings;
    m_len = 0;
    m_str = new char[1];
    m_str[0] = 0;
}

String::String(const char * s)
{
    ++num_strings;
    m_len = std::strlen(s);
    m_str = new char[m_len + 1];
    std::strcpy(m_str, s);
}

String::String(const String& orig)
{
    ++num_strings;
    m_len = orig.m_len;
    m_str = new char[m_len + 1];
    std::strcpy(m_str, orig.m_str);
}

String::~String()
{
    --num_strings;
    delete[] m_str;
}


/// overloaded operator methods
/// assign a String from a String

String & String::operator=(const String& orig)
{
    /// 首先进行检查 自我赋值的问题
    if(this == &orig)
        return * this;
    delete[] m_str;
    m_len = orig.m_len;
    m_str = new char[m_len + 1];
    std::strcpy(m_str, orig.m_str);
    return *this;
}

/// assign a C string to a String

String & String::operator=(const char *s)
{
    delete[] m_str;
    m_len = std::strlen(s);
    m_str = new char[m_len + 1];
    std::strcpy(m_str, s);
    return *this;
}

/// read-write char access for non-const String

char & String::operator[](int i)
{
    return m_str[i];
}

/// read-only char access for const String

const char & String::operator[](int i) const
{
    return m_str[i];
}

/// overloaded operator friends fucntions

bool operator<(const String & str1, const String & str2)
{
    return (std::strcmp(str1.m_str, str2.m_str) < 0);
}

bool operator>(const String & str1, const String & str2)
{
//    return str2 < str1;
    return (std::strcmp(str1.m_str, str2.m_str) > 0);
}

bool operator==(const String & str1, const String & str2)
{
    return (std::strcmp(str1.m_str, str2.m_str) == 0);
}

std::ostream & operator<<(std::ostream & os, const String & str)
{
    os << str.m_str;
    return os;
}

/// quick and dirty String input
std::istream & operator>>(std::istream & is, String & str)
{
    /// 使用缓存机制
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if(is)
    {
        str = temp;
    }
    /// 清除多余内容
    while (is && is.get() != '\n')
        continue;
    return is;
}
