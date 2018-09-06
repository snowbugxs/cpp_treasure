#include "CKHelloClass.h"

IMPLEMENT_CLASS(CKHelloClass)
CKHelloClass::CKHelloClass()
{

}

CKHelloClass::~CKHelloClass()
{

}

void* CKHelloClass::createInstance()
{
    return new CKHelloClass();
}

void CKHelloClass::registProperty()
{
    m_propertyMap.insert(pair<string, setValue>("setm_pValue", setm_pValue));
    m_propertyMap.insert(pair<string, setValue>("setm_pName", setm_pName));
}

void CKHelloClass::display()
{
    cout << getm_pValue() << endl;
    cout << getm_pName() << endl;
}
