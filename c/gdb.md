## 入门
1. 编译时加入debug信息`gcc -g source.c`
2. 载入可执行文件`gdb target.out`
在gdb下的命令：<br>
`r`，执行程序<br>
`list`，显示源代码<br>
`break 行号或标识符`，设置断点<br>
&emsp;`next [count=1]`
&emsp;`c`，跳转到下一个断点<br>
&emsp;`p 变量名`，查看变量信息<br>
`info break`，查看断点信息<br>
