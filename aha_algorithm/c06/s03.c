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

weight_t *bellman_ford(graph_t *g, vertex_t vex, int *exist_circuit){
	weight_t *t_weight = (weight_t *)calloc(g->vex_num, sizeof(weight_t));
	for (int i = 0; i < g->vex_num; i++) {
		*(t_weight+i) = i == vex ? 0 : MAX_WEIGHT;
	}

	int m
		, n = g->vex_num
		, changed = 1;
	while (n-->0 && changed) {
		changed = 0;
		m = g->arc_num;
		while (m-->0) {
			if (*(g->arc_svex+m) == vex) {
				weight_t o_weight = *(t_weight+*(g->arc_evex+m));
				weight_t n_weight = *(t_weight+*(g->arc_svex+m)) + *(g->arc_weight+m);
				if (o_weight > n_weight) {
					*(t_weight+*(g->arc_evex+m)) = n_weight;
					changed = 1;
				}
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
	weight_t *t_weight = bellman_ford(g, 0, exist_circuit);
	for (int i = 0; i < 4; i++) {
		printf("%d ", *(t_weight+i));
	}

	free(t_weight);
	free(g);
	free(exist_circuit);
	return 0;
}
