#pragma once
#include "yt/file/file.h"
#include "yt/file/memfilemap.h"
#include "yt/file/filelock.h"
#include "yt/util/mutex.h"
#include "yt/util/tss.h"
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <map>
#include <iostream>
#include <stdint.h>
#include <assert.h>
using namespace yt;
using namespace std;

void Clear(void *p);

#pragma pack(push,1) 
struct HEADER
{
	char locktype;
	char flag1;
	char flag2;
	char flag3;
	char flag4;
	uint64_t datacount;
	uint64_t w_pos;
	uint64_t r_pos;
	uint64_t ex_w_pos;
	uint64_t ex_r_pos;
};
#pragma pack(pop)
enum LOCKTYPE
{
	LOCKPROCESS = 0,
	LOCKTHREAD,
	NOLOCKTYPE
};

class FDS
{
	public:
		~FDS()
		{
			map<string,int>::iterator it;
			for(it = m_map.begin();it != m_map.end();it++)
			{
				close(it->second);
			}
			m_map.clear();
		}
		map<string,int> m_map;
};

class FileQueue 
{
	public:
		FileQueue(const char *pathname,const char *filename,size_t maxlen,bool *isterminated=NULL):m_pathname(pathname),m_filename(filename),m_p_header(NULL),m_start(NULL),m_maxlen(maxlen),m_IsOpenEx(false),m_datalen(8),m_isterminated(isterminated)
	{
	}
		FileQueue(){}
		virtual ~FileQueue(){}
		inline void SetDatalen(size_t len){ m_datalen = len; }
		bool Open(bool isCreate = true,string *strerrdesc = NULL);
		bool Put(char* data,string *strerrdesc = NULL);	
		bool Get(char* data,bool isWait = true,string *strerrdesc = NULL);
		int Peek(int count,vector<uint64_t> &v,string *strerrdesc = NULL);
		void SetLockType(char locktype);
		uint64_t GetCount();
		void Close();
		char GetLockType();
	private:
		bool PutData(char* data,size_t len,string *strerrdesc = NULL);
		bool GetData(char* data,size_t len,string *strerrdesc = NULL);
		int PeekData(int count,vector<uint64_t> &v,string *strerrdesc = NULL);
		int GetProcessLockFD();
		MemFileMapping m_mf;
		File m_file;
		File m_file_ex;
		string m_pathname;
		string m_filename;
		string m_pathfile;
		HEADER *m_p_header;
		char *m_start;
		size_t m_maxlen;
		bool m_IsOpenEx;
		size_t m_datalen;
		char m_usersetlocktype;
		bool *m_isterminated;
		static TSS __tss;
		ThreadMutex m_mutex;
};

