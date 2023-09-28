#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include<math.h>

typedef struct Node {
    int key;
    struct Node *right;
    struct Node *left;
}Node;

typedef struct Info {
    Node * root;
    float size;
}Info;

typedef struct RBST {
    Info * info;
}RBST;

RBST initRBST(); //Initializes an RBST struct to an empty tree

Node * insertRand(Node * node, Node * new, int size, int * visits);

Node * createNode(int key); //creates node with given key 

int insertRBST(RBST bst, int key); //Inserts and returns number of nodes visited

Node * insertNode(Node * node, Node * insert);

void inOrderPrintBST(RBST tree);

void inOrderRec(Node * node);

void flattenRec(Node * node);

int freeRBST(RBST bst); //Frees entire tree and returns number of nodes visited

int freeTree(Node * tree, int * visits);  

int testInsertRBST(int n, int*unknown);

int testFreeRBST(int n, int*unknown);

int scalingTests(int tests_per);