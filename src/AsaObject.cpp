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
    return to_int(*this).add(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).add(to_bigint(o));

  case asa::Float:
    return to_float(*this).add(to_float(o));

  case asa::Double:
    return to_double(*this).add(to_double(o));

  case asa::BigDouble:
    return to_bigdouble(*this).add(to_bigdouble(o));

  case asa::String:
    return AsaString(str()).add(o);

  default:
    throw runtime_error("add not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::sub(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).sub(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).sub(to_bigint(o));

  case asa::Float:
    return to_float(*this).sub(to_float(o));

  case asa::Double:
    return to_double(*this).sub(to_double(o));

  case asa::BigDouble:
    return to_bigdouble(*this).sub(to_bigdouble(o));

  default:
    throw runtime_error("sub not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::mul(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).mul(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).mul(to_bigint(o));

  case asa::Float:
    return to_float(*this).mul(to_float(o));

  case asa::Double:
    return to_double(*this).mul(to_double(o));

  case asa::BigDouble:
    return to_bigdouble(*this).mul(to_bigdouble(o));

  default:
    throw runtime_error("mul not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::div(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).div(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).div(to_bigint(o));

  case asa::Float:
    return to_float(*this).div(to_float(o));

  case asa::Double:
    return to_double(*this).div(to_double(o));

  case asa::BigDouble:
    return to_bigdouble(*this).div(to_bigdouble(o));

  default:
    throw runtime_error("div not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::lshift(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).lshift(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).lshift(to_bigint(o));

  default:
    throw runtime_error("lshift not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::rshift(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).rshift(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).rshift(to_bigint(o));

  default:
    throw runtime_error("rshift not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_or(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).bitwise_or(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).bitwise_or(to_bigint(o));

  default:
    throw runtime_error("bitwise_or not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_and(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).bitwise_and(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).bitwise_and(to_bigint(o));

  default:
    throw runtime_error("bitwise_and not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_xor(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).bitwise_xor(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).bitwise_xor(to_bigint(o));

  default:
    throw runtime_error("bitwise_xor not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_not() {
  switch (type) {
  case asa::Integer:
    return to_int(*this).bitwise_not();

  case asa::BigInteger:
    return to_bigint(*this).bitwise_not();

  default:
    throw runtime_error("bitwise_not not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::ceil() {
  switch (type) {
  case asa::Integer:
    return to_int(*this).ceil();

  case asa::BigInteger:
    return to_bigint(*this).ceil();

  case asa::Float:
    return to_float(*this).ceil();

  case asa::Double:
    return to_double(*this).ceil();

  case asa::BigDouble:
    return to_bigdouble(*this).ceil();

  default:
    throw runtime_error("ceil not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::floor() {
  switch (type) {
  case asa::Integer:
    return to_int(*this).floor();

  case asa::BigInteger:
    return to_bigint(*this).floor();

  case asa::Float:
    return to_float(*this).floor();

  case asa::Double:
    return to_double(*this).floor();

  case asa::BigDouble:
    return to_bigdouble(*this).floor();

  default:
    throw runtime_error("floor not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::round() {
  switch (type) {
  case asa::Integer:
    return to_int(*this).round();

  case asa::BigInteger:
    return to_bigint(*this).round();

  case asa::Float:
    return to_float(*this).round();

  case asa::Double:
    return to_double(*this).round();

  case asa::BigDouble:
    return to_bigdouble(*this).round();

  default:
    throw runtime_error("round not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::incr() {
  switch (type) {
  case asa::Integer:
    return to_int(*this).incr();

  case asa::BigInteger:
    return to_bigint(*this).incr();

  case asa::Float:
    return to_float(*this).incr();

  case asa::Double:
    return to_double(*this).incr();

  case asa::BigDouble:
    return to_bigdouble(*this).incr();

  default:
    throw runtime_error("incr not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::decr() {
  switch (type) {
  case asa::Integer:
    return to_int(*this).decr();

  case asa::BigInteger:
    return to_bigint(*this).decr();

  case asa::Float:
    return to_float(*this).decr();

  case asa::Double:
    return to_double(*this).decr();

  case asa::BigDouble:
    return to_bigdouble(*this).decr();

  default:
    throw runtime_error("decr not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::cmp(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return to_int(*this).cmp(to_int(o));

  case asa::BigInteger:
    return to_bigint(*this).cmp(to_bigint(o));

  case asa::Float:
    return to_float(*this).cmp(to_float(o));

  case asa::Double:
    return to_double(*this).cmp(to_double(o));

  case asa::BigDouble:
    return to_bigdouble(*this).cmp(to_bigdouble(o));

  case asa::String:
    return AsaString(str()).cmp(o);

  default:
    throw runtime_error("cmp not supported for type: " + type_to_str(type));
  }
}
