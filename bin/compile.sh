#!/bin/sh

# TODO add forcing debug mode (maybe map key missing will tell which key missing? Hunt stackover how to..)

mkdir build 2>/dev/null
cd build
pwd
c99 -c ../*.c
# Allegedly -D_GLIBCXX_DEBUG helps to checks STL container operations 
g++ -c -D_GLIBCXX_DEBUG ../*.cpp  


