/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector.cpp
 * Author: xuwei.huang
 * Vector.cpp--methods for the Vector Class
 * Created on 2017年6月14日, 下午7:51
 */

#include <cmath>
#include "Vector.h"


using std::sqrt;
using std::sin;
using std::cos;
using std::atan;
using std::atan2;
using std::cout;
using std::endl;
using std::cin;

namespace VECTOR
{

    const double RadToDeg = 45 / atan(1);

    Vector::Vector()
    {
        m_mode = RECT;
        m_x = 0;
        m_y = 0;
        m_len = 0;
        m_ang = 0;
    }

    Vector::Vector(const Vector& orig)
    {
        m_x = orig.m_x;
        m_y = orig.m_y;
        m_mode = orig.m_mode;
        m_len = orig.m_len;
        m_ang = orig.m_ang;
    }

    Vector::Vector(double n1, double n2, Mode form)
    {
        m_mode = form;
        if(RECT == m_mode)
        {
            m_x = n1;
            m_y = n2;
            setLen();
            setAng();
        }
        else if(POL == m_mode)
        {
            m_len = n1;
            m_ang = n2 / RadToDeg;
            setX();
            setY();
        }
        else
        {
            cout << endl << "Incorrect 3rd argument to Vector() -- ";
            cout << "Vector set to 0" << endl;
            m_x = m_y = m_len = m_ang = 0;
            m_mode = RECT;
        }
    }

    Vector::~Vector()
    {
    }

    bool Vector::reset(double n1, double n2, Mode form)
    {
        m_mode = form;
        if(RECT == m_mode)
        {
            m_x = n1;
            m_y = n2;
            setLen();
            setAng();
        }
        else if(POL == m_mode)
        {
            m_len = n1;
            m_ang = n2;
            setX();
            setY();
        }
        else
        {
            cout << endl << "Incorrect 3rd argument to Vector() -- ";
            cout << "Vector set to 0" << endl;
            m_x = m_y = m_len = m_ang = 0;
            m_mode = RECT;
        }
        return true;
    }

    inline Vector::Mode Vector::getMode() const
    {
        return m_mode;
    }

    bool Vector::setRectMode()
    {
        m_mode = RECT;
        return true;
    }

    bool Vector::setPolMode()
    {
        m_mode = POL;
        return true;
    }

    /// operator overloading

    Vector& Vector::operator-()
    {
        m_x = -m_x;
        m_y = -m_y;
        m_len = -m_len;
        m_ang = -m_ang;
        return *this;
    }

    Vector Vector::operator+(const Vector& b) const
    {
        return Vector(m_x + b.m_x, m_y + b.m_y);
    }

    Vector Vector::operator-(const Vector& b) const
    {
        return Vector(m_x - b.m_x, m_y - b.m_y);
    }

    Vector Vector::operator*(double n) const
    {
        return Vector(m_x * n, m_y * n);
    }

    /// friend methods
#ifdef FRIEND
    /// 只有友元函数才可以 将基本类型在前 在*本类对象,  如果是成员函数重载的, 就必须是对象*double
    Vector operator*(double n, const Vector &a)
    {
        return a * n;
    }
#endif

    /// 重载cout, 不能传入const对象, 因为 内部 << 实际上以及改变了对量的值了
    std::ostream & operator<<(std::ostream & os, const Vector & a)
    {
        if(Vector::RECT == a.m_mode)
        {
            os << "(x, y) = (" << a.m_x << ", " << a.m_y << ")" << endl;
        }
        else if(Vector::POL == a.m_mode)
        {
            os << "(l, a) = (" << a.m_len << ", " << a.m_ang << ")" << endl;
        }
        else
        {
            os << "Vector object mode is invalid " << endl;
        }
        return os;
    }

    bool Vector::setLen()
    {
        m_len = sqrt(m_x * m_x + m_y * m_y);
    }

    bool Vector::setAng()
    {
        if(m_x == 0 && m_y == 0)
        {
            m_ang = 0;
        }
        else
        {
            m_ang = atan2(m_y, m_x);
        }
    }

    bool Vector::setX()
    {
        m_x = m_len * cos(m_ang);
    }

    bool Vector::setY()
    {
        m_y = m_len * sin(m_ang);
    }

#ifndef FRIEND

    Vector operator*(double n, Vector &a)
    {
        return a * n;
    }
#endif

}/// end of namespace VECTOR

