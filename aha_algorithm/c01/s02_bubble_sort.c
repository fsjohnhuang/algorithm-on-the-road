#include <stdio.h>
#include <stdlib.h>


struct student{
	char *name;
	char score;
};

void bubble_sort(int size, float *source);
void student_bubble_sort(int size, struct student *source);

int main(){
	/*float source[] = {2.1, 3.1, 1.1, 4.4};
	int size = sizeof(source) / sizeof(float);
	bubble_sort(size, source);

	int i;
	for(i = 0; i < size; ++i){
		printf("%f\n", source[i]);
	}*/

	struct student students[3];
	students[0].name = "john";
	students[0].score = 12;
	students[1].name = "mary";
	students[1].score = 22;
	students[2].name = "kay";
	students[2].score = 2;

	student_bubble_sort(3, students);

	int i;
	for(i = 0; i < 3; ++i){
		printf("%s:%d\n", students[i].name, students[i].score);
	}
}

// 冒泡排序
// 时间复杂度：O(N^2)
void bubble_sort(int size, float *source){
	int i,j;
	float tmp;
	for(i = 0; i < size; ++i){
		for(j = 0; j < size - i - 1; ++j){
			if (*(source+j) < *(source+j+1)){
				tmp = *(source+j);
				*(source+j) = *(source+j+1);
				*(source+j+1) = tmp;
			}
		}
	}
}

void student_bubble_sort(int size, struct student *source){
	int i,j;
	struct student *curr, *next, tmp;
	for(i = 0; i < size; ++i){
		for(j = 0; j < size - i - 1; ++j){
			curr = source+j;
			next = curr + 1;
			if (curr->score < next->score){
				tmp = *curr;
				*curr = *next;
				*next = tmp;
			}
		}
	}
}
