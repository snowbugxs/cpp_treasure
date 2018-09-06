#!/bin/bash

echo
echo
echo
date

echo "------------------>"
echo "开始100环境更新"
echo "------------------>"

cd ~/02_assign_environment/quantdo/
svn update
echo "svn update success"

cd ~/02_assign_environment/quantdo/bin
rm *
cd ~/02_assign_environment/quantdo/build
make #2>/home/xuwei.huang/02_assign_environment/update_err.log
if [ $? -ne 0 ]
then
	echo "$?"
	echo "make error"
	a=$(date)
	echo "make failure    ${a} " | mail -s "make failure" 1019927127@qq.com 
	exit
else
	echo "$?"
	echo "make successfully"
fi

cd ~/02_assign_environment/quantdo/bin
mv quantdoOrgClear quantdo
tar -zcvf deploy.tar.gz member quantdo scc
echo "tar finish"

echo "100 web transfer start"
scp deploy.tar.gz web@192.168.3.100:/home/web/temp
echo "100 web transfer successfully"
ssh web@192.168.3.100 "sh ~/00_showBackground.sh"
ssh web@192.168.3.100 "sh ~/deploy.sh"

echo "------------------>"
echo "100环境更新完毕"
echo "------------------>"


echo "------------------>"
echo "开始101102环境更新"
echo "------------------>"

#cd ~/02_assign_environment/101102/quantdo/
#svn update
#echo "101102 svn update success"
#
#cd ~/02_assign_environment/101102/quantdo/bin
#rm *
#cd ~/02_assign_environment/101102/quantdo/build
#make #2>/home/xuwei.huang/02_assign_environment/update_err.log
#
#if [ $? -ne 0 ]
#then
#	echo "$?"
#	echo "make error"
#	a=$(date)
#	echo "make failure    ${a} " | mail -s "make failure" 1019927127@qq.com 
#	exit
#else
#	echo "$?"
#	echo "make successfully"
#fi
#
#cd ~/02_assign_environment/101102/quantdo/bin
#mv quantdoOrgClear quantdo
#tar -zcvf deploy.tar.gz member quantdo scc
#echo "101102 tar finish"

echo "------------------>"
echo "101环境更新前休眠"
echo "------------------>"
sleep 1m

echo "101  web1 transfer start"
scp deploy.tar.gz web1@192.168.3.101:/home/web1/temp
echo "101  web1 transfer successfully"
ssh web1@192.168.3.101 "sh ~/00_showBackground.sh"
ssh web1@192.168.3.101 "sh ~/deploy.sh"

echo "------------------>"
echo "101环境更新完毕"
echo "------------------>"


echo "------------------>"
echo "102环境更新前休眠"
echo "------------------>"
sleep 1m

echo "102  web2 transfer start"
scp deploy.tar.gz web2@192.168.3.102:/home/web2/temp
echo "102  web2 transfer successfully"
ssh web2@192.168.3.102 "sh ~/00_showBackground.sh"
ssh web2@192.168.3.102 ". ~/deploy.sh"

echo "------------------>"
echo "102环境更新完毕"
echo "------------------>"

date
echo "------------------>"
echo "所有环境更新成功"
echo "------------------>"
echo
echo
echo
