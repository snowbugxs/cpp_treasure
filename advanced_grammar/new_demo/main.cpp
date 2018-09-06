/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年6月18日, 下午5:40
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <new>

using namespace std;
const int BUFSIZE = 512;

/// 总计占用16字节内存
class JustTest
{
private:
    /// 占用8字节, 字符串存放在堆中
    string words;
    int number;

public:

    JustTest(const string &s = "object in char buffer array", int n = 0) : words(s), number(n)
    {
        cout << words << " constructed \n";
    }

    ~JustTest()
    {
        cout << words << " destroyed\n";
    }

    bool Show() const
    {
        cout << words << ",  " << number << endl;
    }

};

/**
 * main 函数
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char** argv)
{
    char * buffer = new char[BUFSIZE];
    JustTest *pc1 = NULL, *pc2 = NULL;
    
    /// place object in buffer
    pc1 = new (buffer) JustTest;
    /// place object on heap
    pc2 = new JustTest("Heap 1", 20);
    /// buffer 就是起始空间的首地址, buffer + sizeof(JustTest) 就是从第一个对象之后的位置开始创建新的对象
    JustTest * pc3 = new (buffer + sizeof(JustTest)) JustTest("new object in buffer");
    JustTest * pc4 = new JustTest("Heap2", 10);
    
    pc1->Show();
    pc2->Show();
    pc3->Show();
    pc4->Show();
    
    cout << "Memory contents:\n"<< endl;
    cout << "buffer : " << (void *) buffer << endl;
    cout << "pc1    : " << pc1 << endl;
    cout << "pc2    : " << pc2 << endl;
    cout << "pc3    : " << pc3 << endl;
    cout << "pc4    : " << pc4 << endl;
    
    cout << "destory all the objects" << endl;
    delete pc2;
    delete pc4;
    
    /// 对于使用定位new分配空间生成的对象, 必须显式调用其析构函数.
    /// delete只能和普通new产生联动, 而不会与定位new进行联动
    /// 显式调用析构函数顺序, 先进后出, 先析构后创建的对象
    /// explicitly destory placement new objects
    pc3->~JustTest();
    pc1->~JustTest();
    /// delete[] 和 new [] 联动
    /// free buffer
    delete [] buffer;
    cout << "Done, BYE!" << endl;
    cout << "size of string: " << sizeof(string) << endl;
    
    return 0;
}

