#include<stdlib.h>
#include<limits.h>
#include "common.h"

/*
 * test area
 */
void test_operator_overlap();
void test_structor_virtual();
void test_class_mem_fun_ptr();
void test_class_method_hide();
void test_class_method_hide_solved();
void test_class_method_hide_solved2();
void test_get_base_offset();
void test_cast();
void test_nullptr_visit_memfun();
void test_assignment_or_copy();
void test_initilize_list_seq();
void test_private_inheritance();
class class_test_static;
/*
 * test area end.
 */

int main()
{
    test_operator_overlap();
    test_structor_virtual();
    test_class_mem_fun_ptr();
    test_class_method_hide();
    //
    test_get_base_offset();
    //
    test_cast();
    //
    test_nullptr_visit_memfun();
    //
    test_assignment_or_copy();
    //
    test_initilize_list_seq();
    //
    test_class_method_hide_solved();
    test_class_method_hide_solved2();
    //
    test_private_inheritance();
		//
}


//---- ---- rel ---- ---->
class Arr
{
public:
    Arr():a(1){}
    const int a;
    int b;
    char* operator[](int i){ 
        printf("char* operator[]\n");
        return "hello"; 
    }
    //const char* operator[](int i){ //‘const char* Arr::operator[](int)’无法被重载
    const char* operator[](int i)const { 
        printf("visit no-const member:%d \n",this->b);
        return const_cast<const char*>( (*this)[i] ); //not *this[i]
    }
};
void test_operator_overlap()
{
    ENTER_TEST();
    Arr a1;
    char* buf1 = a1[1];
    printf("%s const member:%d \n", __FUNCTION__,a1.a);
    //const Arr a2;
    //const char* buf2 = a2[1];
}

class Base{
public:
    Base(){run("construct1 >>> ");}
    virtual ~Base(){run("destruct1");}
    virtual void run(const char* f){ printf("base %s\n",f); }
};
class Derived: public Base{
public:
    Derived():m(2){run("construct2 >>> ");}
    ~Derived(){run("destruct2");}
    void run(const char* f){ printf("derived %s\n",f); }
    void display(){ printf("only derived display \n"); }

    int m;
};
class TClass1{
public:
    enum Enum{ EItem=2,EItem2=32767,EItem3=UINT_MAX+200 }; //不占内存  ????
};
void test_structor_virtual()
{
    ENTER_TEST();
    printf("%s 基类构造->子类构造? 虚析构掉用虚函数没有多态! \n",__FUNCTION__);
    Base* pt = new Derived();
    delete pt;
    printf("%s 测试结束! \n",__FUNCTION__);
    //
    printf("%s 截断后的多态! \n",__FUNCTION__);
    Derived de;
    Base& bb = de;//基类类型 对子类对象的引用，如果调用子类的非重写方法，就会调不到
    bb.run("hello");
    printf("%s 测试结束! \n",__FUNCTION__);
    //bb.display();
    printf("%s 直接delete通过base指向derived的指针,内存泄露? \n",__FUNCTION__);
    Derived* pd = new Derived();
    Base *pb = pd;
    printf("Derived size:%d m:%d  \n", sizeof(Derived), *((int*)pb+1));
    delete pb;
    printf("Derived after del m:%d  \n", *((int*)pb+1));
    printf("%s 测试结束! \n",__FUNCTION__);

    printf("%s 连续调用~destruct! \n",__FUNCTION__);
    pd = new Derived();
    pd->~Derived();
    pd->~Derived();
    pd->~Derived();
    free(pd);
    printf("%s 测试结束! \n",__FUNCTION__);

    printf("%s enum占内存吗? \n",__FUNCTION__);
    printf("%s TClass1 size:%d item1:%d item2:%d item3:%d(这里有异常，看来enum不能超过UINT_MAX ! ) \n",__FUNCTION__, sizeof(TClass1),TClass1::EItem, TClass1::EItem2, TClass1::EItem3); //2 ???????
    printf("%s 测试结束! \n",__FUNCTION__);
}

