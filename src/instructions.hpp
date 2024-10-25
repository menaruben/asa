#include "objects.hpp"
#include "vector"
#include "list"

namespace instructions {

enum InstructionKind { Show, Push, Plus, Minus, Mult, Div };

struct Instruction {
  InstructionKind kind;
  asa::AsaObj operand;
};

asa::AsaObj plus(asa::AsaObj a, asa::AsaObj b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return asa::ERROR_ARITHMETIC;

  switch (a.type) {
  case asa::AsaType::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int sum = ai + bi;
    return {.value = std::to_string(sum), .type = asa::AsaType::Integer};
  }
  case asa::AsaType::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float sum = af + bf;
    return {.value = std::to_string(sum), .type = asa::AsaType::Integer};
  }
  case asa::AsaType::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double sum = ad + bd;
    return {.value = std::to_string(sum), .type = asa::AsaType::Integer};
  }

  default:
    return asa::ERROR_ILLEGALINSTRUCTION;
  }
}

asa::AsaObj minus(asa::AsaObj a, asa::AsaObj b) {
  if (a.type != b.type)
    return asa::ERROR_TYPEMISMATCH;

  if (!isNumericType(a) || !isNumericType(b))
    return asa::ERROR_ARITHMETIC;

  switch (a.type) {
  case asa::AsaType::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int delta = ai - bi;
    return {.value = std::to_string(delta), .type = asa::AsaType::Integer};
  }
  case asa::AsaType::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float delta = af - bf;
    return {.value = std::to_string(delta), .type = asa::AsaType::Integer};
  }
  case asa::AsaType::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double delta = ad - bd;
    return {.value = std::to_string(delta), .type = asa::AsaType::Integer};
  }
  default:
    return asa::ERROR_ILLEGALINSTRUCTION;
  }
}

std::vector<asa::AsaObj> pop(std::list<asa::AsaObj> *stack, int count)
{
  std::vector<asa::AsaObj> args;
  std::list<asa::AsaObj>::iterator it;
  if (stack->size() < count)
  {
    args.push_back(asa::ERROR_STACKUNDERFLOW);
    return args;
  };
  
  asa::AsaObj o;
  int i = 0;
  while (i < count)
  {
    o = stack->back();
    args.push_back(o);
    it = std::prev(stack->end());
    stack->erase(it);
    i++;
  }
  return args;
}
}
