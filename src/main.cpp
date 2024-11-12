#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <pthread.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace asa;
using namespace transpiler;

int main(int argc, char **argv) {
  if (argc < 2)
    throw runtime_error("Please enter a file path!");
  string sourcepath = argv[1];
  string source = read_file(sourcepath, "//");
  vector<Token> tokens = lexer::tokenize(source);

  Program program = load_program(tokens);
  list<asa::Object> stack;
  if (program.find("main") == program.end()) {
    cout << "[ERROR]: No entry point 'main' found!" << endl;
  }

  Object result = interpreter::eval(program, "main", &stack);
  if (result.error != Ok) {
    cout << "[ERROR]: " << result.value << endl;
    return -1;
  }
  return 0;
}
