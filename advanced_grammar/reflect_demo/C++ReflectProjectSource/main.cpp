/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 * ��Ҫ֧��C++11, ��Ȼ�޷�����
 *
 * Created on 2017��5��17��, ����9:47
 */

#include <stdio.h>
#include "ObjectFactory.h"
#include <assert.h>


int main()
{
	ObjectFactory::Instance()->CreateObject("MyObject1");
	ObjectFactory::Instance()->CreateObject("MyObject2");

	assert(ObjectFactory::Instance()->CreateObject("MyObject3") == nullptr);

	getchar();
	return 0;
}

