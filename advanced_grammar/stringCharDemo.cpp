#include <iostream>
#include <stdio.h>
int main()
{
	using namespace std;

	/// 可以这样使用,但是会报警告, 不建议从字符串常量到char*的转换
	/// char *name = "This is a string demo";
	char name[] = "This is another string demo";
	/// string可以直接使用 char* 来赋值
	string str = name;
	printf("%s\n", str.c_str());
	cout << "char * name: " << name << endl;
	cout << "string  str: " << str << endl;

	return 0;
}
