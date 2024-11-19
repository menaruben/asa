#include "list"
#include "objects.hpp"
#include "vector"
#include <cfloat>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#define RAISE                                                                  \
  { .kind = InstructionKind::Raise }

#define HALT                                                                   \
  { .kind = InstructionKind::Halt }

#define CLEAR                                                                  \
  { .kind = InstructionKind::Clear }

#define PUSH(val, t)                                                           \
  { .kind = InstructionKind::Push, .operand = {.value = val, .type = t}, }

#define INCREMENT(name)                                                        \
  { .kind = InstructionKind::Increment, .id = name }

#define DECREMENT(name)                                                        \
  { .kind = InstructionKind::Decrement, .id = name }

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

#define STR                                                                    \
  { .kind = InstructionKind::Str }

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

#define GETTYPE                                                                \
  { .kind = InstructionKind::GetType }

#define SHOW                                                                   \
  { .kind = InstructionKind::Show }

#define PRINT                                                                  \
  { .kind = InstructionKind::Print }

#define PRINTLN                                                                \
  { .kind = InstructionKind::Println }

#define LSHIFT                                                                 \
  { .kind = InstructionKind::Lshift }

#define RSHIFT                                                                 \
  { .kind = InstructionKind::Rshift }

namespace instructions {

enum InstructionKind {
  Show,
  Str,
  Print,
  Println,
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
  Call,
  Lshift,
  Rshift,
  GetType,
  Raise,
};

struct Instruction {
  InstructionKind kind;
  asa::Object operand;
  std::string id;
  std::vector<Instruction> block;
};

asa::Type determine_return_type(asa::Object a, asa::Object b) {
  if (a.type == asa::BigDouble || b.type == asa::BigDouble)
    return asa::Type::BigDouble;
  if (a.type == asa::BigInteger || b.type == asa::BigInteger)
    return asa::Type::BigInteger;
  if (a.type == asa::Double || b.type == asa::Double)
    return asa::Type::Double;
  if (a.type == asa::Float || b.type == asa::Float)
    return asa::Type::Float;
  if (a.type == asa::Integer || b.type == asa::Integer)
    return asa::Type::Integer;
  if (a.type == asa::String || b.type == asa::String)
    return asa::Type::String;
  if (a.type == asa::Char || b.type == asa::Char)
    return asa::Type::Char;
  if (a.type == asa::Bool || b.type == asa::Bool)
    return asa::Type::Bool;
  throw std::runtime_error("Unreachable: Can not determine return_type");
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6) {
  std::ostringstream out;
  out.precision(n);
  out << std::fixed << a_value;
  return std::move(out).str();
}

template <typename T>
asa::Object perform_arithmetic_operation(asa::Object a, asa::Object b,
                                         std::function<T(T, T)> op,
                                         asa::Type return_t) {
  a.type = return_t;
  b.type = return_t;

  switch (return_t) {
  case asa::BigInteger: {
    long long int av = std::stoll(a.value);
    long long int bv = std::stoll(b.value);
    long long int res = op(av, bv);
    return {.value = std::to_string(res), .type = asa::BigInteger};
  }
  case asa::BigDouble: {
    long double ad = std::stold(a.value);
    long double bd = std::stold(b.value);
    long double res = op(ad, bd);
    std::string resstr = to_string_with_precision(res, LDBL_DIG);
    return {.value = resstr, .type = asa::BigDouble};
  }
  case asa::Integer: {
    int ai = std::stoi(a.value);
    int bi = std::stoi(b.value);
    int res = op(ai, bi);
    return {.value = std::to_string(res), .type = asa::Integer};
  }
  case asa::Float: {
    float af = std::stof(a.value);
    float bf = std::stof(b.value);
    float res = op(af, bf);
    std::string resstr = to_string_with_precision(res, FLT_DIG);
    return {.value = resstr, .type = asa::Float};
  }
  case asa::Double: {
    double ad = std::stod(a.value);
    double bd = std::stod(b.value);
    double res = op(ad, bd);
    std::string resstr = to_string_with_precision(res, DBL_DIG);
    return {.value = resstr, .type = asa::Double};
  }
  case asa::String: {
    std::string as = a.value;
    std::string bs = b.value;
    std::string res = as + bs; // Assuming concatenation for strings
    return {.value = res, .type = asa::String};
  }
  default:
    return asa::error_illegal_instruction(
        "Unsupported type for arithmetic operation");
  }
}

asa::Object add(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  return perform_arithmetic_operation<long double>(
      a, b, std::plus<long double>(), return_t);
}

asa::Object subtract(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  return perform_arithmetic_operation<long double>(
      a, b, std::minus<long double>(), return_t);
}

asa::Object multiply(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  return perform_arithmetic_operation<long double>(
      a, b, std::multiplies<long double>(), return_t);
}

asa::Object divide(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  return perform_arithmetic_operation<long double>(
      a, b, std::divides<long double>(), return_t);
}

template <typename T>
asa::Object perform_bitwise_operation(asa::Object a, asa::Object b,
                                      std::function<T(T, T)> op,
                                      asa::Type return_t) {
  a.type = return_t;
  b.type = return_t;

  T av = std::stoll(a.value);
  T bv = std::stoll(b.value);
  T res = op(av, bv);
  return {.value = std::to_string(res), .type = return_t};
}

asa::Object lshift(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  if (return_t != asa::Integer && return_t != asa::BigInteger) {
    return asa::error_illegal_instruction(
        "Unsupported type for bitwise operation: " +
        asa::type_to_str(return_t));
  }
  return perform_bitwise_operation<long long int>(
      a, b, [](long long int x, long long int y) { return x << y; }, return_t);
}

asa::Object rshift(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  if (return_t != asa::Integer && return_t != asa::BigInteger) {
    return asa::error_illegal_instruction(
        "Unsupported type for bitwise operation: " +
        asa::type_to_str(return_t));
  }
  return perform_bitwise_operation<long long int>(
      a, b, [](long long int x, long long int y) { return x >> y; }, return_t);
}

std::string to_string(asa::Object a) {
  if (a.type == asa::BigDouble)
    return to_string_with_precision(std::stold(a.value), LDBL_DIG);
  if (a.type == asa::BigInteger)
    return std::to_string(std::stoll(a.value));
  if (a.type == asa::Double)
    return to_string_with_precision(std::stod(a.value), DBL_DIG);
  if (a.type == asa::Float)
    return to_string_with_precision(std::stof(a.value), FLT_DIG);
  return a.value;
}

asa::Object compare(asa::Object a, asa::Object b) {
  asa::Type return_t = determine_return_type(a, b);
  a.type = return_t;
  b.type = return_t;
  switch (return_t) {
  case asa::Char: {
    char ac = a.value[0];
    char bc = b.value[0];
    std::string result;
    if (ac < bc)
      result = "-1";
    if (ac == bc)
      result = "0";
    if (ac > bc)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::Bool: {
    bool ab = a.value == "true";
    bool bb = b.value == "true";
    std::string result;
    if (ab < bb)
      result = "-1";
    if (ab == bb)
      result = "0";
    if (ab > bb)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

  case asa::BigDouble: {
    long double ad = std::stold(a.value);
    long double bd = std::stold(b.value);
    std::string result;
    if (ad < bd)
      result = "-1";
    if (ad == bd)
      result = "0";
    if (ad > bd)
      result = "1";
    return {.value = result, .type = asa::Integer};
  }

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

  case asa::BigInteger: {
    long long int av = std::stoll(a.value);
    long long int bv = std::stoll(b.value);
    std::string res;
    if (av < bv)
      res = "-1";
    if (av == bv)
      res = "0";
    if (av > bv)
      res = "1";
    return {.value = res, .type = asa::Integer};
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
  case Print:
    return "Print";
  case Println:
    return "Println";
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
  case Raise:
    return "Raise";
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
