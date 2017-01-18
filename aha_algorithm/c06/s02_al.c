#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_WEIGHT 999999

typedef int vertex_t;
typedef unsigned int weight_t;
typedef struct {
	vertex_t *arc_svex;
	vertex_t *arc_evex;
	weight_t *arc_weight;
	int *first;
	int *next;
	unsigned int arc_num;
	unsigned int vex_num;
} graph_t;
graph_t *create_graph(const unsigned int vex_num){
	graph_t *g = (graph_t *)malloc(sizeof(graph_t));
	int count = pow(vex_num, 2);
	g->vex_num = vex_num;
	g->arc_svex = (vertex_t *)calloc(count, sizeof(vertex_t));
	g->arc_evex = (vertex_t *)calloc(count, sizeof(vertex_t));
	g->arc_weight = (weight_t *)calloc(count, sizeof(weight_t));
	g->arc_num = 0;
	g->first = (int *)calloc(vex_num, sizeof(int));
	for (int i = 0; i < g->vex_num; i++) {
		*(g->first+i) = -1;
	}
	g->next = (int *)calloc(count, sizeof(int));
	for (int i = 0; i < count; i++) {
		*(g->next+i) = -1;
	}

	return g;
}
void add_arc(graph_t *g, const vertex_t s, const vertex_t e, const weight_t w){
	*(g->arc_svex+g->arc_num) = s;
	*(g->arc_evex+g->arc_num) = e;
	*(g->arc_weight+g->arc_num) = w;

	*(g->next+g->arc_num) = *(g->first+s);
	*(g->first+s) = g->arc_num;
	g->arc_num += 1;
}

typedef struct {
	vertex_t *vexs;
	int size;
	int head;
	int rear;
} queue_t;
queue_t *qnew(const int size){
	queue_t *q = (queue_t *)malloc(sizeof(queue_t));
	q->size = size;
	q->head = q->rear = 0;
	q->vexs = (vertex_t *)calloc(size, sizeof(vertex_t));

	return q;
}
void enqueue(queue_t *q, vertex_t v){
	*(q->vexs+q->rear%q->size) = v;
	q->rear += 1;
}
vertex_t dequeue(queue_t *q){
	vertex_t v = *(q->vexs+q->head%q->size);
	q->head += 1;

	return v;
}
int q_isempty(queue_t *q){
	return q->head == q->rear;
}

vertex_t min(queue_t *q, weight_t *t_weight){
	vertex_t min_vex = dequeue(q);
	int size = q->rear - q->head;
	while (size-->0) {
		vertex_t curr_vex = dequeue(q);
		if (*(t_weight+curr_vex) <= *(t_weight+min_vex)){
			enqueue(q, min_vex);
			min_vex = curr_vex;
		}
		else{
			enqueue(q, curr_vex);
		}
	}

	return min_vex;
}

void slack(graph_t *g, vertex_t vex, weight_t *t_weight){
	int next = *(g->first+vex);
	while (next != -1) {
		vertex_t evex = *(g->arc_evex+next);
		weight_t old = *(t_weight+evex);
		weight_t new = *(t_weight+vex) + *(g->arc_weight+next);
		if (new < old) {
			*(t_weight+evex) = new;
		}
		next = *(g->next+next);
	}
}

weight_t *dijkstra(graph_t *g, const vertex_t vex){
	queue_t *q = qnew(g->vex_num);
	weight_t *t_weight = (weight_t *)calloc(g->vex_num, sizeof(weight_t));
	for (int i = 0; i < g->vex_num; i++) {
		enqueue(q, i);
		*(t_weight+i) = vex == i ? 0 : MAX_WEIGHT;
	}
	
	while (!q_isempty(q)) {
		vertex_t vex = min(q, t_weight);
		slack(g, vex, t_weight);
	}

	return t_weight;
}

int main(int argc, int **argv){
	graph_t *g = create_graph(4);
	add_arc(g, 0, 1, 2);
	add_arc(g, 0, 2, 5);
	add_arc(g, 0, 3, 8);
	add_arc(g, 1, 2, 1);
	add_arc(g, 2, 3, 1);

	weight_t *t_weight = dijkstra(g, 0);
	for (int i = 0; i < 4; i++) {
		printf("%d ", *(t_weight+i));
	}

	return 0;
}
