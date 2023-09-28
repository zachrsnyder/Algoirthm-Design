#include "lab8.h"

typedef struct Info
{
    struct Object * front;
    int ec;
    int size;
}Info;

typedef struct Object
{
    void * data;
    int priority;
    struct Object * next;
} Object;

int pqGetErrorCode(PQueue q)
{
    return q.info->ec; //checks the ec member of Info pointer inside of queue
}

//-2
// O(1)
PQueue pqInit()
{
    Object * dummy = malloc(sizeof(Object)); //malloc dummy node
    Info * queue = malloc(sizeof(Info)); //malloc info pointer
    PQueue q; //creates queue variable
    if(dummy && queue) //tests both mallocs for success
    {
        dummy->data = NULL; //NULLIFIES all variables of dummy
        dummy->next = NULL;
        dummy->priority = -1; //sets priority of dummy to a negative value
        queue->ec = 0; //initializing all members of info struct
        queue->size = 0;
        queue->front = dummy;
        q.info = queue;
    }else{
        printf("ERROR: Memory Allocation Failure. Returning NULL queue.");
        q.info = NULL;
    };
    return q;
}

//-3
// O(n)
int pqInsert(void *data, int priority, PQueue q)
{
    Object * p = malloc(sizeof(Object)); //mallocs new node
    Object * i = q.info->front; //index node set to front of list
    if(p) //testing malloc success
    {
        p->data = data; //initializing new node with the given data and priority
        p->priority = priority;
        p->next = NULL;
        while(i) //while haven't reached end of struct
        {
            if((i->next == NULL) || (p->priority >= i->next->priority)) //tests for empty/end of list, then checks if p has higher priority then the next member
            {
                p->next = i->next; //sets p next to the member that has a lower than or equal to priority.
                i->next = p; //sets i next = to p. Putting p inside of the list after i.
                ++q.info->size; //increase size of list via the info struct
                q.info->ec = 0; //success!
                return 0;
            };
            i = i->next; //if if statement fails, meaning the priority is higher than p's, i indexes further into the list.
        };
        return 0;//here in case of entirely empty list, which should not happen with dummy node implementation
    }else{
        q.info->ec = 1; //sets error code to one meaning malloc failure.
        return 1;
    };
}

//-4
// O(1)
void * pqRemoveMax(PQueue q)
{
    if(q.info->front->next == NULL) //tests for empty list
    {
        printf("Cannot dequeue from empty list. Returning NULL"); 
        q.info->ec = 2;
        return NULL;
    }else{
        void * data = q.info->front->next->data; //sets data variable to the soon to be removed data
        Object * p = q.info->front->next; //sets p object to the soon to be removed queue node
        q.info->front->next = q.info->front->next->next; //removes that member of queue from the link
        free(p); //free the node
        --q.info->size; //lowers size by one
        q.info->ec = 0;
        return data;
    };
}

//-5
// O(1)
void * pqPeek(PQueue q)
{
    if(q.info->front->next == NULL) //tests for empty list
    {
        printf("ERROR: Cannot view data from empty queue. Returning NULL");
        q.info->ec = 2;
        return NULL;
    };
    q.info->ec = 0; 
    return q.info->front->next->data; //returns data from first member in queue, which in this queue will also have the highest priority
}

//-6
// O(1)
int pqGetSize(PQueue q)
{
    return q.info->size; //returns size value of info struct
}

//-7
// O(n)
void pqFree(PQueue q)
{
    Object * p; //will be freed 
    while(q.info->front != NULL) //tests if the list is empty 
    {
        p = q.info->front; //p is the front of the list
        q.info->front = q.info->front->next; //removes the front of the list from the list
        free(p); //frees the old front of the list.
    };
    free(q.info); //frees the info struct pointer inside of the queue.
}
