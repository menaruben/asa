#include "instructions.hpp"
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
namespace interpreter {

#define MAX_STACK_SIZE 8192

#define PUSH(val, t)                                                           \
  { .kind = InstructionKind::Push, .operand = {.value = val, .type = t}, }

#define LABEL(name)                                                            \
  { .kind = InstructionKind::Label, .id = name, }

#define JUMP(name)                                                             \
  { .kind = InstructionKind::Jump, .id = name, }

#define DEF(name, val, t)                                                      \
  {                                                                            \
    .kind = InstructionKind::DefVar, .operand = {.value = val, .type = t},     \
    .id = name,                                                                \
  }

#define SET(name)                                                              \
  { .kind = InstructionKind::SetVar, .id = name }

#define GET(name)                                                              \
  { .kind = InstructionKind::GetVar, .id = name }

#define CMP                                                                    \
  { .kind = InstructionKind::Cmp }

#define IF(val, gotoLabel)                                                     \
  {                                                                            \
    .kind = InstructionKind::If,                                               \
    .operand =                                                                 \
        {                                                                      \
            .value = val,                                                      \
            .type = asa::Integer,                                              \
        },                                                                     \
    .id = gotoLabel                                                            \
  }

#define PLUS                                                                   \
  { .kind = InstructionKind::Plus }

#define MINUS                                                                  \
  { .kind = InstructionKind::Minus }

#define MULT                                                                   \
  { .kind = InstructionKind::Mult }

#define DIV                                                                    \
  { .kind = InstructionKind::Div }

#define SHOW                                                                   \
  { .kind = InstructionKind::Show }

asa::Object eval(std::vector<Instruction> insts) {
  std::list<asa::Object> stack;
  std::unordered_map<std::string, int> labels;
  std::unordered_map<std::string, asa::Object> variables;
  std::list<asa::Object>::iterator it;
  int instPosition = 0;
  Instruction inst;
  bool halt = false;

  while (!halt) {
    if (instPosition >= insts.size()) {
      halt = true;
      continue;
    }

    inst = insts[instPosition++];
    switch (inst.kind) {
    case Push:
      if (stack.size() + 1 > MAX_STACK_SIZE)
        return asa::ERROR_STACKOVERFLOW;

      stack.push_back(inst.operand);
      break;

    case Label:
      labels[inst.id] = instPosition;
      break;

    case Jump: {
      if (labels.find(inst.id) == labels.end()) {
        return asa::ERROR_LABEL_NOT_FOUND;
      }
      instPosition = labels[inst.id];
      break;
    }

    case If: {
      if (stack.size() < 1)
        return asa::ERROR_STACKUNDERFLOW;
      if (labels.find(inst.id) == labels.end()) {
        return asa::ERROR_LABEL_NOT_FOUND;
      }
      asa::Object top = pop(&stack, 1)[0];
      if (top.value == inst.operand.value) {
        instPosition = labels[inst.id];
      }
      break;
    }

    case DefVar: {
      variables[inst.id] = {.value = inst.operand.value,
                            .type = inst.operand.type};
      break;
    }

    case SetVar: {
      if (stack.size() < 1)
        return asa::ERROR_STACKUNDERFLOW;

      if (variables.find(inst.id) == variables.end())
        return asa::ERROR_UNDEFINED_VARIABLE;

      asa::Object o = pop(&stack, 1)[0];
      variables[inst.id] = o;
      break;
    }

    case GetVar: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE;
      }
      asa::Object o = variables[inst.id];
      stack.push_back(o);
      break;
    }

    case Cmp: {
      if (stack.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      std::vector<asa::Object> objs = pop(&stack, 2);
      stack.push_back(compare(objs[1], objs[0]));
      break;
    }

    case Plus: {
      std::vector<asa::Object> args = pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = plus(b, a);
      if (c.error != asa::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case Minus: {
      std::vector<asa::Object> args = pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = minus(b, a);
      if (c.error != asa::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case Mult: {
      std::vector<asa::Object> args = pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = mult(b, a);
      if (c.error != asa::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case Div: {
      std::vector<asa::Object> args = pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = div(b, a);
      if (c.error != asa::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case Show:
      printf("Stack:\n");
      if (stack.empty()) {
        printf("    [ EMPTY ]\n");
        break;
      }

      stack.reverse();
      for (asa::Object o : stack) {
        std::cout << "    Value: " << o.value
                  << ", Type: " << asa::typeToStr(o.type) << std::endl;
      }
      printf("\n");
      stack.reverse();
      break;
    }
  }
  return asa::ERROR_OK;
}
} // namespace interpreter
