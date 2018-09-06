#ifndef _SHMDATA_H_HEADER
#define _SHMDATA_H_HEADER

#define TEXT_SZ 2048



/// 可以将要使用的共享内存设置为一个结构体, 或者数组等等.  
/// 前面部分用于识别和表示, 后段部分为真实信息数据
struct shared_use_st
{
    int written;        //作为一个标志，非0：表示可读，0表示可写
    char text[TEXT_SZ]; //记录写入和读取的文本
};

#endif