#include<stdio.h>

void test_domain();
void test_swap();

int main()
{
    test_domain();
    test_swap();
    return 0;    
}

//---- rel ---->
int num = 1;
void test_domain()
{
    int num = 2;
    printf("num local:%d, num global:%d \n", num, ::num);
}

void swap_1(int& a, int& b)
{
    /*
    a = a+b;
    b = a-b;
    a = a-b;
    */
    a = a^b; //??
    b = a^b;
    a = a^b;
}
void test_swap()
{
    int a=1, b=2;
    swap_1(a, b);
    printf("1,2 after swap_1, a:%d, b:%d \n",a,b);
}


