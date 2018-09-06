/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年6月4日, 上午11:20
 * 
 * Summary: 对于有冲突的命名空间变量, 尽量使用全路径, 虽然麻烦但不会出错, 当然程序员的自我修养很重要
 * 
 */

#include <iostream>

const int i = 6;

namespace detail
{
    const int i = 66;
} // end namespace detail

namespace ant
{
    namespace blas
    {
        const int i = 666;
    } // end blas

    const int i = 67;

    namespace detail
    {
        const int i = 667;

        void test()
        {
            std::cout << "i:667 \t\t\t" << i << std::endl; // 667
            std::cout << "::i:6 \t\t\t" << ::i << std::endl; // 6
            std::cout << "::detail::i:66 \t\t\t" << ::detail::i << std::endl; // 66
            std::cout << "detail::i:667 \t\t\t" << detail::i << std::endl; // 667
            std::cout << "::ant::blas::i:666 \t\t\t" << ::ant::blas::i << std::endl; // 666
            std::cout << "ant::blas::i:666 \t\t\t" << ::ant::blas::i << std::endl; // 666
            std::cout << "blas::i:67 \t\t\t" << blas::i << std::endl; // 67
            std::cout << "ant::i:67 \t\t\t" << ant::i << std::endl; // 67
            //std::cout<<"::blas::i: \t\t\t"<<::blas::i<<std::endl;                 // error
        }
    } // end detail
} // end namespace ant

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;

    //    //绝对命名空间路径,在任何时候都是可以的
    //    ant::detail::test();

    //    using namespace ant::detail;
    //    test();
    {
        using namespace detail;
        //     // 在匿名空间中有const i, 直接使用i会去匿名空间和detail空间寻找,有歧义就会报错
        //     // 所以尽量不要在匿名空间或者说全局空间中申明变量, 全局命名空间的变量容易扰乱其他命名, 特别是你想偷懒的时候
        //    cout << i << endl; 
        cout << ::i << endl;
        cout << detail::i << endl;

        // 或者直接进行using声明是哪个i, 就可以直接覆盖其他名称空间的i了     
        using detail::i;
        cout << i << endl;
    }

    {
        using namespace ant;
        using ant::i;
        cout << i << endl;
        // 没有歧义的下级名称空间引用, 可以使用相对位置, 但有歧义的话, 就要使用全路径
//        cout << detail::i << endl;
        cout << ant::detail::i << endl;
        cout << blas::i << endl;
    }
    
    {
        cout << i << endl;
    }

    return 0;
}


