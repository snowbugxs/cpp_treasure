#if !defined(AFX_RAUSHM_H__24B9323D_EFD2_40DE_AC7B_C68A7B7F7566__INCLUDED_)

#define AFX_RAUSHM_H__24B9323D_EFD2_40DE_AC7B_C68A7B7F7566__INCLUDED_



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000



#ifdef WIN32

#include <windows.h>

typedef int key_t;

typedef HANDLE SHMID;

#define INVALID_ID NULL

#else

/* *********** 

����ϵͳƽ̨�������Ҫ������Щͷ�ļ���

#include <sys/types.h>

#include <sys/ipc.h>

*******************************************************/

#include <sys/shm.h>

typedef int SHMID;

#define INVALID_ID -1

#endif



#ifdef KSSHMT_EXPORTS

#define KSSHMT_API __declspec(dllexport)

#else

#ifdef _WINDOWS

#define KSSHMT_API __declspec(dllimport)

#else

#define KSSHMT_API 

#endif

#endif



class KSSHMT_API CRAUShm  
{

private:

   int m_fileno;        // ���ڼ������ļ�, Ҳ���ǻ����ļ�

   SHMID m_shmid;       // �����ڴ�ID

   int m_size;          // �������ڴ泤��

   void *m_address;     // �����ڴ�ռ��ڱ������еĵ�ַ

   char m_szmsg[256];   // �ڴ����ʱ�����ڴ�Ŵ�����Ϣ



public:

	CRAUShm();
	virtual ~CRAUShm();

	bool Unlock(int offset=0, int len = -1);

	bool Lock(int offset=0,int len=-1);

	bool WriteLock(int offset=0,int len=-1);

	bool ReadLock(int offset=0,int len=-1);

	static bool Remove(const char *name);

	void * Open(const char *name, int shmsize);

	static key_t myftok(const char *path, int ID);

	void * GetSHMPtr();

	char * GetMessage();

	void Close();

private:

	bool locktype(int ltype, unsigned int offset, unsigned int  len);
	bool lockwitype(int ltype, unsigned int offset, unsigned int len);

};



#undef KSSHMT_API



#endif // !defined(AFX_RAUSHM_H__24B9323D_EFD2_40DE_AC7B_C68A7B7F7566__INCLUDED_)

