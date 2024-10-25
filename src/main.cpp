#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

std::vector<instructions::Instruction> program = {
    PUSH("1", asa::AsaType::Double),
    PUSH("3", asa::AsaType::Double),
    PUSH("5", asa::AsaType::Double),
    PUSH("6.9", asa::AsaType::Double),
    PUSH("42", asa::AsaType::Double),
    SHOW,
    PLUS,
    SHOW,
    DIV,
    SHOW,
    MULT,
    SHOW,
    MINUS,
    SHOW
};

int main() {
  asa::AsaObj result = interpreter::eval(program);
  if (result.error != asa::AsaError::Ok) {
    std::cout << "Error encountered: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
