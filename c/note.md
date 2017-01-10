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


## QA
### 虽然写了`#include <math.h>`但运行时报`undefined reference to 'pow'`
原因：动态链接失败导致找不到pow定义
解决方式：`gcc "%" -lm`，将libm.so静态链接到可执行文件中．
由于`/lib/`和`/usr/lib/`下的库均以`lib<name>.a`或`lib<name>.so`方式命名，因此gcc静态链接选项为`-l<name>`．而`<math.h>`的定义则在`libm.so`文件中，所以选项为`-lm`．
