#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

void* worker1(void* arg);
void* worker2(void* arg);
void test_thread_variable_addr();

int main()
{
	test_thread_variable_addr();
	pause();
	return 0;
}


const int i=5;
__thread int var=i;//两种方式效果一样
//__thread int var=5;//
void test_thread_variable_addr(){
	int m = 4;
	cout<<"global temp: "<<&m<<endl;
	pthread_t pid1,pid2;
	//__thread int temp=5;
	static __thread  int temp=10;//修饰函数内的static变量
	pthread_create(&pid1,NULL,worker1,NULL);
	pthread_create(&pid2,NULL,worker2,NULL);
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	cout<<"temp: "<<temp<<endl;//输出10
}


void* worker1(void* arg){
	int m = 2;
	cout<<"thread val:"<<&m<<endl;
	cout<<"thread1: pt:"<<&var<<" value:"<<++var<<endl;//输出 6
}
void* worker2(void* arg){
	sleep(1);//等待线程1改变var值，验证是否影响线程2
	cout<<"thread2: pt:"<<&var<<" value:"<<++var<<endl;//输出 6
}

