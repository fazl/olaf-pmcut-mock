// Example to help figure out what we need in the PoorMansMock (PMMock) library

// Unit test module Foo and mocking out its dependency, module Bar

// Other module includes
#include "PMCUTMock.hpp"

extern "C" {
  #include "Foo.h"
}

// Library includes
#include <cstdio>

char acHello[] = "hello world";

// HAND WRITTEN
// -------------


// Conceptually,  part of the 'PREPARE' and 'ASSERT' phases of a test
//
extern "C"{

  // Mocked Functions from module Bar using Variadic API
  // API callNonVoidVariadic() expects args: function name, retVal,  args if any
  // Signature (return and args types) deduced by variadic template mechanism
  // which sadly needs the variadic part last i.e. return type must precede args.
  uint32_t Bar_u32DoBar0( void ){
    printf("\tIn: (mock) uint32_t Bar_u32DoBar0(void), register call with mocklib, to return '%u'\n", 42u);
    uint32_t ret = PoorMansCppUTestMock::callNonVoidVariadic("Bar_u32DoBar0", 42u );
    printf("\t..mock returning %u\n", ret);
    return ret;
  }

  char* Bar_pcDoBar0( void ){
    printf("\tIn: (mock) char* Bar_pcDoBar0(void), register call with mocklib, to return '%s'\n", acHello);
    // Expects args: function name, retVal, args
    char* ret = PoorMansCppUTestMock::callNonVoidVariadic("Bar_pcDoBar0", acHello);
    printf("\t..mock returning '%s'\n", ret);
    return ret;
  }

  void* Bar_pvDoBar3( char* strArg0, int32_t i32Arg1, uint32_t u32Arg3 ){
    printf("\tIn: (mock) char* Bar_pvDoBar3(char*,i32,u32), registering call with mocklib..\n");
    // Expects args:                                       function name, retVal,            args 
    void* ret = PoorMansCppUTestMock::callNonVoidVariadic("Bar_pvDoBar3", (void*)0xdeadbeef, strArg0, i32Arg1, u32Arg3 );
    printf("\t..mock returning %p\n", ret);
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
int main(int argc, char** argv){

  if( 1<argc){
    printTypeIds();
  }

  printf( "Unit test of module Foo while mocking out module Bar\n" );

  // Note expected calls to mocked functions
  // // TODO have to record all supplied args when mock registers 'actual call'
  //
  // expect::ErrorHandler_vSetFatalError(ErrorHandler_FATAL_ERRTYPE_FATAL,
  //                                       ErrorHandler_FATAL_ERROR_PWRCYCLE_SEQUENCE,
  //                                       IgnoreParameter::YES);

  // // uint32_t 
  // expect::Bar_u32DoBar0();
  // //char* 
  // expect::Bar_pcDoBar0();
  // //void* 
  // expect::Bar_pvDoBar3( 'joe bloggs', -1i, 42u ); 

  
  // ACT

  printf( "Calling Foo_u32DoFoo1(123u).. \n" );
  uint32_t ret = Foo_u32DoFoo1(123u);
  printf( "Got %u\n", ret );
  
//  mock().checkExpectations();


  return 0;

}