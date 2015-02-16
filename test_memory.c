#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_test_wild_pt(int* p1,int* p2);
char* get_memory_heap();
char* get_memory_stack();

int main()
{
    int a=1;
    int b=2;
    //swap_test_wild_pt(&a, &b);
    //
    char *p = get_memory_heap();
    printf("new memory heap: %s \n",p); //not *p
    delete[] p;
    //
    char *p2 = get_memory_stack();
    printf("new memory stack: %s \n",p2); //what will happen
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

char* get_memory_heap()
{
    char *p = (char*)malloc(sizeof(char)*4);
    //*p = "123"; //why not  ?????
    strcpy(p,"123");
    return p;
}

char* get_memory_stack()
{
    char p[4] = "456"; 
    printf("in %s: %s \n",__FUNCTION__,p); //not *p
    return p;
}

