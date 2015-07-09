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

void delete_link_node_new(LNode** head, PCompare pfun)
{//change the *pt
    LNode** cur = head;
	while(*cur != NULL){
	   if (pfun( (*cur)->value )){
	       //delete *cur
	       *cur = (*cur)->next;
	   }
	   cur = &((*cur)->next);
	}
}

/*
 * refer to http://coolshell.cn/articles/8990.html
 */
void delete_link_node_by_LinusTorvalds(LNode** head, PCompare pfun)
{//change the *pt
    for (LNode **curr=head; *curr; ){
	    LNode *entry = *curr;
		if (pfun(entry->value)){
		    *curr = entry->next;
			//free entry
		}
		else
		    curr = &entry->next;
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

    printf("Ready for LinusTorvalds's method... ...\n");
    LNode n30(3,NULL);
    LNode n20(2,&n30);
    LNode n10(1,&n20);
    LNode head0(0,&n10);
    print_lnode(&head0);

    LNode *ht = &head0;
    LNode **pt = &ht;
    printf("try LinusTorvalds's method... ...\n");
    delete_link_node_by_LinusTorvalds(pt, compare);
    //delete_link_node_new(&(&head0), compare);//error: lvalue required as unary ¿&¿ operand
    print_lnode(&head0);

}


