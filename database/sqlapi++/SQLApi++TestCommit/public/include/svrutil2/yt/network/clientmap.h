#pragma once
#include "yt/util/seqmap.h"

namespace yt
{
	class ClientSocketBase;
	class ClientMap : public SeqMap<ClientSocketBase*>
	{
	public:
		void Close();
		ClientSocketBase* Get(int seq);
		void SendAll(const char *buf,size_t buflen);
		void SendSomeAll(int id,const char *buf,size_t buflen);
	};
}
