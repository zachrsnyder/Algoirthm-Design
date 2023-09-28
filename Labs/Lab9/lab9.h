#include <stdio.h>
#include <stdlib.h>


void * makeArray(int arraySize, int elementSize);

int getSize(void *array);

typedef struct {
	unsigned int flightNumber;
	float distance;
	unsigned short passengers;
} Flight;


// O(log(n))

int searchFlights(Flight *array, Flight *query);

// O(1)

int compareFlights(Flight *a, Flight *b);

void freeArray(void *array);

