#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int size;
	int *result;
} Result;
Result distinct(int size, int *source);
void quick_sort(int size, int *source);

int main(){
	int amount = 5
		, isbns[] = { 400, 301, 999, 301, 321 };
	Result r = distinct(5, isbns);
	for (int i = 0; i < r.size; i++) {
		printf("%d ", *(r.result+i));
	}
	return 0;
}

Result distinct(int size, int *source){
	quick_sort(size, source);

	Result r;
	int *result = calloc(size, sizeof(int));
	int j = 0;
	int last, curr;
	for (int i = 0; i < size; i++) {
		curr = *(source + i);
		if (curr != last) {
			*(result + j) = curr;
			j += 1;
		}
		last = curr;
	}

	r.size = j;
	r.result = result;

	return r;
}

void quick_sort(int size, int *source){
	if (size <= 1) return;

	int ref = *source;
	int *p_l = source;
	int *p_r = source + size - 1;

	int tmp;
	while (p_l != p_r) {
		while (*p_r >= ref && p_l != p_r) {
			p_r -= 1;
		}
		while (*p_l <= ref && p_l != p_r) {
			p_l += 1;
		}

		tmp = *p_l;
		*p_l = *p_r;
		*p_r = tmp;
	}

	tmp = *p_l;
	*p_l = *source;
	*source = tmp;

	int l_size = (int)(p_l - source) - 1;
	quick_sort(l_size, source);

	int r_size = size - l_size - 2;
	quick_sort(r_size, p_l + 1);
}
