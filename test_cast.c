#include <stdio.h>

void test_const_cast();
void test_reinterpret_cast();
void test_static_cast();

int main()
{
	test_const_cast();
    test_reinterpret_cast();
    test_static_cast();
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
    int m_test = 1;
};
void test_const_cast()
{
	Test1 t1;
    const Test1* p1 = &t1;	//new Test1   read-only object
	//p1->m_test = 1;  //error
	//-- cast to non-const -->
	Test1* p2 = const_cast<Test1*>(p1);
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