class Base1{
public:
    void run(){ printf("(b.*prun)(); \n"); }
};
typedef void(Base1::*PRUN)(); //take care
void test_class_mem_fun_ptr()
{
    ENTER_TEST();
    Base1 b;
    PRUN prun= &Base1::run;
    (b.*prun)(); //(b.(*prun))(); //错误：expected unqualified-id before ‘(’ token
    //_ZN5Base13runEv(&b);
    //Base1::run(&b);
}


class Base2{
public:
    virtual void run(int a){ printf("base value:%d \n",a); }
};
class Derived2:public Base2{
public:
    void run(float f){ printf("derive value:%f \n",f); }
};
void test_class_method_hide()
{
    ENTER_TEST();
    Derived2 de;
    int a = 1;
    int f = 1.0f;
    de.run(a);
    de.run(f);
}

class Derived20:public Base2{
public:
    void run(char *buf){ printf("derive value:%s \n",buf); }
    using Base2::run;
};
void test_class_method_hide_solved()
{
    ENTER_TEST2("用using把隐藏的函数加回来！");
    Derived20 de;
    char buf[] = "hello";
    int f = 1.0f;
    de.run(buf);
    de.run(f);
}

class Base21{
public:
    virtual void run(){ printf("virtual void run\n"); }
    void run(int m){ printf("void run(int) \n"); }
};
class Derived21: private Base21{
public:
    void CallBaseRun(){ Base21::run(1); } 
};

void test_class_method_hide_solved2()
{
    ENTER_TEST();
    Derived21 de;
    //de.run(); //‘virtual void Base21::run()’无法访问,错误：‘Base21’是‘Derived21’的一个不可访问的基类
}


class Base31{
public:
    virtual void run1(){}
    int m1;
};
class Base32{
public:
    Base32():m2(2){}
    int m2;
};
class Derived3:public Base31,public Base32{
};
/* ???? (typedef PRInt32 PROffset32; typedef int PRInt32;)  mozilla/xpcom/glue/nsISupportsImpl.h, CPP, unix, cp936
622 #define NS_INTERFACE_TABLE_ENTRY(_class, _interface)                          \
623   { &_interface::COMTypeInfo<int>::kIID,                                      \
624     PROffset32( reinterpret_cast<char*>(static_cast<_interface*>((_class*)0x1000)) -         \
626                 reinterpret_cast<char*>((_class*)0x1000) )
627   },
*/
//char 一个字节的步长  
#define offset(derived,base) int( reinterpret_cast<char*>(static_cast<base*>((derived*)0x1000)) -\
                                  reinterpret_cast<char*>((derived*)0x1000) )
//应该可以使用dynamic_cast，仅仅是data read noly！没有写没问题, 但是如果是在运行期，可能改了进程空间某些有意义的内存，结果就不能预料了
void test_get_base_offset()
{
    ENTER_TEST();
    printf("%s 对象内存模型 基类偏移量 Derived3 Base32 offset:%d \n",__FUNCTION__,offset(Derived3,Base32));
    printf("%s 对象内存模型 基类偏移量 static_cast<base*>((derived*)0x10):%p \n",__FUNCTION__,static_cast<Base32*>((Derived3*)0x10) );
    printf("%s 对象内存模型 基类偏移量 static_cast<base*>((derived*)0x0):%p \n",__FUNCTION__,static_cast<Base32*>((Derived3*)0x0) );
    printf("%s 对象内存模型 基类偏移量 (base*)((derived*)0x0):%p \n",__FUNCTION__,(Base32*)((Derived3*)0x0) );
    printf("%s 对象内存模型 基类偏移量 (derived*)0x0:%p \n",__FUNCTION__,((Derived3*)0x0) );
}

