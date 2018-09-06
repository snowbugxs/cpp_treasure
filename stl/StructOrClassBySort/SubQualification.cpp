/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SubQualification.cpp
 * Author: xuwei.huang
 * 
 * Created on 2017年6月18日, 下午7:31
 */

#include "SubQualification.h"

SubQualification::SubQualification()
{
    m_user_id = "000001";
    m_user_name = "ageofempires";
    m_user_addr = "steam";
    m_volume = 100;
}

SubQualification::SubQualification(const std::string &id, const std::string & name, const std::string & addr, const int volume) : m_user_id(id), m_user_name(name), m_user_addr(addr), m_volume(volume)
{

}

SubQualification::SubQualification(const SubQualification& orig)
{
    m_user_id = orig.m_user_id;
    m_user_name = orig.m_user_name;
    m_user_addr = orig.m_user_addr;
    m_volume = orig.m_volume;
}

SubQualification::~SubQualification()
{
}

SubQualification SubQualification::operator=(const SubQualification & orig)
{
    if(this == &orig)
    {

    }
    else
    {
        m_user_id = orig.m_user_id;
        m_user_name = orig.m_user_name;
        m_user_addr = orig.m_user_addr;
        m_volume = orig.m_volume;
    }
    return *this;
}

/// 一级比较,小于直接返回true, 如果等于再接着向后比较, (大于的话直接返回false了), 后面的二级,三级比较依次类推
/// 错了, 原来的排序没有想好
/// 只适合单一层次排序, 不适合全部排序. sort()排序的时候是

bool SubQualification::operator<(const SubQualification & b) const
{
    if(m_user_id < b.m_user_id)
    {
        return true;
    }
    else if(m_user_id == b.m_user_id)
    {
        if(m_user_name < b.m_user_name)
        {
            return true;
        }
        else if(m_user_name == b.m_user_name)
        {
            if(m_user_addr < b.m_user_addr)
            {
                return true;
            }
            else if(m_user_addr == b.m_user_addr)
            {
                if(m_volume < b.m_volume)
                {
                    return true;
                }
                else if(m_volume == b.m_volume)
                    return false;
            }
        }
    }
    return false;
}

std::ostream & operator<<(std::ostream & os, const SubQualification & object)
{
    os << "id     : " << object.m_user_id;
    os << "     name   : " << object.m_user_name;
    os << "     addr   : " << object.m_user_addr;
    os << "     volume : " << object.m_volume;
    os << "\n";
    return os;
}