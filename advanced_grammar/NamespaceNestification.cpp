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
    std::cout << "i:667 \t\t\t" << i << std::endl;                           // 667
    std::cout << "::i:6 \t\t\t" << ::i << std::endl;                         // 6
    std::cout << "::detail::i:66 \t\t\t" << ::detail::i << std::endl;        // 66
    std::cout << "detail::i:667 \t\t\t" << detail::i << std::endl;           // 667
    std::cout << "::ant::blas::i:666 \t\t\t" << ::ant::blas::i << std::endl; // 666
    std::cout << "ant::blas::i:666 \t\t\t" << ::ant::blas::i << std::endl;   // 666
    std::cout << "blas::i:666 \t\t\t" << blas::i << std::endl;                // 666
    std::cout << "ant::i:67 \t\t\t" << ant::i << std::endl;                  // 67
    //std::cout<<"::blas::i: \t\t\t"<<::blas::i<<std::endl;                 // error
}
} // end detail
} // end namespace ant

int main()
{
    using namespace std;
    ant::detail::test();
    return 0;
}
