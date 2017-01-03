#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EQ 2
#define ADD 2
int num[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main(){
	int m = 19;
	m = m - EQ - ADD;
	int len = sizeof(num) / sizeof(int);

	char *strs[20];
	int k = 0;
	for (int idx = 0; idx < 20; idx++) {
		strs[idx] = NULL;
	}

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			int sum = i+j;
			int the_unit = sum - 10;
			int decade = the_unit >= 0 ? 1: 0;
			the_unit = the_unit >= 0 ? the_unit : sum;
			
			char *str = (char *)calloc(6, sizeof(char));
			if (num[i] + num[j] + (decade ? num[decade] : 0) + num[the_unit] == m) {
				if (decade){
					sprintf(str, "%d,%d,%d%d", i, j, decade ,the_unit);
				}
				else{
					sprintf(str, "%d,%d,%d", i, j, the_unit);
				}
				int existed = 0;
				for (int idx = 0; idx < 20 && strs[idx] != NULL && !existed; idx++) {
					existed = strs[idx] == str;
				}
				if (!existed){
					strs[k] = str;
					k += 1;
				}
			}
		}
	}


	char *delimit = ",";
	int d_len = strlen(delimit);
	for (int idx = 0; idx < 20 && strs[idx] != NULL; idx++) {
		char *s = strs[idx];
		char *buf = strstr(s, delimit);
		*buf = '\0';
		printf("%s+", s);

		s = buf + d_len;
		buf = strstr(s, delimit);
		*buf = '\0';
		printf("%s=", s);

		s = buf + d_len;
		printf("%s\n", s);
	}

	return 0;
}
