#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int *data
		, size
		, head
		, tail;
} Queue;
Queue *create_queue(const int size){
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->size = size;
	q->head = q->tail = 0;
	q->data = (int *)calloc(size, sizeof(int));

	return q;
}
int q_isempty(Queue *q){
	return q->head == q->tail;
}
void enqueue(Queue *q, int v){
	*(q->data+q->tail%q->size) = v;
	q->tail += 1;
}
int dequeue(Queue *q){
	if (q_isempty(q)) return -1;

	int v = *(q->data+q->head%q->size);
	q->head += 1;
	return v;
}

typedef struct arc Arc;
struct arc {
	int pos;
	Arc *next;
};
typedef struct {
	char info;
	Arc *next;
} VertexType;
typedef struct {
	int vex_num;
	VertexType *vexs;
} MGraph;

MGraph *create_mgraph(const unsigned int size, const char *vexs){
	MGraph *g = (MGraph *)malloc(sizeof(MGraph));
	g->vex_num = size;
	g->vexs = (VertexType *)calloc(size, sizeof(VertexType));
	for (int i = 0; i < size; i++) {
		(*(g->vexs+i)).info = *(vexs+i);
	}

	return g;
}

unsigned int bfs(MGraph *g, const unsigned int start, const unsigned int target){
	int step = 0;
	int walked[g->vex_num];
	for (int i = 0; i < g->vex_num; i++) {
		walked[i] = -1;
	}
	Queue *q = create_queue(g->vex_num);
	enqueue(q, start);
	walked[start] = step;
	while (!q_isempty(q)) {
		int curr = dequeue(q);
		step = walked[curr];
		if (curr == target) break;

		Arc *next = (*(g->vexs+curr)).next;
		while (next != NULL) {
			if (walked[next->pos] == -1){
				walked[next->pos] = step + 1;
				enqueue(q, next->pos);
			}
			next = next->next;
		}
	}

	return step;
}

int main(int argc, int **argv){
	char vexs[] = {'A', 'B', 'C', 'D', 'E'};
	MGraph *g = create_mgraph(sizeof(vexs)/sizeof(char), vexs);

	Arc *arc01 = (*g->vexs).next = (Arc *)malloc(sizeof(Arc));
	arc01->pos = 1;
	Arc *arc02 = arc01->next = (Arc *)malloc(sizeof(Arc));
	arc02->pos = 3;
	arc02->next = NULL;

	Arc *arc11 = (*(g->vexs+1)).next = (Arc *)malloc(sizeof(Arc));
	arc11->pos = 0;
	Arc *arc12 = arc11->next = (Arc *)malloc(sizeof(Arc));
	arc12->pos = 2;
	arc12->next = NULL;

	Arc *arc21 = (*(g->vexs+2)).next = (Arc *)malloc(sizeof(Arc));
	arc21->pos = 1;
	arc21->next = NULL;

	Arc *arc31 = (*(g->vexs+3)).next = (Arc *)malloc(sizeof(Arc));
	arc31->pos = 0;
	Arc *arc32 = arc31->next = (Arc *)malloc(sizeof(Arc));
	arc31->pos = 4;
	arc31->next = NULL;

	Arc *arc41 = (*(g->vexs+4)).next = (Arc *)malloc(sizeof(Arc));
	arc41->pos = 3;
	arc41->next = NULL;

	unsigned int min_step = bfs(g, 0, 3);
	printf("min_step:%d", min_step);
	return 0;
}
