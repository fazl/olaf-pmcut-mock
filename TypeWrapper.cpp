#include "TypeWrapper.hpp"

#include <string>

#define SPECIALISE( x ) \
const std::string TypeWrapper<x  >::name = #x ;\
const std::string TypeWrapper<x *>::name = #x "*";

// const std::string TypeWrapper<char>::name = "char";

// e.g.
//
// template <>
// struct C99Type<char>{
//	   static const std::string name="char";
// };

// Template specialisations for intrinsic types
//
// Fundamental types
SPECIALISE(char)
SPECIALISE(signed char)
SPECIALISE(unsigned char)
SPECIALISE(short)
SPECIALISE(unsigned short)
SPECIALISE(int)
SPECIALISE(unsigned int)
SPECIALISE(long)
SPECIALISE(unsigned long)
SPECIALISE(void)

// SPECIALISE(const char)
/*
// Signed intX_t types
SPECIALISE(int8_t)
SPECIALISE(int16_t)
SPECIALISE(int32_t)
SPECIALISE(int64_t)
SPECIALISE(int_fast8_t)
SPECIALISE(int_fast16_t)
SPECIALISE(int_fast32_t)
SPECIALISE(int_fast64_t)
SPECIALISE(int_least8_t)
SPECIALISE(int_least16_t)
SPECIALISE(int_least32_t)
SPECIALISE(int_least64_t)
SPECIALISE(intmax_t)
SPECIALISE(intptr_t)
// Unsigned uintX_t types
SPECIALISE(uint8_t)
SPECIALISE(uint16_t)
SPECIALISE(uint32_t)
SPECIALISE(uint64_t)
SPECIALISE(uint_fast8_t)
SPECIALISE(uint_fast16_t)
SPECIALISE(uint_fast32_t)
SPECIALISE(uint_fast64_t)
SPECIALISE(uint_least8_t)
SPECIALISE(uint_least16_t)
SPECIALISE(uint_least32_t)
SPECIALISE(uint_least64_t)
SPECIALISE(uintmax_t)
SPECIALISE(uintptr_t)
*/