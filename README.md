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
> I am not a C++ developer so keep that in mind but I will definitely clean up and refactor a lot :D

> g++ version used: 13.2.0

```pascal
// define new 'fib' block/function
begin fib:
  pop n;
  // base cases
  push n; push 0; cmp; ifgoto 0 base_zero;
  push n; push 1; cmp; ifgoto 0 base_one;

  // if n >= 2 we do the following...
  push 0; pop first;
  push 1; pop second;
  push 2; pop i;
  label loop;
    push first; push second; add; pop result; // result  = first + second
    push second; pop first;                   // first   = second
    push result; pop second;                  // second  = result
    push i; push 1; add; pop i;               // i       = i + 1
    push i; push n; cmp; ifgoto -1 loop;      // if  i < n then goto loop
    push i; push n; cmp; ifgoto 0 loop;       // if i == n then goto loop
  push second; pop result; goto return;       // else: result = second + goto return label

  label base_zero;
    push 0; pop result; goto return;          // result  = 0 + goto return label 

  label base_one; 
    push 1; pop result; goto return;          // result  = 1 + goto return label

  label return;
    push result;                              // push whatever result is onto stack
end

// define main entrypoint
begin main:
  push 0;  call fib;
  push 1;  call fib;
  push 7;  call fib;
  push 10; call fib;
  show;
end
```
```
Stack:
    Value: 55, Type: Integer
    Value: 13, Type: Integer
    Value: 1, Type: Integer
    Value: 0, Type: Integer
```
As we can see we successfully calculated `fib(0)`, `fib(1)`, `fib(7)` and `fib(10)`.

# Instructions / Keywords
## Functions / Blocks
In asa you can define functions by using the `begin` and `end` keyword. These functions are then called by using the
`call` instruction. Here is a quick example:
```pascal
begin do_something:
  push "doing something...";
end

begin main:
  call do_something;
  show;
end
```
The `main` function is the entrypoint of the program if we try to run it. 

## Variables
In order to store something in a variable we usually `push` a value onto the stack and then `pop` it into a variable:
```pascal
begin main:
  push 1; pop x; // x = 1
  push 2; pop x; // variables are mutable, therefore x = 2 now
  push x;        // we can also push the value of the variable to the stack
end
```

## Comparing data
Asa has a `cmp` instruction which takes the two top values of the stack and compares them:
```pascal
begin main:
  push 1; push 2; cmp; // pushes -1 to stack because 1  < 2
  push 2; push 2; cmp; // pushes  0 to stack because 2 == 2
  push 3; push 2; cmp; // pushes  1 to stack because 3  > 2
end
```

## Labels + Goto (and Ifgoto)
Labels are used to mark a position in the program and Gotos are used to jump to the position. The following program pushes 1 to the stack until we get
a stack overflow:
```pascal
begin main:
  label loop;
  push 1;
  goto loop;
end
```
Loops can also be used to skip a portion of code. 
```pascal
begin main:
  push 21; pop age;
  push 18; push age; cmp; pop 18_to_age;  // 18 < 21 <=> 18_to_age = -1

  // if 18 <= age then goto over_18
  push 18_to_age; ifgoto -1 over_18;
  push 18_to_age; ifgoto 0 over_18;

  // otherwise do this and goto return:
  push "not allowed to drink"; pop verdict;
  goto return; // skips the over_18 body

  label over_18;
    push "allowed to drink"; pop verdict;
    goto return; // not really needed here since it is the next instruction anyways...

  label return;
    push verdict;

  show;
end
```

## Math Operations
In asa there are `add`, `sub`, `mul` and `div`. The
```pascal
begin main:
  // evaluate (3*5 + 1)/4 - 3 = 1
  push 3; push 5; mul;   // 3 * 5  = 15 
  push 1; add;           // 15 + 1 = 16
  push 4; div;           // 16 / 4 =  4
  push 3; sub;           // 4 - 3  =  1
  show;                  // shows 1 in stack
end
```

## Importing
asa also allows us to modularize our code because it supports `import` statements. Let's say that we have the following file (in the same directory):
stringlib.asa:
```pascal
begin concat:
    pop b; pop a;
    push a; push b; add;
end
```
We can import `stringlib.asa` into our code by using `import`:
```pascal
import "stringlib.asa";

begin main:
    push "Hi"; push " User!";
    call concat;
    show;
end
```
The result of this code correctly shows `"Hi User"` in the stack.
