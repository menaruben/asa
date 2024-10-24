#include "interpreter.hpp"
#include <vector>

std::vector<instructions::Instruction> program = {
    PUSH("42", asa::AsaType::Integer),
    PUSH("69", asa::AsaType::Integer),
    SHOW,
    PLUS,
    SHOW,
    PUSH("3.141", asa::AsaType::Float),
    PUSH("69.420", asa::AsaType::Float),
    MINUS,
};

int main() { return interpreter::eval(program); }
