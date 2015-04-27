#include<stdio.h>
#include "common.h"

void test_delete_link_node();


int main()
{
    test_delete_link_node();
    
}


typedef struct LNode LNode;
struct LNode{
    int value;
    LNode* next;
    LNode(int val,LNode* next):value(val),next(next){}
};
void print_lnode(const LNode* head)
{
    while(NULL != head){
        printf("%d \n",head->value);
        head = head->next;
    }
}
bool compare(int m){
    return m == 2;
}
typedef bool (*PCompare)(int m);
void delete_link_node_old(LNode* head, PCompare pfun)
{
    //assert(head)
    LNode* prev = head;
    LNode* cur = head->next;
    if (pfun(prev->value)){ //not *pfun(prev->value)
        if (NULL == cur) 
            head = NULL;
        else
            head = cur;
        return;
    }
    while(NULL != cur){
        printf("in: %d \n",cur->value);
        if (pfun(cur->value)){
            prev->next = cur->next;
            printf("hit: %d prev value:%d next:%d\n",cur->value,prev->value,prev->next->value);
        }
        prev = prev->next;
        cur = cur->next;
    }
}
void test_delete_link_node()
{
    ENTER_TEST();
    //prepare
    LNode n3(3,NULL);
    LNode n2(2,&n3);
    LNode n1(1,&n2);
    LNode head(0,&n1);
    print_lnode(&head);

    delete_link_node_old(&head, compare);
    print_lnode(&head);

    //尝试使用LNode**而不是prev
    //delete_link_node_new(&head, compare);
    //print_lnode(&head);
}


