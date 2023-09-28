#include"lab9.h"

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

// O(log(n))
int binarySearchFlight(int flightNum, Flight * array, int first, int last)
{
    if(array)
    {
        int mid;
        if (first == last){ //the whole list has been searched or the list is empty
            puts("flight not found returning negative index");
            return(-1);
        };
        mid = first + (last-first)/2; //finds middle of remaining part of list
        if (flightNum < array[mid].flightNumber) //if the flight number is lower it searches from first to mid
        {
            return(binarySearchFlight(flightNum,array,first,mid));
        }
        else if (flightNum > array[mid].flightNumber) //if flight number is higher it searches from mid to last
        {
            return(binarySearchFlight(flightNum, array, mid + 1, last));
        };
        return(mid); //once all of the if statements have failed, the query has successfully been found
    }else{
        puts("Invalid list. Returning negative index.\n");
        return -1;
    }
}

int searchFlights(Flight *array, Flight *query)
{
    if(query && array) //tests for valid pointers
    {
        int queryNum = query->flightNumber; //using flight number to search
        int size = getSize(array); //uses getSize function to get size of list
        return(binarySearchFlight(queryNum, array, 0, size - 1));
    }else{
        puts("ERROR: invalid flight list or flight to search");
        return(-1);
    };
}


// O(1)

int compareFlights(Flight *a, Flight *b)
{
    if(a && b)
    {
        if(a->distance > b->distance) //tests distances for all possible comparisons. If it isn't greater than or less than, they must be equal
        {
            return 1;
        };
        if(a->distance < b->distance)
        {
            return -1;
        };
        return 0;
    }else{
        printf("invalid flight pointer. Returning -99 just cause");
        return -99;
    };
}

void freeArray(void *array)
{
    free((int*)array-1); //frees memory of array including the index in front of it where size was held
}
