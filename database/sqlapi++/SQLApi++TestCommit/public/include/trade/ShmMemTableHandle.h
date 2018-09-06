#pragma once

#include "stdafx.h"
#include "Package.h"
#include "Constant.h"
#include "RAUShm.h"
#include "GuardResult.h"

class CShmQuoteTable
{
public:
	static CShmQuoteTable* Instance()
	{
		static CShmQuoteTable h_s;
		return &h_s;
	}

	~CShmQuoteTable()
	{
	}

	bool Init(const string& strShmFileName)
	{
		if (m_bShmInit)
			return m_bShmInit;

		m_pHqData = (ShmHqData*)m_HqShmHandle.Open(strShmFileName.c_str(), sizeof(ShmHqData));
		if (NULL == m_pHqData)
		{
			return m_bShmInit;
		}
		m_bShmInit = true;

		return m_bShmInit;
	}

	inline void Clean()
	{
		if (NULL != m_pHqData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_HqShmHandle);
			memset((char*)&m_pHqData->stHq[0], 0, sizeof(ShmHqData));
		}
	}

	inline bool SetHq(QuoteInfo& Hq)
	{
		if (Hq.m_iId <= 0 || Hq.m_iId > MAX_ID)
			return false;

		if (NULL != m_pHqData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_HqShmHandle);
			m_pHqData->stHq[Hq.m_iId].m_iId = Hq.m_iId;
			m_pHqData->stHq[Hq.m_iId].m_iBuyPrice = Hq.m_iBuyPrice;
			m_pHqData->stHq[Hq.m_iId].m_iSellPrice = Hq.m_iSellPrice;
			return true;
		} else
			return false;
	}

	inline bool GetHq(QuoteInfo& Hq)
	{
		if (Hq.m_iId <= 0 || Hq.m_iId > MAX_ID)
			return false;

		if (NULL != m_pHqData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_HqShmHandle);
			Hq.m_iId = m_pHqData->stHq[Hq.m_iId].m_iId;
			Hq.m_iBuyPrice = m_pHqData->stHq[Hq.m_iId].m_iBuyPrice;
			Hq.m_iSellPrice = m_pHqData->stHq[Hq.m_iId].m_iSellPrice;
			return true;
		} else
			return false;
	}

private:
	CShmQuoteTable():m_pHqData(NULL),m_bShmInit(false) 
	{
	}

	CRAUShm m_HqShmHandle;
	ShmHqData* m_pHqData;
	bool m_bShmInit;
};


class CShmBaseBizTable
{
public:
	static CShmBaseBizTable* Instance()
	{
		static CShmBaseBizTable h_s;
		return &h_s;
	}

	~CShmBaseBizTable() 
	{
	}

	
	bool Init(const string& strShmFileName)
	{
		if (m_bShmInit)
			return m_bShmInit;
		
		m_pShmBizData = (ShmBizData*)m_BizShmHandle.Open(strShmFileName.c_str(), sizeof(ShmBizData));
		if (NULL == m_pShmBizData)
		{
			return m_bShmInit;
		}
		
		m_bShmInit = true;

		return m_bShmInit;
	}

