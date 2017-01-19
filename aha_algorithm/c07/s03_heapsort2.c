#include <stdio.h>
#include <stdlib.h>

#define IGNORE -1

typedef int node_t;
typedef node_t* tree_t;

tree_t tree_create(node_t *nodes, int count){
	tree_t t = (tree_t)calloc(count, sizeof(node_t));
	for (int i = 0; i < count; i++) {
		*(t+i) = nodes[i];
	}

	return t;
}

void tree_print(tree_t t, int count){
	for (int i = 1; i < count; i++) {
		printf("%d ", *(t+i));
		if (i%2 == 1) {
			printf("\n");
		}
	}
}

void swap(node_t *f, node_t *s){
	node_t tmp = *f;
	*f = *s;
	*s = tmp;
}

int min(tree_t t, const int count, int f, int s){
	if (s >= count) return f;
	return *(t+f) > *(t+s) ? s : f;
}
int max(tree_t t, const int count, int f, int s){
	if (s >= count) return f;
	return *(t+f) > *(t+s) ? f : s;
}

typedef int (*cond)(tree_t, int ,int);
// 最小堆
int min_heap(tree_t t, int curr, int next){
	return *(t+curr) > *(t+next);
}
// 最大堆
int max_heap(tree_t t, int curr, int next){
	return *(t+curr) < *(t+next);
}

void shiftdown(tree_t t, const int count, const int pos, cond c){
	int curr = pos;
	int next = curr * 2;
	int swapped = 1;
	while (next < count && swapped){
		swapped = 0;
		next = max(t, count, next, next+1);
		if (c(t, curr, next)){
			swapped = 1;
			swap(t+curr, t+next);
			curr = next;
			next = curr * 2;
		}
	}
}

void heapsort(tree_t t, const int count){
	int t_count = count;
	node_t root, last;
	while (t_count-->1) {
		// 将最后一个移动到根节点
		swap(t+1, t+t_count);
		// 向下调整
		shiftdown(t, t_count, 1, max_heap);
	}
}

int main(int argc, int **argv){
	node_t nodes[] = {IGNORE, 99,23,45,9,5,54};
	int count = sizeof(nodes)/sizeof(node_t);
	tree_t t = tree_create(nodes, count);
	for (int i = count / 2; i >= 1; i--) {
		shiftdown(t, count, i, max_heap);
	}
	tree_print(t, count);

	printf("\n\n");
	heapsort(t, count);
	tree_print(t, count);

	return 0;
}
