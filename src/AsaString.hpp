#pragma once
#include "AsaObject.hpp"
#include "AsaInteger.hpp"

using namespace asa;

class AsaString : public AsaObject {
private:
  string str_value;

public:
  AsaString(string val) : AsaObject(val, String), str_value(val) {}

  string get_value() const { return str_value; }
  void set_value(string val) { str_value = val; }

  AsaString add(AsaObject o) {
    string val = str_value + o.str();
    return AsaString(val);
  }

  AsaInteger cmp(AsaString o) {
    if (str_value < o.get_value()) return AsaInteger(-1);
    if (str_value == o.get_value()) return AsaInteger(0);
    return AsaInteger(1);
  }
};
