#include "interpreter.hpp"
#include <ostream>
#include <vector>
#include <iostream>

std::vector<instructions::Instruction> program = {
    PUSH("6.9", asa::AsaType::Float),
    PUSH("42.0", asa::AsaType::Float),
    SHOW,
    PLUS,
    SHOW,
};

int main() { 
    asa::AsaObj result = interpreter::eval(program); 
    if (result.error != asa::AsaError::Ok) {
        std::cout << "Error encountered: " << result.value << std::endl;
        return -1;
    }
    return 0;
}
