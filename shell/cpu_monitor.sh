#!/bin/sh
#取样间隔时间
space=1
#取样次数
num=5
#日志文件名
LOGFILE=cpu.log
#查看进程列表
process="compositor|tkernel|front"

#执行命令    截断重定位写入
echo "以下是各字段的头" > $LOGFILE
#追加重定位写入
ps u >> $LOGFILE
#循环
i=1;
while [[ $i -le $num ]];do
    echo $i;
    ((i=i+1));
	ps aux | grep $USER | grep -E $process | grep -v grep >> $LOGFILE; 
	sleep $space;
done;

#输出说明：
#u参数显示面向用户的输出。这包括 USER、PID、%CPU、%MEM、SZ、RSS、TTY、STAT、STIME、TIME 和 COMMAND 字段
#SZ   ??（-l 和 l 标志）该进程核心映像的大小，单位是 1KB。
#RSS  ??进程的实际内存（驻留集）大小（单位是 1KB）。
#TTY  ??（所有标志）进程的控制工作站：
#STAT ?? （s、u 和 v 标志）包含进程状态：


