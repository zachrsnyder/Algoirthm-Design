/*
    Aaron Yang
    Lab 11
    CS_2050
    Spring 2023
*/

typedef struct Node Node;

struct BST{
    Node *root;
    int size;
    int max;
};

struct Node {
    int info;
    Node *right;
    Node *left;
};

Node* insertBSTRecursion(Node *node, int data);
Node* newNode(int data);
void preOrderPrintBSTRecursion(Node *tree);
void deleteTree(Node *node);

#include "lab11.h"

BST * initBST()
{
    BST *bst;
    bst = malloc(sizeof(BST));
    if(bst == NULL) //checks if malloc worked correctly returns NULL if not
    {
        bst = NULL;
        printf("\nMALLOC HAS FAILED\n");
        return(bst);
    }

    bst->size = 0; //sets the size to zero
    bst->root = NULL; //root pointer to NULL
    return(bst); //returns the pointer to the BST struct
}

int insertBST(BST *tree, int data)
{
    if(tree->root == NULL) //checks if the bst is empty
    {
        tree->root = insertBSTRecursion(tree->root, data); //adds a single node if it is empty
        tree->max = data; //since the tree is empty the new node must have the maximum value
        tree->size += 1; //increments the size by one
        return(0); //returns zero upon success
    }
    else
    {
        insertBSTRecursion(tree->root, data); //otherwise it itereates through the tree untill
        if(data > tree->max)                  //the right spot is found
        {
            tree->max = data; //checks if there is a new maximum
        }
        tree->size += 1;//increments size by one
        return(0);
    }
    return(1); //returns one for an error
}

int getSizeBST(BST *tree)
{
    return(tree->size); //returns the size of the tree
}

int getMaxBST(BST *tree)
{
    return(tree->max); //returns the max of the tree
}

void preOrderPrintBST(BST *tree)
{
    if(tree->root == NULL)
    {
        return; //if the tree is empty there is nothing to print
    }
    else
    {
        preOrderPrintBSTRecursion(tree->root); //explained in the helper fucntion
    }

}

void freeBST(BST *tree)
{
    deleteTree(tree->root); //explained in the helper fucntion, frees the entire tree besides the bst pointer
    free(tree); //frees the bst pointer
}

//------------------------------Helper Fucntions------------------------------//

Node* insertBSTRecursion(Node *node, int data)//recursive helper fucntion for insertBST
{
    if(node == NULL)
    {
        return newNode(data); //base case, adds a node when it is reached
    }

    if(data < node->info)
    {
        node->left = insertBSTRecursion(node->left, data); //goes to the left tree if new data is less than
    }                                                      //the current data
    else if(data > node->info)
    {
        node->right = insertBSTRecursion(node->right, data); //goes to the right tree if new data is more than
    }                                                        //the current data
    return(node);
}

Node* newNode(int data) //helper fucntion for creating a node
{
    Node *new_node;
    new_node = malloc(sizeof(Node)); //helper function just to make a node 
    if(new_node == NULL)
    {
        printf("\nMALLOC has failed\n");
        return(NULL);
    }

    new_node->info = data; //sets the data
    new_node->left = NULL; //sets the right and left pointers to NULL
    new_node->right = NULL;
    return(new_node); //returns the new node
}

void preOrderPrintBSTRecursion(Node *tree)//helper function for preOrderPrintBST
{
    if(tree == NULL) //if the tree is NULL then there is nothing to print
    {
        return;
    }
    else
    {
        printf("\n%d\n", tree->info);
        preOrderPrintBSTRecursion(tree->left); //iterates through the left tree and prints everything in preorder
        preOrderPrintBSTRecursion(tree->right);//iterates through the right tree and prints everything in preorder
    }
}

void deleteTree(Node *node) //helper function for freeBST
{
    if(node == NULL) //if the tree is NULL then there is nothing to free
    {
        return; 
    }

    deleteTree(node->left); //iterates trhough the left tree and frees all nodes
    deleteTree(node->right);//iterates through the right tree and frees all nodes
    free(node);
}