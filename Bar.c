#include "Bar.h"

// Module Bar impl
#include <assert.h>

// As we are mocking Bar in this code, none of these impls should actually be called.
// But these asserts may help catch build config errors.

// Takes and returns nothing
void Bar_vDoBar0(void){
	assert(!"!!ERROR!! In: (real) void Bar_vDoBar0(void)\n");
}

// Takes nothing
uint32_t Bar_u32DoBar0(void){
	assert(!"!!ERROR!! In: (real) uint32_t Bar_u32DoBar0(void)\n");
}

char* Bar_pcDoBar0(void){
	assert(!"!!ERROR!! In: (real) char* Bar_pcDoBar0(void)\n");
}

void* Bar_pvDoBar3( char* name, int32_t i32Value, uint32_t u32Value ){
    assert(!"\t!!ERROR!! In: (real) char* Bar_pvDoBar3(char*,i32,u32)");
}

