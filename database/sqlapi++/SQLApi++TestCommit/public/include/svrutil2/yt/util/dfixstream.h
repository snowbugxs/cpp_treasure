#pragma once

#include "yt/util/protocolstream.h"
#include <map>

using namespace std;

namespace yt
{
	enum DFIXVALUETYPE
	{
		TEXT = 0x01,	//��ͨ�ı�
		RAW,		//������
		REE,		//�����ݼ��׼���
		REA,		//������AES����
		RCF,		//������FASTѹ��
		RCZ,		//������ZLIBѹ��
	};
	static const char SOH = 0x1;
	struct DFixValue
	{
		char *buf;
		size_t buflen;
		DFIXVALUETYPE type;
	};
	class DFixReadStream : public ReadStreamImpl
	{	
		private:
			const char* const ptr;
			const size_t len;
		public:
			map<string,DFixValue> m;
			DFixReadStream(const char *ptr,size_t len);
			virtual ~DFixReadStream(){}
			virtual const char* GetData() const;
			virtual size_t GetSize() const;
			bool Parse();
			bool GetValue(const char *tag,char **buf,size_t &buflen,DFIXVALUETYPE *type = NULL);
	};
	class DFixWriteStream : public WriteStreamImpl
	{
		static const size_t MAXHEADERLEN = 11;
		private:
			char* const ptr;
			const size_t len;
			char* const begin;
			char* cur;
			char *hdrbegin;
		public:
			virtual const char* GetData() const;
			virtual size_t GetSize() const;

			DFixWriteStream(char *ptr,size_t len);
			bool AddInt(const char *tag,int i);
			bool AddText(const char *tag,const char *buf,size_t buflen);
			bool AddRaw(const char *tag,const char *buf,size_t buflen);
			void Clear();
			bool Flush();
	};
}

