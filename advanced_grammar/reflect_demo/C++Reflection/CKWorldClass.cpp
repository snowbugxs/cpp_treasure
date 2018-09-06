#include "CKWorldClass.h"

IMPLEMENT_CLASS(CKWorldClass)
CKWorldClass::CKWorldClass()
{

}

CKWorldClass::~CKWorldClass()
{

}

void* CKWorldClass::createInstance()
{
    return new CKWorldClass();
}

void CKWorldClass::registProperty()
{
    m_propertyMap.insert(pair<string, setValue>("setm_pName", setm_pName));
}

void CKWorldClass::display()
{
    cout << getm_pName() << endl;
}
