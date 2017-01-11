# 图
图，由定点和边组成

## 邻接矩阵(adjacency matrix),图的顺序存储结构
G=(V, E), G为图，V为顶点，E为边．
顶点作为x,y轴坐标，数组元素表示两个顶点间是否存在边(1有,0没有)，或表示权重
无向图，邻接矩阵沿主对角线对称构成对称矩阵．
```
typedef char VertexType;
typedef int EdgeType;
typedef struct {
	VertexType *vexs;    // 顶点表
	EdgeType *edges; // 邻接矩阵(边表)
} MGraph;

MGraph *create_mgraph(const unsigned int vex_num){
	MGraph *g = (MGraph *)malloc(sizeof(MGraph));
	g->vexs = (Vertex *)calloc(vex_num, sizeof(VertexType));
	g->edges = (EdgeType *)calloc(pow(vex_num, 2), sizeof(EdgeType));

	return g;
}
```

## 邻接表(adjacency list),图的链式存储结构
为每个顶点建立独立的单链表，第i个单链表的节点，无向图中表示为依附顶点Vi的边，有向图中表示为以顶点Vi为尾的弧．
```
typedef int VertexType;
typedef struct {
	VertexType vex;
	char info;
	Arc *next_arc;
} Arc;
typedef struct {
	Arc **ptr_arcs;
} Graph;

Graph *create_graph(const unsigned int vex_num){
	Graph *g = (Graph *)malloc(size(Graph));
	g->ptr_arcs = (Arc **)calloc(vex_num, sizeof(Arc *));
	for (int i = 1; i <= vex_num; i++){
		*(g->ptr_arcs+i) = (Arc *)malloc(sizeof(Arc));
		(*(g->ptr_arcs+i))->info = (*(g->ptr_arcs+i))->vex = i;
	}

	return g;
}
```

## 最短路径算法
Floyd
Bellman-Ford
Dijkstra
