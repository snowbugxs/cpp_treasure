#!/bin/bash

echo
echo "tresult: udp"
netstat -anp | grep 51801
echo "tseries: udp"
netstat -anp | grep 51803
echo "tinit  : udp"
netstat -anp | grep 51809
echo "front  : udp"
netstat -anp | grep 51811


echo
echo
echo "below is tcp port"
echo
echo "tquery :"
netstat -anp | grep 15820
echo
echo "mdftd  :"
netstat -anp | grep 15822
echo
echo "frontftd : "
netstat -anp | grep 15824
netstat -anp | grep 11000
echo
echo "hotline  : item 1"
netstat -anp | grep 15828
echo
echo "hotline  : item 2"
netstat -anp | grep 15829
echo
echo "arb    : "
netstat -anp | grep 15830
echo
echo "tcp_mdbpub : "
netstat -anp | grep 15834
echo
echo "tinit  : "
netstat -anp | grep 15835




echo
echo
echo "fgateway: port"
netstat -anp | grep 21001
netstat -anp | grep 11001
netstat -anp | grep 11000
netstat -anp | grep 21002
netstat -anp | grep 11002
netstat -anp | grep 21003
netstat -anp | grep 11003
