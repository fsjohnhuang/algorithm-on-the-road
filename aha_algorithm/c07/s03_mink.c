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

typedef int (*either)(tree_t, const int , const int , const int);
int min(tree_t t, const int count, const int f, const int s){
	if (s >= count) return f;
	return *(t+f) > *(t+s) ? s : f;
}
int max(tree_t t, const int count, const int f, const int s){
	if (s >= count) return f;
	return *(t+f) > *(t+s) ? f : s;
}

typedef int (*cond)(tree_t, const int , const int);
// 最小堆
int min_heap(tree_t t, const int curr, const int next){
	return *(t+curr) > *(t+next);
}
// 最大堆
int max_heap(tree_t t, const int curr, const int next){
	return *(t+curr) < *(t+next);
}

typedef struct {
	cond cfn;
	either efn;
} cond_t;

void shiftdown(tree_t t, const int count, const int pos, cond_t *c){
	int curr = pos;
	int next = curr * 2;
	int swapped = 1;
	while (next < count && swapped){
		swapped = 0;
		next = c->efn(t, count, next, next+1);
		if (c->cfn(t, curr, next)){
			swapped = 1;
			swap(t+curr, t+next);
			curr = next;
			next = curr * 2;
		}
	}
}

int main(int argc, int **argv){
	node_t nodes[] = {IGNORE, 99,23,45,9,5,54};
	int count = sizeof(nodes)/sizeof(node_t);

	int k = 0;
	puts("Input min K please!");
	scanf("%d", &k);
	tree_t t = tree_create(nodes, k+1);
	cond_t *c = (cond_t *)malloc(sizeof(cond_t));
	c->cfn = max_heap;
	c->efn = max;
	for (int i = (k+1)/2; i > 0; i--) {
		shiftdown(t, k+1, i, c);
	}

	for (int i = k + 1; i < count; i++) {
		if (nodes[i] < *(t+1)) {
			*(t+1) = nodes[i];
			shiftdown(t, k+1, 1, c);
		}
	}

	tree_print(t, k+1);

	free(c);
	free(t);
	return 0;
}
