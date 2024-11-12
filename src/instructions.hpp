#include "list"
#include "objects.hpp"
#include "vector"
#include <exception>
#include <string>
#include <vector>

#define HALT                                                                   \
  { .kind = InstructionKind::Halt }

#define CLEAR                                                                  \
  { .kind = InstructionKind::Clear }

#define PUSH(val, t)                                                           \
  { .kind = InstructionKind::Push, .operand = {.value = val, .type = t}, }

#define POP                                                                    \
  { .kind = InstructionKind::Pop }

#define CALL(name)                                                             \
  { .kind = InstructionKind::Call, .id = name }

#define LABEL(name, pos)                                                       \
  {                                                                            \
    .kind = InstructionKind::Label,                                            \
    .operand = {.value = pos, .type = asa::Integer}, .id = name,               \
  }

#define GOTO(name)                                                             \
  { .kind = InstructionKind::Goto, .id = name, }

#define DEF(name, val, t)                                                      \
  {                                                                            \
    .kind = InstructionKind::DefVar, .operand = {.value = val, .type = t},     \
    .id = name,                                                                \
  }

// basically SET n == POP n <=> pop top of stack to var n
#define SET(name)                                                              \
  { .kind = InstructionKind::SetVar, .id = name }

#define GET(name)                                                              \
  { .kind = InstructionKind::GetVar, .id = name }

#define CMP                                                                    \
  { .kind = InstructionKind::Cmp }

#define IF(val, codeblock)                                                     \
  { .kind = InstructionKind::If, .block = codeblock }

#define IFGOTO(val, label)                                                     \
  {                                                                            \
    .kind = InstructionKind::IfGoto,                                           \
    .operand = {.value = val, .type = asa::Integer}, .id = label               \
  }

#define ADD                                                                    \
  { .kind = InstructionKind::Add }

#define SUB                                                                    \
  { .kind = InstructionKind::Subtract }

#define MUL                                                                    \
  { .kind = InstructionKind::Multiply }

#define DIV                                                                    \
  { .kind = InstructionKind::Divide }

#define SHOW                                                                   \
  { .kind = InstructionKind::Show }

