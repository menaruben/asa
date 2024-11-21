#pragma once

#include "AsaObject.hpp"
#include <string>

// Forward declarations
class AsaInteger;
class AsaFloat;
class AsaString;

class AsaBigDouble : public AsaObject {
private:
  long double double_value;

public:
  AsaBigDouble(long double val);

  double get_value() const;
  void set_value(double v);
  std::string str() const;

  AsaObject add(AsaObject o);
  AsaObject sub(AsaObject o);
  AsaObject mul(AsaObject o);
  AsaObject div(AsaObject o);

  AsaObject ceil();
  AsaObject floor();
  AsaObject round();

  AsaObject incr();
  AsaObject decr();

  AsaObject cmp(AsaObject o);
};
