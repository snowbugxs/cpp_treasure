#!/bin/sh
#ȡ�����ʱ��
space=1
#ȡ������
num=5
#��־�ļ���
LOGFILE=cpu.log
#�鿴�����б�
process="compositor|tkernel|front"

#ִ������    �ض��ض�λд��
echo "�����Ǹ��ֶε�ͷ" > $LOGFILE
#׷���ض�λд��
ps u >> $LOGFILE
#ѭ��
i=1;
while [[ $i -le $num ]];do
    echo $i;
    ((i=i+1));
	ps aux | grep $USER | grep -E $process | grep -v grep >> $LOGFILE; 
	sleep $space;
done;

#���˵����
#u������ʾ�����û������������� USER��PID��%CPU��%MEM��SZ��RSS��TTY��STAT��STIME��TIME �� COMMAND �ֶ�
#SZ   ??��-l �� l ��־���ý��̺���ӳ��Ĵ�С����λ�� 1KB��
#RSS  ??���̵�ʵ���ڴ棨פ��������С����λ�� 1KB����
#TTY  ??�����б�־�����̵Ŀ��ƹ���վ��
#STAT ?? ��s��u �� v ��־����������״̬��


