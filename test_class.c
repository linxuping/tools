#include<stdio.h>

void test_operator_overlap();
void test_structor_virtual();
void test_class_mem_fun_ptr();

int main()
{
    test_operator_overlap();
    test_structor_virtual();
    test_class_mem_fun_ptr();
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
    Base(){run("construct1");}
    ~Base(){run("destruct1");}
    virtual void run(const char* f){ printf("base %s\n",f); }
};
class Derived: public Base{
public:
    Derived(){run("construct2");}
    ~Derived(){run("destruct2");}
    void run(const char* f){ printf("derived %s\n",f); }
};
void test_structor_virtual()
{
    Base* pt = new Derived();
    delete pt;
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

