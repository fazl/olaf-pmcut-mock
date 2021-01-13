#ifndef PM_MOCK_H
#define PM_MOCK_H 1

#include <type_traits>
#include <typeinfo>  //for typeid

extern "C" {
  #include <stdio.h>
}

// Eventually move what's needed into mock support class
void printTypeIds();
const char* const fundamentalTypeName(const char* const typeIdName );

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
    template <typename retType>
    static retType callNonVoid(const char* const fName){
      retType retVal;
      printf(
        "\t\tIn: PMCUTMock::callNonVoid() TODO record noargs func '%s' was called, returning a %s=%lu\n",
        fName, fundamentalTypeName(typeid(retType).name()), retVal );
      return retVal;
    }


};

#endif //PM_MOCK_H