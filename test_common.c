#include<stdio.h>

void test_domain();
void test_swap();
void test_class_obj();

int main()
{
    test_domain();
    test_swap();
    test_class_obj();
    return 0;    
}

//---- rel ---->
int num = 1;
void test_domain()
{
    int num = 2;
    printf("num local:%d, num global:%d \n", num, ::num);
}
class Test1{
};
void test_class_obj()
{
    Test1 t1;
    Test1 t2(); //both are ok.
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


