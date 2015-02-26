#include<stdio.h>

void test_domain();
void test_swap();
void test_class_obj();
void test_operator();
void test_switch();
void test_type();

int main()
{
    test_domain();
    test_swap();
    test_class_obj();
    test_operator();
    test_switch();
    test_type();
    return 0;    
}

//---- ---- rel ---- ---->
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

void test_type()
{
    unsigned int a = 6;
    int b = -6;
    printf("uint 6 + int -6 = %d \n",a+b);
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

int _test1(){ 
    int tmp=1; 
    return tmp; //like operator++(int) return tmp
}
void test_operator()
{
    int a = 0;
    //(a++) += a; //赋值运算的左操作数必须是左值  why ??
    //(a++) = 0; 
    //_test1() = a;
}

class Test2{
public:
    int operator()(){ return 1; }
};
void test_switch()
{
    int i = 3;
    switch(i){
        default:
            printf("switch(int)\n");
    }
    char c = 'a';
    switch(c){
        default:
            printf("switch(char)\n");
    }
    /*
    char *buf = "he";
    switch(buf){
        case "he"://switch 语句中的值不是一个整数
            printf("switch(char)\n");
    }
    */
    Test2 t2;
    switch(t2()){
        case 1:
            printf("switch( int class::operator() )\n");
    }
}

