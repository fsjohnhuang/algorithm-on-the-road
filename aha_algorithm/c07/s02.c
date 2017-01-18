#include <stdio.h>
#include <stdlib.h>

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
	for (int i = 0; i < count; i++) {
		printf("%d ", *(t+i));
		if (i%2 == 0) {
			printf("\n");
		}
	}
}

int main(int argc, int **argv){
	node_t nodes[] = {1,2,3,4,5};
	int count = sizeof(nodes)/sizeof(node_t);
	tree_t t = tree_create(nodes, count);
	tree_print(t, count);

	return 0;
}
