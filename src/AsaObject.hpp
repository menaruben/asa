#pragma once

#include "objects.hpp"
#include <stdexcept>
#include <string>

using namespace asa;

class AsaObject {
private:
  std::string value;
  Type type;
  Error error;

public:
  AsaObject() : error(Ok) {}

  AsaObject(std::string val, Type t) : value(val), type(t), error(Ok) {}

  AsaObject(Error err, std::string message)
      : value(message), type(String), error(err) {}

  std::string get_error() const { return error_to_str(error) + ": " + value; }

  Error get_error_type() const { return error; }

  std::string get_value() const { return value; }

  void set_value(std::string val) { value = val; }

  Type get_type() const { return type; }

  std::string get_type_str() const { return type_to_str(type); }

  virtual std::string str() const { return value; }

  virtual AsaObject add(AsaObject o) {
    throw std::runtime_error("Add Not Implemented");
  }
  virtual AsaObject sub(AsaObject o) {
    throw std::runtime_error("Sub Not Implemented");
  }
  virtual AsaObject mul(AsaObject o) {
    throw std::runtime_error("Mul Not Implemented");
  }
  virtual AsaObject div(AsaObject o) {
    throw std::runtime_error("Div Not Implemented");
  }

  virtual AsaObject lshift(AsaObject o) {
    throw std::runtime_error("Lshift Not Implemented");
  }
  virtual AsaObject rshift(AsaObject o) {
    throw std::runtime_error("Rshift Not Implemented");
  }

  virtual AsaObject ceil() { throw std::runtime_error("Ceil Not Implemented"); }
  virtual AsaObject floor() { throw std::runtime_error("Floor Not Implemented"); }
  virtual AsaObject round() { throw std::runtime_error("Round Not Implemented"); }
  virtual AsaObject incr() { throw std::runtime_error("Incr Not Implemented"); }
  virtual AsaObject decr() { throw std::runtime_error("Decr Not Implemented"); }

  virtual AsaObject bitwise_or(AsaObject o) {
    throw std::runtime_error("Or Not Implemented");
  }
  virtual AsaObject bitwise_xor(AsaObject o) {
    throw std::runtime_error("Xor Not Implemented");
  }
  virtual AsaObject bitwise_and(AsaObject o) {
    throw std::runtime_error("And Not Implemented");
  }
  virtual AsaObject bitwise_not() {
    throw std::runtime_error("Not Not Implemented");
  }

  virtual AsaObject cmp(AsaObject o) {
    throw std::runtime_error("Cmp Not Implemented");
  }

  // virtual AsaObject to_int() { throw std::runtime_error("Not Implemented"); }
  // virtual AsaObject to_bigint() { throw std::runtime_error("Not Implemented"); }
  // virtual AsaObject to_float() { throw std::runtime_error("Not Implemented"); }
  // virtual AsaObject to_double() { throw std::runtime_error("Not Implemented"); }
  // virtual AsaObject to_bigdouble() { throw std::runtime_error("Not Implemented"); }
};

class AsaError : public AsaObject {
public:
  AsaError(Error err, std::string msg) : AsaObject(err, msg) {}
};

// TODO: convert to separate error classes and add value of label, variable id
// etc..
const AsaError OkError = AsaError(Ok, "No error, everything is fine! :)");
const AsaError StackOverflowError =
    AsaError(StackOverflow, "Stack reached its limit");
const AsaError StackUnderflowError =
    AsaError(StackUnderflow, "Cannot pop from empty stack");
const AsaError LabelNotFoundError = AsaError(LabelNotFound, "Label not found");
const AsaError DivByZeroError =
    AsaError(DivByZero, "Division by Zero encountered");
const AsaError IllegalInstructionError =
    AsaError(IllegalInstruction, "Illegal instruction encountered");
const AsaError UndefinedVariableError =
    AsaError(UndefinedVariable, "Undefined variable");

class AsaInteger;
class AsaFloat;
class AsaDouble;
class AsaString;
class AsaChar;
class AsaBigInteger;
class AsaBigDouble;
