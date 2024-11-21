#pragma once

#include <string>

using namespace std;

namespace asa {
enum Type { Integer, BigInteger, Float, Double, BigDouble, String, Char, Bool };

enum Error {
  Ok,
  StackOverflow,
  StackUnderflow,
  TypeMismatch,
  ArithmeticOnNonNumericType,
  DivByZero,
  IllegalInstruction,
  LabelNotFound,
  UndefinedVariable,
};

string error_to_str(Error e);
string type_to_str(Type t);
Type str_to_type(string t);
} // namespace asa
