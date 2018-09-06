#ifndef C___Reflection_CKClassFactory_h
#define C___Reflection_CKClassFactory_h

#include<string>
#include<map>
#include<iostream>
using namespace std;

typedef void* (*createClass)(void);

class CKClassFactory
{
public:
    CKClassFactory();

    virtual ~CKClassFactory();

    void* getClassByName(string className);

    void registClass(string name, createClass method);

    static CKClassFactory& sharedClassFactory();

private:
    map<string, createClass> m_classMap;
};


#endif
