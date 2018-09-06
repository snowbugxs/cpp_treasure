#ifndef _CLASS_INFO_H_
#define _CLASS_INFO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ClassInfo.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/17
//  Description:	记录类的相关信息，包括类名及用于生成类对象的函数指针
		生成ClassInfo对象时，会自动将此对象注册于反射类型集合中，使得之后能够根据提供的类型信息生成相应对象，
		所有需要反射功能的类ClassNeedReflect均需具有一个ClassInfo静态对象，用于将ClassNeedReflect注册到反射类型集合中，
		生成的对象指针为void*类型，可根据需要自定义类型，并使所有需要反射功能的类ClassNeedReflect继承自该自定义类型
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/17
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <string>

//using FunctionCreateObject = void*(*)();
typedef void*(*FunctionCreateObject)();

class ClassInfo
{
public:
	ClassInfo(const std::string type, FunctionCreateObject createObject);
	
	std::string type;	/*类型名*/
	FunctionCreateObject createObject;	/*函数指针，用于生成相应类型的对象*/
};

#endif