#include <stdio.h>

void swap_test_wild_pt(int* p1,int* p2);

int main()
{
    int a=1;
    int b=2;
    swap_test_wild_pt(&a, &b);
    return 0;   
}


//-------------------- fun --------------------
void swap_test_wild_pt( int* p1,int* p2 )
{
    //int k = 0;
    //int* p = &k;
    int* p; //hello, wild pointer is dangerous 
    *p =*p1; //segmentation fault
    *p1 =*p2;
    *p2 =*p;
}


