#pragma once

#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include "AsaObject.hpp"
#include "AsaString.hpp"
#include <string>

using namespace asa;

class AsaInteger : public AsaObject {
private:
    int int_value;

public:
    AsaInteger(int val);

    int get_value() const;
    void set_value(int v);
    std::string str() const;

    AsaString  add(AsaString o);
    AsaInteger add(AsaInteger o);
    AsaFloat   add(AsaFloat o);
    AsaDouble  add(AsaDouble o);

    AsaInteger sub(AsaInteger o);
    AsaFloat   sub(AsaFloat o);
    AsaDouble  sub(AsaDouble o);

    AsaInteger mul(AsaInteger o);
    AsaFloat   mul(AsaFloat o);
    AsaDouble  mul(AsaDouble o);

    AsaInteger div(AsaInteger o);
    AsaFloat   div(AsaFloat o);
    AsaDouble  div(AsaDouble o);

    AsaInteger lshift(AsaInteger o);
    AsaInteger rshift(AsaInteger o);

    AsaInteger bitwise_or(AsaInteger o);
    AsaInteger bitwise_xor(AsaInteger o);
    AsaInteger bitwise_and(AsaInteger o);
    AsaInteger bitwise_not();

    AsaInteger ceil();
    AsaInteger floor();
    AsaInteger round();

    AsaInteger incr();
    AsaInteger decr();

    AsaInteger cmp(AsaInteger o);
    AsaInteger cmp(AsaFloat o);
    AsaInteger cmp(AsaDouble o);
};
