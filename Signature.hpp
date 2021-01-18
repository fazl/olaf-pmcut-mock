#ifndef SIGNATURE_H
#define SIGNATURE_H 1

// Other module includes
#include "typeidutils.hpp"

// Library includes
#include <iostream>
#include <tuple>
#include <vector>

// Signature operations:
// ctor: template<typename RetType, ...ArgTypes> Signature(const char* const fName, RetType retVal, ... ArgTypes args){}
//
// inspectors:
// 
// + get name
// + get return type / value
// + get argument count
// + get args type / value

class ArgBase{};

template <class A>  struct Argument : public ArgBase
{
    A value;
    Argument(A a) : value(a){}
};

class Signature
{
  const char* const name;
  ArgBase* ret;
//std::tuple<ArgBase*...> args; // compiler :  pattern ‘ArgBase*’ contains no parameter pack
  std::vector<ArgBase*> args;

  public:
  
  template<typename RetType, typename... ArgTypes>
  Signature(const char* const fName, RetType retVal, ArgTypes... argVals) 
  : name(fName) 
  {
      ret = new Argument<RetType>(retVal);
    //   std::tuple<ArgTypes...> topper = std::make_tuple(argVals...);
      std::cout<<"Signature ctor: fName='"<<fName<<"', returns a " << basicType(typeid(retVal).name()) << "=" << retVal << "\n";
 }
};

#endif //SIGNATURE_H