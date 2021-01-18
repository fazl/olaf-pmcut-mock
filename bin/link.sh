#!/bin/sh



# Bar.o omitted as Bar is mocked in UnitTest.cpp
cd build && g++ -D_GLIBCXX_DEBUG UnitTest.o PMCUTMock.o TypeWrapper.o Foo.o -o UnitTest.exe

