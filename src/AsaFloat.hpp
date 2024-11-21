#pragma once

#include "AsaDouble.hpp"
#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include "AsaString.hpp"
#include <string>

using namespace asa;

class AsaFloat : public AsaObject {
private:
  float float_value;

public:
  AsaFloat(float val);

  float get_value() const;
  void set_value(float v);
  std::string str() const;

  AsaString add(AsaString o);
  AsaFloat add(AsaInteger o);
  AsaFloat add(AsaFloat o);
  AsaDouble add(AsaDouble o);

  AsaFloat sub(AsaInteger o);
  AsaFloat sub(AsaFloat o);
  AsaDouble sub(AsaDouble o);

  AsaFloat mul(AsaInteger o);
  AsaFloat mul(AsaFloat o);
  AsaDouble mul(AsaDouble o);

  AsaFloat div(AsaInteger o);
  AsaFloat div(AsaFloat o);
  AsaDouble div(AsaDouble o);

  AsaFloat ceil();
  AsaFloat floor();
  AsaFloat round();

  AsaFloat incr();
  AsaFloat decr();

  AsaInteger cmp(AsaInteger o);
  AsaInteger cmp(AsaFloat o);
  AsaInteger cmp(AsaDouble o);
};
