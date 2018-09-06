#include <map>
#include <iostream>
#include <string>
using namespace std;

typedef void* (*PTRCreateObject)(void);  

class ClassFactory{
private:  
    map<string, PTRCreateObject> m_classMap ;  
    ClassFactory(){}; //构造函数私有化

public:   
    void* getClassByName(string className);  
    void registClass(string name, PTRCreateObject method) ;  
    static ClassFactory& getInstance() ;  
};

void* ClassFactory::getClassByName(string className){  
    map<string, PTRCreateObject>::const_iterator iter;  
    iter = m_classMap.find(className) ;  
    if ( iter == m_classMap.end() )  
        return NULL ;  
    else  
        return iter->second() ;  
}  

void ClassFactory::registClass(string name, PTRCreateObject method){  
    m_classMap.insert(pair<string, PTRCreateObject>(name, method)) ;  
}  

ClassFactory& ClassFactory::getInstance(){
    static ClassFactory sLo_factory;  
    return sLo_factory ;  
}  

class RegisterAction{
public:
    RegisterAction(string className,PTRCreateObject ptrCreateFn){
        ClassFactory::getInstance().registClass(className,ptrCreateFn);
    }
};

#define REGISTER(className)                                             \
    className* objectCreator##className(){                              \
        return new className;                                           \
    }                                                                   \
    RegisterAction g_creatorRegister##className(                        \
        #className,(PTRCreateObject)objectCreator##className)

//test class
class TestClass{
public:
    void m_print(){
        cout<<"hello TestClass"<<endl;
    };
};
REGISTER(TestClass);

int main(int argc,char* argv[]){
    TestClass* ptrObj=(TestClass*)ClassFactory::getInstance().getClassByName("TestClass");
    ptrObj->m_print();
}