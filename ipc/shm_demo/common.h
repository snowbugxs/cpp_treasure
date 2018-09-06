/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   common.h
 * Author: xuwei.huang
 *
 * Created on 2017年7月28日, 下午8:43
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define PATH_NAME "."
#define PROJ_ID 66

int common(size_t size, int flags);

int CreatShm(size_t size);

int GetShm(size_t size);

int DestroyShm(int shmid);

#endif /* COMMON_H */

