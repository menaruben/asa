#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {
  DEF("times", "4", Integer),
  DEF("count", "0", Integer),

  LABEL("loop"),
  PUSH("1", Integer),
  PUSH("1", Integer),
  GET("count"),
  PLUS,
  SET("count"),
  GET("count"),
  GET("times"),
  CMP,
  IF("-1", "loop"),  

  PUSH("Pushed 4 ones to stack successfully!", String),
  SHOW
};

int main() {
  Object result = eval(program);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
