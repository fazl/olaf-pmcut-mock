#include "typeidutils.hpp"

// Other module includes

// Library includes
#include <cstdio>
#include <cstring>
#include <map>

typedef std::map<const char* const,const char* const> dict_t;

#define GENPAIRS(x)\
{ #x, typeid(x).name() },\
{ #x "*", typeid(x *).name() },\
{ "const " #x "*", typeid(const x *).name() }

// Lookup table maps C types to C++ typeid name
// to allow us to discriminate types at runtime.
// Note: https://en.cppreference.com/w/cpp/language/typeid) claims
// that typeid of const T and T are same, however 
// char* maps to Pc, but
// const char* maps to PKc !!
//
// From this we build reverse direction map.
static const dict_t c99Types2Names = {
  // Fundamental types
  GENPAIRS(char),
  GENPAIRS(signed char),
  GENPAIRS(unsigned char),
  GENPAIRS(short),
  GENPAIRS(unsigned short),
  GENPAIRS(int),
  GENPAIRS(unsigned int),
  GENPAIRS(long),
  GENPAIRS(unsigned long),
  GENPAIRS(void),
};

//-----------------------------------------------------------------------------
static dict_t reverseLookup(const dict_t dict){
  dict_t reversed;
  for(dict_t::const_iterator i = dict.begin(); i != dict.end(); ++i){    
    if(0 == reversed.count(i->second)){
      reversed.insert(std::make_pair(i->second,i->first));
    }else{
      printf("Duplicate typeid name; trying to insert name: '%s' ", i->second);
      throw "Error: please fix.";
    }
  }
  return reversed;
}
static const dict_t c99Names2Types = reverseLookup(c99Types2Names);


//-----------------------------------------------------------------------------
// const dict_t forceTypeDictInit(){
//     return c99Names2Types;
// }
//-----------------------------------------------------------------------------
const char* const basicType(const char* const typeIdName ){
    // uncomment if map lookup throws out_of_range
    //   printf("Lookup basic type for shortcode: %s in dict c99Names2Types of size: %d\n", 
    //        typeIdName, c99Names2Types.size()); 
    //   fflush(0);
  return c99Names2Types.at(typeIdName);
}

//-----------------------------------------------------------------------------
bool isLongType(const char* const typeIdName ){
  return nullptr != strstr(c99Names2Types.at(typeIdName), "long");
}

//-----------------------------------------------------------------------------
bool isPtrType(const char* const typeIdName ){
  return nullptr != strstr(c99Names2Types.at(typeIdName), "*");
}

//-----------------------------------------------------------------------------
bool isStringType(const char* const typeIdName ){
  return nullptr != strstr(c99Names2Types.at(typeIdName), "char*");
}

//-----------------------------------------------------------------------------
bool isUnsignedType(const char* const typeIdName ){
  return nullptr != strstr(c99Names2Types.at(typeIdName), "unsigned");
}

//-----------------------------------------------------------------------------
const char* const mapTypeIdNameToPrintFmt(const char* const retTypeIdName){
  if( isStringType(retTypeIdName) ){
    printf( "\t\tString " ); 
    return "'%s'";
  }else if(isPtrType(retTypeIdName)){
    printf( "\t\tPtr   "); 
    return "%p";
  }else{
    printf( "\t\tIntegral "); 
    static char acBuf[]={'%',0,0,0};
    int nextIdx = 1;
    if(isLongType(retTypeIdName)){
        acBuf[nextIdx++] = 'l';
    }
    acBuf[nextIdx++] = isUnsignedType(retTypeIdName) ? 'u' : 'd';
    return acBuf;
  }
}

//-----------------------------------------------------------------------------
void printTypeIds(){
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = c99Names2Types.begin(); i != c99Names2Types.end(); ++i){
    printf("typeid(..).name() %s represents type: %s \n", i->first, i->second );
  }
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = c99Types2Names.begin(); i != c99Types2Names.end(); ++i){
    const char* const arithType = i->first;
    const char* const typeIdName = i->second;
    
    printf("typeid(..).name() of %-15s -like %-15s- is %s, \n",
           arithType, basicType(typeIdName), typeIdName );
  }
  printf("---------------------------------------\n");
}

