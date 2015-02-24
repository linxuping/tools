#include <stdio.h>

const int get_const_int();
const char* get_const_str();
class Test1;

int main()
{
    int m = 100;
    //1.
    const int a1 = 1;    
    const int* p1 = &a1;
    //*p1 = 11;  //error !
    //2.
    int a2 = 2;    
    int* const p2 = &a2; //not int const *
    *p2 = 22;
    //p2 = &m;   //error !(error: assignment of read-only variable ‘p2’)
    printf("const int *:%p, int const *:%p \n", p1, p2);
    //3.
    const int a3 = get_const_int();
    int a4 = get_const_int();
    //4.   for pointer
    const char* p3 = get_const_str();
    //char* p4 = get_const_str(); //error !
    return 0;
}



//------------------rel------------------->
const int get_const_int(){
    return 1;
}

const char* get_const_str(){
    return "test";
}

class Test1
{
public:
    int m_test;
    mutable int m_mt;
    void Push(int elem);
    int Pop(void);
    int GetCount(void) const; // const 成员函数
private:
    int m_num;
    int m_data[100];
};
int Test1::GetCount(void) const
{
    //++m_num; // 编译错误，企图修改数据成员m_num
    //Pop(); // 编译错误，企图调用非const 函数
    m_mt = 100; //ok, for it is mutable
    return m_num;
}



