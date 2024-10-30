#include "Lexer.hpp"
#include "instructions.hpp"
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;

namespace transpiler {

std::unordered_map<std::string, std::vector<Instruction>>
load_program(std::string source) {
  std::unordered_map<std::string, std::vector<Instruction>> program;
  std::vector<Token> tokens = lexer::tokenize(source);
  Token t;

  for (int i = 0; i < tokens.size(); i++) {
    throw std::runtime_error("Not implemented yet...");
    t = tokens[i];
  }
}
} // namespace transpiler
