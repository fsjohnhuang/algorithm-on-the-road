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

void dfs(graph_t *g, int *cut_edges, int *num, int *low, int *timestamp, vertex_t cur, vertex_t father){
	num[cur] = low[cur] = *timestamp;
	*timestamp += 1;
	for (int i = 0; i < g->e_count; i++) {
		if (belong2(g, i, cur)) {
			vertex_t next = *(g->svexs+i) == cur ? *(g->evexs+i) : *(g->svexs+i);
			if (num[next] == 0) {
				// 未访问过
				dfs(g, cut_edges, num, low, timestamp, next, cur);
				low[cur] = min(low[cur], low[next]);
				if (cur != father){
					if (low[next] > num[cur]                         // 访问真正根节点和其他节点时
							|| (num[cur] != 2 && low[next] == num[cur])) // 访问其他节点时
					{
						*(cut_edges+i) = 1;
					}
				}
			}
			else if(next != father){
				// 访问过且不为父节点
				low[cur] = min(num[next], low[cur]);
			}
		}
	}
}

int *get_cut_edges(graph_t *g){
	// 加入伪根节点，用于解决根节点为割点的情况
	vertex_t pseudo_root = g->v_count - 1;
	add_edge(g, pseudo_root, 0, pseudo_root);
	int num[g->v_count], low[g->v_count];
	for (int i = 0; i < g->v_count; i++) {
		num[i] = low[i] = 0;
	}
	int timestamp = 1;
	int *cut_edges = (int *)calloc(g->e_count, sizeof(int));
	dfs(g, cut_edges, num, low, &timestamp, pseudo_root, pseudo_root);

	return cut_edges;
}

int main(int argc, int **argv){
	graph_t *g = create_graph(6);
	add_edge(g, 0, 1, 3);
	add_edge(g, 0, 2, 2);
	add_edge(g, 1, 2, 3);
	add_edge(g, 2, 1, 3);
	add_edge(g, 3, 2, 4);
	add_edge(g, 4, 2, 2);

	int *cut_edges = get_cut_edges(g);

	for (int i = 0; i < g->e_count; i++) {
		if (*(cut_edges+i) == 1) {
			printf("cut_edge:%d\n", i);
		}
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
