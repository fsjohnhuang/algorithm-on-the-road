#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define UNIT 13

typedef struct{
	int *data;
	int size;
	int top;
} Stack;

Stack *s_new(int size){
	Stack *s = malloc(sizeof(Stack));
	s->size = size;
	s->data = calloc(size, sizeof(int));
	s->top = 0;

	return s;
}
int is_empty(Stack *s){
	return s->top == 0;
}
int is_full(Stack *s){
	return s->size == s->top;
}
void push(Stack *s, int v){
	if (is_full(s));else {
		*(s->data+s->top++) = v;
	}
}
int pop(Stack *s){
	if (is_empty(s)) return -1;

	s->top -= 1;
	return *(s->data+s->top);
}
int peek(Stack *s){
	if (is_empty(s)) return -1;

	int top = s->top - 1;
	return *(s->data+top);
}

char *draw_map(){
	char source[]= {
		'$','$','$','$','$','$','$','$','$','$','$','$','$',
		'.','.','.','.','.','.','.','$','.','.','.','.','$',
		'$','$','$','.','$','.','$','.','$','.','$','.','$',
		'$','.','.','.','.','.','.','.','$','.','.','M','$',
		'$','.','$','.','$','$','$','.','$','.','$','.','$',
		'$','.','.','.','.','.','.','.','$','.','.','.','$',
		'$','.','$','.','$','.','$','.','$','.','$','$','$',
		'$','$','.','.','.','.','.','.','.','.','.','.','$',
		'$','.','$','.','$','.','$','$','$','.','$','.','$',
		'$','.','.','.','.','$','.','.','.','.','.','.','$',
		'$','.','$','.','$','.','$','.','$','.','$','.','$',
		'$','.','.','.','.','.','.','$','.','.','.','.','$',
		'$','$','$','$','$','$','$','$','$','$','$','$','$'
	};

	int count = pow(UNIT, 2);
	char *map = calloc(count, sizeof(char));
	for (int i = 0; i < count; i++) {
		*(map + i) = source[i];
	}

	return map;
}

void traverse(char *map){
	int count = pow(UNIT, 2);
	for (int i = 0; i < count; i++) {
		printf(" %c ", *(map+i));
		if ((i+1) % UNIT == 0) {
			printf("\n");
		}
	}
}

int is_target(char c){
	return c == 'M';
}
int is_solid_wall(char c){
	return c == '$';
}
int is_aisle(char c){
	return c == '.';
}

int find_entry(char *map){
	int entry = -1, count = pow(UNIT, 2);
	for (int i = 0; i < UNIT && entry == -1; i++) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}
	for (int i = count - 1; i >= count - UNIT && entry == -1; i--) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}
	for (int i = 0; i < count && entry == -1; i += UNIT) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}
	for (int i = UNIT; i < count && entry == -1; i += UNIT) {
		if (is_aisle(*(map+i))) {
			entry = i;
		}
	}

	return entry;
}

int upward(int pos){
	int n = pos - UNIT;
	return n >= 0 ? n : -1;
}
int forward(int pos){
	int n = pos + 1;
	return n < pow(UNIT, 2) ? n : -1;
}
int downward(int pos){
	int n = pos + UNIT;
	return n < pow(UNIT, 2) ? n : -1;
}
int backward(int pos){
	int n = pos - 1;
	return n >= 0 ? n : -1;
}

typedef int (*Go_award)(int);

void dfs(int *bucket, char *map, Stack *s, Stack *ms){
	int pos = peek(s);

	if (is_solid_wall(*(map+pos))
			|| *(bucket+pos) > 1) {
		return;
	}

	if (is_target(*(map+pos))){
		if (is_empty(ms)
				|| s->top < ms->top) {
			ms->size = s->size;
			ms->top = s->top;
			ms->data = calloc(ms->size, sizeof(int));
			memcpy(ms->data, s->data, ms->size);
		}
		return;
	}

	Go_award f[] = {upward, forward, downward, backward};
	int next;
	for (int i = 0; i < 4; i++) {
		next = f[i](pos);
		if (next >= 0){
			push(s, next);
			bucket[next] += 1;
			dfs(bucket, map, s, ms);
			pop(s);
			bucket[next] -= 1;
		}
	}
}

int main(){
	int count = pow(UNIT, 2);
	char *map = draw_map();
	int bucket[count];
	for (int i = 0; i < count; i++) {
		bucket[i] = 0;
	}
	printf("Playground is like below:\n");
	traverse(map);

	int entry = find_entry(map);
	bucket[entry] += 1;

	Stack *ms = s_new(pow(UNIT, 2))
		, *s = s_new(pow(UNIT, 2));
	push(s, entry);
	dfs(bucket, map, s, ms);

	printf("\n\n");
	pop(ms);
	while (!is_empty(ms)) {
		*(map+pop(ms)) = '>';
	}
	traverse(map);

	free(map);

	return 0;
}

