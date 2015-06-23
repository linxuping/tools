#include <stdarg.h>
//no bool definition in c 
#define bool int
#define false 0
#define true 1

void test_open_c_overload();

int main()
{
	bool b = true;
	test_open_c_overload();
	return 0;
}

//---- ---- function definition ---- ----
void open_c_overload(char *file, ...){
	va_list v;
	va_start(v,file);
	int next = va_arg(v, int);
	if (1 == next)
		printf("open_c_overload(%s, %d)\n",file,next);
	else if (next == 2)
		printf("open_c_overload(%s, %d, %d)\n",file,next,va_arg(v, int));
	else
		printf("open_c_overload unknow\n");
}
void test_open_c_overload()
{
	open_c_overload("a.out",1);
	open_c_overload("a.out",2,4);
}

