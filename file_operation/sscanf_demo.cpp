#include <stdio.h>    
#include <string.h>
int main( void )  
{
    char  tokenstring[] = "abc ccc 15 12 14...";
    char  s[81];
    char  c;
    int   i;
    float fp;

    //sscanf 在扫描一个存在空格的字符串的时候,如果要扫描出的内容是字符串,那么遇到空格会停止
    sscanf( tokenstring, "%6s", s ); // C4996
    sscanf( tokenstring, "%c", &c );  // C4996
    sscanf( tokenstring, "%d", &i );  // C4996
    sscanf( tokenstring, "%f", &fp ); // C4996
 
    printf( "tokenstring = %s\n", tokenstring);
    printf( "sizeof(s) = %d\n", sizeof(s));
    printf( "strlen(s) = %d\n", strlen(s));
    printf( "String    = %s\n", s );
    printf( "Character = %c\n", c );
    printf( "Integer:  = %d\n", i );
    printf( "Real:     = %f\n", fp );
 
}  
