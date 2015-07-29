/*
 * printf format.
 */
#include<stdio.h>

int main()
{
	printf("|%4x|\n",16);
	printf("|%-4x|\n",16);
	printf("|%4d|\n",2);
	printf("|%-4d|\n",2);
	printf("|%4s|\n","abc");
	printf("|%4s|\n","abcdef");
	printf("|%-4s|\n","abc");
	return 0;
}

