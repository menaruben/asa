#include "objects.hpp"

namespace instructions {

enum InstructionKind { Show, Push, Plus, Minus, Mult, Div };

struct Instruction {
  InstructionKind kind;
  asa::AsaObj operand;
};
}
