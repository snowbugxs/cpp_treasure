#pragma once

#include "yt/network/eventhandler.h"
#include "yt/util/queue.h"

namespace yt
{
#define AD_PROCESSQUEUEFULL "process queue full"
#define AD_RESULTQUEUEFULL "result queue full"
#define AD_CLIENTOVERFLOW "client over flow"
	static const short AT_PROCESSQUEUEFULL = 1;
	static const short AT_RESULTQUEUEFULL = 2;
	static const short AT_CLIENTOVERFLOW = 3;
	static const short AT_SERVERCONNERROR = 4;
	static const short AT_PACKTIMEOUT = 5;
	static const short AT_MEMERROR = 6;
	static const short AT_SENDBUFFULL = 7;
	static const short AT_RECVBUFFULL = 8;
	static const short AT_WRITECACHEERROR = 9;
	static const short AT_MYSQLTIMEOUT = 10;
	static const short AT_MYSQLERROR = 11;
	static const short AT_WRITEKVDBERROR = 12;
	static const short AT_APPENDKVDBERROR = 13;
	static const short AT_DATAERROR1 = 14;
	static const short AT_DIDSTATISTICS = 15;
	static const short AT_UISTATISTICS = 16;
	enum ALARMLEVEL		//��������
	{
		AL_OK = 0x0,
		AL_1 = 0x01,
		AL_2,
		AL_3,
		AL_4,//ͳ��
	};
#pragma pack(1)
	struct JsonHeader	//�����ͼ�ص�JsonЭ��ͷ,�����ͼ�ص�����ͨѶ����jsonЭ��,Э��ͷ���ö�����
	{
		uint32_t m_len;	//����
		uint16_t m_cmd;	//Э��������
		uint32_t m_seq;	//Э�����к�
	};
#pragma pack()
	struct AlarmInfo
	{
		int level;	//��������
		short type;	//��������
		string info;	//��������
	};
	class Alarm
	{
	public:
		Alarm(FDEventHandler *handler);
		~Alarm();
		bool Init();
		void Alarm0(short type,const char *info);
		void Alarm1(short type,const char *info);
		void Alarm2(short type,const char *info);
		void Alarm3(short type,const char *info);
		void Alarm4(short type,const char *info);
		SyncQueue<AlarmInfo> m_alarmqueue;		//������Ϣ���
	private:
		void Notify(int level,short type,const char *info);	//֪ͨ�����߳�
		int m_fd[2];
		FDEventHandler *m_handler;
	};
	extern Alarm *g_alarm;
	void Alarm1(short type,const char *info);	//����1����
	void Alarm2(short type,const char *info);	//����2����
	void Alarm3(short type,const char *info);	//����3����
	void Alarm4(short type,const char *info);	//����4����
}

