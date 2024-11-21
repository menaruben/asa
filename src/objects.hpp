#pragma once

#include <stdexcept>
#include <string>

using namespace std;

namespace asa {
enum Type { Integer, BigInteger, Float, Double, BigDouble, String, Char, Bool };

enum Error {
  Ok,
  StackOverflow,
  StackUnderflow,
  TypeMismatch,
  ArithmeticOnNonNumericType,
  DivByZero,
  IllegalInstruction,
  LabelNotFound,
  UndefinedVariable,
};

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
    default: throw runtime_error("Not implemented");
  }
}

string type_to_str(Type t) {
  switch (t) {
  case BigInteger:
    return "BigInteger";
  case Integer:
    return "Integer";
  case Float:
    return "Float";
  case BigDouble:
    return "BigDouble";
  case String:
    return "String";
  case Bool:
    return "Bool";
  case Char:
    return "Char";
  default:
    throw runtime_error("Invalid type");
  }
}

Type str_to_type(string t) {
  if (t == "BigInteger")
    return BigInteger;
  if (t == "BigDouble")
    return BigDouble;
  if (t == "Integer")
    return Integer;
  if (t == "Float")
    return Float;
  if (t == "Double")
    return Double;
  if (t == "String")
    return String;
  if (t == "Bool")
    return Bool;
  throw runtime_error("Invalid type: " + t);
}
}
