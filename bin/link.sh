#!/bin/sh

mkdir build 2>/dev/null
cd build
# Bar.o omitted as Bar is mocked in UnitTest.cpp
g++ UnitTest.o PMCUTMock.o TypeWrapper.o Foo.o -o UnitTest.exe

