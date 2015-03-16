#include<stdio.h>

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
    ~Base(){run("destruct1");}
    virtual void run(const char* f){ printf("base %s\n",f); }
};
class Derived: public Base{
public:
    Derived(){run("construct2 >>> ");}
    ~Derived(){run("destruct2");}
    void run(const char* f){ printf("derived %s\n",f); }
    void display(){ printf("only derived display \n"); }
};
void test_structor_virtual()
{
    printf("%s 1.derived()2.base() ? \n",__FUNCTION__);
    Base* pt = new Derived();
    delete pt;
    //
    Derived de;
    Base& bb = de;//基类类型 对子类对象的引用，如果调用子类的非重写方法，就会调不到
    bb.run("hello");
    //bb.display();
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




