#ifndef PM_MOCK_H
#define PM_MOCK_H 1

// TODO review for need to cover noexcept/ref-qualifiers/cv-qualifiers

#include <type_traits>
#include <typeinfo>  //for typeid
// #include "TypeWrapper.hpp"

extern "C" {
  #include <assert.h>
  #include <stdio.h>
}

extern char acFormat[256];
void concatAcFormat(const char* const preBlah, const char* const pcRetFmt);

enum class IgnoreParameter { YES };


template<typename BaseType>
class Parameter {
public:
    /**
     * Constructor for non-ignored parameters.
     * @param value [in] Value of the parameter
     */
    Parameter(const BaseType &value) : m_value(&value), m_isIgnored(false) {}

    /**
     * Constructor for ignored parameters.
     *
     * The actual value of the passed parameter is ignored.
     */
    Parameter(IgnoreParameter) : m_value(nullptr),  m_isIgnored(true) {}

    /**
     * Returns the parameter value.
     * @return Parameter value
     */
    const BaseType& getValue()
    {
        return *m_value;
    }

    /**
     * Returns the parameter value.
     * @return Parameter value
     */
    const BaseType& getPointerValue()
    {
        return m_value;
    }

    /**
     * Indicates if the parameter is ignored.
     * @return @c true if the parameter is ignored, @c false otherwise
     */
    bool isIgnored()
    {
        return m_isIgnored;
    }


private:
    typename std::remove_reference<const BaseType>::type *m_value;
    bool m_isIgnored;
};

class PoorMansCppUTestMock
{
  private:
    static const char* const basicType(const char* const typeIdName );
    static bool isLongType(const char* const typeIdName );
    static bool isPtrType(const char* const typeIdName );
    static bool isStringType(const char* const typeIdName );
    static bool isUnsignedType(const char* const typeIdName );

    // From typeid().name() deduce whether the type is a string, other pointer, or
    // basic integral type and return the respective printf format string (%s, 0x%p, or %lu)
    static const char* const mapTypeIdNameToPrintFmt(const char* const retTypeIdName);

    //struct that represents expectations for all fns in poorMansCppuTestMockFnDef
    void expectNoCall (const char * const fnName) { this->expectNCalls(0, fnName ); }  // today it's public
    void expectOneCall(const char * const fnName) { this->expectNCalls(1, fnName); }
    void expectNCalls (const int count, const char * const fnName) { /*TBD;*/ }

    public:
    static void printTypeIds(); //scaffolding

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
    // template <typename retType>
    // static retType callNonVoid(const char* const fName){
    //   retType retVal;
    //   printf(
    //     "\t\tIn: '%15s PMCUTMock::callNonVoid(\"%s\")': TODO record noargs func '%s' was called, returning a %s=%lu\n",
    //     TypeWrapper<retType>::name.c_str(), fName, fName, TypeWrapper<retType>::name.c_str(), retVal ); // or basicType(typeid(retType).name())

    //   return retVal;
    // }

    // On variadic functions arguments https://en.cppreference.com/w/cpp/language/parameter_pack
    // Note: a lot of this cruft is scaffolding just to catch if I mess up the type handling and
    // can hopefully be deleted once it's settled down a bit..
    //
    template <typename retType, typename... ArgTypes>
    static retType callNonVoidVariadic(const char* const fName, retType retVal, ArgTypes... args){
      const char* const retTypeIdName = typeid(retType).name();
      const char* const retTypeName = basicType(retTypeIdName); // or TypeWrapper<retType>::name.c_str(); 

      // At end of fmt, use numeric %lu for numeric result, %s for string, %p for pointer. 
      const char* const pcRetFmt = mapTypeIdNameToPrintFmt(retTypeIdName);
      printf( "return type %s needs format '%s'\n", basicType(retTypeIdName), pcRetFmt ); 

      concatAcFormat( 
        "\t\tIn: '%15s PMCUTMock::callNonVoidVariadic()': TODO record call to %d-args func '%s', returning a %s", 
        pcRetFmt);
        
      printf( acFormat,  retTypeName, sizeof...(args), fName, retTypeName, retVal ); 

      // Record actual call details
      
      // Simple idea:  map the name to an arg list and return value?
      // Something like: actualCallsMap
      // Key:     name of function
      // Looksup: List of name+typed-value pairs (arguments), and return type-value
      // ... ?
      //


      return retVal;
    }

};

#endif //PM_MOCK_H