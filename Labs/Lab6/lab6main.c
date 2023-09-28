#include"lab6.h"


int main(void){
    Node * head,*p; 
    void * data = NULL;
    printf("test makelist EC: %d", makeList(&head));
    printf("size of list is %d", getSize(head));
    getAtIndex(head,-1);
    for(int i=0; i<100; i++){  
        insertAtTail(head, data);
        printf("size of list is %d", getSize(head)); // Put int i at head of list 
    }; // Write a loop to print the values in the list 
    for (p = head->next; p->next != NULL; p = p->next)
    {
        printf("%p\n", p->data);
    };
    //printf("The number at index %d is %d", 5, getAtIndex(head,5)); 
    printf("size of list is %d", getSize(head));
    removeFromHead(head);
    printf("size of list is %d", getSize(head));
    freeList(&head);
};