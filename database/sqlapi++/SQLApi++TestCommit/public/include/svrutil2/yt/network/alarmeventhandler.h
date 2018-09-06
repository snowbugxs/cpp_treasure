#pragma once

#include "yt/network/eventhandler.h"
#include "yt/network/clientmap.h"

namespace yt
{
	struct AlarmInfo;
	class AlarmEventHandlerBase : public FDEventHandler
	{
	public:
		AlarmEventHandlerBase(Reactor *pReactor);
		~AlarmEventHandlerBase(){}
		virtual void OnFDRead();
		virtual void OnAlarm(AlarmInfo* ) = 0;
		virtual void OnFDWrite();
		virtual void OnFDReadTimeOut();
		virtual void OnFDWriteTimeOut();
	};
	class AlarmEventHandler : public AlarmEventHandlerBase
	{
	public:
		AlarmEventHandler(Reactor *pReactor,ClientMap *pClientMap);
		void OnAlarm(AlarmInfo *info);
	private:
		ClientMap *m_pClientMap;
	};
}
