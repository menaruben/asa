#include "Tokens.hpp"
#include <cctype>
#include <sstream>
#include <vector>

using namespace tokens;

namespace lexer {

bool isSymbol(char value) {
  return value == '+' || value == '-' || value == '*' || value == '/' ||
         value == ',' || value == ':' || value == ';' || value == '<' ||
         value == '=';
}

enum LexCtx { InString, Normal };

std::vector<Token> tokenize(std::string source) {
  std::vector<Token> tokens;
  std::stringstream currentToken;
  LexCtx ctx = Normal;
  Token t;
  char ch;
  
  for (int i = 0; i < source.length(); i++) {
    ch = source[i];
    
    // special cases:
    if (ctx == Normal && currentToken.str().length() == 0 && isspace(ch))
      continue; // skip whitespace

    if (ctx == InString && ch != '"') {
      currentToken << ch;
      continue;
    }

    // handle double quotes:
    if (ch == '"') {
      if (ctx == Normal) {
        if (currentToken.str().length() > 0) {
          t = tokenFromStr(currentToken.str());
          tokens.push_back(t);
          currentToken.str("");
        }
        ctx = InString;
        currentToken << ch;
        continue;
      }
      if (ctx == InString) {
        currentToken << ch;
        t = tokenFromStr(currentToken.str());
        tokens.push_back(t);
        currentToken.str(""); // clear stringstream
        ctx = Normal;
        continue;
      }
    }

    /* handle whitespace with non-empty
    stringstream in non-string context */
    if (isspace(ch)) {
      t = tokenFromStr(currentToken.str());
      tokens.push_back(t);
      currentToken.str("");
      continue;
    }
    
    // handle symbols
    if (isSymbol(ch)) {
      if (currentToken.str().length() > 0) {
        t = tokenFromStr(currentToken.str());
        tokens.push_back(t);
        currentToken.str("");
      }
      currentToken << ch;
      if (ch == '=' && source[i+1] == '=') {
        currentToken << source[++i];
      } 
      t = tokenFromStr(currentToken.str());
      tokens.push_back(t);
      currentToken.str("");
      continue;
    }

    currentToken << ch;
  }

  if (currentToken.str().length() > 0) {
    t = tokenFromStr(currentToken.str());
    tokens.push_back(t);
  }
  
  return tokens;
}
} // namespace lexer
