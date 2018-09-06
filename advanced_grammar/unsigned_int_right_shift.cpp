#include <iostream>
#include <cstdio>
#include <climits>

using namespace std;

int GetMinLargerSecondPowerNum(int num){
	unsigned n = (unsigned int)(num -1);
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	num = (int) n;
	return (num < 0) ? 1 : (num >= INT_MAX ? INT_MAX : num + 1); 	
}

int main(){
	int i_origin = -200;
	cout << i_origin << ": ";
	printf("%x\n", i_origin);
	cout << (i_origin >> 2) << endl;
	printf("%x\n", (i_origin >> 2));
	cout << ((unsigned int)i_origin >> 2) << endl;
	printf("%x\n", ((unsigned int)i_origin >> 2));

	cout << GetMinLargerSecondPowerNum(2) << endl;
	cout << GetMinLargerSecondPowerNum(7) << endl;
	cout << GetMinLargerSecondPowerNum(16) << endl;
	cout << GetMinLargerSecondPowerNum(-11) << endl;
}
