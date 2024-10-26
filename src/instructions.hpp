#include "list"
#include "objects.hpp"
#include "vector"

namespace instructions {
enum InstructionKind;
struct Instruction;

asa::Object plus(asa::Object a, asa::Object b);
asa::Object minus(asa::Object a, asa::Object b);
asa::Object mult(asa::Object a, asa::Object b);
asa::Object div(asa::Object a, asa::Object b);
std::vector<asa::Object> pop(std::list<asa::Object> *stack, int count);
} // namespace instructions
