#include "Foo.h"

// Module Foo (uses Module Bar internally)
#include "Bar.h"

#include <stdio.h>

// Takes and returns nothing
void Foo_vDoFoo0(void){
	printf("In: (real) void Foo_vDoFoo0(void), doing some Fooey stuff");
}

// Takes 1 arg, depends on Bar module
uint32_t Foo_u32DoFoo1( uint32_t u32Arg1 ){
	printf("In: (real) uint32_t Foo_u32DoFoo1(uint32_t=%u)\n", u32Arg1);

	// calls to Bar module (mocked in tests)
	
	printf("..and calling Bar_u32DoBar0(void)\n");
	uint32_t u32Ret = Bar_u32DoBar0();
	printf("..which returned %u\n", u32Ret);

	printf("..and next, calling Bar_pcDoBar0(void)\n");
	char* pcRet = Bar_pcDoBar0();
	printf("..which returned '%s'", pcRet);

  	printf("..and next, calling Bar_pvDoBar3('joe bloggs', -1, 42)\n");
	void* pvRet = Bar_pvDoBar3("joe bloggs", -1, 42u);
	printf("..which returned %p\n", pvRet);

	return 3;
}