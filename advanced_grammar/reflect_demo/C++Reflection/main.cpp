/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: xuwei.huang
 *
 * Created on 2017年5月17日, 上午9:56
 */


#include "CKBaseClass.h"
#include "CKClassFactory.h"
#include "CKDynamicClass.h"
#include "CKHelloClass.h"
#include "CKWorldClass.h"
#include "CKHelloWorldClass.h"

#include <stdio.h>
using namespace std;

int main(int argc, char* argv[])
{
    CKBaseClass *pHello = (CKBaseClass*) CKClassFactory::sharedClassFactory().getClassByName("CKHelloClass");
    CKBaseClass *pWorld = (CKBaseClass*) CKClassFactory::sharedClassFactory().getClassByName("CKWorldClass");
    CKBaseClass *pHelloWorld = (CKBaseClass*) CKClassFactory::sharedClassFactory().getClassByName("CKHelloWorldClass");
    pHello->registProperty();
    pWorld->registProperty();
    pHelloWorld->registProperty();

    string pHelloName = "CKHelloClass";
    string pWorldName = "CKWorldClass";
    string pHelloWorldName = "CKHelloWorldClass";

    pHello->m_propertyMap["setm_pName"](pHello, &pHelloName);

    pWorld->m_propertyMap["setm_pName"](pWorld, &pWorldName);

    pHelloWorld->m_propertyMap["setm_pHello"](pHelloWorld, pHello);
    pHelloWorld->m_propertyMap["setm_pWorld"](pHelloWorld, pWorld);

    pHelloWorld->display();
    getchar();
    return 0;
}


