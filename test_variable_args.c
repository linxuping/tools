#include <stdio.h>
//#include <stdarg.h>
#include <iostream>
#include <string>
using namespace std;

int Sum(int nCount,... );
string SumStr(int nCount,...);
int SumNew(int nCount,... );
string SumStrNew(int nCount,...);
void printf1(const char* fmt,...);
void printf2(const char* fmt,...);

int main()
{
    Sum(3, 10, 20, 30);
    SumStr(5, "aa", "bb", "cc", "dd", "ff");
    cout << "\nimitate va realize ... ... ... ...\n" << endl;
    SumNew(3, 1, 2, 3);
    SumStrNew(3, "12", "34", "56");
    cout << "\nva test ... ... ... ...\n" << endl;
    printf1("va test1: ",11,22,33);
    printf2("va test2: 1:%s,2:%d \n","aa",22);

    return 0;
}

//---- raw realize ---->
int Sum(int nCount,... )
{
    int nSum = 0;
    int* p = &nCount;
    for(int i=0; i<nCount; ++i)
    {
        cout << *(++p) << endl;
        nSum += *p;
    }

    cout << "Sum:" << nSum << endl << endl;
    return nSum;
}

string SumStr(int nCount,...)
{
    string str;
    int* p = &nCount;

    for(int i=0; i<nCount; ++i)
    {
        char* pTemp = (char*)*(++p);
        cout <<  pTemp << endl;
        str += pTemp;
    }

    cout << "SumStr:" << str << endl;
    return str;
}
//---- imitate va realize ---->
typedef char *  va_list;

#define _ADDRESSOF(v)   ( &reinterpret_cast<const char &>(v) )
#define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

#define _crt_va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
#define _crt_va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define _crt_va_end(ap)      ( ap = (va_list)0 )

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end
int SumNew(int nCount,... )
{
    int nSum = 0;
    va_list vl = 0;
    va_start(vl, nCount);

    for(int i=0; i<nCount; ++i)
    {
        int n = va_arg(vl, int);
        cout << n << endl;
        nSum += n;
    }

    va_end(vl);
    cout << "SumNew:" << nSum << endl << endl;
    return nSum;
}

//use va_arg,  praram is char*
string SumStrNew(int nCount,... )
{
    string str;
    va_list vl = 0;
    va_start(vl, nCount);

    for(int i=0; i<nCount; ++i)
    {
        char* p = va_arg(vl, char*);
        cout <<  p << endl;
        str += p;
    }

    cout << "SumStrNew:" << str << endl << endl;
    return str;
}

void printf1(const char* fmt,...)
{
    va_list ap;
    va_start(ap, fmt);//将ap指向fmt后的第一个参数
    int value;
    do{
        value = va_arg(ap,int);//前提是我们知道第一个参数是int型；指针指向下一个参数 
        printf("value[%d]\n",value);
    }while(value!=0);
    va_end(ap);//将ap置为NULL
}

void printf2(const char* fmt,...)
{
    va_list ap;
    va_start(ap, fmt);//将ap指向fmt后的第一个参数
    vfprintf(stderr,fmt,ap);
    va_end(ap);//将ap置为NULL
}

void printf3(const char* fmt, ...)
{
	//fmt %d-int %s-void* %c-char ....   
	//%d p+ sizeof(type) to get args.
}

