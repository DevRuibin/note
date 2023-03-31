# Run time stack

![N|Solid](https://github.com/ruibinzhang021/ruibinzhang021/blob/main/static/imgs/mylogon.png?raw=true)

## 内存和栈
先放一张内存图，让大家有一个直观了解。然后要记住，stack是从高地址向低地址延伸

![stacl](https://github.com/ruibinzhang021/note/blob/main/runtimestack/imgs/stack.gif?raw=true)

## 汇编基础

Intel, x86:

`operation destination, source`

不同类型的指令

1. 在内存和寄存器之间传数据(`mov, push, pop, lea`)
2. 计算(`add, negl`)
3. 跳跃(`jump, jge`)
4. test(`cmp 和相应的旗帜`)
5. 其他(`function call, ret`)

例子

`mov [EBP+9], value`: 将value放到EBP+9指向的地址中
`lea eax, [ebp+9]`: 加载存在ebp+9的指向的地址的数据到eax寄存器

## 大端和小端

我们知道4个二进制数是一个16进制数字，2个16进制数字是一个字节。

正常情况下，我们在纸上写下一个16进制数字：`0xffcefade`。大端存储是这样的：从低地址到高地址`\xff\ce\fa\de`，而小端存储是`\de\fa\ce\ff`。所以大小端是按照字节跌倒顺序，在每个字节中8bits,还是按照从小到大排列的。

## 寄存器

EBP: 指向stack frame的开始,我们通过EBP访问本地变量
ESP: 指向stack frame的末尾
EIP: 下一条指令地址

### Debuggers

1. Debgger: 允许用户查看程序运行的各个状态(比如GDB)
2. Disassembler: 将二进制机器码转为汇编语言
3. Decompiler: 将二进制机器码转化为高级语言。

> 一般debugger中有disassmbler

## GDB

使用方法：

1. 编译程序`gcc -g program.c -o program`(可以使用-m32指定编译为32位机器上的可执行程序)
2. 执行gdb：`gdb -q program` (-q 可以关闭那些开始的欢迎信息)
3. 使用：
    ```bash
    # break points:
    b main
    b function1
    break funtion1
    break main

    b *address
    b line

    # 二进制转化为汇编
    disass fun
    disass # 转化当前函数

    # 查看寄存器信息
    i r register
    print $register

    # 查看寄存器存储的地址指向的信息
    print *$register

    x/NxU Address
    # N 是unit的数目，U是unit的大小

    # display the words two words(4 bytes each) from the address pointed by the register
    X/2xw $register
    ```

## Run time stack

stack 操作的是4个字节即一个word

```bash
push value: add value on top of stack
pop dest: remove top value from stack and save it in dest
```
**函数被调用前**：
入栈函数参数

**要调用的时候** call func;

push EIP // 保存调用函数在内存代码段的地址，以便被调用函数执行完毕后，指导要返回舍么地方
jmp function's address

**At beginning of the function**:

1. push ebp(save ebp of calling frame)
2. move ebp to esp, (so now the new ebp equals to esp)
3. push local variables

**When the function terminates:

1. leave: move the value of ESP to EBP(restore old esp). And POP EBP(restore old ebp)
2. ret: pop eip,
3. stack from of the function is erased


### 知识

1. 参数是从右向左入栈
2. 经过我的验证，我认为本地变量也是从下往上的。参考文章：**`基本的内存安全问题`**

## 下一篇

GDB 练习



