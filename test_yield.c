#include <stdio.h>

void test1()
{
	static int val = 0;
	val += 1;
	printf("val changed: %d \n",val);
}

int test_case(void){
	static int i,state=0;
	switch(state){
		case 0:
			printf("case 0. \n");
			for (i=0; i<10; ++i){
				state = 1;
				return i;
				case 1:
					printf("case 1. \n");
					break;
				case 2:
					printf("case 2. \n");
					break;
			}
	}
	printf("%s end.\n",__FUNCTION__);
}

int main()
{
	for (int i=0; i<10; ++i){
		test1();
	}

	test_case();
	test_case();
}

