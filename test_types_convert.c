#include <stdio.h>
#include "common.h"

void test_double_division();

int main()
{
    test_double_division();
    return 0;
}

//---- ---- ---- ---- ---- ----
void test_double_division()
{
    ENTER_TEST();
    double d = 3.1416;
    printf("double: %.2f %.2f \n",d,d/3.0);
    printf("double: %.2f %.2f \n",d,d/3);
    printf("double: %.2f %.2f \n",6,6/d);
}

