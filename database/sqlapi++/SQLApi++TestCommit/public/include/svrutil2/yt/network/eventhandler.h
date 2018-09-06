#pragma once
#include "yt/util/non_copyable.h"
#include "yt/network/reactor.h"
#include <unistd.h>
#include <sys/time.h>

namespace yt
{
	class EventHandler : public NonCopyable
	{
	public:
		EventHandler(){}
		inline void SetReactor(Reactor *pReactor){m_pReactor = pReactor;}
		virtual ~EventHandler(){}
		inline Reactor* GetReactor(){return m_pReactor;}
		virtual void Close() = 0;
	protected:
		Reactor *m_pReactor;
	};
	class IdleEventHandler : virtual public EventHandler
	{
	public:
		IdleEventHandler(Reactor *pReactor){
			SetReactor(pReactor);
		}
		virtual ~IdleEventHandler(){}
		virtual void OnRun() = 0;
		void RegisterIdle();
		void UnRegisterIdle();
		virtual void Close();
	};
	class TMEventHandler : virtual public EventHandler
	{
	public:
		TMEventHandler(){};
		TMEventHandler(Reactor *pReactor)
		{
			SetReactor(pReactor);
		}
		virtual ~TMEventHandler(){}
		virtual void OnTimeOut() = 0;
		void RegisterTimer(struct timeval *timeout);
		void RegisterTimer(int timeout);
		void UnRegisterTimer();
		virtual void Close();
	public:
		struct timeval to;
		struct timeval regtime;
		struct timeval endtime;
	};
	class FDEventHandler : virtual public EventHandler
	{
	public:
		FDEventHandler(Reactor *pReactor):m_fd(0){
			SetReactor(pReactor);
		}
		FDEventHandler(){}
		virtual ~FDEventHandler(){}
		inline void SetFD(int fd){m_fd = fd;}
		virtual void OnFDRead() = 0;
		virtual void OnFDWrite() = 0;
		virtual void OnFDReadTimeOut() = 0;
		virtual void OnFDWriteTimeOut() = 0;
		int RegisterRead(struct timeval *timeout);
		int RegisterRead(int timeout);
		int RegisterWrite(struct timeval *timeout);
		int RegisterWrite(int timeout);
		int UnRegisterRead();
		int UnRegisterWrite();
		inline int GetFD() const {return m_fd;}
		int SetNonBlocking(bool blocking = true);
		static int SetNonBlocking(int fd,bool blocking = true);	
		virtual void Close();
	protected:
		int m_fd;
	};
}

