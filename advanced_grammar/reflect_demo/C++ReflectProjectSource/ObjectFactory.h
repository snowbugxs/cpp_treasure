#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ObjectFactory.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/17
//  Description:	反射工厂，用于根据提供的类型信息生成该类型的对象
		本工厂为单例模式，存储所有需提供反射功能的类型信息
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/17
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <map>

class ClassInfo;

class ObjectFactory
{

public:
	static ObjectFactory* Instance();	/*获取唯一对象*/

	void* CreateObject(const std::string& className);	/*根据类名生成相应对象指针*/
	bool Register(ClassInfo* classInfo);	/*注册类型信息*/

private:
	/*单例模式*/
	ObjectFactory();
	ObjectFactory(const ObjectFactory&) = delete;
	ObjectFactory& operator=(const ObjectFactory&) = delete;
	~ObjectFactory();

private:
	std::map<std::string, ClassInfo*> m_classInfoMap;	/*类型信息集合*/
};

#endif