#include <unistd.h>
#include <stdio.h>

void test_vfork1();
void test_vfork2();

int main(void)
{
    //test_vfork1();
    test_vfork2();
    return 0;
}




//---- ---- rel ---- ---->
void test_vfork1() //why coredump.
{
    pid_t pid;
    int count=0;
    pid=vfork();
    count++;
    printf("vfork1 count= %d\n",count);
}

void test_vfork2()
{
    pid_t pid;
    int count=0;
    pid=vfork();
    if(pid==0)
    {
        count++;
        _exit(0);
    }
    else
    {
        count++;
    }
    printf("vfork2 count= %d\n",count);
}

