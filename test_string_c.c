#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

void test_strcpy();
void test_strlen();

void test_char_stack();
void test_char_heap();
void test_strstr();
void test_strcat();
void test_loopmove();

int main()
{
    test_strcpy();
    test_strlen();

    test_char_stack();
    test_char_heap();
    test_strstr();
    test_strcat();
    test_loopmove();
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
    while(*orig++ != '\0')++len; //使用*pt++
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
    //数组，存放在栈，可改(array to stack)
    char arr[6] = "hello";
    *arr = 'a';
    printf("arr changed: %s \n",arr);
    printf("arr address    (stack):%p \n",&arr[0]);
    //指针，在rodata，不可改(pointer to rodata)
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
    memset(buf,'.',10);
    /*
    *buf++ = 'x';  //after buf++, it will output from current pointer
    *buf++ = 'y';  //
    */
    char *tmp = buf;
    *tmp++ = 'x';  
    *tmp++ = 'y';  
    printf("%s buf:%s \n",__FUNCTION__,buf);
}

//how to return -> strDest
char* strcat_1(char* strDest, const char* strSrc) //最好传len_dest进来判断,以防栈溢出
{
    //if beyond strDesc size, how to solve... ... 
    assert((strDest!=NULL)&&(strSrc!=NULL));
    char* pt = strDest + strlen(strDest);
    memcpy(pt, strSrc, strlen(strSrc));
    return strDest;//为了实现链式操作，将目的地址返回 
}
void test_strcat()
{
    char buf1[20] = "hello,world";
    char buf2[5] = "xyz";
    strcat_1(buf1,buf2);
    printf("%s strcat:%s\n",__FUNCTION__,buf1);
}

void test_strstr()
{
  char str[] ="This is a simple string";
  char * pch;
  pch = strstr (str,"simple");
  strncpy (pch,"sample",6);
  puts (str);
}
char* loopmove(char* orig, int steps) //error 
{
    assert(orig!=NULL);
    unsigned int len = strlen(orig);  //not sizeof, it is nk
    steps = steps%len;
    const unsigned int MAX = 65535; //c++
    char tmp[MAX];
    /*//1 error
    memcpy(tmp, orig+(len-steps),steps);
    printf("--1-- %s %s \n",tmp,orig);
    memcpy(orig+steps, orig, len-steps);  //self memcpy, some problems
    printf("--2-- %s \n",orig);  //helloworld -> hehellllor
    memcpy(orig, tmp, steps);
    */
    /*
    //2 ok
    strcpy(tmp, orig+(len-steps));
    strcpy(tmp+steps, orig);
    *(tmp+len) = '\0';
    strcpy(orig,tmp);
    */
    //3 ok
    memmove(tmp, orig+(len-steps),steps);
    memmove(orig+steps, orig, len-steps);  
    memmove(orig, tmp, steps);
    return orig;
}
void test_loopmove()
{
    char buf[11] = "helloworld";
    char *desc = loopmove(buf,2);
    printf("steps:%d, loopmove:%s \n",2,desc);
    desc = loopmove(buf,10);
    printf("steps:%d, loopmove:%s \n",10,desc);
    desc = loopmove(buf,12);
    printf("steps:%d, loopmove:%s \n",12,desc);
}

