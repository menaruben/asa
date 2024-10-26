#include "interpreter.hpp"
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

asa::Object eval(std::vector<Instruction> insts);
} // namespace interpreter
