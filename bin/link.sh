#!/bin/sh



# Bar.o omitted as Bar is mocked in UnitTest.cpp
cd build && g++ -D_GLIBCXX_DEBUG UnitTest.o PMCUTMock.o Parameter.o Foo.o Signature.o typeidutils.o -o UnitTest.exe

