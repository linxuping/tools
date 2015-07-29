#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

void test_base1();
void test_base2();

void test_strcpy();
void test_strlen();

void test_char_stack();
void test_char_heap();
void test_strstr();
void test_strcat();
void test_strcmp();
void test_loopmove();
void test_substr();
void test_unicode(); //中文-char* 和 wchar_t*的差别
void test_snprintf();

int main()
{

	test_strcpy();
	test_strlen();

	test_char_stack();
	test_char_heap();
	test_strstr();
	test_strcat();
	test_strcmp();
	test_loopmove();
	test_substr();
	test_unicode(); //中文-char* 和 wchar_t*的差别
	test_snprintf();
	test_base1();
	test_base2();
	return 0;    
}

//--------- rel ---------->
/*
 *http://www.cnblogs.com/alaigle/archive/2012/05/24/2516062.html
 */
void test_base1()
{
	ENTER_TEST();
	char* str = "127.0.0.1";
	printf("strchr: find '.' in %s: %d \n", str, strchr(str,'.')-str);
	printf("strrchr: find '.' in %s: %d \n", str, strrchr(str,'.')-str);
	printf("strstr: find '0.' in %s: %d \n", str, strstr(str,"0.")-str);
	
	//strncmpi
	//strcspn
	//strrev  strset

	char *stopstr;
	printf("strtol: %ld \n", strtol(str, &stopstr, 10));
	printf("stopped scan at: %s\n", stopstr);
	//printf("strtol: %ld stopped scan at: %s\n", strtol(str, &stopstr, 10), stopstr);  //coredump code

	char *dup_str; 
	dup_str = strdup(str); 
	printf("strdup: %s \n", dup_str); 
	free(dup_str); 

	//char *buf01 = "BBB", *buf02 = "bbb";
	//printf("stricmp: %s==%s: %d \n",buf01,buf02,strcmpi(buf01,buf02));

	printf("strncmp: '0.0': %d \n", strncmp(str+4, "0.0", 3));
	printf("strcasecmp: abc==ABC? %d \n", strcasecmp("abc", "AbC"));
	char *tmp = strpbrk(str, "789");
	printf("strpbrk: '0.0': %c %p-%p\n", *tmp, str, tmp);

	//strnset
	//strsep   todo...
	//strtok   todo...
	printf("strspn: 27:%d \n", strspn(str, "27"));
	printf("strspn: 127:%d \n", strspn(str, "127"));
	printf("strspn: 0.1:%d \n", strspn(str, "0.1"));

	printf("strcspn: 27:%d \n", strcspn(str, "27"));
	printf("strcspn: 127:%d \n", strcspn(str, "127"));
	printf("strcspn: 0.1:%d \n", strcspn(str, "0.1"));

	char tmp2[16];
	//printf("sscanf ret:%d \n", sscanf("abc123abc","%d",tmp2));
	printf("sscanf ret:%d \n", sscanf("123456abc","%[^a-z]",tmp2));
	//http://blog.chinaunix.net/uid-26284412-id-3189214.html
	char buf[100]="123:asdfasd:2342342:liman:host:34234:hello";
	char user[20]="";
	char host[20]="";
	char msg[20]="";
	int cmd = 0; 
	sscanf(buf, "%*d:%*[^:]:%*[^:]:%[^:]:%[^:]:%d:%s", user, host, &cmd, msg);
	printf("%s %s %s %d \n",user, host, msg, cmd);
	int a,b,c,d;
	sscanf("127.0.0.1", "%d.%d.%d.%d", &a,&b,&c,&d); //not a,b,c,d
	printf("%d-%d-%d-%d \n",a,b,c,d);

	{//memccpy
		char s[]="Goldenx Global View";
		char dest[20];
		char *p;
		p=(char *)memccpy(dest,s,'x',strlen(s));
		if(p)
		{
		   *p='\0'; // MUST Do This
		   printf("Char found: %s.\n",dest);
		}
		else
		   printf("Char not found.\n");
	}

	{//strtok
		char ip[50] = "192.168.0.8";
		char f[] = ".";
		char *a, *b, *c, *d;
		a = strtok(ip, f);
		b = strtok(NULL, f);
		c = strtok(NULL, f);
		d = strtok(NULL, f);
		printf("[%s][%s][%s][%s]\n", a, b, c, d);
	}

}

#include <ctype.h>
void test_base2()
{
	ENTER_TEST();
	printf("isalpha: a:%d \n", isalpha('a'));
	printf("isalpha: *:%d \n", isalpha('*'));
	printf("isupper: a:%d \n", isupper('a'));
	printf("islower: a:%d \n", islower('a'));
	printf("islower: *:%d \n", islower('*'));
}


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
	ENTER_TEST();
	char *orig = "hello,world";
	printf("strlen_1:%d, strlen:%d \n",strlen_1(orig),strlen(orig));
}
void test_strcpy()
{
	ENTER_TEST();
	char *orig = "hello,world";
	char *desc = (char*)malloc(strlen(orig)+1); //not 'char* desc="", it is constant distinct'
	printf("desc before :%s \n",desc);   
	strcpy_1(desc, orig);
	printf("desc after  :%s \n",desc);   
	//strcpy_1(NULL, orig);
}
void test_char_stack()
{
	ENTER_TEST();
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
	ENTER_TEST();
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
	free(buf);
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
	ENTER_TEST();
	char buf1[20] = "hello,world";
	char buf2[5] = "xyz";
	strcat_1(buf1,buf2);
	printf("%s strcat:%s\n",__FUNCTION__,buf1);
}

