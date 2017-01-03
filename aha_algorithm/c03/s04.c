#include <stdio.h>
#include <stdlib.h>

#define N 3
#define R 3

typedef int (*PStop)(int *);

int stop(int *p_existed_y){
	int msg[N];
	int j = 0;
	for (int i = 0; i < R && j < N; i++) {
		if (*(p_existed_y+i) < N && *(p_existed_y+i) >= 0){
			msg[*(p_existed_y+i)] = i;
			j += 1;
		}
	}
	for (int i = 0; i < N; i++) {
		printf("%d", msg[i] + 1);
	}
	printf("\n");
	return 0;
}

// 深度遍历
// 以位置作为Ｘ轴，数字范围作为Y轴构成一个矩阵(图)然后遍历即可
// x/y 1 2 3
//  1  x x x
//  2  x x x
//  3  x x x
void dfs(int step, int *p_existed_y, PStop stop){
	if (step == N) {
		stop(p_existed_y);
		return;
	}
	else{
		for (int i = 0; i < R; i++) {
			if (*(p_existed_y+i) == -1){
				// i表示y值,*(p_existed_y+i)存储的是y值所占的位置
				*(p_existed_y+i) = step;
				dfs(step+1, p_existed_y, stop);
				*(p_existed_y+i) = -1;
			}
		}
	}
}

int main(int argc, char **argv){
	int *p_existed_y = (int *)calloc(R, sizeof(int));
	for (int i = 0; i < R; i++) {
		*(p_existed_y+i) = -1;
	}

	dfs(0, p_existed_y, stop);

	free(p_existed_y);
	return 0;
}
