#ifndef C___Reflection_CKWorldClass_h
#define C___Reflection_CKWorldClass_h

#include "CKBaseClass.h"

class CKWorldClass : public CKBaseClass
{
private:
    DECLARE_CLASS(CKWorldClass)

public:
    SYNTHESIZE(CKWorldClass, string, m_pName)

    CKWorldClass();
    virtual ~CKWorldClass();
    static void* createInstance();
    virtual void registProperty();
    virtual void display();
protected:
    string m_pName;

};

#endif
