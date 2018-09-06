#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <map>
#include <ext/hash_map>
#include <set>
#include "yt/util/non_copyable.h"
using namespace yt;
using namespace std;
using namespace __gnu_cxx;

namespace yt
{
	class TMEventHandler;
	class FDEventHandler;
	class IdleEventHandler;
	class TMMinHeapQueue;
	class Reactor : public NonCopyable
	{
	public:
		virtual ~Reactor(){}
		virtual void RegisterTimer(TMEventHandler *pHandler) = 0;
		virtual int RegisterReadEvent(FDEventHandler *pHandler,struct timeval *timeout) = 0;
		virtual int RegisterWriteEvent(FDEventHandler *pHandler,struct timeval *timeout) = 0;
		virtual void RegisterIdle(IdleEventHandler *pHandler) = 0;
		virtual void UnRegisterTimer(TMEventHandler *pHandler) = 0;
		virtual int UnRegisterEvent(FDEventHandler *pHandler) = 0;
		virtual int UnRegisterReadEvent(FDEventHandler *pHandler) = 0;
		virtual int UnRegisterWriteEvent(FDEventHandler *pHandler) = 0;
		virtual void UnRegisterIdle(IdleEventHandler *pHandler) = 0;
		virtual bool IsETModel() = 0;
		virtual int Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;
		virtual bool IsStop() = 0;
	};
	class EventHandlerSet
	{
	typedef struct FDEHInfo
	{
		FDEventHandler *pHandler;
		int flag;
	}FDEHINFO;
	public:
	        EventHandlerSet();
		~EventHandlerSet();
		void MarkFDEvent(int fd, int event);
		void CancelFDEvent(int fd, int event);
		void AddFDEventHandler(FDEventHandler *pHandler,int mask,struct timeval *timeout);
		void AddTMEventHandler(TMEventHandler *pHandler);
		void AddIdleEventHandler(IdleEventHandler *pHandler);
		void DelFDEventHandler(int fd,int mask);
		void DelFDEventHandler(int fd);
		void DelTMEventHandler(TMEventHandler *pHandler);
		void DelIdleEventHandler(IdleEventHandler *pHandler);
		FDEventHandler* GetFDEventHandler(int fd,int *flag = NULL );
		inline hash_map<int, int> GetFDEvent(){ return m_FDEvent; };
		void Scan();
		void Idle();
	private:
		hash_map<int, int> m_FDEvent;
		hash_map<int,FDEHINFO > m_FDEHMap; 
		set<TMEventHandler*> m_TMEHList;
		TMMinHeapQueue * m_TMEHQueue;
		set<IdleEventHandler*> m_IdleEHList;
		struct timeval m_lasttime;
	};
	class EPReactor : public Reactor
	{
	public:
		EPReactor() : m_running(true){}
		virtual ~EPReactor(){}
		virtual void RegisterTimer(TMEventHandler *pHandler);
		virtual int RegisterReadEvent(FDEventHandler *pHandler,struct timeval *timeout);
		virtual int RegisterWriteEvent(FDEventHandler *pHandler,struct timeval *timeout);
		virtual void RegisterIdle(IdleEventHandler *pHandler);
		virtual void UnRegisterTimer(TMEventHandler *pHandler);
		virtual int UnRegisterEvent(FDEventHandler *pHandler);
		virtual int UnRegisterReadEvent(FDEventHandler *pHandler);
		virtual int UnRegisterWriteEvent(FDEventHandler *pHandler);
		virtual void UnRegisterIdle(IdleEventHandler *pHandler);
		virtual bool IsETModel();
		virtual int Init();
		virtual void Run();
		virtual void Stop();
		virtual bool IsStop(){return !m_running;};
	private:
		EventHandlerSet m_Set;
		int m_epfd;
		bool m_running;
		time_t m_stoptime;
	};
	class EPETReactor : public Reactor
	{
	public:
		EPETReactor() : m_running(true){}
		virtual ~EPETReactor(){}
		virtual void RegisterTimer(TMEventHandler *pHandler);
		virtual int RegisterReadEvent(FDEventHandler *pHandler,struct timeval *timeout);
		virtual int RegisterWriteEvent(FDEventHandler *pHandler,struct timeval *timeout);
		virtual void RegisterIdle(IdleEventHandler *pHandler);
		virtual void UnRegisterTimer(TMEventHandler *pHandler);
		virtual int UnRegisterEvent(FDEventHandler *pHandler);
		virtual int UnRegisterReadEvent(FDEventHandler *pHandler);
		virtual int UnRegisterWriteEvent(FDEventHandler *pHandler);
		virtual void UnRegisterIdle(IdleEventHandler *pHandler);
		virtual bool IsETModel();
		virtual int Init();
		virtual void Run();
		virtual void Stop();
		virtual void CancelFDEvent(int fd, int event);
		virtual void ProcFDEvent();
		virtual bool IsStop(){return !m_running;};
	private:
		EventHandlerSet m_Set;
		int m_epfd;
		bool m_running;
		time_t m_stoptime;
	};
}
