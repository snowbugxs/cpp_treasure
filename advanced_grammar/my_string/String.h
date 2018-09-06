/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   String.h
 * Author: xuwei.huang
 *
 * Created on 2017年6月17日, 下午7:09
 */

#ifndef STRING_H
#define STRING_H
#include <iostream>

class String
{
private:
    static int num_strings; /// num of objects
    /// 真是诡异啊, 后面实验的时候又有效了, 蛋疼
    /// 这里 如果放在private中, 那么后面的>>重载函数会报错:私有的, 但C++PrimerPlus的源码就是private
    static const int CINLIM = 80; /// cin input limit

private:
    char * m_str; /// pointer to string
    int m_len; /// length of objects

public:
    /// static function
    static int HowMany();

public:
    String();
    String(const char *s);
    String(const String& orig);
    virtual ~String();

public:

    inline int length() const
    {
        return m_len;
    }

    /// overloaded operator methods
    String & operator=(const String & orig);
    /// more efficient overloaded equal function
    String & operator=(const char * s);
    char & operator[](int i);
    const char & operator[](int i) const;

    /// friends overloaded operator friends
    friend bool operator<(const String & str1, const String & str2);
    friend bool operator>(const String & str1, const String & str2);
    friend bool operator==(const String & str1, const String & str2);
    friend std::ostream & operator<<(std::ostream & os, const String & str);
    /// 注意, 未定义的引用的时候, 请仔细检查函数原型和函数定义是否有不同, 小细节
    /// const也不要滥用, 特别是和cin有关的时候, cout的os也不能使用
    friend std::istream & operator>>(std::istream & os, String & str);




};

#endif /* STRING_H */

