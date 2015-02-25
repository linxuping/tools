#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void test_strcpy();
void test_strlen();

void test_char_stack();
void test_char_heap();
void test_strstr();

int main()
{
    test_strcpy();
    test_strlen();

    test_char_stack();
    test_char_heap();
    test_strstr();
    return 0;    
}

//--------- rel ---------->
char* strcpy_1(char* desc, const char* orig) //score here
{
    assert((desc!=NULL)&&(orig!=NULL));
    printf("strcpy_1 desc:%s orig:%s %c %c \n",desc,orig,*desc,*orig);
    while((*desc++=*orig++) != '\0');
    return desc;
}
unsigned int strlen_1(const char* orig) //score here
{
    assert(orig!=NULL);
    unsigned int len = 0; 
    while(*orig++ != '\0')++len;
    return len;
}

void test_strlen()
{
    char *orig = "hello,world";
    printf("strlen_1:%d, strlen:%d \n",strlen_1(orig),strlen(orig));
}
void test_strcpy()
{
    char *orig = "hello,world";
    char *desc = (char*)malloc(strlen(orig)+1); //not 'char* desc="", it is constant distinct'
    printf("desc before :%s \n",desc);   
    strcpy_1(desc, orig);
    printf("desc after  :%s \n",desc);   
    //strcpy_1(NULL, orig);
}
void test_char_stack()
{
    //array
    char arr[6] = "hello";
    *arr = 'a';
    printf("arr changed: %s \n",arr);
    printf("arr address    (stack):%p \n",&arr[0]);
    //pointer
    char *buf = "hello";//这个指针指向的是全局的const内存区，const内存区当然不会让你想改就改的
    printf("buf address    (constant distinct):%p \n",buf);
    //*buf = 'a'; //error
    /*//error
    char *tmp = const_cast<char*>(buf);
    *tmp = 'x';
    printf("constant, after const_cast:%s \n",buf);
    */
}
void test_char_heap()
{
    int ssize = 10;
    char *buf = (char*)malloc(sizeof(char)*ssize+1); //with \0 ?
    memset(buf,'c',10);
    /*
    *buf++ = 'x';  //after buf++, it will output from current pointer
    *buf++ = 'y';  //
    */
    char *tmp = buf;
    *tmp++ = 'x';  
    *tmp++ = 'y';  
    printf("%s buf:%s \n",__FUNCTION__,buf);
}

void test_strstr()
{
  char str[] ="This is a simple string";
  char * pch;
  pch = strstr (str,"simple");
  strncpy (pch,"sample",6);
  puts (str);
}
char* loopmove(char* orig, int steps)
{
    unsigned int len = strlen(orig); 
}
void test_loopmove()
{

}

