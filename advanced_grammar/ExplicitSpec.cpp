// ExplicitSpec.cpp -- explicit specialization overrides a tmeplate

#include <iostream>

template <typename T>
void swap(T &a, T &b);

struct Job
{
    char name[40];
    double salary;
    int floor;
};

// explicit specialization
// template <>
// void swap<Job>(Job &j1, Job &j2);

void show(Job &j);

int main()
{
    using namespace std;
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);
    int i = 10, j = 20;
    cout << "i, j = " << i << ", " << j << ".\n";
    cout << "Using compiler-generated in swapper: \n";
    swap(i, j); // generates void swap(int &, int &)
    cout << "Now i, j = " << i << ", " << j << ".\n";

    Job sue = {"Susan Yaffee", 73000.60, 7};
    Job sidney = {"Sidney Taffee", 78060.72, 9};
    cout << "Before job swapping: \n";
    show(sue);
    show(sidney);
    // swap<Job>(sue, sidney); // uses void swap(Job &, Job &)
    cout << "After Job swapping:\n";
    show(sue);
    show(sidney);

    cin.get();

    return 0;
}

template <typename T>
void swap(T &a, T &b) // general version
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

// swaps just the salary and floor fields of a Job structure
// template <>
// void swap<Job>(Job &j1, Job &j2) // specialization
// {
//     double t1;
//     int t2;
//     t1 = j1.salary;
//     j1.salary = j2.salary;
//     j2.salary = t1;
//     t2 = j1.floor;
//     j1.floor = j2.floor;
//     j2.floor = t2;
// }

void show(Job &j)
{
    using namespace std;
    cout << j.name << ": $" << j.salary << " on floor " << j.floor << endl;
}
