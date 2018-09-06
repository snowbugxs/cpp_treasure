#ifndef _OBJECT_REFLECT_H_
#define _OBJECT_REFLECT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ObjectReflect.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/17
//  Description:	本类型为模板类，用于注册类型信息
		所有需提供反射功能的类均可通过声明一个ObjectReflect类型的静态对象来注册
		若某类型需提供反射功能，可在该类定义中声明一个静态的ObjectReflect对象，并用类型名初始化该静态对象，从而完成反射类型注册
		示例：
		class ClassOne
		{
			static ObjectReflect<ClassOne> objectReflect;
		};
		ObjectReflect<ClassOne> ClassOne::objectReflect("ClassOne");
		而后可通过ObjectFactory::Instance()->CreateObject("ClassOne")生成该ClassOne对象。
//  Others:	
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/17
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <string>
#include "ClassInfo.h"

template<typename T>
class ObjectReflect
{
public:
	ObjectReflect(const std::string& name);
	
	static void* CreateInstance();
};

template<typename T>
void* ObjectReflect<T>::CreateInstance()
{
	return new T;
}

template<typename T>
ObjectReflect<T>::ObjectReflect(const std::string& name)
{
	static ClassInfo classInfo(name, CreateInstance);
}

#endif