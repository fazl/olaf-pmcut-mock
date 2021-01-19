#include "typeidutils.hpp"

// Other module includes

// Library includes
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <typeinfo>

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
static const dict_t typeNames2Codes = {
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
static dict_t typeCodes2Names = reverseLookup(typeNames2Codes);

// At program startup we seed the dictionary with real names.
// 
// At runtime, I don't see how to pass the type's verbatim name.
// Will have to pass the code as the name in that case.
// At least there will be a 'representation' of the name available.
// Will have to see how that works out...
void ensureTypeRegistered(const char* const typeCode, const char* const typeName){
    // Note: operator[] inserts and returns default entry if missing
    const char* const existingTypeName = typeCodes2Names[typeCode]; 
    if(0 == existingTypeName){                          // typeCode not mapped: add it
      printf("Mapping new type code '%s' to type '%s'\n", typeCode, typeName);
      typeCodes2Names.insert(std::make_pair(typeCode, typeName)); 
      // doesn't like typeCodes2Names[typeCode] = typeName;
    }else if(0 != strncmp(typeName, existingTypeName, strlen(typeName))){ 
        printf("Type code '%s' already mapped to type '%s' (!= supplied type '%s'))\n", 
               typeCode, existingTypeName, typeName);
    }
}


//-----------------------------------------------------------------------------
// const dict_t forceTypeDictInit(){
//     return typeCodes2Names;
// }
//-----------------------------------------------------------------------------
const char* const basicType(const char* const typeCode ){
    // uncomment if map lookup throws out_of_range
    if(0 == typeCodes2Names.count(typeCode)){
      printf("ERROR Failing to lookup basic type for shortcode: %s in dict typeCodes2Names of size: %d\n", 
           typeCode, typeCodes2Names.size()); 
      assert(!"Please extend types dict to include needed types");
    }
  return typeCodes2Names.at(typeCode);
}

//-----------------------------------------------------------------------------
bool isLongType(const char* const typeCode ){
  return nullptr != strstr(typeCodes2Names.at(typeCode), "long");
}

//-----------------------------------------------------------------------------
bool isPtrType(const char* const typeCode ){
  return nullptr != strstr(typeCodes2Names.at(typeCode), "*");
}

//-----------------------------------------------------------------------------
bool isStringType(const char* const typeCode ){
  return nullptr != strstr(typeCodes2Names.at(typeCode), "char*");
}

//-----------------------------------------------------------------------------
bool isUnsignedType(const char* const typeCode ){
  return nullptr != strstr(typeCodes2Names.at(typeCode), "unsigned");
}

//-----------------------------------------------------------------------------
const char* const mapTypeCodeToPrintFmt(const char* const typeCode){
  if( isStringType(typeCode) ){
    printf( "\t\tString " ); 
    return "'%s'";
  }else if(isPtrType(typeCode)){
    printf( "\t\tPtr   "); 
    return "%p";
  }else{
    printf( "\t\tIntegral "); 
    static char acBuf[]={'%',0,0,0};
    int nextIdx = 1;
    if(isLongType(typeCode)){
        acBuf[nextIdx++] = 'l';
    }
    acBuf[nextIdx++] = isUnsignedType(typeCode) ? 'u' : 'd';
    return acBuf;
  }
}

//-----------------------------------------------------------------------------
void printTypeIds(){
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = typeCodes2Names.begin(); i != typeCodes2Names.end(); ++i){
    printf("typeid(..).name() %s represents type: %s \n", i->first, i->second );
  }
  printf("---------------------------------------\n");
  for(dict_t::const_iterator i = typeNames2Codes.begin(); i != typeNames2Codes.end(); ++i){
    const char* const typeName = i->first;
    const char* const typeCode = i->second;
    
    printf("typeid(..).name() of %-15s -like %-15s- is %s, \n",
           typeName, basicType(typeCode), typeCode );
  }
  printf("---------------------------------------\n");
}

