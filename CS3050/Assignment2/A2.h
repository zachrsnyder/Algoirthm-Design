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

void countArray(Node * node, int * array_size, int * visits);

void flattenInArray(Node * node, int * array, int * index, int * visits);

//int * ripApart(Node *node, Node * prev, int data, int * insert_length, int left);

RBST initRBST(); //Initializes an RBST struct to an empty tree

Node * insertRand(Node * node, Node * new, int size, int * visits);

int * flatten(Node * node, int * array_size, int * visits);

Node * createNode(int key); //creates node with given key 

int insertRBST(RBST bst, int key); //Inserts and returns number of nodes visited

Node * insertNode(Node * node, int key, int * visits);

void inOrderPrintBST(RBST tree);

void inOrderRec(Node * node);

//Node * flatten(Node * node, int * size);

void flattenRec(Node * node, int * size, int * visits);

int freeRBST(RBST bst); //Frees entire tree and returns number of nodes visited

int freeTree(Node * tree, int * visits);  

//int testInsertRBST(int n, int*unknown);
//int testFreeRBST(int n, int*unknown);