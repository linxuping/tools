#include <stdio.h>
#include <string.h> //strlen in c
#include <string> //string in c++
using namespace std;

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
    //
    char buf[10] = "hello";
    printf("buf size:%d, strlen:%d \n",sizeof(buf),strlen(buf));
    //
    char **a[3][4];
    char *b[3][4];
    char c[3][4];
    printf("**a[3][4] size:%d \n",sizeof(a)); //??? int a[2] vs int* a[2]
    printf("b[3][4] size:%d \n",sizeof(b));   //???
    printf("c[3][4] size:%d \n",sizeof(c));
    //
    //string s1 = "hello";
    printf("string size:%d \n",sizeof(string));
    /*//size overflow
    for (unsigned char i=0; i<=255; ++i) 
    	printf("unsigned char i:%d \n",i); */

    return 0;
}
