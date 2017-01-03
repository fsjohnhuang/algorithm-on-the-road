#include <stdio.h>
#include <stdlib.h>

#define N 9
#define R 9

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
	int n1 = 100*(msg[0]+1)+10*(msg[1]+1)+(msg[2]+1)
		, n2 = 100*(msg[3]+1)+10*(msg[4]+1)+(msg[5]+1)
		, s1 = 100*(msg[6]+1)+10*(msg[7]+1)+(msg[8]+1);

	if (n1 + n2 == s1)
	{
		printf("%d+%d=%d\n", n1, n2, s1);
	}
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
