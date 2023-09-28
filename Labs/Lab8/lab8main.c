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

int main()
{
    PQueue p;
    p = pqInit();
    //void * data;
    int j = 1;
    for(int i = 100; i > 0; --i)
    {
        pqInsert(&i,j,p);
        printf("i = %d\t", i);
        printf("size of queue = %d\n", pqGetSize(p));
        j++;
    };
    //printf("%d\n", getSizeT(p));
    printf("%d\n", *((int*)pqRemoveMax(p)));
    pqRemoveMax(p);
    printf("%d\n", *((int*)pqRemoveMax(p)));
    printf("%d\n", *((int*)pqRemoveMax(p)));
    while(p.info->front->next != NULL)
    {
        printf("The highest prioirty value in the queue = %d\n", *((int*)pqRemoveMax(p)));
        //printf("The size of the priority queue = %d\n", pqGetSize(p));
    };
    pqFree(p);
}