// logfile.h: interface for the CLogFile class.

//

//////////////////////////////////////////////////////////////////////



#if !defined(AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_)

#define AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_

#ifdef _MT   // �����ģ�����ڶ��߳�ϵͳ��ʱ����Ҫ���궨��

#include "mutex.h"

#endif



#ifdef RAUPUB_EXPORTS

#define RAUPUB_API __declspec(dllexport)

#else

#ifdef _WINDOWS

#define RAUPUB_API __declspec(dllimport)

#else

#define RAUPUB_API 

#endif

#endif



#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000





class RAUPUB_API CLogFile  

{

private:

   FILE *fp;      // ��־�ļ����

   char logpath[256];   // ��־�ļ����·��

   int  logdate;        // ��ǰ��־�ļ�����

   time_t lastftime;

   int flashdelay;      // ˢ����ʱ, ��λ��

   int mode;            // 0:����PID��1:��PID



#ifdef _MT

   CMUTEX m_mutex;   // ������

#endif



private:

	bool open();

	void close();

   

public:

	void ToFlush();

	int RemoveOverdueLogFile(int overdue=30);

	bool Open(const char *szLogPath=NULL,int LogFileMode=0);

	void WriteLogEx(int level, const char *pFormat, ...);

	void SetFlushDelay(int iFlushDelayInSecond);

	void Close();

	CLogFile(char *szLogPath=NULL,int fdelay=60);

	virtual ~CLogFile();



};



RAUPUB_API void SetLogShowLevel(int logshowlevel);



#undef RAUPUB_API



//extern int g_ShowLogLevel;

#endif // !defined(AFX_LOGFILE_H__2A6C7BA5_B629_4353_928E_F19768A217CC__INCLUDED_)

