#include "MyObject1.h"
#include <iostream>
#include "ClassInfo.h"


ObjectReflect<MyObject1> MyObject1::m_objectReflect("MyObject1");



MyObject1::MyObject1()
{
	std::cout << "MyObject1"<<std::endl;
}
