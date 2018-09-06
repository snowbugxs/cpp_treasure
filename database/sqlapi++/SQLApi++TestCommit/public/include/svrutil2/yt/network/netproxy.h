#pragma once

#include "yt/network/reactor.h"
#include "yt/network/listensocket.h"
#include "yt/network/datadecoder.h"
#include "yt/network/clientmap.h"
#include "yt/network/dataprocessor.h"
#include "yt/util/tsvector.h"
#include "yt/util/thread.h"

namespace yt
{
	//�첽ͨѶ��������
	template <class CLIENTSOCKET = ClientSocket>
		class NetProxy
		{
			public:
				NetProxy(const char *host,int port,int maxclientcount,int conntimeout,int maxinpacklen,int maxoutpacklen,DataDecoderBase *clientdatadecoder) : m_listener(host,port,&m_reactor,conntimeout,clientdatadecoder,&m_clientmap,maxclientcount,maxinpacklen,maxoutpacklen){}
				NetProxy(int fd,int maxclientcount,int conntimeout,int maxinpacklen,int maxoutpacklen,DataDecoderBase *clientdatadecoder) : m_listener(fd,&m_reactor,conntimeout,clientdatadecoder,&m_clientmap,maxclientcount,maxinpacklen,maxoutpacklen){}
				virtual ~NetProxy(){}
				virtual bool Init()
				{
					if(m_reactor.Init() != 0)
					{
						AC_ERROR("reactor init error");
						return false;
					}
					return true;
				}
				virtual bool Initctx(SSL_CTX *ctx)
				{
					if(m_reactor.Init() != 0)
					{
						AC_ERROR("reactor init error");
						return false;
					}
					if(ctx != NULL)
					{
						m_listener.SetSSLctx(ctx);
					}
					return true;
				}
				virtual bool Start()
				{
					if(m_listener.Listen() != 0)
					{
						AC_ERROR("main listen error");
						return false;
					}
					m_reactor.Run();
					return true;
				}
				virtual void Stop()
				{
					m_reactor.Stop();
				}
				virtual void UnInit()
				{
					m_listener.Close();
					m_clientmap.Close();
				}
				inline Reactor* GetReactor(){
					return &m_reactor;
				}
				inline ClientMap* GetClientMap(){
					return &m_clientmap;
				}
				inline void SetOnAccept2(OnAccept2 fun){
					m_listener.SetOnAccept2(fun);
				}
				inline void SetSSLctx(SSL_CTX *ctx){
					m_listener.SetSSLctx(ctx);
				}
				inline void AddSocket(ClientSocketBase* pClient)
				{
					int seq = m_listener.GetClientIDFromCounter();
					pClient->SetClientID(seq);	//���ÿͻ��˵�id
					m_clientmap.Put(seq,pClient);//����clientmap
				}
				inline void DelSocket(ClientSocketBase* pClient)
				{
					m_clientmap.Del(pClient->GetClientID());
				}
			public:
				EPReactor m_reactor;
				ListenSocket<CLIENTSOCKET> m_listener;
				ClientMap m_clientmap;
		};
	//NetProxyQueueThreadsProcess�Ĵ����߳�
	class ProcessThread : public Thread
	{
		public:
			ProcessThread(SyncQueue<pair<int,string>* > *processqueue,SyncQueue<pair<int,string>* > *outqueue,DataProcessor *processor,TSVector<long> *timelist);
			void Run();
		private:
			SyncQueue<pair<int,string>* > *m_processqueue;
			SyncQueue<pair<int,string>* > *m_outqueue;
			DataProcessor *m_processor;
			TSVector<long> *m_timelist;
	};
	//�߼����������첽֪ͨ��
	class SocketPairEventHandler : public FDEventHandler
	{
		public:
			SocketPairEventHandler(Reactor *pReactor,ClientMap *clientmap,SyncQueue<pair<int,string>* > *outqueue);
			~SocketPairEventHandler(){}
			virtual void OnFDRead();
			virtual void OnFDWrite(){};
			virtual void OnFDReadTimeOut(){};
			virtual void OnFDWriteTimeOut(){};
		private:
			ClientMap *m_clientmap;
			SyncQueue<pair<int,string>* > *m_outqueue;
	};
	//���̴߳������磬�����̳߳ش����������
	class NetProxyQueueThreadsProcess : public NetProxy<>
	{
		public:
			NetProxyQueueThreadsProcess(const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount);
			NetProxyQueueThreadsProcess(const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount,DataDecoder_Q *_clientdatadecoder);
			NetProxyQueueThreadsProcess(int fd,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount,DataDecoder_Q *_clientdatadecoder);
			virtual bool Init();
			virtual bool Start();
			virtual void Stop();
			virtual void UnInit();
			long GetSpeed();
			bool SendAll(const char *buf,size_t buflen);
			bool SendOne(int clientid,const char *buf,size_t buflen);
		public:
			TSVector<long> m_timelist;
			DataDecoder_Q clientdatadecoder;
			DataDecoder_Q *clientdatadecoder2;
			DataProcessor *m_processor;
			SyncQueue<pair<int,string>* > m_processqueue;
			SyncQueue<pair<int,string>* > m_outqueue;
			SocketPairEventHandler m_speh;
			int m_fd[2];
			SocketNotification m_sn;
			int m_threadcount;
			vector<Thread*> m_threadlist;
	};
	unsigned long pthreads_thread_id(void);
	void pthreads_locking_callback(int mode, int type, char *file,int line);
	bool SSLLibInit();
	bool SSLLibUnInit();
	class SSLNetProxyQueueThreadsProcess :public NetProxy<SSLClientSocket>
	{
		public:
			SSLNetProxyQueueThreadsProcess(const char *crt,const char * pkey,const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount,DataDecoder_Q* _clientdatadecoder);
			bool static SSLInit();
			virtual bool Init();
			virtual bool Start();
			virtual void Stop();
			virtual void UnInit();
			long GetSpeed();
			bool SendAll(const char *buf,size_t buflen);
			bool SendOne(int clientid,const char *buf,size_t buflen);
		public:
			const char *m_pachcrt;
			const char *m_pactkey;
			TSVector<long> m_timelist;
			DataDecoder_Q clientdatadecoder;
			DataDecoder_Q *clientdatadecoder2;
			DataProcessor *m_processor;
			SyncQueue<pair<int,string>* > m_processqueue;
			SyncQueue<pair<int,string>* > m_outqueue;
			SocketPairEventHandler m_speh;
			int m_fd[2];
			SocketNotification m_sn;
			int m_threadcount;
			vector<Thread*> m_threadlist;
			SSL_CTX *m_ctx;
	};
	class NetProxyQueueThreadsProcess_Thread : public NetProxyQueueThreadsProcess,public Thread
	{
		public:
			NetProxyQueueThreadsProcess_Thread(const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount);
			NetProxyQueueThreadsProcess_Thread(const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount,DataDecoder_Q *_clientdatadecoder);
			NetProxyQueueThreadsProcess_Thread(int fd,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount,DataDecoder_Q *_clientdatadecoder);
			~NetProxyQueueThreadsProcess_Thread(){};
			void StartThread() { Thread::Start(); }
		private:
			virtual void Run();
			virtual bool Start();
	};
	class SSLNetProxyQueueThreadsProcess_Thread : public SSLNetProxyQueueThreadsProcess,public Thread
	{
		public:
			SSLNetProxyQueueThreadsProcess_Thread(const char *crt,const char * pkey,const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int threadcount,DataDecoder_Q *_clientdatadecoder);
			~SSLNetProxyQueueThreadsProcess_Thread(){};
			void StartThread() { Thread::Start(); }
		private:
			virtual void Run();
			virtual bool Start();
	};
	class NetworkThread;
	
