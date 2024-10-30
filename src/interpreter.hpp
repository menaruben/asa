#include "transpiler.hpp"
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
namespace interpreter {

#define MAX_STACK_SIZE 8192

#define HALT                                                                   \
  { .kind = InstructionKind::Halt }

#define CLEAR                                                                  \
  { .kind = InstructionKind::Clear }

#define PUSH(val, t)                                                           \
  { .kind = InstructionKind::Push, .operand = {.value = val, .type = t}, }

#define CALL(name)                                                             \
  { .kind = InstructionKind::Call, .id = name }

#define LABEL(name)                                                            \
  { .kind = InstructionKind::Label, .id = name, }

#define GOTO(name)                                                             \
  { .kind = InstructionKind::Goto, .id = name, }

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

#define IF(val, codeblock)                                                     \
  { .kind = InstructionKind::If, .block = codeblock }

#define IFGOTO(val, gotoLabel)                                                 \
  {                                                                            \
    .kind = InstructionKind::IfGoto,                                           \
    .operand =                                                                 \
        {                                                                      \
            .value = val,                                                      \
            .type = asa::Integer,                                              \
        },                                                                     \
    .id = gotoLabel                                                            \
  }

#define IFHALT(val)                                                            \
  {                                                                            \
    .kind = InstructionKind::IfHalt, .operand = {                              \
      .value = val,                                                            \
      .type = asa::Integer                                                     \
    }                                                                          \
  }

#define INCR(var)                                                              \
  { .kind = InstructionKind::Increment, .id = var }

#define DECR(var)                                                              \
  { .kind = InstructionKind::Decrement, .id = var }

#define ADD                                                                    \
  { .kind = InstructionKind::Add }

#define SUB                                                                    \
  { .kind = InstructionKind::Subtract }

#define MUL                                                                    \
  { .kind = InstructionKind::Multiply }

#define DIV                                                                    \
  { .kind = InstructionKind::Divide }

#define SHOW                                                                   \
  { .kind = InstructionKind::Show }

asa::Object
eval(std::unordered_map<std::string, std::vector<Instruction>> program,
     std::string entryPoint, std::list<asa::Object> *stack) {
  std::unordered_map<std::string, int> labels;
  std::unordered_map<std::string, asa::Object> variables;
  std::list<asa::Object>::iterator it;
  int instPosition = 0;
  Instruction inst;
  bool halt = false;

  while (!halt) {
    if (instPosition >= program[entryPoint].size()) {
      halt = true;
      continue;
    }

    inst = program[entryPoint][instPosition++];
    switch (inst.kind) {
    case Halt: {
      halt = true;
      break;
    }

    case Clear: {
      stack->clear();
      break;
    }

    case Push:
      if (stack->size() + 1 > MAX_STACK_SIZE)
        return asa::ERROR_STACKOVERFLOW;

      stack->push_back(inst.operand);
      break;

    case Label:
      labels[inst.id] = instPosition;
      break;

    case Goto: {
      if (labels.find(inst.id) == labels.end()) {
        return asa::ERROR_LABEL_NOT_FOUND;
      }
      instPosition = labels[inst.id];
      break;
    }

    case If: {
      if (stack->size() < 2)
        return asa::ERROR_STACKUNDERFLOW;

      std::vector<asa::Object> objs = pop(stack, 2);
      asa::Object result = compare(objs[1], objs[0]);
      if (result.value == inst.operand.value) {
        for (const auto& blockInst : inst.block) {
          if (halt) break;
          eval({{entryPoint, {blockInst}}}, entryPoint, stack);
        }
      }
      break;
    }

    case IfGoto: {
      if (stack->size() < 1)
        return asa::ERROR_STACKUNDERFLOW;
      if (labels.find(inst.id) == labels.end()) {
        return asa::ERROR_LABEL_NOT_FOUND;
      }
      
      asa::Object top = pop(stack, 1)[0];
      if (top.value == inst.operand.value) {
        instPosition = labels[inst.id];
      }
      break;
    }

    case IfHalt: {
      if (stack->size() < 1)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object top = pop(stack, 1)[0];
      if (top.value == inst.operand.value) {
        halt = true;
        break;
      }
    }

    case DefVar: {
      variables[inst.id] = {.value = inst.operand.value,
                            .type = inst.operand.type};
      break;
    }

    case SetVar: {
      if (stack->size() < 1)
        return asa::ERROR_STACKUNDERFLOW;

      if (variables.find(inst.id) == variables.end())
        return asa::ERROR_UNDEFINED_VARIABLE;

      asa::Object o = pop(stack, 1)[0];
      variables[inst.id] = o;
      break;
    }

    case GetVar: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE;
      }
      asa::Object o = variables[inst.id];
      stack->push_back(o);
      break;
    }

    case Increment: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE;
      }
      asa::Object o = variables[inst.id];
      variables[inst.id] = add(o, {.value = "1", .type = o.type});
      break;
    }

    case Decrement: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE;
      }
      asa::Object o = variables[inst.id];
      variables[inst.id] = subtract(o, {.value = "1", .type = o.type});
      break;
    }

    case Cmp: {
      if (stack->size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      std::vector<asa::Object> objs = pop(stack, 2);
      stack->push_back(compare(objs[1], objs[0]));
      break;
    }

    case Add: {
      std::vector<asa::Object> args = pop(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = add(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case Subtract: {
      std::vector<asa::Object> args = pop(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = subtract(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case Multiply: {
      std::vector<asa::Object> args = pop(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = multiply(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case Divide: {
      std::vector<asa::Object> args = pop(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW;
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = divide(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case Call: {
      if (program.find(inst.id) == program.end()) {
        return asa::ERROR_ILLEGALINSTRUCTION;
      }
      std::vector<Instruction> funcinsts = program[inst.id];
      asa::Object result = eval(program, inst.id, stack);
      if (result.error != asa::Ok) {
        return result;
      }
      break;
    }

    case Show:
      printf("Stack:\n");
      if (stack->empty()) {
        printf("    [ EMPTY ]\n");
        break;
      }

      stack->reverse();
      for (asa::Object o : *stack) {
        std::cout << "    Value: " << o.value
                  << ", Type: " << asa::typeToStr(o.type) << std::endl;
      }
      printf("\n");
      stack->reverse();
      break;
    }
  }
  return asa::ERROR_OK;
}
} // namespace interpreter
