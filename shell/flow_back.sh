#!/bin/bash

cd ~

mkdir ~/temp_flow
mkdir ~/temp_flow/compositor
mkdir ~/temp_flow/front
mkdir ~/temp_flow/mdkernel
mkdir ~/temp_flow/qkernel
mkdir ~/temp_flow/tinit
mkdir ~/temp_flow/tkernel
mkdir ~/temp_flow/tmdb

cp ~/compositor?/flow/*     ~/temp_flow/compositor
echo "cp ~/compositor?/flow/*     ~/temp_flow/compositor"
cp ~/front?/flow/*          ~/temp_flow/front
echo "cp ~/front?/flow/*          ~/temp_flow/front"
cp ~/mdkernel?/flow/*       ~/temp_flow/mdkernel
echo "cp ~/mdkernel?/flow/*       ~/temp_flow/mdkernel"
cp ~/qkernel?/flow/*        ~/temp_flow/qkernel
echo "cp ~/qkernel?/flow/*        ~/temp_flow/qkernel"
cp ~/tinit?/flow/*          ~/temp_flow/tinit
echo "cp ~/tinit?/flow/*          ~/temp_flow/tinit"
cp ~/tkernel?/flow/*        ~/temp_flow/tkernel
echo "cp ~/tkernel?/flow/*        ~/temp_flow/tkernel"
cp ~/tmdb?/flow/*           ~/temp_flow/tmdb
echo "cp ~/tmdb?/flow/*           ~/temp_flow/tmdb"

tar -zcvf temp_flow.tar.gz temp_flow