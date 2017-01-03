#include <stdio.h>
#include <stdlib.h>

int* bucket_sort(int max_value, int size, int* source);

int main(){
	int max_value = 10
		, source[] = {5,1,3,2,3};
	int size = sizeof(source) / sizeof(int);

	int *p_result;
	p_result = bucket_sort(max_value, size, source);

	int i;
	for(i = 0; i < size; ++i){
		printf("%d", *(p_result+i));
	}

	free(p_result);

}

/*
 * 简易的桶排序
 */
int* bucket_sort(int max_value, int size, int* source){
	int *p_result = calloc(size, sizeof(int))
		, *p_next = p_result;
	
	// 初始化桶
	int i;
	int bucket[max_value]
		, *p_bucket = bucket;
	for(i = 0; i < max_value; ++i){
		*(p_bucket+i) = 0;
	}

	// 在桶对应的位置标记元素
	int j;
	for(j = 0; j < size; ++j){
		*(p_bucket+*(source+j)) += 1;
	}

	// 过滤无效值
	int k
		, tmp_value;
	for(k = 0; k < max_value; ++k){
		tmp_value = *(p_bucket+k);
		while(tmp_value > 0){
			*p_next++ = k;
			tmp_value -= 1;
		}
	}

	return p_result;
}
