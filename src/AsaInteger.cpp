#include "AsaInteger.hpp"
#include "AsaBigDouble.hpp"
#include "AsaBigInteger.hpp"
#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include "AsaObject.hpp"
#include "AsaString.hpp"
#include "objects.hpp"
#include <stdexcept>
#include <string>
#include "AsaTypeConverter.hpp"

AsaInteger::AsaInteger(int val)
    : AsaObject(std::to_string(val), Integer), int_value(val) {}

int AsaInteger::get_value() const { return int_value; }

void AsaInteger::set_value(int v) { int_value = v; }

std::string AsaInteger::str() const { return std::to_string(int_value); }

AsaObject AsaInteger::add(AsaObject o) {
  switch (o.get_type()) {
  case asa::String: {
    return AsaString(str() + o.str());
  }

  case asa::Integer:
    return AsaInteger(int_value + to_int(o.str(), o.get_type()).get_value());

  case asa::BigInteger:
    return AsaBigInteger(int_value + to_bigint(o.str(), o.get_type()).get_value());

  case asa::Float:
    return AsaFloat(int_value + to_float(o.str(), o.get_type()).get_value());

  case asa::Double:
    return AsaDouble(int_value + to_double(o.str(), o.get_type()).get_value());

  case asa::BigDouble:
    return AsaBigDouble(int_value + to_bigdouble(o.str(), o.get_type()).get_value());

  default:
    throw runtime_error("Add not supported for Integer and " +
                        type_to_str(o.get_type()));
  }
}

AsaObject AsaInteger::sub(AsaObject o) {
  switch (o.get_type()) {
  case asa::Integer:
    return AsaInteger(int_value - to_int(o.str(), o.get_type()).get_value());

  case asa::BigInteger:
    return AsaBigInteger(int_value - to_bigint(o.str(), o.get_type()).get_value());

  case asa::Float:
    return AsaFloat(int_value - to_float(o.str(), o.get_type()).get_value());

  case asa::Double:
    return AsaDouble(int_value - to_double(o.str(), o.get_type()).get_value());

  case asa::BigDouble:
    return AsaBigDouble(int_value - to_bigdouble(o.str(), o.get_type()).get_value());

  default:
    throw runtime_error("Sub not supported for Integer and " +
                        type_to_str(o.get_type()));
  }
}

AsaObject AsaInteger::mul(AsaObject o) {
  
  switch (o.get_type()) {
  case asa::Integer:
    return AsaInteger(int_value * to_int(o.str(), o.get_type()).get_value());

  case asa::BigInteger:
    return AsaBigInteger(int_value * to_bigint(o.str(), o.get_type()).get_value());

  case asa::Float:
    return AsaFloat(int_value * to_float(o.str(), o.get_type()).get_value());

  case asa::Double:
    return AsaDouble(int_value * to_double(o.str(), o.get_type()).get_value());

  case asa::BigDouble:
    return AsaBigDouble(int_value * to_bigdouble(o.str(), o.get_type()).get_value());

  default:
    throw runtime_error("Mul not supported for Integer and " +
                        type_to_str(o.get_type()));
  }
}

AsaObject AsaInteger::div(AsaObject o) {
  switch (o.get_type()) {
  case asa::Integer:
    return AsaInteger(int_value / to_int(o.str(), o.get_type()).get_value());

  case asa::BigInteger:
    return AsaBigInteger(int_value / to_bigint(o.str(), o.get_type()).get_value());

  case asa::Float:
    return AsaFloat(int_value / to_float(o.str(), o.get_type()).get_value());

  case asa::Double:
    return AsaDouble(int_value / to_double(o.str(), o.get_type()).get_value());

  case asa::BigDouble:
    return AsaBigDouble(int_value / to_bigdouble(o.str(), o.get_type()).get_value());

  default:
    throw runtime_error("Div not supported for Integer and " +
                        type_to_str(o.get_type()));
  }
}

AsaObject AsaInteger::lshift(AsaObject o) {
  return AsaInteger(int_value << to_int(o.str(), o.get_type()).get_value());
}
AsaObject AsaInteger::rshift(AsaObject o) {
  return AsaInteger(int_value >> to_int(o.str(), o.get_type()).get_value());
}

AsaObject AsaInteger::bitwise_or(AsaObject o) {
  return AsaInteger(int_value | to_int(o.str(), o.get_type()).get_value());
}
AsaObject AsaInteger::bitwise_xor(AsaObject o) {
  return AsaInteger(int_value ^ to_int(o.str(), o.get_type()).get_value());
}
AsaObject AsaInteger::bitwise_and(AsaObject o) {
  return AsaInteger(int_value & to_int(o.str(), o.get_type()).get_value());
}

AsaObject AsaInteger::bitwise_not() { return AsaInteger(~int_value); }

AsaObject AsaInteger::ceil() { return AsaInteger(int_value); }
AsaObject AsaInteger::floor() { return AsaInteger(int_value); }
AsaObject AsaInteger::round() { return AsaInteger(int_value); }

AsaObject AsaInteger::incr() { return AsaInteger(int_value + 1); }
AsaObject AsaInteger::decr() { return AsaInteger(int_value - 1); }

AsaObject AsaInteger::cmp(AsaObject o) {
  if (int_value < to_int(o.str(), o.get_type()).get_value())
    return AsaInteger(-1);
  if (int_value == to_int(o.str(), o.get_type()).get_value())
    return AsaInteger(0);
  return AsaInteger(1);
}
