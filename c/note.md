## `malloc`,`calloc`和`realloc`
引入`#include <stdlib.h>`

数组申明和定义是同时发生的，而且不单单会分配内存空间，而且会将所分配的内存空间设置为0.
```
int vals[3] = {-1};
for (int i = 0; i < 3; i++){
	printf("%d", vals[i]);
}
// 显示 -100
```

## `strcpy`,`memcpy`和`memmove`
`strcpy(char *desination, const char *source)`
1. 用于复制字符串;
2. 不需要指定长度，遇到字符串结束符`\0`就结束.
`memcpy(void *destination, const void *source, size_t num)`
1. 用于复制任何类型的数据;
2. 要指定复制的字节数.
注意：
1. 要确保已分配内存空间给destination,否则会报segmentfault;
2. 要确保已分配足够的空间给destination,否则会导致意外覆盖其他内存空间内容的问题;
3. 若destination和source所指向的内存空间重叠,那么有可能导致source所指向的内存空间内容发生变化，此时可使用`memmove`来避免.
`memmove(void *destination, const void *source, size_t num)`
1. 内部通过buffer暂存source~source+num间的内容，然后复制到destination中.

## 预定义数据类型
### `size_t`
`sizeof`的返回类型，表示某块内存的占多少个字节．其取值范围是OS可操作的内存大小(32bitOS可操作2^32的内存空间，64bitOS可操作2^64的内存空间)
OS相关类型,32位OS即等于unsigned int,64位OS即等于long unsigned int.
C中位于`<stddef.h>`,C++中位于`<cstddef.h>`.

## 数据模型表示法
`I`:int
`L`:long
`LL`:long long
`P`:非函数的指针类型
示例：
1. `I16P32`表示int占16bit,指针占32bit;
2. `I16LP32`表示int占16bit,long和指针占32bit.
P为32表示寻址空间为2^32byte

## QA
### 虽然写了`#include <math.h>`但运行时报`undefined reference to 'pow'`
原因：动态链接失败导致找不到pow定义
解决方式：`gcc "%" -lm`，将libm.so静态链接到可执行文件中．
由于`/lib/`和`/usr/lib/`下的库均以`lib<name>.a`或`lib<name>.so`方式命名，因此gcc静态链接选项为`-l<name>`．而`<math.h>`的定义则在`libm.so`文件中，所以选项为`-lm`．
