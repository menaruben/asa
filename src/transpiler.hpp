#include "Tokens.hpp"
#include "instructions.hpp"
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "messages.hpp"

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

void parse_begin(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {

  index++; // skip begin
  string errmsg;
  Token current_block_tok = (*tokens)[index++];
  if (current_block_tok.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "block name identifier", token_kind_to_str(current_block_tok.kind),
      (*tokens)[--index].line);
    throw runtime_error(errmsg);
  }
  current_block = current_block_tok.value;
  (*program)[current_block] = Block();
  Token colonToken = (*tokens)[index];
  if (colonToken.kind != TokenKind::Colon) {
    errmsg = msgs::expected_but_got_at_line(
      "':' (colon)", colonToken.value,
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

void parse_push(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  string errmsg;
  if (current_block == "") {
    errmsg = msgs::expected_but_got_at_line(
      "block", "push",
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }

  index++; // skip push
  Token t = (*tokens)[index++];
  if (t.kind == TokenKind::Identifier) {
    (*program)[current_block].instructions.push_back(GET(t.value));
  } else {
    asa::Type type = token_kind_to_asatype(t.kind);
    (*program)[current_block].instructions.push_back(PUSH(t.value, type));
  }
  t = (*tokens)[index];
  if (t.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line_column(
      "';' (semicolon)", t.value,
      (*tokens)[index-1].line,
      (*tokens)[index-1].column + (*tokens)[index-1].value.size() 
      + (*tokens)[index-2].value.size() + 1 + 1
    );
    throw runtime_error(errmsg);
  }
}

void parse_pop(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  if (current_block == "") {
    throw runtime_error("Pop instruction must be inside a block!");
  }

  string errmsg;
  index++; // skip pop
  Token t = (*tokens)[index++];
  if (t.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "Identifier", token_kind_to_str(t.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  (*program)[current_block].instructions.push_back(SET(t.value));

  t = (*tokens)[index];
  if (t.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line(
      "';' (semicolon)", t.value,
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
}

void parse_label(int &index, vector<Token> *tokens, Program *program,
                 string &current_block) {
  if (current_block == "") {
    throw runtime_error("Label instruction must be inside a block!");
  }

  index++; // skip label
  string errmsg;
  Token labeltoken = (*tokens)[index++];
  if (labeltoken.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "Identifier", token_kind_to_str(labeltoken.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  Token semicolon = (*tokens)[index];
  if (semicolon.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line(
      "';' (semicolon)", token_kind_to_str(semicolon.kind),
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
  int pos = (*program)[current_block].instructions.size();
  (*program)[current_block].labels[labeltoken.value] = pos;
}

void parse_goto(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  if (current_block == "") {
    throw runtime_error("Goto instruction must be inside a block!");
  }

  index++; // skip goto
  string errmsg;
  Token t = (*tokens)[index++];
  if (t.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "Identifier", token_kind_to_str(t.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  (*program)[current_block].instructions.push_back(GOTO(t.value));
  t = (*tokens)[index];
  if (t.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line(
      "';' (semicolon)", token_kind_to_str(t.kind),
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

void parse_ifgoto(int &index, vector<Token> *tokens, Program *program,
                  string &current_block) {
  if (current_block == "") {
    throw runtime_error("IfGoto instruction must be inside a block!");
  }

  index++; // skip ifgoto
  string errmsg;
  Token expected = (*tokens)[index++];
  if (expected.kind != TokenKind::Integer) {
    errmsg = msgs::expected_but_got_at_line(
      "integer", token_kind_to_str(expected.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  if (expected.value != "-1" && expected.value != "0" &&
      expected.value != "1") {
    errmsg = msgs::expected_but_got_at_line(
      "-1, 0 or 1", expected.value,
      (*tokens)[index-1].line);    
    throw runtime_error(errmsg);
  }
  Token label = (*tokens)[index++];
  if (label.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "Identifier", token_kind_to_str(label.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  (*program)[current_block].instructions.push_back(
      IFGOTO(expected.value, label.value));
  Token t = (*tokens)[index];
  if (t.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line(
      "';' (semicolon)", token_kind_to_str(t.kind),
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

void parse_var(int &index, vector<Token> *tokens, Program *program,
               string &current_block) {
  if (current_block == "") {
    throw runtime_error("Var instruction must be inside a block!");
  }

  index++; // skip var
  string errmsg;
  Token id = (*tokens)[index++];
  if (id.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "Identifier", token_kind_to_str(id.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  Token value = (*tokens)[index++];
  (*program)[current_block].instructions.push_back(
      DEF(id.value, value.value, token_kind_to_asatype(value.kind)));
  Token t = (*tokens)[index];
  if (t.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line(
      "';' (semicolon)", token_kind_to_str(t.kind),
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

void parse_call(int &index, vector<Token> *tokens, Program *program,
                string &current_block) {
  if (current_block == "") {
    throw runtime_error("Call instruction must be inside a block!");
  }

  index++; // skip call
  string errmsg;
  Token t = (*tokens)[index++];
  if (t.kind != TokenKind::Identifier) {
    errmsg = msgs::expected_but_got_at_line(
      "Identifier", token_kind_to_str(t.kind),
      (*tokens)[index-1].line);
    throw runtime_error(errmsg);
  }
  (*program)[current_block].instructions.push_back(CALL(t.value));
  t = (*tokens)[index];
  if (t.kind != TokenKind::Semicolon) {
    errmsg = msgs::expected_but_got_at_line(
      "';' (semicolon)", token_kind_to_str(t.kind),
      (*tokens)[index].line);
    throw runtime_error(errmsg);
  }
}

Program load_program(vector<Token> tokens) {
  Program program;
  string current_block = "";

  for (int i = 0; i < tokens.size(); i++) {
    Token t = tokens[i];

    switch (t.kind) {
    case TokenKind::Begin: {
      parse_begin(i, &tokens, &program, current_block);
      break;
    }

    case TokenKind::Push: {
      parse_push(i, &tokens, &program, current_block);
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
          "';' (semicolon)", token_kind_to_str(sc.kind),
          tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Sub: {
      program[current_block].instructions.push_back(SUB);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
          "';' (semicolon)", token_kind_to_str(sc.kind),
          tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Mul: {
      program[current_block].instructions.push_back(MUL);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
          "';' (semicolon)", token_kind_to_str(sc.kind),
          tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Div: {
      program[current_block].instructions.push_back(DIV);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
          "';' (semicolon)", token_kind_to_str(sc.kind),
          tokens[i].line);
        throw runtime_error(errmsg);
      }
      break;
    }

    case TokenKind::Show: {
      program[current_block].instructions.push_back(SHOW);
      Token sc = tokens[++i];
      if (sc.kind != TokenKind::Semicolon) {
        string errmsg = msgs::expected_but_got_at_line(
          "';' (semicolon)", token_kind_to_str(sc.kind),
          tokens[i].line);
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
          "';' (semicolon)", token_kind_to_str(sc.kind),
          tokens[i].line);
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
        string errmsg = msgs::expected_but_got_at_line(
          "block", "end",
          tokens[i].line);
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
