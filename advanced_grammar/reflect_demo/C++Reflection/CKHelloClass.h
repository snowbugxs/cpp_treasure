#ifndef C___Reflection_CKHelloClass_h
#define C___Reflection_CKHelloClass_h


#include "CKBaseClass.h"

class CKHelloClass : public CKBaseClass
{
private:
    DECLARE_CLASS(CKHelloClass)

public:
    SYNTHESIZE(CKHelloClass, int, m_pValue)
    SYNTHESIZE(CKHelloClass, string, m_pName)

    CKHelloClass();
    virtual ~CKHelloClass();
    static void* createInstance();
    virtual void registProperty();
    virtual void display();
protected:
    int m_pValue;
    string m_pName;

};

#endif
