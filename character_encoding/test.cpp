
#include <iostream>
#include <string>
 
using std::cout;
using std::endl;
 
std::string Utf8SubStr(const std::string&name, size_t need) {
    size_t i=0;
    size_t j=0;
    while (i<need && j<name.length()) {
        unsigned char c = (unsigned char)name[j++];
        i += ((c & 0xc0) != 0x80);
    }
 
    while (j<name.length()) {
        unsigned char c = (unsigned char)name[j];
        if ((c & 0xc0) == 0x80) {
            j++;
        } else {
            break;
        }
    }
    return name.substr(0, j);
}
 
int main(int argc, char *argv[]) {
    std::string name("h你好");
	cout << "name: len: " << name.size() << endl;
    cout<<Utf8SubStr(name, 2)<<endl;
    return 0;
}

