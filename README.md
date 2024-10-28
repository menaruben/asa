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
## Factorial
```cpp

#include "interpreter.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace instructions;
using namespace asa;
using namespace interpreter;

std::vector<Instruction> program = {
  DEF("n", "10", Integer),
  DEF("ans", "1", Integer),
  
  DEF("i", "1", Integer),
  LABEL("factorial"),
    // push current ans to stack
    GET("ans"),
  
    // calculate ans = ans * i
    GET("ans"),
    GET("i"),
    MUL,
    SET("ans"),

    // increment i
    INCR("i"),
    
    // check if i < n 
    GET("i"),
    GET("n"),
    CMP,
    IFGOTO("-1", "factorial"),
    // check if i == n 
    GET("i"),
    GET("n"),
    CMP,
    IFGOTO("0", "factorial"),
  
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
```asm
Stack:
    Value: 362880, Type: Integer
    Value: 40320, Type: Integer
    Value: 5040, Type: Integer
    Value: 720, Type: Integer
    Value: 120, Type: Integer
    Value: 24, Type: Integer
    Value: 6, Type: Integer
    Value: 2, Type: Integer
    Value: 1, Type: Integer
    Value: 1, Type: Integer
```
The goal is that you don't have to write the c++ main.cpp but write a `.asa` file
that may look like this:
```asm
;; create a new instruction called "factorial" with an argument n
factorial n:
    DEF ans, 1
	DEF i, 1
	LABEL fact_loop
		;; ans = ans * i
		GET ans
		GET i
		MUL
		SET ans

		;; increment i
		INCR i

		;; check if i <= n
		IF i <= n THEN GOTO fact_loop

	;; push ans on stack
	GET ans
end

main:
	CALL factorial, 10  ;; calls factorial with 10 as arg for n
	SHOW                ;; show stack (contains result)
end
```

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
    SUB,
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
                                    ADD,
                                    SHOW,
                                    DIV,
                                    SHOW,
                                    MUL,
                                    SHOW,
                                    SUB,
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
