/*
 * A++B+CD+E+FGH -> +++++ABCDEFGH 
 */
#include <stdio.h>
#include <string.h>

void move(char* str)
{
	int start=0, count=0;
	int len = strlen(str);
	for (int i=0; i<len; ++i){
		if (str[i] != '+'){
			if (count == 0)
				start = i;
			count++;
		}
		else{
			memmove(&str[start+1], &str[start], count);
			str[start] = '+';
			start++;
		}
	}
}

int main()
{
	char str[] = "+A++B+CD+E+FGH++";
	printf("from: %s \n",str);
	move(str);
	printf("to: %s \n",str);
	return 0;
}

