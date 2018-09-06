#include "MyObject2.h"
#include <iostream>
#include "ClassInfo.h"



ObjectReflect<MyObject2> MyObject2::m_objectReflect("MyObject2");


MyObject2::MyObject2()
{
	std::cout << "MyObject2" << std::endl;
}

MyObject2::~MyObject2()
{

}

