#include "Signature.hpp"

// static dict_t dict = forceTypeDictInit(); // don't seem to need it actually !

// E.g. Signature for call u32int_t dummyFunc1("hello world") returning 42 :
static Signature sigTest1("dummyFunc1", 42u, "hello world");

// E.g. Signature for const char* dummyFunc2(123, "hello world", 0xdeadbeef) returning "RTS" :
static Signature sigTest2("dummyFunc2", (const char*)"RTS", 123, "hello world", (void*)0xdeadbeef);
