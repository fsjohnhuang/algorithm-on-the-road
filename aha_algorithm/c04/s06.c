#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define UNIT 8

int dir_next[] = {-UNIT, 1, UNIT, -1};

char asset_patterns[] = {
	' ',
	'j',
	'L',
	'F',
	'J',
	'-',
	'|'
};

typedef int bool;

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3
typedef struct {
	int type;
	int dirs[4];
} Asset;
typedef struct {
	Asset *asset;
	int entry;
	int pos;
} Step;

Asset *a_new(){
	Asset *ptr_asset= (Asset *)malloc(sizeof(Asset));
	ptr_asset->type = 0;
	for (int i = 0; i < 4; i++) {
		ptr_asset->dirs[i] = 0;
	}

	return ptr_asset;
}
void a_set(Asset *ptr_asset, int dir){
	ptr_asset->dirs[dir] = 1;
}
bool a_empty(Asset *ptr_asset){
	return ptr_asset->type == 0;
}

void ma0(Asset *ptr_asset){}
void ma1(Asset *ptr_asset){
	ptr_asset->type = 1;
	a_set(ptr_asset, WEST);
	a_set(ptr_asset, NORTH);
}
void ma2(Asset *ptr_asset){
	ptr_asset->type = 2;
	a_set(ptr_asset, NORTH);
	a_set(ptr_asset, EAST);
}
void ma3(Asset *ptr_asset){
	ptr_asset->type = 3;
	a_set(ptr_asset, EAST);
	a_set(ptr_asset, SOUTH);
}
void ma4(Asset *ptr_asset){
	ptr_asset->type = 4;
	a_set(ptr_asset, SOUTH);
	a_set(ptr_asset, WEST);
}
void ma5(Asset *ptr_asset){
	ptr_asset->type = 5;
	a_set(ptr_asset, WEST);
	a_set(ptr_asset, EAST);
}
void ma6(Asset *ptr_asset){
	ptr_asset->type = 6;
	a_set(ptr_asset, NORTH);
	a_set(ptr_asset, SOUTH);
}
typedef void (*MapAsset)(Asset *);
MapAsset map_assets[] = { ma0, ma1, ma2, ma3, ma4, ma5, ma6 };

Asset **gen_map(){
	int count = pow(UNIT, 2);
	int src_map[] = {
		5, 4, 2, 3, 4, 5, 6, 1,
		1, 1, 2, 3, 4, 5, 6, 1,
		1, 1, 2, 3, 4, 5, 0, 1,
		1, 1, 2, 3, 4, 5, 2, 1,
		1, 1, 2, 3, 4, 5, 1, 1,
		1, 1, 2, 3, 4, 5, 3, 1,
		1, 1, 2, 3, 4, 5, 2, 1,
		1, 1, 2, 3, 4, 5, 1, 1,
	};
	Asset **map = (Asset **)calloc(count, sizeof(Asset *));
	for (int i = 0; i < count; i++) {
		*(map+i) = a_new();
		map_assets[src_map[i]](*(map+i));
	}

	return map;
}

typedef struct {
	Step **data;
	int size;
	int top;
} Stack;
Stack *snew(int size){
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->size = size;
	s->top = 0;
	s->data = (Step **)calloc(size, sizeof(Step *));

	return s;
}
void spush(Stack *s, Step *step){
	*(s->data+s->top++) = step;
}
Step *spop(Stack *s){
	if (s->top == 0) return NULL;

	return *(s->data+(--s->top));
}
bool sisempty(Stack *s){
	return s->top == 0;
}

void draw_map(Asset **map, int *bucket){
	int count = pow(UNIT, 2);
	for (int i = 0; i < count; i++) {
		printf("%c", bucket[i] ? '*' : asset_patterns[(*(map+i))->type]);
		if (i%UNIT == UNIT - 1) {
			printf("\n");
		}
	}
}

Asset *rotate(Asset *orig){
	Asset *a = NULL;
	switch (orig->type) {
		case 1:
		case 2:
		case 3:
		case 5:
						a = a_new();
						map_assets[orig->type+1](a);
						break;
	}
	return a;
}

void find_path(Stack *stack, int *bucket, Asset **map
	, int next_entry, int next_pos, Stack *result){
	int count = pow(UNIT, 2);

	// 遇到已遍历或空组件即返回
	if (bucket[next_pos] || (*(map+next_pos))->type == 0) return;

	// 到达目标位置时
	if (next_entry == 0 && next_pos == 16){
		printf("bingo\n");
		memcpy(result->data, stack->data, stack->size * sizeof(Step *));
		result->top = stack->top;
		Step *p_step = (Step *)malloc(sizeof(Step));
		p_step->pos = next_pos;
		p_step->entry = next_entry;
		spush(result, p_step);
		return;
	}
	
	Asset *curr = *(map+next_pos);
	while (curr != NULL) {
		if (curr->dirs[next_entry]){
			Step *p_step = (Step *)malloc(sizeof(Step));
			p_step->asset = curr;
			p_step->pos = next_pos;
			p_step->entry = next_entry;
			spush(stack, p_step);
			bucket[next_pos] += 1;

			int entry = 0;
			for (int i = 0; i < 4; i++) {
				if (i != next_entry
						&& curr->dirs[i]){
					entry = (4+i-2)%4;
					int pos = (next_pos + dir_next[i]);
					if (pos >= 0 && count > pos){
						printf("entry:%d;pos:%d\n", entry, pos);
						find_path(stack, bucket, map
							, entry, pos, result);
					}
				}
			}

			bucket[next_pos] -= 1;
			spop(stack);
		}
		curr = rotate(curr);
	}
}

int main(int argc, int **argv){
	int count = pow(UNIT, 2)
		, bucket[count];
	for (int i = 0; i < count; i++) bucket[i] = 0;
	Asset **map = gen_map();
	draw_map(map, bucket);

	Stack *stack = snew(pow(UNIT, 2));
	Stack *result = snew(pow(UNIT, 2));
	find_path(stack, bucket, map
	, 3, 0, result);

	while (!sisempty(result)) {
		bucket[(spop(result))->pos] += 1;
	}
	draw_map(map, bucket);
}
