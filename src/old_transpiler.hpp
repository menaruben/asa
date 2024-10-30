#include "instructions.hpp"
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;

namespace trash_transpiler {
std::string trim(const std::string &str) {
  size_t start = str.find_first_not_of(" \t");
  return (start == std::string::npos) ? "" : str.substr(start);
}

std::vector<std::string> splitStr(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

void parseCmp(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = InstructionKind::Cmp});
}

void parseHalt(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() > 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = InstructionKind::Halt});
}

void parseShow(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() > 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = InstructionKind::Show});
}

void parseClear(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() > 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = InstructionKind::Clear});
}

void parseGoto(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = InstructionKind::Goto, .id = id});
}

void parseDef(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 4)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  std::string val = instParts[2];
  asa::Type type = asa::strToType(instParts[3]);
  program[ctx].push_back({.kind = instructions::DefVar,
                          .operand = {.value = val, .type = type},
                          .id = id});
}

void parseSet(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = instructions::SetVar, .id = id});
}

void parseLabel(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = instructions::Label, .id = id});
}

void parseGet(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = instructions::GetVar, .id = id});
}

void parseAdd(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = instructions::Add});
}

void parseSub(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = instructions::Subtract});
}

void parseMul(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = instructions::Multiply});
}

void parseDiv(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 1)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  program[ctx].push_back({.kind = instructions::Divide});
}

void parseIncr(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {

  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = instructions::Increment, .id = id});
}

void parseDecr(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = instructions::Decrement, .id = id});
}

void parseIfGoto(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 7)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string lhs = instParts[1];
  std::string cmpop = instParts[2];
  std::string rhs = instParts[3];
  std::string label = instParts[6];
  std::string ifval;

  if (cmpop == "<")
    ifval = "-1";
  else if (cmpop == "==")
    ifval = "0";
  else if (cmpop == ">")
    ifval = "1";
  else
    throw std::runtime_error("Invalid compare operator: " + cmpop +
                             " at line: " + std::to_string(linenum));

  program[ctx].push_back({.kind = InstructionKind::GetVar, .id = lhs});
  program[ctx].push_back({.kind = InstructionKind::GetVar, .id = rhs});
  program[ctx].push_back({.kind = InstructionKind::Cmp});
  program[ctx].push_back({
      .kind = InstructionKind::IfGoto,
      .operand = {.value = ifval, .type = asa::Integer},
      .id = label,
  });
}

void parseIf(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() < 7)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string lhs = instParts[1];
  std::string cmpop = instParts[2];
  std::string rhs = instParts[3];
  std::string ifval;

  if (cmpop == "<")
    ifval = "-1";
  else if (cmpop == "==")
    ifval = "0";
  else if (cmpop == ">")
    ifval = "1";
  else
    throw std::runtime_error("Invalid compare operator: " + cmpop +
                             " at line: " + std::to_string(linenum));
  // TODO: implement
  throw std::runtime_error("Not implemented yet, somehow need to identify block correctly... !");

  std::vector<Instruction> block;
  program[ctx].push_back({
      .kind = InstructionKind::If,
      .operand = {.value = ifval, .type = asa::Integer},
      .id = "",
      .block = block,
  });
}

void parseIfHalt(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  std::string lhs = instParts[1];
  std::string cmpop = instParts[2];
  std::string rhs = instParts[3];
  std::string ifval;

  if (cmpop == "<")
    ifval = "-1";
  else if (cmpop == "==")
    ifval = "0";
  else if (cmpop == ">")
    ifval = "1";
  else
    throw std::runtime_error("Invalid compare operator: " + cmpop +
                             " at line " + std::to_string(linenum));

  program[ctx].push_back({.kind = InstructionKind::GetVar, .id = lhs});
  program[ctx].push_back({.kind = InstructionKind::GetVar, .id = rhs});
  program[ctx].push_back({.kind = InstructionKind::Cmp});
  program[ctx].push_back({
      .kind = InstructionKind::IfHalt,
      .operand = {.value = ifval, .type = asa::Integer},
  });
}

void parseCall(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 2)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));
  std::string id = instParts[1];
  program[ctx].push_back({.kind = InstructionKind::Call, .id = id});
}

void parsePush(
    std::vector<std::string> instParts, int linenum,
    std::unordered_map<std::string, std::vector<Instruction>> &program,
    std::string ctx) {
  if (instParts.size() != 3)
    throw std::runtime_error("Invalid amount of arguments at line: " +
                             std::to_string(linenum));

  std::string val = instParts[1];
  asa::Type type = asa::strToType(instParts[2]);
  program[ctx].push_back(
      {.kind = InstructionKind::Push, .operand = {.value = val, .type = type}});
}

std::unordered_map<std::string, std::vector<Instruction>>
loadProgramFromMemory(std::string source) {
  std::unordered_map<std::string, std::vector<Instruction>> program;
  std::vector<std::string> lines = splitStr(source, '\n');
  int linenum = 1;
  std::vector<std::string> ctx;
  int depth = 0;

  for (std::string line : lines) {
    // to support indentation (optional)
    line = trim(line);
    // to support multiple instructions in one line separated by ';'
    std::vector<std::string> lines = splitStr(line, ';');

    for (std::string inststr : lines) {
      inststr = trim(inststr);
      std::vector<std::string> instParts = splitStr(inststr, ' ');
      if (instParts.size() < 1)
        continue;
      std::string instkw = instParts[0];
      Instruction inst;

      if (instkw == "BEGIN") {
        if (instParts.size() < 2)
          throw std::runtime_error(
              "No name for beginning block defined at line " +
              std::to_string(linenum));
        ctx[depth++] = instParts[1];
        linenum++;
        continue;
      }

      if (ctx[depth] == "")
        throw std::runtime_error(
            "Instructions must be inside a block, line: " +
            std::to_string(linenum));

      if (instkw == "SHOW") {
        parseShow(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "DEF") {
        parseDef(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "SET") {
        parseSet(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "LABEL") {
        parseLabel(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "GET") {
        parseGet(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "ADD") {
        parseAdd(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "SUB") {
        parseSub(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "MUL") {
        parseMul(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "DIV") {
        parseDiv(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "HALT") {
        parseHalt(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "CLEAR") {
        parseClear(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "GOTO") {
        parseGoto(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "INCR") {
        parseIncr(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "DECR") {
        parseDecr(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "IF") {
        // if must be inside a begin...end block => therefore depth must be atleast 1
        if (depth < 1) throw std::runtime_error(
          "Unexpected IF at line: " + std::to_string(linenum) + " (IF must be inside a BEGIN...END block)"); 
        
        ctx[depth++] = "if"; 
        parseIf(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "ENDIF") {
        if (ctx[depth] != "if")
          throw std::runtime_error("Unexpected ENDIF at line: " + std::to_string(linenum));

        if (instParts.size() != 1)
          throw std::runtime_error("Invalid amount of arguments at line: " + std::to_string(linenum));
        
        ctx.pop_back();
        depth--;
        linenum++;
        continue;
      }

      if (instkw == "END") {
        if (instParts.size() != 1)
          throw std::runtime_error("Invalid amount of arguments at line: " + std::to_string(linenum));
        
        ctx.pop_back();
        depth--;
        linenum++;
        continue;
      }

      if (instkw == "PUSH") {
        parsePush(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "CALL") {
        parseCall(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }

      if (instkw == "CMP") {
        parseCmp(instParts, linenum, program, ctx[depth]);
        linenum++;
        continue;
      }
    }
  }
  return program;
}
} // namespace transpiler
