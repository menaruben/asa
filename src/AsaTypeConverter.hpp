#pragma once

#include "AsaBigDouble.hpp"
#include "AsaBigInteger.hpp"
#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include "AsaInteger.hpp"
#include "objects.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

inline string strip_suffix(std::string val, const std::string &suffix) {
  if (val.size() > suffix.size() &&
      val.substr(val.size() - suffix.size()) == suffix) {
    val = val.substr(0, val.size() - suffix.size());
  }
  return val;
}

inline AsaInteger to_int(const std::string &input_str, asa::Type type) {
  std::string stripped_input = strip_suffix(input_str, "bi");
  stripped_input = strip_suffix(stripped_input, "bd");

  try {
    switch (type) {
    case asa::Type::Integer:
    case asa::Type::String:
      return AsaInteger(stoi(stripped_input));
    case asa::Type::Float:
      return AsaInteger(static_cast<int>(stof(stripped_input)));
    case asa::Type::Double:
      return AsaInteger(static_cast<int>(stod(stripped_input)));
    case asa::Type::BigInteger:
      return AsaInteger(static_cast<int>(stoll(stripped_input)));
    case asa::Type::BigDouble:
      return AsaInteger(static_cast<int>(stold(stripped_input)));
    default:
      throw runtime_error("Cannot convert " + asa::type_to_str(type) +
                          " to int");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << input_str
         << " to int. Error: " << e.what() << endl;
    throw;
  }
}

inline AsaBigDouble to_bigdouble(const std::string &input_str, asa::Type type) {
  try {
    std::string stripped_input = strip_suffix(input_str, "bi");
    stripped_input = strip_suffix(stripped_input, "bd");

    switch (type) {
    case asa::Type::BigDouble:
      return AsaBigDouble(stold(stripped_input));
    case asa::Type::Integer:
      return AsaBigDouble(static_cast<long double>(stoi(stripped_input)));
    case asa::Type::Float:
      return AsaBigDouble(static_cast<long double>(stof(stripped_input)));
    case asa::Type::Double:
      return AsaBigDouble(static_cast<long double>(stod(stripped_input)));
    case asa::Type::BigInteger:
      return AsaBigDouble(static_cast<long double>(stoll(stripped_input)));
    case asa::Type::String:
      cerr << "Attempting to convert string to BigDouble: " << stripped_input
           << endl;
      return AsaBigDouble(stold(stripped_input));
    default:
      throw runtime_error("Cannot convert " + asa::type_to_str(type) +
                          " to BigDouble");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << input_str
         << " to BigDouble. Error: " << e.what() << endl;
    throw runtime_error(string("Error in to_bigdouble: ") + e.what() +
                        "\nInput: " + input_str);
  }
}

inline AsaBigInteger to_bigint(const std::string &input_str, asa::Type type) {
  try {
    std::string stripped_input = strip_suffix(input_str, "bi");
    stripped_input = strip_suffix(stripped_input, "bd");

    switch (type) {
    case asa::Type::BigInteger:
      return AsaBigInteger(stoll(stripped_input));
    case asa::Type::Integer:
      return AsaBigInteger(static_cast<long long int>(stoi(stripped_input)));
    case asa::Type::Float:
      return AsaBigInteger(static_cast<long long int>(stof(stripped_input)));
    case asa::Type::Double:
      return AsaBigInteger(static_cast<long long int>(stod(stripped_input)));
    case asa::Type::BigDouble:
      return AsaBigInteger(static_cast<long long int>(stold(stripped_input)));
    case asa::Type::String:
      cerr << "Attempting to convert string to BigInteger: " << stripped_input
           << endl;
      return AsaBigInteger(stoll(stripped_input));
    default:
      throw runtime_error("Cannot convert " + asa::type_to_str(type) +
                          " to BigInteger");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << input_str
         << " to BigInteger. Error: " << e.what() << endl;
    throw runtime_error(string("Error in to_bigint: ") + e.what() +
                        "\nInput: " + input_str);
  }
}

inline AsaFloat to_float(const std::string &input_str, asa::Type type) {
  try {
    std::string stripped_input = strip_suffix(input_str, "bi");
    stripped_input = strip_suffix(stripped_input, "bd");

    switch (type) {
    case asa::Type::Float:
      return AsaFloat(stof(stripped_input));
    case asa::Type::Integer:
      stripped_input += ".0f";
      return AsaFloat(static_cast<float>(stoi(stripped_input)));
    case asa::Type::Double:
      return AsaFloat(static_cast<float>(stod(stripped_input)));
    case asa::Type::BigInteger:
      return AsaFloat(static_cast<float>(stoll(stripped_input)));
    case asa::Type::BigDouble:
      return AsaFloat(static_cast<float>(stold(stripped_input)));
    case asa::Type::String:
      return AsaFloat(stof(stripped_input));
    default:
      throw runtime_error("Cannot convert " + asa::type_to_str(type) +
                          " to float");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << input_str
         << " to float. Error: " << e.what() << endl;
    throw runtime_error(string("Error in to_float: ") + e.what() +
                        "\nInput: " + input_str);
  }
}

inline AsaDouble to_double(const std::string &input_str, asa::Type type) {
  try {
    std::string stripped_input = strip_suffix(input_str, "bi");
    stripped_input = strip_suffix(stripped_input, "bd");

    switch (type) {
    case asa::Type::Double:
      return AsaDouble(stod(stripped_input));
    case asa::Type::Integer:
      return AsaDouble(static_cast<double>(stoi(stripped_input)));
    case asa::Type::Float:
      return AsaDouble(static_cast<double>(stof(stripped_input)));
    case asa::Type::BigInteger:
      return AsaDouble(static_cast<double>(stoll(stripped_input)));
    case asa::Type::BigDouble:
      return AsaDouble(static_cast<double>(stold(stripped_input)));
    case asa::Type::String:
      return AsaDouble(stod(stripped_input));
    default:
      throw runtime_error("Cannot convert " + asa::type_to_str(type) +
                          " to double");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << input_str
         << " to double. Error: " << e.what() << endl;
    throw;
  }
}
