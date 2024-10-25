```
  aaaaaaaaaaaaa      ssssssssss     aaaaaaaaaaaaa   
  a::::::::::::a   ss::::::::::s    a::::::::::::a  
  aaaaaaaaa:::::ass:::::::::::::s   aaaaaaaaa:::::a 
           a::::as::::::ssss:::::s           a::::a 
    aaaaaaa:::::a s:::::s  ssssss     aaaaaaa:::::a 
  aa::::::::::::a   s::::::s        aa::::::::::::a 
 a::::aaaa::::::a      s::::::s    a::::aaaa::::::a 
a::::a    a:::::assssss   s:::::s a::::a    a:::::a 
a::::a    a:::::as:::::ssss::::::sa::::a    a:::::a 
a:::::aaaa::::::as::::::::::::::s a:::::aaaa::::::a 
 a::::::::::aa:::as:::::::::::ss   a::::::::::aa:::a
  aaaaaaaaaa  aaaa sssssssssss      aaaaaaaaaa  aaaa
```

# Example
The following example evaluates the mathematical expression `1 - 3 * (5 / (6.9 + 42))`:
```cpp
#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

std::vector<instructions::Instruction> program = {
    PUSH("1", asa::AsaType::Double),
    PUSH("3", asa::AsaType::Double),
    PUSH("5", asa::AsaType::Double),
    PUSH("6.9", asa::AsaType::Double),
    PUSH("42", asa::AsaType::Double),
    SHOW,
    PLUS,
    SHOW,
    DIV,
    SHOW,
    MULT,
    SHOW,
    MINUS,
    SHOW
};

int main() {
  asa::AsaObj result = interpreter::eval(program);
  if (result.error != asa::AsaError::Ok) {
    std::cout << "Error encountered: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
```
This is evaluated to the following expression:
```asm
Stack:
    Value: 42, Type: Double
    Value: 6.9, Type: Double
    Value: 5, Type: Double
    Value: 3, Type: Double
    Value: 1, Type: Double

Stack:
    Value: 48.900000, Type: Double
    Value: 5, Type: Double
    Value: 3, Type: Double
    Value: 1, Type: Double

Stack:
    Value: 0.102249, Type: Double
    Value: 3, Type: Double
    Value: 1, Type: Double

Stack:
    Value: 0.306747, Type: Double
    Value: 1, Type: Double

Stack:
    Value: 0.693253, Type: Double
```
The result is `0.693252` and has the type `Double`

# Instructions
## PUSH
Pushes and element with the value `v` (as string) and type
`t` onto the stack

## Plus
Adds and pops the last two elements from the stack and
pushes the result to the stack

## Minus
Subtracts the last element from the second last element
and pushes the result to the stack

## Mult
Multiplies the last two elements from the stack and pushes 
the result to the stack.

## Div
Divides the second last element by the last element and pushes
the result to the stack

## Show
Prints the current state of the stack with the "newest" element
at the top. 

# Types
- Integer
- Double
- Float
- Boolean
- String
- Char
- Bool
