#pragma once

#include <sys/types.h>

namespace yt
{
	enum 
	{
		MAX_BLOCK_SIZE = 1048576,
		BLOCK_EXPAND_SIZE = 1024
	};
	enum ECircleCacheMode
	{ 
		SEND_CIRCLE_CACHE = 1, 
		RECV_CIRCLE_CACHE
	};
	class DataBlock
	{
	public:
		DataBlock(size_t maxsize = MAX_BLOCK_SIZE,size_t expandsize = BLOCK_EXPAND_SIZE);
		void Init(size_t maxsize = MAX_BLOCK_SIZE,size_t expandsize = BLOCK_EXPAND_SIZE);
		virtual ~DataBlock();
		inline void SetExpandSize(size_t expandsize){m_expandsize = expandsize;}
		inline void SetMaxSize(size_t maxsize){m_maxsize = maxsize;}
		inline int Append(const char *buf,size_t buflen){return Copy(m_pos,buf,buflen);}
		inline char* GetBuf() const {return m_buf;}
		inline size_t GetPos() const {return m_pos;}
		inline size_t GetSize() const {return m_size;}
		inline void SetMode2(size_t maxexpandsize = 104857600 * 2){
			m_mode = 1;
			m_maxexpandsize2 = maxexpandsize;
		}		
		void InitPos();
		int Copy(size_t pos,const char *buf,size_t buflen);
		int Expand(size_t buflen);
	private:
		char *m_buf;
		size_t m_maxsize;
		size_t m_expandsize;
		size_t m_maxexpandsize2;
		size_t m_pos;
		size_t m_size;
		int m_mode;
	};	
	class DataBlock2
	{	
	public:		
		DataBlock2(size_t maxsize = MAX_BLOCK_SIZE,size_t expandsize = BLOCK_EXPAND_SIZE);
		~DataBlock2();
		void Init(size_t maxsize = MAX_BLOCK_SIZE,size_t expandsize = BLOCK_EXPAND_SIZE);
		void InitPos();
		int GetBuf(char **buf, size_t &size);
		int Append(const char *buf,size_t buflen, ECircleCacheMode mode = RECV_CIRCLE_CACHE);
		void move(size_t size);
		bool empty() { return GetLen() == 0; }		
		inline void SetExpandSize(size_t expandsize){m_expandsize = expandsize;}
		inline void SetMaxSize(size_t maxsize){m_maxsize = maxsize;}
		inline size_t GetSize() const {return m_size;}
		inline void SetMode2(size_t maxexpandsize = 104857600 * 2){
			m_mode = 1;
			m_maxexpandsize2 = maxexpandsize;
		}
		size_t GetLen();
		int Copy(int i, const char *src, size_t len); 	
	private:
		int Expand(size_t buflen);
		void copy(const char *buf, size_t buflen, ECircleCacheMode mode = RECV_CIRCLE_CACHE);
	private:
		char *m_buf;
		size_t m_maxsize;
		size_t m_expandsize;
		size_t m_maxexpandsize2;
		size_t m_bgpos;
		size_t m_endpos;
		size_t m_size;
		int m_mode;
	};
}

