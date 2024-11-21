#include "AsaBigDouble.hpp"
#include "AsaBigInteger.hpp"
#include "AsaObject.hpp"
#include "AsaString.hpp"
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

bool can_pop(list<AsaObject> stack, int count = 1) {
  if (stack.size() < count)
    return false;
  return true;
}

bool can_push(list<AsaObject> stack) {
  if (stack.size() + 1 > MAX_STACK_SIZE)
    return false;
  return true;
}

AsaObject eval(Program program, string entryPoint, list<AsaObject> *stack) {
  unordered_map<string, AsaObject> variables;
  list<AsaObject>::iterator it;

  int instPosition = 0;
  bool halt = false;
  string blockctx = entryPoint;

  while (!halt) {
    if (instPosition >= program[entryPoint].instructions.size()) {
      halt = true;
      continue;
    }

    Instruction inst = program[entryPoint].instructions[instPosition++];
    switch (inst.kind) {
    case InstructionKind::Halt: {
      halt = true;
      break;
    }

    case InstructionKind::Ceil: {
      AsaObject o = pop_args(stack, 1)[0];
      stack->push_back(o.ceil());
      break;
    }

    case InstructionKind::Floor: {
      AsaObject o = pop_args(stack, 1)[0];
      stack->push_back(o.floor());
      break;
    }

    case InstructionKind::Round: {
      AsaObject o = pop_args(stack, 1)[0];
      stack->push_back(o.round());
      break;
    }

    case InstructionKind::Clear: {
      stack->clear();
      break;
    }

    case InstructionKind::Raise: {
      AsaObject o = pop_args(stack, 1)[0];
      throw runtime_error(o.str());
    }

    case InstructionKind::Push: {
      if (!can_push(*stack))
        return StackOverflowError;

      stack->push_back(inst.operand);
      break;
    }

    case InstructionKind::Pop: {
      if (!can_pop(*stack))
        return StackUnderflowError;

      stack->pop_back();
      break;
    }

    // str <=> to_string
    case InstructionKind::Str: {
      if (!can_pop(*stack))
        return StackUnderflowError;

      AsaObject o = pop_args(stack, 1)[0];
      stack->push_back(AsaString(o.str()));
      break;
    }

    case InstructionKind::GetType: {
      can_pop(*stack);
      AsaObject o = pop_args(stack, 1)[0];
      stack->push_back(AsaString(o.get_type_str()));
      break;
    }

    case InstructionKind::Label:
      break;

    case InstructionKind::Goto: {
      if (program[entryPoint].labels.find(inst.id) ==
          program[entryPoint].labels.end()) {
        return AsaError(LabelNotFound, inst.id);
      }
      instPosition = program[entryPoint].labels[inst.id];
      break;
    }

    case InstructionKind::IfGoto: {
      if (!can_pop(*stack))
        return StackUnderflowError;
      if (program[entryPoint].labels.find(inst.id) ==
          program[entryPoint].labels.end()) {
        return AsaError(LabelNotFound, inst.id);
      }

      AsaObject top = pop_args(stack, 1)[0];
      AsaObject other = inst.operand;
      if (top.cmp(other).str() == "0")
        instPosition = program[entryPoint].labels[inst.id];
      break;
    }

    case InstructionKind::DefVar: {
      switch (inst.operand.get_type()) {
      case asa::Integer: {
        variables[inst.id] = AsaInteger(stoi(inst.operand.str()));
        break;
      }

      case asa::Float: {
        variables[inst.id] = AsaFloat(stof(inst.operand.str()));
        break;
      }

      case asa::Double: {
        variables[inst.id] = AsaDouble(stod(inst.operand.str()));
        break;
      }

      case asa::String: {
        variables[inst.id] = AsaString(inst.operand.str());
        break;
      }

      case asa::BigInteger: {
        variables[inst.id] = AsaBigInteger(stoll(inst.operand.str()));
        break;
      }

      case asa::BigDouble: {
        variables[inst.id] = AsaBigDouble(stold(inst.operand.str()));
        break;
      }

      default:
        throw runtime_error("Not Implemented");
      }
      break;
    }

    // SetVar <=> Pop
    case InstructionKind::SetVar: {
      AsaObject o = pop_args(stack, 1)[0];
      variables[inst.id] = o;
      break;
    }

    case InstructionKind::GetVar: {
      if (variables.find(inst.id) == variables.end()) {
        return UndefinedVariableError;
      }
      AsaObject o = variables[inst.id];
      stack->push_back(o);
      break;
    }

    case InstructionKind::Increment: {
      if (variables.find(inst.id) == variables.end()) {
        return UndefinedVariableError;
      }
      AsaObject o = variables[inst.id];
      variables[inst.id] = o.add(AsaInteger(1));
      break;
    }

    case InstructionKind::Decrement: {
      if (variables.find(inst.id) == variables.end()) {
        return UndefinedVariableError;
      }
      AsaObject o = variables[inst.id];
      variables[inst.id] = o.sub(AsaInteger(1));
      break;
    }

    case InstructionKind::Cmp: {
      vector<AsaObject> objs = pop_args(stack, 2);
      stack->push_back(objs[0].cmp(objs[1]));
      break;
    }

    case InstructionKind::Add: {
      vector<AsaObject> args = pop_args(stack, 2);
      AsaObject rhs = args[0];
      AsaObject lhs = args[1];
      AsaObject res = rhs.add(lhs);
      if (res.get_error_type() != Ok)
        return res;
      stack->push_back(res);
      break;
    }

    case InstructionKind::Subtract: {
      vector<AsaObject> args = pop_args(stack, 2);
      AsaObject rhs = args[0];
      AsaObject lhs = args[1];
      AsaObject res = lhs.sub(rhs);
      if (res.get_error_type() != Ok)
        return res;
      stack->push_back(res);
      break;
    }

    case InstructionKind::Multiply: {
      vector<AsaObject> args = pop_args(stack, 2);
      AsaObject rhs = args[0];
      AsaObject lhs = args[1];
      AsaObject res = rhs.mul(lhs);
      if (res.get_error_type() != Ok)
        return res;
      stack->push_back(res);
      break;
    }

    case InstructionKind::Divide: {
      vector<AsaObject> args = pop_args(stack, 2);
      AsaObject rhs = args[0];
      AsaObject lhs = args[1];
      AsaObject res = lhs.div(rhs);
      if (res.get_error_type() != Ok)
        return res;
      stack->push_back(res);
      break;
    }

    case InstructionKind::Lshift: {
      vector<AsaObject> args = pop_args(stack, 2);
      AsaObject rhs = args[0];
      AsaObject lhs = args[1];
      AsaObject res = lhs.lshift(rhs);
      if (res.get_error_type() != Ok)
        return res;
      stack->push_back(res);
      break;
    }

    case InstructionKind::Rshift: {
      vector<AsaObject> args = pop_args(stack, 2);
      AsaObject rhs = args[0];
      AsaObject lhs = args[1];
      AsaObject res = lhs.rshift(rhs);
      if (res.get_error_type() != Ok)
        return res;
      stack->push_back(res);
      break;
    }

    case InstructionKind::Call: {
      if (program.find(inst.id) == program.end()) {
        return IllegalInstructionError;
      }
      vector<Instruction> funcinsts = program[inst.id].instructions;
      AsaObject result = eval(program, inst.id, stack);
      if (result.get_error_type() != asa::Ok) {
        return result;
      }
      break;
    }

    case InstructionKind::Print: {
      if (!can_pop(*stack))
        return StackUnderflowError;
      AsaObject top = stack->back();
      std::cout << top.str();
      break;
    }

    case InstructionKind::Println: {
      if (!can_pop(*stack))
        return StackUnderflowError;
      AsaObject top = stack->back();
      std::cout << top.str() << std::endl;
      break;
    }

    case InstructionKind::Show:
      printf("Stack:\n");
      if (stack->empty()) {
        printf("    [ EMPTY ]\n");
        break;
      }
      list<AsaObject>::reverse_iterator it = stack->rbegin();
      while (it != stack->rend()) {
        cout << "    Value: " << it->str()
             << ", Type: " << asa::type_to_str(it->get_type()) << endl;
        it++;
      }
      cout << endl;
      stack->reverse();
      break;
    }
  }
  return OkError;
}
} // namespace interpreter
