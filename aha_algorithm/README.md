# ＜啊哈！算法＞读书笔记
## c01 第一章 一大波数正在靠近-排序
`s01_bucket_sort`, 桶排序
`s01_ex1`, 桶排序练习
`s02_bubble_sort`, 冒泡排序
`s03_quick_sort`, 快速排序
`s04_ex_bucketsort`, 小哼买书练习桶排序
`s04_ex_quicksort`, 小哼买书练习快速排序

## c02 第二章 栈,队列,链表
`s01_queue`, 解密QQ号－队列
`s02_stack`, 解密回文－栈
`s03_ex`, 小猫钓鱼
`s04_linklist`, 链表
`s05_mock_linklist`, 模拟链表

## c03 第三章 枚举！很暴力
`s01`, 坑爹的奥数
`s02`, 炸弹人
`s03`, 火柴棍等式
`s03_1`, 火柴棍等式(书中的解法)
`s04`, 数的全排列

## c04 第四章 万能的搜索
`s02`, 解救小哈（深度搜索，作者John E. Hopcropf和Robert E. Tarjan）
`s03`, 层层递进-广度优先搜索(Edward F. Moore"如何从迷宫中寻找出路"提出的解决方案)
`s05`, 宝岛探险(Floodfill,漫水/种子填充法, windows画板填充也是这个算法)
`s06`, 水管工游戏

## c05 第五章 图的遍历
图，由定点和边组成
邻接矩阵(adjacency matrix),图的顺序存储结构
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

邻接表(adjacency list),图的链式存储结构
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

`s01_dfs`, 深度优先遍历(采用了邻接矩阵)
`s01_bfs`, 广度优先遍历(采用了邻接表)
