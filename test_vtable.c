#include <stdio.h>

class Base{
public:
    typedef void (Base::*PRUN)();
    virtual void run(){ printf("base\n"); }
};
class Derived:public Base{
public:
    void run(){ printf("derived\n"); }
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
    return 0;
}
