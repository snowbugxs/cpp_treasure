#include "ObjectFactory.h"
#include "ClassInfo.h"

ObjectFactory::ObjectFactory()
	:m_classInfoMap({})
{

}

ObjectFactory::~ObjectFactory()
{
}

void* ObjectFactory::CreateObject(const std::string& className)
{
	auto iter = m_classInfoMap.find(className);

	/*若未找到该类型，返回nullptr*/
	if (iter==m_classInfoMap.end())
	{
		return nullptr;
	}

	return iter->second->createObject();
}

bool ObjectFactory::Register(ClassInfo* classInfo)
{
	/*若已存在该类型，返回false*/
	if (m_classInfoMap.find(classInfo->type) != m_classInfoMap.end())
	{
		return false;
	}

	m_classInfoMap[classInfo->type] = classInfo;
	return true;
}


ObjectFactory* ObjectFactory::Instance()
{
	static ObjectFactory objectFactory;

	return &objectFactory;
}

