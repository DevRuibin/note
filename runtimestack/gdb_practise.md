```c
#include <stdio.h>
    #include <stdlib.h>

        int func(int a) {
            int b=10;
            return a+b;
        }

        void main() {
            int result;
            result=func(5);
            printf("The result is %d\n",result);
        }
```

1. 编译程序，运行gdb

```bash

gcc -g -o basic basic.c
./basic
gdb -q basic
```

2. 运行gdb

```bash
run main
```

3. 在function这里打断点

```bash
b func
```

4. 我们发现代码会在function这里暂停

```bash
s // step 执行每一步
c // 执行到下一个断点或者结束如果没有断点
```

5. 假设我们在第四步执行的是s,我们应该能看到程序将要运行return指令。

```bash
p a
p b // 打印 a 和 b 
```



1. 让我们重新运行一遍程序，在程序执行到断点出停止的时候
