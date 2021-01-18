#include "typeidutils.hpp"

// Other module includes

// Library includes
#include <cstdio>
#include <cstring>
#include <map>

typedef std::map<const char* const,const char* const> dict_t;

#define GENPAIR(x)\
{ #x, typeid(x).name() },\
{ #x "*", typeid(x *).name() }

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
  GENPAIR(void),
};

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
const char* const basicType(const char* const typeIdName ){
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