void test_cast()
{
    ENTER_TEST();
    Derived3 de;
    printf("%s derived:%p \n",__FUNCTION__,&de);
    printf("%s base2:%p 基类指向子类的指针地址，和原来指针地址不一致 \n",__FUNCTION__,(Base32*)&de);
    printf("%s base2:%p static_cast \n",__FUNCTION__,static_cast<Base32*>(&de) );
    printf("%s base2:%p dynamic_cast \n",__FUNCTION__,dynamic_cast<Base32*>(&de) );

    long long m = 4;
    printf("%s (longlong*)m:%p (int*)m:%p (char*)m:%p \n",__FUNCTION__,&m, (int*)&m, (char*)&m);
}

class Test1{
public:
    void run(){ printf("Test1 run ... ... \n"); } 
    void run2(){ printf("Test1 run ... ... %d can visit Enum\n",Item1); } 
    void run3(){ printf("Test1 run ... ... %d cannot visit int\n",m); } 
    enum Enum{ Item1=1 };
    int m;
};
void test_nullptr_visit_memfun()
{
    ENTER_TEST();
    printf("%s 空指针也能调用成员函数哦! \n",__FUNCTION__);
    Test1* pt = NULL;
    pt->run();
    pt->run2();
    //pt->run3(); //coredump!!! this = (Test1 * const) 0x0
}

class Test2 {
public:
    Test2() {}
    ~Test2() {}
    Test2(const Test2 &) { printf("    copy construct\n"); }
    Test2(int m) { printf("    Test2(int m)\n"); }
    Test2 &operator=(const Test2 &) { printf("    = operator\n"); return *this; }
    Test2 &operator=(int m) { printf("    Test2 &operator=(int m)\n"); return *this; }
};
void test_assignment_or_copy()   //A b(a);和A c = a;都调用的是拷贝构造函数  ？？
{
    ENTER_TEST();
    printf("init Test2 a:   \n");
    Test2 a;
    printf("testing b(a) =>   \n");
    Test2 b(a);
    printf("testing c=a  =>   \n"); 
    Test2 c = a;        //为什么A c=a;也调用的是拷贝构造函数呢？其实这种写法只是一种语法糖，是为了兼容C的写法。
    Test2 d;
    printf("testing d=a  =>   \n");
    d = a;
    printf("testing e(1)  =>   \n");
    Test2 e(1);
    printf("testing Test2 f = 1  =>   \n");
    Test2 f = 1;
    printf("testing g = 1  =>   \n");
    Test2 g;
    g = 1;
}


class Stick {
public:
    int n;
    const int &length; // 一个const的引用，能够读取但无法修改
    Stick(): true_length(100), length(true_length),m(true_length) {}
    Stick(Stick &st): true_length(st.true_length), length(true_length) {}
    Stick(int a): true_length(a), length(true_length),m(true_length),n(true_length) {}
    void setLength(int b) { true_length = b; }
    // int getLength() { return true_length; }
private:
    int true_length;
    int m;

    friend void test_initilize_list_seq(); 
};
struct foo
{
    int i ;
    int j ;
    foo(int x):j(x), i(j){} // i值未定义
};
void test_initilize_list_seq()   //A b(a);和A c = a;都调用的是拷贝构造函数  ？？
{
    ENTER_TEST();
    Stick s(1000);
    printf("s.true_length:%d  s.length:%d  s.m:%d s.n:%d ??? ??? \n",s.true_length,s.length,s.m,s.n);
    struct foo f(20);
    printf("f.i:%d  f.j:%d \n",f.i,f.j);

}

class Base4
{
public:
    void run1(){ printf("Base3::run1() \n"); }
};
class Derived4:private Base4
{
public:
    void run2(){ printf("Derived4::run2() \n"); }
};
void test_private_inheritance()
{
    ENTER_TEST();
    Derived4 de;
    //de.run1(); 
    de.run2(); 
    //Base4 *pt = &de; //error: ‘Base4’ is an inaccessible base of ‘Derived4’
}

class class_test_static
{
	void fun_non_static(){ fun_static(); }
	static void fun_static(){ 
		;//fun_non_static(); //cannot call member function ‘void class_test_static::fun_non_static()’ without object.  在类的非静态成员不存在的时候类的静态成员就已经存在了，访问一个内存中不存在的东西当然会出错
	} 
};


