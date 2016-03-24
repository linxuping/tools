#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
/*
    auto x = 2;
    decltype(x) y = x; 
    printf("x:%d, y:%d \n",x,y);
    int arr{11,22,33};
    for (auto _a : arr){
        printf("arr item:%d \n",_a);
    }
*/
		auto func = [] () { printf("hello,world\n"); };
		printf("after auto func.\n");
		func(); // now call the function

		std::vector<int> c { 1,2,3,4,5,6,7 };
		int x = 5;
		c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; } ), c.end());
		for_each(begin(c), end(c), [&](int n){  //= assignment of read-only variable ‘x’
			x=n;
			printf("each:%d x:%d \n",n,x);
		});

		function<int (char &c)> myfunc = [](char &c) { cout<<c<<endl; c='t'; return 9; };
		if(myfunc){
			cout<<"myfunc:"<<endl;
			char chh = 'h';
			int t = myfunc(chh);//'h'
			cout<<t<<endl;//9
			cout<<chh<<endl;//'t'
		}

    return 0;
}

//g++ -std=c++11 test_c++11.c
