#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNIT 13

char *draw_map(){
	char source[]= {
		'$','$','$','$','$','$','$','$','$','$','$','$','$',
		'.','.','.','.','.','.','.','$','.','.','.','.','$',
		'$','$','$','.','$','.','$','.','$','.','$','.','$',
		'$','.','.','.','.','.','.','.','$','.','.','M','$',
		'$','.','$','.','$','$','$','.','$','.','$','.','$',
		'$','.','.','.','.','.','.','.','$','.','.','.','$',
		'$','.','$','.','$','.','$','.','$','.','$','$','$',
		'$','$','.','.','.','.','.','.','.','.','.','.','$',
		'$','.','$','.','$','.','$','$','$','.','$','.','$',
		'$','.','.','.','.','$','.','.','.','.','.','.','$',
		'$','.','$','.','$','.','$','.','$','.','$','.','$',
		'$','.','.','.','.','.','.','$','.','.','.','.','$',
		'$','$','$','$','$','$','$','$','$','$','$','$','$'
	};

	int count = pow(UNIT, 2);
	char *map = calloc(count, sizeof(char));
	for (int i = 0; i < count; i++) {
		*(map + i) = source[i];
	}

	return map;
}

void traverse(char *map){
	int count = pow(UNIT, 2);
	for (int i = 0; i < count; i++) {
		printf(" %c ", *(map+i));
		if ((i+1) % UNIT == 0) {
			printf("\n");
		}
	}
}

int is_aisle(char c){
	return c == '.';
}

int find_entry(char *map){
	int entry = -1, count = pow(UNIT, 2);
	for (int i = 0; i < UNIT && entry == -1; i++) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}
	for (int i = count - 1; i >= count - UNIT && entry == -1; i--) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}
	for (int i = 0; i < count && entry == -1; i += UNIT) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}
	for (int i = UNIT; i < count && entry == -1; i += UNIT) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}

	return entry;
}

int is_target(char c){
	return c == 'M';
}
int is_solid_wall(char c){
	return c == '$';
}

typedef struct{
	int n;
	int s;
} Node;

typedef struct {
	Node *data;
	int head;
	int tail;
	int size;
} Queue;
Queue *new(int size){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->size = size;
	q->head = q->tail = 0;
	q->data = (Node *)calloc(size, sizeof(Node));

	return q;
}
int is_empty(Queue *q){
	return q->head == q->tail;
}
int is_full(Queue *q){
	return q->tail - q->head == q->size;
}
void enqueue(Queue *q, Node v){
	if (is_full(q)) return;
	*(q->data+(q->tail++)%q->size) = v;
}
Node *dequeue(Queue *q){
	if (is_empty(q)) return NULL;
	return q->data+(q->head++)%q->size;
}

void bfs(char *map, Queue *q, int *bucket){
	int count = pow(UNIT, 2);
	while (!is_empty(q)) {
		Node *p = dequeue(q);
		if (is_target(*(map+p->n))){
			printf("find %d", p->s);
			break;
		}
		
		int n = p->n - UNIT;
		if (n >= 0
				&& !is_solid_wall(*(map+n))
				&& !bucket[n]){
			Node nn = {n, p->s+1};
			enqueue(q, nn);
			bucket[n] += 1;
		}
		n = p->n + 1;
		if (n < count
				&& !is_solid_wall(*(map+n))
				&& !bucket[n]){
			Node nn = {n, p->s+1};
			enqueue(q, nn);
			bucket[n] += 1;
		}
		n = p->n + UNIT;
		if (n < count
				&& !is_solid_wall(*(map+n))
				&& !bucket[n]){
			Node nn = {n, p->s+1};
			enqueue(q, nn);
			bucket[n] += 1;
		}
		n = p->n - 1;
		if (n >= 0
				&& !is_solid_wall(*(map+n))
				&& !bucket[n]){
			Node nn = {n, p->s+1};
			enqueue(q, nn);
			bucket[n] += 1;
		}
	}
}

int main(int argc, int **argv){
	char *map = draw_map();
	int count = pow(UNIT, 2);
	Queue *q = new(count/2);
	int bucket[count];
	for (int i = 0; i < count; i++) {
		bucket[i] = 0;
	}

	int entry = find_entry(map);
	Node nn = {entry, 0};
	enqueue(q, nn);

	bfs(map, q, bucket);
}
