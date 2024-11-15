#pragma once

#include <exception>
#include <stdexcept>
#include <string>

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
  IntegerOverflow,
  IntegerUnderflow,
  FloatOverflow,
  FloatUnderflow,
};

std::string typeToStr(Type t) {
  switch (t) {
  case BigInteger: return "BigInteger";
  case Integer:    return "Integer";
  case Float:      return "Float";
  case Double:     return "Double";
  case BigDouble:  return "BigDouble";
  case String:     return "String";
  case Bool:       return "Bool";
  case Char:       return "Char";
  default:         throw std::runtime_error("Invalid type");
  }
}

Type strToType(std::string t) {
  if (t == "BigInteger") return BigInteger;
  if (t == "BigDouble")  return BigDouble;
  if (t == "Integer")    return Integer;
  if (t == "Float")      return Float;
  if (t == "Double")     return Double;
  if (t == "String")     return String;
  if (t == "Bool")       return Bool;
  throw std::runtime_error("Invalid type: " + t);
}

struct Object {
  std::string value;
  Type type;
  Error error;
};

Object ERROR_OK = {.value = "Ok", .error = Error::Ok};

Object error_stackoverflow(std::string msg) {
  return {.value = msg, .error = Error::StackOverflow};
}

Object error_stackunderflow(std::string msg) {
  return {.value = msg, .error = Error::StackUnderflow};
}

Object error_typemismatch(std::string msg) {
  return {.value = msg, .error = Error::TypeMismatch};
}

Object error_arithmetic(std::string msg) {
  return {.value = msg, .error = Error::ArithmeticOnNonNumericType};
}

Object error_div_by_zero(std::string msg) {
  return {.value = msg, .error = Error::DivByZero};
}

Object error_illegal_instruction(std::string msg) {
  return {.value = msg, .error = Error::IllegalInstruction};
}

Object error_label_not_found(std::string msg) {
  return {.value = msg, .error = Error::LabelNotFound};
}

Object error_undefined_variable(std::string msg) {
  return {.value = msg, .error = Error::UndefinedVariable};
}

Object error_integer_overflow(std::string msg) {
  return {.value = msg, . error = Error::IntegerOverflow};
}

Object error_integer_underflow(std::string msg) {
  return {.value = msg, . error = Error::IntegerOverflow};
}

bool is_numeric_type(Object o) {
  return o.type == Type::Float || o.type == Type::Double ||
         o.type == Type::Integer || o.type == Type::BigInteger ||
         o.type == Type::BigDouble;
}
} // namespace asa
