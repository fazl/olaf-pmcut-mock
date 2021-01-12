// Example to help figure out what we need in the PoorMansMock (PMMock) library

// Unit test module Foo and mocking out its dependency, module Bar

#include "PMCUTMock.hpp"

extern "C" {
  #include "Foo.h"
  #include <stdio.h>
}

#include <cassert>
#include <map>
#include <string>

// HAND WRITTEN
// -------------


extern "C"{

  // Mocked Function from module Bar
  uint32_t Bar_u32DoBar0( void ){
    printf("\tIn: (mock) uint32_t Bar_u32DoBar0(void), registering call with mocklib..\n");
    uint32_t ret = PoorMansCppUTestMock::callNonVoid<uint32_t>("Bar_u32DoBar0");
    printf("\t..mock returning %u\n", ret);
    return ret;
  }

}

/*
extern "C" void ErrorHandler_vSetFatalError(ErrorHandler_FATAL_ERRTYPE_t tFatatlErrType,
                                            ErrorHandler_FATAL_ERROR_t eError,
                      uint32_t u32CodePointId)
{
    // option 1: return PoorMansCppuTestMock::callNonVoid("ErrorHandler_vSetFatalError", tFatatlErrType, eError, u32CodePointId)
  // option 2: PoorMansCppuTestMock::callVoid("ErrorHandler_vSetFatalError", tFatatlErrType, eError, u32CodePointId)
  // option 3: throw ...
}

// expectations for mocked functions
namespace expect {

void ErrorHandler_vSetFatalError(...)  // TBD does this require at least one named param?-- has all params plus return value
   PoorMansCppuTestMock::setExpectations("ErrorHandler_vSetFatalError", va_args);
   // one possible expectation: expected number of calls (default 1)
}
// in case of void argument, you still want to be able to set the num of calls


static const struct
{
    const char * const         fnName;
  (void const * const)(void) fnPtr;
} poorMansCppuTestMockFnDef[] =
{
    { "ErrorHandler_vSetFatalError", &(expect::ErrorHandler_vSetFatalError),
      { ErrorHandler_FATAL_ERRTYPE_t, ErrorHandler_FATAL_ERROR_t, uint32_t } } // check how param types can be put
                                       // or that
};

*/
typedef std::map<const char* const,const char* const> dict_t;

#define GENPAIR(x) { #x, typeid(x).name() }
const dict_t mope = {
  GENPAIR(char),
  GENPAIR(signed char),
  GENPAIR(unsigned char),
  GENPAIR(short),
  GENPAIR(unsigned short),
  GENPAIR(int),
  GENPAIR(unsigned int),
  GENPAIR(long),
  GENPAIR(unsigned long),
  GENPAIR(int8_t),
  GENPAIR(int16_t),
  GENPAIR(int32_t),
  GENPAIR(int64_t),
  GENPAIR(int_fast8_t),
  GENPAIR(int_fast16_t),
  GENPAIR(int_fast32_t),
  GENPAIR(int_fast64_t),
  GENPAIR(int_least8_t),
  GENPAIR(int_least16_t),
  GENPAIR(int_least32_t),
  GENPAIR(int_least64_t),
  GENPAIR(intmax_t),
  GENPAIR(intptr_t),
  GENPAIR(uint8_t),
  GENPAIR(uint16_t),
  GENPAIR(uint32_t),
  GENPAIR(uint64_t),
  GENPAIR(uint_fast8_t),
  GENPAIR(uint_fast16_t),
  GENPAIR(uint_fast32_t),
  GENPAIR(uint_fast64_t),
  GENPAIR(uint_least8_t),
  GENPAIR(uint_least16_t),
  GENPAIR(uint_least32_t),
  GENPAIR(uint_least64_t),
  GENPAIR(uintmax_t),
  GENPAIR(uintptr_t)
};

const size_t NUM_INT_TYPES = mope.size();

const char* const fundamentalTypeName(const char* const typeIdName ){
  for(dict_t::const_iterator i = mope.begin(); i != mope.end(); ++i){
//    printf("typeid(..).name() of %s --> %s", i->first, i->second);
    if((const std::string&) typeIdName == i->second){
      return i->first; break;
    }
  }
  return "No entry in map has typeid name given!";
}

void printTypeIds(){

  printf(" NUM_INT_TYPES = %u\n",  NUM_INT_TYPES );

  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = mope.begin(); i != mope.end(); ++i){
    printf("typeid(..).name() of %-14s -like %-14s- is %s, \n",
           i->first, fundamentalTypeName(i->second), i->second );
  }
  printf("---------------------------------------\n");
}

int main(void){

  printTypeIds();

  printf( "Unit test of module Foo while mocking out module Bar\n" );

  // ACT

  printf( "Calling Foo_u32DoFoo1(123u).. \n" );
  uint32_t ret = Foo_u32DoFoo1(123u);
  printf( "Got %u\n", ret );

  return 0;

}