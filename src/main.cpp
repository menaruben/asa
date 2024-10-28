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
    MUL,
    SET("ans"),

    // increment i
    INCR("i"),
    
    // check if i < n 
    GET("i"),
    GET("n"),
    CMP,
    IFGOTO("-1", "factorial"),
    // check if i == n 
    GET("i"),
    GET("n"),
    CMP,
    IFGOTO("0", "factorial"),
  
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
