#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int size;
	int *result;
} Result;

Result bucket_sort(int max, int size, int *source);

int main(){
	int amount = 5
		, isbns[] = { 400, 301, 999, 301, 321 };
	Result r = bucket_sort(1000, 5, isbns);
	for (int i = 0; i < r.size; i++) {
		printf("%d ", *(r.result+i));
	}

	return 0;
}

Result bucket_sort(int max, int size, int *source){
	int bucket[max];
	for (int i = 0; i < max; i++) {
		bucket[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		bucket[*(source+i)] += 1;
	}

	int j = 0;
	int *result = calloc(size, sizeof(int));
	for (int i = 0; i < max; i++) {
		if (bucket[i]) {
			*(result + j) = i;
			j += 1;
		}
	}
	
	Result ret;
	ret.size = j;
	ret.result = result;

	return ret;
}