//use \0
int strcmp_1(const char* s1, const char* s2) //>>> >>> you know? \0 is 0 in ascii
{
	assert((s1!=NULL)&&(s2!=NULL)); 
	while((*s1++==*s2++)&&('\0'!=*s1)&&('\0'!=*s2)); //while(*s1++ == *s2++); p *s1 => Cannot access memory at address 0xbffff000
	if ('\0'==*s1 && '\0'==*s2)
		return 0;
	else if (*s1 == '\0')
		return -1;
	else if(*s2 == '\0')
		return 1;
	return *s1>*s2?1:-1;
}
//use 0
int strcmp_2(const char* s1, const char* s2) 
{
	assert((s1!=NULL)&&(s2!=NULL)); 
	while(*s1 && *s2 && (*s1++)*(*s2++)); //bug 1.  if a=a => while((*s1++!=0) && (*s2++!=0)) 2. ''='' s1++ will stack overflow
	if ((*s1==0) && (*s2==0)) return 0;
	return *s1>*s2?1:-1;

}
int strcmp_baidu(const char *str1,const char *str2)
{
	/*不可用while(*str1++==*str2++)来比较，当不相等时仍会执行一次++，
    return返回的比较值实际上是下一个字符。应将++放到循环体中进行。*/
	while(*str1 == *str2)
	{
	  if(*str1 == '\0')
		  return 0;

	  str1++;
	  str2++;
  }
	return *str1 - *str2;
}
void test_strcmp()
{
	ENTER_TEST();
	char buf[] = "";
	char buf1[] = "12";
	char buf2[] = "1234";
	printf("buf[] sizeof:%d \n ", sizeof(buf));
	printf("%s_1 12>1234? %d \n",__FUNCTION__,strcmp_1(buf1,buf2));
	printf("%s 1234>12? %d \n",__FUNCTION__,strcmp_1(buf2,buf1));
	printf("%s 12=12? %d \n",__FUNCTION__,strcmp_1(buf1,buf1));
	printf("%s ''=''? %d \n",__FUNCTION__,strcmp_1(buf,buf));
	printf("%s ''=12? %d \n",__FUNCTION__,strcmp_1(buf,buf1));

	printf("%s_2 12>1234? %d \n",__FUNCTION__,strcmp_2(buf1,buf2));
	printf("%s 1234>12? %d \n",__FUNCTION__,strcmp_2(buf2,buf1));
	printf("%s 12=12? %d \n",__FUNCTION__,strcmp_2(buf1,buf1));
	printf("%s ''=''? %d \n",__FUNCTION__,strcmp_2(buf,buf));
	printf("%s ''=12? %d \n",__FUNCTION__,strcmp_2(buf,buf1));

	printf("%s_baidu 12>1234? %d \n",__FUNCTION__,strcmp_baidu(buf1,buf2));
	printf("%s 1234>12? %d \n",__FUNCTION__,strcmp_baidu(buf2,buf1));
	printf("%s 12=12? %d \n",__FUNCTION__,strcmp_baidu(buf1,buf1));
	printf("%s ''=''? %d \n",__FUNCTION__,strcmp_baidu(buf,buf));
	printf("%s ''=12? %d \n",__FUNCTION__,strcmp_baidu(buf,buf1));
}

void test_strstr()
{
	ENTER_TEST();
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
	ENTER_TEST();
	char buf[11] = "helloworld";
	char *desc = loopmove(buf,2);
	printf("steps:%d, loopmove:%s \n",2,desc);
	desc = loopmove(buf,10);
	printf("steps:%d, loopmove:%s \n",10,desc);
	desc = loopmove(buf,12);
	printf("steps:%d, loopmove:%s \n",12,desc);
}

void test_substr()
{
	ENTER_TEST();
	char result[12];
	char *buf = "hello,world123";
	strncpy(result, buf+11, strlen(buf)-11);
	result[3] = '\0';
	printf("get 123: %s \n",result);
}

#include <wchar.h>
void test_unicode() //中文-char* 和 wchar_t*的差别
{
	char *buf = "中文";
	wchar_t *wbuf = L"中文";
	printf("中文 char* size:%d \n",strlen(buf)*sizeof(char));
	printf("中文 wchar_t* size:%d \n",wcslen(wbuf)*sizeof(wchar_t));
}

//The  functions  snprintf()  and  vsnprintf() write at most size bytes (including the terminating null byte ('\0')) to str.
void test_snprintf()
{
	ENTER_TEST();
	char *buf = "123456789";
	char buf2[4];
	snprintf(buf2, 4, buf);
	printf("snprintf: %s\n",buf2);
}

