#include <stdio.h>

int main()
{
    auto x = 2;
    decltype(x) y = x; 
    printf("x:%d, y:%d \n",x,y);
    int arr{11,22,33};
    for (auto _a : arr){
        printf("arr item:%d \n",_a);
    }
    return 0;
}

//g++ -std=c++11 test_c++11.c
