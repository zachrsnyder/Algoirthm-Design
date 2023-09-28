#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
	void *data;
	Node *next;
};


int makeList(Node **list);

int getSize(Node *list);

int insertAtTail(Node **list, void *data);

void * removeFromHead(Node **list);

void freeList(Node **list);

