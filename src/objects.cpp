#include "objects.hpp"
#include <stdexcept>

namespace asa {
string error_to_str(Error e) {
  switch (e) {
    case Ok:                 return "Ok";
    case StackOverflow:      return "Stack Overflow";
    case StackUnderflow:     return "Stack Underflow";
    case TypeMismatch:       return "Type Mismatch";
    case DivByZero:          return "Division By Zero";
    case IllegalInstruction: return "Illegal Instruction";
    case LabelNotFound:      return "Label not found";
    case UndefinedVariable:  return "Undefined variable";
    default:                 throw runtime_error("Not implemented");
  }
}

string type_to_str(Type t) {
  switch (t) {
  case BigInteger: return "BigInteger";
  case Integer:    return "Integer";
  case Float:      return "Float";
  case BigDouble:  return "BigDouble";
  case Double:     return "Double";
  case String:     return "String";
  case Bool:       return "Bool";
  case Char:       return "Char";
  default:         throw runtime_error("Invalid type");
  }
}

Type str_to_type(string t) {
  if (t == "BigInteger") return BigInteger;
  if (t == "BigDouble")  return BigDouble;
  if (t == "Integer")    return Integer;
  if (t == "Float")      return Float;
  if (t == "Double")     return Double;
  if (t == "String")     return String;
  if (t == "Bool")       return Bool;
  throw runtime_error("Invalid type: " + t);
}

// Type return_type_of(AsaObject a, AsaObject b) {
//   if (a.get_type() == asa::String     || b.get_type() == asa::String)     return asa::String;

//   if (a.get_type() == asa::BigDouble  || b.get_type() == asa::BigDouble)  return asa::BigDouble;
//   if (a.get_type() == asa::Float      && b.get_type() == asa::BigInteger) return asa::BigDouble;
//   if (a.get_type() == asa::BigInteger && b.get_type() == asa::Float)      return asa::BigDouble;
  
//   if (a.get_type() == asa::Double     || b.get_type() == asa::Double)     return asa::Double;


//   if (a.get_type() == asa::BigInteger || b.get_type() == asa::BigInteger) return asa::BigInteger;
//   if (a.get_type() == asa::Integer    || b.get_type() == asa::BigInteger) return asa::BigInteger;
  
//   if (a.get_type() == asa::Float      || b.get_type() == asa::Float)      return asa::Float;

//   if (a.get_type() == asa::Integer    || b.get_type() == asa::Integer)    return asa::Integer;
//   throw runtime_error("Unreachable (determine return type) for " + 
//     type_to_str(a.get_type()) + " and " + type_to_str(b.get_type()));
// }
}
