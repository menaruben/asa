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

# Examples
## Conditions
This example showcases the use of conditions and comparisons...
```cpp


#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {
  // define variable "remaining" with 
  // initial value 4 and type Integer
  DEF("remaining", "4", Integer),
  
  // create a label to simulate loop in a goto style
  LABEL("loop"),
    PUSH("1", Integer),
    
    // decrement remaining variable my one
    GET("remaining"),
    PUSH("1", Integer),
    MINUS,
    SET("remaining"),
    
    // check if remaining is 0
    GET("remaining"),
    PUSH("0", Integer),
    CMP,
  // if remaining > 0  then it pushes  1 onto the stack
  // if remaining == 0 then it pushes  0 onto the stack
  // if remaining < 0  then it pushes -1 onto the stack
  IF("1", "loop"),
  
  // else show the stack
  PUSH("done!", String),
  SHOW,
};

int main() {
  Object result = eval(program);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
```
The above code evaluates to the following:
```asm
Stack:
    Value: done!, Type: String
    Value: 1, Type: Integer
    Value: 1, Type: Integer
    Value: 1, Type: Integer
    Value: 1, Type: Integer
```

## Math
The following example evaluates the mathematical expression `1 - 3 * (5 / (6.9 + 42))`:
```cpp
#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {PUSH("1", asa::Double),
                                    PUSH("3", asa::Double),
                                    PUSH("5", asa::Double),
                                    PUSH("6.9", asa::Double),
                                    PUSH("42", asa::Double),
                                    SHOW,
                                    PLUS,
                                    SHOW,
                                    DIV,
                                    SHOW,
                                    MULT,
                                    SHOW,
                                    MINUS,
                                    SHOW};

int main() {
  Object result = eval(program);
  if (result.error != Ok) {
    std::cout << "Error encountered: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
```
This is evaluated as the following:
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

# Documentation
> work in progress :)

## Instruction
docs coming soon... :)
