#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define INF 99999

typedef char vertex_t;
typedef unsigned int weight_t;
typedef struct {
	unsigned int vex_num;
	vertex_t *vexs;
	weight_t *map; // adjacency matrix
} graph_t;
graph_t *create_mgraph(const unsigned int vex_num, const vertex_t *vexs, const weight_t *map){
	graph_t *g = (graph_t *)malloc(sizeof(graph_t));
	g->vex_num = vex_num;
	g->vexs = (vertex_t *)calloc(vex_num, sizeof(vertex_t));
	memcpy(g->vexs, vexs, vex_num * sizeof(vertex_t));
	g->map = (weight_t *)calloc(pow(vex_num, 2), sizeof(weight_t));
	memcpy(g->map, map, pow(vex_num, 2) * sizeof(weight_t));

	return g;
}

void draw_graph(graph_t *g){
	int count = pow(g->vex_num, 2);
	for (int i = 0; i < count; i++) {
		printf("%d,", *(g->map+i));
		if (i % g->vex_num == g->vex_num-1){
			printf("\n");
		}
	}
}

void floyd_warshall(graph_t *g){
	int count = g->vex_num;
	for (int i = 0; i < count; i++) {
		for (int a = 0; a < count; a++) {
			for (int b = a+1; b < count; b++) {
				weight_t curr = *(g->map+(a*count+b))
								,candidate = *(g->map+(a*count+i)) + *(g->map+(i*count+b));
				if (curr > candidate) {
					*(g->map+(a*count+b)) = *(g->map+(b*count+a)) = candidate;
				}
			}
		}
	}
}

int main(int argc, int **argv){
	vertex_t vexs[] = {'A', 'B', 'C', 'D'};
	const unsigned int vex_num = sizeof(vexs) / sizeof(vertex_t);
	weight_t map[] = {
		 0, 1, 8, 6,
		 1, 0, 7, 3,
		 8, 7, 0,INF,
		 6, 3,INF, 0
	};
	graph_t *g = create_mgraph(vex_num, vexs, map);
	draw_graph(g);
	puts("after floyd-warshall:");
	floyd_warshall(g);
	draw_graph(g);
	
	return 0;
}
