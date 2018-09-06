#pragma once
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include "yt/network/listensocketbase.h"
#include "yt/network/clientsocket.h"
#include "yt/network/datadecoder.h"
#include "yt/log/log.h"
#include "yt/network/alarm.h"

namespace yt
{
	class ClientSocket;
	class DataDecoderBase;
	class ClientMap;
	template <class CLIENTSOCKET = ClientSocket>
	class UnixListenSocket : public UnixListenSocketBase
	{
	public:
		UnixListenSocket(const char *path,Reactor *pReactor,int clientreadtimeout,DataDecoderBase *pDecoder,ClientMap *pClientMap,int maxclient,size_t maxinbufsize,size_t maxoutbufsize) : 
			UnixListenSocketBase(path,pReactor,clientreadtimeout),
			m_pDecoder(pDecoder),
			m_pClientMap(pClientMap),
			m_maxclient(maxclient),
			m_maxinbufsize(maxinbufsize),
			m_maxoutbufsize(maxoutbufsize){}
		UnixListenSocket(int fd,Reactor *pReactor,int clientreadtimeout,DataDecoderBase *pDecoder,ClientMap *pClientMap,int maxclient,size_t maxinbufsize,size_t maxoutbufsize) : 
			UnixListenSocketBase(fd,pReactor,clientreadtimeout),
			m_pDecoder(pDecoder),
			m_pClientMap(pClientMap),
			m_maxclient(maxclient),
			m_maxinbufsize(maxinbufsize),
			m_maxoutbufsize(maxoutbufsize){}
		virtual void OnAccept(int fd)
		{
			if((int)m_pClientMap->Size() > m_maxclient)
			{
				AC_ERROR("too many client");
				Alarm3(AT_CLIENTOVERFLOW,AD_CLIENTOVERFLOW);
				::close(fd);
				return;
			}
			CLIENTSOCKET *pClient = new(std::nothrow) CLIENTSOCKET(GetReactor(),m_pDecoder,m_pClientMap,fd,m_maxinbufsize,m_maxoutbufsize);
			if(!pClient)
			{
				AC_ERROR("Cann't Allocate client in pool");
				Alarm3(AT_MEMERROR,"cann't allocate client");
				::close(fd);
				return;
			}
			int seq = GetClientIDFromCounter();
			pClient->SetClientID(seq);
			m_pClientMap->Put(seq,pClient);
			if(pClient->RegisterRead(m_clientreadtimeout) != 0)
			{
				AC_ERROR("register read error");
				pClient->Close();
				return;
			}
			if(m_pDecoder)
				m_pDecoder->OnAcceptClient(pClient);
		}
		inline int GetClientIDFromCounter(){
			int seq = m_Counter.Get();
			while(  ( m_pClientMap->Get(seq) )  != NULL   )
			{
				AC_INFO("seq overlap");
				seq = m_Counter.Get();
			}
			return seq;
		}
	private:
		Counter m_Counter;
		DataDecoderBase *m_pDecoder;
		ClientMap *m_pClientMap;
		int m_maxclient;
		size_t m_maxinbufsize;
		size_t m_maxoutbufsize;
	};
	typedef void (*OnAccept2)(void *);
	template <class CLIENTSOCKET = ClientSocket>
	class ListenSocket : public ListenSocketBase
	{
	public:
		ListenSocket(const char *host,int port,Reactor *pReactor,int clientreadtimeout,DataDecoderBase *pDecoder,ClientMap *pClientMap,int maxclient,size_t maxinbufsize,size_t maxoutbufsize) : 
			ListenSocketBase(host,port,pReactor,clientreadtimeout),
			m_pDecoder(pDecoder),
			m_pClientMap(pClientMap),
			m_maxclient(maxclient),
			m_maxinbufsize(maxinbufsize),
			m_maxoutbufsize(maxoutbufsize),
			m_fun(NULL),
			m_ctx(NULL){}
		ListenSocket(int fd,Reactor *pReactor,int clientreadtimeout,DataDecoderBase *pDecoder,ClientMap *pClientMap,int maxclient,size_t maxinbufsize,size_t maxoutbufsize) : 
			ListenSocketBase(fd,pReactor,clientreadtimeout),
			m_pDecoder(pDecoder),
			m_pClientMap(pClientMap),
			m_maxclient(maxclient),
			m_maxinbufsize(maxinbufsize),
			m_maxoutbufsize(maxoutbufsize),
			m_fun(NULL),
			m_ctx(NULL){}
		virtual void OnAccept(int fd)
		{
			if((int)m_pClientMap->Size() > m_maxclient)
			{
				AC_ERROR("too many client");
				Alarm3(AT_CLIENTOVERFLOW,AD_CLIENTOVERFLOW);
				::close(fd);
				return;
			}
			
			ClientSocket *pClient = NULL;
			if(m_ctx == NULL)
			{
				pClient= new(std::nothrow) ClientSocket(GetReactor(),m_pDecoder,m_pClientMap,fd,m_maxinbufsize,m_maxoutbufsize);	//创建客户端对象
			}
			else
			{
				pClient= (ClientSocket*)new(std::nothrow) SSLClientSocket(m_ctx,GetReactor(),m_pDecoder,m_pClientMap,fd,m_maxinbufsize,m_maxoutbufsize);	//创建客户端对象
			}
			if(!pClient)
			{
				AC_ERROR("Cann't Allocate client in pool");
				Alarm3(AT_MEMERROR,"cann't allocate client");
				::close(fd);
				return;
			}
			int seq = GetClientIDFromCounter();
			pClient->SetClientID(seq);
			m_pClientMap->Put(seq,pClient);
			if(pClient->RegisterRead(m_clientreadtimeout) != 0)
			{
				AC_ERROR("register read error");
				pClient->Close();
				return;
			}
			if(m_fun)
				m_fun(pClient);
			if(m_pDecoder)
				m_pDecoder->OnAcceptClient(pClient);
		}
		inline void SetOnAccept2(OnAccept2 fun){
			m_fun = fun;
		}
		inline void SetSSLctx(SSL_CTX *ctx){
			m_ctx = ctx;
		}
		inline int GetClientIDFromCounter(){
			int seq = m_Counter.Get();
			while(( m_pClientMap->Get(seq))  != NULL)
			{
				AC_INFO("seq overlap");
				seq = m_Counter.Get();
			}
			return seq;
		}
	private:
		Counter m_Counter;
		DataDecoderBase *m_pDecoder;
		ClientMap *m_pClientMap;
		int m_maxclient;
		size_t m_maxinbufsize;
		size_t m_maxoutbufsize;
		OnAccept2 m_fun;
		SSL_CTX *m_ctx;
	};
}

