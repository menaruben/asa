#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include <string>

AsaInteger::AsaInteger(int val)
    : AsaObject(std::to_string(val), Integer), int_value(val) {}

int AsaInteger::get_value() const { return int_value; }

void AsaInteger::set_value(int v) { int_value = v; }

std::string AsaInteger::str() const { return std::to_string(int_value); }

AsaObject AsaInteger::add(AsaObject o) {
  return AsaInteger(int_value + stoi(o.str()));
}

AsaObject AsaInteger::sub(AsaObject o) {
  return AsaInteger(int_value - stoi(o.str()));
}

AsaObject AsaInteger::mul(AsaObject o) {
  return AsaInteger(int_value * stoi(o.str()));
}

AsaObject AsaInteger::div(AsaObject o) {
  return AsaInteger(int_value / stoi(o.str()));
}

AsaObject AsaInteger::lshift(AsaObject o) {
  return AsaInteger(int_value << stoi(o.str()));
}
AsaObject AsaInteger::rshift(AsaObject o) {
  return AsaInteger(int_value >> stoi(o.str()));
}

AsaObject AsaInteger::bitwise_or(AsaObject o) {
  return AsaInteger(int_value | stoi(o.str()));
}
AsaObject AsaInteger::bitwise_xor(AsaObject o) {
  return AsaInteger(int_value ^ stoi(o.str()));
}
AsaObject AsaInteger::bitwise_and(AsaObject o) {
  return AsaInteger(int_value & stoi(o.str()));
}

AsaObject AsaInteger::bitwise_not() { return AsaInteger(~int_value); }

AsaObject AsaInteger::ceil() { return AsaInteger(int_value); }
AsaObject AsaInteger::floor() { return AsaInteger(int_value); }
AsaObject AsaInteger::round() { return AsaInteger(int_value); }

AsaObject AsaInteger::incr() { return AsaInteger(int_value + 1); }
AsaObject AsaInteger::decr() { return AsaInteger(int_value - 1); }

AsaObject AsaInteger::cmp(AsaObject o) {
  if (int_value < stoi(o.str()))  return AsaInteger(-1);
  if (int_value == stoi(o.str())) return AsaInteger(0);
  return AsaInteger(1);
}
