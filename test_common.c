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
void test_string();
void test_struct();
void test_pointer_len();
void test_ascii();
void test_if();

int main()
{
    printf("%s %d %s %s \n",__FILE__, __LINE__, __DATE__, __TIME__);
    test_domain();
    test_swap();
    test_class_obj();
    test_operator();
    test_switch();
    test_type();
    test_union_pointer_to_int();
    test_addressing();
    test_typedef();
    test_define();
    test_string();
    test_struct();
    test_pointer_len();
    test_ascii();
    test_if();

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
    //int *p = nullptr; //需开启-std=c++0x编译选项
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
    int b=1,c=2;
    a = b+++c;
    printf("%s a=b+++c a:%d b:%d c:%d \n",__FUNCTION__,a,b,c); //operator priority
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

class Base{};
class Derived:public Base{
    int m;
};
void test_addressing()
{//sizeof是C/C++中的一个操作符（operator），简单的说其作用就是返回一个对象或者类型所占的内存字节数。
    int *pt = (int*)0x8048000;
    printf("%s int* +1:%p \n",__FUNCTION__,(int*)pt+1);
    pt = (int*)0x8048000;
    printf("%s char* +1:%p \n",__FUNCTION__,(char*)pt+1);
    //尝试使用sizeof(*pt)来获取类的size
    Base *pbase = new Derived();
    Derived *pderived = new Derived();
    printf("%s pbase size:%d \n",__FUNCTION__,sizeof(*pbase)); //汇编层面应该知道pt的寻址？
    printf("%s pderived size:%d \n",__FUNCTION__,sizeof(*pderived));
    delete pbase;
    delete pderived;
}

void test_typedef()
{
    typedef char *pStr; //can 'char *pStr', merge together
    const pStr pt = "hello,world";
    //pt++;  //type pStr has '++' ???   baidu typedef for answer
    printf("%s buf:%s \n",__FUNCTION__,pt);

    //typedef 0x01 NULL; //error. expected unqualified-id before numeric constant
    #define NULL (int*)0x01
    int *pt2 = NULL;
    printf("%s (#define NULL (int*)0x01) pt2:%p \n",__FUNCTION__,pt2);
}

void test_define()
{
    #define f(x) x*x 
    int m = 1;
    printf("%s m:%d, end:%d \n",__FUNCTION__,m,f(m++));
}

#include<string.h>
#include<stdlib.h>
char* get_str_from_constant_area(){
    char *buf = "hello";
    return buf;
}
char* get_str_from_stack(){
    char buf[] = "hello";
    return buf;
}
void test_string()
{
    //char buf[]; //错误：‘buf’的存储大小未知
    char buf[] = ""; 
    strcpy(buf, "123");
    printf("%s buf:%s \n",__FUNCTION__,buf);
    strcpy(buf, "123444567");
    printf("%s buf:%s len:%d size:%d dangerous????? \n",__FUNCTION__,buf,strlen(buf),sizeof(buf)); //为什么还能寻址到2之后？？？
    //
    char *buf2 = (char*)malloc(100);
    memset(buf2, 0, 100);
    strcpy(buf2, "hello");
    printf("%s malloc buf2:%s len:%d \n",__FUNCTION__,buf2,strlen(buf2)); //为什么还能寻址到2之后？？？
    delete buf2;
    //
    //得到函数返回的字符串常量指针？ http://blog.csdn.net/n567656756765676567/article/details/6908929
    printf("%s get from contant area:%s \n",__FUNCTION__,get_str_from_constant_area()); 
    printf("%s get from stack:%s \n",__FUNCTION__,get_str_from_stack()); 
    //不同定义会引用到同一个字符串常量吗? oh my god, it is
    printf("%s contant area p1:%p \n",__FUNCTION__,get_str_from_constant_area()); 
    char *buf11 = "hello";
    printf("%s contant area p2:%p (p2=p1?oh my god, really it is !)\n",__FUNCTION__,buf11); 
    char *buf12 = "hell";
    printf("%s contant area p3:%p \n",__FUNCTION__,buf12); 
}

struct STest1{
    int m;
    char buf[0];
};
void test_struct()
{
    struct STest1 st1;
    printf("%s st1 size:%d, addr:%p, buf:%p \n", __FUNCTION__,sizeof(struct STest1),(int*)&st1,(int*)( (&st1)->buf ));
}

void test_pointer_len() //指针大小保存在哪里？
{
    char *buf = (char*)malloc( sizeof(char)*6 );
    //printf("%s buf:%p, %d \n",__FUNCTION__,buf,*((int*)(&buf)+1));
}

void test_ascii()
{
    printf("%s gan 0 is %d \n",__FUNCTION__,int('\0'));
    printf("%s gan 1 is %d \n",__FUNCTION__,int('\1'));
    printf("%s ' ' is %d \n",__FUNCTION__,int(' '));
}

void test_if()
{
    if ('\0')
        printf("gan 0 is true \n");
    else
        printf("gan 0 is false \n");

    if ('\n')
        printf("gan n is true \n");
    else
        printf("gan n is false \n");   

    if (-1)
        printf("-1 is true \n");
    else
        printf("-1 is false \n");   
}


