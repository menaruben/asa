#pragma once

#include "objects.hpp"
#include <regex>
#include <stdexcept>
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
  Import,
  EndOfFile,
};

std::string token_kind_to_str(TokenKind k) {
  switch (k) {
  case String:
    return "String";
  case Integer:
    return "Integer";
  case Bool:
    return "Bool";
  case Float:
    return "Float";
  case Double:
    return "Double";
  case Begin:
    return "Begin";
  case End:
    return "End";
  case Goto:
    return "Goto";
  case IfGoto:
    return "IfGoto";
  case Label:
    return "Label";
  case Comma:
    return "Comma";
  case Semicolon:
    return "Semicolon";
  case Colon:
    return "Colon";
  case Add:
    return "Add";
  case Sub:
    return "Sub";
  case Mul:
    return "Mul";
  case Div:
    return "Div";
  case Assign:
    return "Assign";
  case Cmp:
    return "Cmp";
  case Show:
    return "Show";
  case Var:
    return "Var";
  case Identifier:
    return "Identifier";
  case Push:
    return "Push";
  case Pop:
    return "Pop";
  case Println:
    return "Println";
  case Print:
    return "Print";
  case Call:
    return "Call";
  case Import:
    return "Import";
  case EndOfFile:
    return "EndOfFile";
  default:
    return "Unknown TokenKind";
  }
}

asa::Type token_kind_to_asatype(TokenKind k) {
  switch (k) {
  case String:
    return asa::String;
  case Integer:
    return asa::Integer;
  case Bool:
    return asa::Bool;
  case Float:
    return asa::Float;
  case Double:
    return asa::Double;
  default:
    throw std::runtime_error("Can not convert" + token_kind_to_str(k) +
                             " token to type");
  }
}

struct Token {
  std::string value;
  TokenKind kind;
  int line;   // end line of token
  int column; // end column of token
};

// literal patterns
const std::regex STRING_PATTERN("^\".*\"");
const std::regex INT_PATTERN("^[+-]?\\d+$");
const std::regex
    FLOAT_PATTERN("^[+-]?\\d*\\.\\d+f$"); // example: 0.325f or .45f
const std::regex DOUBLE_PATTERN("^[+-]?\\d*\\.\\d+$"); // example: 0.325  or .45
const std::regex BOOL_PATTERN("^(true|false)$");
const std::regex IDENTIFIER_PATTERN("^[a-zA-Z_][a-zA-Z0-9_]*$");

// keyword patterns (case insensitive)
const std::regex BEGIN_PATTERN("^Begin$", std::regex_constants::icase);
const std::regex END_PATTERN("^End$", std::regex_constants::icase);
const std::regex IMPORT_PATTERN("^Import$", std::regex_constants::icase);
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

Token token_from_str(std::string value, int line, int column) {
  if (std::regex_match(value, STRING_PATTERN))
    return {.value = value, .kind = String, .line = line, .column = column};
  if (std::regex_match(value, INT_PATTERN))
    return {.value = value, .kind = Integer, .line = line, .column = column};
  if (std::regex_match(value, FLOAT_PATTERN))
    return {.value = value, .kind = Float, .line = line, .column = column};
  if (std::regex_match(value, DOUBLE_PATTERN))
    return {.value = value, .kind = Double, .line = line, .column = column};
  if (std::regex_match(value, BOOL_PATTERN))
    return {.value = value, .kind = Bool, .line = line, .column = column};

  if (std::regex_match(value, BEGIN_PATTERN))
    return {.value = value, .kind = Begin, .line = line, .column = column};
  if (std::regex_match(value, END_PATTERN))
    return {.value = value, .kind = End, .line = line, .column = column};
  if (std::regex_match(value, IMPORT_PATTERN))
    return {.value = value, .kind = Import, .line = line, .column = column};
  if (std::regex_match(value, IFGOTO_PATTERN))
    return {.value = value, .kind = IfGoto, .line = line, .column = column};
  if (std::regex_match(value, GOTO_PATTERN))
    return {.value = value, .kind = Goto, .line = line, .column = column};
  if (std::regex_match(value, SHOW_PATTERN))
    return {.value = value, .kind = Show, .line = line, .column = column};
  if (std::regex_match(value, VAR_PATTERN))
    return {.value = value, .kind = Var, .line = line, .column = column};
  if (std::regex_match(value, PUSH_PATTERN))
    return {.value = value, .kind = Push, .line = line, .column = column};
  if (std::regex_match(value, POP_PATTERN))
    return {.value = value, .kind = Pop, .line = line, .column = column};
  if (std::regex_match(value, PRINTLN_PATTERN))
    return {.value = value, .kind = Println, .line = line, .column = column};
  if (std::regex_match(value, PRINT_PATTERN))
    return {.value = value, .kind = Print, .line = line, .column = column};
  if (std::regex_match(value, CALL_PATTERN))
    return {.value = value, .kind = Call, .line = line, .column = column};
  if (std::regex_match(value, CMP_PATTERN))
    return {.value = value, .kind = Cmp, .line = line, .column = column};
  if (std::regex_match(value, LABEL_PATTERN))
    return {.value = value, .kind = Label, .line = line, .column = column};
  if (std::regex_match(value, ADD_PATTERN))
    return {.value = value, .kind = Add, .line = line, .column = column};
  if (std::regex_match(value, SUB_PATTERN))
    return {.value = value, .kind = Sub, .line = line, .column = column};
  if (std::regex_match(value, MUL_PATTERN))
    return {.value = value, .kind = Mul, .line = line, .column = column};
  if (std::regex_match(value, DIV_PATTERN))
    return {.value = value, .kind = Div, .line = line, .column = column};
  if (std::regex_match(value, IDENTIFIER_PATTERN))
    return {.value = value, .kind = Identifier, .line = line, .column = column};

  if (value == ",")
    return {.value = value, .kind = Comma, .line = line, .column = column};
  if (value == ";")
    return {.value = value, .kind = Semicolon, .line = line, .column = column};
  if (value == ":")
    return {.value = value, .kind = Colon, .line = line, .column = column};
  if (value == "=")
    return {.value = value, .kind = Assign, .line = line, .column = column};

  throw std::runtime_error("Invalid token: " + value);
}

} // namespace tokens
