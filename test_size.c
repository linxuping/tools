#include <stdio.h>
#include <string.h> //strlen in c
#include <string> //string in c++
using namespace std;
#include <vector>

void test_string_capacity();
void test_vector_capacity();
void test_struct_offset();
void test_size_32or64();
void test_type_size();

struct A{
  char b,c,d;
};
struct B{
  int a;
  char b,c;
};

int main()
{
    test_string_capacity();
    //
    test_vector_capacity();
    //
    test_struct_offset();
    //
    test_size_32or64();
    //
    test_type_size();

    return 0;
}


//---------- rel -------->
void test_string_capacity() //test capacity swap
{
    printf("string size:%d \n",sizeof(string));
    string s1 = "he";
    printf("s1=he     capacity*2:%d \n",s1.capacity());
    s1 = "hehe";
    printf("s1=hehe   capacity*2:%d \n",s1.capacity());
    s1 = "hehehe";
    printf("s1=hehehe capacity*2:%d \n",s1.capacity());
    s1 = "hello                                                                                                       ";
    printf("s1 capacity:%d \n",s1.capacity());
    s1 = "he";
    printf("s1 capacity:%d \n",s1.capacity());
    string(s1).swap(s1);
    printf("s1 capacity:%d \n",s1.capacity());
}
void test_vector_capacity() //test capacity swap
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    printf("vec size:%d \n",vec.capacity());
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    vec.push_back(6);
    printf("vec size:%d \n",vec.capacity());
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vector<int>(vec).swap(vec);
    printf("vec size:%d \n",vec.capacity());
}
typedef struct TStruct TStruct;
struct TStruct{
    int m1;
    char c1;
    float f1;
    int m2;
}; 
//#define tsoffset(i) (char*)&(((TStruct*)0)->i)-(char*)0  //pointer step: 1by1, if int* is 4by1
#define tsoffset(i) &(((TStruct*)0)->i)  //score here
//#define tsoffset2(type, member) (unsigned int)(&(((type *)0)->member)) //error in 64.
#define tsoffset2(type, member) (intptr_t)(&(((type *)0)->member))
void test_struct_offset()
{
    printf("offset of c1:%d \n",tsoffset(c1));
    printf("offset of f1:%d \n",tsoffset(f1));
    printf("offset of m2:%d \n",tsoffset(m2));
    //online
    printf("offset2 of c1:%d \n",tsoffset2(TStruct, c1));
    printf("offset2 of f1:%d \n",tsoffset2(TStruct, f1));
    printf("offset2 of m2:%d \n",tsoffset2(TStruct, m2));
}
void test_size_32or64() 
{
    printf("Type SIze:  char:%d, int:%d, float:%d, short:%d, double:%d, long:%d \n",sizeof(char),sizeof(int),sizeof(float),sizeof(short),sizeof(double),sizeof(long));
}

#define printme(hint,size) do{printf("%s %s:%d \n",__FUNCTION__,hint,size);}while(0)
void test_type_size() 
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
    /*//size overflow
    for (unsigned char i=0; i<=255; ++i)  //hello,dead cycle... ...
    	printf("unsigned char i:%d \n",i); */
    //
    char buf1[] = "hello";
    printme("buf1[] size:",sizeof(buf1) );
    char buf2[10] = {'a','b'};
    printme("buf2[10]={'a','b'} size",sizeof(buf2) );
    //printme("void size",sizeof(void) );

    printf("%s intptr_t size:%d \n",__FUNCTION__,sizeof(intptr_t) );//‘intptr_t’ was not declared in this scope gcc 4.8.1 ??
    printf("%s ssize_t size:%d \n",__FUNCTION__,sizeof(ssize_t) );
    printf("%s size_t size:%d \n",__FUNCTION__,sizeof(size_t) );
    printf("%s long long size:%d \n",__FUNCTION__,sizeof(long long) );
    printf("%s long long int size:%d \n",__FUNCTION__,sizeof(long long int) );
    printf("%s unsigned long long size:%d \n",__FUNCTION__,sizeof(unsigned long long) );
    printf("%s unsigned long long int size:%d \n",__FUNCTION__,sizeof(unsigned long long int) );
}


