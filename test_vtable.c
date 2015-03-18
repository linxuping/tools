#include <stdio.h>
void test_obj_assign();
void test_vptr_vbtr();
void test_multi_inheritance();
void test_vir_inheritance_complex();

typedef void(*PVFUN)(void); //普通指针类型访问 类成员变量 ?

class Base{
public:
    enum Enum{ m_start=101, m_end=102 }; //not m_start=1;
    typedef void (Base::*PRUN)();
    virtual void run(){ printf("base run m_start:%d \n",m_start); }
private:
    virtual void run_private(){ printf("base run in private, cannot run in derived ?\n"); }
};
class Derived:public Base{
public:
    void run(){ printf("derived run m_start:%d \n",m_start); }
};

int main()
{
    Base* pb = new Derived();
    printf("vtable:%p \n", (int*)*(int*)pb); //check objdump -h a.out to .rodata
    //( (Base::PRUN)((int*)*(int*)pb+0) )();
    PVFUN pfun2 = (PVFUN)*((int*)*(int*)pb+0); //error: (PVFUN)((int*)*(int*)pb+0)
    pfun2();
    //pfun2 = (PVFUN)*((void*)*(void*)pb+0); //error: ‘void*’ is not a pointer-to-object type
    //pfun2();
    //
    Derived* pb2 = new Derived();
    pfun2 = (PVFUN)*((int*)*(int*)pb2+0); 
    pfun2();
    pfun2 = (PVFUN)*((int*)*(int*)pb2+1);  //fuck, run Base::private function, like pb2->run_private()
    pfun2();
    //
    test_obj_assign();
    //
    test_vptr_vbtr();
    //
    test_multi_inheritance();
    //
    test_vir_inheritance_complex();
    //
    return 0;
}

//---- rel ---->
void test_obj_assign()
{
    printf("%s => test 'Base b=derived' \n",__FUNCTION__);
    Derived de;
    Base be = de; //vptr直接覆盖，还是operator=会再更新be的vptr ? 和c++模型里面讲的对照
    de.run();
    //Derived de2 = static_cast<Derived>(be);
    //de2.run();
}

class Base2{
public:
    int m_a;
};
class Derived21:virtual public Base2{};
class Derived22:virtual public Base2{};
class Derived2:virtual public Derived21, virtual public Derived22{
public:
    virtual void run(){ printf("Derived2::run() \n"); }
};
void test_vptr_vbtr()
{
    printf("%s Derived2 size:%d 12=member+vptr+vbtr? \n",__FUNCTION__,sizeof(Derived2)); //vbtr就能够辨识出m_a
    Derived2 *pt = new Derived2();
    pt->m_a = 100;
    printf("%s Derived2 m_a:%d  \n",__FUNCTION__,*((int*)pt+1));
    printf("%s Derived2 base virtual offset:%d ??? \n",__FUNCTION__,(int)*( (int*)*((int*)pt+2) -1 ));
    //(*((int*)*(int*)pt))(); //‘*(int*)(*(int*)pt)’不能用作函数  不是随便的指针都能做函数使
    ( (PVFUN)*((int*)*(int*)pt) )();
    delete pt; 

    /*coredump ?
    Base2 *pt2 = new Derived2(); 
    //Base2  virtual ~Base2(){} // must added, why?
    delete pt2;
    */
    printf("%s so: 1.vptr 2.member 3.vbtr \n",__FUNCTION__);
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
class Base33{
public:
    virtual void run3(){}
    int m3;
};
class Base34{
};
class Base35{
    int m5; //private
public:
    Base35():m5(5){}
    int get(){ return m5; }
};
class Derived3:public Base31,public Base32,public Base33,public Base34,public Base35{
public:
    int d;
};
void test_multi_inheritance()
{
    printf("%s Derived3 size:%d =?= 8+4+8+0+4 +4 \n",__FUNCTION__,sizeof(Derived3));
    Derived3 d3;
    printf("%s Derived3 基类public 变量被继承过来 m2:%d \n",__FUNCTION__,*((int*)((char*)&d3+8)) );
    printf("%s Derived3 基类private变量被继承过来 m5:%d \n",__FUNCTION__,*((int*)((char*)&d3+8+4+8+0)) );
    Base35 b35 = d3;
    printf("%s Base35 m5:%d \n",__FUNCTION__,b35.get(),&b35 );
}


class B{
public:
    virtual void f(){}
    void bf(){}

    int ib;
    int cb;
};
class B1:virtual public B{
public:
    void f(){}
    virtual void f1(){}
    void bf1(){}

    int ib1;
    int cb1;
};
class B2:virtual public B{
public:
    void f(){}
    virtual void f2(){}
    void bf2(){}

    int ib2;
    int cb2;
};
class D:public B1,public B2{
public:
    //D():ib(1),cb(2),ib1(3),cb1(4),ib2(5),cb2(6),id(7),cd(8){} 错误：类‘D’没有名为‘ib’...的字段
    void f(){}
    void f1(){}
    void f2(){}
    void df(){}

    int id;
    int cd;
};
void test_vir_inheritance_complex()
{
    //refer: http://coolshell.cn/articles/12176.html
    printf("%s D size:%d =?= [B1/B2 in D:(vptr)4+4+4]*2+(vbtr)4+4+4 \n",__FUNCTION__,sizeof(D) );
    D d;
    for(int i=0; i<11; ++i)
        printf("%d: %d \n",i,*((int*)&d+i) );
}



void test_this()
{
}


