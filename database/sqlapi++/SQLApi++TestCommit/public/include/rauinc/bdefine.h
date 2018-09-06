


#if !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)

#define AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_





#if _MSC_VER > 1000

#pragma once

#endif // _MSC_VER > 1000

#include "cemsg.h"

#include "raupub.h"

#include "comstru.h"

#include "svrlink.h"

#include "logfile.h"



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



// ����ҵ������̣�

// ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��

// ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ

// ����  : ST_PACK *rPack ҵ������������

// ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0

// ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""

typedef int (* APPFUNC)(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg); 



#define INSERT_FUNCTION(funcno,func,comment,coder,pr) {funcno,func,comment,coder,pr,false,0,0,0,0,0},



typedef struct 

{

   unsigned int RequestType;  // �����ܺ�

   APPFUNC  pFunc;            // �����ܺ���ָ�룬��������ڵ�ַ

   char szRTName[80];         // ������ҵ������

   char szProgrammer[20];     // �����Ա��

   int  iPriority;            // ���ȼ� Ŀǰ��Ϊ1,2,3 �Ըߵ���

                              /* ͬʱҲ�����䴦������ȼ�

                                           1 - �����ࣨ���޸����ݵ����󣩻� �ؼ���ѯҵ�� ...

                                           2 - ���ʷ������ݲ�ѯ

                                           3 - ��ʷ������ݲ�ѯ

                              */

   bool bStoped;              // �Ƿ���ʱֹͣ��ҵ��

   unsigned int nSuccess;     // ����ɹ�����

   unsigned int nFail;        // ����ʧ�ܴ���

   double       dTakentime;   // ����ɹ��ۼ�ʱ�� �Ժ���ƣ����ڲ����ڱ�RAC�¸�ҵ��Ĵ����ٶ�

   unsigned int nTt_max;      // �����ʱ��

   unsigned int nTt_min;      // ��С����ʱ��

} TBDefine;



extern TBDefine *g_BDefines;



typedef int (*XPROCESS_M)(TRUSERID *handle,char *rdata,int rdlen,int *iRetCode, char *szMsg);

extern XPROCESS_M pProcess;



typedef int (*XCALLBDFUNC_M)(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);

extern XCALLBDFUNC_M pCallBDFunc;

typedef int (*XWRITEAPPFUNC)(int racBaseFuncNo,int racID);

extern XWRITEAPPFUNC pWriteAppInfo;


int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);


int WriteAppInfo(int racBaseFuncNo,int racID);


RAUPUB_API int ResetBPFunctions();


RAUPUB_API int ListBPFunctions(char *bpfile);

RAUPUB_API int FindBPFunction(unsigned int reqtype);





#ifdef __cplusplus

}

#endif


RAUPUB_API CSvrLink *RAUPubInitialize(TBDefine *pBDefine,XCALLBDFUNC_M pCallFunc,XWRITEAPPFUNC pWriteApp,CLogFile *pLogFile,XPROCESS_M process=NULL);



#undef RAUPUB_API



#endif // !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)

