/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        client.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2017年7月28日, 下午8:43
 */


/**
 * main 函数
 * para:    argc
 * para:    argv
 * return:  int, 0 is ok, other is abnormal
 */
#include "common.h"

int main()
{
    int shmid = CreatShm(4096);
    sleep(3);

    /// 新的进程挂接到那块共享内存空间, 可以直接看到内存中的东西
    char *buf = (char *) shmat(shmid, NULL, 0);

    int numCount = 60;
    while (numCount--)
    {
        printf("%s\n", buf);
        sleep(1);
    }

    shmdt(buf);
    return 0;
}

