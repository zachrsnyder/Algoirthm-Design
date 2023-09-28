#include"zrshmn.h"

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
    //srand48(time(0)); seeds the random number genarator so that is different each time.
    return(bst);
}

/*void flattenRec(Node * node, int * size, int * visits)
*   1.  If node doesn't exist, or is a leaf node, then this portion is already flattened, so return.
*   2.  If node->left isn't NULL:
*       a) Call recursively to the left.
*       b) Move the left pointer in between the root and right.
*       c) Index to the end of the linked list. Then insert the node to the list.
*   3.  Call recursively to the right. 
*/
void flattenRec(Node * node)
{
    //tests for node existence and if it is a leaf node.
    if(node == NULL)
        return;
    if(node->left == NULL && node->right == NULL)
        return;

    //if node left isn't NULL, then that value needs to be moved to the right and link the right to it.
    if(node->left != NULL){
        flattenRec(node->left);
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
    
    flattenRec(node->right);
}
//#Code from GeeksforGeeks

/*Node * insertRand(Node * node, Node * new, int size, int * visits)
*   1.  If node doesn't exist, then we have arrived at a leaf node. This means the new node can simply be inserted at the bottom of the tree.
*   2.  drand48 produces a random decimal number between zero and one. That random number, compared with a ratio decided by the size of the current subtree, will trigger the if statement at random. Then it will do the following:
*       a)  The current subtree is flattened into a linked list, but using bst structure. See the flattenRec() function for more on that.
*       b)  While the linked list node exists, each member of the list is reinserted back into the BST using a traditional insertion function for BSTs.
*       c)  The new root is then returned by the function, which will then reattach it the original bst with the other values also attached.
*   3.  If the randomness doesn't pass, normal BST insertion is then used to decide where to move the new node recursively using this same function.
*   Size is devided by two each time the new node is moved further down the tree. This is done because balance is assumed for this tree, so the size of eachsubtree should be around half of the previous one. 
*/
Node * insertRand(Node * node, Node * new, int size, int * visits)
{
    ++(*visits);
    if(!node)
        return new;
    if(drand48() <= (float)1/(size + 1))
    {
        flattenRec(node);
        while(node)
        {
            Node * hold = node;
            node = node->right;
            insertNode(new, hold);
        };
        return new;
    }
    if(new->key <= node->key)
        node->left = insertRand(node->left, new, size/2, visits);
    else node->right = insertRand(node->right, new, size/2, visits);
    return node;
}


/*Node * insertNode(Node * node, Node * insert, int * visits)
*   This is a simple recursive insertion algorithm for BSTs. In this context it will be used to reinsert the flattened subtree back into the overall tree. 
*   1.  If node doesn't exist, then the inserted node is freed from the linked list "insert->right = NULL" the that node is returned.
*   2.  If we are still at an existing node, then compare the keys. If new node is less than, it goes left, and if its greater than, it goes right.   
*/
Node * insertNode(Node * node, Node * insert)
{
    if(!node){
        insert->right = NULL;
        return insert;
    };
    if(insert->key <= node->key)
        node->left = insertNode(node->left, insert);
    else node->right = insertNode(node->right, insert);
    return node;
}

/*Node * createNode(int key)
*   1.  Creates new node and mallocs the space equivalent to the size of a node.
*   2.  Tests for malloc failure. If it fails, NULL will be returned. If it succeeds, it initializes the new node to the specified key and assigns it's left and right pointers to NULL. 
*/
Node * createNode(int key)
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

/*int insertRBST(RBST bst, int key)
*   1.  If the root is NULL, then root can be assigned a node of the given key. Size will be incremented.
*   2.  Else, new node is created and it is passed to the insertRand function, which will decide it's fate.
*   3.  This function returns visits. This value is also passed to the insertRand function, and it keeps track of the number of nodes visited as the new value is inserted into the RBST.
*       However, to accurately show how the randomization effects the depth of the RBST, visits does not count node visits that take place during the flattening and reinsertion of the tree.
*/
int insertRBST(RBST bst, int key) //Inserts and returns number of nodes visited
{
    int visits = 0;
    if(bst.info->root == NULL)
    {
        ++bst.info->size;
        bst.info->root = createNode(key);
        if(bst.info->root == NULL)
        {
            return 0;
        }
        return visits + 1;
    }else
    {
        Node * new = createNode(key);
        if(!new)
        {
            return 0;
        }
        bst.info->root = insertRand(bst.info->root, new, bst.info->size, &visits);
        ++bst.info->size;
        return visits;
    };
}

/*void inOrderPrintBST(RBST tree)
*   Wrapper function used to call recursive inOrder print.
*/
void inOrderPrintBST(RBST tree)
{
    inOrderRec(tree.info->root);
}

/*void inOrderRec(Node * node)
*   1.  If there is no node, return.
*   2.  Call function recurively until far left of the tree is reached.
*   3.  Print the current nodes keys
*   4.  Move recursively to the right. Set up to hit lefts before rights. 
*/
void inOrderRec(Node * node)
{
    if(!node)return;
    inOrderRec(node->left);
    printf("%d\n", node->key);
    inOrderRec(node->right);
}

/*int freeRBST(RBST bst)
*   1.  Sets visits equal to recursive free tree function.
*   2.  Free the info struct for the RBST.
*   3.  Returns the number of visits, which is equivalent to the number of nodes in the tree.
*/
int freeRBST(RBST bst) //Frees entire tree and returns number of nodes visited
{
    int visits = 0;
    visits = freeTree(bst.info->root, &visits);
    free(bst.info);
    return visits;
}

/*int freeTree(Node * tree, int * visits)
*   1.  If current tree is NULL then return visits, nothing to be done with an empty node
*   2.  Recurses all the way left, moves right, then frees up the tree, keeping track of visits.  
*/
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

/*int testInsertRBST(int n, int*array)
*   1.  Initializes rbst and keeps track of total vists returned from all inserts, then returns that value
*/
int testInsertRBST(int n, int*unknown)
{
    RBST rbst = initRBST();
    int total_visits = 0;
    for(int i = 0; i < n; ++i)
    {
        int hold = insertRBST(rbst, unknown[i]);
        if(hold == 0)
        {
            return 0;
        }
        total_visits += hold;
    };
    return total_visits;
}

/*int testFreeRBST(int n, int*array)
*   1.  Initializes and creates a bst of specificied size.
*   2.  Frees using freeRBST function the returns the size. 
*/
int testFreeRBST(int n, int*unknown)
{
    RBST rbst = initRBST();
    int total_visits = 0;
    for(int i = 0; i < n; ++i)
    {
        int hold = insertRBST(rbst, unknown[i]);
        if(hold == 0)
        {
            return 0;
        };
    };
    total_visits = freeRBST(rbst);
    return total_visits;
}

/*int scalingTests(int tests_per, int scalars, int init_length)
*   1.  Seeds random generator.
*   2.  Opens/creates file for appending
*   3.  Runs the specified number of tests for 131072 values and tests the average of those tests against the complexity of O(NLogN), N being the currenbt number of nodes. Then it divides that value by 2 and decrease the power by 1 to test smaller datasets.
*   4.  It writes the total visits of each test into a csv file in csv format, which allows the user to upload that data into excel, and generate a simple graph if they please.
*   5.  If the averages stay below NLogN, then one is returned. If it goes above NLogN, then 0 is returned. 
*/
int scalingTests(int tests_per)
{
    srand48(time(0));
    FILE * RAHGHHH = fopen("ResultsInsert.csv", "a+");
    int decision = 1;
    int list_length = 131072;
    int power = 17;
    for(int k = 0; k < list_length; ++k)
    {
        float average = 0;
        for(int i = 0; i < tests_per; ++i)
        {
            RBST rbst = initRBST();
            int * array = malloc(sizeof(int) * list_length);
            for(int j = 0; j < list_length; ++j)
            {    
                array[j] = j;
            };
            int hold = testInsertRBST(list_length, array);
            average += hold;
            fprintf(RAHGHHH, "%d, ", hold);
            free(array);
            freeRBST(rbst);
        };
        fprintf(RAHGHHH, "\n");
        double nlogn = list_length * power;
        average /= tests_per;
        if(nlogn < average)
        {
            decision = 0;
        };
        list_length /= 2;
        power--;
    };
    fclose(RAHGHHH);
    return decision;
}