#include<iostream>
using namespace std;

struct Node {
    int m;
    Node *left;
    Node *right;
};

struct Tree {
    Node *root;
};

void visit_tree(Node *node) {
    if (node == NULL) {
        printf("visit tree fin.\n");
        return;
    }
    printf("%d\n",node->m);
    if (node->left) {
        visit_tree(node->left);
    }
    else if (node->right) {
        visit_tree(node->right);
    }
}

void pre_visit_tree(Node *node) {
    if (node == NULL) {
        printf("visit tree fin.\n");
        return;
    }
    printf("%d\n",node->m);
    if (node->left) {
        pre_visit_tree(node->left);
    }
    if (node->right) {
        pre_visit_tree(node->right);
    }
}

/* error version must +1 */
int get_tree_len(Node *node, int depth) {
    if (node == NULL) {
        printf("visit tree fin.\n");
        return 0;
    }
    printf("%d\n",node->m);
    int dep = 0;
    if (node->left) {
        dep = get_tree_len(node->left, depth+1);
    }
    else if (node->right) {
        dep = get_tree_len(node->right, depth+1);
    }
    return dep>depth? dep:depth;
}

int get_tree_len2(Node *node) {
    if (node == NULL) {
        printf("visit tree fin.\n");
        return 0;
    }
    printf("%d\n",node->m);
    int depl = get_tree_len2(node->left);
    int depr = get_tree_len2(node->right);
    return max(depl,depr)+1;
}

int main(){
    printf("123\n"); 
    Node *root = new Node();
    root->m = 0;
    Node *n1 = new Node();
    n1->m = 11;
    Node *n2 = new Node();
    n2->m = 12;
    Node *n3 = new Node();
    n3->m = 32;
    Node *n4 = new Node();
    n4->m = 41;
    Node *n5 = new Node();
    n5->m = 51;

    root->left = n1;
    root->right = n2;

    n1->right = n3;

    n3->left = n4;

    n4->left = n5;

    visit_tree(root);
    int len = get_tree_len(root, 0);
    printf("depth: %d\n", len);
    int len2 = get_tree_len2(root);
    printf("depth 2: %d\n", len2);
    printf("+++ pre_visit_tree: \n");
    pre_visit_tree(root);
}
