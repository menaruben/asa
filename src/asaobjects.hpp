#include <string>

namespace asa {
enum AsaType { Integer, Float, Double, String, Bool };

struct AsaObj {
  std::string value;
  AsaType type;
};

bool isNumericType(AsaObj o) {
  return o.type == AsaType::Float || o.type == AsaType::Double ||
         o.type == AsaType::Integer;
}

AsaObj add(AsaObj a, AsaObj b) {
  if (a.type != b.type)
    throw std::exception();
  if (!isNumericType(a) || !isNumericType(b))
    throw std::exception();

  switch (a.type) {
  case AsaType::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stof(b.value);
    int sum = ai + bi;
    return {.value = std::to_string(sum), .type = AsaType::Integer};
  }

  default:
    throw std::exception();
  }
}
}
