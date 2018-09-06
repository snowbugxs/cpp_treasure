//FileFunction.cpp -- function with ostream & parameter
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void file_it(ostream &os, double fo, const double fe[], int n);
const int LIMIT = 5;

int main()
{
    ofstream fout;
    const char *fn = "ep-data-FileFunction.txt";
    fout.open(fn);
    if (!fout.is_open())
    {
        cout << "Cant't open" << fn << ". Bye .";
        exit(EXIT_FAILURE);
    }
    double objective;
    cout << "Enter the focal length of your "
            "telescope objective in mm: ";
    // cin >> objective;
    while (!(cin >> objective))
    {
        cin.clear();
        while (cin.get() != '\n')
        {
        }
        cout << "bad input, please input double number" << endl;
    }

    double eps[LIMIT];
    cout << "Enter the focal lengths, in mm, of " << LIMIT << " eyepieces: \n";
    int NEWLIMIT = LIMIT;
    for (int i = 0; i < LIMIT; ++i)
    {
        cout << "Eyepiece #" << i + 1 << "(or 'q' to quit): ";
        cin >> eps[i];
        if (!cin)
        {
            NEWLIMIT = i;
            break;
        }
    }
    file_it(fout, objective, eps, NEWLIMIT);
    file_it(cout, objective, eps, NEWLIMIT);
    cout << "\nDone" << endl;

    return 0;
}

void file_it(ostream &os, double fo, const double fe[], int n)
{
    ios_base::fmtflags initial;
    initial = os.setf(ios_base::fixed); // save initial formatting state
    os.precision(0);
    os << "Focal length of objective: " << fo << " mm\n";
    os.setf(ios::showpoint);
    os.precision(1);
    os.width(12);
    os << "f.l. eyepiece";
    os.width(15);
    os << "magnification" << endl;
    for (int i = 0; i < n; ++i)
    {
        os.width(12);
        os << fe[i];
        os.width(15);
        if (0 != fe[i])
            os << int(fo / fe[i] + 0.5) << endl;
        else
            os << "error" << endl;
    }
    os.setf(initial); // restore initial formatting state
}