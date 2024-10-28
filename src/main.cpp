#include "interpreter.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <pthread.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;


std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
}

int main(int argc, char** argv) {
  if (argc < 2) throw std::runtime_error("Please enter a file path!");
  std::string sourcepath = argv[1];
  std::string source = readFile(sourcepath);
  std::unordered_map<std::string, std::vector<Instruction>> program = transpiler::loadProgramFromMemory(source);
  std::list<asa::Object> stack;
  if (program.find("main") == program.end()) {
    std::cout << "[ERROR]: No entry point 'main' found!" << std::endl;
  }
  
  Object result = eval(program, "main", &stack);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
