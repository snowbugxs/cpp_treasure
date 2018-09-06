#pragma once

#ifdef WIN32
#pragma warning (disable:4786)
#endif

#include <set>
#include <vector>
#include <string>
#include <map>
#include <list>


/*委托通用业务报文*/
class CFldOrder
{
public:
	
	CFldOrder():Uid(0),OperUid(0),ContractId(0),OrderID(0),OrderType(0),CancelType(0),BillType(0),OperType(0),BSFlag(0),
		OrderCurPrice(0),OrderPrice(0),SlPrice(0),SPPrice(0),Qty(0.0),Point(0),BackHandQty(0.0),LimitOpen(0),
		LimitClose(0),MatchPrice(0),OrderTime(0), iRet(1)
	{
	}
	
public:
	
	int           Uid;
	int           OperUid;
	int           ContractId;
	int           OrderID;
	unsigned char OrderType;
	int           CancelType;
	unsigned char BillType;
	unsigned char OperType;
	unsigned char BSFlag;
	int	          OrderCurPrice;
	int	          OrderPrice;
	int	          SlPrice;
	int	          SPPrice;
	double	      Qty;
	int	          Point;
	double	      BackHandQty;
	unsigned int LimitOpen;  //orderno
	unsigned int LimitClose; //orderno
	int           MatchPrice; //限价成交价
	int           OrderTime;
	char        strHeadBf[256];
	int           iRet;

};

/*查询请求通用业务报文*/
class CFldBizQueryReq
{
public:

	CFldBizQueryReq():Uid(0), iRet(0)
	{
	}

public:

	int       Uid;
	string    BegTime;
	string    EndTime;
	string    HeadBf;
	int       iRet;
};

/*成交明细查询*/
class CFldMatchDetail
{
public:

	CFldMatchDetail():uid(0),id(0),orderid(0),hdorid(0),matchno(0)
	{

	}

public:
	int     uid;
	int     id;
	int     orderid;
	int     hdorid;
	int     matchno;
	int     mtprice;
	string  ce;
	string  bsflag;
	string  ocflag;
	string  qty;
	string  mttime;
	string  optype;
	string  offsetpl;
};

/*实时增加用户*/
class CFldAddUser
{
public:
	CFldAddUser():iUid(0), iFid(0), dFreeMargin(0.00) {};

	int iUid;
	int iFid;
	double dFreeMargin;
	string strVTid;
};

/*资金信息查询 11900 fund_info2*/
class CFldFundInfo
{
public:

	CFldFundInfo():uid(0),fid(0),iRet(0)
	{
	}

public:

	int     uid;
	int     fid;
	int     iRet;
	string  fmg;
	string  umg;
	string  fzmg;
	string  atin;
	string  atout;
	string  cha;
	string  pl;
	string  interest;
	string  pvbe;
	string  rlbe;
	string  d_rate;
	string  wrate;
	string  windays;
	string  than10days;
	string  dayrank;
	string  weekrank;
	string  winrank;
	string  than10rank;
	string  dchange;
	string  wchange;
	string  profitchange;
	string  tenchange;
	string  date;
	string  amount;
};

/*客户资金流水查询 11901 all_fund_flow_info*/
class CFldFundFlowInfo
{
public:

	CFldFundFlowInfo():uid(0),fid(0),flowid(0),rnno(0),orid(0)
	{
	}

public:

	int      uid;
	int      fid;
	int      flowid;
	int      rnno;
	int      orid;
	string   tedate;
	string   type;
	string   amount;
	string   balance;
	string   descript;
	string   cedate;
};

/*获取限价单信息查询 11994 get_limit_order_info*/
class CFldLimitOrder
{
public:

	CFldLimitOrder():ltorid(0),id(0),uid(0),fid(0),ltprice(0),slprice(0),spprice(0)
	{
	}

public:

	int      ltorid;
	int      id;
	int      uid;
	int      fid;
	int      ltprice;
	int      slprice;
	int      spprice;
	string   bsflag;
	string   qty;
	string   ontime;
	string   orstaus;
};

/*获取建仓单信息查询 11995 get_open_order_info*/
class CFldOpenOrder
{
public:

	CFldOpenOrder():hdorid(0),onorid(0),uid(0),fid(0),id(0),opprice(0),orderprice(0)
	{
	}

public:

	int      hdorid;
	int      onorid;
	int      uid;
	int      fid;
	int      id;
	int      opprice;
	int      orderprice;
	string   bsflag;
	string   qty;
	string   ce;
	string   ontime;
	string   oetype;
};

/*获取平仓单信息查询 11996 get_close_order_info*/
class CFldOffsetOrder
{
public:

	CFldOffsetOrder():hdorid(0),ceorid(0),uid(0),fid(0),id(0),opprice(0),hdprice(0),ceprice(0),orderprice(0)
	{
	}

public:

