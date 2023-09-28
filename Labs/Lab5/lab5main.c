#include"lab5.h"

int main(void)
{
    Node * head, *p; 
    makeList(&head);
    makeList(&p);
    //int data = 3;
    //void * raah = &data;
    for(int i=0; i<100; i++){  
        insertAtTail(&head, &i); // Put int i at head of list 
    }; // Write a loop to print the values in the list 
    /*for (p = head; p->next != NULL; p = p->next)
    {
        //printf("%d\n", rah);
    };*/
    removeFromHead(&head);
    printf("The size of the list is %d", getSize(head));
    freeList(&head);
}