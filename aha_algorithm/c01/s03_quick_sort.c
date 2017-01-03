#include <stdio.h>

void quick_sort(int size, int *source);

int main(){
	int source[] = {5,4,3,2,1,1};
	int size = sizeof(source) / sizeof(int);

	quick_sort(size, source);

	int i;
	for(i = 0; i < size; ++i){
		printf("%d", source[i]);
	}
}

void quick_sort(int size, int *source){
	if (1 >= size) return;

	int ref = *source
		, *p_left = source
		, *p_right = source + size - 1;
	
	int tmp;
	// 左侧小于基准值，右侧大于基准值
	// 右 小于基准值则停止
	// 左 大于基准值则停止
	while(p_left != p_right){
		while(*p_right >= ref && p_left != p_right){
			p_right -= 1;
		}
		while(*p_left <= ref && p_left != p_right){
			p_left += 1;
		}

		tmp = *p_left;
		*p_left = *p_right;
		*p_right = tmp;
	}

	// 左右指针均指向同一个位置
	tmp = *source;
	*source = *p_right;
	*p_right = tmp;

	int lsize = (int)(p_left - source);
	quick_sort(lsize, source);

	int rsize = size - (int)(p_left + 1 - source);
	quick_sort(rsize, p_left + 1);
}
