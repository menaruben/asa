#pragma once

#include "objects.hpp"
#include <regex>
#include <stdexcept>
#include <string>

namespace tokens {

enum TokenKind {
  Char,
  String,
  Str,
  Integer,
  BigInteger,
  Bool,
  Float,
  Double,
  BigDouble,
  Def,
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
  Increment,
  Decrement,
  Lshift,
  Rshift,
  Halt,
  GetType,
  Raise,
  Floor,
  Ceil,
  Round,
  EndOfFile,
};

std::string token_kind_to_str(TokenKind k) {
  switch (k) {
  case Char:        return "Char";
  case String:      return "String";
  case Str:         return "tostr";  // used for to_string
  case Integer:     return "Integer";
  case BigInteger:  return "BigInteger";
  case Bool:        return "Bool";
  case Float:       return "Float";
  case Double:      return "Double";
  case BigDouble:   return "BigDouble";
  case GetType:     return "GetType";
  case Def:         return "Def";
  case End:         return "End";
  case Goto:        return "Goto";
  case IfGoto:      return "IfGoto";
  case Label:       return "Label";
  case Comma:       return "Comma";
  case Semicolon:   return "Semicolon";
  case Colon:       return "Colon";
  case Add:         return "Add";
  case Sub:         return "Sub";
  case Mul:         return "Mul";
  case Div:         return "Div";
  case Assign:      return "Assign";
  case Cmp:         return "Cmp";
  case Show:        return "Show";
  case Var:         return "Var";
  case Identifier:  return "Identifier";
  case Push:        return "Push";
  case Pop:         return "Pop";
  case Println:     return "Println";
  case Print:       return "Print";
  case Call:        return "Call";
  case Import:      return "Import";
  case Increment:   return "Increment";
  case Decrement:   return "Decrement";
  case Halt:        return "Halt";
  case Raise:       return "Raise";
  case Floor:       return "Floor";
  case Ceil:        return "Ceil";
  case Round:       return "Round";
  case EndOfFile:   return "EndOfFile";
  default:          return "Unknown TokenKind";
  }
}

asa::Type token_kind_to_asatype(TokenKind k) {
  switch (k) {
  case Char:       return asa::Char;
  case String:     return asa::String;
  case Integer:    return asa::Integer;
  case BigInteger: return asa::BigInteger;
  case Bool:       return asa::Bool;
  case Float:      return asa::Float;
  case Double:     return asa::Double;
  case BigDouble:  return asa::BigDouble;
  default:         throw std::runtime_error(
                    "Can not convert " +
                    token_kind_to_str(k) + " token to type");
  }
}

struct Token {
  std::string value;
  TokenKind kind;
  int line;
  int column;
};

// literal patterns
const std::regex CHAR_PATTERN("^'.'");
const std::regex STRING_PATTERN("^\".*\"");
const std::regex INT_PATTERN("^[+-]?\\d+$");
const std::regex BIGINT_PATTERN("^[+-]?\\d+bi$");           // example: 123bi or -123bi or +123bi
const std::regex FLOAT_PATTERN("^[+-]?\\d*\\.\\d+f$");      // example: 0.325f or .45f ...
const std::regex DOUBLE_PATTERN("^[+-]?\\d*\\.\\d+$");      // example: 0.325  or .45 ...
const std::regex BIGDOUBLE_PATTERN("^[+-]?\\d*\\.\\d+bd$"); // example: 0.325bd  or .45bd ...
const std::regex BOOL_PATTERN("^(true|false)$");
const std::regex IDENTIFIER_PATTERN("^[a-zA-Z_][a-zA-Z0-9_/]*\\??$"); // allow ? as suffix and / for namespaces

// keyword patterns (case insensitive)
const std::regex DEF_PATTERN("^Def$", std::regex_constants::icase);
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
const std::regex LABEL_PATTERN("^Label$", std::regex_constants::icase);
const std::regex ADD_PATTERN("^Add$", std::regex_constants::icase);
const std::regex SUB_PATTERN("^Sub$", std::regex_constants::icase);
const std::regex MUL_PATTERN("^Mul$", std::regex_constants::icase);
const std::regex DIV_PATTERN("^Div$", std::regex_constants::icase);
const std::regex INCREMENT_PATTERN("^Incr$", std::regex_constants::icase);
const std::regex DECREMENT_PATTERN("^Decr$", std::regex_constants::icase);
const std::regex STR_PATTERN("^Str$", std::regex_constants::icase);
const std::regex LSHIFT_PATTERN("^Lshift$", std::regex_constants::icase);
const std::regex RSHIFT_PATTERN("^Rshift$", std::regex_constants::icase);
const std::regex GETTYPE_PATTERN("^Type$", std::regex_constants::icase);
const std::regex HALT_PATTERN("^Halt$", std::regex_constants::icase);
const std::regex RAISE_PATTERN("^Raise$", std::regex_constants::icase);
const std::regex ROUND_PATTERN("^Round$", std::regex_constants::icase);
const std::regex FLOOR_PATTERN("^Floor$", std::regex_constants::icase);
const std::regex CEIL_PATTERN("^Ceil$", std::regex_constants::icase);

Token token_from_str(std::string value, int line, int column) {
  if (std::regex_match(value, STRING_PATTERN))     return {.value = value.substr(1, value.size()-2),
                                                           .kind = String, .line = line, .column = column};

  // literals
  if (std::regex_match(value, INT_PATTERN))        return {.value = value, .kind = Integer, .line = line, .column = column};
  if (std::regex_match(value, BIGINT_PATTERN))     return {.value = value, .kind = BigInteger, .line = line, .column = column};
  if (std::regex_match(value, CHAR_PATTERN))       return {.value = value, .kind = Char, .line = line, .column = column};
  if (std::regex_match(value, FLOAT_PATTERN))      return {.value = value, .kind = Float, .line = line, .column = column};
  if (std::regex_match(value, BIGDOUBLE_PATTERN))  return {.value = value, .kind = BigDouble, .line = line, .column = column};
  if (std::regex_match(value, DOUBLE_PATTERN))     return {.value = value, .kind = Double, .line = line, .column = column};
  if (std::regex_match(value, BOOL_PATTERN))       return {.value = value, .kind = Bool, .line = line, .column = column};

  // keywords / instructions
  if (std::regex_match(value, DEF_PATTERN))        return {.value = value, .kind = Def, .line = line, .column = column};
  if (std::regex_match(value, END_PATTERN))        return {.value = value, .kind = End, .line = line, .column = column};
  if (std::regex_match(value, IMPORT_PATTERN))     return {.value = value, .kind = Import, .line = line, .column = column};
  if (std::regex_match(value, IFGOTO_PATTERN))     return {.value = value, .kind = IfGoto, .line = line, .column = column};
  if (std::regex_match(value, GOTO_PATTERN))       return {.value = value, .kind = Goto, .line = line, .column = column};
  if (std::regex_match(value, SHOW_PATTERN))       return {.value = value, .kind = Show, .line = line, .column = column};
  if (std::regex_match(value, VAR_PATTERN))        return {.value = value, .kind = Var, .line = line, .column = column};
  if (std::regex_match(value, PUSH_PATTERN))       return {.value = value, .kind = Push, .line = line, .column = column};
  if (std::regex_match(value, POP_PATTERN))        return {.value = value, .kind = Pop, .line = line, .column = column};
  if (std::regex_match(value, PRINTLN_PATTERN))    return {.value = value, .kind = Println, .line = line, .column = column};
  if (std::regex_match(value, PRINT_PATTERN))      return {.value = value, .kind = Print, .line = line, .column = column};
  if (std::regex_match(value, CALL_PATTERN))       return {.value = value, .kind = Call, .line = line, .column = column};
  if (std::regex_match(value, CMP_PATTERN))        return {.value = value, .kind = Cmp, .line = line, .column = column};
  if (std::regex_match(value, LABEL_PATTERN))      return {.value = value, .kind = Label, .line = line, .column = column};
  if (std::regex_match(value, ADD_PATTERN))        return {.value = value, .kind = Add, .line = line, .column = column};
  if (std::regex_match(value, SUB_PATTERN))        return {.value = value, .kind = Sub, .line = line, .column = column};
  if (std::regex_match(value, MUL_PATTERN))        return {.value = value, .kind = Mul, .line = line, .column = column};
  if (std::regex_match(value, DIV_PATTERN))        return {.value = value, .kind = Div, .line = line, .column = column};
  if (std::regex_match(value, INCREMENT_PATTERN))  return {.value = value, .kind = Increment, .line = line, .column = column};
  if (std::regex_match(value, DECREMENT_PATTERN))  return {.value = value, .kind = Decrement, .line = line, .column = column};
  if (std::regex_match(value, STR_PATTERN))        return {.value = value, .kind = Str, .line = line, .column = column};
  if (std::regex_match(value, LSHIFT_PATTERN))     return {.value = value, .kind = Lshift, .line = line, .column = column};
  if (std::regex_match(value, RSHIFT_PATTERN))     return {.value = value, .kind = Rshift, .line = line, .column = column};
  if (std::regex_match(value, GETTYPE_PATTERN))    return {.value = value, .kind = GetType, .line = line, .column = column};
  if (std::regex_match(value, HALT_PATTERN))       return {.value = value, .kind = Halt, .line = line, .column = column};
  if (std::regex_match(value, RAISE_PATTERN))      return {.value = value, .kind = Raise, .line = line, .column = column};
  if (std::regex_match(value, FLOOR_PATTERN))      return {.value = value, .kind = Floor, .line = line, .column = column};
  if (std::regex_match(value, CEIL_PATTERN))       return {.value = value, .kind = Ceil, .line = line, .column = column};
  if (std::regex_match(value, ROUND_PATTERN))      return {.value = value, .kind = Round, .line = line, .column = column};
  if (std::regex_match(value, IDENTIFIER_PATTERN)) return {.value = value, .kind = Identifier, .line = line, .column = column}; // must be last

  if (value == ",") return {.value = value, .kind = Comma, .line = line, .column = column};
  if (value == ";") return {.value = value, .kind = Semicolon, .line = line, .column = column};
  if (value == ":") return {.value = value, .kind = Colon, .line = line, .column = column};
  if (value == "=") return {.value = value, .kind = Assign, .line = line, .column = column};
  throw std::runtime_error("Invalid token: " + value);
}
} // namespace tokens
