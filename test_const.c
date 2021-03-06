#include <stdio.h>

const int get_const_int();
const char* get_const_str();
void test_class_const_function();
void test_class_const();
void test_const_in_4k_readonly_page();
class Test1;

int main()
{
    int m = 100;
    //1.
    const int a1 = 1;    
    const int* p1 = &a1;
    //*p1 = 11;  //error !
    //2.
    int a2 = 2;    
    int* const p2 = &a2; //not int const *
    *p2 = 22;
    //p2 = &m;   //error !(error: assignment of read-only variable ‘p2’) 指针常量不能被修改!
    printf("const int *:%p, int const *:%p \n", p1, p2);
    //3.
    const int a3 = get_const_int();
    int a4 = get_const_int();
    //4.   for pointer
    const char* p3 = get_const_str();
    //char* p4 = get_const_str(); //从类型‘const char*’到类型‘char*’的转换无效 !
    //5.   const class member function
    test_class_const_function();
    //
    test_class_const();
    //
    test_const_in_4k_readonly_page();
    return 0;
}



//------------------rel------------------->
const int get_const_int(){
    return 1;
}

const char* get_const_str(){
    return "test";
}

class Item
{
public:
    int m_val;
};
class Test1
{
public:
    Test1():m_pitem(new Item){}
    ~Test1(){ delete m_pitem; }
    int m_test;
    mutable int m_mt;
    void Push(int elem);
    int Pop(void);
    int GetCount(void) const; // const 成员函数
private:
    int m_num;
    int m_data[100];
    Item* m_pitem;
};
int Test1::GetCount(void) const
{
    //++m_num; // 编译错误，企图修改数据成员m_num
    //Pop(); // 编译错误，企图调用非const 函数
    m_mt = 100; //ok, for it is mutable   这样都行。。。。。。。。
    //
    //m_pitem = NULL; // member ‘Test1::m_pitem’ in read-only object
    m_pitem->m_val = 101; //不修改指针，但是你修改指针对象对应的内容还是可以的.

    return m_num;
}

void test_class_const_function()
{
    Test1 t1;
    t1.GetCount();
}

class Test2{
public:
    Test2():m(1){ n=2; }
    const int m;
    int n;
    //
    void run1(){}
    void run2()const {}
};
void test_class_const()
{
    /*
    1\const对象rodata?  -> no
    2\const成员函数和非const成员函数存储位置 ->no but .text
      这两个函数的全局符号是？区别一下 
    3\const对象访问成员函数必须找到'对应的含有const的全局符号'? ->no, 应该是先隐式转换和匹配函数
    const变量 vs 常量区？
    */

    const Test2 t21; 
    printf("%s const class obj add:%p \n", __FUNCTION__,&t21);
    printf("%s class const mem fun:%p \n", __FUNCTION__,&Test2::run2);
    //printf("%s class mem fun:%p \n", &(t21.run1)); //错误：ISO C++ 不允许通过取已绑定的成员函数的地址来构造成员函数指针。请改用‘&Test2::run2’ [-fpermissive]   函数地址本身就是在.text里面
    printf("%s class       mem fun:%p \n", __FUNCTION__,&Test2::run1);

    //t21.run1(); //将‘const Test2’作为‘void Test2::run1()’的‘this’实参时丢弃了类型限定   const难转非const? 非const易转const?
    t21.run2();

    Test2 t22; 
    t22.run1();
    t22.run2();

    const Test2* pt21 = &t22; //没问题
    //Test2* pt22 = &t21; //从类型‘const Test2*’到类型‘Test2*’的转换无效
    Test2* pt23 = const_cast<Test2*>(&t21); //从类型‘const Test2*’到类型‘Test2*’的转换无效
}

class Test3{
public:
    static const int x;
    static int y;
    //static const enum Enum{ y=3 };
};
const int Test3::x = 10; //static const init.
int Test3::y = 10;//not: static int Test3::y = 10; //static const init.


void test_const_in_4k_readonly_page()
{
    int a1 = 0;
    const int a2 = 0;
    int a3 = 0;
    printf("%s a1:%p, a2:%p, a3:%p in sequence ??? \n",__FUNCTION__,&a1,&a2,&a3);
    //so it is not 4k_readonly_page, but pointer mark
}
