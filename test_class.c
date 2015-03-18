#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void test_operator_overlap();
void test_structor_virtual();
void test_class_mem_fun_ptr();
void test_class_method_hide();
void test_get_base_offset();
void test_cast();
void test_nullptr_visit_memfun();

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
    printf("%s TClass1 size:%d item1:%d item2:%d item3:%d \n",__FUNCTION__, sizeof(TClass1),TClass1::EItem, TClass1::EItem2, TClass1::EItem3); //2 ???????
    printf("%s 测试结束! \n",__FUNCTION__);
}

class Base1{
public:
    void run(){ printf("(b.*prun)(); \n"); }
};
typedef void(Base1::*PRUN)(); //take care
void test_class_mem_fun_ptr()
{
    Base1 b;
    PRUN prun= &Base1::run;
    (b.*prun)(); //(b.(*prun))(); //错误：expected unqualified-id before ‘(’ token
}


class Base2{
public:
    void run(int a){ printf("base value:%d \n",a); }
};
class Derived2{
public:
    void run(float f){ printf("derive value:%f \n",f); }
};
void test_class_method_hide()
{
    Derived2 de;
    int a = 1;
    int f = 1.0f;
    de.run(a);
    de.run(f);
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
    printf("%s 对象内存模型 基类偏移量 Derived3 Base32 offset:%d \n",__FUNCTION__,offset(Derived3,Base32));
    printf("%s 对象内存模型 基类偏移量 static_cast<base*>((derived*)0x10):%p \n",__FUNCTION__,static_cast<Base32*>((Derived3*)0x10) );
    printf("%s 对象内存模型 基类偏移量 static_cast<base*>((derived*)0x0):%p \n",__FUNCTION__,static_cast<Base32*>((Derived3*)0x0) );
    printf("%s 对象内存模型 基类偏移量 (base*)((derived*)0x0):%p \n",__FUNCTION__,(Base32*)((Derived3*)0x0) );
    printf("%s 对象内存模型 基类偏移量 (derived*)0x0:%p \n",__FUNCTION__,((Derived3*)0x0) );
}

void test_cast()
{
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
    void run2(){ printf("Test1 run ... ... %d \n",Item1); } 
    void run3(){ printf("Test1 run ... ... %d \n",m); } 
    enum Enum{ Item1=1 };
    int m;
};
void test_nullptr_visit_memfun()
{
    printf("%s 空指针也能调用成员函数哦! \n",__FUNCTION__);
    Test1* pt = NULL;
    pt->run();
    pt->run2();
    pt->run3(); //this = (Test1 * const) 0x0
    //printf("尝试获取空对象的成员变量m:%d \n",pt->m);
}


