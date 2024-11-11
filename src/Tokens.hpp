#pragma once

#include <regex>
#include <stdexcept>
#include <string>
#include "objects.hpp"

namespace tokens {

enum TokenKind {
  String,
  Integer,
  Bool,
  Float,
  Double,
  Begin,
  End,
  IfGoto,
  Goto,
  Label,
  Comma,
  Semicolon,
  Colon,
  Add,
  Sub,
  Mul,
  Div,
  Assign,
  Cmp,
  Identifier,
  Show,
  Var,
  Push,
  Pop,
  Println,
  Print,
  Call,
  EndOfFile,
};

std::string token_kind_to_str(TokenKind k) {
  switch (k) {
    case String:       return "String";
    case Integer:      return "Integer";
    case Bool:         return "Bool";
    case Float:        return "Float";
    case Double:       return "Double";
    case Begin:        return "Begin";
    case End:          return "End";
    case Goto:         return "Goto";
    case IfGoto:       return "IfGoto";
    case Label:        return "Label";
    case Comma:        return "Comma";
    case Semicolon:    return "Semicolon";
    case Colon:        return "Colon";
    case Add:          return "Add";
    case Sub:          return "Sub";
    case Mul:          return "Mul";
    case Div:          return "Div";
    case Assign:       return "Assign";
    case Cmp:          return "Cmp";
    case Show:         return "Show";
    case Var:          return "Var";
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

asa::Type token_kind_to_asatype(TokenKind k) {
  switch (k)
  {
  case String: return asa::String;
  case Integer: return asa::Integer;
  case Bool: return asa::Bool;
  case Float: return asa::Float;
  case Double: return asa::Double;
  default: throw std::runtime_error("Can not convert" + token_kind_to_str(k) + " token to type");
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
const std::regex IDENTIFIER_PATTERN("^[a-zA-Z_][a-zA-Z0-9_]*$");

// keyword patterns (case insensitive)
const std::regex BEGIN_PATTERN("^Begin$", std::regex_constants::icase);
const std::regex END_PATTERN("^End$", std::regex_constants::icase);
const std::regex IFGOTO_PATTERN("^Ifgoto$", std::regex_constants::icase);
const std::regex GOTO_PATTERN("^Goto$", std::regex_constants::icase);
const std::regex SHOW_PATTERN("^Show$", std::regex_constants::icase);
const std::regex VAR_PATTERN("^Var$", std::regex_constants::icase);
const std::regex PRINTLN_PATTERN("^Println$", std::regex_constants::icase);
const std::regex PRINT_PATTERN("^Print$", std::regex_constants::icase);
const std::regex CALL_PATTERN("^Call$", std::regex_constants::icase);
const std::regex PUSH_PATTERN("^Push$", std::regex_constants::icase);
const std::regex POP_PATTERN("^Pop$", std::regex_constants::icase);
const std::regex CMP_PATTERN("^Cmp$", std::regex_constants::icase);
const std::regex DEF_PATTERN("^Def$", std::regex_constants::icase);
const std::regex LABEL_PATTERN("^Label$", std::regex_constants::icase);
const std::regex ADD_PATTERN("^Add$", std::regex_constants::icase);
const std::regex SUB_PATTERN("^Sub$", std::regex_constants::icase);
const std::regex MUL_PATTERN("^Mul$", std::regex_constants::icase);
const std::regex DIV_PATTERN("^Div$", std::regex_constants::icase);

Token token_from_str(std::string value) {
  if (std::regex_match(value, STRING_PATTERN))     return {.value = value, .kind = String};
  if (std::regex_match(value, INT_PATTERN))        return {.value = value, .kind = Integer};
  if (std::regex_match(value, FLOAT_PATTERN))      return {.value = value, .kind = Float};
  if (std::regex_match(value, DOUBLE_PATTERN))     return {.value = value, .kind = Double};
  if (std::regex_match(value, BOOL_PATTERN))       return {.value = value, .kind = Bool};
  if (std::regex_match(value, BEGIN_PATTERN))      return {.kind = Begin};
  if (std::regex_match(value, END_PATTERN))        return {.kind = End};
  if (std::regex_match(value, IFGOTO_PATTERN))     return {.kind = IfGoto};
  if (std::regex_match(value, GOTO_PATTERN))       return {.kind = Goto};
  if (std::regex_match(value, SHOW_PATTERN))       return {.kind = Show};
  if (std::regex_match(value, VAR_PATTERN))        return {.kind = Var};
  if (std::regex_match(value, PUSH_PATTERN))       return {.kind = Push};
  if (std::regex_match(value, POP_PATTERN))        return {.kind = Pop};
  if (std::regex_match(value, PRINTLN_PATTERN))    return {.kind = Println};
  if (std::regex_match(value, PRINT_PATTERN))      return {.kind = Print};
  if (std::regex_match(value, CALL_PATTERN))       return {.kind = Call};
  if (std::regex_match(value, CMP_PATTERN))        return {.kind = Cmp};
  if (std::regex_match(value, LABEL_PATTERN))      return {.kind = Label};
  if (std::regex_match(value, ADD_PATTERN))        return {.kind = Add};
  if (std::regex_match(value, SUB_PATTERN))        return {.kind = Sub};
  if (std::regex_match(value, MUL_PATTERN))        return {.kind = Mul};
  if (std::regex_match(value, DIV_PATTERN))        return {.kind = Div};
  if (std::regex_match(value, IDENTIFIER_PATTERN)) return {.value = value, .kind = Identifier};

  if (value == ",") return {.kind = Comma};
  if (value == ";") return {.kind = Semicolon};
  if (value == ":") return {.kind = Colon};
  if (value == "=") return {.kind = Assign};


  throw std::runtime_error("Invalid token: " + value);
}

} // namespace tokens
