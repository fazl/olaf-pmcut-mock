#include "PMCUTMock.hpp"

#include <map>
#include <string>
#include <utility> // make_pair

typedef std::map<const char* const,const char* const> dict_t;

#define GENPAIR(x) { #x, typeid(x).name() }

// Lookup table maps C types to C++ typeid name
// Hoping this will allow us to discriminate types
// Still need to build reverse direction map.
static const dict_t c99Types2Names = {
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
  // GENPAIR(int8_t),
  // GENPAIR(int16_t),
  // GENPAIR(int32_t),
  // GENPAIR(int64_t),
  // GENPAIR(int_fast8_t),
  // GENPAIR(int_fast16_t),
  // GENPAIR(int_fast32_t),
  // GENPAIR(int_fast64_t),
  // GENPAIR(int_least8_t),
  // GENPAIR(int_least16_t),
  // GENPAIR(int_least32_t),
  // GENPAIR(int_least64_t),
  // GENPAIR(intmax_t),
  // GENPAIR(intptr_t),
  // Unsigned uintX_t types
  // GENPAIR(uint8_t),
  // GENPAIR(uint16_t),
  // GENPAIR(uint32_t),
  // GENPAIR(uint64_t),
  // GENPAIR(uint_fast8_t),
  // GENPAIR(uint_fast16_t),
  // GENPAIR(uint_fast32_t),
  // GENPAIR(uint_fast64_t),
  // GENPAIR(uint_least8_t),
  // GENPAIR(uint_least16_t),
  // GENPAIR(uint_least32_t),
  // GENPAIR(uint_least64_t),
  // GENPAIR(uintmax_t),
  // GENPAIR(uintptr_t)
};

static dict_t reverseLookup(const dict_t dict){
  dict_t reversed;
  for(dict_t::const_iterator i = dict.begin(); i != dict.end(); ++i){
    const char* const key = i->first;
    const char* const value = i->second;
    
    if(0 != reversed.count(value)){
      printf("Duplicate typeid name; trying to insert name: '%s' ", value);
      throw "Error: please fix.";
    }

    reversed.insert(std::make_pair(value,key));
  }
  return reversed;
}

static const dict_t c99Names2Types = reverseLookup(c99Types2Names);


const char* const fundamentalTypeName(const char* const typeIdName ){
  return c99Names2Types.at(typeIdName);
}

void printTypeIds(){
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = c99Names2Types.begin(); i != c99Names2Types.end(); ++i){
    printf("typeid(..).name() %s represents type: %s \n", i->first, i->second );
  }
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = c99Types2Names.begin(); i != c99Types2Names.end(); ++i){
    const char* const arithType = i->first;
    const char* const typeIdName = i->second;
    
    printf("typeid(..).name() of %-14s -like %-14s- is %s, \n",
           arithType, fundamentalTypeName(typeIdName), typeIdName );
  }
  printf("---------------------------------------\n");
}

