#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "../lib/colors.c"

#define UNIT 12

char *altitude_colors[] = {
	B_L_BLUE, B_L_GREEN, B_GREEN, B_YELLOW, B_RED, B_L_RED, B_WHITE
};

int *gen_map(){
	int count = pow(UNIT, 2);
	int *p_map = calloc(count, sizeof(int))
		, map[] = {
			5,4,2,1,1,0,0,0,0,0,0,0,
			4,4,2,0,0,0,0,0,0,0,0,0,
			3,3,3,0,0,0,0,1,0,0,0,0,
			2,2,0,0,0,0,0,2,1,0,0,0,
			0,0,0,0,0,3,3,1,0,0,0,0,
			0,0,0,0,0,5,4,2,0,0,0,0,
			0,0,0,0,0,5,5,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,
			0,1,1,0,0,0,0,0,2,0,0,0,
			0,1,2,2,0,0,0,0,2,2,0,0,
			0,2,3,2,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,
		};

	for (int i = 0; i < count; i++) {
		*(p_map+i) = map[i];
	}

	return p_map;
}

void draw_map(int *map){
	int count = pow(UNIT, 2);
	for (int i = 0; i < count; i++) {
		int altitude = map[i];
		printf("%s  %s", altitude_colors[altitude], NONE);
		if (i%UNIT == UNIT - 1){
			printf("\n");
		}
	}
}


typedef struct {
	int *data;
	int size;
	int head;
	int tail;
} Queue;

Queue *qnew(int size){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->size = size;
	q->head = q->tail = 0;
	q->data = (int *)calloc(size, sizeof(int));

	return q;
}
int qempty(Queue *q){
	return q->head == q->tail;
}
int qfull(Queue *q){
	return q->tail - q->head == q->size;
}
void enq(Queue *q, int v){
	if (qfull(q));else {
		*(q->data+(q->tail++)%q->size) = v;
	}
}
int deq(Queue *q){
	if (qempty(q)) return -1;

	return *(q->data+(q->head++)%q->size);
}

Queue *area(int *map, int start){
	int count = pow(UNIT, 2);
	int walked[count];
	for (int i = 0; i < count; i++) {
		walked[i] = 0;
	}
	int dirs[] = {
		-UNIT,
		1,
		UNIT,
		-1
	};

	Queue *q = qnew(count/2);
	enq(q, start);
	walked[start] += 1;
	while (!qempty(q)){
		int c = deq(q);
		int n;
		for (int i = 0; i < 4; i++) {
			n = c + dirs[i];
			if (n >=0 && n < count
					&& !walked[n]
					&& *(map+n)) {
				walked[n] += 1;
				enq(q, n);
			}
		}
	}

	return q;
}

int landing(int *map, int *walked){
	int count = pow(UNIT, 2);
	
	for (int i = 0; i < count; i++) {
		if (*(walked+i) == 0){
			if (*(map+i) > 0) return i;
			*(walked+i) += 1;
		}
	}
}

int *compose(int *map, Queue *q){
	int count = pow(UNIT, 2);
	int *nmap = (int *)calloc(count, sizeof(int));
	memcpy(nmap, map, count*sizeof(int));

	while (!qempty(q)) {
		int n = deq(q);
		*(nmap+n) = 6;
	}

	return nmap;
}

int main(int argc, int **argv){
	int count = pow(UNIT, 2);
	int *map = gen_map();
	draw_map(map);

	int walked[count], walked_count = 0;
	for (int i = 0; i < count; i++) {
		walked[i] = 0;
	}

	int s, *nmap = NULL;
	int sum = 0;
	do{
		s = landing(map, walked);
		Queue *q = area(map, s);
		q->head = 0;
		sum += q->tail - q->head;
		while (!qempty(q)) {
			int n = deq(q);
			walked[n] += 1;
		}
		q->head = 0;
		nmap = compose(nmap == NULL ? map : nmap, q);
		free(q);

		walked_count = 0;
		for (int i = 0; i < count; i++) {
			walked_count += walked[i];
		}
	}while(walked_count < count);

	draw_map(nmap);
	int i = 0;
	while (1) {
		printf("\033[2J");
		printf("The area of island is %d.\n", sum);
		draw_map(i++%2 ? nmap : map);

		sleep(1);
	}

	free(map);
	free(nmap);
}
