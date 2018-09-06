/// append.cpp -- appending information to a file

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // for exit()

const char * fileName = "append_guests.txt";

int main()
{
    using namespace std;
    char ch;
    /// show initial contents
    ifstream fin;
    fin.open(fileName);
    if(fin.is_open())
    {
        cout << "Here are the current contens of the " << fileName << "file: \n";
        while(fin.get(ch))
            cout << ch;
        fin.close();
    }
    
    /// add new names
    ofstream fout(fileName, ios::in | ios::app);
    if(!fout.is_open())
    {
        cerr << "Cant't open " << fileName << " file for output. \n";
        exit(EXIT_FAILURE);
    }

    cout << "Enter guest names (enter a blank line to quit): \n";
    string name;
    while(getline(cin, name) && name.size() > 0)
    {
        fout << name << endl;
    }
    fout.close();
    
    /// show revised file
    /// not necessary for some compilers
    fin.clear();
    fin.open(fileName);
    if(fin.is_open())
    {
        cout << "Here are the new contents of the " << fileName << " file: \n";
        while(fin.get(ch))
            cout << ch;
        fin.close();
    }
    cout << "Done!!!" << endl;
    
    return 0;

}

