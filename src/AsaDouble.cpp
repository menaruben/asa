#include "AsaDouble.hpp"
#include "AsaObject.hpp"
#include "AsaInteger.hpp"
#include <cmath>
#include <string>

AsaDouble::AsaDouble(double val)
    : AsaObject(std::to_string(val), Double), double_value(val) {}

double AsaDouble::get_value() const { return double_value; }
void AsaDouble::set_value(double v) { double_value = v; }
std::string AsaDouble::str() const { return std::to_string(double_value); }

AsaObject AsaDouble::add(AsaObject o) {
  return AsaDouble(double_value + stod(o.str()));
}

AsaObject AsaDouble::sub(AsaObject o) {
  return AsaDouble(double_value - stod(o.str()));
}

AsaObject AsaDouble::mul(AsaObject o) {
  return AsaDouble(double_value * stod(o.str()));
}

AsaObject AsaDouble::div(AsaObject o) {
  return AsaDouble(double_value / stod(o.str()));
}

AsaObject AsaDouble::ceil() { return AsaDouble(std::ceil(double_value)); }
AsaObject AsaDouble::floor() { return AsaDouble(std::floor(double_value)); }
AsaObject AsaDouble::round() { return AsaDouble(std::round(double_value)); }

AsaObject AsaDouble::incr() { return AsaDouble(double_value + 1); }
AsaObject AsaDouble::decr() { return AsaDouble(double_value - 1); }

AsaObject AsaDouble::cmp(AsaObject o) {
  if (double_value < stod(o.str()))  return AsaInteger(-1);
  if (double_value == stod(o.str())) return AsaInteger(0);
  return AsaInteger(1);
}
