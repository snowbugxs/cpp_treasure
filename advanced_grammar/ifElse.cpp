//ifelse.cpp  --using the if else statement
#include <iostream>

int main()
{
	using std::cin;
	using std::cout;
	using std::endl;
	
	char ch;
	cout << "Type, and I shall repeat" << endl;
	cin.get(ch);
	while(ch != '.')
	{
		if(ch =='\n')
			cout << ch;
		else
			//cout << ++ch;
			cout << ch + 1;//字符与整型(实型)作运算, 字符类型被强制提升为int型(实型), 然后输出为实型
		cin.get(ch);
	}
	cout << "\nPlease excuse the slight confusion." << endl;
	return 0;
}

