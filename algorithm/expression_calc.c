/*
 * a+b/c-d*e 
 */
 #include <stdio.h>
 #include <string.h>

int calc(char *str)
{
	int rets[16];
	memset(rets, 0, 16);

	char *pt = str;
	char tmp[8];
	while(pt-str < strlen(str)){
		if (sscanf(pt, "%[^+-/*]", tmp)){
			printf("%s \n",tmp);
			pt += strlen(tmp);	
		}
		else if (sscanf(pt, "%[+-/*]", tmp)){
			printf("%s \n",tmp);
			pt += strlen(tmp);	
		}
	}
}

int main()
{
	char str[] = "12+3/5-32*8";
	calc(str);
	return 0;
}

