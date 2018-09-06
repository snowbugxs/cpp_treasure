#ifndef C___Reflection_CKBaseClass_h
#define C___Reflection_CKBaseClass_h

#include "CKDynamicClass.h" 

class CKBaseClass;

typedef void (*setValue)(CKBaseClass *t, void* c);

class CKBaseClass
{
private:
    DECLARE_CLASS(CKBaseClass)

public:
    CKBaseClass();
    virtual ~CKBaseClass();
    static void* createInstance();
    virtual void registProperty();
    virtual void display();
    map<string, setValue> m_propertyMap;
};

#define SYNTHESIZE(classType, varType, varName)    \
public:                                             \
inline static void set##varName(CKBaseClass*cp, void*value){ \
    classType* tp = (classType*)cp ;                        \
    tp->varName = *((varType *)value) ;                      \
}                                                       \
inline varType get##varName(void) const {                \
        return varName;                                      \
}              \


#endif
