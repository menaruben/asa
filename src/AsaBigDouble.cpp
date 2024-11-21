#include "AsaBigDouble.hpp"
#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include <cmath>
#include <string>

AsaBigDouble::AsaBigDouble(long double val)
    : AsaObject(std::to_string(val), Double), double_value(val) {}

double AsaBigDouble::get_value() const { return double_value; }
void AsaBigDouble::set_value(double v) { double_value = v; }
std::string AsaBigDouble::str() const { return std::to_string(double_value); }

AsaObject AsaBigDouble::add(AsaObject o) {
  return AsaBigDouble(double_value + (long double)stold(o.str()));
}

AsaObject AsaBigDouble::sub(AsaObject o) {
  return AsaBigDouble(double_value - (long double)stold(o.str()));
}

AsaObject AsaBigDouble::mul(AsaObject o) {
  return AsaBigDouble(double_value * (long double)stold(o.str()));
}

AsaObject AsaBigDouble::div(AsaObject o) {
  return AsaBigDouble(double_value / (long double)stold(o.str()));
}

AsaObject AsaBigDouble::ceil() { return AsaBigDouble(std::ceil(double_value)); }
AsaObject AsaBigDouble::floor() {
  return AsaBigDouble(std::floor(double_value));
}
AsaObject AsaBigDouble::round() {
  return AsaBigDouble(std::round(double_value));
}

AsaObject AsaBigDouble::incr() { return AsaBigDouble(double_value + 1); }
AsaObject AsaBigDouble::decr() { return AsaBigDouble(double_value - 1); }

AsaObject AsaBigDouble::cmp(AsaObject o) {
  if (double_value < stold(o.str()))
    return AsaInteger(-1);
  if (double_value == stold(o.str()))
    return AsaInteger(0);
  return AsaInteger(1);
}
