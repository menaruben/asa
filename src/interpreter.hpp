#include "instructions.hpp"
#include <iostream>
#include <list>
#include <vector>

namespace interpreter {

#define MAX_STACK_SIZE 8192


#define PUSH(val, t)                                                           \
  {                                                                            \
    .kind = instructions::InstructionKind::Push,                               \
    .operand = {.value = val, .type = t},                                      \
  }

#define LABEL(name)                                                            \
  {                                                                            \
    .kind = instructions::InstructionKind::Label,                              \
    .operand = {.value = name },                                               \
  }

#define PLUS                                                                   \
  { .kind = instructions::InstructionKind::Plus }

#define MINUS                                                                  \
  { .kind = instructions::InstructionKind::Minus }

#define MULT                                                                   \
  { .kind = instructions::InstructionKind::Mult }

#define DIV                                                                    \
  { .kind = instructions::InstructionKind::Div }

#define SHOW                                                                   \
  { .kind = instructions::InstructionKind::Show }


asa::AsaObj eval(std::vector<instructions::Instruction> insts) {
  std::list<asa::AsaObj> stack;
  std::list<asa::AsaObj>::iterator it;
  for (instructions::Instruction inst : insts) {
    switch (inst.kind) {
    case instructions::Push:
      if (stack.size() + 1 > MAX_STACK_SIZE)
        return asa::ERROR_STACKOVERFLOW;

      stack.push_back(inst.operand);
      break;

    case instructions::Plus: {

      std::vector<asa::AsaObj> args = instructions::pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::AsaObj a = args[0];
      asa::AsaObj b = args[1];
      asa::AsaObj c = instructions::plus(b, a);
      if (c.error != asa::AsaError::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case instructions::Minus: {
      std::vector<asa::AsaObj> args = instructions::pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::AsaObj a = args[0];
      asa::AsaObj b = args[1];
      asa::AsaObj c = instructions::minus(b, a);
      if (c.error != asa::AsaError::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case instructions::Mult: {
      std::vector<asa::AsaObj> args = instructions::pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::AsaObj a = args[0];
      asa::AsaObj b = args[1];
      asa::AsaObj c = instructions::mult(b, a);
      if (c.error != asa::AsaError::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case instructions::Div: {
      std::vector<asa::AsaObj> args = instructions::pop(&stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::AsaObj a = args[0];
      asa::AsaObj b = args[1];
      asa::AsaObj c = instructions::div(b, a);
      if (c.error != asa::AsaError::Ok)
        return c;
      stack.push_back(c);
      break;
    }

    case instructions::Show:
      printf("Stack:\n");
      if (stack.empty()) {
        printf("    [ EMPTY ]\n");
        break;
      }

      stack.reverse();
      for (asa::AsaObj o : stack) {
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
