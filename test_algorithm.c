#include<stdio.h>

void test_arrange();
void test_add_1_to_MAX();
void test_add_MAX_MAX();

int main()
{
    test_arrange();
    //test_add_1_to_MAX();
    test_add_MAX_MAX();
    return 0;
}

void swap(char *p1, char *p2){
    char tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
void my_arrange(char *buf, int pos1, int pos2)
{
    if (pos1 >= pos2){
        return;//printf("- buf:%s -\n",buf);
    }
    for (int i=pos1; i<=pos2; ++i){
        swap(&buf[pos1], &buf[i]);
        printf("pos1:%d i:%d buf:%s \n",pos1,i,buf);
        my_arrange(buf, pos1+1, pos2); //not my_arrange(buf, i+1, pos2);
        swap(&buf[pos1], &buf[i]);
    }
}
void test_arrange()
{
    char buf[] = "1234";
    my_arrange(buf, 0, 3);
}

#include<limits.h>
void test_add_1_to_MAX()
{
    //printf("int max:%d \n",INT_MAX);
    int count = 0;
    for(int i=0; i<INT_MAX; ++i)
        count += i;
    printf("%s  count:%u > INT_MAX:%d \n",__FUNCTION__,count,INT_MAX);
    //INT_MAX*2
}

class Plus{
public:
    char m; //jinwei
    //enum Enum{ MAX_SIZE=20 };
    char *buf;
    explicit Plus(const char* buf2){
        /*
        int len = strlen(buf2)+1;
        buf = (char*)malloc(len);
        memset(buf,0,MAX_SIZE);
        strcpy(buf, buf2);
        */
    }
    //~Plus(){ delete[] buf }
    char* operator+(const Plus& pobj){
        ;//...
    }
};
void add_MAX_MAX(char *buf1, char *buf2)
{
}
#include<stdio.h>
void test_add_MAX_MAX()
{
    printf("INT_MAX:%d \n",INT_MAX);
    //char buf1[INT_MAX+1]; //警告：整数溢出 [-Woverflow]
    //char buf1[INT_MAX]; //错误：局部对象的总大小太大
}

