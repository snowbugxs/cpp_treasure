#pragma once

//[ǰ�û�]

const unsigned int TID_FRONT_MATCHNOTIFY =                    101015256; //1�ֲ�ʽ 01 ǰ�û� rau �ɽ�֪ͨ
const unsigned int TID_FRONT_FORCENOTIFY =                    101015257; //1�ֲ�ʽ 01 ǰ�û� rau �ɽ�֪ͨ
const unsigned int TID_FRONT_HQNOTIFY =                       101010101; //1�ֲ�ʽ 01 ǰ�û� rau ����֪ͨ

//[���ؾ���] �������TID
const unsigned int TID_LOAD_BASE =                            102000000; //1�ֲ�ʽ 02 ���ؾ���rau
const unsigned int TID_LOAD_REQORDER =                        102012201; //1�ֲ�ʽ 02 ���ؾ���rau ί��ҵ����ת��
const unsigned int TID_LOAD_REQCANCELORDER =                  102012202; //1�ֲ�ʽ 02 ���ؾ���rau ί�г���ҵ����ת��


//[CHECK]
const unsigned int TID_CHECK_BASE =                           103000000; //1�ֲ�ʽ 03 ���rau
const unsigned int TID_CHECK_ORDER =                          103012201; //1�ֲ�ʽ 03 ���rau ί�е����
const unsigned int TID_CHECK_CANCELORDER =                    103012202; //1�ֲ�ʽ 03 ���rau �������
const unsigned int TID_CHECK_UPDATEQUOTE =                    103010101; //1�ֲ�ʽ 03 ���rau �����ڴ�����

//[FUND]
const unsigned int TID_FUND_BASE =                            104000000; //1�ֲ�ʽ 04 FUNDrau
const unsigned int TID_FUND_MARKETOPENPOSI =                  104000001; //1�ֲ�ʽ 04 FUNDrau �м۵����ּ���
const unsigned int TID_FUND_MARKETOFFSETPOSI =                104000002; //1�ֲ�ʽ 04 FUNDrau �м۵�ƽ�ּ���
const unsigned int TID_FUND_LIMITOPENPOSI =                   104000003; //1�ֲ�ʽ 04 FUNDrau �޼۵����ּ���
const unsigned int TID_FUND_LIMITOFFSETPOSI =                 104000004; //1�ֲ�ʽ 04 FUNDrau �޼۵�ƽ�ּ���
const unsigned int TID_FUND_CANCELLIMITORDER =                104000005; //1�ֲ�ʽ 04 FUNDrau �޼۵���������
const unsigned int TID_FUND_LIMITMATCH =                      104000006; //1�ֲ�ʽ 04 FUNDrau �޼۵��ɽ�����
const unsigned int TID_FUND_SPSLMATCH =                       104000007; //1�ֲ�ʽ 04 FUNDrau ֹӯֹ�𵥼���
const unsigned int TID_FUND_FORCEOFFSET =                     104000008; //1�ֲ�ʽ 04 FUNDrau �޼۵��ɽ�����
const unsigned int TID_FUND_INITDATA =                        104000009; //1�ֲ�ʽ 04 FUNDrau ��ʼ�����ݼ���

//[SYNW]
const unsigned int TID_SYN_BASE =                             105000000;
const unsigned int TID_SYN_MARKETOPENORDER =                  105000001;   //�мۿ���
const unsigned int TID_SYN_MARKETOFFSETORDER =                105000002;   //�м�ƽ��
const unsigned int TID_SYN_LIMITOPENORDER =                   105000003;   //�޼ۿ���
const unsigned int TID_SYN_LIMITOFFSETORDER =                 105000004;   //�޼�ƽ��
const unsigned int TID_SYN_CANCELORDER =                      105000005;   //���� �޼۵���ֹӯֹ��
const unsigned int TID_SYN_LIMITMATCH =                       105000006;   //�޼۵��ɽ�
const unsigned int TID_SYN_SLSPMATCH =                        105000007;   //ֹӯֹ��ɽ�
const unsigned int TID_SYN_FORCEOFFSET =                      105000008;   //ǿƽ������

