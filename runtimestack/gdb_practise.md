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

## 实战

在这里我会提供一个二进制程序，具体访问这个网址：[网址](https://1drv.ms/u/s!AtjGRmN0hGM-ecokQwv2iAgr-Rw?e=r4LNdl)。我们一起分析这个玩具代码

```bash
gdb -q ./code
```

```bash
run
```

我们得到：

```bash
(gdb) r
Starting program: /home/ruibin/Downloads/files (1)/Tutorial-03/Cheating/3.4/code 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
Input passcode: 
```
我们随便输一个密码就， 结果当然是密码错误。

接着我们看汇编代码

```
disass main
```

这是输出结果

```bash
(gdb) disass main
Dump of assembler code for function main:
   0x0000000000401146 <+0>:	push   %rbp
   0x0000000000401147 <+1>:	mov    %rsp,%rbp
   0x000000000040114a <+4>:	sub    $0x20,%rsp
   0x000000000040114e <+8>:	mov    %edi,-0x14(%rbp)
   0x0000000000401151 <+11>:	mov    %rsi,-0x20(%rbp)
   0x0000000000401155 <+15>:	mov    $0x402010,%edi
   0x000000000040115a <+20>:	mov    $0x0,%eax
   0x000000000040115f <+25>:	call   0x401040 <printf@plt>
   0x0000000000401164 <+30>:	lea    -0x4(%rbp),%rax
   0x0000000000401168 <+34>:	mov    %rax,%rsi
   0x000000000040116b <+37>:	mov    $0x402021,%edi
   0x0000000000401170 <+42>:	mov    $0x0,%eax
   0x0000000000401175 <+47>:	call   0x401050 <__isoc99_scanf@plt>
   0x000000000040117a <+52>:	mov    -0x4(%rbp),%eax
   0x000000000040117d <+55>:	cmp    $0xcafebabe,%eax
   0x0000000000401182 <+60>:	jne    0x401190 <main+74>
   0x0000000000401184 <+62>:	mov    $0x402024,%edi
   0x0000000000401189 <+67>:	call   0x401030 <puts@plt>
   0x000000000040118e <+72>:	jmp    0x40119a <main+84>
   0x0000000000401190 <+74>:	mov    $0x402041,%edi
   0x0000000000401195 <+79>:	call   0x401030 <puts@plt>
   0x000000000040119a <+84>:	mov    $0x0,%eax
   0x000000000040119f <+89>:	leave
   0x00000000004011a0 <+90>:	ret
End of assembler dump.
```

> 我们知道既然有输入密码，肯定有要比较的地方，就找cmp函数。
> `   0x000000000040117d <+55>:	cmp    $0xcafebabe,%eax`

找到了, 

`0xcafebabe` 这个就是要找的立即数，我们把它打印出来

```bash
(gdb) printf "%d\n%u\n", 0xcafebabe, 0xcafebabe
-889275714
3405691582
```
一个是有符号数字，一个是无符号数字。这两是一样的，都是密码。

```bash
(gdb) r 
Starting program: /home/ruibin/Downloads/files (1)/Tutorial-03/Cheating/3.4/code 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
Input passcode: -889275714
You guessed the secret code!
[Inferior 1 (process 26435) exited normally]
(gdb) r 
Starting program: /home/ruibin/Downloads/files (1)/Tutorial-03/Cheating/3.4/code 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
Input passcode: 3405691582
You guessed the secret code!
[Inferior 1 (process 26437) exited normally]
```

## 实战2

这里也有一个二进制程序：[网址](https://1drv.ms/u/s!AtjGRmN0hGM-eqJofuOTo5rqqCM?e=GI1iXd)

我们现在运行一下这个程序，了解他的基本行为。然后，我告诉你们，这个程序有一个后门，你们很难触发他，请你用gdb去触发它。

思路：

我们找那些`jmp`指令，找到之后，让程序跳转至那里，然后运行。

1. 运行gdb
2. 直接运行一遍，初始化内存
3. `break main`
4. `disass main`
5. 分析我们首先找到一个
   ```
    0x00000000004011c0 <+90>:	je     0x40122f <main+201>
    0x00000000004011c2 <+92>:	mov    -0xc(%rbp),%eax
   ```
   现在我们怀疑有一个条件在这里很难到达，只有开发者知道如何才能触发。所以我就在这里打断点`b *0x00000000004011c2`。然后运行程序，发现真的程序不会暂停。于是我就在main函数入口处设立断点，之后使用`jump *0x00000000004011c2`  让程序强制跳转，跳转后，执行`continue`，之后就会发现我们找到了后门。
   ```
   (gdb) break main
    Breakpoint 9 at 0x40116a
    (gdb) r
    Starting program: /home/ruibin/Downloads/files (1)/Tutorial-03/Cheating/3.5/backdoor 
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".

    Breakpoint 9, 0x000000000040116a in main ()
    (gdb) jump 0x00000000004011c2
    Function "0x00000000004011c2" not defined.
    (gdb) jump *0x00000000004011c2
    Continuing at 0x4011c2.

    Breakpoint 7, 0x00000000004011c2 in main ()
    (gdb) continue
    Continuing.
    Today I am evil and your input is now 468775808
    You input was 0
    [Inferior 1 (process 28526) exited normally]
   ```
   
### 分析
    程序对这个函数进行了复杂的分析，只有满足这个条件才会跳转。比如，这个数据在某个比特位必须是1。
    
## 
    
