#include "AsaBigInteger.hpp"
#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include <string>
#include "AsaTypeConverter.hpp"

AsaBigInteger::AsaBigInteger(long long int val)
    : AsaObject(std::to_string(val), Integer), int_value(val) {}

int AsaBigInteger::get_value() const { return int_value; }

void AsaBigInteger::set_value(int v) { int_value = v; }

std::string AsaBigInteger::str() const { return std::to_string(int_value); }

AsaObject AsaBigInteger::add(AsaObject o) {
  return AsaBigInteger(int_value + to_bigint(o.str(), o.get_type()).get_value());
}

AsaObject AsaBigInteger::sub(AsaObject o) {
  return AsaBigInteger(int_value - to_bigint(o.str(), o.get_type()).get_value());
}

AsaObject AsaBigInteger::mul(AsaObject o) {
  return AsaBigInteger(int_value * to_bigint(o.str(), o.get_type()).get_value());
}

AsaObject AsaBigInteger::div(AsaObject o) {
  return AsaBigInteger(int_value / to_bigint(o.str(), o.get_type()).get_value());
}

AsaObject AsaBigInteger::lshift(AsaObject o) {
  return AsaBigInteger(int_value << to_bigint(o.str(), o.get_type()).get_value());
}
AsaObject AsaBigInteger::rshift(AsaObject o) {
  return AsaBigInteger(int_value >> to_bigint(o.str(), o.get_type()).get_value());
}

AsaObject AsaBigInteger::bitwise_or(AsaObject o) {
  return AsaBigInteger(int_value | to_bigint(o.str(), o.get_type()).get_value());
}
AsaObject AsaBigInteger::bitwise_xor(AsaObject o) {
  return AsaBigInteger(int_value ^ to_bigint(o.str(), o.get_type()).get_value());
}
AsaObject AsaBigInteger::bitwise_and(AsaObject o) {
  return AsaBigInteger(int_value & to_bigint(o.str(), o.get_type()).get_value());
}

AsaObject AsaBigInteger::bitwise_not() { return AsaBigInteger(~int_value); }

AsaObject AsaBigInteger::ceil() { return AsaBigInteger(int_value); }
AsaObject AsaBigInteger::floor() { return AsaBigInteger(int_value); }
AsaObject AsaBigInteger::round() { return AsaBigInteger(int_value); }

AsaObject AsaBigInteger::incr() { return AsaBigInteger(int_value + 1); }
AsaObject AsaBigInteger::decr() { return AsaBigInteger(int_value - 1); }

AsaObject AsaBigInteger::cmp(AsaObject o) {
  if (int_value < to_bigint(o.str(), o.get_type()).get_value())
    return AsaInteger(-1);
  if (int_value == to_bigint(o.str(), o.get_type()).get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}
