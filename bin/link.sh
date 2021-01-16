#!/bin/sh



# Bar.o omitted as Bar is mocked in UnitTest.cpp
cd build && g++ UnitTest.o PMCUTMock.o TypeWrapper.o Foo.o -o UnitTest.exe

