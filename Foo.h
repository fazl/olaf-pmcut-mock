#ifndef FOO_H
#define FOO_H 1

// Module Foo interface
// Not visible here, but impl uses Module Bar

#include <stdint.h>

void Foo_vDoFoo0(void);

// Takes 1 arg, depends on Bar module
uint32_t Foo_u32DoFoo1( uint32_t u32Arg1 );


#endif //FOO_H
