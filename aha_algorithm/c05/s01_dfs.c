#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef char VertexType;
typedef int EdgeType;
typedef struct {
	int vex_num;
	VertexType *vexs;// 顶点表
	EdgeType *edges; // 邻接矩阵(边表)
} MGraph;

MGraph *create_mgraph(const unsigned int vex_num, char *vexs){
	MGraph *g = (MGraph *)malloc(sizeof(MGraph));
	g->vex_num = vex_num;
	g->vexs = (VertexType *)calloc(vex_num, sizeof(VertexType));
	g->edges = (EdgeType *)calloc(pow(vex_num, 2), sizeof(EdgeType));

	for (int i = 0; i < vex_num; i++) {
		*(g->vexs+i) = *(vexs+i);
	}

	return g;
}

void draw_arcs(MGraph *g){
	unsigned int arcs[] = {
		0, 1, 1, 0, 1,
		1, 0, 0, 1, 1,
		1, 0, 0, 1, 1,
		1, 1, 1, 0, 1,
		1, 0, 1, 1, 0
	};

	int count = pow(g->vex_num, 2);
	for (int i = 0; i < count; i++) {
		*(g->edges+i) = arcs[i];
	}
}

void dfs(MGraph *g, int *vex_walked, const unsigned int seq, VertexType vex){
	int pos = vex - 1;
	if (*(vex_walked+pos) != -1) return;

	*(vex_walked+pos) = seq;
	int count = pow(g->vex_num, 2);
	while (pos >= 0 && pos < count) {
		if (*(g->edges+pos) == 1){
			dfs(g, vex_walked, seq + 1, pos/5 + 1);
		}
		pos += g->vex_num;
	}
}

int main(int argc, int **argv){
	char vexs[] = {'A', 'B', 'C', 'D', 'E'};
	MGraph *g = create_mgraph(sizeof(vexs)/sizeof(char), vexs);
	draw_arcs(g);

	int vex_walked[g->vex_num];
	for (int i = 0; i < g->vex_num; i++) {
		vex_walked[i] = -1;
	}
	dfs(g, vex_walked, 0, 1);

	char result[g->vex_num];
	for (int i = 0; i < g->vex_num; i++) {
		result[vex_walked[i]] = *(g->vexs+i);
	}
	for (int i = 0; i < g->vex_num; i++) {
		printf("%c", result[i]);
	}

	free(g);
	return 0;
}
