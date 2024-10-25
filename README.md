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
The following example evaluates the mathematical expression `3 * (5 / (6.9 + 42))`:
```cpp
#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

std::vector<instructions::Instruction> program = {
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
