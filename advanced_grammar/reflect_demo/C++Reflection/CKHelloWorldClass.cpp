#include "CKHelloWorldClass.h"

IMPLEMENT_CLASS(CKHelloWorldClass)
CKHelloWorldClass::CKHelloWorldClass()
{

}

CKHelloWorldClass::~CKHelloWorldClass()
{

}

void* CKHelloWorldClass::createInstance()
{
    return new CKHelloWorldClass();
}

void CKHelloWorldClass::registProperty()
{
    m_propertyMap.insert(pair<string, setValue>("setm_pName", setm_pName));
    m_propertyMap.insert(pair<string, setValue>("setm_pHello", setm_pHello));
    m_propertyMap.insert(pair<string, setValue>("setm_pWorld", setm_pWorld));
}

void CKHelloWorldClass::display()
{
    cout << m_pHello.getm_pName() << " " << m_pWorld.getm_pName() << endl;
}
