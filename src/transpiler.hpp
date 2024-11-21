#include "AsaBigDouble.hpp"
#include "AsaBigInteger.hpp"
#include "AsaDouble.hpp"
#include "AsaFloat.hpp"
#include "AsaInteger.hpp"
#include "AsaObject.hpp"
#include "AsaString.hpp"
#include "Lexer.hpp"
#include "Tokens.hpp"
#include "fileread.hpp"
#include "instructions.hpp"
#include "messages.hpp"
#include "objects.hpp"
#include <cstddef>
#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace std;
using namespace tokens;

#define SINGLE_LINE_COMMENT "//"

namespace transpiler {
string trim(const string &str) {
  size_t start = str.find_first_not_of(" \t");
  return (start == string::npos) ? "" : str.substr(start);
}

vector<string> splitStr(const string &str, char delimiter) {
  vector<string> tokens;
  stringstream ss(str);
  string token;
  while (getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

struct Block {
  vector<Instruction> instructions;
  unordered_map<string, int> labels;
};
typedef unordered_map<string, Block> Program;

void check_expected(TokenKind expected, TokenKind got, int line) {
  if (expected != got) {
    string errmsg = msgs::expected_but_got_at_line(
        token_kind_to_str(expected), token_kind_to_str(got), line);
    throw runtime_error(errmsg);
  }
}

void check_current_block(string current_block, TokenKind got, int line) {
  if (current_block == "") {
    string errmsg =
        msgs::expected_but_got_at_line("block", token_kind_to_str(got), line);
    throw runtime_error(errmsg);
  }
}

// Forward declaration of load_program
Program load_program(vector<Token> tokens);

// Forward declaration of parse_import
void parse_import(int &index, vector<Token> *tokens, Program *program,
                  string &current_block);

bool has_namespace(const string &blockname) {
  return blockname.find('/') != string::npos;
}

void parse_import(int &index, vector<Token> *tokens, Program *program,
                  string &current_block) {
  index++; // skip import
  string errmsg;
  Token filepath = (*tokens)[index++];
  if (filepath.kind != TokenKind::String) {
    errmsg = msgs::expected_but_got_at_line(
        "string", token_kind_to_str(filepath.kind), (*tokens)[index - 1].line);
    throw runtime_error(errmsg);
  }
  string path = filepath.value;
  // first search in current dir and then in stdlib dir!
  string source;
  if (path.find("/") == std::string::npos) {
    string currentdir_path = "./" + path;
    if (std::filesystem::exists(currentdir_path)) {
      source = read_file(currentdir_path, SINGLE_LINE_COMMENT);
    } else {
      string stdlibdir_path = "/lib/asa/" + path;
      if (!std::filesystem::exists(stdlibdir_path))
        throw runtime_error("File not found: Can not import " + path);
      source = read_file(stdlibdir_path, SINGLE_LINE_COMMENT);
    }
  } else {
    if (!std::filesystem::exists(path))
      throw runtime_error("File not found: Can not import " + path);
    source = read_file(path, SINGLE_LINE_COMMENT);
  }

  vector<Token> importedtoks = lexer::tokenize(source);
  Program imported = load_program(importedtoks);

  string namespaceid = path.substr(0, path.find(".asa"));
  for (auto &block : imported) {
    string blockname = block.first;
    // if namespace not there, add one depending on name of file
    if (!has_namespace(blockname)) {
      blockname = namespaceid + "/" + blockname;
    }
    (*program)[blockname] = block.second;
  }
  Token semicolon = (*tokens)[index];
  if (semicolon.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line("';' (semicolon)",
                                            token_kind_to_str(semicolon.kind),
                                            (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

void parse_def(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  index++; // skip def
  string errmsg;
  Token current_block_tok = (*tokens)[index++];
  check_expected(TokenKind::Identifier, current_block_tok.kind,
                 (*tokens)[index - 1].line);
  current_block = current_block_tok.value;
  (*program)[current_block] = Block();
  Token colonToken = (*tokens)[index];
  check_expected(TokenKind::Colon, colonToken.kind, colonToken.line);
}

void parse_push(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  check_current_block(current_block, TokenKind::Push, (*tokens)[index].line);
  index++; // skip push
  Token id_tok = (*tokens)[index++];
  if (id_tok.kind == TokenKind::Identifier) {
    (*program)[current_block].instructions.push_back(GET(id_tok.value));
  } else {
    try {
      asa::Type type = token_kind_to_asatype(id_tok.kind);
      switch (type) {

      case asa::Integer: {
        AsaInteger o = AsaInteger(stoi(id_tok.value));
        (*program)[current_block].instructions.push_back(PUSH(o));
        break;
      }

      case asa::BigInteger: {
        AsaBigInteger o = AsaBigInteger(stoll(id_tok.value));
        (*program)[current_block].instructions.push_back(PUSH(o));
        break;
      }

      case asa::Float: {
        AsaFloat o = AsaFloat(stof(id_tok.value));
        (*program)[current_block].instructions.push_back(PUSH(o));
        break;
      }

      case asa::Double: {
        AsaDouble o = AsaDouble(stod(id_tok.value));
        (*program)[current_block].instructions.push_back(PUSH(o));
        break;
      }

      case asa::BigDouble: {
        AsaBigDouble o = AsaBigDouble(stold(id_tok.value));
        (*program)[current_block].instructions.push_back(PUSH(o));
        break;
      }

      case asa::String: {
        AsaString o = AsaString(id_tok.value);
        (*program)[current_block].instructions.push_back(PUSH(o));
        break;
      }

      default:
        throw runtime_error("Not Implemented: push for asa type " +
                            type_to_str(type));
      }

    } catch (runtime_error e) {
      string errmsg = string(e.what()) + ", at ";
      errmsg += to_string(id_tok.line) + ", in block " + current_block + '\n' +
                e.what();
      throw runtime_error(errmsg);
    }
  }
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_str(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  check_current_block(current_block, TokenKind::Str, (*tokens)[index].line);
  index++;
  (*program)[current_block].instructions.push_back(STR);
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_incr(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  check_current_block(current_block, TokenKind::Increment,
                      (*tokens)[index].line);
  index++; // skip incr
  Token id_token = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id_token.kind, id_token.line);
  (*program)[current_block].instructions.push_back(INCREMENT(id_token.value));
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_decr(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  check_current_block(current_block, TokenKind::Decrement,
                      (*tokens)[index].line);
  index++; // skip decr
  Token id_token = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id_token.kind, id_token.line);
  (*program)[current_block].instructions.push_back(DECREMENT(id_token.value));
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_pop(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  check_current_block(current_block, TokenKind::Pop, (*tokens)[index].line);
  index++; // skip pop
  Token id_tok = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id_tok.kind, id_tok.line);
  (*program)[current_block].instructions.push_back(SET(id_tok.value));
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.column);
}

void parse_label(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {
  check_current_block(current_block, TokenKind::Label, (*tokens)[index].line);
  index++; // skip label
  Token labeltoken = (*tokens)[index++];
  check_expected(TokenKind::Identifier, labeltoken.kind, labeltoken.line);
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
  int pos = (*program)[current_block].instructions.size();
  (*program)[current_block].labels[labeltoken.value] = pos;
}

void parse_goto(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  check_current_block(current_block, TokenKind::Goto, (*tokens)[index].line);
  index++; // skip goto
  Token id_tok = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id_tok.kind, id_tok.line);
  (*program)[current_block].instructions.push_back(GOTO(id_tok.value));
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_ifgoto(int &index, vector<Token> *tokens, Program *program,
                  string &current_block) {
  check_current_block(current_block, TokenKind::IfGoto, (*tokens)[index].line);
  index++; // skip ifgoto
  Token expected = (*tokens)[index++];
  check_expected(TokenKind::Integer, expected.kind, expected.line);
  if (expected.value != "-1" && expected.value != "0" &&
      expected.value != "1") {
    string errmsg = msgs::expected_but_got_at_line("-1, 0 or 1", expected.value,
                                                   expected.line);
    throw runtime_error(errmsg);
  }
  Token label_id = (*tokens)[index++];
  check_expected(TokenKind::Identifier, label_id.kind, label_id.line);

  asa::Type expected_t = token_kind_to_asatype(expected.kind);
  try {
    switch (expected_t) {
    case asa::Integer: {
      AsaInteger o = AsaInteger(stoi(expected.value));
      (*program)[current_block].instructions.push_back(
          IFGOTO(o, label_id.value));
      break;
    }

    case asa::BigInteger: {
      AsaBigInteger o = AsaBigInteger(stoll(expected.value));
      (*program)[current_block].instructions.push_back(
          IFGOTO(o, label_id.value));
      break;
    }

    case asa::Float: {
      AsaFloat o = AsaFloat(stof(expected.value));
      (*program)[current_block].instructions.push_back(
          IFGOTO(o, label_id.value));
      break;
    }

    case asa::Double: {
      AsaDouble o = AsaDouble(stod(expected.value));
      (*program)[current_block].instructions.push_back(
          IFGOTO(o, label_id.value));
      break;
    }

    case asa::BigDouble: {
      AsaBigDouble o = AsaBigDouble(stold(expected.value));
      (*program)[current_block].instructions.push_back(
          IFGOTO(o, label_id.value));
      break;
    }

    case asa::String: {
      AsaString o = AsaString(expected.value);
      (*program)[current_block].instructions.push_back(
          IFGOTO(o, label_id.value));
      break;
    }

    default:
      throw runtime_error("Not Implemented: ifgoto for type " +
                          type_to_str(expected_t));
    }
  } catch (runtime_error e) {
    throw runtime_error("Error in ifgoto: " + string(e.what()));
  }

  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_var(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  check_current_block(current_block, TokenKind::Var, (*tokens)[index].line);
  index++; // skip var
  Token id = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id.kind, id.line);
  Token value = (*tokens)[index++];

  try {
    asa::Type type = token_kind_to_asatype(value.kind);
    switch (type) {

    case asa::Integer: {
      AsaInteger o = AsaInteger(stoi(value.value));
      (*program)[current_block].instructions.push_back(DEF(id.value, o));
    }

    case asa::BigInteger: {
      AsaBigInteger o = AsaBigInteger(stoll(value.value));
      (*program)[current_block].instructions.push_back(DEF(id.value, o));
    }

    case asa::Float: {
      AsaFloat o = AsaFloat(stof(id.value));
      (*program)[current_block].instructions.push_back(DEF(id.value, o));
    }

    case asa::Double: {
      AsaDouble o = AsaDouble(stod(id.value));
      (*program)[current_block].instructions.push_back(DEF(id.value, o));
    }
    
    case asa::BigDouble: {
      AsaBigDouble o = AsaBigDouble(stold(value.value));
      (*program)[current_block].instructions.push_back(DEF(id.value, o));
    }
    
    case asa::String: {
      AsaString o = AsaString(id.value);
      (*program)[current_block].instructions.push_back(DEF(id.value, o));
    }
    default:
      throw runtime_error("Not Implemented");
    }
  } catch (runtime_error e) {
    string errmsg = string(e.what()) + ", at ";
    errmsg += to_string(value.line) + ", in block " + current_block + '\n';
    throw runtime_error(errmsg);
  }

  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_call(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  check_current_block(current_block, TokenKind::Call, (*tokens)[index].line);
  index++; // skip call
  Token id_tok = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id_tok.kind, id_tok.line);
  (*program)[current_block].instructions.push_back(CALL(id_tok.value));
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_raise(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {
  check_current_block(current_block, TokenKind::Call, (*tokens)[index].line);
  index++; // skip raise
  (*program)[current_block].instructions.push_back(RAISE);
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_floor(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {
  check_current_block(current_block, TokenKind::Floor, (*tokens)[index].line);
  index++; // skip floor
  (*program)[current_block].instructions.push_back(FLOOR);
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_ceil(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  check_current_block(current_block, TokenKind::Ceil, (*tokens)[index].line);
  index++; // skip ceil
  (*program)[current_block].instructions.push_back(CEIL);
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_round(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {
  check_current_block(current_block, TokenKind::Round, (*tokens)[index].line);
  index++; // skip round
  (*program)[current_block].instructions.push_back(ROUND);
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

Program load_program(vector<Token> tokens) {
  Program program;
  string current_block = "";

  for (int i = 0; i < tokens.size(); i++) {
    Token t = tokens[i];

    switch (t.kind) {
    case TokenKind::Import: {
      parse_import(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Def: {
      parse_def(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Push: {
      parse_push(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Str: {
      parse_str(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Increment: {
      parse_incr(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Decrement: {
      parse_decr(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Var: {
      parse_var(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Pop: {
      parse_pop(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Label: {
      parse_label(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Raise: {
      parse_raise(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Add: {
      program[current_block].instructions.push_back(ADD);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Sub: {
      program[current_block].instructions.push_back(SUB);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Mul: {
      program[current_block].instructions.push_back(MUL);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Div: {
      program[current_block].instructions.push_back(DIV);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Lshift: {
      program[current_block].instructions.push_back(LSHIFT);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Rshift: {
      program[current_block].instructions.push_back(RSHIFT);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Ceil: {
      parse_ceil(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Floor: {
      parse_floor(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Round: {
      parse_round(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::GetType: {
      program[current_block].instructions.push_back(GETTYPE);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Halt: {
      program[current_block].instructions.push_back(HALT);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Show: {
      program[current_block].instructions.push_back(SHOW);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Print: {
      program[current_block].instructions.push_back(PRINT);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Println: {
      program[current_block].instructions.push_back(PRINTLN);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::Goto: {
      parse_goto(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Cmp: {
      program[current_block].instructions.push_back(CMP);
      Token sc = tokens[++i];
      check_expected(TokenKind::Semicolon, sc.kind, sc.line);
      break;
    }

    case TokenKind::IfGoto: {
      parse_ifgoto(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Call: {
      parse_call(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Identifier: {
      check_current_block(current_block, TokenKind::Identifier, t.line);
      throw runtime_error("Unexpected identifier: " + t.value + " in block " +
                          current_block);
    }

    case TokenKind::End: {
      if (current_block == "") {
        string errmsg =
            msgs::expected_but_got_at_line("block", "end", tokens[i].line);
        throw runtime_error(errmsg);
      }
      current_block = "";
      break;
    }

    case TokenKind::EndOfFile: {
      break;
    }

    default:
      throw runtime_error("Unsupported token kind: " +
                          token_kind_to_str(t.kind));
    }
  }
  return program;
}
} // namespace transpiler
