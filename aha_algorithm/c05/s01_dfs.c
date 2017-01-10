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

MGraph *create_mgraph(const unsigned int vex_num){
	MGraph *g = (MGraph *)malloc(sizeof(MGraph));
	g->vex_num = vex_num;
	g->vexs = (VertexType *)calloc(vex_num, sizeof(VertexType));
	g->edges = (EdgeType *)calloc(pow(vex_num, 2), sizeof(EdgeType));

	for (int i = 0; i < vex_num; i++) {
		*(g->vexs+i) = i+1;
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

	int count = sizeof(arcs)/sizeof(unsigned int);
	for (int i = 0; i < count; i++) {
		*(g->edges+i) = arcs[i];
	}
}

void dfs(MGraph *g, int *vex_walked, const unsigned int seq, VertexType vex){
	int pos = vex - 1;
	if (*(vex_walked+pos) != -1) return;

	*(vex_walked+pos) = seq;
	while (pos >= 0 && pos < 5*5) {
		if (*(g->edges+pos) == 1){
			dfs(g, vex_walked, seq + 1, pos/5 + 1);
		}
		pos += 5;
	}
}

int main(int argc, int **argv){
	MGraph *g = create_mgraph(5);
	draw_arcs(g);

	int vex_walked[] = {-1, -1, -1, -1, -1};
	dfs(g, vex_walked, 0, 1);

	int result[5];
	for (int i = 0; i < 5; i++) {
		result[vex_walked[i]] = i+1;
	}
	for (int i = 0; i < 5; i++) {
		printf("%d\n", result[i]);
	}

	free(g);
	return 0;
}
