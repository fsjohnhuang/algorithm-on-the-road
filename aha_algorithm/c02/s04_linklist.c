#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int data;
	struct Node *next;
} Node;

Node *node_new(Node *prev, int data);
void append(int data, Node *prev);
void traverse(Node *start);

int main(){
	Node *head = NULL
		, *p = NULL;
	for (int i = 0; i < 5; i++) {
		if (head == NULL) {
			head = node_new(p, i);
			p = head;
		}
		else{
			p = node_new(p, i);
		}
	}

	traverse(head);
	append(12, head->next);
	traverse(head);

	return 0;
}

Node *node_new(Node *prev, int data){
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	if (prev != NULL) {
		Node *tmp = prev->next;
		prev->next = node;
		node->next = tmp;
	}

	return node;
}

void traverse(Node *start){
	while (start->next != NULL) {
		printf("haha%d\n", start->data);
		start = start->next;
	}
	printf("haha%d\n", start->data);
}

void append(int data, Node *prev){
	node_new(prev, data);
}
