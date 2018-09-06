#ifndef _MY_OBJECT_1_H_
#define _MY_OBJECT_1_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MyObject2.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2016/11/17
//  Description:	示例对象，用于测试能够正确生成对象
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2016/11/17
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "ObjectReflect.h"

class MyObject1
{
public:
	MyObject1();

private:
	static ObjectReflect<MyObject1> m_objectReflect;
};

#endif