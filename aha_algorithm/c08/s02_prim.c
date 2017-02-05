#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_WEIGHT 99999

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
int prim(const graph_t *, vertex_t, int *);

int main(int argc, int **argv){
	graph_t *g = create_graph(5);
	add_edge(g, 0, 1, 3);
	add_edge(g, 0, 2, 2);
	add_edge(g, 1, 2, 3);
	add_edge(g, 2, 1, 3);
	add_edge(g, 3, 2, 4);
	add_edge(g, 4, 2, 2);
	add_edge(g, 4, 3, 4);

	/*add_edge(g, 4, 3, 7);
	add_edge(g, 4, 2, 6);
	add_edge(g, 3, 2, 5);
	add_edge(g, 2, 1, 4);
	add_edge(g, 1, 2, 3);
	add_edge(g, 0, 2, 2);
	add_edge(g, 0, 1, 1);*/

	int *e_idxs = (int *)calloc(g->v_count, sizeof(int));
	int e_idxs_count = prim(g, 0, e_idxs);

	printf("e_idxs_count:%d\n", e_idxs_count);
	for (int i = 0; i < e_idxs_count; i++) {
		printf("e:%d\n", *(e_idxs+i));
	}

	return 0;
}


void shiftdown(int *idxs, weight_t *a, const count_t a_count, int p, int l){
	p -= 1;
	l -= 1;

	if (p >= a_count || l >= a_count) return;
	weight_t pw = *(a+p)
		, lw = *(a+l)
		, rw = l+1 < a_count ? *(a+l+1) : -9999999;
	int s = lw >= rw ? l : l+1;
	if (*(a+s) <= pw) return;

	*(a+p) = *(a+s);
	*(a+s) = pw;

	int tmp_idx = *(idxs+p);
	*(idxs+p) = *(idxs+s);
	*(idxs+s) = tmp_idx;

	shiftdown(idxs, a, a_count, s+1, (s+1)*2);
}
int *heapsort(const weight_t *ws, const count_t w_count){
	weight_t *a = (weight_t *)calloc(w_count, sizeof(weight_t));
	memcpy(a, ws, w_count * sizeof(weight_t));

	int *idxs = (int *)calloc(w_count, sizeof(int));
	for (int i = 0; i < w_count; i++) {
		*(idxs+i) = i;
	}

	for (int i = w_count/2; i >= 1; i--) {
		shiftdown(idxs, a, w_count, i, i*2);
	}

	int i = w_count;
	int root = 1;
	while (i-->root) {
		weight_t tmp = *a;
		*a = *(a+i);
		*(a+i) = tmp;

		int tmp_idx = *idxs;
		*idxs = *(idxs+i);
		*(idxs+i) = tmp_idx;
		shiftdown(idxs, a, i, 1, 2);
	}

	free(a);
	return idxs;
}

int prim(const graph_t *g, vertex_t seed, int *vexs){
	weight_t t_weights[g->v_count];
	int counts[g->v_count];
	for (int i = 0; i < g->v_count; i++) {
		t_weights[i] = i == seed ? 0 : MAX_WEIGHT;
		counts[i] = 0;
	}
	int *idxs =heapsort(t_weights, g->v_count);
	int i = g->v_count;
	int k = 0;
	while (i-->0) {
		int idx = *idxs;
		printf("idx:%d\n", idx);
		counts[idx] = 1;
		vexs[k++] = idx;
		for (int j = 0; j < g->e_count; j++) {
			weight_t w = *(g->ws+j);
			vertex_t svex = *(g->svexs+j);
			vertex_t evex = *(g->evexs+j);
			if (counts[svex] && counts[evex]);else if(svex == idx || evex == idx){
				t_weights[idx == svex ? evex : svex] = w < t_weights[idx == svex ? evex : svex] 
					? w
					: t_weights[idx == svex ? evex : svex];
			}
			for (int i = 0; i < g->v_count; i++) {
				if (counts[i]) {
					t_weights[i] = MAX_WEIGHT;
				}
			}
		}
		
		idxs = heapsort(t_weights, g->v_count);
	}

	return k;
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
