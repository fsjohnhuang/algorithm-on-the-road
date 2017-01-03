#include <stdio.h>
#include <stdlib.h>

#define MAX 1111
#define EQ 2
#define ADD 2
int num[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};


int fun(int x){
	int n = 0;
	while (x / 10 > 0) {
		n += num[x % 10];
		x = x / 10;
	}

	n += num[x];

	return n;
}

int main(int argc, char **argv){
	int c, sum = 0, m = 16;
	for (int a = 0; a < MAX; a++) {
		for (int b = 0; b < MAX; b++) {
			c = a + b;
			if (fun(a) + fun(b) + fun(c) == m - EQ - ADD){
				sum += 1;
				printf("%d + %d = %d\n", a, b, c);
			}
		}
	}

	return 0;
}
