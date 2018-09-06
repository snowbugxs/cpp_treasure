/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        main.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2017年7月28日, 下午8:42
 */


#include "common.h"

int main()
{
    int shmid = CreatShm(4096);
    printf("shmid = %d \n", shmid);
    sleep(3);

    /// 挂接
    /// shmat第二个参数为空, 表示系统分配地址空间, 返回一个虚拟地址
    char *buf = (char *) shmat(shmid, NULL, 0);
    printf("buf = %p \n", buf);

    int i = 0;
    int numCount = 60;
    while (numCount--)
    {
        buf[i] = 'A' + i % 26;
        i++;
        buf[i] = 0;
        sleep(1);
    }

    /// 断开共享内存
    shmdt(buf);
    sleep(3);

    /// 销毁共享内存
    DestroyShm(shmid);

    return 0;
}

