#ifndef __MYPUB_H_

#define __MYPUB_H_


#ifdef RAUPUB_EXPORTS

#define RAUPUB_API __declspec(dllexport)

#else

#ifdef _WINDOWS

#define RAUPUB_API __declspec(dllimport)

#else

#define RAUPUB_API 

#endif

#endif


#ifdef __cplusplus

extern "C" {

#endif


#ifndef BYTE

typedef unsigned char	BYTE;

typedef unsigned short	WORD;

#endif

#ifndef INT4

typedef char			INT1;

typedef short			INT2;

typedef int				INT4;

#endif

#ifndef REAL4

typedef float			REAL4;

typedef double			REAL8;

#endif


//��Windows�£����¶���MAX��MIN��

#ifdef WIN32

#define MAX(a,b) _MAX(a,b)

#define MIN(a,b) _MIN(a,b)

#endif


#ifndef ASSERT

#ifdef _DEBUG

#define ASSERT(booleanExpression )\
	if(!(booleanExpression))\
	{\
		RAISE_DESIGN_ERROR(#booleanExpression);\
	}



#define DebugMessageDisplay(msg)   printf("%s:%d <%s>\n",__FILE__,__LINE__,msg)



#else

#define ASSERT(booleanExpression)

#define DebugMessageDisplay(msg)

#endif

#endif



#include <fcntl.h>

#include <sys/stat.h>

#ifdef WIN32

#include <share.h>

#define sh_fopen(a,b,c) _fsopen(a,b,c)

#include <io.h>

#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)

#else

#define SH_DENYNO    0x40

#define SH_DENYWR    0x20

#define sh_fopen(a,b,c) fopen(a,b)

#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)

#endif





/* ȥ�����ҿո�   */

RAUPUB_API char *mytrim(char *s);


RAUPUB_API char *Strncpy(char *dest,char *source,unsigned int count);


RAUPUB_API char *Strncpy_t(char *dest,char *source,unsigned int count);


RAUPUB_API char *mytrim_r(char *dest);


RAUPUB_API char *Strncpy_rt(char *dest,char *source,unsigned int count);

RAUPUB_API int percolate(char *str);

RAUPUB_API char *getfmttime(void *ptm,int fmttype,char *outstr);


RAUPUB_API void mysleep(unsigned int milliseconds);



#ifndef WIN32

RAUPUB_API unsigned int GetTickCount();

#endif



RAUPUB_API unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1);



RAUPUB_API void DataDumpFile(char *filename,char *data,int datalen);


RAUPUB_API void OutErrorFile(const char *efilename, const char *msg, const char *sourcefile, int lineno);


RAUPUB_API void DebugFileOut(char *dfilename,char *msg,char *sourcefile,int lineno);

RAUPUB_API int RemoveOverdueFile(char *path_mark,char *ext,int overdue);





//�׳�һ��CDesignError�쳣

//@����	msg	char*	ָ���Ĵ�����Ϣ

//@�쳣	CDesignError	�׳����쳣������λ���ڵ�ǰ�ļ���ǰ��

#define RAISE_DESIGN_ERROR(msg) { OutErrorFile("DesignError",msg,__FILE__,__LINE__); exit(-1000);}



//�׳�һ��CRuntimeError

//@����	msg	char*	ָ���Ĵ�����Ϣ

//@�쳣	CRuntimeError	�׳����쳣������λ���ڵ�ǰ�ļ���ǰ��

#define RAISE_RUNTIME_ERROR(msg) { OutErrorFile("RuntimeError",msg,__FILE__,__LINE__); exit(-1001);}


extern int iThisProcID;   // �������ID��ʶ����Ӧ�÷���ܹ����䣬������Ϊ������ϵͳ��Ψһ������OutErrorFile��Ϊ�ļ�����¼���������� 


#if defined(RAUPUB_EXPORTS)||defined(RAUPUBLIB)

#define DEBUG_RUNTIME_MSGOUT(msg) { g_pLogFile->WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }

#else

#define DEBUG_RUNTIME_MSGOUT(msg) { g_LogFile.WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }

#endif



#ifdef __cplusplus

}

#endif


#ifndef PM_INACK 

   #define PM_CLEAR  'X'

   #define PM_INACK  '0'  /* �ǿɿ����� */

   #define PM_ACK    '1'  /* �ɿ�����,��Ҫ�Է����պ�����н���ȷ�ϻص� */

   #define PM_ANSWER '2'  /* �����������ʹ�ã���Ϊ�����͸�Ŀ��㣬�ⲿ���������Ӧ�𷵻ص�ʱ����Ҫ�ٴ��ύ��ԭʼ��BUNIT */

#endif


#ifndef AM_AUTO

   #define AM_AUTO     'A'   // һ�������ݾʹ���Զ����͸�����ͻ���

   #define AM_CONFIRM  'C'   // ������ֻ����ҵ����Ҫ��ŷ��͸�����ͻ���,��Ҫ��AnswerData��AnswerDataPart�ŷ���

#endif



#undef RAUPUB_API



#endif