	/** NotifyEventHandler **/
	class NotifyEventHandler : public FDEventHandler
	{
		public:
			NotifyEventHandler(Reactor *pReactor) : FDEventHandler(pReactor) {}
			
			bool Init();
			void Close();

			virtual void OnFDRead(){ RecvNotify(); }
			virtual void OnFDWrite(){};
			virtual void OnFDReadTimeOut(){};
			virtual void OnFDWriteTimeOut(){};
			
			int GetSendFD() { return m_fdpair[0]; }
			int GetRecvFD() { return m_fdpair[1]; }

			virtual void SendNotify(const char* buf, size_t len) = 0;
			virtual void RecvNotify() = 0;

		private:
			int m_fdpair[2];					// 0: ����; 1: ����
	};

	class FdNotifyEventHandler : public NotifyEventHandler
	{
		public:
			FdNotifyEventHandler(Reactor *pReactor) : NotifyEventHandler(pReactor) {}
			
			void SetProcessHandler(NetworkThread *pMyThread) { m_pMyThread = pMyThread; }

			void SendNotify(const char* buf, size_t len);
			void SendNotify(int fd);
			void RecvNotify();

		private:
			NetworkThread *m_pMyThread;
	};

	class OnlyNotifyEventHandler : public NotifyEventHandler, public SocketNotification
	{
		public:
			OnlyNotifyEventHandler(Reactor *pReactor) : NotifyEventHandler(pReactor) {}

			bool Init();
			void SetProcessHandler(NetworkThread *pMyThread) { m_pMyThread = pMyThread; }

			void SendNotify(const char*, size_t) {}
			void RecvNotify();

			void notify();
			
		private:
			NetworkThread *m_pMyThread;
	};

