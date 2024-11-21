#pragma once
#include "objects.hpp"
#include <stdexcept>
#include <string>

using namespace asa;

class AsaObject {
private:
  string value;
  Type type;
  Error error;

public:
  AsaObject() {}
  
  AsaObject(string val, Type t) {
    value = val;
    type = t;
    error = Ok;
  }

  AsaObject(Error err, string message) {
    value = message;
    type = String;
    error = err;
  }

  string get_error() const { return error_to_str(error) + ": " +  value; }
  Error get_error_type() const { return error; }

  string get_value() const { return value; }
  void set_value(string val) { value = val; }
  Type get_type() const { return type; }
  string get_type_str() const { return type_to_str(type); }
  string str() const { return value; }

  AsaObject add(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject sub(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject mul(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject div(AsaObject o) { throw runtime_error("Not Implemented"); }

  AsaObject lshift(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject rshift(AsaObject o) { throw runtime_error("Not Implemented"); }

  AsaObject ceil() { throw runtime_error("Not Implemented"); }
  AsaObject floor() { throw runtime_error("Not Implemented"); }
  AsaObject round() { throw runtime_error("Not Implemented"); }
  AsaObject incr() { throw runtime_error("Not Implemented"); }
  AsaObject decr() { throw runtime_error("Not Implemented"); }

  AsaObject bitwise_or(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject bitwise_xor(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject bitwise_and(AsaObject o) { throw runtime_error("Not Implemented"); }
  AsaObject bitwise_not(AsaObject o) { throw runtime_error("Not Implemented"); }

  AsaObject cmp(AsaObject o) { throw runtime_error("Not Implemented"); }
};

class AsaError : public AsaObject {
private:
public:
  AsaError(Error err, string msg) : AsaObject(err, msg) {}
};

// TODO: convert to separate error classes and add value of label, variable id etc..
const AsaError OkError = AsaError(Ok, "No error, everything is fine! :)");
const AsaError StackOverflowError = AsaError(StackOverflow, "Stack reached its limit");
const AsaError StackUnderflowError = AsaError(StackUnderflow, "Cannot pop from empty stack");
const AsaError LabelNotFoundError = AsaError(LabelNotFound, "Label not found");
const AsaError DivByZeroError = AsaError(DivByZero, "Division by Zero encountered");
const AsaError IllegalInstructionError = AsaError(IllegalInstruction, "Illegal instruction encountered");
const AsaError UndefinedVariableError = AsaError(UndefinedVariable, "Undefined variable");

class AsaInteger;
class AsaFloat;
class AsaDouble;
class AsaString;
class AsaChar;
class AsaBigInteger;
class AsaBigDouble;
