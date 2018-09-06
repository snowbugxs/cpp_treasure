#pragma once
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include "yt/network/eventhandler.h"
#include "yt/network/clientmap.h"
#include "yt/util/protocolstream.h"
#include "yt/util/freesizememallocator.h"
#include "yt/log/log.h"
#include "yt/util/seqmap.h"
#include "yt/util/tss.h"
#include "yt/util/data_block.h"

namespace yt
{
	class DataDecoderBase;
	class ClientMap;
	typedef int (*OnSpectialRequest)(void* client,const char* inbuf,size_t buflen);
	typedef int (*OnClientClose)(int clientid,int threadid);
	class ClientSocketBase : public FDEventHandler
	{
	protected:
		static const int WRITETIMEOUT = 5;
		static const size_t MAXRECVBUFSIZE = 65535;
		static const size_t MAXSENDBUFSIZE = 65535;
	public:
		ClientSocketBase(Reactor *pReactor,DataDecoderBase *decoder,size_t maxrecvbufsize = MAXRECVBUFSIZE,size_t maxsendbufsize = MAXSENDBUFSIZE);
		virtual ~ClientSocketBase();
		virtual void OnFDRead();
		virtual void OnFDWrite();
		virtual void OnFDReadTimeOut();
		virtual void OnFDWriteTimeOut();
		DataBlock* GetRecvbuf();
		DataBlock2* GetSendbuf();
		int SendStream(const WriteStreamImpl &stream);
		int SendStream(const WriteStreamImpl *stream);
		virtual int SendBuf(const char *buf,size_t buflen);
		string GetPeerIp();
		static string GetPeerIp(int fd);
		int GetPeerPort();
		static int GetPeerPort(int fd);
		virtual void Close();
		void SetOnClientClose(OnClientClose p);
		void SetCallBacks(int id,OnSpectialRequest callback);
		bool GetCallBacks(int id,OnSpectialRequest& pdata);
		void SetClientID(int id,int threadid=0);
		int GetClientID();
		int GetThreadID();
	protected:
		DataDecoderBase *m_pDecoder;
		DataBlock m_recvbuf;
		DataBlock2 m_sendbuf;
		OnClientClose m_OnClientClose;
		map<int,OnSpectialRequest> m_allCallBacks;
		int m_id;
		int m_threadid;
	};
	class ClientSocket :public ClientSocketBase
	{
		public:
			ClientSocket(Reactor *pReactor,DataDecoderBase *decoder,ClientMap *pClientMap,int fd,size_t maxrecvbufsize = MAXRECVBUFSIZE,size_t maxsendbufsize = MAXSENDBUFSIZE);
			virtual void Close();
			ClientMap *m_pClientMap;
	};
	class SSLClientSocket :public ClientSocket
	{
		public:
			SSLClientSocket(SSL_CTX *m_ctx,Reactor *pReactor,DataDecoderBase *decoder,ClientMap *pClientMap,int fd,size_t maxrecvbufsize = MAXRECVBUFSIZE,size_t maxsendbufsize = MAXSENDBUFSIZE) : ClientSocket(pReactor,decoder,pClientMap,fd,maxrecvbufsize,maxsendbufsize)
			{
					m_sslcn = SSL_new(m_ctx);
					if(m_sslcn)
					{
						if(SSL_set_fd(m_sslcn, fd) == 0)
						{
							AC_ERROR("SSL_set_fd ERROR");
							m_sslcn = NULL;
							return ;
						}	
                    	SSL_set_accept_state(m_sslcn);
				}	
			}
			virtual void OnFDRead();
			virtual void OnFDWrite();
			virtual void Close();
		private:
			SSL *m_sslcn;
	};
	static const short GETSERVERSYSINFO_C2S2C = -1;

#define RETURNGETSYSINFO(CMD,SEQ,PCLIENTSOCKET)\
	if(CMD == GETSERVERSYSINFO_C2S2C)\
	{\
		struct sysinfo s_info;\
		int error;\
		error = sysinfo(&s_info);\
		if(error == 0)\
		{\
			RUNLOG("GETSERVERSYSINFO_C2S2C,load = %d",(int)s_info.loads[0]);\
			char outbuf[64];\
			BinaryWriteStream2 writestream(outbuf,sizeof(outbuf));\
			writestream.Write(CMD);\
			writestream.Write(SEQ);\
			writestream.Write((int)s_info.loads[0]);\
			writestream.Flush();\
			if(PCLIENTSOCKET->SendStream(writestream) != 0)\
			return -1;\
		}\
		return 0;\
	}
#define GONEGETSYSINFO(CMD) \
	if(CMD == GETSERVERSYSINFO_C2S2C)\
		return 0;
}


