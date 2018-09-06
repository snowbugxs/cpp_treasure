#ifndef C___Reflection_CKHelloWorldClass_h
#define C___Reflection_CKHelloWorldClass_h


#include "CKBaseClass.h"
#include "CKHelloClass.h"
#include "CKWorldClass.h"

class CKHelloWorldClass : public CKBaseClass
{
private:
    DECLARE_CLASS(CKHelloWorldClass)

public:
    SYNTHESIZE(CKHelloWorldClass, string, m_pName)
    SYNTHESIZE(CKHelloWorldClass, CKHelloClass, m_pHello)
    SYNTHESIZE(CKHelloWorldClass, CKWorldClass, m_pWorld)

    CKHelloWorldClass();
    virtual ~CKHelloWorldClass();
    static void* createInstance();
    virtual void registProperty();
    virtual void display();
protected:
    string m_pName;
    CKHelloClass m_pHello;
    CKWorldClass m_pWorld;

};

#endif
