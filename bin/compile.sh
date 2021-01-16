#!/bin/sh

mkdir build 2>/dev/null
cd build
pwd
c99 -c ../*.c
g++ -c ../*.cpp

