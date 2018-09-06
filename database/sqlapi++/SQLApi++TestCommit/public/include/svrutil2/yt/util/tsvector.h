#pragma once

#include "yt/util/mutex.h"
#include "yt/util/lockguard.h"
#include <vector>
#include <list>
#include <set>
#include <string>
#include <map>

using namespace std;

namespace yt
{
	//�̰߳�ȫ������
	template<class T>
	class TSVector : public vector<T> , public ThreadMutex{};

	template<class T>
	class TSList : public list<T> , public ThreadMutex{};

	template <class Key,class Traits=less<Key>,class Allocator=allocator<Key> >
	class TSSet : public set<Key,Traits,Allocator> ,public ThreadMutex{};

	class TSString : public string,public ThreadMutex{};

	template <class Key,class Type,class Traits = less<Key>,class Allocator=allocator<pair <const Key, Type> > >
		class TSMap : public map<Key,Type,Traits,Allocator> , public ThreadMutex{};
}
