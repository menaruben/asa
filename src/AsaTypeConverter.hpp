#pragma once

#include "AsaBigDouble.hpp"
#include "AsaBigInteger.hpp"
#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include "objects.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

inline AsaInteger to_int(AsaObject o) {
  try {
    switch (o.get_type()) {
    case asa::Integer: {
      int val = stoi(o.str());
      return AsaInteger(val);
    }

    case asa::Float: {
      int val = static_cast<int>(stof(o.str()));
      return AsaInteger(val);
    }

    case asa::Double: {
      int val = static_cast<int>(stod(o.str()));
      return AsaInteger(val);
    }

    case asa::BigInteger: {
      int val = static_cast<int>(stoll(o.str()));
      return AsaInteger(val);
    }

    case asa::BigDouble: {
      int val = static_cast<int>(stold(o.str()));
      return AsaInteger(val);
    }

    case asa::String: {
      int val = stoi(o.str());
      return AsaInteger(val);
    }

    default:
      throw runtime_error("Cannot convert " + type_to_str(o.get_type()) +
                          " to int");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << o.str()
         << " to int. Error: " << e.what() << endl;
    throw;
  }
}

inline AsaBigInteger to_bigint(AsaObject o) {
  try {
    switch (o.get_type()) {
    case asa::BigInteger: {
      long long int val = static_cast<long long int>(stoll(o.str()));
      return AsaBigInteger(val);
    }

    case asa::Integer: {
      long long int val = static_cast<long long int>(stoi(o.str()));
      return AsaBigInteger(val);
    }

    case asa::Float: {
      long long int val = static_cast<long long int>(stof(o.str()));
      return AsaBigInteger(val);
    }

    case asa::Double: {
      long long int val = static_cast<long long int>(stod(o.str()));
      return AsaBigInteger(val);
    }

    case asa::BigDouble: {
      long long int val = static_cast<long long int>(stold(o.str()));
      return AsaBigInteger(val);
    }

    case asa::String: {
      long long int val = stoll(o.str());
      return AsaBigInteger(val);
    }

    default:
      throw runtime_error("Cannot convert " + type_to_str(o.get_type()) +
                          " to bigint");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << o.str()
         << " to bigint. Error: " << e.what() << endl;
    throw;
  }
}

inline AsaBigDouble to_bigdouble(AsaObject o) {
  try {
    switch (o.get_type()) {
    case asa::BigDouble:
      return AsaBigDouble(stold(o.str()));

    case asa::Integer: {
      long double val = static_cast<long double>(stoi(o.str()));
      return AsaBigDouble(val);
    }

    case asa::Float: {
      long double val = static_cast<long double>(stof(o.str()));
      return AsaBigDouble(val);
    }

    case asa::Double: {
      long double val = static_cast<long double>(stod(o.str()));
      return AsaBigDouble(val);
    }

    case asa::BigInteger: {
      long double val = static_cast<long double>(stoll(o.str()));
      return AsaBigDouble(val);
    }

    case asa::String: {
      long double val = stold(o.str());
      return AsaBigDouble(val);
    }

    default:
      throw runtime_error("Cannot convert " + type_to_str(o.get_type()) +
                          " to bigdouble");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << o.str()
         << " to bigdouble. Error: " << e.what() << endl;
    throw;
  }
}

inline AsaFloat to_float(AsaObject o) {
  try {
    switch (o.get_type()) {
    case asa::Float:
      return AsaFloat(stof(o.str()));

    case asa::Integer: {
      float val = static_cast<float>(stoi(o.str()));
      return AsaFloat(val);
    }

    case asa::Double: {
      float val = static_cast<float>(stod(o.str()));
      return AsaFloat(val);
    }

    case asa::BigInteger: {
      float val = static_cast<float>(stoll(o.str()));
      return AsaFloat(val);
    }

    case asa::BigDouble: {
      float val = static_cast<float>(stold(o.str()));
      return AsaFloat(val);
    }

    case asa::String: {
      float val = stof(o.str());
      return AsaFloat(val);
    }

    default:
      throw runtime_error("Cannot convert " + type_to_str(o.get_type()) +
                          " to float");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << o.str()
         << " to float. Error: " << e.what() << endl;
    throw;
  }
}

inline AsaDouble to_double(AsaObject o) {
  try {
    switch (o.get_type()) {
    case asa::Double:
      return AsaDouble(stod(o.str()));

    case asa::Integer: {
      double val = static_cast<double>(stoi(o.str()));
      return AsaDouble(val);
    }

    case asa::Float: {
      double val = static_cast<double>(stof(o.str()));
      return AsaDouble(val);
    }

    case asa::BigInteger: {
      double val = static_cast<double>(stoll(o.str()));
      return AsaDouble(val);
    }

    case asa::BigDouble: {
      double val = static_cast<double>(stold(o.str()));
      return AsaDouble(val);
    }

    case asa::String: {
      double val = stod(o.str());
      return AsaDouble(val);
    }

    default:
      throw runtime_error("Cannot convert " + type_to_str(o.get_type()) +
                          " to double");
    }
  } catch (const exception &e) {
    cerr << "Failed to convert input: " << o.str()
         << " to double. Error: " << e.what() << endl;
    throw;
  }
}
