#include "transpiler.hpp"
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace transpiler;
namespace interpreter {

#define MAX_STACK_SIZE 8192

asa::Object eval(Program program,
     string entryPoint, list<asa::Object> *stack) {
  unordered_map<string, asa::Object> variables;
  list<asa::Object>::iterator it;
  int instPosition = 0;
  Instruction inst;
  bool halt = false;
  string blockctx = entryPoint;

  while (!halt) {
    if (instPosition >= program[entryPoint].instructions.size()) {
      halt = true;
      continue;
    }

    inst = program[entryPoint].instructions[instPosition++];
    switch (inst.kind) {
    case InstructionKind::Halt: {
      halt = true;
      break;
    }

    case InstructionKind::Clear: {
      stack->clear();
      break;
    }

    case InstructionKind::Push: {
      if (stack->size() + 1 > MAX_STACK_SIZE)
        return asa::ERROR_STACKOVERFLOW("STACK OVERFLOW: Cannot push more than " +
                                        to_string(MAX_STACK_SIZE) + " elements");

      stack->push_back(inst.operand);
      break;
    }

    case InstructionKind::Pop: {
      if (stack->size() <= 0)
        return asa::ERROR_STACKUNDERFLOW("STACK UNDERFLOW: Cannot pop from an empty stack");

      stack->pop_back();
      break;
    }

    case InstructionKind::Label:
      break;

    case InstructionKind::Goto: {
      if (program[entryPoint].labels.find(inst.id) == program[entryPoint].labels.end()) {
        return asa::ERROR_LABEL_NOT_FOUND("LABEL NOT FOUND: " + inst.id);
      }
      instPosition = program[entryPoint].labels[inst.id];
      break;
    }

    case InstructionKind::IfGoto: {
      if (stack->size() < 1)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot perform IfGoto without at least one element (-1, 0 or 1) on the stack");

      if (program[entryPoint].labels.find(inst.id) == program[entryPoint].labels.end()) {
        return asa::ERROR_LABEL_NOT_FOUND("LABEL NOT FOUND: " + inst.id);
      }

      asa::Object top = pop_args(stack, 1)[0];
      if (top.value == inst.operand.value)
        instPosition = program[entryPoint].labels[inst.id];
      break;
    }

    case InstructionKind::IfHalt: {
      if (stack->size() < 1)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot perform IfHalt without at least one element (-1, 0 or 1) on the stack");
      asa::Object top = pop_args(stack, 1)[0];
      if (top.value == inst.operand.value) {
        halt = true;
        break;
      }
    }

    case InstructionKind::DefVar: {
      variables[inst.id] = {.value = inst.operand.value,
                            .type = inst.operand.type};
      break;
    }

    // SetVar <=> Pop
    case InstructionKind::SetVar: {
      if (stack->size() < 1)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot pop value to variable in an empty stack");

      asa::Object o = pop_args(stack, 1)[0];
      variables[inst.id] = o;
      break;
    }

    case InstructionKind::GetVar: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE("UNDEFINED VARIABLE: " + inst.id);
      }
      asa::Object o = variables[inst.id];
      stack->push_back(o);
      break;
    }

    case InstructionKind::Increment: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE("UNDEFINED VARIABLE: " + inst.id);
      }
      asa::Object o = variables[inst.id];
      variables[inst.id] = add(o, {.value = "1", .type = o.type});
      break;
    }

    case InstructionKind::Decrement: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::ERROR_UNDEFINED_VARIABLE("UNDEFINED VARIABLE: " + inst.id);
      }
      asa::Object o = variables[inst.id];
      variables[inst.id] = subtract(o, {.value = "1", .type = o.type});
      break;
    }

    case InstructionKind::Cmp: {
      if (stack->size() < 2)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot compare without at least two elements on the stack");
      vector<asa::Object> objs = pop_args(stack, 2);
      stack->push_back(compare(objs[1], objs[0]));
      break;
    }

    case InstructionKind::Add: {
      vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot add without at least two elements on the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = add(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Subtract: {
      vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot subtract without at least two elements on the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = subtract(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Multiply: {
      vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot multiply without at least two elements on the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = multiply(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Divide: {
      vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::ERROR_STACKUNDERFLOW(
          "STACK UNDERFLOW: Cannot divide without at least two elements on the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = divide(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Call: {
      if (program.find(inst.id) == program.end()) {
        return asa::ERROR_ILLEGALINSTRUCTION("ILLEGAL INSTRUCTION/BLOCK: " + inst.id);
      }
      vector<Instruction> funcinsts = program[inst.id].instructions;
      asa::Object result = eval(program, inst.id, stack);
      if (result.error != asa::Ok) {
        return result;
      }
      break;
    }

    case InstructionKind::Show:
      printf("Stack:\n");
      if (stack->empty()) {
        printf("    [ EMPTY ]\n");
        break;
      }

      stack->reverse();
      for (asa::Object o : *stack) {
        cout << "    Value: " << o.value
                  << ", Type: " << asa::typeToStr(o.type) << endl;
      }
      printf("\n");
      stack->reverse();
      break;
    }
  }
  return asa::ERROR_OK;
}
} // namespace interpreter
