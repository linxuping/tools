#include<stdio.h>
#include<vector>
#include<list>
using namespace std; //needed
//using std::vector; //needed

void test_vector_erase();
void test_list_erase();

int main()
{
    test_vector_erase();
    test_list_erase();
    return 0;
}

//---- rel ---->
void test_vector_erase()
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    vec.push_back(1);
    printf("%s capacity:%d, size:%d \n",__FUNCTION__,vec.capacity(),vec.size());
    typedef vector<int>::iterator Myiterator;
    Myiterator pos = vec.begin();
    while(pos != vec.end()){
        pos = vec.erase(pos);
        //vec.erase(pos++); //coredump 
    }
    printf("%s capacity:%d, size:%d \n",__FUNCTION__,vec.capacity(),vec.size());
}

void test_list_erase()
{
    list<int> lis;
    lis.push_back(1);
    lis.push_back(1);
    lis.push_back(1);
    lis.push_back(1);
    lis.push_back(1);
    lis.push_back(1);
    lis.push_back(1);
    printf("%s size:%d \n",__FUNCTION__,lis.size());
    typedef list<int>::iterator Myiterator;
    Myiterator pos = lis.begin();
    while(pos != lis.end()){
        //pos = lis.erase(pos);
        lis.erase(pos++); //ok 
    }
    printf("%s size:%d \n",__FUNCTION__,lis.size());
}

