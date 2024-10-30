#include "list"
#include "objects.hpp"
#include "vector"
#include <exception>
#include <string>
#include <vector>

namespace instructions {

enum InstructionKind {
  Show,
  Push,
  Add,
  Subtract,
  Multiply,
  Divide,
  Label,
  Goto,
  DefVar,
  SetVar,
  GetVar,
  Cmp,
  If,
  IfGoto,
  IfHalt,
  Halt,
  Clear,
  Increment,
  Decrement,
  Call
};

struct Instruction {
  InstructionKind kind;
  asa::Object operand;
  std::string id;
  std::vector<Instruction> block;
};

asa::Object add(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return asa::ERROR_ARITHMETIC;

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int sum = ai + bi;
    return {.value = std::to_string(sum), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float sum = af + bf;
    return {.value = std::to_string(sum), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double sum = ad + bd;
    return {.value = std::to_string(sum), .type = asa::Double};
  }

  default:
    return asa::ERROR_ILLEGALINSTRUCTION;
  }
}

asa::Object subtract(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return asa::ERROR_ARITHMETIC;

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int delta = ai - bi;
    return {.value = std::to_string(delta), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float delta = af - bf;
    return {.value = std::to_string(delta), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double delta = ad - bd;
    return {.value = std::to_string(delta), .type = asa::Double};
  }
  default:
    return asa::ERROR_ILLEGALINSTRUCTION;
  }
}
asa::Object multiply(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return asa::ERROR_ARITHMETIC;

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int prod = ai * bi;
    return {.value = std::to_string(prod), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float prod = af * bf;
    return {.value = std::to_string(prod), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double prod = ad * bd;
    return {.value = std::to_string(prod), .type = asa::Double};
  }
  default:
    return asa::ERROR_ILLEGALINSTRUCTION;
  }
}

asa::Object divide(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return asa::ERROR_ARITHMETIC;

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int quotient = ai / bi;
    return {.value = std::to_string(quotient), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float quotient = af / bf;
    return {.value = std::to_string(quotient), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double quotient = ad / bd;
    return {.value = std::to_string(quotient), .type = asa::Double};
  }
  default:
    return asa::ERROR_ILLEGALINSTRUCTION;
  }
}

asa::Object compare(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;
  asa::Type returnType = a.type;

  switch (returnType) {
  case asa::String: {
    std::string result;
    if (a.value < b.value)
      result = "-1";
    if (a.value == b.value)
      result = "0";
    if (a.value < b.value)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    std::string result;
    if (ai < bi)
      result = "-1";
    if (ai == bi)
      result = "0";
    if (ai > bi)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Float: {
    int af = std::stof(a.value);
    int bf = std::stof(b.value);
    std::string result;
    if (af < bf)
      result = "-1";
    if (af == bf)
      result = "0";
    if (af > bf)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Double: {
    int ad = std::stod(a.value);
    int bd = std::stod(b.value);
    std::string result;
    if (ad < bd)
      result = "-1";
    if (ad == bd)
      result = "0";
    if (ad > bd)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  default:
    throw std::exception(); // unreachable
  }
}

std::vector<asa::Object> pop(std::list<asa::Object> *stack, int count) {
  std::vector<asa::Object> args;
  std::list<asa::Object>::iterator it;
  if (stack->size() < count) {
    args.push_back(asa::ERROR_STACKUNDERFLOW);
    return args;
  };

  asa::Object o;
  int i = 0;
  while (i < count) {
    o = stack->back();
    args.push_back(o);
    it = std::prev(stack->end());
    stack->erase(it);
    i++;
  }
  return args;
}
} // namespace instructions
