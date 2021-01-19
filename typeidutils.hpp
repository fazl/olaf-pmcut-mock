#ifndef TYPE_ID_UTILS_H
#define TYPE_ID_UTILS_H 1

// Utility funcs to help inspect types.
//
//The typeid().name() of a C++ type is generally a short code e.g. on cygwin/g++:
// typeid(char).name() gives c
// typeid(char*).name() gives Pc
// typeid(const char*).name() gives PKc
//

   
// Lookup type name for given type code 
const char* const basicType(const char* const typeCode );

// If typeCode not already registered, map it to typeName
void ensureTypeRegistered(const char* const typeCode, const char* const typeName);

// Is original a long type ?
bool isLongType(const char* const typeCode );

// Is original a pointer type ?
bool isPtrType(const char* const typeCode );

// Is original a (C) string type ?
bool isStringType(const char* const typeCode );

// Is original an unsigned type ?
bool isUnsignedType(const char* const typeCode );

// Return the respective printf format string (%s, 0x%p, or %lu) depending on 
// whether original is a string, pointer, or basic arithmetic type
const char* const mapTypeCodeToPrintFmt(const char* const typeCode);

void printTypeIds(); 


#endif //TYPE_ID_UTILS_H 