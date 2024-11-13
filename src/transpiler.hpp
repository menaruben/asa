#include "Tokens.hpp"
#include "Lexer.hpp"
#include "instructions.hpp"
#include "fileread.hpp"
#include "messages.hpp"
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace std;
using namespace tokens;

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
      token_kind_to_str(expected), 
      token_kind_to_str(got), line);
    throw runtime_error(errmsg);
  }
}

void check_current_block(string current_block, TokenKind got, int line) {
  if (current_block == "") {
    string errmsg = msgs::expected_but_got_at_line(
      "block", token_kind_to_str(got), line);
    throw runtime_error(errmsg);
  }
}

// Forward declaration of load_program
Program load_program(vector<Token> tokens);

// Forward declaration of parse_import
void parse_import(int &index, vector<Token> *tokens, Program *program, string &current_block);

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
        "string", token_kind_to_str(filepath.kind), 
        (*tokens)[index - 1].line);
    throw runtime_error(errmsg);
  }
  string path = filepath.value.substr(1, filepath.value.size() - 2);
  string source = read_file(path, "//");
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
    errmsg = msgs::expected_but_got_at_line(
        "';' (semicolon)", token_kind_to_str(semicolon.kind), 
        (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

void parse_begin(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {
  index++; // skip begin
  string errmsg;
  Token current_block_tok = (*tokens)[index++];
  check_expected(TokenKind::Identifier, current_block_tok.kind, (*tokens)[index-1].line);
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
    asa::Type type = token_kind_to_asatype(id_tok.kind);
    (*program)[current_block].instructions.push_back(PUSH(id_tok.value, type));
  }
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}


void parse_incr(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  check_current_block(current_block, TokenKind::Increment, (*tokens)[index].line);
  index++; // skip incr
  Token id_token = (*tokens)[index++];
  check_expected(TokenKind::Identifier, id_token.kind, id_token.line);
  (*program)[current_block].instructions.push_back(INCREMENT(id_token.value));
  Token sc = (*tokens)[index];
  check_expected(TokenKind::Semicolon, sc.kind, sc.line);
}

void parse_decr(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  check_current_block(current_block, TokenKind::Decrement, (*tokens)[index].line);
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
  Token expected_num = (*tokens)[index++];
  check_expected(TokenKind::Integer, expected_num.kind, expected_num.line);
  if (expected_num.value != "-1" && 
      expected_num.value != "0" &&
      expected_num.value != "1") {
    string errmsg = msgs::expected_but_got_at_line(
      "-1, 0 or 1", expected_num.value, expected_num.line);
    throw runtime_error(errmsg);
  }
  Token label_id = (*tokens)[index++];
  check_expected(TokenKind::Identifier, label_id.kind, label_id.line);
  (*program)[current_block].instructions.push_back(
      IFGOTO(expected_num.value, label_id.value));
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
  (*program)[current_block].instructions.push_back(
      DEF(id.value, value.value, token_kind_to_asatype(value.kind)));
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
      
    case TokenKind::Begin: {
      parse_begin(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Push: {
      parse_push(i, &tokens, &program, current_block);
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

    case TokenKind::Add: {
      program[current_block].instructions.push_back(ADD);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Sub: {
      program[current_block].instructions.push_back(SUB);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Mul: {
      program[current_block].instructions.push_back(MUL);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Div: {
      program[current_block].instructions.push_back(DIV);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Show: {
      program[current_block].instructions.push_back(SHOW);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Print: {
      program[current_block].instructions.push_back(PRINT);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Println: {
      program[current_block].instructions.push_back(PRINTLN);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Goto: {
      parse_goto(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Cmp: {
      program[current_block].instructions.push_back(CMP);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
            "';' (semicolon)", token_kind_to_str(sc.kind), tokens[i].line);
        throw runtime_error(errmsg);
      }
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
      if (current_block == "") {
        throw runtime_error("Unexpected identifier: " + t.value);
      }
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
