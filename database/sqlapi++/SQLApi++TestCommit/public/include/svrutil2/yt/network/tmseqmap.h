#pragma once

#include "yt/network/eventhandler.h"
#include"yt/util/minheap.h"
#include "yt/util/seqmap.h"
#include "yt/log/log.h"


namespace yt
{
	template <class T>
		class TMT2
		{
			public:
				time_t ti;
				T t;
		};
	template <class T,class TMT = TMT2<T> >
	class TMSeqMap : public SeqMap<TMT>
	{
	public:
		TMSeqMap(){}
		TMSeqMap(int timeout) : m_timeout(timeout){}
		virtual ~TMSeqMap(){}
		inline void SetTimeOut(int timeout){m_timeout = timeout;}
		virtual void OnDel(T& ) = 0;
		virtual void OnTimeOut()
		{
			hash_map<int,TMT> *seqmap = SeqMap<TMT>::GetMap();
			typename hash_map<int,TMT>::iterator it;
			while(!minheap.IsEmpty())
			{
				time_t difsec = time(NULL) -minheap.GetMin().first; 
				if(difsec < m_timeout)
					break;
				pair<time_t ,int > min=minheap.GetMin();
				it=seqmap->find(min.second);
				if(it!=seqmap->end())
				{
					T t=it->second.t;
					seqmap->erase(it);
					OnDel(t);
				}
				minheap.Del(min);
			}
		}
		void Clear()
		{
			hash_map<int,TMT> *seqmap = SeqMap<TMT>::GetMap();
			typename hash_map<int,TMT>::iterator it;
			for(it = seqmap->begin();it != seqmap->end();)
			{
				AC_INFO(" reserve data clear");
				T t/*&t*/ = it->second.t;
				seqmap->erase(it);
				it++;
				OnDel(t);
			}
			seqmap->clear();
			minheap.Clear();
		}
		void Put(int id,T t)
		{
			TMT tmt;
			tmt.ti = time(NULL);
			tmt.t = t;
			if(minheap.Insert(make_pair(tmt.ti,id)))
				SeqMap<TMT>::Put(id,tmt);
		}
		T* Get(int id)
		{
			TMT* pTmt = SeqMap<TMT>::Get(id);
			return &pTmt->t;
		}
		TMT* GetTMT(int id)
		{
			TMT* pTmt = SeqMap<TMT>::Get(id);
			return pTmt;
		}
		MinHeap<pair<time_t,int> > * GetMinHeap()
		{
			return &minheap;
		}
	private:
		int m_timeout;
		MinHeap<pair<time_t,int> > minheap;
	};
}
