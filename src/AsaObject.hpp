#pragma once

#include "objects.hpp"
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
  virtual AsaObject add(AsaObject o);
  virtual AsaObject sub(AsaObject o);
  virtual AsaObject mul(AsaObject o);
  virtual AsaObject div(AsaObject o);
  virtual AsaObject lshift(AsaObject o);
  virtual AsaObject rshift(AsaObject o);
  virtual AsaObject bitwise_or(AsaObject o);
  virtual AsaObject bitwise_xor(AsaObject o);
  virtual AsaObject bitwise_and(AsaObject o);
  virtual AsaObject bitwise_not();
  virtual AsaObject ceil();
  virtual AsaObject floor();
  virtual AsaObject round();
  virtual AsaObject incr();
  virtual AsaObject decr();
  virtual AsaObject cmp(AsaObject o);
};

class AsaInteger;
class AsaFloat;
class AsaDouble;
class AsaString;
class AsaChar;
class AsaBigInteger;
class AsaBigDouble;
