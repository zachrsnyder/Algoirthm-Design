/*
Lab 2
Zach Snyder
CS2050
2/3/2023
*/
#include "lab2.h"
int makeArray(int **array, int size)
{
    *array = malloc(size*sizeof(int)); //gives the array pointer to which **array points enough storage for an array of "size"
    if(*array == NULL) //tests if malloc correctly allocated the memory
    {
        printf("***ERROR: malloc failed***"); //prints this if malloc fails.
        return 1; //returns one upon failure
    }
    else return 0; //returns zero upon succes
}

void initArray(int *array, int size)
{
    if(size <= 0) //tests size value making sure its positive
    {
        printf("***ERROR: invalid size value***"); 
        return;
    }
    else
    {
        for(int i = 0; i < size; ++i) //indexes through each element of the array as a value of i
        {
            *(array + i) = 0; //indexes using pointer arithmetic
        };
    };    
}

int multiplyPositive(int *array, int size, int multiplicand)
{
    if(size <= 0)
    {
        printf("***ERROR: invalid size value***"); //tests size value making sure its positive
        return 0;
    }
    else
    {
        int total = 0;
        for(int i = 0; i < size; ++i)
        {
            if(*(array+i) != 0) //because zero % 2 is still 0, I tested if it was zero before continuing with the function.
            {
                if(*(array+i) % 2 == 0) //this means that the number is even, provided that it is not zero.
                {
                    *(array+i) *= multiplicand; //multiplies even elements by multiplicand
                    ++total; //once multiplication is done it tallies the total multiplications done
                };
            };
        };
        return total;//returns total even numbers and total multiplications performed.
    };
}

void freeArray(int **array)
{
    free(*array); //frees where the pointer to an array pointer points. Therefore, it frees the array pointer.
    *array = NULL; //sets original pointer to NULL
}