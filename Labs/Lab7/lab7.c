#include "lab7.h"

typedef struct Info {
    struct object * front;
    int size;
} Info;

typedef struct object {
    void * data;
    struct object * next;
} Object;

//O(1) function used to malloc a node. Since it has recurring use in this code.
Object * mallocObject(void * data){
    Object * p;
    p = malloc(sizeof(Object));
    if(p) //tests if malloc succeeded
    {
        p->data = data;
        p->next = NULL;

        return p; 
    }else{
        printf("ERROR: Object Malloc Failed"); //returns error upon malloc failure
        return NULL; //makes pointer NULL
    };
}



/* O(1). This function will initialize and return a Stack. If initialization fails, the info pointer in the
returned struct must be set to NULL. Your grade for this function will also include your stack imple-
mentation.*/

Stack initStack()
{
    Info * info;
    Object * dummy = mallocObject(NULL);  //mallocs dummy node
    Stack stack; //creates stack
    info = malloc(sizeof(Info)); //creates embedded info struct
    if(dummy && info) //tests for malloc successes
    {
        info->front = dummy; //sets top of stack to dummy node
        info->size = 0;
    }else{
        printf("ERROR: Stack Memory allocation failed"); //info malloc failed
        info = NULL;
    };
    stack.info = info; //sets stack info to info regardless of failure or success.
    return stack;
}

// O(1)

int getSize(Stack s){
    return s.info->size; //accesses the size member of the info struct
}

// O(1)

void * peekStack(Stack s){
    return s.info->front->next->data; //looks at the data in the first member of the stack
}

/* O(1). This function takes a stack, as well as a data item. It will push the item onto the top of the stack,
and return 0 if insertion was successful, or 1 if it was not. */

int pushStack(Stack s, void *data){
    Object * p;
    if((p = mallocObject(data)) != NULL) //mallocs object and tests fro NULL. Sets new member next to the og first member then sets new member to front of stack
    {
        p->next = s.info->front->next;
        s.info->front->next = p;
        ++(s.info->size); //adds to size
        return 0;
    }else{
        printf("ERROR: push failed");
        return 1;
    };
}

/* O(1). This function takes a stack, and pops the data item from the top of the stack. It returns the item
popped from the stack, or NULL if the stack is empty. */

void * popStack(Stack s){
    if(s.info->front->next != NULL){ //tests for empty stack then sets dummy object to the first member of stack and then removes it from the stack.
        Object * p;
        void * data;
        p = s.info->front->next;
        data = p->data;
        s.info->front->next = s.info->front->next->next;
        free(p);
        --(s.info->size);
        return data;
    }else{
        return NULL;
    };
}

/* O(n). This function takes a stack, as well as a data item. It returns 1 if the given data exists on the
stack, or 0 if it does not. */

int stackContains(Stack s, void *data)
{
    Object * p = s.info->front->next;
    while(p != NULL)
    {
        if(data == p->data) //tests every item with the passed data
        {
            return 1;
        }
        p = p->next; //indexes through the list 
    };
    return 0;
}

// O(n)

void freeStack(Stack s)
{
    Object * p;
    while(s.info->front != NULL)
    {
        p = s.info->front; //sets p to front of list
        s.info->front = s.info->front->next; //moves the list forward one
        free(p); //frees the member that was just unlinked from the list.
    };
    free(s.info); //free the info pointer.
}


