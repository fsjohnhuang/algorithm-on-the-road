#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int *data;
	int size;
	int head;
	int tail;
} Queue;

void main(){
	int source[] = {6, 3, 1, 7, 5, 8, 9, 2, 4, 3};
	int count = sizeof(source) / sizeof(int);

	Queue queue;
	queue.data = source;
	queue.size = count;
	queue.head = 0;
	queue.tail = count;

	while (queue.tail > queue.head) {
		printf("%d", *(queue.data + queue.head%queue.size));
		queue.head += 1;
		
		*(queue.data + queue.tail%queue.size) = *(queue.data + queue.head%queue.size);
		queue.head += 1;
		queue.tail += 1;
	}
}
