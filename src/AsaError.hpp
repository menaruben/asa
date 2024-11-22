#pragma once

#include "AsaObject.hpp"

class AsaError : public AsaObject {
public:
  AsaError(Error err, std::string msg) : AsaObject(err, msg) {}
};

const AsaError OkError = AsaError(Ok, "No error, everything is fine! :)");

const AsaError StackOverflowError =
    AsaError(StackOverflow, "Stack reached its limit");

const AsaError StackUnderflowError =
    AsaError(StackUnderflow, "Cannot pop from empty stack");

inline AsaError LabelNotFoundError(std::string label_name) { return AsaError(LabelNotFound, "Label not found: " + label_name); }

const AsaError DivByZeroError =
    AsaError(DivByZero, "Division by Zero encountered");

inline AsaError IllegalInstructionError(std::string inst_name) {
  return AsaError(IllegalInstruction,
                  "Illegal instruction encountered: " + inst_name);
}

inline AsaError UndefinedVariableError(std::string var_name) {
  return AsaError(UndefinedVariable, "Undefined variable: " + var_name);
}
