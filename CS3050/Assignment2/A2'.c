#include"A2.h"

RBST initRBST()
{
    RBST bst;
    bst.info = NULL;
    Info * init;
    init = malloc(sizeof(Info));
    if(!init){
        printf("\nMalloc of Info Struct Failed\n");
    }else{
        init->root = NULL;
        init->size = 0;
    };
    bst.info = init;
    return(bst);
}

Node* insertRec(Node *node, int data, float size, int * visits)
{
    if(node == NULL)
    {
        ++(*visits);
        return createNode(data);
    };
    if(data <= node->key){
        ++(*visits);
        node->left = insertRec(node->left, data, size/2, visits);
    }
    else{
        ++(*visits);
        node->right = insertRec(node->right, data, size/2, visits);
    };
    return(node);
}

Node* createNode(int key)
{
    Node * new;
    new = malloc(sizeof(Node));
    if(!new)
    {
        printf("Allocation of new node failed\n");
        return NULL;
    }else
    {
        new->key = key;
        new->left = NULL;
        new->right = NULL;
        return new;
    };
}

int insertRBST(RBST bst, int key) //Inserts and returns number of nodes visited
{
    int visits = 0;
    if(bst.info->root == NULL)
    {
        ++bst.info->size;
        bst.info->root = createNode(key);
        return visits+1;
    }else
    {
        ++bst.info->size;
        insertRec(bst.info->root, key, bst.info->size, &visits);
        return visits;
    };

}

/*This function was made to test the removal of a subtree from a BST, which will then be flattened into a list, then reinserted.*/

Node * ripApart(Node *node, int data, int * size)
{
    int newKey = node->key;
    Node * new_root = createNode(node->key);
    node->key = data;
    new_root->left = node->left;
    new_root->right = node->right;
    node->left = NULL;
    node->right = NULL;
    return new_root;
}

void flattenRec(Node * node, int * size, int * visits)
{
    //tests for node existence and if it is a leaf node.
    ++(*visits);
    if(node == NULL)
        return;
    ++(*size);
    if(node->left == NULL && node->right == NULL)
        return;

    //if node left isn't NULL, then that value needs to be moved to the right and link the right to it.
    if(node->left != NULL){
        flattenRec(node->left, size, visits);
        //storing right leaf to attach it to the left after the left becomes the right
        Node * right_temp = node->right;
        node->right = node->left;
        node->left = NULL;

        Node * ind = node->right; //index right-right-right until the end of the list is found
        while(ind->right != NULL)
            ind = ind->right;
        //insert the stored value
        ind->right = right_temp;
    };
    
    flattenRec(node->right, size, visits);
}

void inOrderPrintBST(RBST tree)
{
    inOrderRec(tree.info->root);
}

void inOrderRec(Node * node)
{
    if(!node)return;
    inOrderRec(node->left);
    printf("\n%d\n", node->key);
    inOrderRec(node->right);
}


int freeRBST(RBST bst) //Frees entire tree and returns number of nodes visited
{
    int visits = 0;
    visits = freeTree(bst.info->root, &visits);
    free(bst.info);
    return visits;
}

int freeTree(Node * tree, int * visits) //helper function to recursively delete nodes in the list
{
    if(tree == NULL)
    {
        return *visits;
    };
    freeTree(tree->left, visits);
    freeTree(tree->right, visits);
    ++(*visits);
    free(tree);
    return *visits;
}