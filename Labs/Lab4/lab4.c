#include"lab4.h"

void * makeArray(int arraySize, int elementSize)
{
    int * array; //creates array to return with memory
    
    if((array = malloc(arraySize * elementSize + sizeof(int))) == NULL) //allocates memory, prints error code upon failure
    { 
        printf("***ERROR: Memory allocation failed, returning NULL***");
        
        return NULL;
    } else //proceeds to store size in array upon malloc success
    {
        array[0] = arraySize; //stores size of array in first element
    
        ++array; //indexes one integer length forward
    
        return array; //returns the array indexed one forward
    };
}

int getSize(void *array)
{
    int size = 0; //variable to store size
    
    if((size = *((int*)array-1)) == 0) //indexes array back one to find size, and tests that the memory has a size in it
    {
        printf("***ERROR: size not initialized before array***");
        
        return 0;
    } 
    else 
    {
        return size; //returns size upon finding it before the array
    };
}

int countWithStock(InventoryItem *items, int stockCount)
{
    int countTotal = 0; //the tally of equivalent stock counts
    for(int i = 0; i < getSize(items); ++i) //increments through every item
    {
        if(items[i].stockCount == stockCount) //checks item stockcount for equivalency
        ++countTotal;
    };
    return countTotal;
}

void freeArray(void *array)
{
    free((int*)array-1); //frees memory of array including the index in front of it where size was held
}

