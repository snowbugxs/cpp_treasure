/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        LineQueue.h
 * Author:      xuwei.huang
 * Describe:    declaration of LineQueue
 *              
 * Created on   2017年6月21日, 上午11:14
 */

#ifndef LINEQUEUE_H
#define LINEQUEUE_H

#include "Customer.h"

#include <iostream>

typedef Customer Item;

class LineQueue
{
private:
    /// 定义类中类的时候, 必须放在类的前面, 不然后面出现未定义
    /// class scope definitions
    /// Node is a nested structure definition local to this class

    struct Node
    {
        Item item;
        struct Node * next;
    };

    enum
    {
        Q_SIZE = 10
    };

private:
    /// private class members
    Node * m_head; /// pointer to head of LineQueue
    Node * m_rear; /// pointer to rear of LineQueue
    int m_items; /// current number of items in LineQueue
    const int m_qsize; /// maximum number of items in Queue
private:
    LineQueue(const LineQueue& orig);
    LineQueue& operator=(const LineQueue& orig);

public:
    LineQueue(int qs = Q_SIZE); /// create queue with a qs limit
    virtual ~LineQueue();

public:
    friend std::ostream & operator<<(std::ostream & os, const LineQueue& orig);

public:
    bool isEmpty() const;
    bool isFull() const;
    int queueCount() const;
    /// 等会实验一下, item在内部时候,外部如何引用, 或者  item在匿名空间中如何访问?
    bool enQueue(const Item & item);  /// add item to end
    bool deQueue(Item & item);      /// remove item from front

};

#endif /* LINEQUEUE_H */

