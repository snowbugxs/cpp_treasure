#include "yt/file/file.h"
#include "yt/file/memfilemap.h"
#include "yt/file/filelock.h"
#include "yt/util/mutex.h"
#include "yt/util/tss.h"
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <math.h>
#include <stdint.h>
using namespace yt;
using namespace std;

void FileSeq_Clear(void *p);

#define MINVALUE 1
#define MAXVALUE (uint64_t)(pow(2,sizeof(uint64_t)*8)-100)

class FileSeq
{
	public:
		FileSeq(const char *pathname,const char *filename,uint64_t minvalue = MINVALUE,uint64_t maxvalue = MAXVALUE);
		FileSeq(uint64_t minvalue = MINVALUE,uint64_t maxvalue = MAXVALUE);
		inline void SetPathName(const char *pathname){m_pathname.assign(pathname);}
		inline void SetFileName(const char *filename){m_filename.assign(filename);}
		bool Open(bool isCreate = true,string *strerrdesc = NULL);
		bool Get(uint64_t &seq,string *strerrdesc = NULL);
		void Close();
	private:
		int GetProcessLockFD();
		MemFileMapping m_mf;
		File m_file;
		string m_pathname;
                string m_filename;
		string m_pathfile;
		uint64_t m_minvalue;
		uint64_t m_maxvalue;
		uint64_t *m_seq;
		TSS m_tss;
		
};
