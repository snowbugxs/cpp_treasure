#include <string>  
#include <algorithm>
#include <cstdio>  
using namespace std;  
      
int main()  
{  
        string strA = "yasaken@126_text_TEXT.com";  
        string strB = "LURY@LENOVO_text_TEXT.com";  
        printf("Before transform:\n");  
        printf("strA:%s \n", strA.c_str());  
        printf("strB:%s \n\n", strB.c_str());  
      
        transform(strA.begin(), strA.end(), strA.begin(), ::toupper);  
        transform(strB.begin(), strB.end(), strB.begin(), ::toupper);  
        printf("After transform to toupper:\n");  
        printf("strA:%s \n", strA.c_str());  
        printf("strB:%s \n\n", strB.c_str());  
      
        transform(strA.begin(), strA.end(), strA.begin(), ::tolower);  
        transform(strB.begin(), strB.end(), strB.begin(), ::tolower);  
        printf("After transform to lower:\n");  
        printf("strA:%s \n", strA.c_str());  
        printf("strB:%s \n\n", strB.c_str());  
        return 0;  
}