	// �����̣߳�����������У����Լ��������������
	/** NetworkThread **/
	class NetworkThread : public Thread
	{
		public:
		    static const size_t CONNTIMEOUT = 360;                    // ���ӳ�ʱ
		    NetworkThread(int id, int maxclient, int maxoneinpacklen, int maxoutpacklen, SyncQueue<pair<int, pair<int,string>*> > *inqueue, int conntimeout = CONNTIMEOUT);
		    NetworkThread(int id, int maxclient, int maxoneinpacklen,int pttype,int headlen,int maxoutpacklen, SyncQueue<pair<int, pair<int,string>*> > *inqueue, int conntimeout = CONNTIMEOUT);
		    inline int StartThread() {return Thread::Start();}
		    virtual int CalcWeight();
		    virtual bool ApplyClient(int fd);
			void ProcessOutqueue();
			
		    virtual bool Init();	// ��ʼ��
		    virtual bool Start();	// ����
		    virtual void Stop();	// ֹͣ
		    virtual void UnInit();	// һЩ��������
		    virtual void Run();

		private:
		    void InsertClient(ClientSocket *client);

		public:
			int m_id;
			int m_maxclient;									// �̴߳�������ͻ���
			int m_maxoneinpacklen;
			int m_maxoutpacklen;
			int m_conntimeout;
			
			DataDecoder_Q2 clientdatadecoder;					// ���տͻ������������push���������
			FdNotifyEventHandler m_listennotify;				// ��listen������notify
			OnlyNotifyEventHandler m_outqueuenotify;			// ��outqueue������notify
			SyncQueue<pair<int,string>* > m_outqueue;			// �������������
			SyncQueue<pair<int, pair<int,string>*> > *m_inqueue;// ���õ��������

		    EPReactor m_reactor;
		    Counter m_counter;
		    ClientMap m_clientmap;
	};

	// ���������������ÿ��������̵߳�notify
	/** NbListen **/
	class NbListen : public ListenSocketBase
	{
		public:
		    NbListen(int fd, Reactor *pReactor, vector<NetworkThread*> *pthreadlist) : 
		        ListenSocketBase(fd, pReactor, 0), m_pthreadlist(pthreadlist), m_lastid(0) {}
			NbListen(const char *host,int port,Reactor *pReactor,vector<NetworkThread*> *pthreadlist) :
				ListenSocketBase(host, port, pReactor, 0), m_pthreadlist(pthreadlist), m_lastid(0) {}

		    virtual void OnAccept(int fd);

		private:
		    NetworkThread* SelectThread();

		private:
		    vector<NetworkThread*> *m_pthreadlist;
			int m_lastid;
	};

	/** ProcessThread2 **/
	class ProcessThread2 : public Thread
	{
		public:
			ProcessThread2(SyncQueue<pair<int, pair<int,string>*> > *processqueue, vector<NetworkThread*> *m_networkthreadlist, DataProcessor *processor, TSVector<long> *timelist);
			void Run();
		private:
			SyncQueue<pair<int, pair<int,string>*> > *m_processqueue;
			vector<NetworkThread*> *m_networkthreadlist;
			DataProcessor *m_processor;
			TSVector<long> *m_timelist;
	};

	// ��������̣߳�����һ��������У��е������������
	/** NetProxyQueueThreadsProcess2 **/
	class NetProxyQueueThreadsProcess2
	{
		public:
			static const int NETWORK_THREAD_COUNT = 4;
			NetProxyQueueThreadsProcess2(const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int maxoutpacklen,DataProcessor *processor,int processthreadcount,int networkthreadcount = NETWORK_THREAD_COUNT,TMEventHandler* pTMEventHandler = NULL,int heartbeat_timer=5);
			NetProxyQueueThreadsProcess2(const char *host,int port,int maxclientcount,int conntimeout,int maxoneinpacklen,int pttype,int headlen,int maxoutpacklen,DataProcessor *processor,int processthreadcount,int networkthreadcount = NETWORK_THREAD_COUNT,TMEventHandler* pTMEventHandler = NULL,int heartbeat_timer=5);
			virtual ~NetProxyQueueThreadsProcess2() {}
			virtual bool Init();
			virtual bool Start();
			virtual void Stop();
			virtual void UnInit();
			long GetSpeed();
			void SendAll(const char *buf,size_t buflen,int fd = -1);
			void SendSomeOne(const char *buf,size_t buflen,int NetworkThreadIndex,int fd);
			size_t GetClientSize();

		public:
			int m_maxclient;
			int m_conntimeout;
			int m_maxoneinpacklen;
			int m_maxoutpacklen;
			int m_pttype;
			int m_headlen;
			DataProcessor *m_processor;
			
			TSVector<long> m_timelist;
			int m_networkthreadcount;
			int m_processthreadcount;
			vector<Thread*> m_processthreadlist;
			vector<NetworkThread*> m_networkthreadlist;

			NbListen m_listen;
			EPReactor m_reactor;
			ClientMap m_clientmap;
			SyncQueue<pair<int, pair<int,string>*> > m_processqueue;

			TMEventHandler* m_pTMEventHandler;
			int m_heartbeat_timer;
			bool m_bStop;
	};
}

