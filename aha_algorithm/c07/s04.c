#include <stdio.h>
#include <stdlib.h>

typedef int boss_t;
typedef int criminal_t;
typedef boss_t* criminals_t;

void merge(criminals_t criminals, criminal_t lc, criminal_t rc){
	boss_t boss = (boss_t)rc;
	while (boss != *(criminals+boss) && boss != lc) {
		boss = *(criminals+boss);
	}

	if (boss != lc) {
		*(criminals+boss) = lc;
	}
}

int main(int argc, int **argv){
	int count = 9;
	criminals_t criminals = (criminals_t)calloc(count, sizeof(boss_t));
	for (int i = 0; i < count; i++) {
		*(criminals+i) = i;
	}

	int unit = 2
		, relations[] = {
			0, 1,
			2, 3,
			4, 1,
			3, 5,
			1, 5,
			7, 6,
			8, 6,
			0, 5,
			1, 3
		}
		, relations_count = sizeof(relations)/sizeof(int)/2;

	for (int i = 0; i < relations_count; i++) {
		criminal_t lc = relations[i*unit];
		criminal_t rc = relations[i*unit+1];
		merge(criminals, lc, rc);
	}

	for (int i = 0; i < count; i++) {
		boss_t boss = (boss_t)i;
		while (boss != *(criminals+boss)) {
			boss = *(criminals+boss);
		}
		printf("%d belongs to %d\n", i, boss);
	}
	
	return 0;
}
