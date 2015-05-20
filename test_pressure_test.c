#include <stdio.h>
#include <time.h>
#include <ext/hash_map> 
#include "common.h"
using __gnu_cxx::hash_map; 
typedef struct timespec TimeSpec;

void test_hashmap_20w();


int main()
{
    test_hashmap_20w();

    return 0;
}


//---- ---- ---- ---- ---- ----
void test_hashmap_20w()
{
    ENTER_TEST();
    typedef hash_map<int, int> IPMap;
    typedef IPMap::iterator IPMapIterator;
    IPMap ipmap;
    int tmp;
    TimeSpec time;
    clock_gettime(CLOCK_REALTIME, &time);
    printf("sec:%ld \n",time.tv_sec);
    for (int i=0; i<1000000; ++i){
        tmp = rand()%10;
        ipmap.insert(std::pair<int, int>(i, tmp));
    }
    clock_gettime(CLOCK_REALTIME, &time);
    printf("sec:%ld \n",time.tv_sec);
    IPMapIterator iter = ipmap.begin();
    int oldsize = ipmap.size();
    while(iter!=ipmap.end()){
        if (iter->first%2 == 0){
	    ipmap.erase(iter++);
	    continue;
	}
	++iter;
    }
    clock_gettime(CLOCK_REALTIME, &time);
    printf("sec:%ld \n",time.tv_sec);
    printf("size change: oldsize:%d size:%d [100w的话有1s内的卡顿，10w没卡顿]\n",oldsize,ipmap.size());
}



