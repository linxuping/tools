#include <stdio.h>
#include <typeinfo>
#include "common.h"

//template <class T>
template <class T, class T2>
int count(T* first, T* last, const T2& value) {
    int n = 0;
	for ( ; first != last; ++first)
		if (*first == value)
			++n; 
    return n;
}

class Test{};
template <class T>
void test_type(const T& value)
{
    printf("T size:%d type:%s \n",sizeof(T),typeid(value).name() );
}


int main()
{
    int ret = 0;
    float n1[5] = {1.1f, 1.2f, 1.3f, 1.2f, 0.0f};
    ret = count( &n1[0],&n1[4],1.2f );
    printf("count<float> size:%d \n", ret );
    ret = count( &n1[0],&n1[4],1.2 );
    printf("count<float> size:%d \n", ret );
    int n2[5] = {1, 2, 3, 2, 0};
    ret = count( &n2[0],&n2[4],3 );
    printf("count<int> size:%d \n", ret );

    test_type( (int)1 );
    test_type( (float)1 );
    test_type( (double)1 );
    Test tt;
    test_type( tt );
 
    return 0;
}
