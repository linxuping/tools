#include<stdio.h>
#include<stdlib.h>

void test_operator_overlap();
void test_structor_virtual();
void test_class_mem_fun_ptr();
void test_class_method_hide();

int main()
{
    test_operator_overlap();
    test_structor_virtual();
    test_class_mem_fun_ptr();
    test_class_method_hide();
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
    enum Enum{ EItem=2,EItem2=32767,EItem3=32769 }; //不占内存  ????
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
    printf("%d TClass1 size:%d item1:%d item2:%d item3:%d \n",sizeof(TClass1),TClass1::EItem, TClass1::EItem2, TClass1::EItem3); //2 ???????
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




