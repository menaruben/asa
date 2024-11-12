#include "Tokens.hpp"
#include <cctype>
#include <sstream>
#include <vector>

using namespace tokens;
using namespace std;

namespace lexer {

bool is_separator(char value) {
  return value == ',' || value == ':' || value == ';';
}

enum LexCtx { InString, Normal };

vector<Token> tokenize(string source) {
  vector<Token> tokens;
  stringstream current_token;
  LexCtx ctx = Normal;
  Token t;
  char ch;
  int line = 1;
  int column = 0;

  for (int i = 0; i < source.length(); i++) {
    ch = source[i];

    // special cases:
    if (ctx == Normal && current_token.str().length() == 0 && isspace(ch)) {
      if (ch == '\n') {
        line++;
        column = 1;
      } else {
        column++;
      }
      continue; // skip whitespace
    }

    if (ctx == InString && ch != '"') {
      current_token << ch;
      continue;
    }

    // handle double quotes:
    if (ch == '"') {
      if (ctx == Normal) {
        if (current_token.str().length() > 0) {
          t = token_from_str(current_token.str(), line, column);
          tokens.push_back(t);
          current_token.str("");
        }
        ctx = InString;
        current_token << ch;
        continue;
      }
      if (ctx == InString) {
        current_token << ch;
        t = token_from_str(current_token.str(), line, column);
        tokens.push_back(t);
        current_token.str(""); // clear stringstream
        ctx = Normal;
        continue;
      }
    }

    /* handle whitespace with non-empty
    stringstream in non-string context */
    if (isspace(ch)) {
      t = token_from_str(current_token.str(), line, column);
      tokens.push_back(t);
      current_token.str("");
      continue;
    }

    // handle symbols
    if (is_separator(ch)) {
      if (current_token.str().length() > 0) {
        t = token_from_str(current_token.str(), line, column);
        tokens.push_back(t);
        current_token.str("");
      }
      current_token << ch;
      if (ch == '=' && source[i + 1] == '=') {
        current_token << source[++i];
      }
      t = token_from_str(current_token.str(), line, column);
      tokens.push_back(t);
      current_token.str("");
      continue;
    }

    current_token << ch;
  }

  if (current_token.str().length() > 0) {
    t = token_from_str(current_token.str(), line, column);
    tokens.push_back(t);
  }
  tokens.push_back({.kind = EndOfFile, .line = line, .column = column});
  return tokens;
}
} // namespace lexer
