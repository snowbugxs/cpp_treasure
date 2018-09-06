#include "CKDynamicClass.h"

CKDynamicClass::CKDynamicClass(string name, createClass method)
{
    CKClassFactory::sharedClassFactory().registClass(name, method);
}