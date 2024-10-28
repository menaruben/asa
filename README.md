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

```asm
BEGIN factorial
DEF n 0 Integer
SET n
DEF ans 1 Integer
DEF i 1 Integer
LABEL fact
GET ans
GET i
MUL
SET ans
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
As we can see the function above returns the factorial of 10!
