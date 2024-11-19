#include "objects.hpp"
#include "transpiler.hpp"
#include <cmath>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace transpiler;
namespace interpreter {

#define MAX_STACK_SIZE 8192

asa::Object eval(Program program, string entryPoint, list<asa::Object> *stack) {
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


    case InstructionKind::Ceil: {
      asa::Object o = pop_args(stack, 1)[0];
      int val_new = stoi(o.value) + 1;
      std::string valstr = to_string(val_new);
      o.value = valstr;
      o.type = asa::Integer;
      stack->push_back(o);
      break;
    }


    case InstructionKind::Floor: {
      asa::Object o = pop_args(stack, 1)[0];
      int val_new = stoi(o.value);
      std::string valstr = to_string(val_new);
      o.value = valstr;
      o.type = asa::Integer;
      stack->push_back(o);
      break;
    }

    case InstructionKind::Round: {
      asa::Object o = pop_args(stack, 1)[0];
      double val_new = round(std::stod(o.value));
      std::string valstr = to_string(static_cast<int>(val_new));
      o.value = valstr;
      o.type = asa::Integer;
      stack->push_back(o);
      break;
    }

    case InstructionKind::Clear: {
      stack->clear();
      break;
    }

    case InstructionKind::Raise: {
      asa::Object o = pop_args(stack, 1)[0];
      throw runtime_error(o.value);
    }

    case InstructionKind::Push: {
      if (stack->size() + 1 > MAX_STACK_SIZE)
        return asa::error_stackoverflow(
            "STACK OVERFLOW: Cannot push more than " +
            to_string(MAX_STACK_SIZE) + " elements");

      stack->push_back(inst.operand);
      break;
    }

    case InstructionKind::Pop: {
      if (stack->size() <= 0)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot pop from an empty stack");

      stack->pop_back();
      break;
    }

    // str <=> to_string
    case InstructionKind::Str: {
      if (stack->size() < 1)
        return asa::error_stackunderflow(
          "STACK UNDERFLOW: Cannot convert 'nothing' to string (stack empty)");

      asa::Object o = pop_args(stack, 1)[0];
      o.type = asa::String;
      stack->push_back(o);
      break;
    }

    case InstructionKind::GetType: {
      if (stack->size() < 1)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot get type of 'nothing' (stack empty)");

      asa::Object o = pop_args(stack, 1)[0];
      o.value = asa::type_to_str(o.type);
      o.type = asa::String;
      stack->push_back(o);
      break;
    }

    case InstructionKind::Label:
      break;

    case InstructionKind::Goto: {
      if (program[entryPoint].labels.find(inst.id) ==
          program[entryPoint].labels.end()) {
        return asa::error_label_not_found("LABEL NOT FOUND: " + inst.id);
      }
      instPosition = program[entryPoint].labels[inst.id];
      break;
    }

    case InstructionKind::IfGoto: {
      if (stack->size() < 1)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot perform IfGoto without at least one "
            "element (-1, 0 or 1) on the stack");

      if (program[entryPoint].labels.find(inst.id) ==
          program[entryPoint].labels.end()) {
        return asa::error_label_not_found("LABEL NOT FOUND: " + inst.id);
      }

      asa::Object top = pop_args(stack, 1)[0];
      if (top.value == inst.operand.value)
        instPosition = program[entryPoint].labels[inst.id];
      break;
    }

    case InstructionKind::IfHalt: {
      if (stack->size() < 1)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot perform IfHalt without at least one "
            "element (-1, 0 or 1) on the stack");
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
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot pop value to variable in an empty stack");

      asa::Object o = pop_args(stack, 1)[0];
      variables[inst.id] = o;
      break;
    }

    case InstructionKind::GetVar: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::error_undefined_variable("UNDEFINED VARIABLE: " + inst.id);
      }
      asa::Object o = variables[inst.id];
      stack->push_back(o);
      break;
    }

    case InstructionKind::Increment: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::error_undefined_variable("UNDEFINED VARIABLE: " + inst.id);
      }
      asa::Object o = variables[inst.id];
      variables[inst.id] = add(o, {.value = "1", .type = o.type});
      break;
    }

    case InstructionKind::Decrement: {
      if (variables.find(inst.id) == variables.end()) {
        return asa::error_undefined_variable("UNDEFINED VARIABLE: " + inst.id);
      }
      asa::Object o = variables[inst.id];
      variables[inst.id] = subtract(o, {.value = "1", .type = o.type});
      break;
    }

    case InstructionKind::Cmp: {
      if (stack->size() < 2)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot compare without at least two elements on "
            "the stack");
      vector<asa::Object> objs = pop_args(stack, 2);
      stack->push_back(compare(objs[1], objs[0]));
      break;
    }

    case InstructionKind::Add: {
      vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::error_stackunderflow("STACK UNDERFLOW: Cannot add without "
                                         "at least two elements on the stack");
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
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot subtract without at least two elements on "
            "the stack");
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
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot multiply without at least two elements on "
            "the stack");
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
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot divide without at least two elements on "
            "the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = divide(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Lshift: {
            vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot lshift without at least two elements on "
            "the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = lshift(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Rshift: {
            vector<asa::Object> args = pop_args(stack, 2);
      if (args.size() < 2)
        return asa::error_stackunderflow(
            "STACK UNDERFLOW: Cannot rshift without at least two elements on "
            "the stack");
      asa::Object a = args[0];
      asa::Object b = args[1];
      asa::Object c = rshift(b, a);
      if (c.error != asa::Ok)
        return c;
      stack->push_back(c);
      break;
    }

    case InstructionKind::Call: {
      if (program.find(inst.id) == program.end()) {
        return asa::error_illegal_instruction("ILLEGAL INSTRUCTION/BLOCK: " +
                                              inst.id);
      }
      vector<Instruction> funcinsts = program[inst.id].instructions;
      asa::Object result = eval(program, inst.id, stack);
      if (result.error != asa::Ok) {
        return result;
      }
      break;
    }

    case InstructionKind::Print: {
      if (stack->size() < 1) {
        return asa::error_stackunderflow("STACK UNDERFLOW: Cannot print from empty stack");
      }
      asa::Object top = stack->back();
      std::cout << to_string(top);
      break;
    }

    case InstructionKind::Println: {
      if (stack->size() < 1) {
        return asa::error_stackunderflow("STACK UNDERFLOW: Cannot print from empty stack");
      }
      asa::Object top = stack->back();
      std::cout << to_string(top) << std::endl;
      break;
    }

    case InstructionKind::Show:
      printf("Stack:\n");
      if (stack->empty()) {
        printf("    [ EMPTY ]\n");
        break;
      }
      list<asa::Object>::reverse_iterator it = stack->rbegin();
      while (it != stack->rend()) {
        cout <<
          "    Value: " << it->value <<
          ", Type: " << asa::type_to_str(it->type) <<
        endl;
        it++;
      }
      cout << endl;
      stack->reverse();
      break;
    }
  }
  return asa::ERROR_OK;
}
} // namespace interpreter
