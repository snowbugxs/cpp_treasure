#include <list>
#include <iostream>

int main()
{
    using namespace std;
    list<int> a1{1, 2, 3}, a2{4, 5, 6};
    a1.splice(a1.begin(), a2, ++a2.begin());
    list<int>::iterator it;
    cout << "a1.splice:";
    for(it = a1.begin(); it != a1.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
  
    return 0;
}