	inline void Clean()
	{
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			memset((char*)&m_pShmBizData->stMarketStatus[0], 0, sizeof(ShmBizData));
		}
	}

	//查询市场状态表
	inline bool GetMemMarketStatus(MarketStatusInfo& info)
	{
		if (info.f_contract_id < 0 || info.f_contract_id > MAX_ID)
			return false;

		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			strncpy(info.f_trade_date, m_pShmBizData->stMarketStatus[info.f_contract_id].f_trade_date, sizeof(info.f_trade_date));
			info.f_status = m_pShmBizData->stMarketStatus[info.f_contract_id].f_status;
			return true;

		} else
			return false;
	}

	//插入/更新市场状态表
	inline bool SetMemMarketStatus(MarketStatusInfo& info)
	{
		if (info.f_contract_id < 0 || info.f_contract_id > MAX_ID)
			return false;

		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			strncpy(m_pShmBizData->stMarketStatus[info.f_contract_id].f_trade_date, info.f_trade_date, sizeof(info.f_trade_date));
			m_pShmBizData->stMarketStatus[info.f_contract_id].f_status = info.f_status;
			return true;
			
		} else
			return false;
	}

	////////////////////////////////////////////////////////

	//查询点差类型表
	inline bool GetMemPointType(PointTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;

		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			memcpy((char*)&info, (char*)&m_pShmBizData->stPointType[info.f_contract_id], sizeof(PointTypeInfo));
			return true;
			
		} else
			return false;

	}

	//插入/更新点差类型表
	inline bool SetMemPointType(PointTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;

		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			memcpy((char*)&m_pShmBizData->stPointType[info.f_contract_id], (char*)&info, sizeof(PointTypeInfo));
			return true;
			
		} else
			return false;
	}

	////////////////////////////////////////////////////

	//查询保证金类型表
	inline bool GetMemMarginType(MarginTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			memcpy((char*)&info, (char*)&m_pShmBizData->stMarginType[info.f_contract_id], sizeof(MarginTypeInfo));
			return true;
			
		} else
			return false;
	}

	//插入/更新保证金类型表
	inline bool SetMemMarginType(MarginTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			memcpy((char*)&m_pShmBizData->stMarginType[info.f_contract_id], (char*)&info, sizeof(MarginTypeInfo));
			return true;
			
		} else
			return false;
	}

	////////////////////////////////////////////////////

	//查询数量规则类型
	inline bool GetMemQtyType(QtyTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			memcpy((char*)&info, (char*)&m_pShmBizData->stQtyType[info.f_contract_id], sizeof(QtyTypeInfo));
			return true;
			
		} else
			return false;
	}

	//插入/更新数量规则类型
	inline bool SetMemQtyType(QtyTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			memcpy((char*)&m_pShmBizData->stQtyType[info.f_contract_id], (char*)&info, sizeof(QtyTypeInfo));
			return true;
			
		} else
			return false;
	}

	//////////////////////////////////////////////////////

	//查询合约表
	inline bool GetMemContract(ContractInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			memcpy((char*)&info, (char*)&m_pShmBizData->stContract[info.f_contract_id], sizeof(ContractInfo));
			return true;
			
		} else
			return false;
	}

	//查询全部合约表
	inline bool GetALLMemContract(vector<ContractInfo>& vecInfo)
	{
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			int i = 1;
			for (; i <= MAX_ID; i++)
			{
				if (0 == m_pShmBizData->stContract[i].f_contract_id)
				{
					return true;
				}
				vecInfo.push_back(m_pShmBizData->stContract[i]);
			}
			return true;
			
		} else
			return false;
	}

	//插入/更新合约表
	inline bool SetMemContract(ContractInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;

		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			memcpy((char*)&m_pShmBizData->stContract[info.f_contract_id], (char*)&info, sizeof(ContractInfo));
			return true;
			
		} else
			return false;

	}

	////////////////////////////////////////////////////////////////////

	//查询手续费类型
	inline bool GetMemChargeType(ChargeTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmRLockGuard ReadGuard(&m_BizShmHandle);
			memcpy((char*)&info, (char*)&m_pShmBizData->stChargeType[info.f_contract_id], sizeof(ChargeTypeInfo));
			return true;
			
		} else
			return false;
	}

	//插入/更新手续费类型
	inline bool SetMemChargeType(ChargeTypeInfo& info)
	{
		if (info.f_contract_id <= 0 || info.f_contract_id > MAX_ID)
			return false;
		
		if (NULL != m_pShmBizData && m_bShmInit)
		{
			CShmWLockGuard WriteGuard(&m_BizShmHandle);
			memcpy((char*)&m_pShmBizData->stChargeType[info.f_contract_id], (char*)&info, sizeof(ChargeTypeInfo));
			return true;
			
		} else
			return false;
	}

private:

	CShmBaseBizTable():m_pShmBizData(NULL), m_bShmInit(false) {};

	CRAUShm m_BizShmHandle;
	ShmBizData* m_pShmBizData;
	bool m_bShmInit;
};
