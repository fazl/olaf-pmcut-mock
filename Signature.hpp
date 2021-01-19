#ifndef SIGNATURE_H
#define SIGNATURE_H 1

// Other module includes
#include "typeidutils.hpp"  // TODO : RENAME TO TYPEUTILS AND USE MODULE APPROACH

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

// TODO: can the constructor update the typeName2Code map if needed ?
//
template <class A>  struct Argument : public ArgBase
{
    A value;
    Argument(A a) : value(a){
        // Code for type A will be needed in the type information map
        // Kludge.. but it may suffice for our needs
        const char* const typeCode = typeid(value).name();
        ensureTypeRegistered(typeCode, typeCode); 

    }
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
      // TODO: Retire bloaty iostreams lib throughout 
      std::cout<<"Signature ctor: fName='"<<fName<< "', takes " << sizeof...(argVals) << " args, " 
               << "returns a " << basicType(typeid(retVal).name()) << "=" << retVal << "\n";
      std::tuple<ArgTypes...> toppy = std::make_tuple(argVals...);
 }
};

#endif //SIGNATURE_H