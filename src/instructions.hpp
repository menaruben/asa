#pragma once
#include "AsaObject.hpp"
#include "objects.hpp"
#include "vector"
#include <cfloat>
#include <functional>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define CEIL                                                                   \
  { .kind = InstructionKind::Ceil }

#define FLOOR                                                                  \
  { .kind = InstructionKind::Floor }

#define ROUND                                                                  \
  { .kind = InstructionKind::Round }

#define RAISE                                                                  \
  { .kind = InstructionKind::Raise }

#define HALT                                                                   \
  { .kind = InstructionKind::Halt }

#define CLEAR                                                                  \
  { .kind = InstructionKind::Clear }

#define PUSH(o)                                                                \
  { .kind = InstructionKind::Push, .operand = o, }

#define INCREMENT(name)                                                        \
  { .kind = InstructionKind::Increment, .id = name }

#define DECREMENT(name)                                                        \
  { .kind = InstructionKind::Decrement, .id = name }

#define POP                                                                    \
  { .kind = InstructionKind::Pop }

#define CALL(name)                                                             \
  { .kind = InstructionKind::Call, .id = name }

#define LABEL(name, pos)                                                       \
  {                                                                            \
    .kind = InstructionKind::Label,                                            \
    .operand = {.value = pos, .type = asa::Integer}, .id = name,               \
  }

#define GOTO(name)                                                             \
  { .kind = InstructionKind::Goto, .id = name, }

#define DEF(name, o)                                                           \
  { .kind = InstructionKind::DefVar, .operand = o, .id = name, }

// basically SET n == POP n <=> pop top of stack to var n
#define SET(name)                                                              \
  { .kind = InstructionKind::SetVar, .id = name }

#define GET(name)                                                              \
  { .kind = InstructionKind::GetVar, .id = name }

#define STR                                                                    \
  { .kind = InstructionKind::Str }

#define CMP                                                                    \
  { .kind = InstructionKind::Cmp }

#define IFGOTO(val, label)                                                     \
  {                                                                            \
    .kind = InstructionKind::IfGoto,                                           \
    .operand = val, .id = label               \
  }

#define ADD                                                                    \
  { .kind = InstructionKind::Add }

#define SUB                                                                    \
  { .kind = InstructionKind::Subtract }

#define MUL                                                                    \
  { .kind = InstructionKind::Multiply }

#define DIV                                                                    \
  { .kind = InstructionKind::Divide }

#define GETTYPE                                                                \
  { .kind = InstructionKind::GetType }

#define SHOW                                                                   \
  { .kind = InstructionKind::Show }

#define PRINT                                                                  \
  { .kind = InstructionKind::Print }

#define PRINTLN                                                                \
  { .kind = InstructionKind::Println }

#define LSHIFT                                                                 \
  { .kind = InstructionKind::Lshift }

#define RSHIFT                                                                 \
  { .kind = InstructionKind::Rshift }

namespace instructions {

enum InstructionKind {
  Show,
  Str,
  Print,
  Println,
  Push,
  Pop,
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
  IfGoto,
  Halt,
  Clear,
  Increment,
  Decrement,
  Call,
  Lshift,
  Rshift,
  GetType,
  Raise,
  Ceil,
  Floor,
  Round,
};

struct Instruction {
  InstructionKind kind;
  AsaObject operand;
  std::string id;
  std::vector<Instruction> block;
};

std::vector<AsaObject> pop_args(std::list<AsaObject> *stack, int count) {
  std::vector<AsaObject> args;
  std::list<AsaObject>::iterator it;
  if (stack->size() < count) {
    throw runtime_error(
        AsaError(StackUnderflow, "Cannot pop args without at least " +
                                     std::to_string(count) +
                                     " elements on the stack")
            .get_error());

    return args;
  };

  int i = 0;
  while (i < count) {
    AsaObject o = stack->back();
    args.push_back(o);
    it = std::prev(stack->end());
    stack->erase(it);
    i++;
  }
  return args;
}

std::string instructionkind_to_str(InstructionKind k) {
  switch (k) {
  case Show:
    return "Show";
  case Print:
    return "Print";
  case Println:
    return "Println";
  case Push:
    return "Push";
  case Pop:
    return "Pop";
  case Add:
    return "Add";
  case Subtract:
    return "Subtract";
  case Multiply:
    return "Multiply";
  case Divide:
    return "Divide";
  case Label:
    return "Label";
  case Goto:
    return "Goto";
  case DefVar:
    return "DefVar";
  case SetVar:
    return "SetVar";
  case GetVar:
    return "GetVar";
  case Cmp:
    return "Cmp";
  case IfGoto:
    return "IfGoto";
  case Halt:
    return "Halt";
  case Clear:
    return "Clear";
  case Increment:
    return "Increment";
  case Decrement:
    return "Decrement";
  case Call:
    return "Call";
  case Raise:
    return "Raise";
  default:
    throw std::runtime_error("Unsupported instruction kind");
  }
}

std::string instruction_to_str(Instruction inst) {
  std::string typestr = instructionkind_to_str(inst.kind);
  std::string operand = inst.operand.get_value();
  std::string id = inst.id;
  return "kind: " + typestr + ", operand: " + operand + ", id: " + id;
}

} // namespace instructions
