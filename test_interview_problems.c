#include <stdio.h>
#include "common.h"

void test_pos_is_1or0();

int main()
{
    test_pos_is_1or0();
    return 0;
}

//---- ---- codes ---- ---->
void test_pos_is_1or0()
{
    ENTER_TEST();
    const int count = 10;
    long a[10] = {2,1,2,1,2,1,2,1,2,1};
    //4*10
    printf("sizeof a: %d \n",sizeof(a));
    //#define is1(arr,pos) (a>>(sizeof(a)-1))%2==1
    #define is1(arr,pos) ( a[ pos/sizeof(long) ] >> (pos/sizeof(long)) )%2==1
    printf("is 1 ?: %d item:%d \n", is1(a,1), a[ 1/sizeof(long) ]);
    printf("is 1 ?: %d \n",is1(a,2));
}
