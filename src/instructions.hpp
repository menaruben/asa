#include "list"
#include "objects.hpp"
#include "vector"

namespace instructions {

enum InstructionKind { Show, Push, Plus, Minus, Mult, Div, Label };

struct Instruction {
  InstructionKind kind;
  asa::Object operand;
};

asa::Object plus(asa::Object a, asa::Object b) {
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

asa::Object minus(asa::Object a, asa::Object b) {
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
asa::Object mult(asa::Object a, asa::Object b) {
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

asa::Object div(asa::Object a, asa::Object b) {
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