//[Query]
const unsigned int TID_QUERY_BASE =                           106000000; //1�ֲ�ʽ 06 Query rau
const unsigned int TID_QUERY_CONTRACT =                       106010601; //1�ֲ�ʽ 06 Query rau ��ȡ��Լ��Ϣ
const unsigned int TID_QUERY_MATCHDETAIL =                    106011899; //1�ֲ�ʽ 06 Query rau �ɽ���ϸ��ѯ
const unsigned int TID_QUERY_CLIENTFUNDINFO2 =                106011900; //1�ֲ�ʽ 06 Query rau �ͻ��ʽ��ѯ2
const unsigned int TID_QUERY_CLIENTHISFUNDFLOWINFO =          106011901; //1�ֲ�ʽ 06 Query rau �ͻ���ʷ�͵�ǰ�ʽ���ˮ��Ϣ��ѯ

const unsigned int TID_QUERY_SYSTEMTIME =                     106011967; //1�ֲ�ʽ 06 Query rau ��ȡϵͳʱ��
const unsigned int TID_QUERY_SCHEDULEORDER =                  106011969; //1�ֲ�ʽ 06 Query rau �ͻ���ȡָʱ����Ϣ
const unsigned int TID_QUERY_SCHEDULETRADEPLAN =              106011970; //1�ֲ�ʽ 06 Query rau ��ȡָʱ���׼ƻ�
const unsigned int TID_QUERY_MARKETSTATUS =                   106011985; //1�ֲ�ʽ 06 Query rau ��ѯ�г�״̬


const unsigned int TID_QUERY_LIMITORDERINFO =                 106011994; //1�ֲ�ʽ 06 Query rau �޼۵���Ϣ��ѯ
const unsigned int TID_QUERY_OPENORDERINFO =                  106011995; //1�ֲ�ʽ 06 Query rau ���ֵ���Ϣ��ѯ
const unsigned int TID_QUERY_OFFSETORDERINFO =                106011996; //1�ֲ�ʽ 06 Query rau ƽ�ֵ���Ϣ��ѯ
const unsigned int TID_QUERY_POSIINFO =                       106011997; //1�ֲ�ʽ 06 Query rau �ֲֵ���Ϣ��ѯ
const unsigned int TID_QUERY_CLIENTFUNDINFO =                 106011998; //1�ֲ�ʽ 06 Query rau �ͻ��ʽ��ѯ
const unsigned int TID_QUERY_CONTRACTDETAILINFO =             106011999; //1�ֲ�ʽ 06 Query rau ��Լ��ϸ��Ϣ��ѯ

//[RISK]
const unsigned int TID_RISK_BASE =                            107000000;
const unsigned int TID_RISK_QUOTE =                           107010101; //1�ֲ�ʽ 07 RISK rau �������

//[LOGIN]
const unsigned int TID_LOGIN_BASE =                           108000000;
const unsigned int TID_LOGIN_CERTREQ =                        108010001; //1�ֲ�ʽ��¼����
const unsigned int TID_LOGIN_EXIT =                           108010002; //1�ֲ�ʽ��¼�˳�(����/�쳣)

//[INIT]
const unsigned int TID_INIT_BASE =                            109000000;
const unsigned int TID_INIT_NOTIFY =                          109000001; //1�ֲ�ʽ 09 ���³�ʼ����Ϣ֪ͨ

//[BIZ]
const unsigned int TID_BIZ_BASE =                             110000000;
const unsigned int TID_BIZ_NODE_REGISTER =                    110000001; //1�ֲ�ʽ 10 ��ʼ��ҵ��ģ��ڵ���Ϣע�������¹������

const int PARSE_SUCCESS = 0;
const int RET_SUCCESS = 1;

const int INITFILE_NOT_EXIT = -15;
const int NOT_FULL_PACKAGE = -16;
const int FULL_PACKAGE = -17;
/*�������������ֵ*/
const int PARSE_ERROR = -18;

/*�ڴ�����ݴ���*/
const int MEMDATA_NOT_FOUND = -19;
const int MEMDB_DML_ERROR = -20;

/******************************
-1; -- �û��ʻ�/���ݲ�����
-2; -- ϵͳ����
-3; -- ��������
-4; -- ��Ʒû�н���Ȩ��
-5; -- ���ڿ���״̬
-6; -- �û�û�н���Ȩ��
-7; -- �����ֲ�����
-8; -- ������Χ
-9; -- ��֤�𲻹�
-10; -- �ֵ�������  ����Ʒƽ��
-11; -- ί�м۸�Ƿ�
-12; -- ֹ��۸�Ƿ�
-13; -- ֹӯ�۸�Ƿ�
-14; -- ��Ч��
*******************************/
const int USER_ACCOUNT_NOT_EXIT = -1;
const int SYSTEM_ERROR = -2;
const int PARAM_ERROR = -3;
const int CONTRACT_NOT_TRADE_RIGHT = -4;
const int OPENMARKET_STATUS_ERROR = -5;
const int USER_NOT_TRADE_RIGHT = -6;
const int UPPER_POSI_LIMIT = -7;
const int UPPER_POINT_LIMIT = -8;
const int MARGIN_NOT_ENOUGH = -9;
const int POSIBILL_NOT_ENOUGH = -10;
const int ORDER_PRICE_ERROR = -11;
const int SL_PRICE_ERROR = -12;
const int SP_PRICE_ERROR = -13;
const int INVAILD_ORDER = -14;

