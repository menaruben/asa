#include "instructions.hpp"
#include <iostream>
#include <vector>
#include <list>

namespace interpreter {

#define PUSH(val, t)                                                        \
  {                                                                            \
    .kind = instructions::InstructionKind::Push,                               \
    .operand = {.value = val, .type = t},                                   \
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
      stack.push_back(inst.operand);
      break;

    case instructions::Plus: {
      if (stack.size() < 2) 
        return asa::ERROR_STACKUNDERFLOW;
      
      asa::AsaObj a = stack.back();
      it = std::prev(stack.end());
      stack.erase(it);
      asa::AsaObj b = stack.back();
      it = std::prev(stack.end());
      stack.erase(it);
      stack.push_back(asa::add(a, b));
      break;
    }

    case instructions::Minus: {
      if (stack.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      
      asa::AsaObj a = stack.back();
      it = std::prev(stack.end());
      stack.erase(it);
      asa::AsaObj b = stack.back();
      it = std::prev(stack.end());
      stack.erase(it);
      stack.push_back(asa::subtract(a, b));
      break;
    }

    case instructions::Show:
      printf("Stack:\n");
      if (stack.empty()) {
        printf("[ EMPTY ]\n");
        break;
      }

      for (asa::AsaObj o : stack) {
        std::cout << o.value << std::endl;
      }
      printf("\n");
      break;
    }
  }
  return asa::ERROR_OK;
}
} // namespace interpreter
