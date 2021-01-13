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
	printf("..and calling Bar_u32DoBar0(void)\n");
	uint32_t ret = Bar_u32DoBar0();
	printf("..and returning %u\n", ret);
	return ret;
}