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

EBP: 指向stack frame的开始
ESP: 指向stack frame的末尾

### Debuggers

1. Debgger: 允许用户查看程序运行的各个状态(比如GDB)
2. Disassembler: 将二进制机器码转为汇编语言
3. Decompiler: 将二进制机器码转化为高级语言。

> 一般debugger中有disassmbler
