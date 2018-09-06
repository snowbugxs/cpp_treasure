/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file_watch.h
 * Author: chengye.ke
 *
 * Created on 2017年3月13日, 上午10:47
 */

#ifndef FILE_WATCH_H
#define FILE_WATCH_H
#include <sys/inotify.h>
#define MAX_WD 256
class file_watch {
public:
    file_watch();
    virtual ~file_watch();
private:
    int inotify_fd;
    int wd[MAX_WD];
};

#endif /* FILE_WATCH_H */

