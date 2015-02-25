#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void test_strcpy();
void test_char_stack();
void test_char_heap();

int main()
{
    test_strcpy();
    test_char_stack();
    test_char_heap();
    return 0;    
}

//--------- rel ---------->
char* strcpy_1(char* desc, const char* orig)
{
    assert((desc!=NULL)&&(orig!=NULL));
    printf("strcpy_1 desc:%s orig:%s %c %c \n",desc,orig,*desc,*orig);
    while((*desc++=*orig++) != '\0');
    return desc;
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
    char *buf = "hello";//这个指针指向的是全局的const内存区，const内存区当然不会让你想改就改的
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

