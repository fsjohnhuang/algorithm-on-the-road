#include <stdio.h>
#include <stdlib.h>

int* find_multiple_values(int size, int *source);

int main(){
	int max_value = 10
		, source[] = {5,1,3,2,3};
	int size = sizeof(source) / sizeof(int);

	int *p_result;
	p_result = find_multiple_values(size, source);

	int i;
	for(i = 0; i < size; ++i){
		printf("%d", *(p_result+i));
	}

	free(p_result);
}

/* 应用练习1
 * 有一个由若干个正整数组成的数列，数列中每个数都不超过32,已知数列中存在重复的数字
 * 问：请找出所有重复出现的数
 * 要求：O(N)
 */
#define MAX_VALUE 32

int* find_multiple_values(int size, int *source){

	// O(32)
	int bucket[MAX_VALUE]
		, i;
	for(i = 0; i < MAX_VALUE; ++i){
		bucket[i] = 0;
	}
	
	// O(N)
	int j;
	for(j = 0; j < size; ++j){
		bucket[*(source+j)] += 1;
	}


	// O(32)
	int find_count = 0;
	for(i = 0; i < MAX_VALUE; ++i){
		if (bucket[i] > 1){
			find_count += 1;
		}
	}
	
	// O(32)
	int *p_result = calloc(find_count, sizeof(int))
		, *p_next = p_result;
	for(i = 0; i < MAX_VALUE; ++i){
		if (bucket[i] > 1){
			*p_next++ = i;
		}
	}

	return p_result;
}
