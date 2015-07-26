/*
 * abc  a b c ab ac bc abc 
 */
#include <stdio.h>
#include <string.h>

int g_count = 0;

void run(char *str, int check, int start, int depth, int max)
{
	if (depth == max) {
		for (int i=0 ;i<strlen(str); ++i){
			if (check&(1<<i)) printf("%c ",str[i]);
		}
		++g_count;
		printf("\n");
		return;
	}
	for (int i=start; i<strlen(str); ++i){
		if (str[i]!='\0' && !(check&(1<<i))){
			int tmpcheck = check | (1<<i);
			run(str, tmpcheck, i+1, depth+1, max);
		}
	}

}

int main()
{
	char *str = "abc";
	int check = 0;
	int depth = 0;
	for (int i=1; i<=strlen(str); ++i){
		g_count = 0;
		run(str, check, 0, depth, i);
		printf("%d count:%d \n",i, g_count);
	}


	return 0;
}

