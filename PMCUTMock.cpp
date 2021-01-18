#include "PMCUTMock.hpp"

#include <map>
#include <string>
#include <utility> // make_pair

char acFormat[256];
void concatAcFormat(const char* const pre, const char* const pcRetFmt){
      int count=snprintf(acFormat, sizeof acFormat, "%s=%s\n", pre, pcRetFmt  );
      if( count<0 || sizeof acFormat <= count ){
        printf(
          "!!ERROR building fmt string!! count (%d) <0 || sizeof acFormat (%u) <= count (%d) ", 
          count, sizeof acFormat, count);
        assert(!"Try a larger buffer for acFormat?");
      }
}


//---------------- PoorMansCppUTestMock::methods --------------------------
