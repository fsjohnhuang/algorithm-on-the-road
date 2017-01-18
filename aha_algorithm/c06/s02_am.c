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

typedef struct {
	int *data;
	unsigned int size, head, tail;
} queue_t;
queue_t *create_queue(const unsigned int size){
	queue_t *q = (queue_t *)malloc(sizeof(queue_t));
	q->size = size;
	q->head = q->tail = 0;
	q->data = (int *)calloc(size, sizeof(int));

	return q;
}
typedef int bool_t;
bool_t isempty(queue_t *q){
	return q->head == q->tail;
}
void enqueue(queue_t *q, int val){
	*(q->data+(q->tail++)%q->size) = val;
}
int dequeue(queue_t *q){
	return *(q->data+(q->head++)%q->size);
}

weight_t * dijkstra(graph_t *g, const unsigned int t_vex){
	weight_t *t_weights = (weight_t *)calloc(g->vex_num, sizeof(weight_t));
	memcpy(t_weights, g->map+t_vex*g->vex_num, g->vex_num*sizeof(weight_t));

	queue_t *pool = create_queue(g->vex_num);
	for (int i = 0; i < g->vex_num; i++) {
		enqueue(pool, i);
	}

	queue_t *pool2;
	while (!isempty(pool)) {
		int curr_i, min_i = -1;
		pool2 = create_queue(g->vex_num);
		while (!isempty(pool)){
			curr_i = dequeue(pool);
			if (min_i == -1){
				min_i = curr_i;
			}
			else if(t_weights[curr_i] <= t_weights[min_i]){
				enqueue(pool2, min_i);
				min_i = curr_i;
			}
			else{
				enqueue(pool2, curr_i);
			}
		}

		pool = pool2;
		pool2 = create_queue(g->vex_num);
		int i;
		while (!isempty(pool)){
			i = dequeue(pool);
			if (t_weights[i] > *(g->map+t_vex*g->vex_num+min_i) + *(g->map+min_i*g->vex_num+i)){
				t_weights[i] = *(g->map+t_vex*g->vex_num+min_i) + *(g->map+min_i*g->vex_num+i);
			}
			enqueue(pool2, i);
		}
		pool = pool2;
	}

	return t_weights;
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

int main(int argc, int **argv){
	vertex_t vexs[] = {'A', 'B', 'C', 'D'};
	const unsigned int vex_num = sizeof(vexs) / sizeof(vertex_t);
	weight_t map[] = {
		 0, 1, 8, 6,
		 1, 0, 6, 3,
		 8, 6, 0,INF,
		 6, 3,INF, 0
	};
	graph_t *g = create_mgraph(vex_num, vexs, map);
	draw_graph(g);

	weight_t *res = dijkstra(g, 0);
	puts("after dijkstra:");
	for (int i = 0; i < g->vex_num; i++) {
		printf("%d ", *(res+i));
	}
	
	return 0;
}
