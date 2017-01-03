#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define TAIL -1
#define AVAL -2

typedef struct LinkList{
	int size;
	int head;
	int *data;
	int *next;
} LinkList;

LinkList * new(int size);
int append(int data, LinkList * list);
int del(int index, LinkList * list);
int len(LinkList * list);

int main(){
	int l = 0;
	LinkList * list = new(2);
	append(12, list);
	append(22, list);
	append(42, list);
	del(0, list);
	append(42, list);
	l = len(list);
	printf("%d\n", l);


	return 0;
}

LinkList * new(int size){
	LinkList * list = (LinkList *)malloc(sizeof(LinkList));

	list->size = size;
	list->data = calloc(size, sizeof(int));
	list->next = calloc(size + 1, sizeof(int));
	*list->next = TAIL;
	for (int i = 1; i <= size; i++) {
		*(list->next + i) = AVAL;
	}

	return list;
}

int del(int i, LinkList * list){
	i += 1;
	int res = FALSE;
	if (i >= 1 && len(list));else{
		return res;
	}

	int curr_i = 0;
	int path[list->size + 1];
	int n = 0;
	while (curr_i < i && *(list->next+n) != TAIL){
		path[curr_i] = n;
		curr_i += 1;
		n = *(list->next+n);
	}
	if (curr_i == i){
		res = TRUE;

		*(list->next+path[curr_i - 1]) = *(list->next+n);
		*(list->next+n) = AVAL;
	}

	return res;
}

int len(LinkList * list){
	int l = -1;
	for (int i = 0; i < list->size + 1; i++) {
		if (*(list->next+i) != AVAL) {
			l += 1;
		}
	}

	return l;
}

int append(int data, LinkList * list){
	int res = FALSE;
	if (len(list) == list->size){
		return res;
	}

	int n = *list->next;
	while (*(list->next+n) != TAIL) {
		n = *(list->next+n);
	}

	int a = -1;
	for (int i = 1; i <= list->size && a == -1; i++) {
		if (list->next[i] == AVAL){
			a = i;
		}
	}
	*(list->next+n) = a;
	*(list->next+a) = TAIL;
	*(list->data+a-1) = data;

	return TRUE;
}
