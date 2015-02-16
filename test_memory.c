#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_test_wild_pt(int* p1,int* p2);
char* get_memory();

int main()
{
    int a=1;
    int b=2;
    //swap_test_wild_pt(&a, &b);
    //
    char *p = get_memory();
    printf("new memory: %s \n",p); //not *p
    delete[] p;
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

char* get_memory()
{
    char *p = (char*)malloc(sizeof(char)*4);
    //*p = "123"; //why not  ?????
    strcpy(p,"123");
    return p;
}

