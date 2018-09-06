#include "ClassInfo.h"
#include "ObjectFactory.h"



ClassInfo::ClassInfo(const std::string type, FunctionCreateObject createObject)
	:type(type)
	,createObject(createObject)
{
	/*将此类型信息注册于反射工厂中*/
	ObjectFactory::Instance()->Register(this);
}
