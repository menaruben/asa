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

```cpp
#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

int main() {
  std::unordered_map<std::string, std::vector<Instruction>> program;
  // add program entry point
  program["main"] = {
      PUSH("10", Integer),
      CALL("factorial"),
      SHOW,
  };

  // custom function "factorial"
  program["factorial"] = {
      DEF("n", "0", Integer), // define n
      SET("n"),             // set n to top of stack
      DEF("ans", "1", Integer), DEF("i", "1", Integer),

      LABEL("fact"),
        // compute: ans = ans * i
        GET("ans"), GET("i"), MUL, SET("ans"),
        
        // increment i
        INCR("i"),

        // if i <= n then loop again...
        GET("i"), GET("n"), CMP, IFGOTO("-1", "fact"),
        GET("i"), GET("n"), CMP, IFGOTO("0", "fact"),

      // else push ans to stack
      GET("ans"),
  };

  std::list<asa::Object> stack;
  Object result = eval(program, "main", &stack);
  if (result.error != Ok) {
    std::cout << "[ERROR]: " << result.value << std::endl;
    return -1;
  }
  return 0;
}
```
```asm
Stack:
    Value: 3628800, Type: Integer
```
As we can see the function above returns the factorial of 10!
