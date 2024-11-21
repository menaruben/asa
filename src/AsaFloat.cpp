#include "AsaFloat.hpp"
#include <cmath>

AsaFloat::AsaFloat(float val)
    : AsaObject(std::to_string(val), Float), float_value(val) {}

float AsaFloat::get_value() const { return float_value; }
void AsaFloat::set_value(float v) { float_value = v; }
std::string AsaFloat::str() const { return std::to_string(float_value); }

AsaString AsaFloat::add(AsaString o) {
  return AsaString(str() + o.get_value());
}
AsaFloat AsaFloat::add(AsaInteger o) {
  return AsaFloat(float_value + o.get_value());
}
AsaFloat AsaFloat::add(AsaFloat o) {
  return AsaFloat(float_value + o.get_value());
}
AsaDouble AsaFloat::add(AsaDouble o) {
  return AsaDouble(float_value + o.get_value());
}

AsaFloat AsaFloat::sub(AsaInteger o) {
  return AsaFloat(float_value - o.get_value());
}
AsaFloat AsaFloat::sub(AsaFloat o) {
  return AsaFloat(float_value - o.get_value());
}
AsaDouble AsaFloat::sub(AsaDouble o) {
  return AsaDouble(float_value - o.get_value());
}

AsaFloat AsaFloat::mul(AsaInteger o) {
  return AsaFloat(float_value * o.get_value());
}
AsaFloat AsaFloat::mul(AsaFloat o) {
  return AsaFloat(float_value * o.get_value());
}
AsaDouble AsaFloat::mul(AsaDouble o) {
  return AsaDouble(float_value * o.get_value());
}

AsaFloat AsaFloat::div(AsaInteger o) {
  return AsaFloat(float_value / o.get_value());
}
AsaFloat AsaFloat::div(AsaFloat o) {
  return AsaFloat(float_value / o.get_value());
}
AsaDouble AsaFloat::div(AsaDouble o) {
  return AsaDouble(float_value / o.get_value());
}

AsaFloat AsaFloat::ceil() { return AsaFloat(std::ceil(float_value)); }
AsaFloat AsaFloat::floor() { return AsaFloat(std::floor(float_value)); }
AsaFloat AsaFloat::round() { return AsaFloat(std::round(float_value)); }

AsaFloat AsaFloat::incr() { return AsaFloat(float_value + 1); }
AsaFloat AsaFloat::decr() { return AsaFloat(float_value - 1); }

AsaInteger AsaFloat::cmp(AsaInteger o) {
  if (float_value < o.get_value())
    return AsaInteger(-1);
  if (float_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}
AsaInteger AsaFloat::cmp(AsaFloat o) {
  if (float_value < o.get_value())
    return AsaInteger(-1);
  if (float_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}
AsaInteger AsaFloat::cmp(AsaDouble o) {
  if (float_value < o.get_value())
    return AsaInteger(-1);
  if (float_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}
