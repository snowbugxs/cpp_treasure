#pragma once
#include <mysql.h>
#include <errmsg.h>
#include "dbserver.h"
#include "mysqldataset.h"

using namespace std;

class DataSet;
class MySqlServerConnect : public DBServerConnect
{
	public:
		MySqlServerConnect() : m_mycnn(NULL),m_curpid(0),m_lastpid(0)
		{
		}
		virtual ~MySqlServerConnect()
		{
			Close();
		}
		virtual bool Connect(const char* ip, const char* user, const char* passwd, int port = 0,unsigned int connecttimeout = 5,const char* pdbname = NULL,unsigned int readtimeout = 0,const char* characterset = "gbk");
		virtual void* GetCnn() { return (void*)m_mycnn;};
		virtual bool IsConnected();
	protected:
		virtual bool Init();
		virtual void Close();
		void OnDBConnect();
		MYSQL* m_mycnn;	
		unsigned long m_curpid;		
		unsigned long m_lastpid;
		string	m_characterset;
};
class MySqlServerOperate : public DBServerOperate
{
	public:
		MySqlServerOperate() : m_cnn(NULL), m_dataset(NULL){};
		MySqlServerOperate(DBServerConnect* cnn, DataSet* dataset = 0) : m_cnn(cnn), m_dataset(dataset){}
		virtual ~MySqlServerOperate(){}
		virtual void Init(DBServerConnect* cnn, DataSet* dataset = 0) { m_cnn = cnn; m_dataset = dataset; }
		virtual bool Exec(const string& sql);
		virtual bool SelectDB(const char* dbname);
		virtual bool Response(int resultCnt=0x7fffffff, bool bgetfielddef = true);		
		virtual bool GetFromSQL(const char* from, const int fromlength, char* sto , unsigned long& stolen);
		bool RPCProcedure(const string& dbname, const string& rpcname, vector<string>& params);
		unsigned long GetLastInsertID();
	protected :
		DBServerConnect* m_cnn;
		DataSet *m_dataset;
};
class MysqlResGuard
{
	public :
		MysqlResGuard(MYSQL_RES *res):m_res(res){}
		~MysqlResGuard()
		{
			if (m_res != NULL)
				mysql_free_result(m_res);
		}	
	private :
		MYSQL_RES *m_res;
};


