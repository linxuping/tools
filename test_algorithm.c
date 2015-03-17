#include<stdio.h>
#include<assert.h>

void test_arrange();
void test_add_1_to_MAX();
void test_add_MAX_MAX();
void test_links_merge();
void test_greaterthan_without_operator();

int main()
{
		test_arrange();
		//test_add_1_to_MAX();
		test_add_MAX_MAX();
		test_links_merge();
    test_greaterthan_without_operator();

		return 0;
}

void swap(char *p1, char *p2){
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
}
void my_arrange(char *buf, int pos1, int pos2)
{
		if (pos1 >= pos2){
				return;//printf("- buf:%s -\n",buf);
		}
		for (int i=pos1; i<=pos2; ++i){
				swap(&buf[pos1], &buf[i]);
				printf("pos1:%d i:%d buf:%s \n",pos1,i,buf);
				my_arrange(buf, pos1+1, pos2); //not my_arrange(buf, i+1, pos2);
				swap(&buf[pos1], &buf[i]);
		}
}
void test_arrange()
{
		char buf[] = "1234";
		my_arrange(buf, 0, 3);
}

#include<limits.h>
void test_add_1_to_MAX()
{
		//printf("int max:%d \n",INT_MAX);
		int count = 0;
		for(int i=0; i<INT_MAX; ++i)
				count += i;
		printf("%s  count:%u > INT_MAX:%d \n",__FUNCTION__,count,INT_MAX);
		//INT_MAX*2
}

class Plus{
		public:
				char m; //jinwei
				//enum Enum{ MAX_SIZE=20 };
				char *buf;
				explicit Plus(const char* buf2){
						/*
						   int len = strlen(buf2)+1;
						   buf = (char*)malloc(len);
						   memset(buf,0,MAX_SIZE);
						   strcpy(buf, buf2);
						 */
				}
				//~Plus(){ delete[] buf }
				char* operator+(const Plus& pobj){
						;//...
				}
};
void add_MAX_MAX(char *buf1, char *buf2)
{
}
#include<stdio.h>
void test_add_MAX_MAX()
{
		printf("INT_MAX:%d \n",INT_MAX);
		//char buf1[INT_MAX+1]; //警告：整数溢出 [-Woverflow]
		//char buf1[INT_MAX]; //错误：局部对象的总大小太大
}

typedef struct LNode LNode;
struct LNode{
		int val;
		struct LNode* next;
};
void print_LNode(const LNode* head){
		assert(head != NULL);
		printf("%s \n",__FUNCTION__);
		while(head != NULL){
				printf("LNode:%d \n",head->val);
				head = head->next;
		}
}
void links_merge(LNode* p1, LNode* p2, LNode* pt)
{
		if (NULL == p1){
				pt->next = p2;
				return;
		}
		else if (NULL == p2){
				pt->next = p1;
				return;
		}

		if (p1->val <= p2->val){
				pt->next = p1; 
				p1 = p1->next;
		}
		else{
				pt->next = p2; 
				p2 = p2->next;
		}
		links_merge(p1, p2, pt->next);
}
void links_merge2(LNode* p1, LNode* p2, LNode* pnew)
{
		LNode* pt = pnew;
		while((NULL!=p1) && (NULL!=p2)){
				//if bigger added
				if (p1->val <= p2->val){
						pt->next = p1; 
						p1 = p1->next;
				}
				else{
						pt->next = p2; 
						p2 = p2->next;
				}
				pt = pt->next;
		}
		if (NULL == p1){
				pt->next = p2;
				return;
		}
		else if (NULL == p2){
				pt->next = p1;
				return;
		}
}
void test_links_merge()
{
		//prepare l1(1,3,5) l2(2,4,5,6,7)
		LNode l10,l11,l12;
		l12.val = 3;
		l12.next = NULL;
		l11.val = 3;
		l11.next = &l12;
		l10.val = 1;
		l10.next = &l11;
		print_LNode(&l10);
		LNode l20,l21,l22,l23,l24;
		l24.val = 7;
		l24.next = NULL;
		l23.val = 6;
		l23.next = &l24;
		l22.val = 5;
		l22.next = &l23;
		l21.val = 4;
		l21.next = &l22;
		l20.val = 2;
		l20.next = &l21;
		print_LNode(&l20);
		//
		LNode lnew;
		lnew.val = 0;
		lnew.next = NULL;
		//links_merge(&l10, &l20, &lnew);
		links_merge2(&l10, &l20, &lnew);
		print_LNode(lnew.next);
}

//00000000 00000000 00000000 00000000
bool greaterthan_without_operator(int a, int b)
{
    a = a - b;
    return (a>>31) == 0;
}
void test_greaterthan_without_operator()
{
    printf("%s 1 2 :%d \n",__FUNCTION__,greaterthan_without_operator(1,2));
    printf("%s 1 -2 :%d \n",__FUNCTION__,greaterthan_without_operator(1,-2));
    printf("%s 1 1 :%d \n",__FUNCTION__,greaterthan_without_operator(1,1));
}


