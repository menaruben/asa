#include "objects.hpp"
#include <string>

using namespace asa;

namespace conditionals {

Object GreaterThan(Object a, Object b) {
  if (a.type != b.type)  return ERROR_TYPEMISMATCH;
  if (!isNumericType(a)) return ERROR_ARITHMETIC;

  switch (a.type) {
    
    case Integer: {
      int ai = std::stoi(a.value);
      int bi = std::stoi(b.value);
      bool result = ai > bi;
      return {
        .value = std::to_string(result),
        .type = Bool 
      };   
    }
    
    case Float: {
      float af = std::stof(a.value);
      float bf = std::stof(b.value);
      bool result = af > bf;
      return {
        .value = std::to_string(result),
        .type = Bool 
      };   
    }
    
    case Double: {
      int ad = std::stod(a.value);
      int bd = std::stod(b.value);
      bool result = ad > bd;
      return {
        .value = std::to_string(result),
        .type = Bool 
      };    
    }
    
    default:
      return  ERROR_ILLEGALINSTRUCTION; // unreachable
  }
}
}
