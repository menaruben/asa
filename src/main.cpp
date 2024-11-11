#include "interpreter.hpp"
#include "Lexer.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <pthread.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace asa;
using namespace transpiler;

string readFile(const string &filename, string comment_delim) {
  ifstream file(filename);
  if (!file.is_open()) {
      cerr << "Error opening file." << endl;
      return "";
  }

  stringstream ss;
  string line;
  while (getline(file, line)) {
      line = line.substr(0, line.find(comment_delim));
      ss << line << endl;
  }
  return ss.str();
}

int main(int argc, char **argv) {
  if (argc < 2)
    throw runtime_error("Please enter a file path!");
  string sourcepath = argv[1];
  string source = readFile(sourcepath, "//");
  vector<Token> tokens = lexer::tokenize(source);
  Program program = load_program(tokens); list<asa::Object> stack; 
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
