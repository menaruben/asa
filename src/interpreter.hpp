#include "instructions.hpp"
#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

namespace interpreter {

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define PUSH(valstr, t)                                                        \
  {                                                                            \
    .kind = instructions::InstructionKind::Push,                               \
    .operand = {.value = valstr, .type = t},                                   \
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

int eval(std::vector<instructions::Instruction> insts) {
  std::list<asa::AsaObj> stack;

  std::list<asa::AsaObj>::iterator it;
  for (instructions::Instruction inst : insts) {
    switch (inst.kind) {
    case instructions::Push:
      stack.push_back(inst.operand);
      break;

    case instructions::Plus: {
      if (stack.size() < 2)
        return -1; // TODO: add errors / exceptions
      asa::AsaObj a = stack.back();
      it = std::prev(stack.end());
      stack.erase(it);
      asa::AsaObj b = stack.back();
      it = std::prev(stack.end());
      stack.erase(it);
      stack.push_back(asa::add(a, b));
      break;
    }

    case instructions::Show:
      printf("Stack:\n");
      if (stack.empty()) {
        printf("[ EMPTY ]");
        break;
      }

      for (asa::AsaObj o : stack) {
        std::cout << o.value << std::endl;
      }
      break;
    }
  }
  return 0;
}
} // namespace interpreter
