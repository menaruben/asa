#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

int main() {
  std::unordered_map<std::string, std::vector<Instruction>> program;
  program["main"] = {
      PUSH("10", Integer),
      CALL("factorial"),
      SHOW,
  };
  program["factorial"] = {
      DEF("n", 0, Integer), // define n
      SET("n"),             // set n to top of stack
      DEF("ans", "1", Integer), DEF("i", "1", Integer),
      
      LABEL("fact"),
      // calculate ans = ans * i
      GET("ans"), GET("i"), MUL, SET("ans"),

      // increment i
      INCR("i"),

      // check if i < n
      GET("i"), GET("n"), CMP, IFGOTO("-1", "fact"),
      // check if i == n
      GET("i"), GET("n"), CMP, IFGOTO("0", "fact"),

      GET("ans") // push answer to stack
  };
  Object result = eval(program);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
