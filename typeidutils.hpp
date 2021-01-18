#ifndef TYPE_ID_UTILS_H
#define TYPE_ID_UTILS_H 1

// Utility funcs to help work with typeid's.
//
//The typeid().name() of a C++ type is generally a short code e.g. on cygwin/g++:
// typeid(char).name() gives c
// typeid(char*).name() gives Pc
// typeid(const char*).name() gives PKc
//

   
// Map type shortcode to original type (not typedef)
const char* const basicType(const char* const typeIdName );

// Is original a long type ?
bool isLongType(const char* const typeIdName );

// Is original a pointer type ?
bool isPtrType(const char* const typeIdName );

// Is original a (C) string type ?
bool isStringType(const char* const typeIdName );

// Is original an unsigned type ?
bool isUnsignedType(const char* const typeIdName );

// Return the respective printf format string (%s, 0x%p, or %lu) depending on 
// whether original is a string, pointer, or basic arithmetic type
const char* const mapTypeIdNameToPrintFmt(const char* const retTypeIdName);

void printTypeIds(); 


#endif //TYPE_ID_UTILS_H 