#pragma once
#include "base_filequeue.h"
#include "base_queuedb.h"
#include <set>
#include <map>
#include <dirent.h>
#include <iostream>
#include "yt/util/tsvector.h"
#include "yt/util/tsrwcontainer.h"
#include "fileseq.h"
using namespace std;

#pragma pack(push,1) 
struct STATE_HEADER
{
	char closeflag;
	char flag2;
	char flag3;
	char flag4;
};
#pragma pack(pop)

class QueueGroup
{
	public:
		QueueGroup(const char *envhome,size_t cachesize_G,size_t cachesize_B,size_t seqqueuesize,bool *isterminated = NULL);
		QueueGroup(const char *envhome,size_t cachesize_G,size_t cachesize_B,size_t seqqueuesize,const char *statefile,bool *isterminated = NULL);
		virtual ~QueueGroup();
		bool SetSpecialFileQueueSize(map<int,size_t> &m);
		virtual bool Open(string *strerrdesc = NULL);
		bool IsQueueExists(int id);
		bool CreateQueue(int id,char locktype = LOCKPROCESS,string *strerrdesc = NULL);
		bool DelQueue(int id,string *strerrdesc = NULL);
		bool Put(int id,const char*data,size_t len,string *strerrdesc = NULL);
		bool Get(int id,string &str,bool isWait = true,string *strerrdesc = NULL);
		bool Clear(int id,string *strerrdesc = NULL);
		int Peek(int id,int count,vector<string> &v,string *strerrdesc = NULL);
		int PopHead(int id,int count,string *strerrdesc = NULL);
		size_t GetAllIdQueue(set<int> &s);
		size_t GetHasDataIdQueue(set<int> &s);
		uint64_t GetIdQueueCount(int id,string *strerrdesc = NULL);
		uint64_t GetSeq();
		virtual void Close();
	private:
		FileQueue * GetIdQueue(int id);
		bool LoadStateFile(string *strerrdesc);
		bool LoadFileQueue(string *strerrdesc);
		bool OpenDb(string *strerrdesc);
		RWTSMap<int,FileQueue *> m_IDSEQ_Map;
		RWTSMap<int,size_t> m_SpecialFileQueueSize_Map;
		TSSet<int> m_s_hasdataid;
		FileSeq m_seq1;
		FileSeq m_seq2;
		base_queuedb *qdb;
		string m_envhome;
		string m_dbname;
		size_t m_cachesize_G;
		size_t m_cachesize_B;
		size_t m_seqqueuesize;
		bool *m_isterminated;
		bool m_isStartOK;
		bool m_isStop;
		string m_statefilename;
		File m_statefile;
		MemFileMapping m_statemf;
		STATE_HEADER *m_header;
};

