#include <stdio.h>

int main()
{
    char str[20] = "sprintf";
    double  num = 10.2;
    int  length = 9;
    int  point = 4;
    sprintf(str, "%*.*f", length, point, num);
    printf("%s\n", str);

}

