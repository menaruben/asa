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

```c
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
As we can see we successfully calculated `fib(0)`, `fib(1)`, `fib(7)` and `fib(8)`.
