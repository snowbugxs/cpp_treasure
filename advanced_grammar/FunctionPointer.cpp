// this is just a define ationition of a arryayna arryaaayay to function pointer
// while using function pointer, you would prefer using typedef to understand better
#include <iostream>

// various notations, same signatures
const double *f1(const double ar[], int n);
const double *f2(const double[], int);
const double *f3(const double *, int);
// you can use typedef to simplify/predigest the declaration of function pointer
typedef const double *(*f4)(const double *, int);

int main()
{
    using namespace std;
    double av[3] = {1112.3, 1566.6, 2235.9};

    // pointer to a function
    const double *(*p1)(const double *, int) = f1;
    // C++ automatic type deduction. only single value can use auto
    // auto p2 = f2;
    // pre-C++11 can use the following code instead
    const double *(*p2)(const double *, int) = f2;
    f4 p3 = f3;
    cout << "Using pointers to functions: " << endl;
    cout << " Address Value " << endl;
    cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
    cout << p2(av, 3) << ": " << *p2(av, 3) << endl;
    cout << p3(av, 3) << ": " << *p3(av, 3) << endl;

    // pa an array fo pointers
    // auto doesn't work with list initialization
    const double *(*pa[3])(const double *, int) = {f1, f2, f3};
    // but it does work for initializing to a single value
    // pb a pointer to first element of pa
    // auto pb = pa;
    // pre-C++ can use  the following code instead;
    // const double *(**pb)(const double *, int) = pa;
    // another way to define pb -- using typedef
    f4 *pb = pa;    // this is just a definition of pointer to pointer.  array name is also a pointer
    cout << "\nUsing an array of pointers to functions: " << endl;
    cout << " Address Values " << endl;
    for (int i = 0; i < 3; ++i)
        cout << pa[i](av, 3) << ": " << *pa[i](av, 3) << endl;
    cout << "\nUsing a pointer to pointer to a function: " << endl;
    cout << " Address Value " << endl;
    for (int i = 0; i < 3; ++i)
        cout << pb[i](av, 3) << ": " << *pb[i](av, 3) << endl;

    // what about a pointer to an array of function pointers
    cout << "\nUsing pointer to an array of function pointers: " << endl;
    cout << " Address Value" << endl;
    // easy way to declare pc
    // auto pc = &pa;
    // pre-C++ can use the following code instead
    // const double *(*(*pc)[3])(const double *, int) = &pa;
    f4(*pc)[3] = &pa;   // this is just a definition of an array to function pointer
    cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << endl;
    // hard way to declare pd
    // const double *(*(*pd)[3])(const double *, int) = &pa;
    f4(*pd)[3] = &pa;
    // store return value in pdb
    const double *pdb = (*pd)[1](av, 3);
    cout << pdb << ": " << *pdb << endl;
    // alternative notation
    cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;
    // cin.get();

    return 0;
}

// some rather dull function
const double *f1(const double *ar, int n)
{
    return ar;
}

const double *f2(const double ar[], int n)
{
    return ar + 1;
}

const double *f3(const double *ar, int n)
{
    return ar + 2;
}