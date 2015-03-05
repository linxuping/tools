#include <vector>
#include <iostream>
#include <algorithm> //heap algorithms
#include <iterator>  //ostream_iterator
using namespace std;

void test_heap();

int main()
{
    test_heap();
    return 0;
}

void test_heap()
{
/*
    int i=0; //底层是个list
    int ia[9]={0,1,2,3,4,8,9,3,5};
    vector<int> ivec(ia,ia+9);
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); //0 1 2 3 4 8 9 3 5
    cout<<endl;
    make_heap(ivec.begin(),ivec.end());
    cout<<"after make_heap:"<<endl;
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); //9 5 8 3 4 0 2 3 1(堆排序的大根堆)
    cout<<endl;
    ivec.push_back(7);
    cout<<"after ivec.push_back(7)"<<endl;
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    push_heap(ivec.begin(),ivec.end());
    cout<<"after push_heap(ivec.begin(),ivec.end())"<<endl;
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); //9 7 8 3 5 0 2 3 1 4(堆排序)
    cout<<endl;
    pop_heap(ivec.begin(),ivec.end()); //根节点和最后一个叶子节点互换
    cout<<"top: "<<ivec.back()<<", pop_back >>"<<endl; //9
    ivec.pop_back(); //删除最后一个叶节点
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); //8 7 4 3 5 0 2 3 1(堆排序去掉根节点的方法相同)
    cout<<endl;
    sort_heap(ivec.begin(),ivec.end()); //从小到大排序，一个递增序列 
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); //0 1 2 3 3 4 5 7 8
    cout<<endl;
    sort_heap(ivec.begin(),ivec.end(),greater<int>()); //反： 从小到大排序，一个递增序列 
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); 
    cout<<endl;
    //底层是个array(不能动态添加元素成员)
    cout<<"the array:"<<endl;
    copy(ia,ia+9,ostream_iterator<int>(cout," "));
    cout<<endl;
    make_heap(ia,ia+9);
    cout<<"the array after make_heap:"<<endl;
    copy(ia,ia+9,ostream_iterator<int>(cout," ")); //9 5 8 3 4 0 2 3 1
    cout<<endl;
    sort_heap(ia,ia+9); //经过排序的heap不再是个合法的heap
    cout<<"the array after sort_heap:"<<endl;
    copy(ia,ia+9,ostream_iterator<int>(cout," "));
    cout<<endl;
    make_heap(ia,ia+9);
    copy(ia,ia+9,ostream_iterator<int>(cout," ")); //9 8 5 3 3 4 2 1 0
    cout<<endl;
    pop_heap(ia,ia+9);
    copy(ia,ia+9,ostream_iterator<int>(cout," ")); //8 3 5 3 0 4 2 1 9
    cout<<endl;
    cout<<ia[8]<<endl; //9
*/
    int i=0; //底层是个list
    int ia[9]={10,11,12,13,14,18,19,13,15};
    vector<int> ivec(ia,ia+9);

    make_heap(ivec.begin(),ivec.end());
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); 
    cout<<endl;

    ivec.push_back(7);
    push_heap(ivec.begin(),ivec.end());
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); 
    cout<<endl;

    ivec.push_back(17);
    push_heap(ivec.begin(),ivec.end());
    copy(ivec.begin(),ivec.end(),ostream_iterator<int>(cout," ")); 
    cout<<endl;
    //实践证明，push_heap并不会导致前100个是最大的，如何搞？ 对于算法题
}


