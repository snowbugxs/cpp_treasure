/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mysql_help.cpp
 * Author: chengye.ke
 * 
 * Created on 2017å¹?3??13??, ä¸???10:41
 */

#include "mysql_help.h"

mysql_help::mysql_help()
:con(0)
{
}

mysql_help::~mysql_help() {
    mysql_close(con);
}

bool mysql_help::sql_connect(const char* host, const char* account, const char* passwd, const char* db_name) {
    con = mysql_init(0);
    mysql_set_character_set(con, "utf8");
    if (!mysql_real_connect(con, host, account,passwd, db_name, 3306, 0, 0)) {
        return false;
    }
    return true;
}

sql_processor* mysql_help::insert_into(const char* table_name) {
    return insertor.insert_into(con,table_name);
}

sql_processor* mysql_help::update_set(const char* table_name, const char* key, const char* value, const char* symbol) {
    return insertor.update_set(con,table_name,key,value,symbol);
}
