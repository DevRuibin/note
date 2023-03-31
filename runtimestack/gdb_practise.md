## 

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



1. 让我们重新运行一遍程序，在程序执行到断点处，停止
2. 我们可以加一个临时断点，并且跳过它
    ```c
    tbreak +1
    jump +1
    ```
3. 这个时候我们检查变量
    ```
    p a 
    p b
    ```
4. 我们发现变量b没有定义，可以手动复制
    ```
    set var b = 100
    p b
    ```
5. 继续执行程序，看到结果时按照我们手动设置的b的值定义的。

## 高阶使用（需要汇编知识）

我们还是使用basic.c这个例子

1. 重新启动gdb,不带断点执行一遍程序，我们可以既能发现程序没有异常，也可以初始化程序地址。
2. 查看main函数的汇编 `disass main`
   ```bash
   (gdb) disass main
   Dump of assembler code for function main:
   0x000000000040113e <+0>:     push   %rbp
   0x000000000040113f <+1>:     mov    %rsp,%rbp
   0x0000000000401142 <+4>:     sub    $0x10,%rsp
   0x0000000000401146 <+8>:     mov    $0x5,%edi
   0x000000000040114b <+13>:    call   0x401126 <func>
   0x0000000000401150 <+18>:    mov    %eax,-0x4(%rbp)
   0x0000000000401153 <+21>:    mov    -0x4(%rbp),%eax
   0x0000000000401156 <+24>:    mov    %eax,%esi
   0x0000000000401158 <+26>:    mov    $0x402010,%edi
   0x000000000040115d <+31>:    mov    $0x0,%eax
   --Type <RET> for more, q to quit, c to continue without paging--
   0x0000000000401162 <+36>:    call   0x401030 <printf@plt>
   0x0000000000401167 <+41>:    nop
   0x0000000000401168 <+42>:    leave
   0x0000000000401169 <+43>:    ret
   ```
   
   在这里我们可以看见`0x000000000040114b <+13>:    call   0x401126 <func>`。在这条指令处打断点。`b *0x000000000040114b `
3. 运行程序，程序会在断点处停止。我们查看一下EIP(rip)寄存器 `i r rip`
4. 让程序执行一步 `s`
5. 再次检查EIP,`i r rip`
6. 查看fuc函数的汇编 `disass func`
7. 让函数执行到即将结束的时候。我们需要不停的使用`disass` 查看目前具体函数执行哪个指令
8. 一般返回值都在eax寄存器，我们可以修改这个寄存器，`set $eax=1024`, 可以再次查看eax寄存器的状态`i r eax`
9. 让程序执行完毕 `c`
10. 我们发现结果是1024。

## 更高阶

在这个部分，我们让可执行程序不带源代码信息 `gcc basic.c -o basic`
大家可以自己去尝试一遍，这个和带调试信息的区别。 大体是一样的，区别就是当我们使用s命令的时候，之前的方式会跳转到下一个有行信息的指令。但是现在我们的源代码信息丢失了，所以我们使用c就不知道能跳转到哪里去了。
