#include<stdio.h>

class Test{
public:
    Test():m(9){}
    int getcount(); 
    int getcount2(); 
private:
    int m;
};
inline int Test::getcount(){
    printf("run count \n");
    return m;
}
int Test::getcount2(){
    printf("run count2 \n");
    return m;
}

int main()
{
    Test tt;
    printf("getcount:%d \n",tt.getcount());
    printf("getcount2:%d \n",tt.getcount2());
    return 0;
}
/*
g++ -g test_compiler.c or -O0
(gdb) p tt
$1 = {m = 9}
(gdb) p tt.getcount()
run count 
$2 = 9
(gdb) p tt.getcount2()
run count2 
$3 = 9
-------------------
g++ -g test_compiler.c -O1 [尝试优化编译时间和可执行文件大小]
(gdb) p tt
$1 = {m = 9}
(gdb) p tt.getcount()
Cannot evaluate function -- may be inlined
(gdb) p tt.getcount2()
run count2 
$2 = 9
-------------------
g++ -g test_compiler.c -O2 [更多的优化，会尝试几乎全部的优化功能，但不会进行“空间换时间”的优化方法]
(gdb) p tt
$3 = {m = 9}
(gdb) p tt.getcount()
Can't take address of "tt" which isn't an lvalue.
(gdb) p tt.getcount2()
Can't take address of "tt" which isn't an lvalue.
-------------------
g++ -g test_compiler.c -O3 [在-O2的基础上再打开一些优化选项：-finline-functions， -funswitch-loops 和 -fgcse-after-reload]
(gdb) p tt
$1 = {m = 9}
(gdb) p tt.getcount()
Can't take address of "tt" which isn't an lvalue.
(gdb) p tt.getcount2()
Can't take address of "tt" which isn't an lvalue.
--------------------
g++ -g test_compiler.c -O3 -fno-inline
(gdb) p tt.getcount()
run count 
$2 = 9
(gdb) p tt.getcount2()
run count2 
$3 = 9

*/
