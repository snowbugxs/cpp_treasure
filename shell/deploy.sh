#!/bin/bash

echo
echo "PATH:"
echo $PATH
echo
echo "LD_LIBRARY_PATH:"
echo "增加当前程序运行库路径: -->"
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./../lib/
echo $LD_LIBRARY_PATH
echo

cd ~/temp
tar -zxvf deploy.tar.gz

cd ~/member/bin
./member -s
rm member*
cp ~/temp/member .
./member -d -w
echo "member ok"

cd ~/quantdo/bin
./quantdo -s
rm quantdo*
cp ~/temp/quantdo .
./quantdo -d -w
echo "quantdo ok"

cd ~/scc/bin
./scc -s
rm scc*
cp ~/temp/scc .
./scc -d -w
echo "scc ok"

