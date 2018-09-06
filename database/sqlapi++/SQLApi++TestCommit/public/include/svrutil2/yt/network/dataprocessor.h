#pragma once

#include "yt/util/non_copyable.h"
#include "yt/log/log.h"
#include<string>
using namespace std;
namespace yt
{
	class ClientSocketBase;
	typedef void (*ParseCallBack)(void* client);
	class DataProcessor : public NonCopyable
	{
	public:
		DataProcessor():m_fun(NULL){}
		virtual ~DataProcessor(){}
		virtual int Process(const char * /*inbuf*/,size_t /*inbuflen*/,string & /*outbuf*/){return 0;};
		virtual int Process(const char * /*inbuf*/,size_t /*inbuflen*/,string & /*outbuf*/,int /*clientid*/){return 0;};
		virtual int Process(const char * /*inbuf*/,size_t /*inbuflen*/,string & /*outbuf*/,int /*NetworkId*/,int /*clientid*/){return 0;};			
		ParseCallBack m_fun;
	};
}