/****** ������־ *****/
const unsigned char BS_BUY = 'B';
const unsigned char BS_SELL = 'S';

/******** ί������   *****
********* Order Type *****/
//�м�ί��
const unsigned char OT_MARKET = '1';

//�޼�ί��
const unsigned char OT_LIMIT = '2';

/****  ��������  ***** 
*****  Bill Type *****/
//1 : ��
const unsigned char BT_OPEN = '1';

//2 : ����ֹ��
const unsigned char BT_OPEN_SL = '2';

//3 : ����ֹӯ
const unsigned char BT_OPEN_SP = '3';

//4 : ����ֹ��ֹӯ
const unsigned char BT_OPEN_SLSP = '4';

//5 : ƽ
const unsigned char BT_OFFSET = '5';

//6 : ƽ��ֹ��
const unsigned char BT_OFFSETSL = '6';

//7 : ƽ��ֹӯ
const unsigned char BT_OFFSETSP = '7';

//8 : ƽ��ֹ��ֹӯ
const unsigned char BT_OFFSETSLSP = '8';

/***** �ύ��������ָ�� *****/
//�м۵�����
const unsigned short TID_MARKETOPENPOSI = 1;

//�м۵�ƽ��
const unsigned short TID_MARKETOFFSETPOSI = 2;

//�޼۵�����
const unsigned short TID_LIMITOPENPOSI = 3;

//�޼۵�ƽ��
const unsigned short TID_LIMITOFFSETPOSI = 4;

//�޼۵�����
const unsigned short TID_CANCELLIMITORDER = 5;

/**** �������� ******/
const int CBY_CANCEL_SL = 1;
const int CBY_CANCEL_SP = 2;
const int CBY_CANCEL_LO = 3;

/**** �޼۵�״̬ *****/
const unsigned char LS_ORDER = '1';    //ί��
const unsigned char LS_CANCEL = '2';   //����
const unsigned char LS_COMPLETE = '3'; //�ѳɽ�

// �г�״̬
typedef enum {
	MarketStatus_Trading = 1, // ������ 1
		MarketStatus_Pause, // ��ͣ����
		MarketStatus_SectionPause, // �ڼ���Ϣ
		MarketStatus_Close, // ���� 4
		MarketStatus_Open, // ����
		MarketStatus_ClearOver, // ������� 6
		MarketStatus_Clearing, // ������
} MarketStatus;

typedef enum _TraderType {
	TraderType_User = '1',//1 : �û��µ�
		TraderType_Agent_User = '2',//2 : �����µ�
		TraderType_System_User = '3',//3 : ϵͳ�µ�
		TraderType_System_Match = '4',//4 : ��ϳɽ�
		TraderType_System_Cut = '5',//5 : ϵͳǿƽ
		TraderType_Agent_Cut = '6',//6 : �ֹ�ǿƽ
		TraderType_Timer_Trade = '7',//7 : ָʱ�ɽ�
} TraderType;

typedef enum
{
	HTTPMSG = 1,  //HTTP stream
	TJMSG,    //Binary stream
	EMSG,    //EMSG struct
}e_MsgType;

typedef enum
{
	INIT_HQ = 1,     //����
	INIT_MKSTATUS,   //�г�״̬
}e_InitType;//��ʼ��֪ͨ����

#define MSGTYPE_VAILD_BIT 0x0000000F

#define REAL_ZERO 1E-6 //ʵ����
#define SQLSIZE_S  1024
#define SQLSIZE_B  2048

#define FUNCNO_VAILD_BIT 1000000
#define MSGTYPE_VAILD_BIT 0x0000000F

#define MAX_STREAM_SIZE 4000

#define SEQ_FACTOR 100000000

#ifdef WIN32
    #define snprintf _snprintf
#else
    #define snprintf snprintf
#endif
