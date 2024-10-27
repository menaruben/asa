#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {
  DEF("n", "10", Integer),
  DEF("ans", "1", Integer),
  
  DEF("i", "1", Integer),
  LABEL("factorial"),
    // push current ans to stack
    GET("ans"),
  
    // calculate ans = ans * i
    GET("ans"),
    GET("i"),
    MULT,
    SET("ans"),

    // increment i
    INCR("i"),
    
    // check if n > i
    GET("n"),
    GET("i"),
    CMP,
    IFGOTO("1", "factorial"),
  
  SHOW,
};

int main() {
  Object result = eval(program);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
