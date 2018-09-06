/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        LineQueue.cpp
 * Author:      xuwei.huang
 * Describe:    implementation of LineQueue
 *              
 * Created on   2017年6月21日, 上午11:14
 */

#include "LineQueue.h"

LineQueue::LineQueue(int qs) : m_qsize(qs)
{
    m_head = NULL;
    m_rear = NULL;
    m_items = 0;
}

/// 析构函数这里: 队列对象过期时, 内部的item对象不一定都被清空了, 需要在析构函数中全部释放

LineQueue::~LineQueue()
{
    Node * temp = NULL;
    if(NULL != m_head) /// while queue is not yet empty
    {
        temp = m_head;
        m_head = m_head->next;
        delete temp;
    }

}

std::ostream & operator<<(std::ostream & os, const LineQueue& orig)
{
    /// 注意这里要使用 类名:: 来访问类的内置类型. 名称空间不一致
    LineQueue::Node * temp = NULL;
    int i = 0;
    for(temp = orig.m_head; temp != orig.m_rear->next; temp = temp->next, ++i)
    {
        os << "第 " << i << " 位客户";
        os << temp->item << std::endl;
    }
    return os;
}

bool LineQueue::isEmpty() const
{
    return 0 == m_items;
}

bool LineQueue::isFull() const
{
    return m_qsize == m_items;
}

int LineQueue::queueCount() const
{
    return m_items;
}

/// 等会实验一下, item在内部时候,外部如何引用, 或者  item在匿名空间中如何访问?

bool LineQueue::enQueue(const Item & item) /// add item to end
{
    if(isFull())
        return false;
    Node * add = new Node;
    add->item = item;
    add->next = NULL;
    ++m_items;

    if(NULL == m_head)
    {
        m_head = add;
        m_rear = add;
    }
    else
    {
        m_rear->next = add;
        m_rear = add;
    }

    return true;
}

bool LineQueue::deQueue(Item & item) /// remove item from front
{
//    if(isEmpty())
    if(NULL == m_head)
        return false;
    item = m_head->item;
    --m_items;
    Node * temp = m_head;
    m_head = m_head->next;
    delete temp;
    if(0 == m_items)
    {
        m_rear = NULL;
    }
    
    return true;
    
}

