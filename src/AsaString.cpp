#include "AsaString.hpp"
#include "AsaInteger.hpp"

AsaString::AsaString(std::string val)
    : AsaObject(val, String), str_value(val) {}

AsaString::~AsaString() {}  // Add destructor definition

std::string AsaString::get_value() const { return str_value; }
void AsaString::set_value(std::string val) { str_value = val; }

AsaObject AsaString::add(AsaObject o) {
  std::string val = str_value + o.str();
  return AsaString(val);
}

AsaInteger AsaString::cmp(AsaString o) {
  if (str_value < o.get_value())  return AsaInteger(-1);
  if (str_value == o.get_value()) return AsaInteger(0);
  return AsaInteger(1);
}

std::string AsaString::str() const {  // Implement str method
  return str_value;
}
