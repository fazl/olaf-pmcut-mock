#ifndef PM_MOCK_H
#define PM_MOCK_H 1

// TODO review for need to cover noexcept/ref-qualifiers/cv-qualifiers

// Other module includes
#include "Parameter.hpp"
#include "typeidutils.hpp"

// Library includes
#include <cassert>
#include <cstdio>
#include <typeinfo>

extern char acFormat[256];
const char* const concatAcFormat(const char* const preBlah, const char* const pcRetFmt);

class PoorMansCppUTestMock
{
  private:
    //struct that represents expectations for all fns in poorMansCppuTestMockFnDef
    void expectNoCall (const char * const fnName) { this->expectNCalls(0, fnName ); }  // today it's public
    void expectOneCall(const char * const fnName) { this->expectNCalls(1, fnName); }
    void expectNCalls (const int count, const char * const fnName) { /*TBD;*/ }

    public:
    void clear(void);
    void checkExpectations(void);

    // Record no-arg function calls
    static void callVoid(const char* const fName){
      printf("\t\tIn: PMCUTMock::callVoid() TODO record noargs func '%s' was called\n", fName);
    }
    // TODO figure out how return values used in tests
    // TODO try to hide the complexity
    // TODO how to avoid dynamic allocation during main runtime
    // I thought we cannot overload on return types - but it seems to work!
    // 
    // template <typename RetType>
    // static RetType callNonVoid(const char* const fName){
    //   RetType retVal;
    //   printf(
    //     "\t\tIn: '%15s PMCUTMock::callNonVoid(\"%s\")': TODO record noargs func '%s' was called, returning a %s=%lu\n",
    //     TypeWrapper<RetType>::name.c_str(), fName, fName, TypeWrapper<RetType>::name.c_str(), retVal ); // or basicType(typeid(RetType).name())

    //   return retVal;
    // }

    // On variadic functions arguments https://en.cppreference.com/w/cpp/language/parameter_pack
    // Note: a lot of this cruft is scaffolding just to catch if I mess up the type handling and
    // can hopefully be deleted once it's settled down a bit..
    //
    template <typename RetType, typename... ArgTypes>
    static RetType callNonVoidVariadic(const char* const fName, RetType retVal, ArgTypes... argVals){
      const char* const retTypeIdName = typeid(RetType).name();
      const char* const retTypeName = basicType(retTypeIdName); // or TypeWrapper<RetType>::name.c_str(); 

      // At end of fmt, use numeric %lu for numeric result, %s for string, %p for pointer. 
      const char* const pcRetFmt = mapTypeIdNameToPrintFmt(retTypeIdName);
      printf( "return type %s needs format '%s'\n", basicType(retTypeIdName), pcRetFmt ); 

      concatAcFormat( 
        "\t\tIn: '%15s PMCUTMock::callNonVoidVariadic()': TODO record call to %d-args func '%s', returning a %s", 
        pcRetFmt);

      printf( acFormat,  retTypeName, sizeof...(argVals), fName, retTypeName, retVal ); 

      // Record actual call details
      
      // Note : if std::tuple doesn't suit, try https://www.stroustrup.com/C++11FAQ.html#variadic-templates
      // (Looks like Lisp Programming during Compilation of C++ ! LOL)
      // Simple idea:  map the name to an arg list and return value?
      // Something like: actualCallsMap
      // Key:     name of function
      // Looksup: List of name+typed-value pairs (arguments), and return type-value
      // ... ?
      //
      // actualCallsMap.insert(std::make_pair(fName,std::make_tuple(argVals..)))
      // Maybe record typeid().name() values for type information, to reduce template bloat?

      // std::map<const char* const, Signature_t> actualCallsMap;
      // Signature sig(retVal, ...argVals); //Obj can give us typed values (arg names will need more smarts)
      // actualCallsMap.insert(fname, sig);

  
  


      return retVal;
    }

};

#endif //PM_MOCK_H