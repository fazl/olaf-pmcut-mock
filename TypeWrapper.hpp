#ifndef TYPE_WRAPPER_H
#define TYPE_WRAPPER_H 1

#include <string>

// family of classes allows lookup of name of types
//
// pro: quick and easy to use inside templates
// pro: compile time lookup
// con: generates lots of classes
// con: doesn't distinguish typedefs, (same as typeid)
template <typename T> struct TypeWrapper {
	static const std::string name;
};


#define SPECIALWRAPPER( x ) \
template <> struct TypeWrapper<x  >{ static const std::string name;};\
template <> struct TypeWrapper<x *>{ static const std::string name;};
// Specialisations for intrinsic types
//
// e.g.
//
// template <>
// struct TypeWrapper<char>{ 
// 	static const std::string name;
// };

// Fundamental types
SPECIALWRAPPER(char)
SPECIALWRAPPER(signed char)
SPECIALWRAPPER(unsigned char)
SPECIALWRAPPER(short)
SPECIALWRAPPER(unsigned short)
SPECIALWRAPPER(int)
SPECIALWRAPPER(unsigned int)
SPECIALWRAPPER(long)
SPECIALWRAPPER(unsigned long)
SPECIALWRAPPER(void)

// SPECIALWRAPPER(const char) // can discriminate on const
/*

// Typedefs are not distinct types; they decay to (and collide
// with) fundamental types above .. sadly.

// Signed intX_t types
SPECIALWRAPPER(int8_t)
SPECIALWRAPPER(int16_t)
SPECIALWRAPPER(int32_t)
SPECIALWRAPPER(int64_t)
SPECIALWRAPPER(int_fast8_t)
SPECIALWRAPPER(int_fast16_t)
SPECIALWRAPPER(int_fast32_t)
SPECIALWRAPPER(int_fast64_t)
SPECIALWRAPPER(int_least8_t)
SPECIALWRAPPER(int_least16_t)
SPECIALWRAPPER(int_least32_t)
SPECIALWRAPPER(int_least64_t)
SPECIALWRAPPER(intmax_t)
SPECIALWRAPPER(intptr_t)
// Unsigned uintX_t types
SPECIALWRAPPER(uint8_t)
SPECIALWRAPPER(uint16_t)
SPECIALWRAPPER(uint32_t)
SPECIALWRAPPER(uint64_t)
SPECIALWRAPPER(uint_fast8_t)
SPECIALWRAPPER(uint_fast16_t)
SPECIALWRAPPER(uint_fast32_t)
SPECIALWRAPPER(uint_fast64_t)
SPECIALWRAPPER(uint_least8_t)
SPECIALWRAPPER(uint_least16_t)
SPECIALWRAPPER(uint_least32_t)
SPECIALWRAPPER(uint_least64_t)
SPECIALWRAPPER(uintmax_t)
SPECIALWRAPPER(uintptr_t)
*/
#endif //TYPE_WRAPPER_H
