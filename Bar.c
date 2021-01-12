#include "Bar.h"

// Module Bar impl
#include <stdio.h>

// Takes and returns nothing
void Bar_vDoBar0(void){
	printf("In: (real) void Bar_vDoBar0(void) and returning nothing");
}

// Takes nothing
uint32_t Bar_u32DoBar0(void){
	printf("In: (real) uint32_t Bar_u32DoBar0(void) and returning 42\n");
	return 42u;
}

