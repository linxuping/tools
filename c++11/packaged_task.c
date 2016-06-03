//http://www.atatech.org/articles/55579/?frm=mail_daily&uid=141710
//g++ packaged_task.c --std=c++11 -g -Wl,--no-as-needed -lpthread
#include <iostream>
#include<vector>
#include <future>
using namespace std;

long long jiechen(int n)
{
	long long ret=1;
	for (int i=1;i<=n; i++)
		ret*=i;
	return ret;

}

int main()
{
	vector<int> data={9,11,13,17,19};
	vector<future<long long>> fus;
	for (auto i:data)
	{
		packaged_task<long long() > pt(bind(jiechen,i));
		fus.push_back(std::move(pt.get_future()));
		std::thread(std::move(pt)).detach();
	}
	for(auto& i:fus)
	{
		i.wait();
		cout<<i.get()<<endl;
	}
	return 0;
}
