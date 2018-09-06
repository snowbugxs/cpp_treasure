/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:        common.cpp
 * Author:      xuwei.huang
 * Describe:    
 * Created on   2017年7月28日, 下午8:42
 */

#include "common.h"

int common(size_t size, int flags)
{
    key_t key = ftok(PATH_NAME, PROJ_ID);
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }

    /// 获取共享内存的标识符 shmid
    int shmid = shmget(key, size, flags);
    if (shmid < 0)
    {
        perror("shmget");
        printf("shmget, %d \n");
        return -2;
    }
    return shmid;
}

int CreatShm(size_t size)
{
    return common(size, IPC_CREAT | 0666);
}

int GetShm(size_t size)
{
    return common(size, IPC_CREAT | 0666);
}

int DestroyShm(int shmid)
{
    int ret = shmctl(shmid, IPC_RMID, NULL);
    if (ret < 0)
    {
        perror("shmtcl");
        return -3;
    }
    return 0;
}


