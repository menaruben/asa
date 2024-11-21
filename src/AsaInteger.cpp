#include "AsaInteger.hpp"
#include <string>

AsaInteger::AsaInteger(int val)
    : AsaObject(std::to_string(val), Integer), int_value(val) {}

int AsaInteger::get_value() const { return int_value; }
void AsaInteger::set_value(int v) { int_value = v; }
std::string AsaInteger::str() const { return std::to_string(int_value); }

AsaString AsaInteger::add(AsaString o) {
  return AsaString(str() + o.get_value());
}
AsaInteger AsaInteger::add(AsaInteger o) {
  return AsaInteger(int_value + o.get_value());
}
AsaFloat AsaInteger::add(AsaFloat o) {
  return AsaFloat(int_value + o.get_value());
}
AsaDouble AsaInteger::add(AsaDouble o) {
  return AsaDouble(int_value + o.get_value());
}

AsaInteger AsaInteger::sub(AsaInteger o) {
  return AsaInteger(int_value - o.get_value());
}
AsaFloat AsaInteger::sub(AsaFloat o) {
  return AsaFloat(int_value - o.get_value());
}
AsaDouble AsaInteger::sub(AsaDouble o) {
  return AsaDouble(int_value - o.get_value());
}

AsaInteger AsaInteger::mul(AsaInteger o) {
  return AsaInteger(int_value * o.get_value());
}
AsaFloat AsaInteger::mul(AsaFloat o) {
  return AsaFloat(int_value * o.get_value());
}
AsaDouble AsaInteger::mul(AsaDouble o) {
  return AsaDouble(int_value * o.get_value());
}

AsaInteger AsaInteger::div(AsaInteger o) {
  return AsaInteger(int_value / o.get_value());
}
AsaFloat AsaInteger::div(AsaFloat o) {
  return AsaFloat(int_value / o.get_value());
}
AsaDouble AsaInteger::div(AsaDouble o) {
  return AsaDouble(int_value / o.get_value());
}

AsaInteger AsaInteger::lshift(AsaInteger o) {
  return AsaInteger(int_value << o.get_value());
}
AsaInteger AsaInteger::rshift(AsaInteger o) {
  return AsaInteger(int_value >> o.get_value());
}

AsaInteger AsaInteger::bitwise_or(AsaInteger o) {
  return AsaInteger(int_value | o.get_value());
}
AsaInteger AsaInteger::bitwise_xor(AsaInteger o) {
  return AsaInteger(int_value ^ o.get_value());
}
AsaInteger AsaInteger::bitwise_and(AsaInteger o) {
  return AsaInteger(int_value & o.get_value());
}
AsaInteger AsaInteger::bitwise_not() { return AsaInteger(~int_value); }

AsaInteger AsaInteger::ceil() { return AsaInteger(int_value); }
AsaInteger AsaInteger::floor() { return AsaInteger(int_value); }
AsaInteger AsaInteger::round() { return AsaInteger(int_value); }

AsaInteger AsaInteger::incr() { return AsaInteger(int_value + 1); }
AsaInteger AsaInteger::decr() { return AsaInteger(int_value - 1); }

AsaInteger AsaInteger::cmp(AsaInteger o) {
  if (int_value < o.get_value())
    return AsaInteger(-1);
  if (int_value == o.get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}

AsaInteger AsaInteger::cmp(AsaFloat o) {
  if (int_value < o.get_value())  return AsaInteger(-1);
  if (int_value == o.get_value()) return AsaInteger(0);
  return AsaInteger(1);
}

AsaInteger AsaInteger::cmp(AsaDouble o) {
  if (int_value < o.get_value())  return AsaInteger(-1);
  if (int_value == o.get_value()) return AsaInteger(0);
  return AsaInteger(1);
}
