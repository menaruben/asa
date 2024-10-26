#include "instructions.hpp"
#include <iostream>
#include <list>
#include <vector>

using namespace instructions;
namespace interpreter {

#define MAX_STACK_SIZE 8192


#define PUSH(val, t)                                                           \
  {                                                                            \
    .kind = InstructionKind::Push,                               \
    .operand = {.value = val, .type = t},                                      \
  }

#define LABEL(name)                                                            \
  {                                                                            \
    .kind = InstructionKind::Label,                              \
    .operand = {.value = name },                                               \
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
