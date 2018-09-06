#pragma once
#include <set>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "dataset.h"
using namespace std;

class MySqlDataSet_Set : public DataSet
{
	public :
		MySqlDataSet_Set(set<string>* arrayset) : m_arrayset(arrayset){}
		virtual ~MySqlDataSet_Set(){}
		virtual bool onData(const char* data,unsigned long length,const int rowindex,const int fieldindex);
	private:
		set<string>* m_arrayset;
};

class MySqlDataSet_Int : public DataSet
{
	public :
		MySqlDataSet_Int(int * count): m_count(count){}
		virtual ~MySqlDataSet_Int(){}
		virtual bool onData(const char* data,unsigned long length,const int rowindex,const int fieldindex);
 	private:
		int* m_count;
};

class MySqlDataSet_Vector : public DataSet
{
	public :
		MySqlDataSet_Vector(vector<string>* varray) : m_varray(varray) {}
		virtual ~MySqlDataSet_Vector() {}
		void init(vector<string>* varray) { m_varray = varray; }
		virtual bool onData(const char* data,unsigned long length,const int rowindex,const int fieldindex);
	private:
		vector<string>* m_varray;
};

class MySqlDataSet_String : public DataSet
{//使用的时候要注意，所有字段拼到这个string后，最后一个字符为分隔符
 	public :
		MySqlDataSet_String(string* pstr,string spritstr=" ") :m_pstr(pstr),m_spritstr(spritstr){}
		virtual ~MySqlDataSet_String(){}
		virtual bool onData(const char* data,unsigned long length,const int rowindex,const int fieldindex);
	private:
    		string* m_pstr;
		string  m_spritstr;//每个数据字段的分隔符
};

class MySqlDataSet_Vector2: public DataSet
{
	public :
		MySqlDataSet_Vector2(){}
		virtual ~MySqlDataSet_Vector2() {}
		void init(vector<string> varray) { m_varray = varray; }
		virtual bool onData(const char* data,unsigned long length,const int rowindex,const int fieldindex);
		
		vector<string> m_varray;    
};


