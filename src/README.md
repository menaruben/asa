# Adding a new instruction
## Create new `TokenKind` (in order to be recognized by the lexer)
- 1. Open [Tokens.hpp](./Tokens.hpp)
- 2. Add a new value to the enum `TokenKind`
- 3. Add a new case for the TokenKind in the function `string token_kind_to_str(TokenKind k)`
- 4. Create a new regex pattern for the new token.
```cpp
const std::regex INCREMENT_PATTERN("^Incr$", std::regex_constants::icase);
```
- 5. Go to the `Token token_from_str(std::string value, int line, int column)` function and
add a new case for the token (usually above the `IDENTIFIER_PATTERN` unless it is a single symbol).

## Add new `InstructionKind`
- 1. Open [instructions.hpp](./instructions.hpp)
- 2. Add a new value to the enum `InstructionKind`
- 3. Define a new macro at the top of the file. Example:
```cpp
#define DEF(name, val, t)                                                      \
  {                                                                            \
    .kind = InstructionKind::DefVar, .operand = {.value = val, .type = t},     \
    .id = name,                                                                \
  }
```
Keep in mind that instructions are defined as the following:
```cpp
struct Instruction {
  InstructionKind kind;
  asa::Object operand;
  std::string id;
  std::vector<Instruction> block;
};
```

- 4. Define a new function for the instruction.

## Add parsing to transpiler
- 1. Open [transpiler.hpp](./transpiler.hpp)
- 2. Go to the `Program load_program(vector<Token> tokens)` function
- 3. Add a new case for the newly defined `TokenKind` and implement its parsing in a
`parse_<instructionname>(int &index, vector<Token> *tokens, Program *program, string &current_block)` function.

## Add case to interpreter
- 1. Open [interpreter.hpp](./interpreter.hpp)
- 2. Go to the `asa::Object eval(Program program, string entryPoint, list<asa::Object> *stack) ` function
- 3. Add a new case for the newly created `InstructionKind`, pop any arguments from the stack with `pop_args` and call the
function you created defined in [instructions.hpp](./instructions.hpp).
- 4. done! :) you just created a new instruction for asa!

If you have any questions just open a new issue and I'll be happy to help!
