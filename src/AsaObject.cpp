#include "AsaObject.hpp"
#include "AsaBigDouble.hpp"
#include "AsaBigInteger.hpp"
#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include "AsaInteger.hpp"
#include "AsaString.hpp"
#include "objects.hpp"
#include <stdexcept>
#include <string>
#include "AsaTypeConverter.hpp"

AsaObject AsaObject::add(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).add(to_int(o.str(), o.get_type()));
    
  case asa::BigInteger:
    return to_bigint(str(), type).add(to_bigint(o.str(), o.get_type()));

  case asa::Float:
    return to_float(str(), type).add(to_float(o.str(), o.get_type()));

  case asa::Double:
    return to_double(str(), type).add(to_double(o.str(), o.get_type()));

  case asa::BigDouble:
    return to_bigdouble(str(), type).add(to_bigdouble(o.str(), o.get_type()));

  case asa::String:
    return AsaString(str()).add(o);

  default:
    throw runtime_error("add not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::sub(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).sub(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).sub(to_bigint(o.str(), o.get_type()));

  case asa::Float:
    return to_float(o.str(), o.get_type()).sub(to_float(o.str(), o.get_type()));

  case asa::Double:
    return to_double(o.str(), o.get_type()).sub(to_double(o.str(), o.get_type()));

  case asa::BigDouble:
    return to_bigdouble(o.str(), o.get_type()).sub(to_bigdouble(o.str(), o.get_type()));

  default:
    throw runtime_error("sub not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::mul(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).mul(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).mul(to_bigint(o.str(), o.get_type()));

  case asa::Float:
    return to_float(o.str(), o.get_type()).mul(to_float(o.str(), o.get_type()));

  case asa::Double:
    return to_double(o.str(), o.get_type()).mul(to_double(o.str(), o.get_type()));

  case asa::BigDouble:
    return to_bigdouble(o.str(), o.get_type()).mul(to_bigdouble(o.str(), o.get_type()));

  default:
    throw runtime_error("mul not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::div(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).div(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).div(to_bigint(o.str(), o.get_type()));

  case asa::Float:
    return to_float(o.str(), o.get_type()).div(to_float(o.str(), o.get_type()));

  case asa::Double:
    return to_double(o.str(), o.get_type()).div(to_double(o.str(), o.get_type()));

  case asa::BigDouble:
    return to_bigdouble(o.str(), o.get_type()).div(to_bigdouble(o.str(), o.get_type()));

  default:
    throw runtime_error("div not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::lshift(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).lshift(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).lshift(to_bigint(o.str(), o.get_type()));

  default:
    throw runtime_error("lshift not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::rshift(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).rshift(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).rshift(to_bigint(o.str(), o.get_type()));

  default:
    throw runtime_error("rshift not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_or(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).bitwise_or(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).bitwise_or(to_bigint(o.str(), o.get_type()));

  default:
    throw runtime_error("bitwise_or not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_and(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).bitwise_and(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).bitwise_and(to_bigint(o.str(), o.get_type()));

  default:
    throw runtime_error("bitwise_and not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_xor(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).bitwise_xor(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).bitwise_xor(to_bigint(o.str(), o.get_type()));

  default:
    throw runtime_error("bitwise_xor not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_not() {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).bitwise_not();

  case asa::BigInteger:
    return to_bigint(str(), type).bitwise_not();

  default:
    throw runtime_error("bitwise_not not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::ceil() {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).ceil();

  case asa::BigInteger:
    return to_bigint(str(), type).ceil();

  case asa::Float:
    return to_float(str(), type).ceil();

  case asa::Double:
    return to_double(str(), type).ceil();

  case asa::BigDouble:
    return to_bigdouble(str(), type).ceil();

  default:
    throw runtime_error("ceil not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::floor() {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).floor();

  case asa::BigInteger:
    return to_bigint(str(), type).floor();

  case asa::Float:
    return to_float(str(), type).floor();

  case asa::Double:
    return to_double(str(), type).floor();

  case asa::BigDouble:
    return to_bigdouble(str(), type).floor();

  default:
    throw runtime_error("floor not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::round() {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).round();

  case asa::BigInteger:
    return to_bigint(str(), type).round();

  case asa::Float:
    return to_float(str(), type).round();

  case asa::Double:
    return to_double(str(), type).round();

  case asa::BigDouble:
    return to_bigdouble(str(), type).round();

  default:
    throw runtime_error("round not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::incr() {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).incr();

  case asa::BigInteger:
    return to_bigint(str(), type).incr();

  case asa::Float:
    return to_float(str(), type).incr();

  case asa::Double:
    return to_double(str(), type).incr();

  case asa::BigDouble:
    return to_bigdouble(str(), type).incr();

  default:
    throw runtime_error("incr not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::decr() {
  switch (type) {
  case asa::Integer:
    return to_int(str(), type).decr();

  case asa::BigInteger:
    return to_bigint(str(), type).decr();

  case asa::Float:
    return to_float(str(), type).decr();

  case asa::Double:
    return to_double(str(), type).decr();

  case asa::BigDouble:
    return to_bigdouble(str(), type).decr();

  default:
    throw runtime_error("decr not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::cmp(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(o.str(), o.get_type()).cmp(to_int(o.str(), o.get_type()));

  case asa::BigInteger:
    return to_bigint(o.str(), o.get_type()).cmp(to_bigint(o.str(), o.get_type()));

  case asa::Float:
    return to_float(o.str(), o.get_type()).cmp(to_float(o.str(), o.get_type()));

  case asa::Double:
    return to_double(o.str(), o.get_type()).cmp(to_double(o.str(), o.get_type()));

  case asa::BigDouble:
    return to_bigdouble(o.str(), o.get_type()).cmp(to_bigdouble(o.str(), o.get_type()));

  case asa::String:
    return AsaString(str()).cmp(o);

  default:
    throw runtime_error("cmp not supported for type: " + type_to_str(type));
  }
}
