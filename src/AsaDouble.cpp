#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include <cmath>

AsaDouble::AsaDouble(double val)
    : AsaObject(std::to_string(val), Double), double_value(val) {}

double AsaDouble::get_value() const { return double_value; }
void AsaDouble::set_value(double v) { double_value = v; }
std::string AsaDouble::str() const { return std::to_string(double_value); }

AsaString AsaDouble::add(AsaString o) {
  return AsaString(str() + o.get_value());
}
AsaDouble AsaDouble::add(AsaInteger o) {
  return AsaDouble(double_value + o.get_value());
}
AsaDouble AsaDouble::add(AsaFloat o) {
  return AsaDouble(double_value + o.get_value());
}
AsaDouble AsaDouble::add(AsaDouble o) {
  return AsaDouble(double_value + o.get_value());
}

AsaDouble AsaDouble::sub(AsaInteger o) {
  return AsaDouble(double_value - o.get_value());
}
AsaDouble AsaDouble::sub(AsaFloat o) {
  return AsaDouble(double_value - o.get_value());
}
AsaDouble AsaDouble::sub(AsaDouble o) {
  return AsaDouble(double_value - o.get_value());
}

AsaDouble AsaDouble::mul(AsaInteger o) {
  return AsaDouble(double_value * o.get_value());
}
AsaDouble AsaDouble::mul(AsaFloat o) {
  return AsaDouble(double_value * o.get_value());
}
AsaDouble AsaDouble::mul(AsaDouble o) {
  return AsaDouble(double_value * o.get_value());
}

AsaDouble AsaDouble::div(AsaInteger o) {
  return AsaDouble(double_value / o.get_value());
}
AsaDouble AsaDouble::div(AsaFloat o) {
  return AsaDouble(double_value / o.get_value());
}
AsaDouble AsaDouble::div(AsaDouble o) {
  return AsaDouble(double_value / o.get_value());
}

AsaDouble AsaDouble::ceil() { return AsaDouble(std::ceil(double_value)); }
AsaDouble AsaDouble::floor() { return AsaDouble(std::floor(double_value)); }
AsaDouble AsaDouble::round() { return AsaDouble(std::round(double_value)); }

AsaDouble AsaDouble::incr() { return AsaDouble(double_value + 1); }
AsaDouble AsaDouble::decr() { return AsaDouble(double_value - 1); }

AsaInteger AsaDouble::cmp(AsaInteger o) {
  if (double_value < o.get_value())
    return AsaInteger(-1);
  if (double_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}

AsaInteger AsaDouble::cmp(AsaFloat o) {
  if (double_value < o.get_value())
    return AsaInteger(-1);
  if (double_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}

AsaInteger AsaDouble::cmp(AsaDouble o) {
  if (double_value < o.get_value())
    return AsaInteger(-1);
  if (double_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}
