#include "Signature.hpp"

// static dict_t dict = forceTypeDictInit(); // don't seem to need it actually !

// E.g. Signature for call u32int_t mockedFunc1("hello world") returning 42 :
static Signature sigTest1("mockedFunc1", 42u, "hello world");

// E.g. Signature for const char* mockedFunc2(123, "hello world", 0xdeadbeef) returning "RTS" :
static Signature sigTest2("mockedFunc2", (const char*)"RTS", 123, "hello world", (void*)0xdeadbeef);


// Demonstrate that library cannot predict all types we need to be able to lookup.
// We need to cope with _any_user_defined_ types as well as basic C types.
//
typedef struct { int i; char* pc; } myStruct_t;
// E.g. Signature for const myStruct_t* mockedFunc3(123) returning (myStruct_t*)0xdeadbeef :
static Signature sigTest3("mockedFunct3", (myStruct_t*)0xdeadbeef, 123); //--> typeCodes2Names map throws out_of_range
