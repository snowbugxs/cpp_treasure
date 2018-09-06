/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    test of sqlapi++
 *              // sqlapi++ 关闭自动提交后, 那么每次执行Excute()之后就开始了一条事务, 知道遇到Commit()结束.
 *              // 语句在Excute()之后就已经完成了执行, 但如果一直不Commit(), 那么该次事务就会sleep在MySQL中
 *              // MySQL关闭自动提交后, 一条链接中如果执行了Select等查询语句, 那么要使用FetchNext取结果集, 知道为NULL(尽量)
 *              // 不然在切换 insert update delete的时候就会报错, 不然Commit就会报错
 *              // mysql自己的api中: 如果有查询出来的结果集, 那么就要使用mysql_store_result()或mysql_use_result()
 *              // 如果其他其他查询则不需要, 但如果调用了也不会有什么影响
 *              
 * Created on   2017年8月15日, 下午2:23
 */


#include <cstdlib>
#include "SQLAPI.h" // main SQLAPI++ header
#include <stdio.h>  // for printf
#include <iostream>

using namespace std;

int test()
{
    SAConnection con; // create connection object
    SACommand cmd; // create command object

    con.Connect(
            "192.168.19.192:3306@cpp_quantdo_101", // database name
            "tradepro", // user name
            "trading", // password
            SA_MySQL_Client);

    con.setAutoCommit(SA_AutoCommitOff);

    cmd.setConnection(&con);

    cmd.setCommandText("SELECT * FROM ts_clientinstrumentright WHERE id>:1 ORDER BY id");
    cmd.Param(1).setAsLong() = 0;
    cmd.Execute();

//    while (cmd.FetchNext())
//    {
//        printf("abc\n");
//    }

    /*printf("Row fetched: commandno = %ld, fieldname = '%s', fieldcontent = '%s' \n", 
                cmd.Field("commandno").asLong(),
                (const char*)cmd.Field("fieldname").asString(),
                (const char*)cmd.Field("fieldcontent").asString());*/

    const char *testSQL = "SELECT count(*) as c FROM ts_clientinstrumentright ";
    cmd.setCommandText(testSQL);
    cmd.Execute();

//    if(cmd.FetchNext())
//    {
//        printf("if      test\n");
//        printf("if      %ld \n", cmd.Field("c").asLong());
//        printf("if      test\n");
//    }
//    
//    while (cmd.FetchNext())
//    {
//        printf("while       test\n");
//        printf("while       %ld \n", cmd.Field("c").asLong());
//        printf("while        test\n");
//    }
    
    cmd.setCommandText("SELECT * FROM  ts_test");
    cmd.Execute();

//    while (cmd.FetchNext())
//    {
//        printf("abc\n");
//    }
    
    
    /// 注意sql语句不要出错
    const char *testSQLInsert = "insert into ts_test(name, score) Values('wz', 81);";
    

    /// 在同一条链接中可以 执行插入和查询等等操作, 不论是自动提交还是非自动提交.
    /// 但如果有查询的结果集没有被全部使用那么执行 插入操作就会报错
    /// 非自动提交在第一个 Excute() 执行后, 就开始事务了, 知道 Commit() 之后此次事务结束
    /// 每次执行select的Execute()尽量使用 while(FetchNext) 取出所有结果集, 避免错误
//    cmd.setCommandText(testSQLInsert);
//    cmd.Execute();
//    if(cmd.RowsAffected() > 0)
//    {
//        printf("insert       ok\n");
//    }
    
//    con.Rollback();
//    printf("Rollback         ok\n");


//    con.Disconnect();
//    printf("con.Disconnect()");
//    return 1;

    con.Commit();


    //    con.Disconnect();

    return 1;
}


int origin_main(int argc, char** argv)
{
    SAConnection con;
    SACommand cmd;
    try
    {
        string database = "192.168.19.192:3306@cpp_quantdo";
        string user = "tradepro";
        string password = "trading";
        SAClient_t CLIENT = SA_MySQL_Client;
        con.Connect(database.c_str(), user.c_str(), password.c_str(), CLIENT);
        con.setAutoCommit(SA_AutoCommitOff);
        string mysqlCommand = "select * from t_subqualification";
        cmd.setConnection(&con);
        cmd.setCommandText(mysqlCommand.c_str());
        cmd.Execute();
        while(cmd.FetchNext())
        {
            printf("%ld  ", cmd.Field("id").asLong());
            //printf("%ld  ", (cmd.Field("custody_plan_id").asLong()));
            //std::cout << (const char*)cmd.Field("trader_id").asString();
            //printf("%ld   ", cmd.Field("custody_plan_id").asLong());
            //printf("%ld  ", cmd.Field("instrument_id").asLong());
            printf("%f   ", cmd.Field("subvolume").asDouble());
            printf("\n");
        }

    cmd.Close();
        //con.Commit();
        SACommand cmd_new;
        cmd_new.setConnection(&con);
        cmd_new.setCommandText(mysqlCommand.c_str());
        cmd_new.setCommandText(mysqlCommand.c_str());
        cmd_new.Execute();
        while(cmd_new.FetchNext())
        {
            printf("%ld  ", cmd_new.Field("id").asLong());
            //printf("%ld  ", cmd.Field("trader_id").asLong());
            //printf("%ld   ", cmd.Field("custody_plan_id").asLong());
            //printf("%ld  ", cmd.Field("instrument_id").asLong());
            printf("%f   ", cmd_new.Field("subvolume").asDouble());
            printf("\n");
        }
        
        con.Disconnect();


    }
    catch(SAException &x)
    {
        try
        {
            con.Rollback();
        }
        catch(SAException &other)
        {

        }
    }


    return 0;
}



int gangli_main(int argc, char* argv[])
{
    SAConnection con; // create connection object
    SACommand cmd;    // create command object

        con.Connect(
            "192.168.3.100:3306@cpp_quantdo",     // database name
            "tradepro",   // user name
            "tradepro",   // password
            SA_MySQL_Client);

    cmd.setConnection(&con);

    cmd.setCommandText("SELECT * FROM ts_tbcommand WHERE CommandNo>:1 ORDER BY CommandNo");    
    cmd.Param(1).setAsLong() = 0;
    cmd.Execute();

    while(cmd.FetchNext())    
    {
      printf("abc\n");
    }

    /*printf("Row fetched: commandno = %ld, fieldname = '%s', fieldcontent = '%s' \n", 
                cmd.Field("commandno").asLong(),
                (const char*)cmd.Field("fieldname").asString(),
                (const char*)cmd.Field("fieldcontent").asString());*/

   const char *testSQL = "SELECT count(*) as c FROM ts_tbcommand ";
   cmd.setCommandText(testSQL);
   cmd.Execute();
   
    while(cmd.FetchNext())
    {
       printf("%ld", cmd.Field("c").asLong());
    } 

    con.Disconnect();   

    return 1;
}




int main(int argc, char *argv[])
{
    test();

    printf("test ok\n");
    return 0;
}
