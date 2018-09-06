/*
    binary file I/O demo
    using c++ I/O
*/

#include <iostream> /// not necessary for most systems
#include <fstream>
#include <fstream>
#include <iomanip>
#include <cstdlib> /// for exit()

inline void EatLine()
{
    while (std::cin.get() != '\n')
        continue;
}

/// in this case, we just copy this struct into file with byte stream
/// therefore, string can only copy a pointer address. that isn't the thing what we want
struct Planet
{
    char name[20];     /// name of planet, if using string , you just get a pointer
    double population; /// its popolation
    double g;          /// its acceleration of gravity
};

const char *filePath = "planets.txt";

int main()
{
    using namespace std;
    Planet p1;
    cout << fixed << right;

    /// show initial contents
    ifstream fin;
    fin.open(filePath, ios_base::in | ios_base::out | ios_base::binary); ///binary file

    if (fin.is_open())
    {
        cout << "Here are the current contents of the " << filePath << " file \n";
        while (fin.read((char *)&p1, sizeof(p1)))
        {
            cout << setw(20) << p1.name << ": ";
            cout << setprecision(0) << setw(12) << p1.population;
            cout << setprecision(2) << setw(6) << p1.g << endl;
        }
        fin.close();
    }

    /// add new data
    ofstream fout(filePath, ios_base::out | ios_base::app | ios_base::binary);
    if (!fout.is_open())
    {
        cerr << "Cant't open " << filePath << " file for output: \n";
        exit(EXIT_FAILURE);
    }

    cout << "Enter planet name (enter a blank line to quit): \n";
    cin.get(p1.name, 20);
    while (p1.name[0] != '\0')
    {
        EatLine();
        cout << "Enter planetary population: \n";
        cin >> p1.population;
        cout << "Enter planet's acceleration of gravity: \n";
        cin >> p1.g;
        EatLine();
        fout.write((char *)&p1, sizeof(p1));
        cout << "Enter planet name (enter a blank line to quei): \n";
        cin.get(p1.name, 20);
    }
    fout.close();

    /// show revised file
    /// not required for some implementations, but won't hurt
    fin.clear();
    fin.open(filePath, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        cout << "Here are the new contens fo the " << filePath << " file\n";
        while (fin.read((char *)&p1, sizeof(p1)))
        {
            cout << setw(20) << p1.name << ": ";
            cout << setprecision(0) << setw(12) << p1.population;
            cout << setprecision(2) << setw(6) << p1.g << endl;
        }
        fin.close();
    }

    cout << "Done! \n";

    return 0;
}
