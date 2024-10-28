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
      DEF("n", "0", Integer), // define n
      SET("n"),             // set n to top of stack
      DEF("ans", "1", Integer), DEF("i", "1", Integer),

      LABEL("fact"),
        GET("ans"), GET("i"), MUL, SET("ans"),
        INCR("i"),
        GET("i"), GET("n"), CMP, IFGOTO("-1", "fact"),
        GET("i"), GET("n"), CMP, IFGOTO("0", "fact"),

      GET("ans"), // push answer to stack
  };

  std::list<asa::Object> stack;
  Object result = eval(program, "main", &stack);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
