#include "Tokens.hpp"
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

void print_usage() {
  cout << "usage: asa [arg] source.asa" << endl;
  cout << "  arg options:" << endl;
  cout << "    run     interprets the source.asa file" << endl;
  cout << "    build   compiles the source.asa file into an executable" << endl;
}

int main(int argc, char **argv) {
  if (argc < 3) { 
    print_usage();
    return -1;
  }
  
  string action = argv[1];
  string sourcepath = argv[2];
  string source = read_file(sourcepath, "//");
  vector<Token> tokens = lexer::tokenize(source);
  Program program = load_program(tokens);
  list<AsaObject> stack;
  if (program.find("main") == program.end()) {
    cout << "[ERROR]: No entry point 'main' found!" << endl;
  }

  if (action == "run") {
    AsaObject result = interpreter::eval(program, "main", &stack);
    if (result.get_error_type() != Ok) {
      cout << result.get_error() << endl;
      return -1;
    }
  } else if (action == "build") {
    cout << "[ERROR]: Compilation not supported right now" << endl;
    return -1;
  } else {
    print_usage();
    return -1;
  }
  
  return 0;
}
