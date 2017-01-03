#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int *data;
	int top;
	int size;
} Stack;

typedef struct{
	int *data;
	int head;
	int tail;
	int size;
} Queue;

Stack stack_new(int size);
void push(int val, Stack *stack);
int pop(Stack *stack);

Queue queue_new(int size);
void enqueue(int val, Queue *queue);
int dequeue(Queue *queue);
int is_empty(Queue *queue);

int main(int argc, char *argv[]){
	int pock[] = {2, 3, 2, 1};
	int count = sizeof(pock) / sizeof(int);
	Queue queue[2];
	queue[0] = queue_new(count);
	queue[1] = queue_new(count);
	for (int i = 0; i < 2; i++) {
		for (int j = i * (count / 2); j < (i + 1)*(count / 2); j++) {
			enqueue(pock[j], &queue[i]);
		}
	}

	int max = 10;
	int bucket[max];
	for (int i = 0; i < max; i++) {
		bucket[i] = 0;
	}

	Stack stack = stack_new(count - 1);
	while (!(is_empty(&queue[0]) || is_empty(&queue[1]))) {
		for (int i = 0; i < 2; i++) {
			Queue *q = &queue[i];
			int v = dequeue(q);
			push(v, &stack);
			bucket[v] += 1;
			if (bucket[v] > 1) {
				while (bucket[v]) {
					int t = pop(&stack);
					bucket[t] -= 1;
					enqueue(t, q);
				}
			}
		}
	}

	if (is_empty(&queue[0])) {
		printf("a wins");
	}else{
		printf("b wins");
	}

	return 0;
}

Stack stack_new(int size){
	Stack stack;
	stack.size = size;
	stack.data = calloc(stack.size, sizeof(int));
	stack.top = 0;

	return stack;
}
void push(int val, Stack *stack){
	*(stack->data + stack->top) = val;
	stack->top += 1;
}
int pop(Stack *stack){
	stack->top -= 1;
	int v = *(stack->data + stack->top);
	return v;
}

Queue queue_new(int size){
	Queue q;
	q.size = size;
	q.data = calloc(size, sizeof(int));
	q.head = 0;
	q.tail = 0;

	return q;
}
void enqueue(int val, Queue *queue){
	*(queue->data + (queue->tail % queue->size)) = val;
	queue->tail += 1;
}
int dequeue(Queue *queue){
	int val = *(queue->data + (queue->head % queue->size));
	queue->head += 1;
	return val;
}
int is_empty(Queue *queue){
	return queue->head == queue->tail;
}
