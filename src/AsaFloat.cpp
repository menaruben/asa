#include "AsaFloat.hpp"
#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include <cmath>

AsaFloat::AsaFloat(float val)
    : AsaObject(std::to_string(val), Float), float_value(val) {}

float AsaFloat::get_value() const { return float_value; }
void AsaFloat::set_value(float v) { float_value = v; }
std::string AsaFloat::str() const { return std::to_string(float_value); }

AsaObject AsaFloat::add(AsaObject o) {
  return AsaFloat(float_value + stof(o.str()));
}

AsaObject AsaFloat::sub(AsaObject o) {
  return AsaFloat(float_value - stof(o.str()));
}

AsaObject AsaFloat::mul(AsaObject o) {
  return AsaFloat(float_value * stof(o.str()));
}

AsaObject AsaFloat::div(AsaObject o) {
  return AsaFloat(float_value / stof(o.str()));
}

AsaObject AsaFloat::ceil() { return AsaFloat(std::ceil(float_value)); }
AsaObject AsaFloat::floor() { return AsaFloat(std::floor(float_value)); }
AsaObject AsaFloat::round() { return AsaFloat(std::round(float_value)); }

AsaObject AsaFloat::incr() { return AsaFloat(float_value + 1); }
AsaObject AsaFloat::decr() { return AsaFloat(float_value - 1); }

AsaObject AsaFloat::cmp(AsaObject o) {
  if (float_value < stof(o.str()))  return AsaInteger(-1);
  if (float_value == stof(o.str())) return AsaInteger(0);
  return AsaInteger(1);
}
