#include "PMCUTMock.hpp"

#include <map>
#include <string>

typedef std::map<const char* const,const char* const> dict_t;

#define GENPAIR(x) { #x, typeid(x).name() }

// Lookup table maps C types to C++ typeid name
// Hoping this will allow us to discriminate types
// Still need to build reverse direction map.
static const dict_t c99ArithmeticTypeNames = {
  // Fundamental types
  GENPAIR(char),
  GENPAIR(signed char),
  GENPAIR(unsigned char),
  GENPAIR(short),
  GENPAIR(unsigned short),
  GENPAIR(int),
  GENPAIR(unsigned int),
  GENPAIR(long),
  GENPAIR(unsigned long),
  // Signed intX_t types
  GENPAIR(int8_t),
  GENPAIR(int16_t),
  GENPAIR(int32_t),
  GENPAIR(int64_t),
  GENPAIR(int_fast8_t),
  GENPAIR(int_fast16_t),
  GENPAIR(int_fast32_t),
  GENPAIR(int_fast64_t),
  GENPAIR(int_least8_t),
  GENPAIR(int_least16_t),
  GENPAIR(int_least32_t),
  GENPAIR(int_least64_t),
  GENPAIR(intmax_t),
  GENPAIR(intptr_t),
  // Unsigned uintX_t types
  GENPAIR(uint8_t),
  GENPAIR(uint16_t),
  GENPAIR(uint32_t),
  GENPAIR(uint64_t),
  GENPAIR(uint_fast8_t),
  GENPAIR(uint_fast16_t),
  GENPAIR(uint_fast32_t),
  GENPAIR(uint_fast64_t),
  GENPAIR(uint_least8_t),
  GENPAIR(uint_least16_t),
  GENPAIR(uint_least32_t),
  GENPAIR(uint_least64_t),
  GENPAIR(uintmax_t),
  GENPAIR(uintptr_t)
};

const char* const fundamentalTypeName(const char* const typeIdName ){
  for(dict_t::const_iterator i = c99ArithmeticTypeNames.begin(); i != c99ArithmeticTypeNames.end(); ++i){
    if((const std::string&) typeIdName == i->second){
      return i->first;
    }
  }
  return "No entry in map has typeid name given!";
}

void printTypeIds(){
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = c99ArithmeticTypeNames.begin(); i != c99ArithmeticTypeNames.end(); ++i){
    printf("typeid(..).name() of %-14s -like %-14s- is %s, \n",
           i->first, fundamentalTypeName(i->second), i->second );
  }
  printf("---------------------------------------\n");
}


