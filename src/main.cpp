#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {
  // define variable "remaining" with 
  // initial value 4 and type Integer
  DEF("remaining", "4", Integer),
  
  // create a label to simulate loop in a goto style
  LABEL("loop"),
    PUSH("1", Integer),
    
    // decrement i variable my one
    GET("remaining"),
    PUSH("1", Integer),
    MINUS,
    SET("remaining"),
    
    // check if i is 0
    GET("remaining"),
    PUSH("0", Integer),
    CMP,
  // if i > 0 then it pushes 1 onto stack because it is bigger
  IF("1", "loop"),
  
  // else show the stack
  PUSH("done!", String),
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
