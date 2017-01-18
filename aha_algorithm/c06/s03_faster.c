#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WEIGHT 99999

typedef int vertex_t;
typedef unsigned int weight_t;
typedef struct { vertex_t *arc_svex; vertex_t *arc_evex; weight_t *arc_weight;
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

weight_t *bellman_ford_faster(graph_t *g, vertex_t vex, int *exist_circuit){
	int n = g->vex_num;
	weight_t *t_weight = (weight_t *)calloc(g->vex_num, sizeof(weight_t));
	queue_t *q = qnew(n);
	for (int i = 0; i < n; i++) {
		enqueue(q, i);
		*(t_weight+i) = i == vex ? 0 : MAX_WEIGHT;
	}

	while (n-->0 && !q_isempty(q)) {
		int curr = q->rear - q->head;
		for (int i = 0; i < curr; i++) {
			int next = *(g->first+i);
			while (next != -1) {
				weight_t o_weight = *(t_weight+*(g->arc_evex+next));
				weight_t n_weight = *(t_weight+*(g->arc_svex+next)) + *(g->arc_weight+next);
				if (o_weight > n_weight) {
					*(t_weight+*(g->arc_evex+next)) = n_weight;
					enqueue(q, *(g->arc_evex+next));
				}
				next = *(g->next+next);
			}
		}
	}

	*exist_circuit = n == 0;

	return t_weight;
}

int main(int argc, int **argv){
	graph_t *g = create_graph(4);
	add_arc(g, 0, 1, 2);
	add_arc(g, 0, 2, 5);
	add_arc(g, 0, 3, 8);
	add_arc(g, 1, 2, -1);
	add_arc(g, 2, 3, 1);

	int *exist_circuit = (int *)malloc(sizeof(int));
	weight_t *t_weight = bellman_ford_faster(g, 0, exist_circuit);
	for (int i = 0; i < 4; i++) {
		printf("%d ", *(t_weight+i));
	}

	free(t_weight);
	free(g);
	free(exist_circuit);
	return 0;
}
