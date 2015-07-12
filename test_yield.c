#include <stdio.h>

void test1()
{
	static int val = 0;
	val += 1;
	printf("val changed: %d \n",val);
}

int main()
{
	for (int i=0; i<10; ++i){
		test1();
	}
}

