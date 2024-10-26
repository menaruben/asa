#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {
  LABEL("start"),
  PUSH("1", Integer),
  SHOW,
  JUMP("start")
};

int main() {
  Object result = eval(program);
  if (result.error != Ok) {
    std::cout << "Error encountered: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
