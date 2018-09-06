/*
 *	测试一个数是不是小数,实验
 * */

#include <iostream>
using namespace std;

int main()
{
	double a = 3.00000001;
	float b = 3.00;

	if(a - int(a) >  0 )
	{
		cout <<"是小数"<<endl;
	} 
	else
	{
		cout << "不是小数"<<endl;
	}


	if(b - int(b) ==  0 )
	{
		cout << "不是小数"<<endl;
	} 
	else
	{
		cout << "是小数"<<endl;
	}
	

	double c = 5.235235;
	if(c == int(a))
	{
		cout << "不是小数"<<endl;
	}
	else
	{
		cout << "是小数" <<endl;
	}

	return 0;
}
