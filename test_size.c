#include <stdio.h>
#include <string.h> //strlen in c
#include <string> //string in c++
using namespace std;
#include <vector>

void test_string_capacity();
void test_vector_capacity();

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
    /*//size overflow
    for (unsigned char i=0; i<=255; ++i) 
    	printf("unsigned char i:%d \n",i); */
    //
    test_string_capacity();
    //
    test_vector_capacity();

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