namespace instructions {

enum InstructionKind {
  Show,
  Push,
  Pop,
  Add,
  Subtract,
  Multiply,
  Divide,
  Label,
  Goto,
  DefVar,
  SetVar,
  GetVar,
  Cmp,
  If,
  IfGoto,
  IfHalt,
  Halt,
  Clear,
  Increment,
  Decrement,
  Call
};

struct Instruction {
  InstructionKind kind;
  asa::Object operand;
  std::string id;
  std::vector<Instruction> block;
};

asa::Object add(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::error_typemismatch("TYPE MISMATCH: Cannot add " + a.value +
                                   " and " + b.value);

  switch (a.type) {
  case asa::String: {
    std::string as = a.value.substr(0, a.value.size() - 1);
    std::string bs = b.value.substr(1, b.value.size());
    std::string sum = as + bs;
    return {.value = sum, .type = asa::String};
  }

  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int sum = ai + bi;
    return {.value = std::to_string(sum), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float sum = af + bf;
    return {.value = std::to_string(sum), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double sum = ad + bd;
    return {.value = std::to_string(sum), .type = asa::Double};
  }

  default:
    return asa::error_illegal_instruction("Unsupported type for addition");
  }
}

asa::Object subtract(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::error_typemismatch("TYPE MISMATCH: Cannot subtract " + a.value +
                                   " and " + b.value);

  if (!is_numeric_type(a) || !is_numeric_type(b))
    return asa::error_arithmetic(
        "ARITHMETIC ERROR: Cannot subtract non-numeric " + a.value + " and " +
        b.value);

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int delta = ai - bi;
    return {.value = std::to_string(delta), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float delta = af - bf;
    return {.value = std::to_string(delta), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double delta = ad - bd;
    return {.value = std::to_string(delta), .type = asa::Double};
  }
  default:
    return asa::error_illegal_instruction("Unsupported type for subtraction");
  }
}
asa::Object multiply(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::error_typemismatch("TYPE MISMATCH: Cannot multiply " + a.value +
                                   " and " + b.value);

  if (!is_numeric_type(a) || !is_numeric_type(b))
    return asa::error_arithmetic(
        "ARITHMETIC ERROR: Cannot multiply non-numeric " + a.value + " and " +
        b.value);

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int prod = ai * bi;
    return {.value = std::to_string(prod), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float prod = af * bf;
    return {.value = std::to_string(prod), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double prod = ad * bd;
    return {.value = std::to_string(prod), .type = asa::Double};
  }
  default:
    return asa::error_illegal_instruction(
        "Unsupported type for multiplication");
  }
}

asa::Object divide(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::error_typemismatch("TYPE MISMATCH: Cannot divide " + a.value +
                                   " and " + b.value);

  if (!is_numeric_type(a) || !is_numeric_type(b))
    return asa::error_arithmetic(
        "ARITHMETIC ERROR: Cannot divide non-numeric " + a.value + " and " +
        b.value);

  switch (a.type) {
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int quotient = ai / bi;
    return {.value = std::to_string(quotient), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float quotient = af / bf;
    return {.value = std::to_string(quotient), .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double quotient = ad / bd;
    return {.value = std::to_string(quotient), .type = asa::Double};
  }
  default:
    return asa::error_illegal_instruction("Unsupported type for division");
  }
}

asa::Object compare(asa::Object a, asa::Object b) {
  if (a.type != b.type)
    return asa::error_typemismatch("TYPE MISMATCH: Cannot compare " + a.value +
                                   " and " + b.value);
  asa::Type returnType = a.type;

  switch (returnType) {
  case asa::String: {
    std::string result;
    if (a.value < b.value)
      result = "-1";
    if (a.value == b.value)
      result = "0";
    if (a.value < b.value)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    std::string result;
    if (ai < bi)
      result = "-1";
    if (ai == bi)
      result = "0";
    if (ai > bi)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Float: {
    int af = std::stof(a.value);
    int bf = std::stof(b.value);
    std::string result;
    if (af < bf)
      result = "-1";
    if (af == bf)
      result = "0";
    if (af > bf)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Double: {
    int ad = std::stod(a.value);
    int bd = std::stod(b.value);
    std::string result;
    if (ad < bd)
      result = "-1";
    if (ad == bd)
      result = "0";
    if (ad > bd)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  default:
    throw std::runtime_error("Unsupported type for comparison");
  }
}

std::vector<asa::Object> pop_args(std::list<asa::Object> *stack, int count) {
  std::vector<asa::Object> args;
  std::list<asa::Object>::iterator it;
  if (stack->size() < count) {
    args.push_back(asa::error_stackunderflow(
        "STACK UNDERFLOW: Cannot popargs without at least " +
        std::to_string(count) + " elements on the stack"));
    return args;
  };

  asa::Object o;
  int i = 0;
  while (i < count) {
    o = stack->back();
    args.push_back(o);
    it = std::prev(stack->end());
    stack->erase(it);
    i++;
  }
  return args;
}

std::string instructionkind_to_str(InstructionKind k) {
  switch (k) {
  case Show:
    return "Show";
  case Push:
    return "Push";
  case Pop:
    return "Pop";
  case Add:
    return "Add";
  case Subtract:
    return "Subtract";
  case Multiply:
    return "Multiply";
  case Divide:
    return "Divide";
  case Label:
    return "Label";
  case Goto:
    return "Goto";
  case DefVar:
    return "DefVar";
  case SetVar:
    return "SetVar";
  case GetVar:
    return "GetVar";
  case Cmp:
    return "Cmp";
  case If:
    return "If";
  case IfGoto:
    return "IfGoto";
  case IfHalt:
    return "IfHalt";
  case Halt:
    return "Halt";
  case Clear:
    return "Clear";
  case Increment:
    return "Increment";
  case Decrement:
    return "Decrement";
  case Call:
    return "Call";
  default:
    throw std::runtime_error("Unsupported instruction kind");
  }
}

std::string instruction_to_str(Instruction inst) {
  std::string typestr = instructionkind_to_str(inst.kind);
  std::string operand = inst.operand.value;
  std::string id = inst.id;
  return "kind: " + typestr + ", operand: " + operand + ", id: " + id;
}

} // namespace instructions
