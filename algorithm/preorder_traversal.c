#include <stdio.h>
#include <stack>
using namespace std;

typedef struct _treenode{
	_treenode(int v, _treenode* l, _treenode* r):
			val(v),left(l),right(r){}
	int val;
	_treenode* left;
	_treenode* right;
}_treenode;

void visit(_treenode* root){
	stack<_treenode*> nodes;	
	_treenode* pnode = root;
	
	while(true){
		//pop and print.
		//pnode = ?
		if (nodes.size() > 0){
			pnode = nodes.top();
			printf("%d \n",pnode->val);
			nodes.pop();

			if (nodes.size() > 0){
				pnode = nodes.top();
				nodes.pop();
				//printf("%d \n",pnode->val);
			}
			else
				break;
		}

		//push.
		if (pnode->right != NULL)
			nodes.push(pnode->right);
		if (pnode->left != NULL)
			nodes.push(pnode->left);
		nodes.push(pnode);
	}
}

int main()
{
	_treenode lea4(4,NULL,NULL);
	_treenode lea5(5,NULL,NULL);
	_treenode lea1(2,&lea4,&lea5);
	_treenode lea2(3,&lea4,&lea5);
	_treenode root(1,&lea1,&lea2);
	visit(&root);
	return 0;
}



