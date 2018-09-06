#pragma once
#include<string>
using namespace std;

#define MAX_QUEUEDATA_LEN 2097152

class base_queuedb
{
	public:
		base_queuedb(){}
		virtual ~base_queuedb() {}
		virtual bool Open(string *strerrdesc) = 0;
		virtual bool Put(string &_key,string &_data,string *strerrdesc) = 0;
		virtual bool Get(string &_key,string &_data,string *strerrdesc) = 0;
		virtual bool Del(string &_key,string *strerrdesc) = 0;
		virtual void Close() = 0;
};
