#include <regex>
#include <string>

namespace tokens {

enum TokenKind {
  String,
  Integer,
  Bool,
  Float,
  Double,
  Begin,
  End,
  If,
  Goto,
  Label,
  Comma,
  Semicolon,
  Colon,
  Increment,
  Decrement,
  Plus,
  Minus,
  Mult,
  Div,
  Assign,
  LessThan,
  Equals,
  GreaterThan,
  Identifier,
  Show,
  Get,
  Set,
  Push,
  Pop,
  Println,
  Print,
  Call,
  EndOfFile,
};

std::string tokenKindToStr(TokenKind k) {
  switch (k) {
    case String:       return "String";
    case Integer:      return "Integer";
    case Bool:         return "Bool";
    case Float:        return "Float";
    case Double:       return "Double";
    case Begin:        return "Begin";
    case End:          return "End";
    case If:           return "If";
    case Goto:         return "Goto";
    case Label:        return "Label";
    case Comma:        return "Comma";
    case Semicolon:    return "Semicolon";
    case Colon:        return "Colon";
    case Increment:    return "Increment";
    case Decrement:    return "Decrement";
    case Plus:         return "Plus";
    case Minus:        return "Minus";
    case Mult:         return "Mult";
    case Div:          return "Div";
    case Assign:       return "Assign";
    case LessThan:     return "LessThan";
    case Equals:       return "Equals";
    case GreaterThan:  return "GreaterThan";
    case Show:         return "Show";
    case Get:          return "Get";
    case Set:          return "Set";
    case Identifier:   return "Identifier";
    case Push:         return "Push";
    case Pop:          return "Pop";
    case Println:      return "Println";
    case Print:        return "Print";
    case Call:         return "Call";
    case EndOfFile:    return "EndOfFile";
    default:           return "Unknown TokenKind";
  }
}

struct Token {
  std::string value;
  TokenKind kind;
};

// literal patterns
const std::regex STRING_PATTERN("^\".*\"");
const std::regex INT_PATTERN("^[+-]?\\d+$");
const std::regex FLOAT_PATTERN("^[+-]?\\d*\\.\\d+f$"); // example: 0.325f or .45f
const std::regex DOUBLE_PATTERN("^[+-]?\\d*\\.\\d+$"); // example: 0.325  or .45
const std::regex BOOL_PATTERN("^(true|false)$");

// keyword patterns (case insensitive)
const std::regex BEGIN_PATTERN("^Begin$", std::regex_constants::icase);
const std::regex END_PATTERN("^End$", std::regex_constants::icase);
const std::regex IF_PATTERN("^If$", std::regex_constants::icase);
const std::regex GOTO_PATTERN("^Goto$", std::regex_constants::icase);
const std::regex INCR_PATTERN("^Incr$", std::regex_constants::icase);
const std::regex DECR_PATTERN("^Decr$", std::regex_constants::icase);
const std::regex SHOW_PATTERN("^Show$", std::regex_constants::icase);
const std::regex GET_PATTERN("^Get$", std::regex_constants::icase);
const std::regex SET_PATTERN("^Set$", std::regex_constants::icase);
const std::regex PRINTLN_PATTERN("^Println$", std::regex_constants::icase);
const std::regex PRINT_PATTERN("^Print$", std::regex_constants::icase);
const std::regex CALL_PATTERN("^Call$", std::regex_constants::icase);
const std::regex PUSH_PATTERN("^Push$", std::regex_constants::icase);
const std::regex POP_PATTERN("^Pop$", std::regex_constants::icase);

Token tokenFromStr(std::string value) {
  if (std::regex_match(value, STRING_PATTERN)) return {.value = value, .kind = String};
  if (std::regex_match(value, INT_PATTERN))    return {.value = value, .kind = Integer};
  if (std::regex_match(value, FLOAT_PATTERN))  return {.value = value, .kind = Float};
  if (std::regex_match(value, DOUBLE_PATTERN)) return {.value = value, .kind = Double};
  if (std::regex_match(value, BOOL_PATTERN))   return {.value = value, .kind = Bool};

  if (std::regex_match(value, BEGIN_PATTERN))   return {.kind = Begin};
  if (std::regex_match(value, END_PATTERN))     return {.kind = End};
  if (std::regex_match(value, IF_PATTERN))      return {.kind = If};
  if (std::regex_match(value, GOTO_PATTERN))    return {.kind = Goto};
  if (std::regex_match(value, INCR_PATTERN))    return {.kind = Increment};
  if (std::regex_match(value, DECR_PATTERN))    return {.kind = Decrement};
  if (std::regex_match(value, SHOW_PATTERN))    return {.kind = Show};
  if (std::regex_match(value, GET_PATTERN))     return {.kind = Get};
  if (std::regex_match(value, SET_PATTERN))     return {.kind = Set};
  if (std::regex_match(value, PUSH_PATTERN))    return {.kind = Push};
  if (std::regex_match(value, POP_PATTERN))     return {.kind = Pop};
  if (std::regex_match(value, PRINTLN_PATTERN)) return {.kind = Println};
  if (std::regex_match(value, PRINT_PATTERN))   return {.kind = Print};
  if (std::regex_match(value, CALL_PATTERN))    return {.kind = Call};

  if (value == ",")  return {.kind = Comma};
  if (value == ";")  return {.kind = Semicolon};
  if (value == ":")  return {.kind = Colon};
  if (value == "+")  return {.kind = Plus};
  if (value == "-")  return {.kind = Minus};
  if (value == "*")  return {.kind = Mult};
  if (value == "/")  return {.kind = Div};
  if (value == "<")  return {.kind = LessThan};
  if (value == "=")  return {.kind = Assign};
  if (value == "==") return {.kind = Equals};
  if (value == ">")  return {.kind = GreaterThan};

  return {.value = value, .kind = Identifier};
}

} // namespace tokens
