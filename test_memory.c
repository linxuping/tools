#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void swap_test_wild_pt(int* p1,int* p2);
char* get_memory_heap();
char* get_memory_stack();
void get_memory_temp_pt(char *buf);
void test_mmap_address();
void test_stack_overflow();
void test_stack_4m_overornot();
void test_free_cookie();
void test_edata();

int main()
{
    //
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
    //
    char *buf = NULL;
    printf("before, buf:%s %p \n",buf,&buf);
    get_memory_temp_pt(buf);
    printf("after,  buf:%s %p \n",buf,&buf);
    //
    test_mmap_address();
    //
    test_stack_overflow();
    
    //test_stack_4m_overornot();

		test_free_cookie();
		test_edata();
    return 0;   
}


//-------------------- fun --------------------
void swap_test_wild_pt( int* p1,int* p2 )
{
	ENTER_TEST();
	//int k = 0;
	//int* p = &k;
	int* p; //hello, wild pointer is dangerous !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*p =*p1; //segmentation fault
	*p1 =*p2;
	*p2 =*p;
}

char* get_memory_heap()
{
	ENTER_TEST();
	char *p = (char*)malloc(sizeof(char)*4);
	//*p = "123"; //´íÎó£º´ÓÀàÐÍ¡®const char*¡¯µ½ÀàÐÍ¡®char¡¯µÄ×ª»»ÎÞÐ§ [-fpermissive] ??
	strcpy(p,"123");
	return p;
}

char* get_memory_stack()
{
	ENTER_TEST();
	char p[4] = "456"; 
	printf("in %s: %s \n",__FUNCTION__,p); //not *p
	return p;
}

void get_memory_temp_pt(char *buf)
{
	ENTER_TEST();
	//buf Ö¸Õë±äÁ¿µÄ¿½±´
	buf = (char*)malloc(sizeof(char)*4); //ÔÚÒ»¸ö¸±±¾Ö¸ÕëÉÏ×ömalloc£¬¶ø²»ÊÇÔ­Ö¸Õë
	strcpy(buf,"789");
	printf("%s, buf:%s %p \n",__FUNCTION__,buf,&buf);
}

void test_mmap_address()
{
	ENTER_TEST();
	void *pt1 = malloc(128*2*1024);
	void *pt2 = malloc(128*2*1024);
	printf("pt1:%p < pt2:%p ?\n",pt1,pt2);
	void *pt3 = malloc(12*1024);
	void *pt4 = malloc(12*1024);
	printf("pt3:%p < pt4:%p ?\n",pt3,pt4);
	free(pt1);
	free(pt2);
	free(pt3);
	free(pt4);
	/*
pt1:0xb7f1c008 higher
pt2:0xb7edb008 

pt3:0x841b018 
pt4:0x841e020 higher
	 */
}

void test_stack_overflow()
{
	ENTER_TEST();
	char buf1[4] = "a";
	strcpy(buf1, "aaaa");
	char buf2[4] = "bbb";
	printf("take care: %s,  %s \n",buf1, buf2);
}

void test_stack_4m_overornot()
{
	ENTER_TEST();
	char buf0[4*1024*1024*2];
	char buf[4*1024*1024];
	char buf2[4*1024*1024];
	char buf3[4*1024*1024];
	char buf4[4*1024*1024];
	char buf5[4*1024*1024];
	char buf6[4*1024*1024];
	char buf7[4*1024*1024];
	char buf8[4*1024*1024];
	char buf9[4*1024*1024];
	char buf10[4*1024*1024];
}

//whereis the memory cookie ???????????????????????????????????
void test_free_cookie()
{
	ENTER_TEST();
	char* buf = (char*)malloc(5); //0x0101
	strcpy(buf, "abcd");
	free(buf);
	buf = new char(5);
	delete buf;
}

#define ALLOC_SIZE 1024
//from high to low: 1024*1024
//from low to high: 1024
void test_edata()
{
	ENTER_TEST();
	for (int i=0; i<10; ++i){
		char* buf = (char*)malloc(ALLOC_SIZE);
		printf("buf:%p \n",buf);
		free(buf);
	}

	char* buf1 = (char*)malloc(ALLOC_SIZE);
	printf("alloc: %p\n",buf1);
	char* buf2 = (char*)malloc(ALLOC_SIZE);
	char* buf3 = (char*)malloc(ALLOC_SIZE);
	char* buf4 = (char*)malloc(ALLOC_SIZE);
	free(buf2);
	free(buf3);
	char* buf5 = (char*)malloc(ALLOC_SIZE);
	free(buf4);
	printf("alloc: %p\n",buf4);

	char* buf6 = (char*)malloc(ALLOC_SIZE);
	char* buf7 = (char*)malloc(ALLOC_SIZE);
	char* buf8 = (char*)malloc(ALLOC_SIZE);
	free(buf6);
	free(buf7);
	printf("alloc: %p\n",buf8);

}


