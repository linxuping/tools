#include<stdio.h>

void test_domain();
void test_swap();
void test_class_obj();
void test_operator();
void test_switch();
void test_type();
void test_union_pointer_to_int();
void test_addressing();
void test_typedef();
void test_define();

void test_add_1_to_MAX();

int main()
{
    test_domain();
    test_swap();
    test_class_obj();
    test_operator();
    test_switch();
    test_type();
    test_add_1_to_MAX();
    test_union_pointer_to_int();
    test_addressing();
    test_typedef();
    test_define();
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

void test_type() // ???
{
    unsigned int a = 6;
    int b = -6;
    printf("%s uint 6 + int -6 > 6 ? %d \n",__FUNCTION__,a+b>6);
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

union UTest{
    int val;
    int *pt;
    char c;
    double d;
};
void test_union_pointer_to_int()//test union的共享属性
{
    int m = 0;
    UTest t1;
    t1.pt = &m;
    printf("%s UTest.pt:%p, UTest.val:%d, UTest.c:%c \n",__FUNCTION__,t1.pt,t1.val,t1.c);
    printf("%s UTest size:%d \n",__FUNCTION__, sizeof(UTest));
}

#include<limits.h>
void test_add_1_to_MAX()
{
    //printf("int max:%d \n",INT_MAX);
    int count = 0;
    for(int i=0; i<INT_MAX; ++i)
        count += i;
    printf("%s  count:%u > INT_MAX:%d \n",__FUNCTION__,count,INT_MAX);
    //INT_MAX*2
}

void test_addressing()
{
    int *pt = (int*)0x8048000;
    printf("%s int* +1:%p \n",__FUNCTION__,(int*)pt+1);
    pt = (int*)0x8048000;
    printf("%s char* +1:%p \n",__FUNCTION__,(char*)pt+1);
}

void test_typedef()
{
    typedef char *pStr; //can 'char *pStr', merge together
    const pStr pt = "hello,world";
    //pt++;  //type pStr has '++' ???   baidu typedef for answer
    printf("%s buf:%s \n",__FUNCTION__,pt);
}

void test_define()
{
    #define f(x) x*x 
    int m = 1;
    printf("%s m:%d, end:%d \n",__FUNCTION__,m,f(m++));
}


