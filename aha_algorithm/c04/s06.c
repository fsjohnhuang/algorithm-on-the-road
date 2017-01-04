#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define UNIT 8

int assets[][2] = {
	{0, 0},
	{-1, -UNIT},
	{-UNIT, 1},
	{1, UNIT},
	{UNIT, -1},
	{-1, 1},
	{-UNIT, UNIT}
};
char asset_patterns[] = {
	' ',
	'J',
	'L',
	'F',
	'T',
	'-',
	'|'
};

typedef struct{
	int type; // 0: round; 1: line
	int asset;
	int dir[2];
} Asset;

Asset **gen_map(){
	int count = pow(UNIT, 2);
	int src_map[] = {
		1, 1, 2, 3, 4, 5, 6, 1,
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
		Asset **p = &*(map+i);
		*p = (Asset *)malloc(sizeof(Asset));
		(*p)->asset = src_map[i];
		memcpy((*p)->dir, assets[(*p)->asset], 2*sizeof(int));
		(*p)->type = (*p)->asset > 3 ? 0 : 1;
	}

	return map;
}

void draw_map(Asset **map){
	int count = pow(UNIT, 2);
	for (int i = 0; i < count; i++) {
		Asset *p = *(map+i);
		printf("%c", asset_patterns[p->asset]);
		printf("%d", p->asset);
		if (!i%UNIT) {
			printf("\n");
		}
	}
}

int main(int argc, int **argv){
	Asset **map = gen_map();
	draw_map(map);
}
