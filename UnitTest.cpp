// Example to help figure out what we need in the PoorMansMock (PMMock) library

// Unit test module Foo and mocking out its dependency, module Bar

#include "PMCUTMock.hpp"

extern "C" {
  #include "Foo.h"
  #include <stdio.h>
}


// HAND WRITTEN
// -------------


// Conceptually,  part of the 'PREPARE' and 'ASSERT' phases of a test
//
extern "C"{

  // Mocked Function from module Bar
  uint32_t Bar_u32DoBar0( void ){
    printf("\tIn: (mock) uint32_t Bar_u32DoBar0(void), registering call with mocklib..\n");
    uint32_t ret = PoorMansCppUTestMock::callNonVoid<uint32_t>("Bar_u32DoBar0");
    printf("\t..mock returning %u\n", ret);
    return ret;
  }

  // Mocked Function from module Bar
  char* Bar_pcDoBar0( void ){
    printf("\tIn: (mock) char* Bar_u32DoBar0(void), registering call with mocklib..\n");
    char* ret = PoorMansCppUTestMock::callNonVoid<char*>("Bar_pcDoBar0");
    printf("\t..mock returning 0x%x\n", ret);
    return ret;
  }
}

/*
// example of cpputest mock api usage from (therapy tests TfnDoserMock.cpp):
    mock().actualCall(__func__).withIntParameter("u32Now", u32Now)
                                .withUnsignedIntParameter("tRequestedAmount",tRequestedAmount)
                                .withUnsignedIntParameter("u32DurationSecs",u32DurationSecs)
                                .returning....;


// Note the API example shown below differs from the existing cpputest mock api example above
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
int main(void){

  PoorMansCppUTestMock::printTypeIds();

  printf( "Unit test of module Foo while mocking out module Bar\n" );

  // ACT

  printf( "Calling Foo_u32DoFoo1(123u).. \n" );
  uint32_t ret = Foo_u32DoFoo1(123u);
  printf( "Got %u\n", ret );
  
//  mock().checkExpectations();


  return 0;

}