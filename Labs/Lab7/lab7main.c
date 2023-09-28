#include"lab7.h"

typedef struct Info {
    struct object * front;
    int size;
} Info;

typedef struct object {
    void * data;
    struct object * next;
} Object;

int main(void)
{
    Stack stack;
    stack = initStack();
    void * data = NULL;
    for(int i=0; i<100; i++){  
        pushStack(stack,data); // Put int i at head of list 
    }; // Write a loop to print the values in the list 
    printf("%p\n", peekStack(stack));
    printf("The size of the stack is %d\n", getSize(stack)); 
    printf("Does %d exist in the stack. One for yes Zero for no:%d\n", 60, stackContains(stack, data));
    while(stack.info->front->next != NULL)
    {
        printf("%p\n", popStack(stack));
        printf("The size of the stack is %d\n", getSize(stack));
    }; 
    printf("The size of the stack is %d\n", getSize(stack)); 
    freeStack(stack);
}