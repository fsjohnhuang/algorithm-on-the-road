#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
int kruskal(const graph_t *, int *e_idxs);

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

	int *e_idxs = (int *)calloc(g->e_count, sizeof(int));
	int e_idxs_count = kruskal(g, e_idxs);

	printf("e_idxs_count:%d\n", e_idxs_count);
	for (int i = 0; i < e_idxs_count; i++) {
		printf("e:%d\n", *(e_idxs+i));
	}

	return 0;
}

typedef struct {
	vertex_t root; // 记录父节点，用于路径压缩
	int rank;      // 对集合规模作评级，用于按秩合并
	vertex_t *members; // 集合成员
} subset_t;


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

vertex_t find(subset_t **subsets, const vertex_t vex){
	return (*(subsets+vex))->root;
}
void f_union(subset_t **subsets, const vertex_t vex1, const vertex_t vex2){
	int rank1 = (*(subsets+vex1))->rank;
	int rank2 = (*(subsets+vex2))->rank;
	subset_t *maxset, *minset;
	if (rank1 >= rank2) {
		maxset = *(subsets + vex1);
		minset = *(subsets + vex2);
	}
	else{
		maxset = *(subsets + vex2);
		minset = *(subsets + vex1);
	}

	memcpy(maxset->members+maxset->rank, minset->members, minset->rank*sizeof(vertex_t));
	for (int i = 0; i < minset->rank; i++) {
		*(subsets+*(minset->members+i)) = maxset;
	}
	maxset->rank += minset->rank;

	free(minset);
}
int find_union(subset_t **subsets, const vertex_t svex, const vertex_t evex){
	vertex_t sp = find(subsets, svex);
	vertex_t ep = find(subsets, evex);
	if (sp == ep) return 0;

	f_union(subsets, sp, ep);
	return 1;
}

int kruskal(const graph_t *g, int *e_idxs){
	int e_idxs_count = 0;
	// 初始化不相关集合
	subset_t **subsets = (subset_t **)calloc(g->v_count, sizeof(subset_t *));
	for (int i = 0; i < g->v_count; i++) {
		*(subsets+i) = (subset_t *)malloc(sizeof(subset_t));
		(*(subsets+i))->root = i;
		(*(subsets+i))->rank = 1;
		(*(subsets+i))->members = (vertex_t *)calloc(g->v_count, sizeof(vertex_t));
		*((*(subsets+i))->members) = i;
	}

	int *idxs = heapsort(g->ws, g->e_count);

	int sube_count = 0, i = 0;
	while (sube_count < g->v_count - 1
			&& i < g->e_count) {

		int min_idx = *(idxs+i);
		int res = find_union(subsets, *(g->svexs+min_idx), *(g->evexs+min_idx));
		if (res == 1){
			*(e_idxs+e_idxs_count) = min_idx;
			e_idxs_count += 1;
		}

		i += 1;
	}

	free(subsets);
	free(idxs);

	return e_idxs_count;
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

