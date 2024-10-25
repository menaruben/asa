#include <exception>
#include <string>

namespace asa {
enum AsaType { Integer, Float, Double, String, Char, Bool };
enum AsaError {
  Ok,
  StackOverflow,
  StackUnderflow,
  TypeMismatch,
  ArithmeticOnNonNumericType,
  DivByZero,
  IllegalInstruction
};

std::string type_to_str(AsaType t) {
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

struct AsaObj {
  std::string value;
  AsaType type;
  AsaError error;
};

AsaObj ERROR_OK = {.value = "Ok", .error = AsaError::Ok};

AsaObj ERROR_STACKOVERFLOW = {.value = "StackOverflow",
                              .error = AsaError::StackOverflow};

AsaObj ERROR_STACKUNDERFLOW = {.value = "StackUnderflow",
                               .error = AsaError::StackUnderflow};

AsaObj ERROR_TYPEMISMATCH = {.value = "TypeMismatch",
                             .error = AsaError::TypeMismatch};

AsaObj ERROR_ARITHMETIC = {.value = "Arithmetic (Math without numeric type)",
                           .error = AsaError::ArithmeticOnNonNumericType};

AsaObj ERROR_DIVBYZERO = {.value = "DivByZero", .error = AsaError::DivByZero};

AsaObj ERROR_ILLEGALINSTRUCTION = {.value = "IllegalInstruction",
                                   .error = AsaError::IllegalInstruction};

bool isNumericType(asa::AsaObj o) {
  return o.type == asa::AsaType::Float || o.type == asa::AsaType::Double ||
         o.type == asa::AsaType::Integer;
}
} // namespace asa
