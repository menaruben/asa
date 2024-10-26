#include "objects.hpp"
#include <exception>
#include <string>

namespace asa {
enum Type { Integer, Float, Double, String, Char, Bool };
enum Error {
  Ok,
  StackOverflow,
  StackUnderflow,
  TypeMismatch,
  ArithmeticOnNonNumericType,
  DivByZero,
  IllegalInstruction
};

std::string typeToStr(Type t) {
  switch (t) {
  case Integer:
    return "Integer";
  case Float:
    return "Float";
  case Double:
    return "Double";
  case String:
    return "String";
  case Bool:
    return "Bool";
  default:
    throw std::exception(); // unreachable
  }
}

struct Object {
  std::string value;
  Type type;
  Error error;
};

Object ERROR_OK = {.value = "Ok", .error = Error::Ok};

Object ERROR_STACKOVERFLOW = {.value = "StackOverflow",
                              .error = Error::StackOverflow};

Object ERROR_STACKUNDERFLOW = {.value = "StackUnderflow",
                               .error = Error::StackUnderflow};

Object ERROR_TYPEMISMATCH = {.value = "TypeMismatch",
                             .error = Error::TypeMismatch};

Object ERROR_ARITHMETIC = {.value = "Arithmetic (Math without numeric type)",
                           .error = Error::ArithmeticOnNonNumericType};

Object ERROR_DIVBYZERO = {.value = "DivByZero", .error = Error::DivByZero};

Object ERROR_ILLEGALINSTRUCTION = {.value = "IllegalInstruction",
                                   .error = Error::IllegalInstruction};

bool isNumericType(Object o) {
  return o.type == Type::Float ||
         o.type == Type::Double ||
         o.type == Type::Integer;
}
} // namespace asa
