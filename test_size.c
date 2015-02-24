#include <stdio.h>

struct A{
  char b,c,d;
};
struct B{
  int a;
  char b,c;
};

int main()
{
    //printf("WORD:%d \n",sizeof(WORD));
    printf("size of A:%d \n",sizeof(A)); //not 4,why
    printf("size of B:%d \n",sizeof(B));
    printf("size of size_t:%d \n",sizeof(size_t));
    return 0;
}
