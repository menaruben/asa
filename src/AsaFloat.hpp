#pragma once

#include "AsaObject.hpp"
#include <string>

// Forward declarations
class AsaInteger;
class AsaDouble;
class AsaString;

class AsaFloat : public AsaObject {
private:
  float float_value;

public:
  AsaFloat(float val);

  float get_value() const;
  void set_value(float v);
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
