/********************************************************

	��ȡ�����ļ���

	�ļ���: profile.h

	˵��: 

	����: 

	�޸�: ���� 2001-04-20

	�޸�ԭ��: �淶����

**********************************************************/

#ifndef __PROFILE_H

#define __PROFILE_H



typedef void (*FUNC_INI2LOG)(const char *fmt,...);



#ifdef RAUPUB_EXPORTS

#define RAUPUB_API __declspec(dllexport)

#else

#ifdef _WINDOWS

#define RAUPUB_API __declspec(dllimport)

#else

#define RAUPUB_API 

#endif

#endif



RAUPUB_API void SetINI2LOGFunc(FUNC_INI2LOG func);



class RAUPUB_API TIniFile

{

	//���������

   FILE *fin,*fout;

	//����ָ��section���Ƶ��ַ���ָ��

	char *titlePos( char *buf, int *len );

	//�Ƿ���һ��section�ַ���

	bool isTitleLine( char *bufPtr );

	//�Ƿ���ָ����section

	bool containTitle( char *buf, const char *section );

	//�ƶ��ļ�ָ�뵽��Ӧ��sectionλ��

	bool gotoSection(const char *section );

	//����ָ��entry���Ƶ��ַ���ָ��

	char *textPos( char *buf, const char *entry );

	//ȥ���ַ���ǰ��Ŀո�

	void stripQuotationChar( char *buf );

	//��ȡһ��entry��ֵ

	int readEntry( const char *entry, char *buf, int bufSize, bool strip );

	//дһ��entry





public:

   char * ReadTString(const char *section,const char *entry,const char *defaultString,char *buffer,int   bufLen);


   static char * LRTrim(char *str);

	//�����ļ�����

	char FileName[128];

	//�������ļ�

	bool Open(const char *filename);

	//��ȡһ��int��entry��ֵ

	int ReadInt( const char *section, const char *entry, int defaultInt);

	//��ȡһ��string�͵�entry��ֵ

	int ReadString( const char *section, const char *entry,const char *defaultString, char *buffer,int bufLen);

	//дһ��string�͵�entry��ָ����section��

	//дһ��int�͵�entry��ָ����section��

	//�ر������ļ�

	void Close();



   TIniFile();

	~TIniFile();

private:

	char * FGetS(char *pbuf,int size,FILE *fp);

	void out_close();

	void in_close();

	char * percolate(char *str);

};



#undef RAUPUB_API



#endif

