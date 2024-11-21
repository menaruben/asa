#pragma once

#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include <string>

using namespace asa;

class AsaString : public AsaObject {
private:
  std::string str_value;

public:
  AsaString(std::string val);
  ~AsaString();

  std::string get_value() const;
  void set_value(std::string val);

  AsaObject add(AsaObject o);
  AsaInteger cmp(AsaString o);

  std::string str() const;
};
