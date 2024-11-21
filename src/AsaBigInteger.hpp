#pragma once

#include "AsaObject.hpp"
#include <string>

class AsaBigInteger : public AsaObject {
private:
  long long int int_value;

public:
  AsaBigInteger(long long int val);

  int get_value() const;
  void set_value(int v);
  std::string str() const;

  AsaObject add(AsaObject o);
  AsaObject sub(AsaObject o);
  AsaObject mul(AsaObject o);
  AsaObject div(AsaObject o);
  AsaObject lshift(AsaObject o);
  AsaObject rshift(AsaObject o);

  AsaObject bitwise_or(AsaObject o);
  AsaObject bitwise_xor(AsaObject o);
  AsaObject bitwise_and(AsaObject o);
  AsaObject bitwise_not();

  AsaObject ceil();
  AsaObject floor();
  AsaObject round();

  AsaObject incr();
  AsaObject decr();

  AsaObject cmp(AsaObject o);
};
