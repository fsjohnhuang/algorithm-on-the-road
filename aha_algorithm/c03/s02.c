#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNIT 13

typedef struct{
	int *data;
	int size;
} Positions;

typedef struct{
	int *data;
	int size;
	int head;
	int tail;
} Queue;

char *draw_map(){
	char source[]= {
		'$','$','$','$','$','$','$','$','$','$','$','$','$',
		'$','G','G','.','G','G','G','#','G','G','G','.','$',
		'$','#','$','.','$','G','$','G','$','G','$','G','$',
		'$','.','.','M','.','.','.','.','#','.','.','G','$',
		'$','G','$','.','$','#','$','.','$','G','$','G','$',
		'$','G','G','.','G','G','G','.','#','.','G','G','$',
		'$','G','$','.','$','G','$','.','$','.','$','#','$',
		'$','#','G','.','.','.','G','.','.','.','.','.','$',
		'$','G','$','.','$','G','$','#','$','.','$','G','$',
		'$','.','.','.','G','#','G','G','G','.','G','G','$',
		'$','G','$','.','$','G','$','G','$','.','$','G','$',
		'$','G','G','.','G','G','G','#','G','.','G','G','$',
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

int is_ghost(char c){
	return c == 'G';
}
int is_breakable_wall(char c){
	return c == '#';
}
int is_solid_wall(char c){
	return c == '$';
}
int is_aisle(char c){
	return c == '.';
}

int h_traverse(int sign, int start, char *map){
	int count = 0;
	start += sign;
	while (start % UNIT < 12
			&& start % UNIT > 0
			&& !is_solid_wall(*(map+start))) {
		if (is_ghost(*(map+start))) {
			count += 1;
		}
		start += sign;
	}

	return count;
}

int v_traverse(int sign, int start, char *map){
	int count = 0;
	int l = pow(UNIT, 2);
	start += sign*UNIT;
	while (start < l
			&& start > -1
			&& !is_solid_wall(*(map+start))) {
		if (is_ghost(*(map+start))) {
			count += 1;
		}
		start += sign*UNIT;
	}

	return count;
}

Queue *queue_new(int size){
	Queue *q = malloc(sizeof(Queue));
	q->data = calloc(size, sizeof(int));
	q->size = size;
	q->head = 0;
	q->tail = 0;
	
	return q;
}

int is_empty(Queue *queue){
	return queue->head == queue->tail;
}

void enqueue(Queue *queue, int data){
	*(queue->data+(queue->tail%queue->size)) = data;
	queue->tail += 1;
}

int dequeue(Queue *queue){
	if (is_empty(queue)) return -1;

	int rest = *(queue->data+(queue->head%queue->size));
	queue->head += 1;

	return rest;
}

Positions *reachable_pos(char *map, int curr_pos){
	int count = pow(UNIT, 2);
	int *bucket = calloc(count, sizeof(int));
	for (int i = 0; i < count; i++) {
		*(bucket+i) = 0;
	}

	Queue *queue = queue_new(count / 2);
	enqueue(queue, curr_pos);
	while (!is_empty(queue)) {
		int pos = dequeue(queue);
		*(bucket+pos) += 1;
		// horizontal traverse
		int l_pos = pos - 1;
		while (is_aisle(*(map+l_pos))
				&& *(bucket+l_pos) == 0) {
			enqueue(queue, l_pos);
			l_pos -= 1;
		}
		int r_pos = pos + 1;
		while (is_aisle(*(map+r_pos))
				&& *(bucket+r_pos) == 0) {
			enqueue(queue, r_pos);
			r_pos += 1;
		}
		// vertical traverse
		int t_pos = pos - UNIT;
		while (t_pos > 0
				&& is_aisle(*(map+t_pos))
				&& *(bucket+t_pos) == 0) {
			enqueue(queue, t_pos);
			t_pos -= UNIT;
		}
		int b_pos = pos + UNIT;
		while (t_pos < count
				&& is_aisle(*(map+b_pos))
				&& *(bucket+b_pos) == 0) {
			enqueue(queue, b_pos);
			b_pos += UNIT;
		}
	}

	Positions *rest = malloc(sizeof(Positions));
	rest->data = calloc(count, sizeof(char));
	int size = 0;
	for (int i = 0; i < count; i++) {
		if (bucket[i] > 0){
			size += 1;
			*(rest->data+i) = i;
		}
	}
	rest->size = size;
	return rest;
}

int find_max_power_pos(char *map, Positions * positions){
	int max = 0, max_pos = 0, tmp = 0, pos = 0;
	int count = pow(UNIT, 2);
	for (int i = 0; i < positions->size; i++) {
		pos = *(positions->data+i);
		if (is_aisle(*(map+pos))) {
			tmp = h_traverse(-1, pos, map)
				+ h_traverse(1, pos, map)
				+ v_traverse(-1, pos, map)
				+ v_traverse(1, pos, map);
			if (tmp > max){
				max = tmp;
				max_pos = pos;
			}
		}
	}

	return max_pos;
}

int main(){
	char *map = draw_map();
	printf("Playground is like below:\n");
	traverse(map);

	Positions *positions = reachable_pos(map, 42);

	int pos = find_max_power_pos(map, positions);
	*(map+pos) = 'B';
	printf("Playground has changed to as below:\n");
	traverse(map);

	free(map);
	free(positions);

	return 0;
}
