#pragma once

#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include "AsaString.hpp"
#include <cmath>
#include <string>

using namespace asa;

class AsaDouble : public AsaObject {
private:
  double double_value;

public:
  AsaDouble(double val);

  double get_value() const;
  void set_value(double v);
  std::string str() const;

  AsaString add(AsaString o);
  AsaDouble add(AsaInteger o);
  AsaDouble add(AsaFloat o);
  AsaDouble add(AsaDouble o);

  AsaDouble sub(AsaInteger o);
  AsaDouble sub(AsaFloat o);
  AsaDouble sub(AsaDouble o);

  AsaDouble mul(AsaInteger o);
  AsaDouble mul(AsaFloat o);
  AsaDouble mul(AsaDouble o);

  AsaDouble div(AsaInteger o);
  AsaDouble div(AsaFloat o);
  AsaDouble div(AsaDouble o);

  AsaDouble ceil();
  AsaDouble floor();
  AsaDouble round();

  AsaDouble incr();
  AsaDouble decr();

  AsaInteger cmp(AsaInteger o);
  AsaInteger cmp(AsaFloat o);
  AsaInteger cmp(AsaDouble o);
};
