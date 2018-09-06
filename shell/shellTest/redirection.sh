#! /bin/bash

NUM=10
#while [[ $NUM -gt 0 ]]
while (( $NUM > 0 ))
do
	echo " hello " >> test.txt
	#let "NUM-=1"
	#let "NUM--"
	NUM=$((NUM-1))
done
