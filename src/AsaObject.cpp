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

AsaObject AsaObject::to_int() { return AsaInteger(stoi(str())); }
AsaObject AsaObject::to_bigint() { return AsaBigInteger(stoll(str())); }
AsaObject AsaObject::to_float() { return AsaFloat(stof(str())); }
AsaObject AsaObject::to_double() { return AsaDouble(stod(str())); }
AsaObject AsaObject::to_bigdouble() { return AsaBigDouble(stold(str())); }

AsaObject AsaObject::add(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).add(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).add(o);

  case asa::Float:
    return AsaFloat(stof(str())).add(o);

  case asa::Double:
    return AsaDouble(stod(str())).add(o);

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).add(o);

  case asa::String:
    return AsaString(str()).add(o);

  default:
    throw runtime_error("add not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::sub(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).sub(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).sub(o);

  case asa::Float:
    return AsaFloat(stof(str())).sub(o);

  case asa::Double:
    return AsaDouble(stod(str())).sub(o);

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).sub(o);

  default:
    throw runtime_error("sub not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::mul(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).mul(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).mul(o);

  case asa::Float:
    return AsaFloat(stof(str())).mul(o);

  case asa::Double:
    return AsaDouble(stod(str())).mul(o);

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).mul(o);

  default:
    throw runtime_error("mul not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::div(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).div(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).div(o);

  case asa::Float:
    return AsaFloat(stof(str())).div(o);

  case asa::Double:
    return AsaDouble(stod(str())).div(o);

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).div(o);

  default:
    throw runtime_error("div not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::lshift(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).lshift(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).lshift(o);

  default:
    throw runtime_error("lshift not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::rshift(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).rshift(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).rshift(o);

  default:
    throw runtime_error("rshift not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_or(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).bitwise_or(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).bitwise_or(o);

  default:
    throw runtime_error("bitwise_or not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_and(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).bitwise_and(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).bitwise_and(o);

  default:
    throw runtime_error("bitwise_and not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_xor(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).bitwise_xor(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).bitwise_xor(o);

  default:
    throw runtime_error("bitwise_xor not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::bitwise_not() {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).bitwise_not();

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).bitwise_not();

  default:
    throw runtime_error("bitwise_not not supported for type: " +
                        type_to_str(type));
  }
}

AsaObject AsaObject::ceil() {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).ceil();

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).ceil();

  case asa::Float:
    return AsaFloat(stof(str())).ceil();

  case asa::Double:
    return AsaDouble(stod(str())).ceil();

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).ceil();

  default:
    throw runtime_error("ceil not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::floor() {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).floor();

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).floor();

  case asa::Float:
    return AsaFloat(stof(str())).floor();

  case asa::Double:
    return AsaDouble(stod(str())).floor();

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).floor();

  default:
    throw runtime_error("floor not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::round() {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).round();

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).round();

  case asa::Float:
    return AsaFloat(stof(str())).round();

  case asa::Double:
    return AsaDouble(stod(str())).round();

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).round();

  default:
    throw runtime_error("round not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::incr() {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).incr();

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).incr();

  case asa::Float:
    return AsaFloat(stof(str())).incr();

  case asa::Double:
    return AsaDouble(stod(str())).incr();

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).incr();

  default:
    throw runtime_error("incr not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::decr() {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).decr();

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).decr();

  case asa::Float:
    return AsaFloat(stof(str())).decr();

  case asa::Double:
    return AsaDouble(stod(str())).decr();

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).decr();

  default:
    throw runtime_error("decr not supported for type: " + type_to_str(type));
  }
}

AsaObject AsaObject::cmp(AsaObject o) {
  switch (type) {
  case asa::Integer:
    return AsaInteger(stoi(str())).cmp(o);

  case asa::BigInteger:
    return AsaBigInteger(stoll(str())).cmp(o);

  case asa::Float:
    return AsaFloat(stof(str())).cmp(o);

  case asa::Double:
    return AsaDouble(stod(str())).cmp(o);

  case asa::BigDouble:
    return AsaBigDouble(stold(str())).cmp(o);

  case asa::String:
    return AsaString(str()).cmp(o);

  default:
    throw runtime_error("cmp not supported for type: " + type_to_str(type));
  }
}
