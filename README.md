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
begin fib:
    pop n;              // store top variable n
    push 0; pop first;  // first = 0
    push 1; pop second; // second = 1
    push 2; pop i;
    // creates a label called "loop"
    label loop;
        // result = first + second
        push first; push second; add; pop result;
        push second; pop first;          // first = second
        push result; pop second;         // second = result
    push i; push 1; add; pop i;      // i = i + 1
    push i; push n; cmp; ifgoto -1 loop; // if i  < n then goto loop
    push i; push n; cmp; ifgoto 0 loop;  // if i == n then goto loop
    push result;
end

begin main:
    push 10;
    call fib;
    show;
end
```
```
Stack:
    Value: 55, Type: Integer
```
As we can see the "function"/block `fib` above pushes the 10th fib to the stack!
