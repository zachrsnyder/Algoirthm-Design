#include"lab5.h"
/*The function allocates memory using malloc to create an empty member of a linked list. 
After mallocing it tests for malloc success. Upon success it sets the new list member's 
next pointer to NULL and returns 0. Upon failure it prints an error message and then returns 
zero, the inital pointer is unchanged.*/
int makeList(Node **list)
{
    Node * p;
    p = malloc(sizeof(Node)); //allocates enough memory for a NODE
    if(p){
        p->next = NULL; //sets pointer to NULL
        *list = p; //sets the passed Node pointer equal to p
        return(0);
    }else{
        printf("***ERROR: Memory Allocation Failure***");
        return(0);
    };
};
/*This function takes a struct pointer that it expects to be at the beginning of a linked list.
It then cycles through the list adding a tally to the length every time the next pointer of the list
member points to another member. It then returns that length.*/
int getSize(Node *list)
{
    Node * p;
    int length = 0;
    for(p = list; p != NULL; p = p->next) //cycles through the list
    {
        ++length; //adds to length tally
    };
    return length;
};
/*This function is used to insert data to the back end of a linked list. It does this by taking a pointer
to a struct pointer that it is expecting to point to the head of a linked list, then indexing through the 
list until finally the next pointer of the member points to NULL. Once the pointer is indexed to NULL, 
it uses the "makelist"  function to malloc memory for the new member. Upon success of that function, it 
assigns the data parameter of the function to the new member of the list, and it sets the next pointer of 
the member at the tail of the list to the newly created member. Then it returns zero. Upon failure to malloc, 
no changes are then made to the original list, and the function returns 0.*/
int insertAtTail(Node **list, void *data)
{
    Node * p; 
    p = *list; //p to where list points
    while(p->next != NULL) //gets p to the tail of the list
    {
        p = p->next;
    };
    Node * tail; //creates node to be added to the tail
    if((makeList(&tail)) == 0) //initialize tail
    { 
        tail->data = data; //sets tail data equal to the data passed
        p->next = tail; //puts tail at the end of the list
        return 0;
    } else return 0; //returns zero if initialization fails
};
/*This function takes a pointer to the head of a linked list. It then sets to node structs 
(acting as list members) equal to the head of the list. It also creates a void pointer to 
store the data that the head of the list holds, which will then be returned upon removal of 
that member of the list. It indexes one of the node pointers to the next member of the list. 
It then takes the other pointer and frees the memory that it has allocated. The list from the 
calling program is then set to the list pointer that is set to the previous second member of 
the list.*/
void * removeFromHead(Node **list)
{
    Node * p;
    Node * head = *list; //creates head pointer to index through the list
    void * dataP; //used to store the data from the head
    dataP = head->data;
    p = head; //p will be freed
    head = head->next; //moves head to the second item in the list
    free(p); //frees p, which is the first item on the list
    *list = head; //sets the list equal to the head, which points to the second item of the previous list. 
    return dataP; //returns data from the freed NODE
}
/*This function takes a pointer to a linked list head. It then sets a node pointer equal to the head of the list. 
It tests that pointer for NULL. If it isn't NULL (meaning the list isnt over), it sets another node pointer equal 
to where the other one is pointing, and indexes the first pointer forward to the next member of the list. It then 
free the member before it, which is what the other node pointer is pointing to. It does this until the end of the 
list is reached. Finally, the pointer of the calling program is NULLified and the function terminates.*/
void freeList(Node **list)
{
    Node * p;
    Node * head = *list;
    while(head != NULL) //moves through the list
    {
        p = head; 
        head = head->next; //head is going through the list and p is freeing before ahead of it.
        free(p);
    };
    *list = NULL; //sets original pointer to NULL
    return;
}
