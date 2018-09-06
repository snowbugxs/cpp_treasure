/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Vector.h
 * Author: xuwei.huang
 * Vector class with <<, mode state
 * Created on 2017年6月14日, 下午7:51
 */

#ifndef VECTOR_H
#define VECTOR_H

#define FRIEND

#include <iostream>

namespace VECTOR {

    class Vector
    {
    public:
        /// RECT for rectangular, POL for polar modes

        enum Mode
        {
            RECT, POL
        };

    public:
        Vector();
        Vector(const Vector& orig);
        Vector(double n1, double n2, Mode form = RECT);
        virtual ~Vector();

    public:
        bool reset(double n1, double n2, Mode form = RECT);

        /// 内联函数必须在头文件中定义, 不然会出现未定义的错误. 不能放在类的cpp实现文件中
        inline double getX() const
        {
            return m_x;
        }

        inline double getY() const
        {
            return m_y;
        }

        inline double getLen() const
        {
            return m_len;
        }

        inline double getAng() const
        {
            return m_ang;
        }
        Mode getMode() const;
        bool setRectMode();
        bool setPolMode();

    public:
        Vector& operator-();
        Vector operator+(const Vector &b) const;
        Vector operator-(const Vector &b) const;
        Vector operator*(double n) const;
        /// can not define overloading like this, 
        /// you can translate friend overloading functiong into non-member overloading function
        /// can not translate this into member overloading function
        /// Vector operator*(double n, Vector &a) const;
        /// friends function
#ifdef FRIEND
        friend Vector operator*(double n, const Vector & a);
#endif
        /// std::ostream 不能是const对象, 因为使用的时候改变了对象. 比如 ofstream 中, 文件对象实际上已经改变了.(多了内容)
        friend std::ostream & operator<<(std::ostream & os, const Vector &a);

    private:
        bool setLen();
        bool setAng();
        bool setX();
        bool setY();

    private:
        double m_x;
        double m_y;
        double m_len;
        double m_ang;
        Mode m_mode;

    };

#ifndef FRIEND
    /// you can translate friend overloading functiong into non-member overloading function
    /// can not translate this into member overloading function
    Vector operator*(double n, Vector &a);
#endif

} ///end of namespace VECTOR


#endif /* VECTOR_H */

