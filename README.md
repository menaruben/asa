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
> This is a toy project and should not be taken seriously, which means it is NOT for production at all. The goal of this project is to have fun!
> I am not also not a experienced C++ developer but I will definitely clean up and refactor a lot :D

```asm
BEGIN factorial
  DEF n 0 Integer
  SET n
  DEF ans 1 Integer
  DEF i 1 Integer
  LABEL fact
    GET ans; GET i; MUL; SET ans
    INCR i
    IF i < n THEN GOTO fact
    IF i == n THEN GOTO fact
  GET ans
END

BEGIN main
  PUSH 10 Integer
  CALL factorial
  SHOW
END
```
```asm
Stack:
    Value: 3628800, Type: Integer
```
As we can see the "function"/block `factorial` above pushes the factorial of 10 to the stack!

# Instructions
## SHOW
Prints the current stack to the terminal

## PUSH v t
Pushes the value `v` with type `t` to the stack

## ADD
Adds the two elements at the top in the stack (popping them)
and pushes the result to the stack

## SUB
Subtracts the last element from the second last element in the stack (popping them)
and pushes the result to the stack

## MUL 
Multiplies the two elements at the top in the stack (popping them)
and pushes the result to the stack

## DIV
Divides the second last element by the last element in the stack (popping them)
and pushes the result to the stack

## LABEL n 
Creates a label with the name `n`. You can jump to that
label using the `GOTO` instruction or in `IF` instructions:
```
IF i < n THEN GOTO mylabel
```

## GOTO n
Jumps to the label with the name `n`. 

## DEF n v t
Defines a variable with the name `n` with the value `v` and type `t`.

## SET n
Sets the value of the variable to the element at the top of the stack.

## GET n
Pushes the value of the variable to the stack.

## CMP
Compares the second last element (a) to the last element (b) in the stack (top) (popping them).
When...
  - a < b  => pushes -1 to the stack
  - a == b => pushes  0 to the stack
  - a > b  => pushes  1 to the stack

## IF
Jump to a label or halt if a condition is met.
```
IF i < n THEN GOTO mylabel
IF i == n then HALT
```
Keep in mind that the condition must be separated by spaces and that the values
compared must be two variables! Valid compare operators are `<`, `==` and `>`.

## HALT
Stops the program. 

## CLEAR
Clears the stack

## INCR n
Increments the value of the variable n by 1

## DECR n
Decrements the value of the variable by 1

## CALL n
Calls the block/function with the name `n`. Please see the factorial example.
