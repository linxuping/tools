#include <stdio.h>
void test_obj_assign();
void test_vptr_vbtr();

class Base{
public:
    typedef void (Base::*PRUN)();
    virtual void run(){ printf("base run\n"); }
private:
    virtual void run_private(){ printf("base run in private\n"); }
};
class Derived:public Base{
public:
    void run(){ printf("derived run\n"); }
};

typedef void(*PFUN2)(void);

int main()
{
    Base* pb = new Derived();
    printf("vtable:%p \n", (int*)*(int*)pb); //check objdump -h a.out to .rodata
    //( (Base::PRUN)((int*)*(int*)pb+0) )();
    PFUN2 pfun2 = (PFUN2)*((int*)*(int*)pb+0); //error: (PFUN2)((int*)*(int*)pb+0)
    pfun2();
    //pfun2 = (PFUN2)*((void*)*(void*)pb+0); //error: ‘void*’ is not a pointer-to-object type
    //pfun2();
    //
    Derived* pb2 = new Derived();
    pfun2 = (PFUN2)*((int*)*(int*)pb2+0); 
    pfun2();
    pfun2 = (PFUN2)*((int*)*(int*)pb2+1);  //fuck, run Base::private function, like pb2->run_private()
    pfun2();
    //
    test_obj_assign();
    //
    test_vptr_vbtr();
    return 0;
}

//---- rel ---->
void test_obj_assign()
{
    printf("%s run\n",__FUNCTION__);
    Derived de;
    Base be = de; //vptr直接覆盖，还是operator=会再更新be的vptr ? 和c++模型里面讲的对照
    de.run();
    //Derived de2 = static_cast<Derived>(be);
    //de2.run();
}

class Base2{
public:
    int m;
};
class Derived21:virtual public Base2{};
class Derived22:virtual public Base2{};
class Derived2:virtual public Derived21, virtual public Derived22{
public:
    virtual void run(){ printf("Derived2::run() \n"); }
};
void test_vptr_vbtr()
{
    printf("%s Derived2 size:%d 12? \n",__FUNCTION__,sizeof(Derived2));
    Derived2 *pt = new Derived2();
    pt->m = 100;
    printf("%s Derived2 m:%d  \n",__FUNCTION__,*((int*)pt+1));
    printf("%s Derived2 base virtual offset:%d ??? \n",__FUNCTION__,(int)*( (int*)*((int*)pt+2) -1 ));
    //(*((int*)*(int*)pt))(); //‘*(int*)(*(int*)pt)’不能用作函数  不是随便的指针都能做函数使
    ( (PFUN2)*((int*)*(int*)pt) )();
    delete pt; 

    /*coredump ?
    Base2 *pt2 = new Derived2(); 
    //Base2  virtual ~Base2(){} // must added, why?
    delete pt2;
    */
    printf("%s so: 1.vptr 2.member 3.vbtr \n",__FUNCTION__);
}

