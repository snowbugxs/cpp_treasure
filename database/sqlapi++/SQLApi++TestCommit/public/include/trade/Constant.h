#pragma once

//[前置机]

const unsigned int TID_FRONT_MATCHNOTIFY =                    101015256; //1分布式 01 前置机 rau 成交通知
const unsigned int TID_FRONT_FORCENOTIFY =                    101015257; //1分布式 01 前置机 rau 成交通知
const unsigned int TID_FRONT_HQNOTIFY =                       101010101; //1分布式 01 前置机 rau 行情通知

//[负载均衡] 界面填充TID
const unsigned int TID_LOAD_BASE =                            102000000; //1分布式 02 负载均衡rau
const unsigned int TID_LOAD_REQORDER =                        102012201; //1分布式 02 负载均衡rau 委托业务报文转发
const unsigned int TID_LOAD_REQCANCELORDER =                  102012202; //1分布式 02 负载均衡rau 委托撤单业务报文转发


//[CHECK]
const unsigned int TID_CHECK_BASE =                           103000000; //1分布式 03 检查rau
const unsigned int TID_CHECK_ORDER =                          103012201; //1分布式 03 检查rau 委托单检查
const unsigned int TID_CHECK_CANCELORDER =                    103012202; //1分布式 03 检查rau 撤单检查
const unsigned int TID_CHECK_UPDATEQUOTE =                    103010101; //1分布式 03 检查rau 更新内存行情

//[FUND]
const unsigned int TID_FUND_BASE =                            104000000; //1分布式 04 FUNDrau
const unsigned int TID_FUND_MARKETOPENPOSI =                  104000001; //1分布式 04 FUNDrau 市价单开仓计算
const unsigned int TID_FUND_MARKETOFFSETPOSI =                104000002; //1分布式 04 FUNDrau 市价单平仓计算
const unsigned int TID_FUND_LIMITOPENPOSI =                   104000003; //1分布式 04 FUNDrau 限价单开仓计算
const unsigned int TID_FUND_LIMITOFFSETPOSI =                 104000004; //1分布式 04 FUNDrau 限价单平仓计算
const unsigned int TID_FUND_CANCELLIMITORDER =                104000005; //1分布式 04 FUNDrau 限价单撤单计算
const unsigned int TID_FUND_LIMITMATCH =                      104000006; //1分布式 04 FUNDrau 限价单成交计算
const unsigned int TID_FUND_SPSLMATCH =                       104000007; //1分布式 04 FUNDrau 止盈止损单计算
const unsigned int TID_FUND_FORCEOFFSET =                     104000008; //1分布式 04 FUNDrau 限价单成交计算
const unsigned int TID_FUND_INITDATA =                        104000009; //1分布式 04 FUNDrau 初始化数据加载

//[SYNW]
const unsigned int TID_SYN_BASE =                             105000000;
const unsigned int TID_SYN_MARKETOPENORDER =                  105000001;   //市价开仓
const unsigned int TID_SYN_MARKETOFFSETORDER =                105000002;   //市价平仓
const unsigned int TID_SYN_LIMITOPENORDER =                   105000003;   //限价开仓
const unsigned int TID_SYN_LIMITOFFSETORDER =                 105000004;   //限价平仓
const unsigned int TID_SYN_CANCELORDER =                      105000005;   //撤单 限价单，止盈止损单
const unsigned int TID_SYN_LIMITMATCH =                       105000006;   //限价单成交
const unsigned int TID_SYN_SLSPMATCH =                        105000007;   //止盈止损成交
const unsigned int TID_SYN_FORCEOFFSET =                      105000008;   //强平单计算

//[Query]
const unsigned int TID_QUERY_BASE =                           106000000; //1分布式 06 Query rau
const unsigned int TID_QUERY_CONTRACT =                       106010601; //1分布式 06 Query rau 获取合约信息
const unsigned int TID_QUERY_MATCHDETAIL =                    106011899; //1分布式 06 Query rau 成交明细查询
const unsigned int TID_QUERY_CLIENTFUNDINFO2 =                106011900; //1分布式 06 Query rau 客户资金查询2
const unsigned int TID_QUERY_CLIENTHISFUNDFLOWINFO =          106011901; //1分布式 06 Query rau 客户历史和当前资金流水信息查询

const unsigned int TID_QUERY_SYSTEMTIME =                     106011967; //1分布式 06 Query rau 获取系统时间
const unsigned int TID_QUERY_SCHEDULEORDER =                  106011969; //1分布式 06 Query rau 客户获取指时单信息
const unsigned int TID_QUERY_SCHEDULETRADEPLAN =              106011970; //1分布式 06 Query rau 获取指时交易计划
const unsigned int TID_QUERY_MARKETSTATUS =                   106011985; //1分布式 06 Query rau 查询市场状态


const unsigned int TID_QUERY_LIMITORDERINFO =                 106011994; //1分布式 06 Query rau 限价单信息查询
const unsigned int TID_QUERY_OPENORDERINFO =                  106011995; //1分布式 06 Query rau 建仓单信息查询
const unsigned int TID_QUERY_OFFSETORDERINFO =                106011996; //1分布式 06 Query rau 平仓单信息查询
const unsigned int TID_QUERY_POSIINFO =                       106011997; //1分布式 06 Query rau 持仓单信息查询
const unsigned int TID_QUERY_CLIENTFUNDINFO =                 106011998; //1分布式 06 Query rau 客户资金查询
const unsigned int TID_QUERY_CONTRACTDETAILINFO =             106011999; //1分布式 06 Query rau 合约明细信息查询

