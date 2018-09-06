/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mysql_help.h
 * Author: chengye.ke
 *
 * Created on 2017å¹?3??13??, ä¸???10:41
 */

#ifndef MYSQL_HELP_H
#define MYSQL_HELP_H
#include <mysql/mysql.h>
#include <sstream>
#include <iostream>

using namespace std;

class sql_processor {
public:

    sql_processor(){};

    virtual ~sql_processor() {
    };

    sql_processor* insert_into(MYSQL* con, const char* table_name) {
        con_ = con;
        oss_cmd << "insert into " << table_name << "(";
        return this;
    }
    
    sql_processor* update_set(MYSQL* con, const char* table_name, const char* key, const char* value, const char* symbol) {
        con_ = con;
        oss_cmd << "update " << "stock_list" << " set "<< key << "= '" << value << "' where stock_list.ExchangeID = 'SZSE' and stock_list.Symbol = '" << symbol << "'";
        cout << oss_cmd.str() << endl;
        return this;
    }

    template<typename T>
    sql_processor* set_key_n_nalue(const char* key, T T_value, bool islast = false) {
        oss_key << key;
        oss_value << "'" << T_value << "'";
        if (!islast) {
            oss_key << ",";
            oss_value << ",";
        }
        return this;
    }

    bool sql_command_process() {
        oss_cmd << oss_key.str() << ") " << "VALUES(" << oss_value.str() << ");";
        cout << oss_cmd.str() << endl;
        int rt = mysql_real_query(con_, oss_cmd.str().c_str(), oss_cmd.str().size());
        if (rt) {
            cout << "error: " << mysql_error(con_) << endl;
        }
        oss_key.str("");
        oss_value.str("");
        oss_cmd.str("");
        return !rt;
    }
    
    bool update_process() {
        //oss_cmd << oss_key.str() << ") " << "VALUES(" << oss_value.str() << ");";
        //cout << oss_cmd.str() << endl;
        int rt = mysql_real_query(con_, oss_cmd.str().c_str(), oss_cmd.str().size());
        if (rt) {
            cout << "error: " << mysql_error(con_) << endl;
        }
        cout << "error: " << mysql_error(con_) << endl;
        oss_key.str("");
        oss_value.str("");
        oss_cmd.str("");
        return !rt;
    }
private:
    MYSQL* con_;
    stringstream oss_key;
    stringstream oss_value;
    stringstream oss_cmd;
};

class mysql_help {
public:
    mysql_help();
    bool sql_connect(const char* host, const char* account, const char* passwd, const char* db_name);
    sql_processor* insert_into(const char* table_name);
    sql_processor* update_set(const char* table_name, const char* key, const char* value, const char* symbol);

    virtual ~mysql_help();
private:
    MYSQL *con;
    sql_processor insertor;
};

#endif /* MYSQL_HELP_H */

