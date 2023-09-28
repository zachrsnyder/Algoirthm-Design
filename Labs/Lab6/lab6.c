#include"lab6.h"

/*Function used to malloc and insert data into malloced list. Also sets the Node->next to NULL*/
Node * mallocNode(void * data)
{
    Node * p;
    p = malloc(sizeof(Node));
    if(p) //tests if malloc succeeded
    {
        p->data = data;
        p->next = NULL;

        return p; 
    }else{
        printf("ERROR: Malloc Failed"); //returns error upon malloc failure
        return NULL; //makes pointer NULL
    };
}

/*This function will initialize the provided pointer to Node * to an empty list. It will return 0 if
initialization was successful, or 1 if it was not.*/
int makeList(Node **list)
{
    Node * dummy;
    void * data = NULL;
    dummy = mallocNode(data); //dummy node is malloced
    if(dummy) //tests malloc then sets the passed node as a list of only a dummy node pointing to NULL;
    {
        dummy->next = NULL;
        *list = dummy;
        return 0;
    }else{
        return 1;
    };
}

/*This function takes a list, and returns the number of elements on the list. Note that if the list is
empty, the number of elements on the list is 0.*/
int getSize(Node *list)
{
    Node * p = list;
    int length = -1; //starts at -1 for dummy node
    if(p) //first tests if list is NULL
    {
        while(p){ //indexes through list adding to the length upon valid member.
            ++length;
            p = p->next;
        };
        return length; 
    } else return 0; //returns zero if pointer is invalid
}

/*This function takes a list, and returns the element at the given index, or NULL if the index is
invalid. Note that an invalid index is one which is < 0 or >= getSize(list).*/
void * getAtIndex(Node *list, int index)
{
    Node * p = list;
    if(index >= 0) //tests for integer validity
    {
        for(int i = -1;i < getSize(list); ++i) //cycles through list until i = index
        {
            if(i == index)
            {
                return(p->data);
            }else
            {
                p = p->next;
            };
        };
    }else{
        printf("ERROR: Cannot find negative index\n");
        return NULL;
    };
    printf("ERROR: Index not found. Returning NULL\n"); //assuming that the index was valid, and it still could not be found(meaning it was too big), NULL is returned
    return NULL;
}

/*This function takes a pointer to Node, and inserts the given data at the tail of the list. It returns
0 if insertion was successful, or 1 if insertion failed.*/
int insertAtTail(Node *list, void *data)
{
    Node * p; 
    p = list; //p to where list points
    while(p->next != NULL) //gets p to the tail of the list
    {
        p = p->next;
    };
    Node * tail; //creates node to be added to the tail
    if((tail = mallocNode(data)) != NULL) //initialize tail
    { 
        p->next = tail; //puts tail at the end of the list
        return 0;
    }else{
        return 1; //returns zero if initialization fails
    };
}

/*This function takes a pointer to Node, and removes the element at the head of the list (if any). It
will return the data which was removed from the list, or NULL if the list was empty. You may assume
that no data on the list will be NULL.*/
void * removeFromHead(Node *list)
{
    if(list->next != NULL)
    {
        Node * p;
        Node * holder;
        void * dataN = list->next->data; //takes the data from the head member
        p = list;
        holder = p->next; //holder is equal to first member of list
        p->next = p->next->next; //the first member is then set to equal the second member.
        free(holder); //the first members memory is freed
        return(dataN); //returns the data from the removed member
    }else
    {
        printf("ERROR: Cannot remove head of empty list."); //if the list is empty Null is returned
        return NULL;
    }
}

/*This function takes a pointer to Node *, and frees the memory allocated to the list. After freeing,
it sets the pointer to NULL. Note that the data on the list is not considered part of the memory
allocated to the list.*/
void freeList(Node **list){
    Node * p;
    while(p != NULL)
    {
        p = *list;
        *list = (*list)->next;
        free(p);
    };
    *list = NULL;
}