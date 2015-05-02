#include <stdio.h>
#include "common.h"

void test_const_cast();
void test_reinterpret_cast();
void test_static_cast();
void test_dynamic_cast();

int main()
{
    test_const_cast();
    test_reinterpret_cast();
    test_static_cast();
    test_dynamic_cast();
}


//----------- rel --------------->
enum ETest{
    E0=0,
    E1=1,
    E2=2,
};
void test_static_cast()
{
    int m = 3;
    int n = (int)E0;
    ETest e = static_cast<ETest>(m);
    printf("enum size:%d \n",sizeof(ETest)); //4
    printf("int to enum:%d \n",e);
}
class Test1
{
    public:
        int m_test;
};
void test_const_cast()
{
    Test1 t1;
    const Test1* p1 = &t1;	//new Test1   read-only object
    //p1->m_test = 1;  //error
    //-- cast to non-const -->
    Test1* p2 = const_cast<Test1*>(p1); //½ö½öconst_castÓÐÄÜÁ¦cast away
    //Test1* p20 = static_cast<Test1*>(p1); //==== ==== ==== ==== >´íÎó£º´ÓÀàÐÍ¡®const Test1*¡¯µ½ÀàÐÍ¡®Test1*¡¯µÄ static_cast ¶ªÊ§ÁËÏÞ¶¨·û
    p2->m_test = 1001;
    printf("Test1::m_test %d\n",p1->m_test);
    //-- cast to const -->
    const Test1* p3 = const_cast<const Test1*>(p2);
    //p3->m_test = 1002; //error 
}
void test_reinterpret_cast()
{
    Test1 t1;
    void* p1 = reinterpret_cast<void*>(&t1);	//new Test1   read-only object
    printf("Test*:%p void*:%p \n",&t1,p1);
}

class Base1{
public:
    virtual void run(){}
};
class Derived1:public Base1{
    int m;
    int n;
};
class Base2{
};
class Derived2:public Base2{
    int m;
    int n;
};
void test_dynamic_cast()
{
    ENTER_TEST();
    Derived1 *p1 = new Derived1();
    Base1* p2 = dynamic_cast<Base1*>(p1);
    printf("virtual fun derive, Base size:%d \n",sizeof(*p2));
    Derived2 *p11 = new Derived2();
    Base2* p21 = dynamic_cast<Base2*>(p11);
    printf("normal derive, Base size:%d \n",sizeof(*p21));

    Derived1 *p10 = (Derived1*)p2;
    Derived1 *p12 = static_cast<Derived1*>(p2);
    Derived1 *p13 = dynamic_cast<Derived1*>(p2);
    printf("[vir] raw:%p (Derived*)pbase:%p, static_cast<Derived*>(pbase):%p  dynamic_cast<Derived*>(pbase):%p\n",p2,p10,p12,p13);

    Derived2 *p20 = (Derived2*)p21;
    Derived2 *p22 = static_cast<Derived2*>(p21);
    //Derived2 *p23 = dynamic_cast<Derived2*>(p21);// ------------------> error: cannot dynamic_cast ¿p21¿ (of type ¿class Base2*¿) to type ¿class Derived2*¿ (source type is not polymorphic)
    printf("[no vir] raw:%p (Derived*)pbase:%p, static_cast<Derived*>(pbase):%p  but cannot dynamic_cast<Derived*>(pbase)\n",p21,p20,p22);


    delete p1;
    delete p11;
}

