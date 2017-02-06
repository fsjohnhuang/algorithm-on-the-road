#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned short int count_t;
typedef int vertex_t;
typedef int weight_t;
typedef struct {
	count_t v_count, e_count;
	vertex_t *svexs, *evexs;
	weight_t *ws; // an array store the weight of edges
} graph_t;
graph_t *create_graph(const count_t);
void add_edge(graph_t *, const vertex_t, const vertex_t, const weight_t);

int min(int a, int b){
	return a > b ? b : a;
}
int belong2(graph_t *g, int i, vertex_t curr){
	return *(g->svexs+i) == curr || *(g->evexs+i) == curr;
}

int dfs(graph_t *g, vertex_t *matched, int *booked, vertex_t curr){
	if (booked[curr]) return 0;
	booked[curr] += 1;

	for (int j = 0; j < g->e_count; j++) {
		if (belong2(g, j, curr)){
			vertex_t n = *(g->svexs+j)==curr ? *(g->evexs+j) : *(g->svexs+j);
			if (matched[n] == -1 || dfs(g, matched, booked, matched[n])){
				matched[curr] = n;
				matched[n] = curr;
				return 1;
			}
		}
	}

	return 0;
}

int get_max_match(graph_t *g){
	vertex_t matched[g->v_count];
	for (int i = 0; i < g->v_count; i++) matched[i] = -1;
	int booked[g->v_count];
	int max = 0;

	for (int i = 0; i < g->v_count; i++) {
		if (matched[i] == -1) {
			for (int j = 0; j < g->v_count; j++) booked[j] = 0;
			if (dfs(g, matched, booked, i)) max+=1;
		}
	}

	return max;
}

int main(int argc, int **argv){
	graph_t *g = create_graph(5);
	add_edge(g, 0, 1, 3);
	add_edge(g, 0, 2, 2);
	add_edge(g, 3, 2, 4);
	add_edge(g, 4, 3, 4);

	int max = get_max_match(g);
	printf("max:%d\n", max);

	return 0;
}

graph_t *create_graph(const count_t vertex_count){
	int e = pow(vertex_count, 2);
	graph_t *g = (graph_t *)malloc(sizeof(graph_t));
	g->v_count = vertex_count;
	g->e_count = 0;
	g->svexs = (vertex_t *)calloc(e, sizeof(vertex_t));
	g->evexs = (vertex_t *)calloc(e, sizeof(vertex_t));
	g->ws = (vertex_t *)calloc(e, sizeof(vertex_t));

	return g;
}

void add_edge(graph_t *g, const vertex_t svex, const vertex_t evex, const weight_t w){
	*(g->svexs+g->e_count) = svex;
	*(g->evexs+g->e_count) = evex;
	*(g->ws+g->e_count) = w;
	g->e_count += 1;
}
