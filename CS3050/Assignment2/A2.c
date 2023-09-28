#include"A2.h"

/*RBST initRBST()
*   This function creates an RBST, then mallocs a info struct, checks for malloc's success,
*   then upon it's succes, it initializes the root of the tree (represented by bst.info->root) to NULL.
*   Upon failure, it tells the user that malloc failed. After this, info struct created is assigned as the info struct of the bst, then the bst is returned.
*/

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
    srand48(time(0)); //seeds the random number genarator so that is different each time.
    return(bst);
}


//linked list will work with recursive in order traversal just pass node->right
/*void flattenRec(Node * node, int * size, int * visits)
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
}*/


/*Node* insertRec(Node *node, Node*prev, int left, int data, float size, int * visits)
* This is the insert algorithm for this randomzied amortized probabilistic binary search tree (BST) the steps are as follows:
*   1.  test node for NULL. This case means that we are inserting into a empty tree (the root would be NULL) or that we have arrived at the very end of a branch, where the pointer is currently NULL.
*   2. test randomized value and size ratio. With a probability reliant on the size of the current tree or subtree, if this statement is to be TRUE, the current node will then be replaced by the key we are inserting, the subtree will be flattened, then the flattened tree will be reinserted using this same function.
*       a. If the previous is NULL, then we are dealing with a tree that will consist of two nodes upon this ones entry. The idea is to make the new node the root, and then make comparisons to decide where to attach the original root node.
*       b. If the case above fails, we have two other cases, but both can begin with the ripApart function (see description for that). Upon creating that array, two cases follow.
*       c. If both pointers of the current node are NULL, then we are currently on a leaf node. Therefore it can be assumed that the ripApart returned an array of size 1. The singular index of this array can then be inserted back into the newly replaced node of tree then noed can be returned.
*       d. For i = 0 in the range of the size of the array, each index of the array is inserted into the tree starting from the root recently switched.
*   3. If the random probability doesn't trigger, then the key is compared to the value of the current node, if it is less than it, this function is called recursively to the left of the current node.
*   4. If that above is false, it can be assumed that the key is greater than the current node's value, so this function is called recursively to the right of the current node.
*/



/*Node* insertRec(Node *node, Node*prev, int left, int data, float size, int * visits)
{
    ++(*visits);
    if(node == NULL) //either have an empty tree, or at a left or right pointer of a leaf node, simply return new node
    {
        return createNode(data);
    };
    float d = 1/(size + 1); //size of subtree + 1 for the new node being inserted into that tree over one to make a probability
    printf("size ratio : %f\n", d);
    if(drand48() < d) //compares random decimal from 0-1 to the probability that the key will become the value
    {  
        printf("triggered\n");
        int insert_length = 0;
        int * array = ripApart(node, prev, data,&insert_length, left);
        if(prev == NULL) //this is the first node in the tree that you are switching
        {
            printf("!");
            Node * new = createNode(data);
            ++(*visits);
            for(int i = 0; i < insert_length; ++i)
            {
                new = insertRec(new, NULL, 0, array[i], i+1, visits);
            };
            free(array);
            return new;
        }
        printf(">");
        if((node->right == NULL) && (node->left == NULL))//current node is a leaf node.
        {
            printf("$");
            node = insertRec(node, prev, left, array[0], 2, visits);
            free(array);
            return node;
        };
        for(int i = 0; i < insert_length; ++i)
        {
           printf("%%");
            node = insertRec(node, prev, left, array[i],i+1,visits);
        };
        free(array);
        return node;
    };
    if(data <= node->key){
        node->left = insertRec(node->left, node, 1, data, size/2.0, visits);
    }
    else{
        node->right = insertRec(node->right, node, 0, data, size/2.0, visits);
    };
    return(node);
}*/

Node * insertRand(Node * node, Node * new, int size, int * visits)
{
    ++(*visits);
    if(!node)
        return new;
    if(drand48() <= (float)1/(size + 1))
    {
        printf("it tripped\n");
        int size = 0;
        int * array = flatten(node, &size, visits);
        for(int i = 0; i < size; ++i)
        {
            printf("%d ", array[i]);
            insertNode(new, array[i], visits);
        };
        free(array);
        return new;
    }
    if(new->key <= node->key)
        node->left = insertRand(node->left, new, size/2, visits);
    else node->right = insertRand(node->right, new, size/2, visits);
    return node;
}

int * flatten(Node * node, int * array_size, int * visits)
{
    countArray(node, array_size, visits);
    int * treeFlat = malloc(sizeof(int) * *array_size);
    int index = 0;
    flattenInArray(node, treeFlat, &index, visits);
    int visits2 = 0;
    freeTree(node, &visits2);
    return treeFlat;
}

Node * insertNode(Node * node, int key, int * visits)
{
    ++(*visits);
    if(!node)
        return createNode(key);
    if(key <= node->key)
        node->left = insertNode(node->left, key, visits);
    else node->right = insertNode(node->right, key, visits);
    return node;
}

/*Node * switchRoot(Node * node, Node * prev, int key, int left)
*   1.  This function creates a new node with the new key.
*   2.  It then uses the left int as a boolean to test if the new key should be attached to the left or right of the previous node.
*   3.  Upon left being true prev->left becomes the new node created.
*   4.  

*/

/*Node * switchRoot(Node * node, Node * prev, int key, int left)
{
    Node * new = createNode(key);
    if(left)
    {
        prev->left = new;
        return node;
    }else{
        prev->right = new;
        return node;
    };
}*/


/*This function was made to test the removal of a subtree from a BST, which will then be flattened into a list, then reinserted. But I actually liked the function and how it can simplify the appearance of the insert function so I kept it.*/

/*int * ripApart(Node *node, Node * prev, int data, int * insert_length, int left)
{
    countArray(node, insert_length);
    int * array = malloc(sizeof(int) * (*insert_length));
    int index = 0;
    if(!prev)
    {
        flattenInArray(node, array, &index);
        return array;
    }
    if(*insert_length)
    {
        Node * detached = switchRoot(node, prev, data, left);
        node = detached;
        flattenInArray(detached, array, &index);
        return array;
    };
    return NULL;
}*/

void flattenInArray(Node * node, int * array, int * index, int * visits)
{
    ++(*visits);
    if(!node)return;
    flattenInArray(node->left, array, index, visits);
    array[*index] = node->key;
    ++(*index);
    flattenInArray(node->right, array, index, visits);
}

void countArray(Node * node, int * array_size, int * visits)
{
    ++(*visits);
    if(!node)return;
    countArray(node->left, array_size, visits);
    ++(*array_size);
    countArray(node->right, array_size, visits);
};

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
        return visits + 1;
    }else
    {
        Node * new = createNode(key);
        bst.info->root = insertRand(bst.info->root, new, bst.info->size, &visits);
        ++bst.info->size;
        return visits;
    };

}





void inOrderPrintBST(RBST tree)
{
    inOrderRec(tree.info->root);
}

void inOrderRec(Node * node)
{
    if(!node)return;
    inOrderRec(node->left);
    printf("%d\n", node->key);
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