//[RISK]
const unsigned int TID_RISK_BASE =                            107000000;
const unsigned int TID_RISK_QUOTE =                           107010101; //1分布式 07 RISK rau 行情计算

//[LOGIN]
const unsigned int TID_LOGIN_BASE =                           108000000;
const unsigned int TID_LOGIN_CERTREQ =                        108010001; //1分布式登录请求
const unsigned int TID_LOGIN_EXIT =                           108010002; //1分布式登录退出(正常/异常)

//[INIT]
const unsigned int TID_INIT_BASE =                            109000000;
const unsigned int TID_INIT_NOTIFY =                          109000001; //1分布式 09 场下初始化信息通知

//[BIZ]
const unsigned int TID_BIZ_BASE =                             110000000;
const unsigned int TID_BIZ_NODE_REGISTER =                    110000001; //1分布式 10 初始化业务模块节点信息注册至场下管理服务

const int PARSE_SUCCESS = 0;
const int RET_SUCCESS = 1;

const int INITFILE_NOT_EXIT = -15;
const int NOT_FULL_PACKAGE = -16;
const int FULL_PACKAGE = -17;
/*解析请求包返回值*/
const int PARSE_ERROR = -18;

/*内存表数据错误*/
const int MEMDATA_NOT_FOUND = -19;
const int MEMDB_DML_ERROR = -20;

/******************************
-1; -- 用户帐户/单据不存在
-2; -- 系统错误
-3; -- 参数错误
-4; -- 商品没有交易权限
-5; -- 不在开市状态
-6; -- 用户没有交易权限
-7; -- 超过持仓限制
-8; -- 超过点差范围
-9; -- 保证金不够
-10; -- 持单量不够  按商品平仓
-11; -- 委托价格非法
-12; -- 止损价格非法
-13; -- 止盈价格非法
-14; -- 无效单
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

/****** 买卖标志 *****/
const unsigned char BS_BUY = 'B';
const unsigned char BS_SELL = 'S';

/******** 委托类型   *****
********* Order Type *****/
//市价委托
const unsigned char OT_MARKET = '1';

//限价委托
const unsigned char OT_LIMIT = '2';

/****  单据类型  ***** 
*****  Bill Type *****/
//1 : 建
const unsigned char BT_OPEN = '1';

//2 : 建带止损
const unsigned char BT_OPEN_SL = '2';

//3 : 建带止盈
const unsigned char BT_OPEN_SP = '3';

//4 : 建带止损止盈
const unsigned char BT_OPEN_SLSP = '4';

//5 : 平
const unsigned char BT_OFFSET = '5';

//6 : 平带止损
const unsigned char BT_OFFSETSL = '6';

//7 : 平带止盈
const unsigned char BT_OFFSETSP = '7';

//8 : 平带止损止盈
const unsigned char BT_OFFSETSLSP = '8';

/***** 提交订单请求指令 *****/
//市价单开仓
const unsigned short TID_MARKETOPENPOSI = 1;

//市价单平仓
const unsigned short TID_MARKETOFFSETPOSI = 2;

//限价单开仓
const unsigned short TID_LIMITOPENPOSI = 3;

//限价单平仓
const unsigned short TID_LIMITOFFSETPOSI = 4;

//限价单撤单
const unsigned short TID_CANCELLIMITORDER = 5;

/**** 撤单类型 ******/
const int CBY_CANCEL_SL = 1;
const int CBY_CANCEL_SP = 2;
const int CBY_CANCEL_LO = 3;

/**** 限价单状态 *****/
const unsigned char LS_ORDER = '1';    //委托
const unsigned char LS_CANCEL = '2';   //撤单
const unsigned char LS_COMPLETE = '3'; //已成交

// 市场状态
typedef enum {
	MarketStatus_Trading = 1, // 交易中 1
		MarketStatus_Pause, // 暂停交易
		MarketStatus_SectionPause, // 节间休息
		MarketStatus_Close, // 收盘 4
		MarketStatus_Open, // 开盘
		MarketStatus_ClearOver, // 结算完成 6
		MarketStatus_Clearing, // 结算中
} MarketStatus;

typedef enum _TraderType {
	TraderType_User = '1',//1 : 用户下单
		TraderType_Agent_User = '2',//2 : 代客下单
		TraderType_System_User = '3',//3 : 系统下单
		TraderType_System_Match = '4',//4 : 撮合成交
		TraderType_System_Cut = '5',//5 : 系统强平
		TraderType_Agent_Cut = '6',//6 : 手工强平
		TraderType_Timer_Trade = '7',//7 : 指时成交
} TraderType;

typedef enum
{
	HTTPMSG = 1,  //HTTP stream
	TJMSG,    //Binary stream
	EMSG,    //EMSG struct
}e_MsgType;

typedef enum
{
	INIT_HQ = 1,     //行情
	INIT_MKSTATUS,   //市场状态
}e_InitType;//初始化通知类型

#define MSGTYPE_VAILD_BIT 0x0000000F

#define REAL_ZERO 1E-6 //实数零
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
