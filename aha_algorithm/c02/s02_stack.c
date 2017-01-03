#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int *data;
	int top;
	int size;
}Stack;

Stack create_stack(int size);

int main(){
	char *source = "[{]}";
	int len = strlen(source);

	Stack stack = create_stack(5);
	char c;
	for (int i = 0; i < len; i++) {
		c = *(source+i);
		switch (c) {
			case '[':
			case '{':
			case '(':
				*(stack.data+stack.top) = c;
				stack.top += 1;
				break;
			case ']':
				if (stack.top > 0 
						&& *(stack.data+stack.top - 1) == '['){
					stack.top -= 1;
				}
				break;
			case '}':
				if (stack.top > 0 
						&& *(stack.data+stack.top - 1) == '{'){
					stack.top -= 1;
				}
				break;
			case ')':
				if (stack.top > 0 
						&& *(stack.data+stack.top - 1) == '('){
					stack.top -= 1;
				}
				break;
		}
		
	}

	printf("%d", stack.top);
	

	return 0;
}

Stack create_stack(int size){
	Stack stack;
	stack.data = calloc(size, sizeof(int));
	stack.top = 0;
	stack.size = size;

	return stack;
}
