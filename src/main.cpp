#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;

std::vector<Instruction> program = {PUSH("1", asa::Double),
                                    PUSH("3", asa::Double),
                                    PUSH("5", asa::Double),
                                    PUSH("6.9", asa::Double),
                                    PUSH("42", asa::Double),
                                    SHOW,
                                    PLUS,
                                    SHOW,
                                    DIV,
                                    SHOW,
                                    MULT,
                                    SHOW,
                                    MINUS,
                                    SHOW};

int main() {
  asa::Object result = interpreter::eval(program);
  if (result.error != asa::Ok) {
    std::cout << "Error encountered: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
