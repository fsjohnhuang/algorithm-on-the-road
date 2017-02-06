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

int dfs(graph_t *g, vertex_t root_vex, int *num, int idx, int *walked){
	if (walked[root_vex]) return -1;

	for (int i = 0; i < idx; i++) {
		if (*(num+i) == root_vex) return i;
	}
	walked[root_vex] = 1;
	for (int i = 0; i < g->e_count; i++) {
		vertex_t svex = *(g->svexs+i);
		vertex_t evex = *(g->evexs+i);
		if (svex == *(num+idx) || evex == *(num+idx)) continue;

		if (svex == root_vex || evex == root_vex) {
			vertex_t nvex = svex == root_vex ? evex : svex;
			int ret = dfs(g, nvex, num, idx, walked);
			if (ret != -1) {
				return ret;
			}
		}
	}

	walked[root_vex] = 0;
	return -1;
}

int get_cut_vertexs(graph_t *g, vertex_t *cut_vexs){
	int num[g->v_count], low[g->v_count];
	for (int i = 0; i < g->v_count; i++) {
		num[i] = low[i] = -1;
	}
	int idx = 0, vex = 0;
	num[idx] = vex;
	low[idx] = 0;
	int walked1[g->v_count];
	for (int i = 0; i < g->v_count; i++) {
		walked1[i] = 0;
	}
	walked1[vex] = 1;

	int s = g->v_count;
	while(s-->1){
		// 寻找子节点
		int found = -1;
		for (int i = 0; i < g->e_count && found == -1; i++) {
			vertex_t svex = *(g->svexs+i);
			vertex_t evex = *(g->evexs+i);
			if (walked1[svex] && walked1[evex]) continue;
			if (svex == vex || evex == vex) {
				vex = svex == vex ? evex : svex;
				walked1[vex] = 1;
				found = 1;
			}
		}
		// 反向查找父＂时间戳＂
		int walked[g->v_count];
		for (int i = 0; i < g->v_count; i++) {
			walked[i] = 0;
		}
		int a_idx = dfs(g, vex, num, idx++, walked);
		if (a_idx == -1) {
			// 找不到祖先节点
			low[idx] = idx - 1;
		}
		else{
			low[idx] = low[a_idx];
		}
		num[idx] = vex;
	}

	int cut_vex_count = 0;
	for (int i = 0; i < idx - 1; i++) {
		if (low[i] != low[i+1]){
			cut_vexs[cut_vex_count] = num[i];
			cut_vex_count += 1;
		}
	}

	return cut_vex_count;
}

int main(int argc, int **argv){
	graph_t *g = create_graph(5);
	add_edge(g, 0, 1, 3);
	add_edge(g, 0, 2, 2);
	add_edge(g, 1, 2, 3);
	add_edge(g, 2, 1, 3);
	add_edge(g, 3, 2, 4);
	add_edge(g, 4, 2, 2);
	add_edge(g, 4, 3, 4);

	vertex_t cut_vexs[g->v_count];
	int cut_vex_count = get_cut_vertexs(g, cut_vexs);

	for (int i = 0; i < cut_vex_count; i++) {
		printf("e:%d\n", cut_vexs[i]);
	}

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