	int      hdorid;
	int      ceorid;
	int      uid;
	int      fid;
	int      id;
	int      opprice;
	int      hdprice;
	int      ceprice;
	int      orderprice;
	string   bsflag;
	string   qty;
	string   pl;
	string   ce;
	string   ontime;
	string   cetime;
	string   oetype;
};

/*获取持仓单信息查询 11997 get_hold_order_info*/
class CFldPosi
{
public:

	CFldPosi():hdorid(0),uid(0),fid(0),id(0),opprice(0),hdprice(0),slprice(0),spprice(0)
	{
	}

public:

	int      hdorid;
	int      uid;
	int      fid;
	int      id;
	int      opprice;
	int      hdprice;
	int      slprice;
	int      spprice;
	string   interest;
	string   bsflag;
	string   qty;
	string   istrhold;
	string   ontime;
	string   splp;
};


/*查询合约信息 11999 contract_detail_info*/
class CFldContractDetailInfo
{
public:

	CFldContractDetailInfo():id(0),gpid(0),dic(0),aeunit(0),sworder(0),qeceunit(0)
	{
	}
public:

	int  id;
	int  gpid;
	int  dic;
	int  aeunit;
	int  sworder;
	int  qeceunit;
	string  symbol;
	string  name;
	string  spunit;
	string  type;
	string  testatus;
	string  sellvalue;
	string  byvalue;
	string  slvalue;
	string  spvalue;
	string  ltvalue;
	string  pttype;
	string  mnvalue;
	string  mxvalue;
	string  bymxvalue;
	string  slmxvalue;
	string  chargevalue;
	string  usedvalue;
};

//================内存表数据结构==========================================
#define MAX_ID 16     //支持的最大合约数量
#define MAX_GROUP 16  //支持的最大业务组数量

#pragma pack(1)
typedef struct Quote
{
	Quote()
	{
		memset(&m_iId, 0, sizeof(Quote));
	}
	
	int m_iId; // 合约id
	int m_iBuyPrice; // 买价
	int m_iSellPrice; // 卖价
	int m_iPriceTime; // 报价时间
	
} QuoteInfo;

typedef struct s_MarketStatus
{	
	s_MarketStatus()
	{
		memset(&f_contract_id, 0, sizeof(s_MarketStatus));
	}
	
	int f_contract_id;
	int f_status;
	char f_trade_date[16];
	
} MarketStatusInfo;

typedef struct s_PointType
{
	s_PointType()
	{
		memset(&f_contract_id, 0, sizeof(s_PointType));
	}
	
	int f_contract_id;
	int f_point_id;
	int f_id;
	unsigned char f_type;
	double f_sell_value;
	double f_buy_value;
	double f_SL_value;
	double f_SP_value;
	double f_limit_value;
	
} PointTypeInfo;

typedef struct s_MarginType
{
	s_MarginType()
	{
		memset(&f_contract_id, 0, sizeof(s_MarginType));
	}
	
	int f_contract_id;
	int f_margin_id;
	int f_id;
	unsigned char f_type;
	double f_used_value;
	double f_freeze_value;
	double f_maintenance_value;
	double f_market_value;
	
} MarginTypeInfo;

typedef struct s_QtyType
{
	s_QtyType()
	{
		memset(&f_contract_id, 0, sizeof(s_QtyType));
	}
	
	int f_contract_id;
	int f_qty_id;
	int f_id;
	double f_min_value;
	double f_max_value;
	double f_buy_max_value;
	double f_sell_max_value;
	
} QtyTypeInfo;

typedef struct s_ChargeType
{
	s_ChargeType()
	{
		memset(&f_contract_id, 0, sizeof(s_ChargeType));
	}
	
	int f_contract_id;
	int f_charge_id;
	int f_id;
	unsigned char f_type;
	double f_charge_value;
	
} ChargeTypeInfo;

typedef struct s_Contract
{
	s_Contract()
	{
		memset(&f_contract_id, 0, sizeof(s_Contract));
	}
	
	int    f_contract_id;
	int    f_contract_group_id;
	int    f_contract_dic;
	int    f_agree_unit;
	double f_step_unit;
	int    f_show_order;
	unsigned char f_type;
	unsigned char f_trade_status;
	unsigned char f_fluctuat_limit_algr;
	double f_fluctuat_limit_value;//涨跌幅值
	int    f_symbol_exchange_id;
	char   f_symbol[8];
	char   f_symbol_name[16];
	char   f_trade_rights[32];
	
} ContractInfo;

typedef struct s_ShmHq
{
	QuoteInfo stHq[MAX_ID + 1];

} ShmHqData;

typedef struct s_ShmBaseData
{
	MarketStatusInfo stMarketStatus[MAX_ID + 1];
	PointTypeInfo stPointType[MAX_ID + 1];
	MarginTypeInfo stMarginType[MAX_ID + 1];
	QtyTypeInfo stQtyType[MAX_ID + 1];
	ChargeTypeInfo stChargeType[MAX_ID + 1];
	ContractInfo stContract[MAX_ID + 1];

} ShmBizData;

#pragma pack()
