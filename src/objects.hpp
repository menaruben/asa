#include <string>

namespace asa {
enum AsaType { Integer, Float, Double, String, Bool };
enum AsaError {
  Ok,
  StackOverflow,
  StackUnderflow,
  TypeMismatch,
  ArithmeticOnNonNumericType,
  DivByZero,
  IllegalInstruction
};

struct AsaObj {
  std::string value;
  AsaType type;
  AsaError error;
};

AsaObj ERROR_OK =                 { .value = "Ok",                                     .error = AsaError::Ok};
AsaObj ERROR_STACKOVERFLOW =      { .value = "StackOverflow",                          .error = AsaError::StackOverflow};
AsaObj ERROR_STACKUNDERFLOW =     { .value = "StackUnderflow",                         .error = AsaError::StackUnderflow};
AsaObj ERROR_TYPEMISMATCH =       { .value = "TypeMismatch",                           .error = AsaError::TypeMismatch};
AsaObj ERROR_ARITHMETIC =         { .value = "Arithmetic (Math without numeric type)", .error = AsaError::ArithmeticOnNonNumericType};
AsaObj ERROR_DIVBYZERO =          { .value = "DivByZero",                              .error = AsaError::DivByZero};
AsaObj ERROR_ILLEGALINSTRUCTION = { .value = "IllegalInstruction",                     .error = AsaError::IllegalInstruction};

bool isNumericType(AsaObj o) {
  return o.type == AsaType::Float || o.type == AsaType::Double ||
         o.type == AsaType::Integer;
}

AsaObj add(AsaObj a, AsaObj b) {
  if (a.type != b.type)
    return ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return ERROR_ARITHMETIC;

  switch (a.type) {
  case AsaType::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int sum = ai + bi;
    return {.value = std::to_string(sum), .type = AsaType::Integer};
  }
  case AsaType::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float sum = af + bf;
    return {.value = std::to_string(sum), .type = AsaType::Integer};
  }
  case AsaType::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double sum = ad + bd;
    return {.value = std::to_string(sum), .type = AsaType::Integer};
  }

  default:
    return ERROR_ILLEGALINSTRUCTION;
  }
}

AsaObj subtract(AsaObj a, AsaObj b) {
  if (a.type != b.type)
    return ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return ERROR_ARITHMETIC;

  switch (a.type) {
  case AsaType::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int delta = ai - bi;
    return {.value = std::to_string(delta), .type = AsaType::Integer};
  }
  case AsaType::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float delta = af - bf;
    return {.value = std::to_string(delta), .type = AsaType::Integer};
  }
  case AsaType::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double delta = ad - bd;
    return {.value = std::to_string(delta), .type = AsaType::Integer};
  }
  default:
    return ERROR_ILLEGALINSTRUCTION;
  }
}
} // namespace asa
