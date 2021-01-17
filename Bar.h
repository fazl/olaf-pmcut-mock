#ifndef BAR_H
#define BAR_H 1
// Module Bar interface

#include <stdint.h>

// Takes and returns nothing
void Bar_vDoBar0( void );

// Takes nothing, returns calculated value
uint32_t Bar_u32DoBar0( void );

char*    Bar_pcDoBar0( void );

// TODO: add functions that take args
void*    Bar_pvDoBar3( char* strArg1, int32_t i32Arg2, uint32_t u32Arg3 );

#endif //BAR_H
